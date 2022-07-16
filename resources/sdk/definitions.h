#pragma once

#define MAX_COORD_FLOAT 16'384.f
#define MIN_COORD_FLOAT -(MAX_COORD_FLOAT)
#define MAX_DISTANCE 8'192.f
#define MAX_FOV 180.f
#define MAX_DAMAGE 500.f
#define MAX_WEAPONS 64

#pragma region valve_basetypes
inline float BitsToFloat(std::uint32_t i)
{
	union Convertor_t
	{
		float fl;
		unsigned long ul;
	} tmp;

	tmp.ul = i;
	return tmp.fl;
}

#define FLOAT32_NAN_BITS 0x7FC00000U
#define FLOAT32_NAN BitsToFloat(FLOAT32_NAN_BITS)
#define VEC_T_NAN FLOAT32_NAN
#pragma endregion

#pragma region valve_consts
#define MAX_AREA_STATE_BYTES 32
#define MAX_AREA_PORTAL_STATE_BYTES 24

enum ELifeState : int
{
	LIFE_ALIVE = 0,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY
};

enum EFlags : int
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_ANIMDUCKING = (1 << 2),
	FL_WATERJUMP = (1 << 3),
	FL_ONTRAIN = (1 << 4),
	FL_INRAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_ATCONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKECLIENT = (1 << 9),
	FL_INWATER = (1 << 10),
	FL_FLY = (1 << 11),
	FL_SWIM = (1 << 12),
	FL_CONVEYOR = (1 << 13),
	FL_NPC = (1 << 14),
	FL_GODMODE = (1 << 15),
	FL_NOTARGET = (1 << 16),
	FL_AIMTARGET = (1 << 17),
	FL_PARTIALGROUND = (1 << 18),
	FL_STATICPROP = (1 << 19),
	FL_GRAPHED = (1 << 20),
	FL_GRENADE = (1 << 21),
	FL_STEPMOVEMENT = (1 << 22),
	FL_DONTTOUCH = (1 << 23),
	FL_BASEVELOCITY = (1 << 24),
	FL_WORLDBRUSH = (1 << 25),
	FL_OBJECT = (1 << 26),
	FL_KILLME = (1 << 27),
	FL_ONFIRE = (1 << 28),
	FL_DISSOLVING = (1 << 29),
	FL_TRANSRAGDOLL = (1 << 30),
	FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
};

enum EEFlags : int
{
	EFL_KILLME = (1 << 0),
	EFL_DORMANT = (1 << 1),
	EFL_NOCLIP_ACTIVE = (1 << 2),
	EFL_SETTING_UP_BONES = (1 << 3),
	EFL_KEEP_ON_RECREATE_ENTITIES = (1 << 4),
	EFL_DIRTY_SHADOWUPDATE = (1 << 5),
	EFL_NOTIFY = (1 << 6),
	EFL_FORCE_CHECK_TRANSMIT = (1 << 7),
	EFL_BOT_FROZEN = (1 << 8),
	EFL_SERVER_ONLY = (1 << 9),
	EFL_NO_AUTO_EDICT_ATTACH = (1 << 10),
	EFL_DIRTY_ABSTRANSFORM = (1 << 11),
	EFL_DIRTY_ABSVELOCITY = (1 << 12),
	EFL_DIRTY_ABSANGVELOCITY = (1 << 13),
	EFL_DIRTY_SURROUNDING_COLLISION_BOUNDS = (1 << 14),
	EFL_DIRTY_SPATIAL_PARTITION = (1 << 15),
	EFL_HAS_PLAYER_CHILD = (1 << 16),
	EFL_IN_SKYBOX = (1 << 17),
	EFL_USE_PARTITION_WHEN_NOT_SOLID = (1 << 18),
	EFL_TOUCHING_FLUID = (1 << 19),
	EFL_IS_BEING_LIFTED_BY_BARNACLE = (1 << 20),
	EFL_NO_ROTORWASH_PUSH = (1 << 21),
	EFL_NO_THINK_FUNCTION = (1 << 22),
	EFL_NO_GAME_PHYSICS_SIMULATION = (1 << 23),
	EFL_CHECK_UNTOUCH = (1 << 24),
	EFL_DONTBLOCKLOS = (1 << 25),
	EFL_DONTWALKON = (1 << 26),
	EFL_NO_DISSOLVE = (1 << 27),
	EFL_NO_MEGAPHYSCANNON_RAGDOLL = (1 << 28),
	EFL_NO_WATER_VELOCITY_CHANGE = (1 << 29),
	EFL_NO_PHYSCANNON_INTERACTION = (1 << 30),
	EFL_NO_DAMAGE_FORCES = (1 << 31)
};

