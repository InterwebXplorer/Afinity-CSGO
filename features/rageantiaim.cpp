//#include "rageaim.h"
//#include "rageantiaim.h"
#include "../options.h"
#include "../resources/sdk/interfaces/iengineclient.h"
#include "../resources/sdk/interfaces/ienginetrace.h"
#include "../resources/sdk/interfaces/iglobalvars.h"
#include "../resources/sdk/interfaces/inetchannel.h"
#include "../resources/sdk/interfaces/icliententitylist.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/utils/utils.h"
#include "../resources/utils/math.h"

void rageantiaim::excecute(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket) {
    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetFlags() & FL_FROZEN)
        return;

    if (pLocal->GetMoveType() == MOVETYPE_LADDER)
        return;

    if (pLocal->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (pCmd->iButtons & IN_USE)
        return;

    CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

    if (pWeapon == nullptr)
        return;

    short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

    if (pWeaponData == nullptr)
		return;

    float flServerTime = ;//TODO

    if (pWeaponData->IsGun() && pLocal->CanShoot(static_cast<CWeaponCSBase*>(pWeapon)) && pCmd->iButtons & IN_ATTACK)
        return;

    else if (pWeaponData->nDefinitionIndex == WEAPON_REVOLVER && pCmd->iButtons & IN_SECOND_ATTACK)
        return;

    else if (pWeaponData->nWeaponType == WEAPONTYPE_KNIFE) {
        if (pCmd->iButtons & IN_ATTACK && pWeapon->GetNextPrimaryAttack() <= flServerTime)
            return;

        if (pCmd->iButtons & IN_SECOND_ATTACK && pWeapon->GetNextSecondaryAttack() <= flServerTime)
            return;
    }

    else if (pWeaponData->nWeaponType == WEAPONTYPE_GRENADE) {
        auto pGrenade = static_cast<CBaseCSGrenade*>(pWeapon);

        if (pGrenade == nullptr)
            return;

        if (pGrenade->IsPinPulled() && pCmd->iButtons & (IN_ATTACK | IN_SECOND_ATTACK)) {
            if (pGrenade->GetThrowTime() > 0.f)
				return;
        }   
    }

    xaxis();
    yaxis();


    if (Options.misc_general_antiuntrusted) {
        
    }
}

//TODO: Speed modifier

int rageantiaim::xaxis() { //jitter overrides base antiaim???
    if (!Options.antiaim_rage_xenable)
        return;

    int x_angle = viewangle.x;

    switch (Options.antiaim_rage_xanglemode) {
        case 1: x_angle = Options.antiaim_rage_xbaseangle; //static
            break;
    
        case 2: x_angle = M::RandomIntSet(90, 0, -90); //UDZ random
            break;

        case 3: x_angle = M::IntAddSubtractRange(90, -90, -90, 90, 1); //fluctuate
            break;
    }
    return x_angle;

    if (!Options.antiaim_rage_xjitter_enable)
        return;

    int x_jitter = viewangle.x;

    switch (Options.antiaim_rage_xjittermode) {
        case 1: x_jitter = M::RandomIntSet(Options.antiaim_rage_xjitterrangemin, Options.antiaim_rage_xjitterrangemax) //offset
            break;

        case 2: x_jitter = M::RandomIntRange(Options.antiaim_rage_xjitterrangemin, Options.antiaim_rage_xjitterrangemax) //random
            break;
    }
    return x_jitter;
}

int rageantiaim::yaxis() {
    if (!Options.antiaim_rage_yenable)
        return;

    int y_angle = viewangle.y;

    switch (Options.antiaim_rage_yanglemode) {
        case 1: y_angle = Options.antiaim_rage_ybaseangle; //static 
            break;
        
        case 2: y_angle = M::IntAddRange(0, 360, 1); //spin
            break;

        case 3: y_angle = M::RandomIntSet(0, -90, 180, 90); //WASD random
            break;
    }
    return y_angle;

    if (!Options.antiaim_rage_yjitter_enable)
        return;

    int y_jitter = viewangle.y;

    switch (Options.antiaim_rage_yjittermode) {
        case 1: y_jitter = M::RandomIntSet(Options.antiaim_rage_yjitterrangemin, Options.antiaim_rage_yjitterrangemax); //offset
            break;

        case 2: y_jitter = M::RandomIntRange(Options.antiaim_rage_yjitterrangemin, Options.antiaim_rage_yjitterrangemax); //random
            break;
    }
    return y_jitter;
}

/*^ done, i think....*/

int rageantiaim::desync(CUserCmd* pCmd) { 
    if (!Options.antiaim_rage_desyncenable)
        return;

    int y_desync_side = 0;

    switch (Options.antiaim_rage_desyncside) {
        case 1: y_desync_side = 0; //none
            break;

        case 2: y_desync_side = Options.antiaim_rage_desyncrangeleft; //left
            break;

        case 3: y_desync_side = Options.antiaim_rage_desyncrangeright; //right
            break;

        case 4: y_desync_side = M::RandomIntSet(Options.antiaim_rage_desyncrangeleft, Options.antiaim_rage_desyncrangeright); //random
            break;
    }
    return y_desync_side;
}

