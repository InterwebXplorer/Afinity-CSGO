#pragma once

#include <vector>
#include <string>

#define OPTION(type, name, value) type name = value
#define MULTIOPTION(name, ...) enum name { __VA_ARGS__ }

namespace PlayerList {
    extern std::vector<PlayerOptions> PlayerProfiles;

    void AddPlayer(CBaseEntity* Player);
    void ResetPlayerOptions(CBaseEntity* Player);
}

class PlayerOptions {
    public:
        OPTION(std::string, playername, "");
        OPTION(bool, isbot, false);
        OPTION(bool, isresolved, false);
        //------------------------------------------//
        OPTION(bool, stealname, false);
        OPTION(bool, copyclantag, false);
        OPTION(bool, ispriorityplayer, false);
        OPTION(bool, whitelist, false);
        OPTION(bool, set_rage, false);
        OPTION(bool, set_legit, false);
        OPTION(bool, follow, false);
        MULTIOPTION(forcehitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
        OPTION(bool, forcehead, false);
        OPTION(bool, forcebody, false);
        OPTION(bool, dontresolve, false);
        OPTION(bool, resetoptions, false);
}