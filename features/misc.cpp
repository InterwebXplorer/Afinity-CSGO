#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/interfaces.h"
#include "../resources/sdk/entity.h"
#include "../resources/utils/eventlistener.h"
#include "../resources/utils/filelogging.h"
#include "../resources/utils/consolelogging.h"
#include "../resources/utils/inputsystem.h"
#include "../resources/utils/math.h"
#include "../resources/utils/memory.h"
#include "esp.h"
#include "../options.h"
#include "misc.h"
#include <Windows.h>
#include <Vector>

void Misc::AutoPistol(CUserCmd* Cmd) {
    if (!Options.misc_general_autopistol)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

    if (!ActiveWeapon)
        return;
        
	const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
	const CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

	if (!ActiveWeaponData)
		return;

    if (ActiveWeaponData->bFullAuto)
        return;

    if (!ActiveWeaponData->nWeaponType == WEAPONTYPE_PISTOL)
        return;

    if (ActiveWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
        return;

	if (LocalPlayer->CanShoot(static_cast<CWeaponCSBase*>(ActiveWeapon)) && Cmd->iButtons & IN_ATTACK)
		Cmd->iButtons |= IN_ATTACK;
	else
		Cmd->iButtons &= ~IN_ATTACK;
}

void Misc::FixTabletSignal() {
    if (!Options.misc_general_fixtabletsignal)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

    if (!ActiveWeapon)
        return;

    const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
    CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

    if (!ActiveWeaponData)
		return;

	if (!ActiveWeaponData->nWeaponType = WEAPONTYPE_TABLET)
		return;
    
    ActiveWeapon->IsReceptionBlocked() = false;
}

void Misc::AutoDefuse(CUserCmd* Cmd) {
    if (!Options.misc_general_autodefuse)
        return;
        
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    if (!LocalPlayer->GetTeam() == TEAM_CT)
        return;

    CPlantedC4* PlantedBomb = nullptr;
    CBaseEntity* PlantedBombEntity = nullptr;

    for (int i = 0; i <= I::ClientEntityList->GetHighestEntityIndex(); i++) {
        CBaseEntity* Entity = I::ClientEntityList->GetClientEntity(i);

        if (!Entity)
            return;
        
        if (Entity->GetClientClass()->nClassID == EClassIndex::CPlantedC4) {
            PlantedBomb = (CPlantedC4*)Entity;
            PlantedBombEntity = Entity;
            break;
        }
    }

    if (!PlantedBomb)
        return;

    if (PlantedBomb->IsDefused())
        return;

    float RemainingTime = PlantedBomb->GetBlowTime() - (LocalPlayer->GetTickBase() * I::Globals->flIntervalPerTick);
    float DistancetoBomb = LocalPlayer->GetOrigin().DistTo(PlantedBombEntity->GetOrigin());

    if (LocalPlayer->HasDefuser() && RemainingTime > 5.5f)
        return;

    if (!LocalPlayer->HasDefuser() && RemainingTime > 10.5f)
        return;
    
    if (DistancetoBomb <= 75.0f)
        Cmd->iButtons |= IN_USE;
}

void Misc::AutoExtinguishIncendiarys(CUserCmd* Cmd) {
    if (!Options.misc_general_autoextinguishincendiarys)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;
    
    if (!LocalPlayer->IsAlive())
		return;

    for (int i = 0; i <= MAX_WEAPONS; i++) {
        unsigned int* WeaponsHandle = LocalPlayer->GetWeaponsHandle();

        if (!WeaponsHandle)
            continue;

        if (WeaponsHandle[i] == -1)
            continue;

        CBaseCombatWeapon* WeaponEntity = I::ClientEntityList->Get<CBaseCombatWeapon>(WeaponsHandle[i]);

        if (!WeaponEntity)
            continue;

        if (WeaponEntity->GetItemDefinitionIndex() == WEAPON_SMOKEGRENADE)
            break;
    }

    CBaseCSGrenade* Incendiary = nullptr;

    for (int i = 0; i <= I::ClientEntityList->GetHighestEntityIndex(); i++) {
        IClientEntity* Entity = I::ClientEntityList->GetClientEntity(i);

        if (!Entity)
            continue;

        if (Entity->GetClientClass()->nClassID == EClassIndex::CInferno) {
            Incendiary = (CBaseCSGrenade*)Entity;
            break;
        }
    }

    if (!Incendiary)
        return;
	
    float DistanceToIncendiary = LocalPlayer->GetAbsOrigin().DistTo(Incendiary->GetAbsOrigin());
    QAngle IncendiaryViewAngle = Math::CalcAngle(LocalPlayer->GetEyePosition(), Incendiary->GetAbsOrigin());
    QAngle CurrentViewAngle = LocalPlayer->GetEyeAngles();

	if (DistanceToIncendiary <= 120.0f) {
		I::Engine->ExecuteClientCmd("use weapon_smokegrenade");

		CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

		if (!ActiveWeapon)
			return;

		if (!ActiveWeapon->GetItemDefinitionIndex() = WEAPON_SMOKEGRENADE)
			return;

		Cmd->angViewPoint = IncendiaryViewAngle;
	    Cmd->iButtons |= IN_ATTACK;
		Cmd->angViewPoint = CurrentViewAngle;
	}
}

void Misc::ClanTag() {
    if (!Options.misc_general_clantag)
        return;

    const char* ClanTag[] = {"<>", "<A>", "<AF>", "<AFI>", "<AFIN>", "<AFINI>", "<AFINIT>", "<AFINITY>", "<------->", "<AFINITY>", "<------->", "<AFINITY>", "<AFINIT>", "<AFINI>", "<AFIN>", "<AFI>", "<AF>", "<A>", "<>"};

    for (int i = 0; i < ClanTag[].size(); i++) {
        SendClanTag(ClanTag[i], "Afinity");
    }
}

void Misc::BlockBot() { //TODO
    if (!Options.misc_general_blockbot)
        return;
}

void Misc::HeadstandBot() { //TODO
    if (!Options.misc_general_headstandbot)
        return;
}

void Misc::ForceRegion() {
    std::string ServerLocations[] = {"", "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg", "maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp", "jnb", "mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh", "okc", "sea", "iad"};
    std::string** RelayCluster = reinterpret_cast<std::string**>(Memory::FindPattern("steamnetworkingsockets", "B8 ?? ?? B9 ?? ?? 0F 43") + 0x1);

    *RelayCluster = ServerLocations[Options.misc_general_forceregion];
}

void Misc::RevealRanks(CUserCmd* Cmd) { 
    if (!Options.misc_general_revealranks)
        return;

    if (Cmd->iButtons & IN_SCORE)
        I::Client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0U, 0, nullptr);
}
 
