#pragma once
#include <functional>
#include "../datatypes/matrix.h"
#include "../datatypes/utlvector.h"
#include "../bspflags.h"

#pragma region enginetrace_enumerations
enum EDispSurfFlags : int {
	DISPSURF_FLAG_SURFACE = (1 << 0),
	DISPSURF_FLAG_WALKABLE = (1 << 1),
	DISPSURF_FLAG_BUILDABLE = (1 << 2),
	DISPSURF_FLAG_SURFPROP1 = (1 << 3),
	DISPSURF_FLAG_SURFPROP2 = (1 << 4)
};

enum ETraceType : int {
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
	TRACE_FILTERSKY
};

enum EDebugTraceCounterBehavior : int {
	TRACE_COUNTER_SET = 0,
	TRACE_COUNTER_INC,
};
#pragma endregion

struct BrushSideInfo_t {
	VectorAligned vecPlane;
	std::uint16_t uBevel;
	std::uint16_t uThin;
};

struct cplane_t {
	Vector vecNormal;
	float flDistance;
	std::byte dType;
	std::byte dSignBits;
	std::byte pad[0x2];
};

struct csurface_t {
	const char *szName;
	short nSurfaceProps;
	std::uint16_t uFlags;
};

class CBaseTrace {
public:
	CBaseTrace() {}

	Vector vecStart;
	Vector vecEnd;
	cplane_t plane;
	float flFraction;
	int iContents;
	std::uint16_t fDispFlags;
	bool bAllSolid;
	bool bStartSolid;
};

class CBaseEntity;
class CGameTrace : public CBaseTrace {
public:
	CGameTrace() : pHitEntity(nullptr) {}

	float flFractionLeftSolid;
	csurface_t surface;
	int iHitGroup;
	short sPhysicsBone;
	std::uint16_t uWorldSurfaceIndex;
	CBaseEntity *pHitEntity;
	int iHitbox;

	inline bool DidHit() const {
		return (flFraction < 1.0f || bAllSolid || bStartSolid);
	}

	inline bool IsVisible() const {
		return (flFraction > 0.97f);
	}

private:
	CGameTrace(const CGameTrace &other) {
		this->vecStart = other.vecStart;
		this->vecEnd = other.vecEnd;
		this->plane = other.plane;
		this->flFraction = other.flFraction;
		this->iContents = other.iContents;
		this->fDispFlags = other.fDispFlags;
		this->bAllSolid = other.bAllSolid;
		this->bStartSolid = other.bStartSolid;
		this->flFractionLeftSolid = other.flFractionLeftSolid;
		this->surface = other.surface;
		this->iHitGroup = other.iHitGroup;
		this->sPhysicsBone = other.sPhysicsBone;
		this->uWorldSurfaceIndex = other.uWorldSurfaceIndex;
		this->pHitEntity = other.pHitEntity;
		this->iHitbox = other.iHitbox;
	}
};

using Trace_t = CGameTrace;

struct Ray_t {
	Ray_t(const Vector &vecStart, const Vector &vecEnd) : vecStart(vecStart), vecDelta(vecEnd - vecStart), matWorldAxisTransform(nullptr), bIsRay(true) {
		this->bIsSwept = (this->vecDelta.LengthSqr() != 0.f);
	}

	Ray_t(const Vector &vecStart, const Vector &vecEnd, const Vector &vecMins, const Vector &vecMaxs) {
		this->vecDelta = vecEnd - vecStart;

		this->matWorldAxisTransform = nullptr;
		this->bIsSwept = (this->vecDelta.LengthSqr() != 0.f);

		this->vecExtents = vecMaxs - vecMins;
		this->vecExtents *= 0.5f;
		this->bIsRay = (this->vecExtents.LengthSqr() < 1e-6f);

		this->vecStartOffset = vecMins + vecMaxs;
		this->vecStartOffset *= 0.5f;
		this->vecStart = vecStart + this->vecStartOffset;
		this->vecStartOffset *= -1.0f;
	}

	VectorAligned vecStart;
	VectorAligned vecDelta;
	VectorAligned vecStartOffset;
	VectorAligned vecExtents;
	const matrix3x4_t *matWorldAxisTransform;
	bool bIsRay;
	bool bIsSwept;
};

