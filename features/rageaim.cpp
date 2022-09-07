//#include "rageaim.h"
//#include "rageantiaim.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/datatypes/usercmd.h"

void rageaim::execute() {
    if (I::Engine->IsInGame() == false)
        return false;

}

void rageaim::hitboxsetup() {
    switch () {
        case 1: EHitboxIndex->HITBOX_HEAD; //head 
            break;

        case 2: //chest
            break;

        case 3: //body
            break;

        case 4: //arms
            break;
        
        case 5: //legs
            break;
    }
    return hitboxes;
}

void rageaim::doubletap(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.rage_doubletap) {
        static bool doubletap = false;

        if (pLocal->IsAlive() == false)
            return false;

        if (pLocal->GetFlags() & FL_FROZEN)
            return false;

        if (fakeduck == true)
            return false;

        static bool doubletaprecharge = false;
        static int lastdoubletaptick = 0;

        if (doubletap == true) {
            switch (Options.rage_teleportmode) {
                case 1: //default
                    break;

                case 2: //extended
                    break;

                case 3: //disabled 138? cmd which wont simulate on serverside
                    break;
            }

            if (Options.rage_doubletapinstant) {

            }
        }
    }
}

void rageaim::hideshots(CUserCmd* pCmd) {
    if (Options.rage_hideshots) {

    }
}


void rageaim::norecoil(CUserCmd* pCmd) {
    if (Options.rage_global_norecoil) {
        if (pCmd->iButtons & IN_ATTACK) {
            
        }
        else (pCmd->iButtons & IN_SECOND_ATTACK) {

        }
        else () {

        }
    }
}

void rageaim::nospread(CUserCmd* pCmd) { //will not work 100%
    if (Options.rage_global_nospread) {

    }
}