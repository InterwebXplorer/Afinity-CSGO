#pragma once

#pragma region renderbeams_definitions
#define TE_BEAMPOINTS 0
#define TE_SPRITE 1
#define TE_BEAMDISK 2
#define TE_BEAMCYLINDER 3
#define TE_BEAMFOLLOW 4
#define TE_BEAMRING 5
#define TE_BEAMSPLINE 6
#define TE_BEAMRINGPOINT 7
#define TE_BEAMLASER 8
#define TE_BEAMTESLA 9
#define MAX_BEAM_ENTS 10
#define NOISE_DIVISIONS 128
#pragma endregion

enum EBeamType : unsigned int {
	FBEAM_STARTENTITY = 0x00000001,
	FBEAM_ENDENTITY = 0x00000002,
	FBEAM_FADEIN = 0x00000004,
	FBEAM_FADEOUT = 0x00000008,
	FBEAM_SINENOISE = 0x00000010,
	FBEAM_SOLID = 0x00000020,
	FBEAM_SHADEIN = 0x00000040,
	FBEAM_SHADEOUT = 0x00000080,
	FBEAM_ONLYNOISEONCE = 0x00000100,
	FBEAM_NOTILE = 0x00000200,
	FBEAM_USE_HITBOXES = 0x00000400,
	FBEAM_STARTVISIBLE = 0x00000800,
	FBEAM_ENDVISIBLE = 0x00001000,
	FBEAM_ISACTIVE = 0x00002000,
	FBEAM_FOREVER = 0x00004000,
	FBEAM_HALOBEAM = 0x00008000,
	FBEAM_REVERSED = 0x00010000,
};

struct BeamTrail_t {
	BeamTrail_t *pNext;
	float flDie;
	Vector vecOrigin;
	Vector vecVelocity;
};

struct Beam_t {
	Beam_t() = default;

	virtual const Vector &GetRenderOrigin() = 0;
	virtual const QAngle &GetRenderAngles() = 0;
	virtual const matrix3x4_t &RenderableToWorldTransform() = 0;
	virtual void GetRenderBounds(Vector &vecMins, Vector &vecMaxs) = 0;
	virtual bool ShouldDraw() = 0;
	virtual bool IsTransparent() = 0;
	virtual int DrawModel(int nFlags) = 0;
	virtual void ComputeFxBlend() = 0;
	virtual int GetFxBlend() = 0;

	Vector vecMins;
	Vector vecMaxs;
	int *pQueryHandleHalo;
	float flHaloProxySize;
	Beam_t *pNext;
	int nType;
	int nFlags;

	int nAttachments;
	Vector vecAttachment[MAX_BEAM_ENTS];
	Vector vecDelta;

	float flTime;
	float flFrequence;

	float flDie;
	float flWidth;
	float flEndWidth;
	float flFadeLength;
	float flAmplitude;
	float flLife;

	float r, g, b;
	float flBrightness;

	float flSpeed;

	float flFrameRate;
	float flFrame;
	int nSegments;

	CBaseHandle hEntity[MAX_BEAM_ENTS];
	int nAttachmentIndex[MAX_BEAM_ENTS];

	int nModelIndex;
	int nHaloIndex;
	float flHaloScale;
	int iFrameCount;
	float flRgNoise[NOISE_DIVISIONS + 1];

	BeamTrail_t *pTrail;

	float flStartRadius;
	float flEndRadius;

	bool bCalculatedNoise;
	float flHDRColorScale;
};

struct BeamInfo_t {
	BeamInfo_t() {
		nType = TE_BEAMPOINTS;
		nSegments = -1;
		pszModelName = nullptr;
		pszHaloName = nullptr;
		nModelIndex = -1;
		nHaloIndex = -1;
		bRenderable = true;
		nFlags = 0;
	}

	int nType;

	CBaseEntity *pStartEntity;
	int iStartAttachment;
	CBaseEntity *pEndEntity;
	int iEndAttachment;

	Vector vecStart;
	Vector vecEnd;

