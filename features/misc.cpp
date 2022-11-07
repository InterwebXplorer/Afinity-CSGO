#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/entity.h"
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

    if (pWeapon == nullptr)
        return;
        
	const short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	const CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

	if (pWeaponData == nullptr)
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

////DONE ^^^^

void misc::preservekillfeed() {
    if (!Options.misc_general_preservekillfeed)
        return;
    
}

void misc::autodefuse(CUserCmd* pCmd, CPlantedC4* pBomb, CBaseEntity* pLocal) {
    if (!Options.misc_general_autodefuse)
        return;
        
    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetTeam() == TEAM_TT)
        return;



    if (distance <= 75.0f)
        pCmd->iButtons |= IN_USE
}

void misc::autosmoke() {
    if (!Options.misc_general_autosmoke)
        return;

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



    /*
        int hitchance = Options.misc_general_bhophitchance;
        bool random = Options.misc_general_bhophitchancerandom;

        static CConVar* sv_autobunnyhopping = I::ConVar->FindVar(XorStr("sv_autobunnyhopping"));

        if (sv_autobunnyhopping->GetBool() == true)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_LADDER)
            return false;

        if (pLocal->GetFlags() & FL_ONGROUND && pCmd->iButtons & IN_JUMP)
            pCmd->iButtons &= ~IN_JUMP;
    */
}

//autostraife

void misc::aircrouch() {
    if (Options.misc_general_aircrouch)
        return;
}

void misc::peekassist() {
    if (!Options.misc_general_peekassist)
        return;
}

void misc::buybot() {
    const char* buybotprimary[] = {"Off", "Auto", "Scout", "AWP", "Ak/M4"};
    const char* buybotsecondary[] = {"Off", "Dual-Berettas", "P250", "Five7/Tec9", "Deagle/R8"};
    const char* buybotnades[] = {"Smoke", "Flash", "Molotov", "Decoy", "HE Grenade"};
    const char* buybotother[] = {"Kevlar", "Helmet", "Defuser", "Taser", "Riot Sheild"};
    const char* buybotpriority[] = {"Off", "Primary", "Secondary", "Nades", "Other"};

    if (!Options.misc_buybot_enable)
        return;

    switch (Options.misc_buybot_primary) {
        case 1: primary
    }

    switch (Options.misc_buybot_secondary) {
        case 1: secondary
    }

    switch (Options.misc_buybot_nades) {
        case 1: nades
    }

    switch (Options.misc_buybot_other) {

    }
}