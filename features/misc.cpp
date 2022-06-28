#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/entity.h"
#include "../options.h"
#include "misc.h"

void misc::autoaccept() {
    if (Options.misc_general_autoaccept) {
        
    }
}

void misc::autofire(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.misc_general_autopistol) {
        if (pLocal->IsAlive() == false)
            return false;

        CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();
	    const short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	    const CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

	    if (pWeapon == nullptr || pWeaponData == nullptr)
		    return false;

        if (pWeaponData->bFullAuto)
            return false;

        if (pWeaponData->nWeaponType != WEAPONTYPE_PISTOL)
            return false;

	    if (pLocal->CanShoot(static_cast<CWeaponCSBase*>(pWeapon)) && pCmd->iButtons & IN_ATTACK)
		    pCmd->iButtons |= IN_ATTACK;
	    else
		    pCmd->iButtons &= ~IN_ATTACK;
    }
    Sleep(Options.misc_general_autopistoldelay);
}

void misc::preservekillfeed() {
    if (Options.misc_general_preservekillfeed) {

    }
}

void misc::autodefuse(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.misc_general_autodefuse) {
        if (pLocal->IsAlive() == false)
            return false;

        if (pLocal->GetTeam() == TEAM_TT)
            return false;
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
    if (Options.misc_general_revealranks && pCmd->iButtons & IN_SCORE) {
        I::Client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0U, 0, nullptr);
    }
};

void misc::slowwalk(CUserCmd* pCmd) {
    if (Options.misc_general_slowwalk) {

    }
};