enum EMoveType : int
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum ESolidType : int
{
	SOLID_NONE = 0,
	SOLID_BSP,
	SOLID_BBOX,
	SOLID_OBB,
	SOLID_OBB_YAW,
	SOLID_CUSTOM,
	SOLID_VPHYSICS,
	SOLID_LAST
};

enum ESolidFlags : unsigned int
{
	FSOLID_CUSTOMRAYTEST = 0x0001,
	FSOLID_CUSTOMBOXTEST = 0x0002,
	FSOLID_NOT_SOLID = 0x0004,
	FSOLID_TRIGGER = 0x0008,
	FSOLID_NOT_STANDABLE = 0x0010,
	FSOLID_VOLUME_CONTENTS = 0x0020,
	FSOLID_FORCE_WORLD_ALIGNED = 0x0040,
	FSOLID_USE_TRIGGER_BOUNDS = 0x0080,
	FSOLID_ROOT_PARENT_ALIGNED = 0x0100,
	FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,
	FSOLID_MAX_BITS = 10
};

enum EEffectFlags : unsigned int
{
	EF_BONEMERGE = 0x001,
	EF_BRIGHTLIGHT = 0x002,
	EF_DIMLIGHT = 0x004,
	EF_NOINTERP = 0x008,
	EF_NOSHADOW = 0x010,
	EF_NODRAW = 0x020,
	EF_NORECEIVESHADOW = 0x040,
	EF_BONEMERGE_FASTCULL = 0x080,

	EF_ITEM_BLINK = 0x100,
	EF_PARENT_ANIMATES = 0x200,
	EF_MARKED_FOR_FAST_REFLECTION = 0x400,
	EF_NOSHADOWDEPTH = 0x800,
	EF_SHADOWDEPTH_NOCACHE = 0x1000,
	EF_NOFLASHLIGHT = 0x2000,
	EF_NOCSM = 0x4000,
	EF_MAX_BITS = 15
};

enum ECollisionGroup : int
{
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_DEBRIS_TRIGGER,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,
	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,
	COLLISION_GROUP_PZ_CLIP,
	COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE,
	LAST_SHARED_COLLISION_GROUP
};
#pragma endregion

#pragma region valve_shareddefs
#define TICK_INTERVAL (I::Globals->flIntervalPerTick)
#define TIME_TO_TICKS(t) (static_cast<int>(0.5f + static_cast<float>(t) / TICK_INTERVAL))
#define TICKS_TO_TIME(t) (TICK_INTERVAL * static_cast<float>(t))
#define ROUND_TO_TICKS(t) (TICK_INTERVAL * TIME_TO_TICKS(t))
#define TICK_NEVER_THINK (-1)

enum EMultiplayerPhysicsMode : int
{
	PHYSICS_MULTIPLAYER_AUTODETECT = 0,
	PHYSICS_MULTIPLAYER_SOLID = 1,
	PHYSICS_MULTIPLAYER_NON_SOLID = 2,
	PHYSICS_MULTIPLAYER_CLIENTSIDE = 3
};

enum EHitGroupIndex : int
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_NECK,
	HITGROUP_GEAR = 10
};

enum EDamageType : int
{
	DAMAGE_NO = 0,
	DAMAGE_EVENTS_ONLY,
	DAMAGE_YES,
	DAMAGE_AIM
};

enum EObserverMode : int
{
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM,
	OBS_MODE_FREEZECAM,
	OBS_MODE_FIXED,
	OBS_MODE_IN_EYE,
	OBS_MODE_CHASE,
	OBS_MODE_ROAMING
};
#pragma endregion

#pragma region valve_textures

#define TEXTURE_GROUP_LIGHTMAP "Lightmaps"
#define TEXTURE_GROUP_WORLD "World textures"
#define TEXTURE_GROUP_MODEL "Model textures"
#define TEXTURE_GROUP_VGUI "VGUI textures"
#define TEXTURE_GROUP_PARTICLE "Particle textures"
#define TEXTURE_GROUP_DECAL "Decal textures"
#define TEXTURE_GROUP_SKYBOX "SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS "ClientEffect textures"
#define TEXTURE_GROUP_OTHER "Other textures"
#define TEXTURE_GROUP_PRECACHED "Precached"
#define TEXTURE_GROUP_CUBE_MAP "CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET "RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED "Unaccounted textures"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER "Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER "Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP "Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR "Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD "World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS "Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER "Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER "Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER "Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER "DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL "ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS "Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS "Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE "RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS "Morph Targets"

