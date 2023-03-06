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

void RageAntiAim::Execute(CUserCmd* Cmd, CBaseEntity* LocalPlayer, bool& SendPacket) {
    if (!LocalPlayer->IsAlive())
        return;

    if (LocalPlayer->GetFlags() & FL_FROZEN) 
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    if (Cmd->iButtons & IN_USE)
        return;

    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

    if (!ActiveWeapon)
        return;

    const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
    CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

    if (!ActiveWeaponData)
		return;

    float ServerTime = ; //TODO (Prediction system)

    if (ActiveWeaponData->IsGun() && LocalPlayer->CanShoot(static_cast<CWeaponCSBase*>(ActiveWeapon)) && Cmd->iButtons & IN_ATTACK)
        return;

    else if (ActiveWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER) {
        if (Cmd->iButtons & IN_ATTACK && ActiveWeapon->GetNextPrimaryAttack() <= ServerTime)
            return;

        if (Cmd->iButtons & IN_SECOND_ATTACK)
            return;
    }

    else if (ActiveWeaponData->nWeaponType == WEAPONTYPE_KNIFE) {
        if (Cmd->iButtons & IN_ATTACK && ActiveWeapon->GetNextPrimaryAttack() <= ServerTime)
            return;

        if (Cmd->iButtons & IN_SECOND_ATTACK && ActiveWeapon->GetNextSecondaryAttack() <= ServerTime)
            return;
    }

    else if (ActiveWeaponData->nWeaponType == WEAPONTYPE_GRENADE) {
        CBaseCSGrenade* Grenade = static_cast<CBaseCSGrenade*>(ActiveWeapon);

        if (Grenade == nullptr)
            return;

        if (Grenade->IsPinPulled() && Cmd->iButtons & (IN_ATTACK | IN_SECOND_ATTACK)) {
            if (Grenade->GetThrowTime() => 0.0f)
				return;
        }
    }

    QAngle OriginalViewAngles = Cmd->angViewPoint;
    
    struct ViewAngles {
        int x;
        int y;
        int z;
    };

    ViewAngles ViewAngleInts;
        
    ViewAngleInts.x = static_cast<int>(OriginalViewAngles.x);
    ViewAngleInts.y = static_cast<int>(OriginalViewAngles.y);
    ViewAngleInts.z = static_cast<int>(OriginalViewAngles.z);

    TargetDetection();
    WallDetection();
    Desync();
    XAxis();
    YAxis();
    FakeDuck();
    
    QAngle ModifiedViewAngles(static_cast<float>(ViewAngleInts.x), static_cast<float>(ViewAngleInts.y), static_cast<float>(ViewAngleInts.z));

    if (Options.misc_general_antiuntrusted) {
        ModifiedViewAngles.Normalize();
        ModifiedViewAngles.Clamp();
    }

    Cmd->angViewPoint = ModifiedViewAngles;
}

void RageAntiAim::XAxis() {
    if (!Options.antiaim_rage_xenable)
        return;

    switch (Options.antiaim_rage_xanglemode) {
        case STATIC: 
            ViewAngleInts.x = Options.antiaim_rage_xbaseangle;
            break;
    
        case UDZRANDOM: 
            ViewAngleInts.x = Math::RandomIntSet(90, 0, -90);
            break;

        case FLUCTUATE: 
            ViewAngleInts.x = Math::IntAddSubtractRange(90, -90, -90, 90, 1);
            break;
    }

    if (!Options.antiaim_rage_xjitter_enable)
        return;

    switch (Options.antiaim_rage_xjittermode) {
        case OFFSET: 
            static bool Flip = false;
            ViewAngleInts.x = Flip ? Options.antiaim_rage_xjitterrangemin : Options.antiaim_rage_xjitterrangemax;
            Flip = !Flip;
            break;

        case RANDOM: 
            ViewAngleInts.x = Math::RandomIntRange(Options.antiaim_rage_xjitterrangemin, Options.antiaim_rage_xjitterrangemax);
            break;
    }
}

void RageAntiAim::YAxis() {
    if (!Options.antiaim_rage_yenable)
        return;

    switch (Options.antiaim_rage_yanglemode) {
        case STATIC: 
            ViewAngleInts.y = Options.antiaim_rage_ybaseangle;
            break;
        
        case SPIN: 
            ViewAngleInts.y = Math::IntAddRange(0, 360, 1);
            break;

        case WASDRANDOM: 
            ViewAngleInts.y = Math::RandomIntSet(0, -90, 180, 90);
            break;
    }

    if (!Options.antiaim_rage_yjitter_enable)
        return;

    switch (Options.antiaim_rage_yjittermode) {
        case OFFSET: 
            static bool Flip = false;
            ViewAngleInts.y = Flip ? Options.antiaim_rage_yjitterrangemin : Options.antiaim_rage_yjitterrangemax;
            Flip = !Flip;
            break;

        case RANDOM: 
            ViewAngleInts.y = Math::RandomIntRange(Options.antiaim_rage_yjitterrangemin, Options.antiaim_rage_yjitterrangemax);
            break;
    }
}

