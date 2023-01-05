#pragma once
#include <array>
#include <vector>
#include <optional>
#include "animations.h"
#include "definitions.h"
#include "bitbuf.h"
#include "datatypes/usercmd.h"
#include "../utils/netvar.h"
#include "interfaces/icliententitylist.h"
#include "interfaces/irefcount.h"
#include "interfaces/ivmodelinfo.h"

#pragma region entities_definitions
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
#define NUM_ENT_ENTRY_BITS (11 + 2)
#define NUM_ENT_ENTRIES (1 << NUM_ENT_ENTRY_BITS)
#define NUM_SERIAL_NUM_BITS 16
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK ((1 << NUM_SERIAL_NUM_BITS) - 1)
#pragma endregion

#pragma region entities_enumerations
enum EDataUpdateType : int {
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

enum ETeamID : int {
	TEAM_UNASSIGNED = 0,
	TEAM_SPECTATOR,
	TEAM_TT,
	TEAM_CT
};

enum EThinkMethods : int {
	THINK_FIRE_ALL_FUNCTIONS = 0,
	THINK_FIRE_BASE_ONLY,
	THINK_FIRE_ALL_BUT_BASE,
};

enum EItemDefinitionIndex : short {
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_ZONE_REPULSOR = 20,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SHIELD = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE_GG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS = 69,
	WEAPON_BREACHCHARGE = 70,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE = 75,
	WEAPON_HAMMER = 76,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB = 81,
	WEAPON_DIVERSION = 82,
	WEAPON_FRAG_GRENADE = 83,
	WEAPON_SNOWBALL = 84,
	WEAPON_BUMPMINE = 85,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	WEAPON_KNIFE_CORD = 517,
	WEAPON_KNIFE_CANIS = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
	WEAPON_KNIFE_OUTDOOR = 521,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BROKENFANG = 4725,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T = 5028,
	GLOVE_CT = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_HANDWRAPS = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_STUDDED_HYDRA = 5035,
	SPECIAL_AGENT_BLUEBERRIES_BUCKSHOT = 4619,
	SPECIAL_AGENT_TWO_TIMES_MCCOY_TACP = 4680,
	SPECIAL_AGENT_COMMANDOR_MAE_JAMISON = 4711,
	SPECIAL_AGENT_1ST_LIEUTENANT_FARLOW,
	SPECIAL_AGENT_JOHN_KASK,
	SPECIAL_AGENT_BIO_HAZ_SPECIALIST,
	SPECIAL_AGENT_SERGEANT_BOMBSON,
	SPECIAL_AGENT_CHEM_HAZ_SPECIALIST,
	SPECIAL_AGENT_REZAN_THE_REDSHIRT = 4718,
	SPECIAL_AGENT_SIR_BLOODY_MIAMI_DARRYL = 4726,
	SPECIAL_AGENT_SAFECRACKER_VOLTZMANN,
	SPECIAL_AGENT_LITTLE_KEV,
	SPECIAL_AGENT_GETAWAY_SALLY = 4730,
	SPECIAL_AGENT_NUMBER_K = 4732,
	SPECIAL_AGENT_SIR_BLOODY_SILENT_DARRYL = 4733,
	SPECIAL_AGENT_SIR_BLOODY_SKULLHEAD_DARRYL,
	SPECIAL_AGENT_SIR_BLOODY_DARRYL_ROYALE,
	SPECIAL_AGENT_SIR_BLOODY_LOUDMOUTH_DARRYL,
	SPECIAL_AGENT_T = 5036,
	SPECIAL_AGENT_CT = 5037,
	SPECIAL_AGENT_GROUND_REBEL = 5105,
	SPECIAL_AGENT_OSIRIS,
	SPECIAL_AGENT_SHAHMAT,
	SPECIAL_AGENT_MUHLIK,
	SPECIAL_AGENT_SOLDIER = 5205,
	SPECIAL_AGENT_ENFORCER,
	SPECIAL_AGENT_SLINGSHOT,
	SPECIAL_AGENT_STREET_SOLDIER,
	SPECIAL_AGENT_OPERATOR = 5305,
	SPECIAL_AGENT_MARKUS_DELROW,
	SPECIAL_AGENT_MICHAEL_SYFERS,
	SPECIAL_AGENT_AVA,
	SPECIAL_AGENT_3RD_COMMANDO_COMPANY = 5400,
	SPECIAL_AGENT_SEAL_TEAM_6_SOLDIER,
	SPECIAL_AGENT_BUCKSHOT,
	SPECIAL_AGENT_TWO_TIMES_MCCOY_USAF,
	SPECIAL_AGENT_RICKSAW,
	SPECIAL_AGENT_DRAGOMIR = 5500,
	SPECIAL_AGENT_MAXIMUS,
	SPECIAL_AGENT_REZAN_THE_READY,
	SPECIAL_AGENT_BLACKWOLF = 5503,
	SPECIAL_AGENT_THE_DOCTOR,
	SPECIAL_AGENT_DRAGOMIR_FOOTSOLDIERS,
	SPECIAL_AGENT_B_SQUADRON_OFFICER = 5601
};

enum EWeaponType : int {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL = 1,
	WEAPONTYPE_SUBMACHINEGUN = 2,
	WEAPONTYPE_RIFLE = 3,
	WEAPONTYPE_SHOTGUN = 4,
	WEAPONTYPE_SNIPER = 5,
	WEAPONTYPE_MACHINEGUN = 6,
	WEAPONTYPE_C4 = 7,
	WEAPONTYPE_PLACEHOLDER = 8,
	WEAPONTYPE_GRENADE = 9,
	WEAPONTYPE_HEALTHSHOT = 11,
	WEAPONTYPE_FISTS = 12,
	WEAPONTYPE_BREACHCHARGE = 13,
	WEAPONTYPE_BUMPMINE = 14,
	WEAPONTYPE_TABLET = 15,
	WEAPONTYPE_MELEE = 16
};
#pragma endregion

class IHandleEntity {
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &hRef) = 0;
	virtual const CBaseHandle &GetRefEHandle() const = 0;
};

