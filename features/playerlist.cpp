#include "playerlist.h"
#include "../resources/sdk/interfaces.h"

void PlayerList::AddPlayer(CBaseEntity* Player) {
    if (!Player)
        return;
    
}

void PlayerList::

void PlayerList::ResetPlayerOptions(CBaseEntity* Player) {
    if (!PlayerOptions.resetoptions)
        return;

    if (!Player)
        return;

    PlayerOptions.playername = "";
    PlayerOptions.isbot = false;
    PlayerOptions.isresolved = false;
    PlayerOptions.ispriorityplayer = false;
    PlayerOptions.whitelist = false;
    PlayerOptions.set_rage =false;
    PlayerOptions.set_legit = false;
    PlayerOptions.follow = false;
    PlayerOptions.forcehitboxes = false;
    PlayerOptions.forcehead = false;
    PlayerOptions.forcebody = false;
    PlayerOptions.dontresolve = false;
    //--------------------------------//
    PlayerOptions.resetoptions = false;
}

void PlayerList::GetPlayers() {

} 