	int nModelIndex;
	const char *pszModelName;
	int nHaloIndex;
	const char *pszHaloName;
	float flHaloScale;
	float flLife;
	float flWidth;
	float flEndWidth;
	float flFadeLength;
	float flAmplitude;
	float flBrightness;
	float flSpeed;
	int iStartFrame;
	float flFrameRate;
	float flRed;
	float flGreen;
	float flBlue;
	bool bRenderable;
	int nSegments;
	int nFlags;

	Vector vecCenter;
	float flStartRadius;
	float flEndRadius;
};

class CBeam;
class IViewRenderBeams {
public:
	virtual void InitBeams() = 0;
	virtual void ShutdownBeams() = 0;
	virtual void ClearBeams() = 0;
	virtual void UpdateTempEntBeams() = 0;

	virtual void DrawBeam(CBeam *pBeam, const RenderableInstance_t &instance, ITraceFilter *pEntityBeamTraceFilter = nullptr) = 0;
	virtual void DrawBeam(Beam_t *pBeam) = 0;

	virtual void KillDeadBeams(CBaseEntity *pEntity) = 0;

	virtual Beam_t *CreateBeamEnts(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t *CreateBeamEntPoint(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t *CreateBeamPoints(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t *CreateBeamRing(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t *CreateBeamRingPoint(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t *CreateBeamCirclePoints(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t *CreateBeamFollow(BeamInfo_t &beamInfo) = 0;

	virtual void FreeBeam(Beam_t *pBeam) = 0;
	virtual void UpdateBeamInfo(Beam_t *pBeam, BeamInfo_t &beamInfo) = 0;

	virtual void CreateBeamEnts(int iStartEntity, int iEndEntity, int nModelIndex, int iHaloIndex, float flHaloScale,
								float flLife, float flWidth, float flEndWidth, float flFadeLength, float flAmplitude,
								float flBrightness, float flSpeed, int flStartFrame,
								float flFrameRate, float r, float g, float b, int iType = -1) = 0;
	virtual void CreateBeamEntPoint(int iStartEntity, const Vector *pStart, int iEndEntity, const Vector *pEnd,
									int nModelIndex, int iHaloIndex, float flHaloScale,
									float flLife, float flWidth, float flEndWidth, float flFadeLength, float flAmplitude,
									float flBrightness, float flSpeed, int iStartFrame,
									float flFrameRate, float r, float g, float b) = 0;
	virtual void CreateBeamPoints(Vector &vecStart, Vector &vecEnd, int nModelIndex, int iHaloIndex, float flHaloScale,
								  float flLife, float flWidth, float flEndWidth, float flFadeLength, float flAmplitude,
								  float flBrightness, float flSpeed, int iStartFrame,
								  float flFrameRate, float r, float g, float b) = 0;
	virtual void CreateBeamRing(int iStartEntity, int iEndEntity, int nModelIndex, int iHaloIndex, float flHaloScale,
								float flLife, float flWidth, float flEndWidth, float flFadeLength, float flAmplitude,
								float flBrightness, float flSpeed, int iStartFrame,
								float flFrameRate, float r, float g, float b, int iFlags = 0) = 0;
	virtual void CreateBeamRingPoint(const Vector &vecCenter, float flStartRadius, float flEndRadius, int nModelIndex, int iHaloIndex, float flHaloScale,
									 float flLife, float flWidth, float flEndWidth, float flFadeLength, float flAmplitude,
									 float flBrightness, float flSpeed, int iStartFrame,
									 float flFrameRate, float r, float g, float b, int iFlags = 0) = 0;
	virtual void CreateBeamCirclePoints(int iType, Vector &vecStart, Vector &vecEnd,
										int nModelIndex, int iHaloIndex, float flHaloScale, float flLife, float flWidth,
										float flEndWidth, float flFadeLength, float flAmplitude, float flBrightness, float flSpeed,
										int iStartFrame, float flFrameRate, float r, float g, float b) = 0;
	virtual void CreateBeamFollow(int startEnt, int nModelIndex, int iHaloIndex, float flHaloScale,
								  float flLife, float flWidth, float flEndWidth, float flFadeLength, float r, float g, float b,
								  float flBrightness) = 0;
};