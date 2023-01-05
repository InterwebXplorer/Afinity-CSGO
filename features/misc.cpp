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

void misc::autoaccept(const char* pSoundEntry) {
    if (!Options.misc_general_autoaccept)
        return;

    if (strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep")) {
        U::SetLocalPlayerReady();

        FLASHWINFO.cbSize = sizeof(FLASHWINFO);
        FLASHWINFO.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
        FLASHWINFO.uCount = 0;
        FLASHWINFO.dwTimeout = 0;
        FlashWindowEx(FLASHWINFO);
    }
}

void misc::autopistol(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (!Options.misc_general_autopistol)
        return;

    if (!pLocal->IsAlive())
        return;

    CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

    if (!pWeapon)
        return;
        
	const short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	const CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

	if (!pWeaponData)
		return;

    if (pWeaponData->bFullAuto)
        return;

    if (!pWeaponData->nWeaponType == WEAPONTYPE_PISTOL)
        return;

	if (pLocal->CanShoot(static_cast<CWeaponCSBase*>(pWeapon)) && pCmd->iButtons & IN_ATTACK)
		pCmd->iButtons |= IN_ATTACK;
	else
		pCmd->iButtons &= ~IN_ATTACK;
}

void misc::preservekillfeed() { //TODO
    if (!Options.misc_general_preservekillfeed)
        return;
    
    if (!IGameEvent->FindListener("round_end")) //reset???
        return;
}

void misc::autodefuse(CUserCmd* pCmd, CPlantedC4* pBomb, CBaseEntity* pLocal) {
    if (!Options.misc_general_autodefuse)
        return;
        
    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetTeam() == TEAM_TT)
        return;

    if (!pBomb->IsPlanted)
        return; 

    for (int i = 0; i < IClientEntityList::GetHighestEntityIndex(); i++) {
        CBaseEntity* Entity = IClientEntityList::GetClientEntity(i);

        if (!Entity)
            return;
        
        if (Entity->GetClientClass()->nClassID == EClassIndex::CPlantedC4)
            pBomb = (CPlantedC4*)Entity;
    }

    float RemainingTime = pBomb->GetBlowTime();
    float DistancetoBomb = pLocal->GetOrigin().DistTo(pBomb->GetOrigin());

    if (pLocal->HasDefuser() && RemainingTime > 5.5f)
        return;

    if (!pLocal->HasDefuser() && RemainingTime > 10.5f)
        return;
    
    if (DistancetoBomb <= 75.0f)
        pCmd->iButtons |= IN_USE;
}

void misc::autoextinguishincendiarys() { //DIDNT FUCKING WORK
    if (!Options.misc_general_autoextinguishincendiarys)
        return;
    
    if (!pLocal->IsAlive())
        return;
/*
	CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

    if (!pWeapon)
        return;

    int nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
    CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

    if (!pWeaponData)
		return;

    if (!pWeaponData->nDefinitionIndex == WEAPON_SMOKEGRENADE)
        return;

    //

    for (int i = 0; i < I::ClientEntityList->GetHighestEntityIndex(); i++) {
        IClientEntity* EntityIndex = I::ClientEntityList->GetClientEntity(i);

        if (!EntityIndex)
            return;
        
        if (EntityIndex->GetClientClass()->CBaseClient::nClassID == EClassIndex::CInferno)
            pIncendiary = (IClientEntity*)EntityIndex;
    }

    float DistancetoIncendiary = pLocal->GetOrigin().DistTo(pIncendiary->GetAbsOrigin());
    QAngle AngletoIncendiary = M::CalcAngle(pLocal->GetEyePosition(), pIncendiary->GetAbsOrigin());

    if (DistancetoIncendiary <= 120.0f) {
		pCmd->iWeaponSelect = pWeapon->GetItemDefinitionIndex();
        pCmd->angViewPoint += AngletoIncendiary;
        pCmd->iButtons |= IN_ATTACK;
		pCmd->angViewPoint -= AngletoIncendiary;
    }
*/
}

void misc::fakeping() {
    if (!Options.misc_general_fakeping)
        return;

    //Options.misc_general_fakepingamount
}

void misc::clantag() {
    if (!Options.misc_general_clantag)
        return;
}

void misc::blockbot() {
    if (!Options.misc_general_blockbot)
        return;
}

void misc::headstandbot() {
    if (!Options.misc_general_headstandbot)
        return;
};

void misc::forceregion() {
    std::string ServerLocations[] = {"", "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg", "maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp", "jnb", "mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh", "okc", "sea", "iad"} 
};

