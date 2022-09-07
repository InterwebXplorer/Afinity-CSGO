#include <Windows.h>
#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/entity.h"
#include "../options.h"
#include "misc.h"

void misc::autoaccept(const char* sEntry) {
    if (Options.misc_general_autoaccept) {
        
    }
}

void misc::autopistol(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.misc_general_autopistol) {
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

        if (pWeaponData->nWeaponType != WEAPONTYPE_PISTOL)
            return;

	    if (pLocal->CanShoot(static_cast<CWeaponCSBase*>(pWeapon)) && pCmd->iButtons & IN_ATTACK)
		    pCmd->iButtons |= IN_ATTACK;
	    else
		    pCmd->iButtons &= ~IN_ATTACK;
    }
    Sleep(1000 - Options.misc_general_autopistoldelay * 10);
}

void misc::preservekillfeed() {
    if (Options.misc_general_preservekillfeed) {

    }
}

void misc::autodefuse(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.misc_general_autodefuse) {
        if (pLocal->IsAlive() == false)
            return;

        if (pLocal->GetTeam() == TEAM_TT)
            return;

        
    }
}

void misc::autosmoke() {
    if (Options.misc_general_autosmoke) {

    }
}

void misc::clantag() {
    if (Options.misc_general_clantag) {

    }
}

void misc::blockbot() {
    if (Options.misc_general_blockbot) {

    }
}

void misc::headstandbot() {
    if (Options.misc_general_headstandbot) {

    }
};

void misc::forceregion() {

};

void misc::revealoverwatch() {
    if (Options.misc_general_revealoverwatch) {

    }
};

void misc::revealranks(CUserCmd* pCmd) {
    if (Options.misc_general_revealranks && pCmd->iButtons & IN_SCORE)
        I::Client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0U, 0, nullptr);
};

void misc::slowwalk(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.misc_general_slowwalk) {
        if (pLocal->IsAlive() == false)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_LADDER)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_OBSERVER)
            return false;
        
        //add keypress shit

        if (pCmd->iButtons & IN_MOVELEFT)
            //execute shit here no need for {}

        if (pCmd->iButtons & IN_MOVERIGHT)

        if (pCmd->iButtons & IN_FORWARD)

        if (pCmd->iButtons & IN_BACK)
    }
};

//anti untrusted

//bypass sv pure

void misc::infiniteduck(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.misc_general_infiniteduck)
        pCmd->iButtons |= IN_BULLRUSH;
}

void misc::bunnyhop() { //Options.misc_general_bhopmiss
    if (Options.misc_general_bhop) {
        int hitchance = Options.misc_general_bhophitchance;
        bool random = Options.misc_general_bhophitchancerandom;

        if (pLocal->IsAlive() == false)
            return false;

        static CConVar* sv_autobunnyhopping = I::ConVar->FindVar(XorStr("sv_autobunnyhopping"));

        if (sv_autobunnyhopping->GetBool() == true)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_LADDER)
            return false;

        if (pLocal->GetFlags() & FL_ONGROUND && pCmd->iButtons & IN_JUMP)
            pCmd->iButtons &= ~IN_JUMP;
    }
}

//autostraife

void misc::aircrouch() {
    if (Options.misc_general_aircrouch) {
        if (pLocal->IsAlive() == false)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
            return false;

        if (pLocal->GetMoveType() == MOVETYPE_LADDER)
            return false;
    }
}