class IClientUnknown;
class ICollideable {
public:
	virtual IHandleEntity *GetEntityHandle() = 0;
	virtual const Vector &OBBMins() const = 0;
	virtual const Vector &OBBMaxs() const = 0;
	virtual void WorldSpaceTriggerBounds(Vector *pVecWorldMins, Vector *pVecWorldMaxs) const = 0;
	virtual bool TestCollision(const Ray_t &ray, unsigned int fContentsMask, Trace_t &tr) = 0;
	virtual bool TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, Trace_t &tr) = 0;
	virtual int GetCollisionModelIndex() = 0;
	virtual const Model_t *GetCollisionModel() = 0;
	virtual Vector &GetCollisionOrigin() const = 0;
	virtual QAngle &GetCollisionAngles() const = 0;
	virtual const matrix3x4_t &CollisionToWorldTransform() const = 0;
	virtual ESolidType GetSolid() const = 0;
	virtual int GetSolidFlags() const = 0;
	virtual IClientUnknown *GetIClientUnknown() = 0;
	virtual int GetCollisionGroup() const = 0;

	virtual void WorldSpaceSurroundingBounds(Vector *pVecMins, Vector *pVecMaxs) = 0;
	virtual unsigned int GetRequiredTriggerFlags() const = 0;
	virtual const matrix3x4_t *GetRootParentToWorldTransform() const = 0;
	virtual void *GetVPhysicsObject() const = 0;
};

class IClientAlphaProperty {
public:
	virtual IClientUnknown *GetIClientUnknown() = 0;
	virtual void SetAlphaModulation(std::uint8_t uAlpha) = 0;
	virtual void SetRenderFX(int nRenderFx, int nRenderMode, float flStartTime = FLT_MAX, float flDuration = 0.0f) = 0;
	virtual void SetFade(float flGlobalFadeScale, float flDistFadeStart, float flDistFadeEnd) = 0;
	virtual void SetDesyncOffset(int nOffset) = 0;
	virtual void EnableAlphaModulationOverride(bool bEnable) = 0;
	virtual void EnableShadowAlphaModulationOverride(bool bEnable) = 0;
	virtual void SetDistanceFadeMode(int nFadeMode) = 0;
};

class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class CBaseEntity;
class IClientThinkable;
class IClientUnknown : public IHandleEntity {
public:
	virtual ICollideable *GetCollideable() = 0;
	virtual IClientNetworkable *GetClientNetworkable() = 0;
	virtual IClientRenderable *GetClientRenderable() = 0;
	virtual IClientEntity *GetIClientEntity() = 0;
	virtual CBaseEntity *GetBaseEntity() = 0;
	virtual IClientThinkable *GetClientThinkable() = 0;
	virtual IClientAlphaProperty *GetClientAlphaProperty() = 0;
};

struct RenderableInstance_t {
	std::uint8_t uAlpha;
};

using ClientShadowHandle_t = std::uint16_t;
using ClientRenderHandle_t = std::uint16_t;
using ModelInstanceHandle_t = std::uint16_t;
class IClientRenderable {
public:
	virtual IClientUnknown *GetIClientUnknown() = 0;
	virtual Vector &GetRenderOrigin() = 0;
	virtual QAngle &GetRenderAngles() = 0;
	virtual bool ShouldDraw() = 0;
	virtual int GetRenderFlags() = 0;
	virtual bool IsTransparent() = 0;
	virtual ClientShadowHandle_t GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t &RenderHandle() = 0;
	virtual const Model_t *GetModel() const = 0;
	virtual int DrawModel(int nFlags, const RenderableInstance_t &uInstance) = 0;
	virtual int GetBody() = 0;
	virtual void GetColorModulation(float *pColor) = 0;
	virtual bool LODTest() = 0;
	virtual bool SetupBones(matrix3x4_t *matBoneToWorldOut, int nMaxBones, int fBoneMask, float flCurrentTime) = 0;
	virtual void SetupWeights(const matrix3x4_t *matBoneToWorld, int nFlexWeightCount, float *flFlexWeights, float *flFlexDelayedWeights) = 0;
	virtual void DoAnimationEvents() = 0;
	virtual void *GetPVSNotifyInterface() = 0;
	virtual void GetRenderBounds(Vector &vecMins, Vector &vecMaxs) = 0;
	virtual void GetRenderBoundsWorldspace(Vector &vecMins, Vector &vecMaxs) = 0;
	virtual void GetShadowRenderBounds(Vector &vecMins, Vector &vecMaxs, int iShadowType) = 0;
	virtual bool ShouldReceiveProjectedTextures(int nFlags) = 0;
	virtual bool GetShadowCastDistance(float *pDistance, int iShadowType) const = 0;
	virtual bool GetShadowCastDirection(Vector *vecDirection, int iShadowType) const = 0;
	virtual bool IsShadowDirty() = 0;
	virtual void MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable *GetShadowParent() = 0;
	virtual IClientRenderable *FirstShadowChild() = 0;
	virtual IClientRenderable *NextShadowPeer() = 0;
	virtual int ShadowCastType() = 0;
	virtual void unused2() {}
	virtual void CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t GetModelInstance() = 0;
	virtual const matrix3x4_t &RenderableToWorldTransform() = 0;
	virtual int LookupAttachment(const char *pAttachmentName) = 0;
	virtual bool GetAttachment(int nIndex, Vector &vecOrigin, QAngle &angView) = 0;
	virtual bool GetAttachment(int nIndex, matrix3x4_t &matAttachment) = 0;
	virtual bool ComputeLightingOrigin(int nAttachmentIndex, Vector vecModelLightingCenter, const matrix3x4_t &matrix, Vector &vecTransformedLightingCenter) = 0;
	virtual float *GetRenderClipPlane() = 0;
	virtual int GetSkin() = 0;
	virtual void OnThreadedDrawSetup() = 0;
	virtual bool UsesFlexDelayedWeights() = 0;
	virtual void RecordToolMessage() = 0;
	virtual bool ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual std::uint8_t OverrideAlphaModulation(std::uint8_t uAlpha) = 0;
	virtual std::uint8_t OverrideShadowAlphaModulation(std::uint8_t uAlpha) = 0;
	virtual void *GetClientModelRenderable() = 0;
};