void misc::revealoverwatch() {
    if (!Options.misc_general_revealoverwatch)
        return;
};

void misc::revealranks(CUserCmd* pCmd) {
    if (!Options.misc_general_revealranks)
        return;

    if (pCmd->iButtons & IN_SCORE)
        I::Client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0U, 0, nullptr);
};

void misc::slowwalk(CUserCmd* pCmd, CBaseEntity* pLocal) {
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

    //Options.misc_general_slowwalkspeed    


    if (pCmd->iButtons() & IN_FORWARD) {

    }

    if (pCmd->iButtons() & IN_BACK) {

    }

    if (pCmd->iButtons() & IN_LEFT) {

    }

    if (pCmd->iButtons() & IN_RIGHT) {

    }
};

void misc::infiniteduck(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (!Options.misc_general_infiniteduck)
        return;

    if (!pLocal->IsAlive())
        return;

    pCmd->iButtons & IN_BULLRUSH;
}

void misc::bunnyhop(CUserCmd* pCmd, CBaseEntity* pLocal) { //Options.misc_general_bhopmiss
    if (!Options.misc_general_bhop)
        return;

    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (pLocal->GetMoveType() == MOVETYPE_LADDER)
        return;

    if (I::ConVar->FindVar("sv_autobunnyhopping"))
        return;

    //Options.misc_general_bhophitchance;
    //Options.misc_general_bhophitchancerandom;

    /*
        if (pLocal->GetFlags() & FL_ONGROUND && pCmd->iButtons & IN_JUMP)
            pCmd->iButtons &= ~IN_JUMP;
    */
}

//autostraife

void misc::aircrouch(CBaseEntity* pLocal, CUserCmd* pCmd) {
    if (Options.misc_general_aircrouch)
        return;

    if (!pLocal->IsAlive())
        return;

    if (!pLocal->GetFlags() & FL_ONGROUND)
        pCmd->iButtons &= ~IN_DUCK;
    else 
        pCmd->iButtons |= IN_DUCK;
}

void misc::peekassist(CBaseEntity* pLocal, CUserCmd* pCmd) {
    if (!Options.misc_general_peekassist)
        return;

    if (IPT::IsKeyDown(Options.misc_general_peekassistkey)) {
        ImDrawList::AddCircleFilled(ImVec2(0, 0), 10, ImColor(255, 255, 255, 255), 32);

    }

    if (IPT::IsKeyReleased(Options.misc_general_peekassistkey) || pCmd->iButtons(IN_ATTACK || IN_SECOND_ATTACK)) {

    }
}

void misc::buybot(CUserCmd* pCmd) {
    if (!Options.misc_buybot_enable)
        return;

    if (!IGameEvent->FindListener("round_start"))
        return;

    switch (Options.misc_buybot_secondary) {
        case 1: //off
            break;

        case 2: IEngineClient->ExecuteClientCmd("buy elite");
            break;

        case 3: IEngineClient->ExecuteClientCmd("buy p250");
            break;

        case 4: IEngineClient->ExecuteClientCmd("buy tec9");
            break;

        case 5: IEngineClient->ExecuteClientCmd("buy revolver");
            break;
    }

    switch (Options.misc_buybot_nades) {
        case 1: IEngineClient->ExecuteClientCmd("buy smokegrenade");
            break;

        case 2: IEngineClient->ExecuteClientCmd("buy flashbang");
            break;

        case 3: IEngineClient->ExecuteClientCmd("buy molotov");
            break;

        case 4: IEngineClient->ExecuteClientCmd("buy decoy");
            break;

        case 5: IEngineClient->ExecuteClientCmd("buy hegrenade");
            break;
    }

    switch (Options.misc_buybot_other) {
        case 1: IEngineClient->ExecuteClientCmd("buy vest");
            break;

        case 2: IEngineClient->ExecuteClientCmd("buy vesthelm");
            break;

        case 3: IEngineClient->ExecuteClientCmd("buy defuser");
            break;

        case 4: IEngineClient->ExecuteClientCmd("buy taser");
            break;
        
        case 5: IEngineClient->ExecuteClientCmd("buy riotshield");
            break;
    }
}

void misc::triggerban(CUserCmd* pCmd) { //untrusted ban goes weeeeeee
    if (!Options.misc_general_triggerban)
        return;
    
    writetolog("[Warning] Triggering untrusted ban");
    writetoconsole("[Warning] Triggering untrusted ban");

    QAngle angSentView = {999.0f, 999.0f, 999.0f};

    pCmd->angViewPoint = angSentView;
}

void misc::unlockachievements() {
    if (!Options.misc_general_unlockachievements)
        return;
}