#pragma once
#include "imaterialsystem.h"

struct surfacephysicsparams_t {
	float flFriction;
	float flElasticity;
	float flDensity;
	float flThickness;
	float flDampening;
};

struct surfaceaudioparams_t {
	float flReflectivity;
	float flHardnessFactor;
	float flRoughnessFactor;
	float flRoughThreshold;
	float flHardThreshold;
	float flHardVelocityThreshold;
	float flHighPitchOcclusion;
	float flMidPitchOcclusion;
	float flLowPitchOcclusion;
};

struct surfacesoundnames_t {
	std::uint16_t uWalkStepLeft;
	std::uint16_t uWalkStepRight;
	std::uint16_t uRunStepLeft;
	std::uint16_t uRunStepRight;
	std::uint16_t uImpactSoft;
	std::uint16_t uImpactHard;
	std::uint16_t uScrapeSmooth;
	std::uint16_t uScrapeRough;
	std::uint16_t uBulletImpact;
	std::uint16_t uRolling;
	std::uint16_t uBreakSound;
	std::uint16_t uStrainSound;
};

struct surfacesoundhandles_t {
	std::uint16_t uWalkStepLeft;
	std::uint16_t uWalkStepRight;
	std::uint16_t uRunStepLeft;
	std::uint16_t uRunStepRight;
	std::uint16_t uImpactSoft;
	std::uint16_t uImpactHard;
	std::uint16_t uScrapeSmooth;
	std::uint16_t uScrapeRough;
	std::uint16_t uBulletImpact;
	std::uint16_t uRolling;
	std::uint16_t uBreakSound;
	std::uint16_t uStrainSound;
};

struct surfacegameprops_t {
	float flMaxSpeedFactor;
	float flJumpFactor;
	float flPenetrationModifier;
	float flDamageModifier;
	MaterialHandle_t hMaterial;
	std::byte dClimbable;
	std::byte pad0[0x4];
};

struct surfacedata_t {
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
	surfacesoundhandles_t soundhandles;
};

class IPhysicsSurfaceProps {
public:
	virtual ~IPhysicsSurfaceProps() {}
	virtual int ParseSurfaceData(const char *szFileName, const char *szTextFile) = 0;
	virtual int SurfacePropCount() const = 0;
	virtual int GetSurfaceIndex(const char *szSurfacePropName) const = 0;
	virtual void GetPhysicsProperties(int iSurfaceDataIndex, float *flDensity, float *flThickness, float *flFriction, float *flElasticity) const = 0;
	virtual surfacedata_t *GetSurfaceData(int iSurfaceDataIndex) = 0;
	virtual const char *GetString(unsigned short shStringTableIndex) const = 0;
	virtual const char *GetPropName(int iSurfaceDataIndex) const = 0;
	virtual void SetWorldMaterialIndexTable(int *iMapArray, int iMapSize) = 0;
	virtual void GetPhysicsParameters(int iSurfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;
};