#define TEXTURE_SKYBOX_BAGGAGE "cs_baggage_skybox_"
#define TEXTURE_SKYBOX_TIBET "cs_tibet"
#define TEXTURE_SKYBOX_EMBASSY "embassy"
#define TEXTURE_SKYBOX_ITALY "italy"
#define TEXTURE_SKYBOX_JUNGLE "jungle"
#define TEXTURE_SKYBOX_NUKEBLANK "nukeblank"
#define TEXTURE_SKYBOX_OFFICE "office"
#define TEXTURE_SKYBOX_DAYLIGHT01 "sky_cs15_daylight01_hdr"
#define TEXTURE_SKYBOX_DAYLIGHT02 "sky_cs15_daylight02_hdr"
#define TEXTURE_SKYBOX_DAYLIGHT03 "sky_cs15_daylight03_hdr"
#define TEXTURE_SKYBOX_DAYLIGHT04 "sky_cs15_daylight04_hdr"
#define TEXTURE_SKYBOX_CLOUDY01 "sky_csgo_cloudy01"
#define TEXTURE_SKYBOX_NIGHT02 "sky_csgo_night02"
#define TEXTURE_SKYBOX_NIGHT02B "sky_csgo_night02b"
#define TEXTURE_SKYBOX_DUST "sky_dust"
#define TEXTURE_SKYBOX_VENICE "sky_venice"
#define TEXTURE_SKYBOX_VERTIGO "vertigo"
#define TEXTURE_SKYBOX_VERTIGO_HDR "vertigoblue_hdr"
#define TEXTURE_SKYBOX_VIETNAM "vietnam"
#pragma endregion

#pragma region valve_decals
#define CHAR_TEX_ANTLION 'A'
#define CHAR_TEX_BLOODYFLESH 'B'
#define CHAR_TEX_CONCRETE 'C'
#define CHAR_TEX_DIRT 'D'
#define CHAR_TEX_EGGSHELL 'E'
#define CHAR_TEX_FLESH 'F'
#define CHAR_TEX_GRATE 'G'
#define CHAR_TEX_ALIENFLESH 'H'
#define CHAR_TEX_CLIP 'I'
#define CHAR_TEX_SNOW 'K'
#define CHAR_TEX_PLASTIC 'L'
#define CHAR_TEX_METAL 'M'
#define CHAR_TEX_SAND 'N'
#define CHAR_TEX_FOLIAGE 'O'
#define CHAR_TEX_COMPUTER 'P'
#define CHAR_TEX_REFLECTIVE 'R'
#define CHAR_TEX_SLOSH 'S'
#define CHAR_TEX_TILE 'T'
#define CHAR_TEX_CARDBOARD 'U'
#define CHAR_TEX_VENT 'V'
#define CHAR_TEX_WOOD 'W'
#define CHAR_TEX_GLASS 'Y'
#define CHAR_TEX_WARPSHIELD 'Z'
#pragma endregion

enum class EClassIndex : int
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMapVetoPickController,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWeaponZoneRepulsor,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

