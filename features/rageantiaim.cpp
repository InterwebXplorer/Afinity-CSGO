//#include "rageantiaim.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/datatypes/usercmd.h"
#include "../options.h"

/*
#include "../features/rageantiaim.h"
#include "../resources/sdk/interfaces/iengineclient.h"
#include "../resources/sdk/interfaces/ienginetrace.h"
#include "../resources/sdk/interfaces/iglobalvars.h"
#include "../resources/sdk/interfaces/inetchannel.h"
#include "../resources/sdk/interfaces/icliententitylist.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/utils/utils.h"
#include "../options.h"
*/

void antiaim::excecute(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket) {
    if (pLocal->IsAlive() == false)
        return false;

    if (pLocal->GetFlags() & FL_FROZEN)
        return false;

    if (pLocal->GetMoveType() == MOVETYPE_LADDER)
        return false;

    if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
        return false;

    if (pCmd->iButtons & IN_USE)
        return false;

    CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

    short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

    if (pWeapon == nullptr || pWeaponData == nullptr)
		return false;

    float flServerTime = ;//TODO

    if (pWeaponData->IsGun() && pLocal->CanShoot(static_cast<CWeaponCSBase*>(pWeapon)) && pCmd->iButtons & IN_ATTACK)
        return false;

    else if (pWeaponData->nDefinitionIndex == WEAPON_REVOLVER && pCmd->iButtons & IN_SECOND_ATTACK)
        return false;

    else if (pWeaponData->nWeaponType == WEAPONTYPE_KNIFE) {
        if (pCmd->iButtons & IN_ATTACK && pWeapon->GetNextPrimaryAttack() <= flServerTime)
            return false;

        if (pCmd->iButtons & IN_SECOND_ATTACK && pWeapon->GetNextSecondaryAttack() <= flServerTime)
            return false;
    }

    else if (pWeaponData->nWeaponType == WEAPONTYPE_GRENADE) {
        auto pGrenade = static_cast<CBaseCSGrenade*>(pWeapon);

        if (pGrenade == nullptr)
            return false;

        if (pGrenade->IsPinPulled() && pCmd->iButtons & (IN_ATTACK | IN_SECOND_ATTACK)) {
            if (pGrenade->GetThrowTime() > 0.f)
				return false;
        }   
    }

    //////execute functions here//////

    if (Options.misc_general_antiuntrusted) {
        
    }
}

/*
	 \     90|450    /
 	   \     |     /
 	135  \   |   /  45,405
 	       \ | /
 	-180,180 | 0,360,720
 	--------------------
 	       / | \
-135,225 /   |   \ -45,315
 	   /     |     \
 	 /    -90|270   \
*/ 

void antiaim::xaxis() {
    if (Options.antiaim_rage_xenable) {
        x_base_angle = Options.antiaim_rage_xbaseangle;

        switch (Options.antiaim_rage_xanglemode) {
            case 1: x_angle = x_base_angle;
                break;

            case 2: x_angle = //UDZ randow
                break;

            case 3: x_angle = for (int i = -89.0f )                //Fluctuate
                break;
        }

        if (Options.antiaim_rage_xjitter_enable) {
            x_jitter_range = Options.antiaim_rage_xjitterrange;
            x_jitter_speed = Options.antiaim_rage_xjitterspeed;

            switch (Options.antiaim_rage_xjittermode) { //ignore max/min values in math range floats only read set min/max values
                case 1: x_jitter_angle = //Offset //-89.0f, -45.0f, 45.0f, 89.0f (min value, set min value, set max value, max value) snapping between min and max set value 
                    break;

                case 2: x_jitter_angle = //Random //-89.0f, -45.0f, 45.0f, 89.0f (min value, set min value, set max value, max value) rng between min and max set value
                    break;
            }
        }

        /* Untrusted angles
        switch (Options.antiaim_range_x_untrusted) {
            case 1: x_fake_angle = -540.0f; //Fake up

            case 2: x_fake_angle = 540; //Fake down PATCHED?
        }
        */
    }
}

