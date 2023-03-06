#include "rageaim.h"
#include "rageantiaim.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/datatypes/usercmd.h"
#include "../options.h"

void RageAim::Execute(CUserCmd* Cmd, CBaseEntity* Local) { 
    if (!Options.rage_enable)
        return;

    /*
    OPTION(int, Options.rage_default_hitchance, 0);
    MULTIOPTION(Options.rage_default_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_default_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_default_mindmgocluded, 0);
    OPTION(int, Options.rage_default_mindmgvisible, 0);
    OPTION(int, Options.rage_default_delay, 0);
    OPTION(bool, Options.rage_default_forcebody, false);
    OPTION(bool, Options.rage_default_forcehead, false);
    OPTION(bool, Options.rage_default_forceaccuracy, false);
    OPTION(bool, Options.rage_default_inair, false);

    OPTION(int, Options.rage_pistol_hitchance, 0);
    MULTIOPTION(Options.rage_pistol_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_pistol_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_pistol_mindmgocluded, 0);
    OPTION(int, Options.rage_pistol_mindmgvisible, 0);
    OPTION(int, Options.rage_pistol_delay, 0);
    OPTION(bool, Options.rage_pistol_forcebody);
    OPTION(bool, Options.rage_pistol_forcehead);
    OPTION(bool, Options.rage_pistol_forceaccuracy);
    OPTION(bool, Options.rage_pistol_inair);
    OPTION(int, Options.rage_pistol_dmgoverride, 0);

    OPTION(int, Options.rage_awp_hitchance, 0);
    MULTIOPTION(Options.rage_awp_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_awp_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_awp_mindmgocluded, 0);
    OPTION(int, Options.rage_awp_mindmgvisible, 0);
    OPTION(int, Options.rage_awp_delay, 0);
    OPTION(bool, Options.rage_awp_forcebody);
    OPTION(bool, Options.rage_awp_forcehead);
    OPTION(bool, Options.rage_awp_forceaccuracy);
    OPTION(bool, Options.rage_awp_inair);
    OPTION(int, Options.rage_awp_dmgoverride, 0);

    OPTION(int, Options.rage_scout_hitchance, 0);
    MULTIOPTION(Options.rage_scout_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_scout_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_scout_mindmgocluded, 0);
    OPTION(int, Options.rage_scout_mindmgvisible, 0);
    OPTION(int, Options.rage_scout_delay, 0);
    OPTION(bool, Options.rage_scout_forcebody, false);
    OPTION(bool, Options.rage_scout_forcehead, false);
    OPTION(bool, Options.rage_scout_forceaccuracy, false);
    OPTION(bool, Options.rage_scout_inair, false);
    OPTION(int, Options.rage_scout_dmgoverride, 0);

    OPTION(int, Options.rage_auto_hitchance, 0);
    MULTIOPTION(Options.rage_auto_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_auto_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_auto_mindmgocluded, 0);
    OPTION(int, Options.rage_auto_mindmgvisible, 0);
    OPTION(int, Options.rage_auto_delay, 0);
    OPTION(bool, Options.rage_auto_forcebody, false);
    OPTION(bool, Options.rage_auto_forcehead, false);
    OPTION(bool, Options.rage_auto_forceaccuracy, false);
    OPTION(bool, Options.rage_auto_inair, false);
    OPTION(int, Options.rage_auto_dmgoverride, 0);
*/

    switch (WeaponConfig) {
        case DEFAULT:
            
            break;

        case PISTOL:

            break;

        case AWP:

            break;

        case SCOUT:

            break;

        case AUTO:

            break;
    }

    /*
    Options.rage_fov
    Options.rage_silentaim
    Options.rage_autofire
    Options.rage_autoscope 
    Options.rage_autostop
    Options.rage_resolver <- call from resolver.h
    Options.rage_resolverx
    Options.rage_resolverz
    Options.rage_bruteforce
    Options.rage_noscope
    Options.rage_damageoverride
    */
}

void RageAim::Penetration() {
    if (!Options.rage_penetration)
        return;
}

void RageAim::KnifeBot() {
    if (!Options.rage_knifebot)
        return;
}

void RageAim::ZuesBot() {
    if (!Options.rage_zeusbot)
        return;
}

void RageAim::BackTrack() {
    if (!Options.rage_backtrack)
        return;
}

void RageAim::HideShots() {
    if (!Options.rage_hideshots)
        return;
}

void RageAim::DoubleTap(CUserCmd* Cmd, CBaseEntity* Local) {
    if (!Options.rage_doubletap)
        return;

    if (Options.rage_doubletapinstant) {

    }

    switch (Options.rage_teleportmode) {
        case NORMAL:

            break;

        case EXTENDED:

            break;

        case DISABLED:

            break;
    }
}


void RageAim::NoRecoil() {
    if (!Options.rage_global_norecoil)
        return;
}

void RageAim::NoSpread() {
    if (!Options.rage_global_nospread)
        return;
}

void RageAim::RevolverPrep() {
    if (!Options.rage_revolverprep)
        return;

    if ()
}

void RageAim::SpasmLock() {
    if (!Options.rage_spasmlock)
        return;
}