void Misc::SlowWalk(CUserCmd* Cmd) { //TODO
    if (!Options.misc_general_slowwalk)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    if (!LocalPlayer->GetFlags() & FL_ONGROUND)
        return;

    if (!LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (!LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
        return;

    
}

void Misc::InfiniteDuck(CUserCmd* Cmd) {
    if (!Options.misc_general_infiniteduck)
        return;
    
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPLayer->IsAlive())
        return;

    Cmd->iButtons & IN_BULLRUSH;
}

void Misc::QuickStop(CUserCmd* Cmd) { //TODO
    if (!Options.misc_general_quickstop)
        return;
}

void Misc::NameChanger() {
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    std::vector<CBaseEntity*> Players; 

    for (int i = 0; i < I::Engine->GetMaxClients(); i++) {
        CBaseEntity Entity = I::ClientEntityList->Get<CBaseEntity>(i);

        if (!Entity)
            continue;

        if (Entity == LocalPlayer)
            continue;

        Players.push_back(Entity);
    }

    switch (Options.misc_general_namechanger) {
        case OFF: 
            break;

        case TEAMONLY:
            for (int i = 0; i < Players.size(); i++) {
                if (Players[i]->IsEnemy())
                    continue;

                PlayerInfo_t PlayerInfo;

                if (!I::Engine->GetPlayerInfo(Players[i], PlayerInfo))
                    continue;

                if (PlayerInfo.bFakePlayer)
                    continue;

                SendName(PlayerInfo.szName.c_str());
            }
            break;

        case ENEMYONLY:
            for (int i = 0; i < Players.size(); i++) {
                if (!Players[i]->IsEnemy())
                    continue;

                PlayerInfo_t PlayerInfo;

                if (!I::Engine->GetPlayerInfo(Players[i], PlayerInfo))
                    continue;

                if (PlayerInfo.bFakePlayer)
                    continue;

                SendName(PlayerInfo.szName.c_str());
            }
            break;

        case EVERYONE:
            for (int i = 0; i < Players.size(); i++) {
                PlayerInfo_t PlayerInfo;

                if (!I::Engine->GetPlayerInfo(Players[i], PlayerInfo))
                    continue;

                if (PlayerInfo.bFakePlayer)
                    continue;

                SendName(PlayerInfo.szName.c_str());
            }
            break;
    }
}

void Misc::CommandSpammer() {
    if (Options.misc_general_commandspammer.empty())
        return;

    I::Engine->ExecuteClientCmd(Options.misc_general_commandspammer);
}

void Misc::InformationSpammer() {
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();
    CBaseEntity* TargetEntity = nullptr;

    for (int i = 0; i < I::Engine->GetMaxClients(); i++) {
        CBaseEntity* Entity = I::ClientEntityList->Get<CBaseEntity>(i);

        if (!Entity)
            continue;

        if (!Entity->IsEnemy())
            continue;

        if (Entity == LocalPlayer)
            continue;

        TargetEntity = Entity;
    }

    PlayerInfo_t PlayerInfo;
    I::Engine->GetPlayerInfo(TargetEntity, PlayerInfo);

    switch (Options.misc_general_informationspammer) {
        case WEAPON:
            const char* ChatString = PlayerInfo.szName + "is using" + ESP::GetWeaponName(TargetEntity->GetWeapon());
            I::Engine->ExecuteClientCmd(ChatString, 0);
            break;

        case LOCATION:
            const char* ChatString = PlayerInfo.szName + "is at" + TargetEntity->GetLastPlace();
            I::Engine->ExecuteClientCmd(ChatString, 0);
            break;

        case HEALTH:
            const char* ChatString = PlayerInfo.szName + "has" + TargetEntity->GetHealth() + "health";
            I::Engine->ExecuteClientCmd(ChatString, 0);
            break;
    }
}

/*
void Misc::GrenadeHelper() { //TODO
    if (!Options.misc_general_grenadehelper)
        return;

    //Options.misc_general_grenadehelpervisiblekey
    //Options.misc_general_grenadehelperexecutekey
    //Options.misc_general_grenadehelpervwge
}
*/

void Misc::BunnyHop(CUserCmd* Cmd) {
    if (!Options.misc_general_bhop)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    if (I::ConVar->FindVar("sv_autobunnyhopping"))
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_OBSERVER)
        return;

    int RandomNumber = rand() % 100 + 1;
    int SuccessfulHits = 0;
    static int HitChance = Options.misc_general_bhophitchance;

    if (Options.misc_general_bhophitchancerandom)
        HitChance = Math::RandomInt(0, Options.misc_general_bhophitchance);

    if (RandomNumber > HitChance)
        return;

    if (SuccessfulHits > (HitChance / 10)) {
        SuccessfulHits = 0;
        return;
    }

    if (LocalPlayer->GetFlags() & FL_ONGROUND && Cmd->iButtons & IN_JUMP) {
        Cmd->iButtons &= ~IN_JUMP;
        SuccessfulHits += 1;
    }

    else if (!(LocalPlayer->GetFlags() & FL_ONGROUND) && (Cmd->iButtons & IN_JUMP))
        Cmd->iButtons &= ~IN_JUMP;

    else if ((Cmd->iButtons & IN_JUMP) && (LocalPlayer->GetFlags() & FL_ONGROUND)) {
        Cmd->iButtons &= ~IN_JUMP;
        SuccessfulHits += 1;
    }
}