class CBaseClient;
class IClientNetworkable {
public:
	virtual IClientUnknown *GetIClientUnknown() = 0;
	virtual void Release() = 0;
	virtual CBaseClient *GetClientClass() = 0;
	virtual void NotifyShouldTransmit(int iState) = 0;
	virtual void OnPreDataChanged(EDataUpdateType updateType) = 0;
	virtual void OnDataChanged(EDataUpdateType updateType) = 0;
	virtual void PreDataUpdate(EDataUpdateType updateType) = 0;
	virtual void PostDataUpdate(EDataUpdateType updateType) = 0;
	virtual void OnDataUnchangedInPVS() = 0;
	virtual bool IsDormant() const = 0;
	virtual int GetIndex() const = 0;
	virtual void ReceiveMessage(EClassIndex classIndex, bf_read &msg) = 0;
	virtual void *GetDataTableBasePtr() = 0;
	virtual void SetDestroyedOnRecreateEntities() = 0;
};

class CClientThinkHandle;
using ClientThinkHandle_t = CClientThinkHandle *;
class IClientThinkable {
public:
	virtual IClientUnknown *GetIClientUnknown() = 0;
	virtual void ClientThink() = 0;
	virtual ClientThinkHandle_t GetThinkHandle() = 0;
	virtual void SetThinkHandle(ClientThinkHandle_t hThink) = 0;
	virtual void Release() = 0;
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {
public:
	virtual const Vector &GetAbsOrigin() const = 0;
	virtual const QAngle &GetAbsAngles() const = 0;
	virtual void *GetMouth() = 0;
	virtual bool GetSoundSpatialization(struct SpatializationInfo_t &info) = 0;
	virtual bool IsBlurred() = 0;

	void SetAbsOrigin(const Vector &vecOrigin) {
		using SetAbsOriginFn = void(__thiscall *)(void *, const Vector &);
		static auto oSetAbsOrigin = reinterpret_cast<SetAbsOriginFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8")));
		oSetAbsOrigin(this, vecOrigin);
	}

	void SetAbsAngles(const QAngle &angView) {
		using SetAbsAngleFn = void(__thiscall *)(void *, const QAngle &);
		static auto oSetAbsAngles = reinterpret_cast<SetAbsAngleFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8")));
		oSetAbsAngles(this, angView);
	}

	DataMap_t *GetDataDescMap() {
		return MEM::CallVFunc<DataMap_t *>(this, 15);
	}

	DataMap_t *GetPredictionDescMap() {
		return MEM::CallVFunc<DataMap_t *>(this, 17);
	}
};

class CWeaponCSBase;
class CBaseEntity : public IClientEntity {
public:
#pragma region DT_BasePlayer
	N_ADD_PVARIABLE(float, GetFallVelocity, "CBasePlayer->m_flFallVelocity");
	N_ADD_VARIABLE(QAngle, GetViewPunch, "CBasePlayer->m_viewPunchAngle");
	N_ADD_VARIABLE(QAngle, GetPunch, "CBasePlayer->m_aimPunchAngle");
	N_ADD_VARIABLE(Vector, GetViewOffset, "CBasePlayer->m_vecViewOffset[0]");
	N_ADD_VARIABLE(float, GetFriction, "CBasePlayer->m_flFriction");
	N_ADD_VARIABLE(int, GetTickBase, "CBasePlayer->m_nTickBase");
	N_ADD_PVARIABLE(int, GetNextThinkTick, "CBasePlayer->m_nNextThinkTick");
	N_ADD_VARIABLE(Vector, GetVelocity, "CBasePlayer->m_vecVelocity[0]");
	N_ADD_PVARIABLE_OFFSET(QAngle, GetViewAngles, "CBasePlayer->deadflag", 0x4);
	N_ADD_VARIABLE(CBaseHandle, GetGroundEntityHandle, "CBasePlayer->m_hGroundEntity");
	N_ADD_VARIABLE(int, GetHealth, "CBasePlayer->m_iHealth");
	N_ADD_VARIABLE(int, GetLifeState, "CBasePlayer->m_lifeState");
	N_ADD_VARIABLE(float, GetMaxSpeed, "CBasePlayer->m_flMaxspeed");
	N_ADD_VARIABLE(int, GetFlags, "CBasePlayer->m_fFlags");
	N_ADD_PVARIABLE(int, GetObserverMode, "CBasePlayer->m_iObserverMode");
	N_ADD_VARIABLE(CBaseHandle, GetObserverTargetHandle, "CBasePlayer->m_hObserverTarget");
	N_ADD_VARIABLE(CBaseHandle, GetViewModelHandle, "CBasePlayer->m_hViewModel[0]");
	N_ADD_PVARIABLE(const char, GetLastPlace, "CBasePlayer->m_szLastPlaceName");
	N_ADD_VARIABLE_OFFSET(int, GetButtonDisabled, "CBasePlayer->m_hViewEntity", -0xC);
	N_ADD_VARIABLE_OFFSET(int, GetButtonForced, "CBasePlayer->m_hViewEntity", -0x8);
	N_ADD_PVARIABLE_OFFSET(CUserCmd *, GetCurrentCommand, "CBasePlayer->m_hViewEntity", -0x4);

