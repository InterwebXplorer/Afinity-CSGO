#include "entity.h"
#include "../utils/math.h"
#include "../utils.h"
#include "interfaces.h"

#pragma region entity_baseentity
CBaseEntity *CBaseEntity::GetLocalPlayer() {
	return I::ClientEntityList->Get<CBaseEntity>(I::Engine->GetLocalPlayer());
}

int CBaseEntity::GetSequenceActivity(int iSequence) {
	studiohdr_t *pStudioHdr = I::ModelInfo->GetStudioModel(this->GetModel());

	if (pStudioHdr == nullptr)
		return -1;

	using GetSequenceActivityFn = int(__fastcall *)(void *, void *, int);
	static auto oGetSequenceActivity = reinterpret_cast<GetSequenceActivityFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 53 8B 5D 08 56 8B F1 83"));
	assert(oGetSequenceActivity != nullptr);

	return oGetSequenceActivity(this, pStudioHdr, iSequence);
}

CBaseCombatWeapon *CBaseEntity::GetWeapon() {
	return I::ClientEntityList->Get<CBaseCombatWeapon>(this->GetActiveWeaponHandle());
}

int CBaseEntity::GetMaxHealth() {
	if (I::GameTypes->GetCurrentGameType() == GAMETYPE_FREEFORALL)
		return 120;

	return 100;
}

std::optional<Vector> CBaseEntity::GetBonePosition(int iBone) {
	assert(iBone > BONE_INVALID && iBone < MAXSTUDIOBONES);

	std::array<matrix3x4_t, MAXSTUDIOBONES> arrBonesToWorld = {};

	if (this->SetupBones(arrBonesToWorld.data(), arrBonesToWorld.size(), BONE_USED_BY_ANYTHING, 0.f))
		return arrBonesToWorld.at(iBone).at(3);

	return std::nullopt;
}

int CBaseEntity::GetBoneByHash(const FNV1A_t uBoneHash) const {
	if (const auto pModel = this->GetModel(); pModel != nullptr) {
		if (const auto pStudioHdr = I::ModelInfo->GetStudioModel(pModel); pStudioHdr != nullptr) {
			for (int i = 0; i < pStudioHdr->nBones; i++) {
				if (const auto pBone = pStudioHdr->GetBone(i); pBone != nullptr && FNV1A::Hash(pBone->GetName()) == uBoneHash)
					return i;
			}
		}
	}

	return BONE_INVALID;
}

std::optional<Vector> CBaseEntity::GetHitboxPosition(const int iHitbox) {
	assert(iHitbox > HITBOX_INVALID && iHitbox < HITBOX_MAX);

	std::array<matrix3x4_t, MAXSTUDIOBONES> arrBonesToWorld = {};

	if (const auto pModel = this->GetModel(); pModel != nullptr) {
		if (const auto pStudioHdr = I::ModelInfo->GetStudioModel(pModel); pStudioHdr != nullptr) {
			if (const auto pHitbox = pStudioHdr->GetHitbox(iHitbox, 0); pHitbox != nullptr)  {
				if (this->SetupBones(arrBonesToWorld.data(), arrBonesToWorld.size(), BONE_USED_BY_HITBOX, 0.f)) {
					const Vector vecMin = M::VectorTransform(pHitbox->vecBBMin, arrBonesToWorld.at(pHitbox->iBone));
					const Vector vecMax = M::VectorTransform(pHitbox->vecBBMax, arrBonesToWorld.at(pHitbox->iBone));

					return (vecMin + vecMax) * 0.5f;
				}
			}
		}
	}

	return std::nullopt;
}