enum EUserMessages : int
{
	CS_UM_VGUIMenu = 1,
	CS_UM_Geiger = 2,
	CS_UM_Train = 3,
	CS_UM_HudText = 4,
	CS_UM_SayText = 5,
	CS_UM_SayText2 = 6,
	CS_UM_TextMsg = 7,
	CS_UM_HudMsg = 8,
	CS_UM_ResetHud = 9,
	CS_UM_GameTitle = 10,
	CS_UM_Shake = 12,
	CS_UM_Fade = 13,
	CS_UM_Rumble = 14,
	CS_UM_CloseCaption = 15,
	CS_UM_CloseCaptionDirect = 16,
	CS_UM_SendAudio = 17,
	CS_UM_RawAudio = 18,
	CS_UM_VoiceMask = 19,
	CS_UM_RequestState = 20,
	CS_UM_Damage = 21,
	CS_UM_RadioText = 22,
	CS_UM_HintText = 23,
	CS_UM_KeyHintText = 24,
	CS_UM_ProcessSpottedEntityUpdate = 25,
	CS_UM_ReloadEffect = 26,
	CS_UM_AdjustMoney = 27,
	CS_UM_UpdateTeamMoney = 28,
	CS_UM_StopSpectatorMode = 29,
	CS_UM_KillCam = 30,
	CS_UM_DesiredTimescale = 31,
	CS_UM_CurrentTimescale = 32,
	CS_UM_AchievementEvent = 33,
	CS_UM_MatchEndConditions = 34,
	CS_UM_DisconnectToLobby = 35,
	CS_UM_PlayerStatsUpdate = 36,
	CS_UM_DisplayInventory = 37,
	CS_UM_WarmupHasEnded = 38,
	CS_UM_ClientInfo = 39,
	CS_UM_XRankGet = 40,
	CS_UM_XRankUpd = 41,
	CS_UM_CallVoteFailed = 45,
	CS_UM_VoteStart = 46,
	CS_UM_VotePass = 47,
	CS_UM_VoteFailed = 48,
	CS_UM_VoteSetup = 49,
	CS_UM_ServerRankRevealAll = 50,
	CS_UM_SendLastKillerDamageToClient = 51,
	CS_UM_ServerRankUpdate = 52,
	CS_UM_ItemPickup = 53,
	CS_UM_ShowMenu = 54,
	CS_UM_BarTime = 55,
	CS_UM_AmmoDenied = 56,
	CS_UM_MarkAchievement = 57,
	CS_UM_MatchStatsUpdate = 58,
	CS_UM_ItemDrop = 59,
	CS_UM_GlowPropTurnOff = 60,
	CS_UM_SendPlayerItemDrops = 61,
	CS_UM_RoundBackupFilenames = 62,
	CS_UM_SendPlayerItemFound = 63,
	CS_UM_ReportHit = 64,
	CS_UM_XpUpdate = 65,
	CS_UM_QuestProgress = 66,
	CS_UM_ScoreLeaderboardData = 67,
	CS_UM_PlayerDecalDigitalSignature = 68
};

enum EDrawModelFlags : unsigned int
{
	STUDIO_NONE = 0x00000000,
	STUDIO_RENDER = 0x00000001,
	STUDIO_VIEWXFORMATTACHMENTS = 0x00000002,
	STUDIO_DRAWTRANSLUCENTSUBMODELS = 0x00000004,
	STUDIO_TWOPASS = 0x00000008,
	STUDIO_STATIC_LIGHTING = 0x00000010,
	STUDIO_WIREFRAME = 0x00000020,
	STUDIO_ITEM_BLINK = 0x00000040,
	STUDIO_NOSHADOWS = 0x00000080,
	STUDIO_WIREFRAME_VCOLLIDE = 0x00000100,
	STUDIO_NOLIGHTING_OR_CUBEMAP = 0x00000200,
	STUDIO_SKIP_FLEXES = 0x00000400,
	STUDIO_DONOTMODIFYSTENCILSTATE = 0x00000800,
	STUDIO_SKIP_DECALS = 0x10000000,
	STUDIO_SHADOWTEXTURE = 0x20000000,
	STUDIO_SHADOWDEPTHTEXTURE = 0x40000000,
	STUDIO_TRANSPARENCY = 0x80000000
};

enum EShaderStencilFunc : int
{
	SHADER_STENCILFUNC_NEVER = 0,
	SHADER_STENCILFUNC_LESS,
	SHADER_STENCILFUNC_EQUAL,
	SHADER_STENCILFUNC_LEQUAL,
	SHADER_STENCILFUNC_GREATER,
	SHADER_STENCILFUNC_NOTEQUAL,
	SHADER_STENCILFUNC_GEQUAL,
	SHADER_STENCILFUNC_ALWAYS
};

enum EShaderStencilOp : int
{
	SHADER_STENCILOP_KEEP = 0,
	SHADER_STENCILOP_ZERO,
	SHADER_STENCILOP_SET_TO_REFERENCE,
	SHADER_STENCILOP_INCREMENT_CLAMP,
	SHADER_STENCILOP_DECREMENT_CLAMP,
	SHADER_STENCILOP_INVERT,
	SHADER_STENCILOP_INCREMENT_WRAP,
	SHADER_STENCILOP_DECREMENT_WRAP,
};