	N_ADD_DATAFIELD(int, GetEFlags, this->GetPredictionDescMap(), "m_iEFlags");
	N_ADD_PDATAFIELD(int, GetButtons, this->GetPredictionDescMap(), "m_nButtons");
	N_ADD_DATAFIELD(int, GetButtonLast, this->GetPredictionDescMap(), "m_afButtonLast");
	N_ADD_DATAFIELD(int, GetButtonPressed, this->GetPredictionDescMap(), "m_afButtonPressed");
	N_ADD_DATAFIELD(int, GetButtonReleased, this->GetPredictionDescMap(), "m_afButtonReleased");
	N_ADD_PDATAFIELD(int, GetImpulse, this->GetPredictionDescMap(), "m_nImpulse");
	N_ADD_DATAFIELD(float, GetSurfaceFriction, this->GetPredictionDescMap(), "m_surfaceFriction");

	inline bool IsAlive() {

		return (this->GetLifeState() == LIFE_ALIVE);
	}

	int &GetTakeDamage() {
		static const std::uintptr_t uTakeDamageOffset = *reinterpret_cast<std::uintptr_t *>(MEM::FindPattern(CLIENT_DLL, "80 BE ? ? ? ? ? 75 46 8B 86")) + 0x2);
		return *reinterpret_cast<int *>(reinterpret_cast<std::uintptr_t>(this) + uTakeDamageOffset);
	}

	CUserCmd &GetLastCommand() {
		static const std::uintptr_t uLastCommandOffset = *reinterpret_cast<std::uintptr_t *>(MEM::FindPattern(CLIENT_DLL, "8D 8E ? ? ? ? 89 5C 24 3C")) + 0x2);
		return *reinterpret_cast<CUserCmd *>(reinterpret_cast<std::uintptr_t>(this) + uLastCommandOffset);
	}
#pragma endregion

#pragma region DT_CSPlayer
	N_ADD_VARIABLE(int, GetShotsFired, "CCSPlayer->m_iShotsFired");
	N_ADD_VARIABLE_OFFSET(float, GetSpawnTime, "CCSPlayer->m_iAddonBits", -0x4);
	N_ADD_VARIABLE(int, GetMoney, "CCSPlayer->m_iAccount");
	N_ADD_VARIABLE(int, GetTotalHits, "CCSPlayer->m_totalHitsOnServer");
	N_ADD_VARIABLE(int, GetArmor, "CCSPlayer->m_ArmorValue");
	N_ADD_VARIABLE(QAngle, GetEyeAngles, "CCSPlayer->m_angEyeAngles");
	N_ADD_VARIABLE(bool, IsDefusing, "CCSPlayer->m_bIsDefusing");
	N_ADD_VARIABLE(bool, IsScoped, "CCSPlayer->m_bIsScoped");
	N_ADD_VARIABLE_OFFSET(CCSGOPlayerAnimState *, GetAnimationState, "CCSPlayer->m_bIsScoped", -0x14);
	N_ADD_VARIABLE(bool, IsGrabbingHostage, "CCSPlayer->m_bIsGrabbingHostage");
	N_ADD_VARIABLE(bool, IsRescuing, "CCSPlayer->m_bIsRescuing");
	N_ADD_VARIABLE(bool, HasHelmet, "CCSPlayer->m_bHasHelmet");
	N_ADD_VARIABLE(bool, HasHeavyArmor, "CCSPlayer->m_bHasHeavyArmor");
	N_ADD_VARIABLE(bool, HasDefuser, "CCSPlayer->m_bHasDefuser");
	N_ADD_VARIABLE(bool, HasImmunity, "CCSPlayer->m_bGunGameImmunity");
	N_ADD_VARIABLE(bool, IsInBuyZone, "CCSPlayer->m_bInBuyZone");
	N_ADD_PVARIABLE(float, GetFlashMaxAlpha, "CCSPlayer->m_flFlashMaxAlpha");
	N_ADD_VARIABLE_OFFSET(float, GetFlashAlpha, "CCSPlayer->m_flFlashMaxAlpha", -0x8);
	N_ADD_VARIABLE(float, GetFlashDuration, "CCSPlayer->m_flFlashDuration");
	N_ADD_VARIABLE_OFFSET(int, GetGlowIndex, "CCSPlayer->m_flFlashDuration", 0x18);
	N_ADD_VARIABLE(float, GetLowerBodyYaw, "CCSPlayer->m_flLowerBodyYawTarget");
	N_ADD_VARIABLE(int, GetSurvivalTeam, "CCSPlayer->m_nSurvivalTeam");
	N_ADD_VARIABLE_OFFSET(int, IsUsedNewAnimState, "CCSPlayer->m_flLastExoJumpTime", 0x8);

	inline bool IsArmored(const int iHitGroup) {
		bool bIsArmored = false;

		if (this->GetArmor() > 0) {
			switch (iHitGroup) {
			case HITGROUP_GENERIC:
			case HITGROUP_CHEST:
			case HITGROUP_STOMACH:
			case HITGROUP_LEFTARM:
			case HITGROUP_RIGHTARM:
			case HITGROUP_NECK:
				bIsArmored = true;
				break;
			case HITGROUP_HEAD:
				if (this->HasHelmet())
					bIsArmored = true;
				[[fallthrough]];
			case HITGROUP_LEFTLEG:
			case HITGROUP_RIGHTLEG:
				if (this->HasHeavyArmor())
					bIsArmored = true;
				break;
			default:
				break;
			}
		}

		return bIsArmored;
	}
