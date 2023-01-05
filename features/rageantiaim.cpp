#include "../resources/sdk/interfaces/iengineclient.h"
#include "../resources/sdk/interfaces/ienginetrace.h"
#include "../resources/sdk/interfaces/iglobalvars.h"
#include "../resources/sdk/interfaces/inetchannel.h"
#include "../resources/sdk/interfaces/icliententitylist.h"
#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/datatypes/qangle.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/interfaces.h"
#include "../resources/utils/utils.h"
#include "../resources/utils/math.h"
#include "../resources/utils/inputsystem.h"
#include "../options.h"
#include "../global.h"
#include "rageantiaim.h"
#include "rageaim.h"

void antiaim::execute(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket) {
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

    if (!pWeapon)
        return;

    int nDefinitionIndex = pWeapon->GetItemDefinitionIndex();
    CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(nDefinitionIndex);

    if (!pWeaponData)
		return;

    float flServerTime = ; //TODO (Prediction system)

    if (pWeaponData->IsGun() && pLocal->CanShoot(static_cast<CWeaponCSBase*>(pWeapon)) && pCmd->iButtons & IN_ATTACK)
        return;

    else if (pWeaponData->nDefinitionIndex == WEAPON_REVOLVER) {
        if (pCmd->iButtons & IN_ATTACK && pWeapon->GetNextPrimaryAttack() <= flServerTime)
            return;

        if (pCmd->iButtons & IN_SECOND_ATTACK)
            return;
    }

    else if (pWeaponData->nWeaponType == WEAPONTYPE_KNIFE) {
        if (pCmd->iButtons & IN_ATTACK && pWeapon->GetNextPrimaryAttack() <= flServerTime)
            return;

        if (pCmd->iButtons & IN_SECOND_ATTACK && pWeapon->GetNextSecondaryAttack() <= flServerTime)
            return;
    }

    else if (pWeaponData->nWeaponType == WEAPONTYPE_GRENADE) {
        CBaseCSGrenade* pGrenade = static_cast<CBaseCSGrenade*>(pWeapon);

        if (pGrenade == nullptr)
            return;

        if (pGrenade->IsPinPulled() && pCmd->iButtons & (IN_ATTACK | IN_SECOND_ATTACK)) {
            if (pGrenade->GetThrowTime() > 0.0f)
				return;
        }   
    }

    angSentView = pCmd->angViewPoint;

    targetdetection();
    walldetection();
    desync();
    xaxis();
    yaxis();

    if (Options.misc_general_antiuntrusted) {
        angSentView.Normalize();
        angSentView.Clamp();
    }

    pCmd->angViewPoint = angSentView;
}

int rageantiaim::xaxis(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (!Options.antiaim_rage_xenable)
        return;

    switch (Options.antiaim_rage_xanglemode) {
        case 1: angSentView.x = Options.antiaim_rage_xbaseangle; //static
            break;
    
        case 2: angSentView.x = M::RandomIntSet(90, 0, -90); //UDZ random
            break;

        case 3: angSentView.x = M::IntAddSubtractRange(90, -90, -90, 90, 1); //fluctuate
            break;
    }

    if (!Options.antiaim_rage_xjitter_enable)
        return;

    switch (Options.antiaim_rage_xjittermode) {
        case 1: angSentView.x = M::RandomIntSet(Options.antiaim_rage_xjitterrangemin, Options.antiaim_rage_xjitterrangemax) //offset
            break;

        case 2: angSentView.x = M::RandomIntRange(Options.antiaim_rage_xjitterrangemin, Options.antiaim_rage_xjitterrangemax) //random
            break;
    }
}

int rageantiaim::yaxis(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (!Options.antiaim_rage_yenable)
        return;

    switch (Options.antiaim_rage_yanglemode) {
        case 1: angSentView.y = Options.antiaim_rage_ybaseangle; //static 
            break;
        
        case 2: angSentView.y = M::IntAddRange(0, 360, 1); //spin
            break;

        case 3: angSentView.y = M::RandomIntSet(0, -90, 180, 90); //WASD random
            break;
    }

    if (!Options.antiaim_rage_yjitter_enable)
        return;

    switch (Options.antiaim_rage_yjittermode) {
        case 1: angSentView.y = M::RandomIntSet(Options.antiaim_rage_yjitterrangemin, Options.antiaim_rage_yjitterrangemax); //offset
            break;

        case 2: angSentView.y = M::RandomIntRange(Options.antiaim_rage_yjitterrangemin, Options.antiaim_rage_yjitterrangemax); //random
            break;
    }
}

