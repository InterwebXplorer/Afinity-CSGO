#include "rageaim.h"

void rageaim::execute() {
    if (I::Engine->IsInGame() == false)
        return false;

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

//no spread attempt will not work 100% of the time