#pragma endregion

#pragma region DT_BaseEntity
	N_ADD_VARIABLE(float, GetAnimationTime, "CBaseEntity->m_flAnimTime");
	N_ADD_VARIABLE(float, GetSimulationTime, "CBaseEntity->m_flSimulationTime");
	N_ADD_VARIABLE_OFFSET(float, GetOldSimulationTime, "CBaseEntity->m_flSimulationTime", 0x4);
	N_ADD_VARIABLE(Vector, GetOrigin, "CBaseEntity->m_vecOrigin");
	N_ADD_VARIABLE(QAngle, GetRotation, "CBaseEntity->m_angRotation");
	N_ADD_VARIABLE(int, GetEffects, "CBaseEntity->m_fEffects");
	N_ADD_VARIABLE(int, GetTeam, "CBaseEntity->m_iTeamNum");
	N_ADD_VARIABLE(CBaseHandle, GetOwnerEntityHandle, "CBaseEntity->m_hOwnerEntity");
	N_ADD_PVARIABLE(ICollideable, GetCollision, "CBaseEntity->m_Collision");
	N_ADD_VARIABLE(int, GetCollisionGroup, "CBaseEntity->m_CollisionGroup");
	N_ADD_PVARIABLE(bool, IsSpotted, "CBaseEntity->m_bSpotted");

	N_ADD_DATAFIELD(QAngle, GetAbsRotation, this->GetDataDescMap(), "m_angAbsRotation");
	N_ADD_DATAFIELD(const matrix3x4_t, GetCoordinateFrame, this->GetDataDescMap(), "m_rgflCoordinateFrame");
	N_ADD_DATAFIELD(int, GetMoveType, this->GetPredictionDescMap(), "m_MoveType");
#pragma endregion

#pragma region DT_BaseCombatCharacter
	N_ADD_VARIABLE(float, GetNextAttack, "CBaseCombatCharacter->m_flNextAttack");
	N_ADD_VARIABLE(CBaseHandle, GetActiveWeaponHandle, "CBaseCombatCharacter->m_hActiveWeapon");
	N_ADD_PVARIABLE(CBaseHandle, GetWeaponsHandle, "CBaseCombatCharacter->m_hMyWeapons");
	N_ADD_PVARIABLE(CBaseHandle, GetWearablesHandle, "CBaseCombatCharacter->m_hMyWearables");
#pragma endregion

#pragma region DT_BaseAnimating
	N_ADD_VARIABLE(int, GetSequence, "CBaseAnimating->m_nSequence");
	N_ADD_PVARIABLE_OFFSET(CBoneAccessor, GetBoneAccessor, "CBaseAnimating->m_nForceBone", 0x1C);
	N_ADD_VARIABLE(int, GetHitboxSet, "CBaseAnimating->m_nHitboxSet");
	N_ADD_VARIABLE(bool, IsClientSideAnimation, "CBaseAnimating->m_bClientSideAnimation");
	N_ADD_VARIABLE(float, GetCycle, "CBaseAnimating->m_flCycle");

	[[nodiscard]] std::array<float, MAXSTUDIOPOSEPARAM> &GetPoseParameter() {
		static std::uintptr_t m_flPoseParameter = CNetvarManager::Get().mapProps[FNV1A::HashConst("CBaseAnimating->m_flPoseParameter")].uOffset;
		return *reinterpret_cast<std::array<float, MAXSTUDIOPOSEPARAM> *>(reinterpret_cast<std::uintptr_t>(this) + m_flPoseParameter);
	}

	inline void SetPoseAngles(float flYaw, float flPitch) {
		auto &arrPose = this->GetPoseParameter();
		arrPose.at(11U) = (flPitch + 90.f) / 180.f;
		arrPose.at(2U) = (flYaw + 180.f) / 360.f;
	}

	[[nodiscard]] CUtlVector<CAnimationLayer> &GetAnimationOverlays() {
		static const std::uintptr_t uAnimationOverlaysOffset = *reinterpret_cast<std::uintptr_t *>(MEM::FindPattern(CLIENT_DLL, "8B 89 ? ? ? ? 8D 0C D1")) + 0x2;
		return *reinterpret_cast<CUtlVector<CAnimationLayer> *>(reinterpret_cast<std::uintptr_t>(this) + uAnimationOverlaysOffset);
	}

	[[nodiscard]] inline CAnimationLayer *GetAnimationLayer(const int nLayer) {
		if (nLayer >= 0 && nLayer < MAXOVERLAYS)
			return &GetAnimationOverlays()[nLayer];

		return nullptr;
	}