std::optional<Vector> CBaseEntity::GetHitGroupPosition(const int iHitGroup) {
	assert(iHitGroup >= HITGROUP_GENERIC && iHitGroup <= HITGROUP_GEAR);

	std::array<matrix3x4_t, MAXSTUDIOBONES> arrBonesToWorld = {};

	if (const auto pModel = this->GetModel(); pModel != nullptr) {
		if (const auto pStudioHdr = I::ModelInfo->GetStudioModel(pModel); pStudioHdr != nullptr) {
			if (const auto pHitboxSet = pStudioHdr->GetHitboxSet(this->GetHitboxSet()); pHitboxSet != nullptr) {
				if (this->SetupBones(arrBonesToWorld.data(), arrBonesToWorld.size(), BONE_USED_BY_HITBOX, 0.f)) {
					mstudiobbox_t *pHitbox = nullptr;
					for (int i = 0; i < pHitboxSet->nHitboxes; i++) {
						pHitbox = pHitboxSet->GetHitbox(i);

						if (pHitbox->iGroup == iHitGroup)
							break;
					}

					if (pHitbox != nullptr) {

						const Vector vecMin = M::VectorTransform(pHitbox->vecBBMin, arrBonesToWorld.at(pHitbox->iBone));
						const Vector vecMax = M::VectorTransform(pHitbox->vecBBMax, arrBonesToWorld.at(pHitbox->iBone));

						return (vecMin + vecMax) * 0.5f;
					}
				}
			}
		}
	}

	return std::nullopt;
}

void CBaseEntity::ModifyEyePosition(const CCSGOPlayerAnimState *pAnimState, Vector *vecPosition) const {

	if (I::Engine->IsHLTV() || I::Engine->IsPlayingDemo())
		return;

	CBaseEntity *pBaseEntity = pAnimState->pEntity;

	if (pBaseEntity == nullptr)
		return;

	IClientEntity *pGroundEntity = I::ClientEntityList->GetClientEntityFromHandle(pBaseEntity->GetGroundEntityHandle());

	if (!pAnimState->bHitGroundAnimation && pAnimState->flDuckAmount == 0.f && pGroundEntity != nullptr)
		return;

	if (const auto headPosition = pBaseEntity->GetBonePosition(pBaseEntity->GetBoneByHash(FNV1A::HashConst("head_0"))); headPosition.has_value()) {
		Vector vecHead = headPosition.value();
		vecHead.z += 1.7f;

		if (vecHead.z < vecPosition->z) {
			float flFactor = 0.f;
			const float flDelta = std::fabsf(vecPosition->z - vecHead.z);
			const float flOffset = (flDelta - 4.0f) / 6.0f;

			if (flOffset >= 0.f)
				flFactor = std::min(flOffset, 1.0f);

			const float flFactorSquared = (flFactor * flFactor);
			vecPosition->z += ((vecHead.z - vecPosition->z) * ((flFactorSquared * 3.0f) - ((flFactorSquared * 2.0f) * flFactor)));
		}
	}
}

void CBaseEntity::PostThink() {

	using PostThinkVPhysicsFn = bool(__thiscall *)(CBaseEntity *);
	static auto oPostThinkVPhysics = reinterpret_cast<PostThinkVPhysicsFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB"));
	assert(oPostThinkVPhysics != nullptr);

	using SimulatePlayerSimulatedEntitiesFn = void(__thiscall *)(CBaseEntity *);
	static auto oSimulatePlayerSimulatedEntities = reinterpret_cast<SimulatePlayerSimulatedEntitiesFn>(MEM::FindPattern(CLIENT_DLL, "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 74"));
	assert(oSimulatePlayerSimulatedEntities != nullptr);

	I::MDLCache->BeginLock();

	if (this->IsAlive()) {
		this->UpdateCollisionBounds();

		if (this->GetFlags() & FL_ONGROUND)
			*this->GetFallVelocity() = 0.f;

		if (this->GetSequence() == -1)
			this->SetSequence(0);

		this->StudioFrameAdvance();
		oPostThinkVPhysics(this);
	}

	oSimulatePlayerSimulatedEntities(this);

	I::MDLCache->EndLock();
}

bool CBaseEntity::IsEnemy(CBaseEntity *pEntity) {

	if (I::GameTypes->GetCurrentGameType() == GAMETYPE_FREEFORALL)

		return (this->GetSurvivalTeam() != pEntity->GetSurvivalTeam());

	static CConVar *mp_teammates_are_enemies = I::ConVar->FindVar("mp_teammates_are_enemies");

	if (mp_teammates_are_enemies != nullptr && mp_teammates_are_enemies->GetBool() && this->GetTeam() == pEntity->GetTeam() && this != pEntity)
		return true;

	if (this->GetTeam() != pEntity->GetTeam())
		return true;

	return false;
}