class IHandleEntity;
class ITraceFilter {
public:
	virtual bool ShouldHitEntity(IHandleEntity *pEntity, int fContentsMask) = 0;
	virtual ETraceType GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter {
	using FilterCallbackFn = std::function<bool(IHandleEntity *, int)>;

public:
	CTraceFilter(const IHandleEntity *pSkipEntity, ETraceType iTraceType = TRACE_EVERYTHING)
		: pSkip(pSkipEntity), iTraceType(iTraceType) {}

	CTraceFilter(FilterCallbackFn &&checkCallback, ETraceType iTraceType = TRACE_EVERYTHING)
		: checkCallback(std::move(checkCallback)), iTraceType(iTraceType) {}

	bool ShouldHitEntity(IHandleEntity *pHandleEntity, int fContentsMask) override {

		if (checkCallback != nullptr)
			return checkCallback(pHandleEntity, fContentsMask);

		return pHandleEntity != pSkip;
	}

	ETraceType GetTraceType() const override {
		return iTraceType;
	}

private:
	const IHandleEntity *pSkip = nullptr;
	FilterCallbackFn checkCallback = nullptr;
	ETraceType iTraceType = TRACE_EVERYTHING;
};

class ITraceListData {
public:
	virtual ~ITraceListData() {}
	virtual void Reset() = 0;
	virtual bool IsEmpty() = 0;
	virtual bool CanTraceRay(const Ray_t &ray) = 0;
};

class IEntityEnumerator {
public:
	virtual bool EnumEntity(IHandleEntity *pHandleEntity) = 0;
};

struct virtualmeshlist_t;
struct AABB_t;
class ICollideable;
class CPhysCollide;
class CBrushQuery;
class IEngineTrace {
public:
	virtual int GetPointContents(const Vector &vecAbsPosition, int fContentsMask = MASK_ALL, IHandleEntity **ppEntity = nullptr) = 0;
	virtual int GetPointContents_WorldOnly(const Vector &vecAbsPosition, int fContentsMask = MASK_ALL) = 0;
	virtual int GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) = 0;
	virtual void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEntity, Trace_t *pTrace) = 0;
	virtual void ClipRayToCollideable(const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, Trace_t *pTrace) = 0;
	virtual void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, Trace_t *pTrace) = 0;
	virtual void SetupLeafAndEntityListRay(const Ray_t &ray, ITraceListData *pTraceData) = 0;
	virtual void SetupLeafAndEntityListBox(const Vector &vecBoxMin, const Vector &vecBoxMax, ITraceListData *pTraceData) = 0;
	virtual void TraceRayAgainstLeafAndEntityList(const Ray_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, Trace_t *pTrace) = 0;
	virtual void SweepCollideable(ICollideable *pCollide, const Vector &vecAbsStart, const Vector &vecAbsEnd, const Vector &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, Trace_t *pTrace) = 0;
	virtual void EnumerateEntities(const Ray_t &ray, bool bTriggers, IEntityEnumerator *pEnumerator) = 0;
	virtual void EnumerateEntities(const Vector &vecAbsMins, const Vector &vecAbsMaxs, IEntityEnumerator *pEnumerator) = 0;
	virtual ICollideable *GetCollideable(IHandleEntity *pEntity) = 0;
	virtual int GetStatByIndex(int nIndex, bool bClear) = 0;
	virtual void GetBrushesInAABB(const Vector &vecMins, const Vector &vecMaxs, CUtlVector<int> *pOutput, int fContentsMask = MASK_ALL) = 0;
	virtual CPhysCollide *GetCollidableFromDisplacementsInAABB(const Vector &vecMins, const Vector &vecMaxs) = 0;
	virtual int GetNumDisplacements() = 0;
	virtual void GetDisplacementMesh(int nIndex, virtualmeshlist_t *pMeshTriList) = 0;
	virtual bool GetBrushInfo(int iBrush, CUtlVector<BrushSideInfo_t> *pBrushSideInfoOut, int *pContentsOut) = 0;
	virtual bool PointOutsideWorld(const Vector &vecPoint) = 0;
	virtual int GetLeafContainingPoint(const Vector &vecPoint) = 0;
	virtual ITraceListData *AllocTraceListData() = 0;
	virtual void FreeTraceListData(ITraceListData *pListData) = 0;
	virtual int GetSetDebugTraceCounter(int iValue, EDebugTraceCounterBehavior behavior) = 0;
	virtual int GetMeshesFromDisplacementsInAABB(const Vector &vecMins, const Vector &vecMaxs, virtualmeshlist_t *pOutputMeshes, int nMaxOutputMeshes) = 0;
	virtual void GetBrushesInCollideable(ICollideable *pCollideable, CBrushQuery &BrushQuery) = 0;
	virtual bool IsFullyOccluded(int nOcclusionKey, const AABB_t &aabb1, const AABB_t &aabb2, const Vector &vecShadow) = 0;
	virtual void SuspendOcclusionTests() = 0;
	virtual void ResumeOcclusionTests() = 0;
	virtual void FlushOcclusionQueries() = 0;
};
