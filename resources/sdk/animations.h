#pragma once
#include "datatypes/vector.h"
#include "datatypes/qangle.h"
#include "../utils/memory.h"

#define MAXOVERLAYS 15

enum ESequenceActivity : int {
	ACT_CSGO_NULL = 957,
	ACT_CSGO_DEFUSE,
	ACT_CSGO_DEFUSE_WITH_KIT,
	ACT_CSGO_FLASHBANG_REACTION,
	ACT_CSGO_FIRE_PRIMARY,
	ACT_CSGO_FIRE_PRIMARY_OPT_1,
	ACT_CSGO_FIRE_PRIMARY_OPT_2,
	ACT_CSGO_FIRE_SECONDARY,
	ACT_CSGO_FIRE_SECONDARY_OPT_1,
	ACT_CSGO_FIRE_SECONDARY_OPT_2,
	ACT_CSGO_RELOAD,
	ACT_CSGO_RELOAD_START,
	ACT_CSGO_RELOAD_LOOP,
	ACT_CSGO_RELOAD_END,
	ACT_CSGO_OPERATE,
	ACT_CSGO_DEPLOY,
	ACT_CSGO_CATCH,
	ACT_CSGO_SILENCER_DETACH,
	ACT_CSGO_SILENCER_ATTACH,
	ACT_CSGO_TWITCH,
	ACT_CSGO_TWITCH_BUYZONE,
	ACT_CSGO_PLANT_BOMB,
	ACT_CSGO_IDLE_TURN_BALANCEADJUST,
	ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING,
	ACT_CSGO_ALIVE_LOOP,
	ACT_CSGO_FLINCH,
	ACT_CSGO_FLINCH_HEAD,
	ACT_CSGO_FLINCH_MOLOTOV,
	ACT_CSGO_JUMP,
	ACT_CSGO_FALL,
	ACT_CSGO_CLIMB_LADDER,
	ACT_CSGO_LAND_LIGHT,
	ACT_CSGO_LAND_HEAVY,
	ACT_CSGO_EXIT_LADDER_TOP,
	ACT_CSGO_EXIT_LADDER_BOTTOM
};

class matrix3x4a_t;
class CBaseAnimating;
class CBoneAccessor {
public:
	const CBaseAnimating *pAnimating;
	matrix3x4a_t *matBones;
	int nReadableBones;
	int nWritableBones;
};

class CAnimationLayer {
public:
	float flAnimationTime;
	float flFadeOut;
	void *pStudioHdr;
	int nDispatchedSrc;
	int nDispatchedDst;
	int iOrder;
	std::uintptr_t nSequence;
	float flPrevCycle;
	float flWeight;
	float flWeightDeltaRate;
	float flPlaybackRate;
	float flCycle;
	void *pOwner;
	int nInvalidatePhysicsBits;
};

class CBaseEntity;
class CBaseCombatWeapon;
class CCSGOPlayerAnimState {
public:
	void Create(CBaseEntity *pEntity) {
		using CreateAnimationStateFn = void(__thiscall *)(void *, CBaseEntity *);
		static auto oCreateAnimationState = reinterpret_cast<CreateAnimationStateFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46"));

		if (oCreateAnimationState == nullptr)
			return;

		oCreateAnimationState(this, pEntity);
	}

	void Update(QAngle angView) {
		using UpdateAnimationStateFn = void(__vectorcall *)(void *, void *, float, float, float, void *);
		static auto oUpdateAnimationState = reinterpret_cast<UpdateAnimationStateFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24"));

		if (oUpdateAnimationState == nullptr)
			return;

		oUpdateAnimationState(this, nullptr, 0.0f, angView.y, angView.x, nullptr);
	}

	void Reset() {
		using ResetAnimationStateFn = void(__thiscall *)(void *);
		static auto oResetAnimationState = reinterpret_cast<ResetAnimationStateFn>(MEM::FindPattern(CLIENT_DLL, "56 6A 01 68 ? ? ? ? 8B F1"));

		if (oResetAnimationState == nullptr)
			return;

		oResetAnimationState(this);
	}

	std::byte pad0[0x60];
	CBaseEntity *pEntity;
	CBaseCombatWeapon *pActiveWeapon;
	CBaseCombatWeapon *pLastActiveWeapon;
	float flLastUpdateTime;
	int iLastUpdateFrame;
	float flLastUpdateIncrement;
	float flEyeYaw;
	float flEyePitch;
	float flGoalFeetYaw;
	float flLastFeetYaw;
	float flMoveYaw;
	float flLastMoveYaw;
	float flLeanAmount;
	float flLowerBodyYawAlignTime;
	float flFeetCycle;
	float flMoveWeight;
	float flMoveWeightSmoothed;
	float flDuckAmount;
	float flHitGroundCycle;
	float flRecrouchWeight;
	Vector vecOrigin;
	Vector vecLastOrigin;
	Vector vecVelocity;
	Vector vecVelocityNormalized;
	Vector vecVelocityNormalizedNonZero;
	float flVelocityLenght2D;
	float flJumpFallVelocity;
	float flSpeedNormalized;
	float flRunningSpeed;
	float flDuckingSpeed;
	float flDurationMoving;
	float flDurationStill;
	bool bOnGround;
	bool bHitGroundAnimation;
	std::byte pad2[0x2];
	float flNextLowerBodyYawUpdateTime;
	float flDurationInAir;
	float flLeftGroundHeight;
	float flHitGroundWeight;
	float flWalkToRunTransition;
	std::byte pad3[0x4];
	float flAffectedFraction;
	std::byte pad4[0x208];
	float flMinBodyYaw;
	float flMaxBodyYaw;
	float flMinPitch;
	float flMaxPitch;
	int iAnimsetVersion;
};