void antiaim::yaxis(CBaseEntity* pLocal) {
    if (Options.antiaim_rage_yenable) {
        y_base_angle   = Options.antiaim_rage_ybaseangle;
        y_angle_speed  = Options.antiaim_rage_yanglespeed;

        switch (Options.antiaim_rage_yanglemode) {
            case 1: y_angle = y_base_angle;
                break;

            case 2: y_angle = y_base_angle + 1.0f; Sleep(1000 - y_angle_speed * 10); 
                break;

            case 3: y_angle = //rotate 
                break;

        if (Options.antiaim_rage_yjitter_enable) {
            y_jitter_range = Options.antiaim_rage_yjitterrange;
            y_jitter_speed = Options.antiaim_rage_yjitterspeed;

            switch (Options.antiaim_rage_yjittermode) {
                case 1: y_jitter_angle = //offset
                    break;

                case 2: y_jitter_angle = //random
                    break;

                case 3: y_jitter_angle = //wasd random
                    break;
            }
        }
    }
}

//////Z AXIS HERE//////

void antiaim::desync() {
    float getmaxdesyncdelta() {

    }

    if (Options.antiaim_rage_desyncenable) {
        desync_range   = Options.antiaim_rage_desyncrange;
        desync_overlap = Options.antiaim_rage_desyncavoidoverlap;
        desync_dormant = Options.antiaim_rage_desyncdormant;

        switch (Options.antiaim_rage_desyncside) {
            case 1: y_desync_side = 0.0f; 
                break;

            case 2: y_desync_side = -90.0f; 
                break;

            case 3: y_desync_side = +90.0f; 
                break;

            case 4: y_desync_side = //random
                break;
        }

        switch (Options.antiaim_rage_desyncfreestand) {
            case 1:
                break;

            case 2: y_freestand = //freestand
                break;

            case 3: y_freestand = //antifreestand
                break;
        }
    }

}

void antiaim::fakelag() {
    if (Options.antiaim_rage_fakelagenable) {
        fakelag_range   = Options.antiaim_rage_fakelagrange;
        
        switch (Options.antiaim_rage_fakelagtriggers) {
            case 1: //standing

            case 2: //moving

            case 3: //in air

            case 4: //on shot

            case 5: //on peek //Traceray crap will need to be used

            case 6: //on damage

            case 7: //reloading
        }

        if (Options.antiaim_rage_fakelagdormant) {

        }
    }

}

void antiaim::targetdetection() {
    if (Options.antiaim_rage_targetdetection) {

    }
}

void antiaim::walldetection() { //edge antiaim in other cheats
    if (Options.antiaim_rage_walldetection) {

    }
}

void antiaim::slidewalk() {
    switch (Options.antiaim_rage_slidewalk) {
        case 1: pCmd->iButtons ^= IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT; //default
            break;

        case 2: //backwards
            break;
    }
};

void antiaim::fakeduck(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.antiaim_rage_fakeduck) {
        if (pLocal->IsAlive() == false)
            return false;

        pCmd->iButtons |= IN_BULLRUSH;

        if (INetChannel->iChokedPackets <= 7)
            pCmd->iButtons &= ~IN_DUCK;
        else 
            pCmd->iButtons |= IN_DUCK;
    }
};

void antiaim::teleport() { //essentially dt teleport
    if (Options.antiaim_rage_teleport) {
        damage_teleport = Options.antiaim_rage_damageteleport;
        shot_teleport   = Options.antiaim_rage_shotteleport;

    }
}

void antiaim::psuedocrimwalk() { //essentially dt on/off | charge and release
    if (Options.antiaim_rage_crimwalk) {

    }
}

void antiaim::antibackstab(CBaseEntity* pLocal) { //only enemy backstabbing avoided //INCOMPLETE RECODE NEEDED
    if (Options.antiaim_rage_antibackstab) {
        for (int i = 1; i <= I::Globals->nMaxClients; i++) {
            CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(i);

            if (pEntity == nullptr)
                continue;
            
            if (pEntity->IsPlayer())
                continue;

            if (pEntity->IsAlive())
                continue;

            if (pEntity->IsEnemy()) 
                continue;

            if (pEntity->IsDormant())
                continue;
            
            CBaseCombatWeapon* pActiveWeapon = pEntity->GetWeapon();

            short nDefinitionIndex = pActiveWeapon->GetItemDefinitionIndex();
	        CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

            if (pActiveWeapon == nullptr || pWeaponData == nullptr)
		        continue;

            if (pLocal->GetEyePosition().DistTo(pEntity->GetEyePosition()) <= 60.0f) {
                if (pWeaponData->nWeaponType == WEAPONTYPE_KNIFE && /*in backstab(This is going to be hard cause no var for backstab)*/) { //solution check if player is behinf and in attack?
                    y_angle = /*current angle?*/ - 180.0f;
                }
            }
        }
    }
}