void Misc::AutoStrafe(CUserCmd* Cmd) { //TODO
    if (!Options.misc_general_autostrafe)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer->IsAlive())
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
        return;  

    if (LocalPlayer->GetFlags() & FL_ONGROUND)
		return;

    if ()
}

void Misc::AirCrouch(CUserCmd* Cmd) {
    if (Options.misc_general_aircrouch)
        return;
    
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    if (!LocalPlayer->GetFlags() & FL_ONGROUND)
        Cmd->iButtons |= IN_DUCK;
    else 
        Cmd->iButtons &= ~IN_DUCK;
}

void Misc::PeekAssist(CUserCmd* Cmd) { //TODO
    if (!Options.misc_general_peekassist)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;
}

void Misc::BuyBot() {
    if (!Options.misc_buybot_enable)
        return;

    if (!IGameEvent->FindListener("round_start"))
        return;

    switch (Options.misc_buybot_primary) {
        case OFF:
            break;

        case AUTO:
            I::Engine->ExecuteClientCmd("buy g3sg1");
            WriteToLog("[Generic] Bought autosniper");
            WriteToConsole("[Generic] Bought autosniper");
            break;

        case SCOUT:
            I::Engine->ExecuteClientCmd("buy ssg08");
            WriteToLog("[Generic] Bought scout");
            WriteToConsole("[Generic] Bought scout");
            break;

        case AWP:
            I::Engine->ExecuteClientCmd("buy awp");
            WriteToLog("[Generic] Bought awp");
            WriteToConsole("[Generic] Bought awp");
            break;

        case AKM4:
            I::Engine->ExecuteClientCmd("buy ak47");
            WriteToLog("[Generic] Bought ak/m4");
            WriteToConsole("[Generic] Bought ak/m4");
            break;
    }

    switch (Options.misc_buybot_secondary) {
        case OFF:
            break;

        case DUALBERETTAS: 
            I::Engine->ExecuteClientCmd("buy elite");
            WriteToLog("[Generic] Bought dual-berettas");
            WriteToConsole("[Generic] Bought dual-berettas");
            break;

        case P250: 
            I::Engine->ExecuteClientCmd("buy p250");
            WriteToLog("[Generic] Bought p250");
            WriteToConsole("[Generic] Bought p250");
            break;

        case FIVE7TEC9: 
            I::Engine->ExecuteClientCmd("buy tec9");
            WriteToLog("[Generic] Bought five7/tec9");
            WriteToConsole("[Generic] Bought five7/tec9");
            break;

        case DEAGLER8: 
            I::Engine->ExecuteClientCmd("buy revolver");
            WriteToLog("[Generic] Bought deagle/r8");
            WriteToConsole("[Generic] Bought deagle/r8");
            break;
    }

    switch (Options.misc_buybot_nades) {
        case SMOKE: 
            I::Engine->ExecuteClientCmd("buy smokegrenade");
            WriteToLog("[Generic] Bought smoke grenade");
            WriteToConsole("[Generic] Bought smoke grenade");
            break;

        case FLASH: 
            I::Engine->ExecuteClientCmd("buy flashbang");
            WriteToLog("[Generic] Bought flashbang");
            WriteToConsole("[Generic] Bought flashbang");
            break;

        case INCENDIARY: 
            I::Engine->ExecuteClientCmd("buy molotov");
            WriteToLog("[Generic] Bought incendiary");
            WriteToConsole("[Generic] Bought incendiary");
            break;

        case DECOY: 
            I::Engine->ExecuteClientCmd("buy decoy");
            WriteToLog("[Generic] Bought decoy");
            WriteToConsole("[Generic] Bought decoy");
            break;

        case HEGRENADE: 
            I::Engine->ExecuteClientCmd("buy hegrenade");
            WriteToLog("[Generic] Bought he grenade");
            WriteToConsole("[Generic] Bought he grenade");
            break;
    }

    switch (Options.misc_buybot_other) {
        case KEVLAR: 
            I::Engine->ExecuteClientCmd("buy vest");
            WriteToLog("[Generic] Bought half armour");
            WriteToConsole("[Generic] Bought half armour");
            break;

        case HELMET: 
            I::Engine->ExecuteClientCmd("buy vesthelm");
            WriteToLog("[Generic] Bought full armour");
            WriteToConsole("[Generic] Bought full armour");
            break;

        case DEFUSER: 
            I::Engine->ExecuteClientCmd("buy defuser");
            WriteToLog("[Generic] Bought defuser");
            WriteToConsole("[Generic] Bought defuser");
            break;

        case TASER: 
            I::Engine->ExecuteClientCmd("buy taser");
            WriteToLog("[Generic] Bought taser");
            WriteToConsole("[Generic] Bought taser");
            break;
        
        case RIOTSHEILD: 
            I::Engine->ExecuteClientCmd("buy riotshield");
            WriteToLog("[Generic] Bought riotsheild");
            WriteToConsole("[Generic] Bought riotsheild");
            break;
    }
}

void Misc::TriggerBan(CUserCmd* Cmd) {
    if (!Options.misc_general_triggerban)
        return;
    
    WriteToLog("[Warning] Triggering untrusted ban");
    WriteToConsole("[Warning] Triggering untrusted ban");

    QAngle SentView = {999.0f, 999.0f, 999.0f};

    Cmd->angViewPoint = SentView;
}

void Misc::UnlockAchievements() { //TODO
    if (!Options.misc_general_unlockachievements)
        return;

}

#pragma region UtilityFunctions
void Misc::SendClanTag(const char* ClanTag, const char* Identifier) {
    using SendClanTagFunction = void(__fastcall*)(const char*, const char*);
    static auto OriginalSendClanTag = reinterpret_cast<SendClanTagFunction>(Memory::FindPattern(ENGINE_DLL, "53 56 57 8B DA 8B F9 FF 15"));
    assert(OriginalSendClanTag != nullptr);

    OriginalSendClanTag(ClanTag, Identifier);
}

void Misc::SendName(const char* Name) {
    static CConVar* Name = I::ConVar->FindVar("name");
    Name->fnChangeCallbacks.Size() = NULL;

    if (Name != nullptr)
        Name->SetValue(Name);
}
#pragma endregion