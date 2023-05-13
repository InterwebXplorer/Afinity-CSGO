#pragma once

#include <vector>
#include <string>

#define OPTION(type, name, value) type name = value
#define MULTIOPTION(name, ...) enum name { __VA_ARGS__ }

namespace PlayerList {
    void InitializePlayerlist();
    void UpdatePlayerlist();
    void ResetPlayerlist();

    extern std::vector<PlayerOptions> PlayerProfiles;

    OPTION(bool, ResetOptions, false);
}

class PlayerOptions {
    public:
        OPTION(std::string, PlayerName, "");
        OPTION(std::string, SteamID, "");
        OPTION(bool, IsBot, false);
        OPTION(bool, IsResolved, false); //update in resolver.cpp
        OPTION(bool, IsTeamMember, false);
        //------------------------------------------//
        OPTION(bool, StealName, false);
        OPTION(bool, CopyClantag, false);
        OPTION(bool, IsPriorityPlayer, false);
        OPTION(bool, Whitelist, false);
        OPTION(bool, SetRage, false);
        OPTION(bool, SetLegit, false);
        OPTION(bool, Follow, false);
        OPTION(bool, ForceHead, false);
        OPTION(bool, ForceBody, false);
        OPTION(bool, DontResolve, false);
}