struct string_t
{
public:
	bool operator!() const { return (szValue == nullptr); }
	bool operator==(const string_t &rhs) const { return (szValue == rhs.szValue); }
	bool operator!=(const string_t &rhs) const { return (szValue != rhs.szValue); }
	bool operator<(const string_t &rhs) const { return (reinterpret_cast<void *>(const_cast<char *>(szValue)) < reinterpret_cast<void *>(const_cast<char *>(rhs.szValue))); }

	const char *c_str() const { return (szValue) ? szValue : ""; }

protected:
	const char *szValue;
};

#pragma region valve_sharedprops
enum EPropertyDataInteractions : int
{
	PROPINTER_PHYSGUN_WORLD_STICK,
	PROPINTER_PHYSGUN_FIRST_BREAK,
	PROPINTER_PHYSGUN_FIRST_PAINT,
	PROPINTER_PHYSGUN_FIRST_IMPALE,
	PROPINTER_PHYSGUN_LAUNCH_SPIN_NONE,
	PROPINTER_PHYSGUN_LAUNCH_SPIN_Z,
	PROPINTER_PHYSGUN_BREAK_EXPLODE,
	PROPINTER_PHYSGUN_BREAK_EXPLODE_ICE,
	PROPINTER_PHYSGUN_DAMAGE_NONE,
	PROPINTER_FIRE_FLAMMABLE,
	PROPINTER_FIRE_EXPLOSIVE_RESIST,
	PROPINTER_FIRE_IGNITE_HALFHEALTH,
	PROPINTER_PHYSGUN_CREATE_FLARE,
	PROPINTER_PHYSGUN_ALLOW_OVERHEAD,
	PROPINTER_WORLD_BLOODSPLAT,
	PROPINTER_PHYSGUN_NOTIFY_CHILDREN,
	PROPINTER_MELEE_IMMUNE,
	PROPINTER_NUM_INTERACTIONS
};

enum EMultiplayerBreak : int
{
	MULTIPLAYER_BREAK_DEFAULT,
	MULTIPLAYER_BREAK_SERVERSIDE,
	MULTIPLAYER_BREAK_CLIENTSIDE,
	MULTIPLAYER_BREAK_BOTH
};

class IMultiplayerPhysics
{
public:
	virtual int GetMultiplayerPhysicsMode() = 0;
	virtual float GetMass() = 0;
	virtual bool IsAsleep() = 0;
};

class IBreakableWithPropData
{
public:
	virtual void SetDmgModBullet(float flDmgMod) = 0;
	virtual void SetDmgModClub(float flDmgMod) = 0;
	virtual void SetDmgModExplosive(float flDmgMod) = 0;
	virtual float GetDmgModBullet() = 0;
	virtual float GetDmgModClub() = 0;
	virtual float GetDmgModExplosive() = 0;
	virtual float GetDmgModFire() = 0;

	virtual void SetExplosiveRadius(float flRadius) = 0;
	virtual void SetExplosiveDamage(float flDamage) = 0;
	virtual float GetExplosiveRadius() = 0;
	virtual float GetExplosiveDamage() = 0;

	virtual void SetPhysicsDamageTable(string_t iszTableName) = 0;
	virtual string_t GetPhysicsDamageTable() = 0;

	virtual void SetBreakableModel(string_t iszModel) = 0;
	virtual string_t GetBreakableModel() = 0;
	virtual void SetBreakableSkin(int iSkin) = 0;
	virtual int GetBreakableSkin() = 0;
	virtual void SetBreakableCount(int iCount) = 0;
	virtual int GetBreakableCount() = 0;
	virtual void SetMaxBreakableSize(int iSize) = 0;
	virtual int GetMaxBreakableSize() = 0;

	virtual void SetPropDataBlocksLOS(bool bBlocksLOS) = 0;
	virtual void SetPropDataIsAIWalkable(bool bBlocksLOS) = 0;

	virtual void SetInteraction(EPropertyDataInteractions Interaction) = 0;
	virtual bool HasInteraction(EPropertyDataInteractions Interaction) = 0;

	virtual void SetPhysicsMode(int iMode) = 0;
	virtual int GetPhysicsMode() = 0;

	virtual void SetMultiplayerBreakMode(EMultiplayerBreak mode) = 0;
	virtual EMultiplayerBreak GetMultiplayerBreakMode() const = 0;

	virtual void SetBasePropData(string_t iszBase) = 0;
	virtual string_t GetBasePropData() = 0;
};
#pragma endregion
