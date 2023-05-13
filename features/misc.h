#pragma once

namespace Misc {
    void AutoPistol(CUserCmd* Cmd);
    void FixTabletSignal();
    void AutoDefuse(CUserCmd* Cmd);
    void AutoExtinguishIncendiarys(CUserCmd* Cmd);
    void ClanTag();
    void BlockBot();
    void HeadstandBot();
    void ForceRegion();
    void RevealRanks(CUserCmd* Cmd);
    void SlowWalk(CUserCmd* Cmd);
    void InfiniteDuck(CUserCmd* Cmd);
    void QuickStop(CUserCmd* Cmd);
    void NameChanger();
    void CommandSpammer();
    void BunnyHop(CUserCmd* Cmd);
    void AutoStrafe(CUserCmd* Cmd);
    void AirCrouch(CUserCmd* Cmd);
    void PeekAssist(CUserCmd* Cmd);
    void BuyBot();
    void TriggerBan(CUserCmd* Cmd);
    void UnlockAchievements();
    void SendClanTag(const char* ClanTag, const char* Identifier);
    void SendName(const char* Name);
}