bool CBaseEntity::IsTargetingLocal(CBaseEntity *pLocal) {
	Vector vecForward = {};
	const QAngle angView = this->GetEyeAngles();
	M::AngleVectors(angView, &vecForward);
	vecForward *= MAX_DISTANCE;

	const Vector vecStart = this->GetEyePosition();
	const Vector vecEnd = vecStart + vecForward;

	const Ray_t ray(vecStart, vecEnd);
	CTraceFilter filter(this);

	Trace_t trace = {};
	I::EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);

	if (trace.pHitEntity == pLocal)
		return true;

	return false;
}

bool CBaseEntity::CanShoot(CWeaponCSBase *pBaseWeapon) {
	const float flServerTime = TICKS_TO_TIME(this->GetTickBase());

	if (pBaseWeapon->GetAmmo() <= 0)
		return false;

	if (this->GetNextAttack() > flServerTime)
		return false;

	const short nDefinitionIndex = pBaseWeapon->GetItemDefinitionIndex();

	if ((nDefinitionIndex == WEAPON_FAMAS || nDefinitionIndex == WEAPON_GLOCK) &&

		pBaseWeapon->IsBurstMode() && pBaseWeapon->GetBurstShotsRemaining() > 0)
		return true;

	if (pBaseWeapon->GetNextPrimaryAttack() > flServerTime)
		return false;

	if (nDefinitionIndex == WEAPON_REVOLVER && pBaseWeapon->GetFireReadyTime() > flServerTime)
		return false;

	return true;
}

bool CBaseEntity::IsVisible(CBaseEntity *pEntity, const Vector &vecEnd, bool bSmokeCheck) {
	const Vector vecStart = this->GetEyePosition(false);

	const Ray_t ray(vecStart, vecEnd);
	CTraceFilter filter(this);

	Trace_t trace = {};
	I::EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);

	if ((trace.IsVisible() || trace.pHitEntity == pEntity) &&

		!(bSmokeCheck && U::LineGoesThroughSmoke(vecStart, vecEnd)))
		return true;

	return false;
}

bool CBaseEntity::IsBreakable() {
	const int iHealth = this->GetHealth();

	if (iHealth < 0 && this->IsMaxHealth() > 0)
		return true;

	if (this->GetTakeDamage() != DAMAGE_YES)
	{
		const EClassIndex nClassIndex = this->GetClientClass()->nClassID;

		if (nClassIndex != EClassIndex::CFuncBrush)
			return false;
	}

	if (const int nCollisionGroup = this->GetCollisionGroup(); nCollisionGroup != COLLISION_GROUP_PUSHAWAY && nCollisionGroup != COLLISION_GROUP_BREAKABLE_GLASS && nCollisionGroup != COLLISION_GROUP_NONE)
		return false;

	if (iHealth > 200)
		return false;

	if (IMultiplayerPhysics *pPhysicsInterface = dynamic_cast<IMultiplayerPhysics *>(this); pPhysicsInterface != nullptr) {
		if (pPhysicsInterface->GetMultiplayerPhysicsMode() != PHYSICS_MULTIPLAYER_SOLID)
			return false;
	}
	else {
		if (const char *szClassName = this->GetClassname(); !strcmp(szClassName, "func_breakable")) || !strcmp(szClassName, "func_breakable_surf") {
			if (!strcmp(szClassName, "func_breakable_surf")) {
				CBreakableSurface *pSurface = static_cast<CBreakableSurface *>(this);

				if (pSurface->IsBroken())
					return false;
			}
		}
		else if (this->PhysicsSolidMaskForEntity() & CONTENTS_PLAYERCLIP) {

			return false;
		}
	}

	if (IBreakableWithPropData *pBreakableInterface = dynamic_cast<IBreakableWithPropData *>(this); pBreakableInterface != nullptr) {
		if (pBreakableInterface->GetDmgModBullet() <= 0.0f)
			return false;
	}

	return true;
}
#pragma endregion
