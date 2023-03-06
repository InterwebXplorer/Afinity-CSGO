#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/interfaces.h"
#include "../resources/sdk/entity.h"
#include "../resources/utils/eventlistener.h"
#include "../resources/utils/filelogging.h"
#include "../resources/utils/consolelogging.h"
#include "../resources/utils/inputsystem.h"
#include "../resources/utils/math.h"
#include "../options.h"
#include "misc.h"
#include <Windows.h>

void misc::autoaccept(const char* SoundEntry) {
    if (!Options.misc_general_autoaccept)
        return;

    if (strcmp(SoundEntry, "UIPanorama.popup_accept_match_beep")) {
        U::SetLocalPlayerReady();

        FLASHWINFO.cbSize = sizeof(FLASHWINFO);
        FLASHWINFO.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
        FLASHWINFO.uCount = 0;
        FLASHWINFO.dwTimeout = 0;
        FlashWindowEx(FLASHWINFO);
    }
}

void misc::autopistol(CUserCmd* Cmd, CBaseEntity* LocalPlayer) {
    if (!Options.misc_general_autopistol)
        return;

    if (!pLocal->IsAlive())
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

void misc::preservekillfeed() { //TODO
    if (!Options.misc_general_preservekillfeed)
        return;
    
    if (!IGameEvent->FindListener("round_end")) //reset???
        return;
}

void misc::autodefuse(CUserCmd* Cmd, CBaseEntity* LocalPlayer) {
    if (!Options.misc_general_autodefuse)
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

void misc::autoextinguishincendiarys(CUserCmd* Cmd, CBaseEntity* LocalPlayer) {
    if (!Options.misc_general_autoextinguishincendiarys)
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

void misc::fakeping() { //TODO
    if (!Options.misc_general_fakeping)
        return;

    //Options.misc_general_fakepingamount
}

void misc::clantag() { //TODO
    if (!Options.misc_general_clantag)
        return;
}

void misc::blockbot(CBaseEntity* pLocal) { //TODO
    if (!Options.misc_general_blockbot)
        return;

    if (!pLocal->IsAlive())
        return;

    CBaseEntity* pTarget = nullptr;

    for (int i = 0; i <= I::ClientEntityList->nMaxClients(); i++) {
        CBaseEntity* pEntity = I::ClientEntityList->GetClientEntity(i);

        if (!pEntity)
            continue;

        if (!pEntity->IsPlayer())
            continue;

        if (!pEntity->IsAlive())
            continue;

        if (pEntity = pLocal)
            continue;

        if (pEntity->IsEnemy())
            continue;

        float DistancetoEntity = pLocal->GetAbsOrigin().DistTo(pEntity->GetAbsOrigin());

        if (DistancetoEntity <= 250.0f) {
            pTarget = pEntity;
            break;
        }
    }

    if (!pTarget)
        return;

    
    
}

void misc::headstandbot(CBaseEntity* pLocal) { //TODO
    if (!Options.misc_general_headstandbot)
        return;

    if (!pLocal->IsAlive())
        return;

    
};

void misc::forceregion() { //TODO
    switch (Options.misc_general_forceregion) { //switch?
        case 1: 
            break;
    }

    std::string ServerLocations[] = {"", "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg", "maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp", "jnb", "mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh", "okc", "sea", "iad"} 
};

void misc::revealoverwatch() { //TODO
    if (!Options.misc_general_revealoverwatch)
        return;
};

void misc::revealranks(CUserCmd* Cmd) { 
    if (!Options.misc_general_revealranks)
        return;

    if (Cmd->iButtons & IN_SCORE)
        I::Client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0U, 0, nullptr);
};
 
void misc::slowwalk(CUserCmd* Cmd, CBaseEntity* LocalPlayer) { //
    if (!Options.misc_general_slowwalk)
        return;

    if (!pLocal->IsAlive())
        return;

    if (!pLocal->GetFlags() & FL_ONGROUND)
        return;

    if (!pLocal->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (!pLocal->GetMoveType() == MOVETYPE_LADDER)
        return;

    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

    if (!ActiveWeapon)
        return;

    int WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
    CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

    if (!ActiveWeaponData)
		return;

    float MaxWeaponSpeed = ActiveWeaponData->flMaxSpeed();
    float CalculateSpeed = MaxWeaponSpeed \ Options.misc_general_slowwalkspeed;
    
    Vector Velocity = LocalPlayer->GetVelocity();
    QAngle Direction;
    
    Math::VectorAngles(Velocity, Direction);
    
    float Speed = Velocity.Length2D();

    Direction.y = Cmd-> - Direction.y;

    Cmd->flForwardMove = ;
    Cmd->flSideMove = ;
};

void misc::infiniteduck(CUserCmd* Cmd, CBaseEntity* LocalPLayer) {
    if (!Options.misc_general_infiniteduck)
        return;

    if (!LocalPLayer->IsAlive())
        return;

    Cmd->iButtons & IN_BULLRUSH;
}

void misc::quickstop() { //TODO
    if (!Options.misc_general_quickstop)
        return;
}

void misc::unlockinventory() { //TODO
    if (!Options.misc_general_unlockinventory)
        return;
}

void misc::namechanger() { //TODO
    switch (Options.misc_general_namechanger) {
        case OFF: 
            break;

        case TEAMONLY:
            break;

        case ENEMYONLY:
            break;

        case EVERYONE:
            break;

        case CORRUPT:
            break;
    }
}

void misc::commandspammer() { //TODO
   I::Engine->ExecuteClientCmd(Options.misc_general_commandspammer) 
}

void misc::informationspammer() { //TODO
    switch (Options.misc_general_informationspammer) {
        case NAME:
            break;

        case RANK:
            break;
        
        case WEAPON:
            break;

        case LOCATION:
            break;

        case HEALTH:
            break;
    }
}

void misc::grenadehelper() { //TODO
    if (!Options.misc_general_grenadehelper)
        return;

    /*
    OPTION(char, Options.misc_general_grenadehelpervisiblekey, NULL);
    OPTION(char, Options.misc_general_grenadehelperexecutekey, NULL);
    OPTION(bool, Options.misc_general_grenadehelpervwge, false);
    */
}

void misc::bunnyhop(CUserCmd* pCmd, CBaseEntity* pLocal) { //TODO
    if (!Options.misc_general_bhop)
        return;

    if (I::ConVar->FindVar("sv_autobunnyhopping"))
        return;

    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (pLocal->GetMoveType() == MOVETYPE_LADDER)
        return;

    if (pLocal->GetMoveType() == MOVETYPE_OBSERVER)
        return;

    //Options.misc_general_bhophitchance;
    //Options.misc_general_bhophitchancerandom;

    /*
        if (pLocal->GetFlags() & FL_ONGROUND && pCmd->iButtons & IN_JUMP)
            pCmd->iButtons &= ~IN_JUMP;
    */
}

void misc::autostrafe() { //TODO
    if (!Options.misc_general_autostrafe)
        return;

    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (pLocal->GetMoveType() == MOVETYPE_LADDER)
        return;  

    if (pLocal->GetFlags() & FL_ONGROUND)
		return;

    
}

void misc::aircrouch(CBaseEntity* pLocal, CUserCmd* pCmd) {
    if (Options.misc_general_aircrouch)
        return;

    if (!pLocal->IsAlive())
        return;

    if (!pLocal->GetFlags() & FL_ONGROUND)
        pCmd->iButtons |= IN_DUCK;
    else 
        pCmd->iButtons &= ~IN_DUCK;
}

void misc::peekassist(CBaseEntity* pLocal, CUserCmd* pCmd) { //TODO
    if (!Options.misc_general_peekassist)
        return;

    if (IPT::IsKeyDown(Options.misc_general_peekassistkey)) {
        ImDrawList::AddCircleFilled(ImVec2(0, 0), 10, ImColor(255, 255, 255, 255), 32);

    }

    if (IPT::IsKeyReleased(Options.misc_general_peekassistkey) || pCmd->iButtons(IN_ATTACK || IN_SECOND_ATTACK)) {

    }
}

void misc::buybot() {
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

void misc::triggerban(CUserCmd* pCmd) {
    if (!Options.misc_general_triggerban)
        return;
    
    WriteToLog("[Warning] Triggering untrusted ban");
    WriteToConsole("[Warning] Triggering untrusted ban");

    QAngle angSentView = {999.0f, 999.0f, 999.0f};

    pCmd->angViewPoint = angSentView;
}

void misc::unlockachievements() {
    if (!Options.misc_general_unlockachievements)
        return;
}

/*
    OPTION(bool, Options.misc_general_unload, false);
*/