int rageantiaim::desync(CUserCmd* pCmd, CBaseEntity* pLocal, float flServerTime, bool& bSendPacket) { 
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


}

int rageantiaim::freestand(CUserCmd* pCmd, CBaseEntity* pLocal) {

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

void rageantiaim::fakelag(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket) {
    if (!Options.antiaim_rage_fakelagenable)
        return;

    if (IGameEvent->FindListener("round_start"))
        return;

    if (Global::doubletap)
        return;

    if (Global::hideshots)
        return;

    if (Global::fakeduck)
        return;

    if (Global::teleport)
        return;

    if (Options.antiaim_rage_fakelagdormant) {
        for (int i = 0; i < I::ClientEntityList->GetMaxEntities(); i++) {
            CBaseEntity* pEntity = static_cast<int>(IClientEntityList->GetClientEntity(i));

            if (!pEntity->IsEnemy())
                return;
        }
    }

    int maxchokedticks = Options.antiaim_rage_fakelagrangemin;

    switch (Options.antiaim_rage_maxfakelagtriggers) {
        case ON_STANDING: 
                if (pLocal->GetVelocity() < 0.1f)
                    maxchokedticks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ON_MOVING: 
                if (pLocal->GetVelocity() > 0.1f)
                    maxchokedticks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ON_INAIR: 
                if (!pLocal->GetFlags & FL_ONGROUND)
                    maxchokedticks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ON_SHOT: 
                if (pCmd->iButtons & IN_ATTACK || pCmd->iButtons & IN_SECOND_ATTACK)
                    maxchokedticks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ON_PEEK:
                
            break;
        
        case ON_DAMAGE: 
                if (pLocal->GetTakeDamage())
                    maxchokedticks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ON_RELOAD: 
                if (pCmd->iButtons & IN_RELOAD)
                    maxchokedticks = Options.antiaim_rage_fakelagrangemax;
            break;

        default:
            break;
    }

    if (I::ClientState->nChokedCommands > maxchokedticks)
        bSendPacket = true;
    else
        bSendPacket = false;
}

void rageantiaim::targetdetection(CUserCmd* pCmd, CBaseEntity* pEntity) {
    if (!Options.antiaim_rage_targetdetection)
        return;


/*
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
*/
}

void rageantiaim::walldetection(CBaseEntity* pLocal) {
    if (!Options.antiaim_rage_walldetection)
        return;
}

void rageantiaim::slidewalk(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (!Options.antiaim_rage_slidewalk)
        return;

    if (!pLocal->IsAlive())
        return;

    if (pLocal->GetMoveType() == MOVETYPE_LADDER)
        return;

    pCmd->iButtons ^= IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT;
}

void rageantiaim::fakeduck(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (!Options.antiaim_rage_fakeduck)
        return;

    if (!pLocal->IsAlive())
        return;
        
    if (IPT::IsKeyDown(Options.antiaim_rage_fakeduckkey)) {
        pCmd->iButtons |= IN_BULLRUSH;

        if (INetChannel->iChokedPackets <= 7)
            pCmd->iButtons &= ~IN_DUCK;
        else 
            pCmd->iButtons |= IN_DUCK;
    }
};

void rageantiaim::teleport(CUserCmd* pCmd) {
    if (!Options.antiaim_rage_teleport)
        return;

    if (IPT::IsKeyDown(Options.antiaim_rage_teleportkey)) {
        ImDrawList::AddCircleFilled(ImVec2(0, 0), 10, ImColor(255, 255, 255, 255), 32);

        if (I::ClientState->nChokedCommands == 0)
            Global::bSendPacket == false;
    }

    if (IPT::IsKeyReleased(Options.antiaim_rage_teleportkey) || I::ClientState->nChokedCommands == 14) {
        if (pCmd->iButtons & IN_FORWARD)
            pCmd->iButtons |= IN_BACK;

        if (pCmd->iButtons & IN_LEFT)
            pCmd->iButtons |= IN_RIGHT;

        if (pCmd->iButtons & IN_RIGHT)
            pCmd->iButtons |= IN_LEFT;

        if (pCmd->iButtons & IN_BACK)
            pCmd->iButtons |= IN_FORWARD;

        Global::bSendPacket == true;
    }
}

void rageantiaim::psuedocrimwalk() { //essentially dt on/off | charge and release
    if (!Options.antiaim_rage_crimwalk)
        return;
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

void rageantiaim::antibackstab(CBaseEntity* pLocal) {
    if (!Options.antiaim_rage_antibackstab)
        return;
}