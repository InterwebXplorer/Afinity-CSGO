#include "playerlist.h"
#include "../resources/sdk/interfaces.h"

void PlayerList::InitializePlayerlist() {
    if (!I::Engine->IsInGame())
        return;

    PlayerProfiles.clear();

    for (int i = 0; i < I::Engine->GetMaxClients(), i++) {
        PlayerOptions Options;
        CBaseEntity* Entity = I::ClientEntityList->Get<CBaseEntity>(i);

        if (!Entity)
            continue;

        if (!Entity->IsPlayer)
            continue;

        PlayerInfo_t PlayerInfo;

        I::Engine->GetPlayerInfo(Entity, PlayerInfo);

        Options.PlayerName = PlayerInfo.szName;
        Options.SteamID = PlayerInfo.szSteamID;
        Options.IsBot = PlayerInfo.bFakePlayer;
        Options.IsResolved = false;

        if (!Entity->IsEnemy())
            Options.IsTeamMember = true;
        else if (Entity->IsEnemy())
            Options.IsTeamMember = false;
            
        Options.StealName = false;
        Options.CopyClantag = false;
        Options.IsPriorityPlayer = false;
        Options.Whitelist = false;
        Options.SetRage = false;
        Options.SetLegit = false;
        Options.Follow = false;
        Options.ForceHead = false;
        Options.ForceBody = false;
        Options.DontResolve = false;
        Options.ResetOptions = false;
    
        PlayerProfiles.push_back(Options);
    }
}

void PlayerList::ExecuteOptions() {
    if (!I::Engine->IsInGame())
        return;

}

/*                        
    ImGui::Button("Steal name", ImVec2(276, 30), PlayerOptions.stealname);
    ImGui::Button("Copy clantag", ImVec2(276, 30), PlayerOptions.copyclantag);
    UI::Checkbox("Priority", PlayerOptions.priority);
    UI::Checkbox("Whitelist", PlayerOptions.whitelist);
    UI::Checkbox("Rage", PlayerOptions.set_rage);
    UI::Checkbox("Legit", PlayerOptions.set_legit);
    UI::Checkbox("Follow", PlayerOptions.follow);
    UI::Dropdown("Force hitboxes", PlayerHitboxes[], PlayerOptions.forcehitboxes);
    UI::Checkbox("Force head", PlayerOptions.forcehead);
    UI::Checkbox("Force body", PlayerOptions.forcebody);
    UI::Checkbox("Dont resolve", PlayerOptions.dontresolve);
*/

void ResetPlayerlist() {
    if (!I::Engine->IsInGame())
        return;

    if (!ResetOptions)
        return; 

    PlayerProfiles.clear();
    InitializePlayerlist();
}