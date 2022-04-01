#include "../features/rageantiaim.h"
#include "../options.h"
#include "../resources/sdk/interfaces/iengineclient.h"
#include "../resources/sdk/interfaces/ienginetrace.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/interfaces/icliententitylist.h"
#include "../resources/sdk/interfaces/inetchannel.h"
#include "../resources/sdk/datatypes/usercmd.h"
#include "../resources/sdk/interfaces/iglobalvars.h"

static bool antiaim::disable(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket) {
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
};

void antiaim::xaxis(CUserCmd* pCmd, CBaseEntity* pLocal) {
    if (Options.antiaim_rage_xbase_angle.get())


};

void antiaim::yaxis(CUserCmd* pCmd, CBaseEntity* pLocal) {

};

void antiaim::desync(CUserCmd* pCmd, CBaseEntity* pLocal, float flServerTime, bool& bSendPacket) {

};

void antiaim::fakelag() {

};

void antiaim::other() {

};

//if invert desync invert spin