int rageantiaim::freestand(CUserCmd* pCmd) {


    for (int i = 0; i < I::ClientEntityList->GetMaxEntities(); i++) {
        int pTarget = static_cast<int>(IClientEntityList->GetClientEntity(i));
    
    
    }
}

/*
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
*/

void rageantiaim::fakelag(CUserCmd* pCmd) {
    if (!Options.antiaim_rage_fakelagenable)
        return;

    if (doubletap == true || hideshots == true)
        return;

    bool choke = false;

    switch (Options.antiaim_rage_fakelagtriggers) {
        case 1: //standing
            break;

        case 2: //moving
            break;

        case 3: //in air
            break;

        case 4: //on shot
            break;

        case 5: //on peek
            break;
        
        case 6: //on damage
            break;

        case 7: if (pCmd->iButtons & IN_RELOAD) //reloading
            break;
    }
    return choke = true;

    if (Options.antiaim_rage_fakelagdormant) {

    }
}

void rageantiaim::targetdetection(CUserCmd* pCmd, CBaseEntity* pEntity) {
    if (!Options.antiaim_rage_targetdetection)
        return;

    Vector LocalAngle = pEntity->GetEyePosition();

    IClientEntity* pTarget = nullptr;

    if (pTarget == nullptr)
        return;

    for (int i = 0; i < I::ClientEntityList->GetMaxEntities(); i++) {
        int pTarget = static_cast<int>(IClientEntityList->GetClientEntity(i));

        if (!pTarget->IsAlive())
            continue;

        if (!pTarget->IsEnemy())
            continue;

        CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)I::ClientEntityList->GetClientEntityFromHandle(pEntity->GetActiveWeaponHandle);

        if (pWeapon == nullptr)
            continue;

        short nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
	    CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

        if (pWeaponData == nullptr)
		    continue;

        float IdealDistance = pWeaponData->flRange;

        Vector TargetAngle = pTarget->GetEyePosition();
        float TargetDistance = pTarget->GetEyePosition().DistTo(TargetAngle);  

        if (TargetDistance < IdealDistance) {
            TargetDistance = IdealDistance;
            CalcAngle(LocalAngle, TargetAngle, pCmd->angViewPoint);
        }
    }
}

void rageantiaim::walldetection(CUserCmd* pCmd, CBaseEntity* pEntity) {
    if (Options.antiaim_rage_walldetection) {
        for (int i = 0; i < 360; i = +6.0f;) {
            
        }
    }
}

void rageantiaim::slidewalk() {
    switch (Options.antiaim_rage_slidewalk) {
        case 1: pCmd->iButtons ^= IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT; //default
            break;

        case 2: //backwards
            break;
    }
};

void rageantiaim::fakeduck(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.antiaim_rage_fakeduck) {
        static bool fakeduck = false;
        
        if (fakeduck == true) {
            if (pLocal->IsAlive() == false)
                return;

            pCmd->iButtons |= IN_BULLRUSH;

            if (INetChannel->iChokedPackets <= 7)
                pCmd->iButtons &= ~IN_DUCK;
            else 
                pCmd->iButtons |= IN_DUCK;
        }
    }
};

void rageantiaim::teleport() { //essentially dt teleport but with autopeek
    if (Options.antiaim_rage_teleport) {
        Vector startpos = {0, 0, 0};
        ImVec2 startposdraw = {0, 0};

        if (GetAsyncKeyState(Options.antiaim_rage_teleportkey)) {
            ImDrawList::AddCircleFilled(startposdraw, 10, ImColor(255, 255, 255, 255), 32);


            //execute teleport
        }
    }
}

void rageantiaim::psuedocrimwalk() { //essentially dt on/off | charge and release
    if (Options.antiaim_rage_crimwalk) {
        
    }
}

/* crimwalk reference
void Movement::cripwalk() {
    if (!g_input.GetKeyState(g_menu.main.movement.cripwalk.get()))
        return;

    if (g_input.GetKeyState(g_menu.main.movement.cripwalk.get())) { /// was added

        static int old_cmds = 0;

        if (old_cmds != g_cl.m_cmd->m_command_number)
            old_cmds = g_cl.m_cmd->m_command_number;

        if (g_cl.m_packet)
        {
            g_cl.m_cmd->m_tick = INT_MAX;
            g_cl.m_cmd->m_command_number = old_cmds;
        }
        if (!g_cl.m_packet)
        {
            g_cl.m_cmd->m_tick = old_cmds % 0;
            g_cl.m_cmd->m_command_number = INT_MAX;
        }
    }
}
*/

void rageantiaim::antibackstab(CBaseEntity* pLocal) { //time to recode
    if (Options.antiaim_rage_antibackstab) {
        
    }
}