#pragma endregion

	int IsMaxHealth() {
		return MEM::CallVFunc<int>(this, 123);
	}

	void Think() {
		MEM::CallVFunc<void>(this, 139);
	}

	const char *GetClassname() {
		return MEM::CallVFunc<const char *>(this, 143);
	}

	unsigned int PhysicsSolidMaskForEntity() {
		return MEM::CallVFunc<unsigned int>(this, 152);
	}

	bool IsPlayer() {
		return MEM::CallVFunc<bool>(this, 158);
	}

	[[nodiscard]] Vector GetEyePosition(bool bShouldCorrect = true) {
		Vector vecPosition = {};

		MEM::CallVFunc<void>(this, 169, std::ref(vecPosition));

		if (IsUsedNewAnimState() && bShouldCorrect) {
			if (CCSGOPlayerAnimState *pAnimState = this->GetAnimationState(); pAnimState != nullptr)
				ModifyEyePosition(pAnimState, &vecPosition);
		}

		return vecPosition;
	}

	void SetSequence(int iSequence) {
		MEM::CallVFunc<void>(this, 219, iSequence);
	}

	void StudioFrameAdvance() {
		MEM::CallVFunc<void>(this, 220);
	}

	void UpdateClientSideAnimations() {
		MEM::CallVFunc<void>(this, 224);
	}

	void PreThink() {
		MEM::CallVFunc<void>(this, 318);
	}

	void UpdateCollisionBounds() {
		MEM::CallVFunc<void>(this, 340);
	}

	bool PhysicsRunThink(int nThinkMethod) {
		using PhysicsRunThinkFn = bool(__thiscall *)(void *, int);
		static auto oPhysicsRunThink = reinterpret_cast<PhysicsRunThinkFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87"));
		return oPhysicsRunThink(this, nThinkMethod);
	}

	static CBaseEntity *GetLocalPlayer();
	int GetSequenceActivity(int iSequence);
	CBaseCombatWeapon *GetWeapon();
	int GetMaxHealth();
	std::optional<Vector> GetBonePosition(int iBone);
	int GetBoneByHash(const FNV1A_t uBoneHash) const;
	std::optional<Vector> GetHitboxPosition(const int iHitbox);
	std::optional<Vector> GetHitGroupPosition(const int iHitGroup);
	void ModifyEyePosition(const CCSGOPlayerAnimState *pAnimState, Vector *vecPosition) const;
	void PostThink();
	bool IsEnemy(CBaseEntity *pEntity);
	bool IsTargetingLocal(CBaseEntity *pLocal);
	bool CanShoot(CWeaponCSBase *pBaseWeapon);
	bool IsVisible(CBaseEntity *pEntity, const Vector &vecEnd, bool bSmokeCheck = false);
	bool IsBreakable();
};

class CCSWeaponData {
public:
	std::byte pad0[0x14];
	int iMaxClip1;
	int iMaxClip2;
	int iDefaultClip1;
	int iDefaultClip2;
	int iPrimaryMaxReserveAmmo;
	int iSecondaryMaxReserveAmmo;
	const char *szWorldModel;
	const char *szViewModel;
	const char *szDroppedModel;
	std::byte pad1[0x50];
	const char *szHudName;
	const char *szWeaponName;
	std::byte pad2[0x2];
	bool bIsMeleeWeapon;
	std::byte pad3[0x9];
	float flWeaponWeight;
	std::byte pad4[0x4];
	int iSlot;
	int iPosition;
	std::byte pad5[0x1C];
	int nWeaponType;
	std::byte pad6[0x4];
	int iWeaponPrice;
	int iKillAward;
	const char *szAnimationPrefix;
	float flCycleTime;
	float flCycleTimeAlt;
	std::byte pad8[0x8];
	bool bFullAuto;
	std::byte pad9[0x3];
	int iDamage;
	float flHeadShotMultiplier;
	float flArmorRatio;
	int iBullets;
	float flPenetration;
	std::byte pad10[0x8];
	float flRange;
	float flRangeModifier;
	float flThrowVelocity;
	std::byte pad11[0xC];
	bool bHasSilencer;
	std::byte pad12[0xF];
	float flMaxSpeed[2];
	std::byte pad13[0x4];
	float flSpread[2];
	float flInaccuracyCrouch[2];
	float flInaccuracyStand[2];
	std::byte pad14[0x8];
	float flInaccuracyJump[2];
	float flInaccuracyLand[2];
	float flInaccuracyLadder[2];
	float flInaccuracyFire[2];
	float flInaccuracyMove[2];
	float flInaccuracyReload;
	int iRecoilSeed;
	float flRecoilAngle[2];
	float flRecoilAngleVariance[2];
	float flRecoilMagnitude[2];
	float flRecoilMagnitudeVariance[2];
	int iSpreadSeed;

	bool IsGun() const {
		switch (this->nWeaponType) {
		case WEAPONTYPE_PISTOL:
		case WEAPONTYPE_SUBMACHINEGUN:
		case WEAPONTYPE_RIFLE:
		case WEAPONTYPE_SHOTGUN:
		case WEAPONTYPE_SNIPER:
		case WEAPONTYPE_MACHINEGUN:
			return true;
		}

		return false;
	}
};