void RageAntiAim::Desync(CBaseEntity* LocalPlayer, float ServerTime, bool& SendPacket) { //TODO
    if (!Options.antiaim_rage_desyncenable)
        return;

    static int DesyncSide = 0;

    switch (Options.antiaim_rage_desyncside) {
        case OFF: 
            DesyncSide = 0;
            break;

        case LEFT: 
            DesyncSide = Options.antiaim_rage_desyncrangeleft;
            break;

        case RIGHT: 
            DesyncSide = Options.antiaim_rage_desyncrangeright;
            break;

        case RANDOM:
            static bool Flip = false;
            DesyncSide = Flip ? Options.antiaim_rage_desyncrangeleft : Options.antiaim_rage_desyncrangeright;
            Flip = !Flip;
            break;
    }



}

int RageAntiAim::freestand(CUserCmd* Cmd, CBaseEntity* LocalPlayer) { //TODO
    switch (Options.antiaim_rage_desyncfreestand) {
        case OFF:
            break;

        case FREESTAND:

            break;

        case ANTIFREESTAND:

            break;
    }
}

void RageAntiAim::fakelag(CUserCmd* Cmd, CBaseEntity* LocalPlayer) {
    if (!Options.antiaim_rage_fakelagenable)
        return;

    if (IGameEvent->FindListener("round_start"))
        return;

    if (Global::DoubleTap)
        return;

    if (Global::HideShots)
        return;

    if (Global::FakeDuck)
        return;

    if (Options.antiaim_rage_fakelagdormant) { //todo
        for (int i = 0; i < I::ClientEntityList->nMaxClients(); i++) {
            CBaseEntity* Entity = I::ClientEntityList->Get<CBaseEntity>(i);

            if (!Entity->IsPlayer())
                continue;

            if (!Entity->IsEnemy())
                continue;

            if (!Entity->IsAlive())
                continue;
            else
                break;
        }
    }

    int MaxChokedTicks = Options.antiaim_rage_fakelagrangemin;

    switch (Options.antiaim_rage_maxfakelagtriggers) {
        case STANDING: 
            if (LocalPlayer->GetVelocity() = 0.0f)
                MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;

        case MOVING: 
            if (LocalPlayer->GetVelocity() > 0.0f)
                MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;

        case INAIR: 
                if (!LocalPlayer->GetFlags & FL_ONGROUND)
                    MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ONSHOT: 
            if (Cmd->iButtons & IN_ATTACK || Cmd->iButtons & IN_SECOND_ATTACK)
                MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ONPEEK:
            CBaseEntity* TargetEntity = nullptr;

            for (int i = 0; i < I::Globals->nMaxClients()) {
                CBaseEntity* Entity = I::ClientEntityList->Get<CBaseEntity>(i);

                if (!Entity)
                    continue;

                if (!Entity->IsPlayer())
                    continue;

                if (!Entity->IsEnemy())
                    continue;
                else
                    TargetEntity = Entity;
                    break;
            }

            if (LocalPlayer->IsVisible(TargetEntity, TargetEntity->GetBonePosition(BONE_HEAD).value_or(TargetEntity->GetEyePosition(false)), false))
                MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;
        
        case ONDAMAGE: 
            if (LocalPlayer->GetTakeDamage())
                MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;

        case ONRELOAD: 
            if (Cmd->iButtons & IN_RELOAD)
                MaxChokedTicks = Options.antiaim_rage_fakelagrangemax;
            break;
    }

    if (I::ClientState->nChokedCommands >= MaxChokedTicks)
        Global::SendPacket = true;
    else
        Global::SendPacket = false;
}

void RageAntiAim::targetdetection(CUserCmd* Cmd, CBaseEntity* pEntity) {
    if (!Options.antiaim_rage_targetdetection)
        return;

/*
    if (!Options.antiaim_rage_targetdetection)
        return;

    Vector LocalAngle = pEntity->GetEyePosition();

    IClientEntity* pTarget = nullptr;

    if (pTarget == nullptr)
        return;

    for (int i = 0; i < I::ClientEntityList->nMaxClients(); i++) {
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
            CalcAngle(LocalAngle, TargetAngle, Cmd->angViewPoint);
        }
    }
*/

}

void RageAntiAim::walldetection(CBaseEntity* LocalPlayer) {
    if (!Options.antiaim_rage_walldetection)
        return;

    //traceray 8 rays around player check if they hit a wall
}

void RageAntiAim::slidewalk(CUserCmd* Cmd, CBaseEntity* LocalPlayer) {
    if (!Options.antiaim_rage_slidewalk)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    if (LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
        return;

    Cmd->iButtons ^= IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT;
}

void RageAntiAim::FakeDuck(CUserCmd* Cmd, CBaseEntity* LocalPlayer) {
    if (!Options.antiaim_rage_fakeduck)
        return;

    Global::FakeDuck = true;

    if (!LocalPlayer->IsAlive())
        return;
    
    if (!Options.misc_general_infiniteduck)
        Cmd->iButtons |= IN_BULLRUSH;

    if (I::ClientState->nChokedCommands <= 7)
        Cmd->iButtons &= ~IN_DUCK;
    else 
        Cmd->iButtons |= IN_DUCK;
}

void RageAntiAim::psuedocrimwalk() { //essentially dt on/off | charge and release
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

void RageAntiAim::antibackstab(CBaseEntity* LocalPlayer) {
    if (!Options.antiaim_rage_antibackstab)
        return;
}