class IRefCounted;
class CEconItemView {
public:
	N_ADD_OFFSET(CUtlVector<IRefCounted *>, GetCustomMaterials, 0x14);

	CUtlVector<CRefCounted *> &GetVisualsDataProcessors() {

		static const std::uintptr_t uVisualsDataProcessorsOffset = *reinterpret_cast<std::uintptr_t *>(MEM::FindPattern(CLIENT_DLL, "81 C7 ? ? ? ? 8B 4F 0C 8B 57 04 89 4C")) + 0x2;
		return *reinterpret_cast<CUtlVector<CRefCounted *> *>(reinterpret_cast<std::uintptr_t>(this) + uVisualsDataProcessorsOffset);
	}
};

class CBaseCombatWeapon : public IClientEntity {
public:
#pragma region DT_BaseCombatWeapon
	N_ADD_VARIABLE(float, GetNextPrimaryAttack, "CBaseCombatWeapon->m_flNextPrimaryAttack");
	N_ADD_VARIABLE(float, GetNextSecondaryAttack, "CBaseCombatWeapon->m_flNextSecondaryAttack");
	N_ADD_VARIABLE(int, GetAmmo, "CBaseCombatWeapon->m_iClip1");
	N_ADD_VARIABLE(int, GetAmmoReserve, "CBaseCombatWeapon->m_iPrimaryReserveAmmoCount");
	N_ADD_VARIABLE(int, GetViewModelIndex, "CBaseCombatWeapon->m_iViewModelIndex");
	N_ADD_VARIABLE(int, GetWorldModelIndex, "CBaseCombatWeapon->m_iWorldModelIndex");
	N_ADD_VARIABLE(CBaseHandle, GetWorldModelHandle, "CBaseCombatWeapon->m_hWeaponWorldModel");

	N_ADD_DATAFIELD(bool, IsReloading, this->GetPredictionDescMap(), "m_bInReload");
#pragma endregion

#pragma region DT_BaseAttributableItem
	N_ADD_VARIABLE(short, GetItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex");
	N_ADD_VARIABLE(int, GetItemIDHigh, "CBaseAttributableItem->m_iItemIDHigh");
	N_ADD_VARIABLE(int, GetItemIDLow, "CBaseAttributableItem->m_iItemIDLow");
	N_ADD_VARIABLE(int, GetAccountID, "CBaseAttributableItem->m_iAccountID");
	N_ADD_VARIABLE(int, GetEntityQuality, "CBaseAttributableItem->m_iEntityQuality");
	N_ADD_PVARIABLE(char, GetCustomName, "CBaseAttributableItem->m_szCustomName");
	N_ADD_VARIABLE(int, GetOwnerXuidLow, "CBaseAttributableItem->m_OriginalOwnerXuidLow");
	N_ADD_VARIABLE(int, GetOwnerXuidHigh, "CBaseAttributableItem->m_OriginalOwnerXuidHigh");
	N_ADD_VARIABLE(int, GetFallbackPaintKit, "CBaseAttributableItem->m_nFallbackPaintKit");
	N_ADD_VARIABLE(int, GetFallbackSeed, "CBaseAttributableItem->m_nFallbackSeed");
	N_ADD_VARIABLE(float, GetFallbackWear, "CBaseAttributableItem->m_flFallbackWear");
	N_ADD_VARIABLE(int, GetFallbackStatTrak, "CBaseAttributableItem->m_nFallbackStatTrak");
	N_ADD_PVARIABLE(CEconItemView, GetEconItemView, "CBaseAttributableItem->m_Item");
#pragma endregion

	void SetModelIndex(int nModelIndex) {
		MEM::CallVFunc<void>(this, 75, nModelIndex);
	}

	bool IsWeapon() {
		return MEM::CallVFunc<bool>(this, 166);
	}

	[[nodiscard]] float GetSpread() {
		return MEM::CallVFunc<float>(this, 453);
	}

	[[nodiscard]] float GetInaccuracy() {
		return MEM::CallVFunc<float>(this, 483);
	}
};

class CTEFireBullets {
public:
	std::byte pad0[0x10];
	int nPlayer;
	int nItemDefinitionIndex;
	Vector vecOrigin;
	Vector vecAngles;
	int iWeapon;
	int nWeaponID;
	int iMode;
	int nSeed;
	float flInaccuracy;
	float flRecoilIndex;
	float flSpread;
	int nSoundType;
};

class CWeaponCSBase : public CBaseCombatWeapon {
public:
#pragma region DT_WeaponCSBaseGun
	N_ADD_VARIABLE(int, GetZoomLevel, "CWeaponCSBaseGun->m_zoomLevel");
	N_ADD_VARIABLE(int, GetBurstShotsRemaining, "CWeaponCSBaseGun->m_iBurstShotsRemaining");
#pragma endregion

#pragma region DT_WeaponCSBase
	N_ADD_VARIABLE(bool, IsBurstMode, "CWeaponCSBase->m_bBurstMode");
	N_ADD_VARIABLE(float, GetAccuracyPenalty, "CWeaponCSBase->m_fAccuracyPenalty");
	N_ADD_VARIABLE(float, GetFireReadyTime, "CWeaponCSBase->m_flPostponeFireReadyTime");
#pragma endregion

	CUtlVector<IRefCounted *> &GetCustomMaterials() {
		static auto uAddress = *reinterpret_cast<std::uintptr_t *>(MEM::FindPattern(CLIENT_DLL, "83 BE ? ? ? ? ? 7F 67")) + 0x2 - 0xC;
		return *reinterpret_cast<CUtlVector<IRefCounted *> *>(reinterpret_cast<std::uintptr_t>(this) + uAddress);
	}

	bool &IsCustomMaterialInitialized() {
		static auto uAddress = *reinterpret_cast<std::uintptr_t *>(MEM::FindPattern(CLIENT_DLL, "C6 86 ? ? ? ? ? FF 50 04")) + 0x2;
		return *reinterpret_cast<bool *>(reinterpret_cast<std::uintptr_t>(this) + uAddress);
	}
};

class CBaseCSGrenade : public CWeaponCSBase
{
public:
#pragma region DT_BaseCSGrenade
	N_ADD_VARIABLE(bool, IsPinPulled, "CBaseCSGrenade->m_bPinPulled");
	N_ADD_VARIABLE(float, GetThrowTime, "CBaseCSGrenade->m_fThrowTime");
	N_ADD_VARIABLE(float, GetThrowStrength, "CBaseCSGrenade->m_flThrowStrength");
#pragma endregion

#pragma region DT_BaseCSGrenadeProjectile
	N_ADD_VARIABLE(int, GetEffectTickBegin, "CBaseCSGrenadeProjectile->m_nExplodeEffectTickBegin");
#pragma endregion
};

class CSmokeGrenade
{
public:
#pragma region DT_SmokeGrenadeProjectile
	N_ADD_VARIABLE(int, GetEffectTickBegin, "CSmokeGrenadeProjectile->m_nSmokeEffectTickBegin");
#pragma endregion

	inline float GetMaxTime() {
		return 18.f;
	}
};

class CInferno {
public:
#pragma region DT_Inferno
	N_ADD_VARIABLE(int, GetEffectTickBegin, "CInferno->m_nFireEffectTickBegin");
#pragma endregion

	inline float GetMaxTime() {
		return 7.f;
	}
};

class CPlantedC4 {
public:
#pragma region DT_PlantedC4
	N_ADD_VARIABLE(float, GetBlowTime, "CPlantedC4->m_flC4Blow");
	N_ADD_VARIABLE(float, GetTimerLength, "CPlantedC4->m_flTimerLength");
	N_ADD_VARIABLE(float, GetDefuseLength, "CPlantedC4->m_flDefuseLength");
	N_ADD_VARIABLE(float, GetDefuseCountDown, "CPlantedC4->m_flDefuseCountDown");
	N_ADD_VARIABLE(bool, IsPlanted, "CPlantedC4->m_bBombTicking");
	N_ADD_VARIABLE(CBaseHandle, GetDefuserHandle, "CPlantedC4->m_hBombDefuser");
	N_ADD_VARIABLE(bool, IsDefused, "CPlantedC4->m_bBombDefused");

	inline float GetTimer(const float flServerTime) {
		return std::clamp(this->GetBlowTime() - flServerTime, 0.0f, this->GetTimerLength());
	}

	inline float GetDefuseTimer(const float flServerTime) {
		return std::clamp(this->GetDefuseCountDown() - flServerTime, 0.0f, this->GetDefuseLength());
	}
#pragma endregion
};

class CBaseViewModel {
public:
#pragma region DT_BaseViewModel
	N_ADD_VARIABLE(int, GetModelIndex, "CBaseViewModel->m_nModelIndex");
	N_ADD_VARIABLE(CBaseHandle, GetOwnerHandle, "CBaseViewModel->m_hOwner");
	N_ADD_VARIABLE(CBaseHandle, GetWeaponHandle, "CBaseViewModel->m_hWeapon");
#pragma endregion

	void SendViewModelMatchingSequence(int nSequence) {
		MEM::CallVFunc<void>(this, 247, nSequence);
	}

	void SetWeaponModel(const char *szFileName, CBaseCombatWeapon *pWeapon) {

		MEM::CallVFunc<void>(this, 248, szFileName, pWeapon);
	}
};

class CEnvTonemapController {
public:
#pragma region DT_EnvTonemapController
	N_ADD_VARIABLE(bool, IsUseCustomAutoExposureMin, "CEnvTonemapController->m_bUseCustomAutoExposureMin");
	N_ADD_VARIABLE(bool, IsUseCustomAutoExposureMax, "CEnvTonemapController->m_bUseCustomAutoExposureMax");
	N_ADD_VARIABLE(bool, IsUseCustomBloomScale, "CEnvTonemapController->m_bUseCustomBloomScale");
	N_ADD_VARIABLE(float, GetCustomAutoExposureMin, "CEnvTonemapController->m_flCustomAutoExposureMin");
	N_ADD_VARIABLE(float, GetCustomAutoExposureMax, "CEnvTonemapController->m_flCustomAutoExposureMax");
	N_ADD_VARIABLE(float, GetCustomBloomScale, "CEnvTonemapController->m_flCustomBloomScale");
	N_ADD_VARIABLE(float, GetCustomBloomScaleMin, "CEnvTonemapController->m_flCustomBloomScaleMinimum");
	N_ADD_VARIABLE(float, GetBloomExponent, "CEnvTonemapController->m_flBloomExponent");
	N_ADD_VARIABLE(float, GetBloomSaturation, "CEnvTonemapController->m_flBloomSaturation");
#pragma endregion
};

class CBreakableSurface : public CBaseEntity, public IBreakableWithPropData {
public:
#pragma region DT_BreakableSurface
	N_ADD_VARIABLE(bool, IsBroken, "CBreakableSurface->m_bIsBroken");
#pragma endregion
};
