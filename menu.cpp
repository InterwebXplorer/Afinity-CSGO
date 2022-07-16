#include "resources/utils/ui.h"
#include "resources/imgui/imgui.h"
#include "resources/imgui/imgui_freetype.h"
#include "resources/imgui/imgui_internal.h"
#include "resources/imgui/impl/imgui_impl_dx9.h"
#include "resources/imgui/impl/imgui_impl_win32.h"
#include "config.h"

//FUCK FUCK FUCK FUCK FUCK

void RenderMenu(bool menuopen, int& activetab) {
static char* sidebar_tabs[] = {"Legit", "Rage", "Esp", "Antiaim", "Modifier", "Misc"}; //40px hight?
static int sidebar_tab_index = 0;

ImGui::Begin("Afinity", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
ImGui::BeginChild("Border");
ImGui::EndChild();

RenderLegitTab();
RenderRageTab();
RenderEspTab();
RenderAntiAimTab();
RenderModifierTab();
RenderMiscTab();

}


void RenderLegitTab() {
    static char* legit_tab_names[] = {"General", "Triggerbot", "RCS"};
    static int legit_tab_index = 0;
    
    if (legit_tab_index == 0) {
        ImGui::Text("Unavailable");
    }
    if (legit_tab_index == 1) {
        ImGui::Text("Unavailable");
    }
    if (legit_tab_index == 2) {
        ImGui::Text("Unavailable");
    }
}

void RenderRageTab() {
    static char* rage_tab_names[] = {"Global", "Default", "Pistol", "Awp", "Scout", "Auto"};
    static int rage_tab_index = 0;

    if (rage_tab_index == 0) { //this tab will be beside the weapon configs
        const char* resolver[] = {"Off", "Default", "Random", "Psuedo learn", "Animation state"};
        const char* targetscanning[] = {"Low", "Medium", "High"};

        UI::Checkbox("Enable", Options.rage_);
        UI::Checkbox("Safe point", Options.rage_);
        //safepoint crap here
        UI::Checkbox("Silentaim", Options.rage_);
        UI::Checkbox("Autofire", Options.rage_);
        UI::Checkbox("Autoscope", Options.rage_);
        UI::Checkbox("Autostop", Options.rage_);
        UI::Checkbox("Penetration", Options.rage_);
        UI::Checkbox("Knifebot", Options.rage_);
        UI::Checkbox("Zuesbot", Options.rage_);
        UI::Dropdown("Resolver", resolver[], Options.rage_);
        UI::Checkbox("X-Axis", Options.rage_);
        UI::Checkbox("Z-Axis", Options.rage_);
        UI::Checkbox("Bruteforce", Options.rage_); //shoot previous sucessful points
        UI::Checkbox("Hideshots", Options.rage_); //
        UI::Checkbox("Doubletap", Options.rage_); //
        UI::Checkbox("No recoil", Options.rage_global_norecoil);
        UI::Checkbox("Revolver prep", Options.rage_);
        UI::Dropdown("Target scanning", targetscanning[], Options.rage_);
        UI::Checkbox("No-scope", Options.rage_);
        UI::Checkbox("Damage override", Options.rage_);
    }

    if (rage_tab_index == 1) {
        const char* defaulthitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* defaulmultipointthitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        
        UI::Slider("Hitchance", Options.rage_, 0, 100 );
        UI::Dropdownmulti("Hitboxes", defaulthitboxes[], Options.rage_);
        UI::Checkbox("Use multipoint", Options.rage_);
        UI::Dropdownmulti("Multipoint", defaulmultipointthitboxes[], Options.rage_);
        UI::Slider("Min damage(Ocluded)", Options.rage_, 0, 125 );
        UI::Slider("Min damage(Visible)", Options.rage_, 0, 125 );
        UI::Slider("Backtrack", Options.rage_, 0, 400 );
        UI::Slider("Delay", Options.rage_, 0, 500 );
        UI::Checkbox("Force body", Options.rage_);
        UI::Checkbox("Force head", Options.rage_);
        UI::Checkbox("In-Air", Options.rage_); //override all and focus on shots
        UI::Slider("Damage override", Options.rage_, 0, 125 );
    }

    if (rage_tab_index == 2) {
        const char* pistolhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* pistolmultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        UI::Checkbox("Overide default", Options.rage_pistol_enable);
        UI::Slider("Hitchance", Options.rage_, 0, 100 );
        UI::Dropdownmulti("Hitboxes", pistolhitboxes[], Options.rage_);
        UI::Checkbox("Use multipoint", Options.rage_);
        UI::Dropdownmulti("Multipoint", pistolmultipointhitboxes[], Options.rage_);
        UI::Slider("Min damage(Ocluded)", Options.rage_, 0, 125 );
        UI::Slider("Min damage(Visible)", Options.rage_, 0, 125 );
        UI::Slider("Backtrack", Options.rage_, 0, 400 );
        UI::Slider("Delay", Options.rage_, 0, 500 );
        UI::Checkbox("Force body", Options.rage_pistol_enable);
        UI::Checkbox("Force head", Options.rage_pistol_enable);
        UI::Checkbox("In-Air", Options.rage_); 
        UI::Slider("Damage override", Options.rage_, 0, 125 );
    }

    if (rage_tab_index == 3) {
        const char* awphitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* awpmultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        UI::Checkbox("Overide default", Options.rage_awp_enable);
        UI::Slider("Hitchance", Options.rage_, 0, 100 );
        UI::Dropdownmulti("Hitboxes", awphitboxes[], Options.rage_);
        UI::Checkbox("Use multipoint", Options.rage_);
        UI::Dropdownmulti("Multipoint", awpmultipointhitboxes[], Options.rage_);
        UI::Slider("Min damage(Ocluded)", Options.rage_, 0, 125 );
        UI::Slider("Min damage(Visible)", Options.rage_, 0, 125 );
        UI::Slider("Backtrack", Options.rage_, 0, 400 );
        UI::Slider("Delay", Options.rage_, 0, 500 );
        UI::Checkbox("Force body", Options.rage_);
        UI::Checkbox("Force head", Options.rage_);
        UI::Checkbox("In-Air", Options.rage_); 
        UI::Slider("Damage override", Options.rage_, 0, 125 );
    }

    if (rage_tab_index == 4) {
        const char* scouthitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* scoutmultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        UI::Checkbox("Overide default", Options.rage_scout_enable);
        UI::Slider("Hitchance", Options.rage_, 0, 100 );
        UI::Dropdownmulti("Hitboxes", scouthitboxes[], Options.rage_);
        UI::Checkbox("Use multipoint", Options.rage_);
        UI::Dropdownmulti("Multipoint", scoutmultipointhitboxes[], Options.rage_);
        UI::Slider("Min damage(Ocluded)", Options.rage_, 0, 125 );
        UI::Slider("Min damage(Visible)", Options.rage_, 0, 125 );
        UI::Slider("Backtrack", Options.rage_, 0, 400 );
        UI::Slider("Delay", Options.rage_, 0, 500 );
        UI::Checkbox("Force body", Options.rage_);
        UI::Checkbox("Force head", Options.rage_);
        UI::Checkbox("In-Air", Options.rage_); 
        UI::Slider("Damage override", Options.rage_, 0, 125 );
    }

    if (rage_tab_index == 5) {
        const char* autohitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* automultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        UI::Checkbox("Overide default", Options.rage_auto_enable);
        UI::Slider("Hitchance", Options.rage_, 0, 100 );
        UI::Dropdownmulti("Hitboxes", autohitboxes[], Options.rage_);
        UI::Checkbox("Use multipoint", Options.rage_);
        UI::Dropdownmulti("Multipoint", automultipointhitboxes[], Options.rage_)
        UI::Slider("Min damage(Ocluded)", Options.rage_, 0, 125 );
        UI::Slider("Min damage(Visible)", Options.rage_, 0, 125 );
        UI::Slider("Backtrack", Options.rage_, 0, 400 );
        UI::Slider("Delay", Options.rage_, 0, 500 );
        UI::Checkbox("Force body", Options.rage_;
        UI::Checkbox("Force head", Options.rage_);
        UI::Checkbox("In-Air", Options.rage_); 
        UI::Slider("Damage override", Options.rage_, 0, 125 );
    }
}

void RenderEspTab() {
    static char* esp_tab_names[] = {"Enemy", "Team", "Local", "Other"};
    static int esp_tab_index = 0;

    if (esp_tab_index == 0) {
        const char* boxstyle[] = {"Off", "Normal", "Cornered", "3d"};
        const char* enemyflags[] = {"Target", "Resolve Status", "Money", "Armour", "Utility", "Scope", "Reload", "Exploits", "Ping", "Bomb", "Priority", "Location"};
        const char* chamsmaterial[] = {"", ""}; //TODO: add custom materials

        UI::Checkbox("Enable", Options.esp_enemy_enabled); //
        UI::Dropdown("Box", Options.esp_enemy_); ///
        UI::Checkbox("Snaplines", Options.esp_enemy_flags); ///
        UI::Checkbox("Name", Options.esp_enemy_);
        UI::Checkbox("Health", Options.esp_enemy_);
        UI::Checkbox("Ammo", Options.esp_enemy_); ///
        UI::Dropdown("Flags", Options.esp_enemy_);
        UI::Checkbox("Sound", Options.esp_); ///
        UI::Checkbox("Line of sight", Options.esp_); ///
        UI::Checkbox("Skeleton", Options.esp_); ///
        UI::Checkbox("Outline", Options.esp_); ///

        UI::Checkbox("Chams (Backtrack)", Options.esp_); ///
        UI::Checkbox("Chams (Occluded)", Options.esp_); ///
        UI::Checkbox("Chams (Visible)", Options.esp_); ///
        UI::Dropdown("Flat", Options.esp_)
        UI::slider("Chams glow", Options.esp_);
        UI::Dropdown("Chams material", Options.esp_);
        UI::Textbox("Custom", Options.esp_);

        UI::Checkbox("Bullet tracers", Options.esp_enemy_); ///
        UI::Checkbox("Shot records", Options.esp_enemy_); ///
        UI::Checkbox("Dormant", Options.esp_enemy_);
    }

    if (esp_tab_index == 1) {
        ImGui::Text("Unavailable");
    }

    if (esp_tab_index == 2) {
        UI::Checkbox("Enable", Options.esp_local_enabled);

        //arms
        UI::Checkbox("", Options.esp_local_);

    }

    if (esp_tab_index == 3) {
        const char* removals[] = {"Scope overlay", "Scope lines", "View punch", "Aim punch", "Smoke Effects", "Flash Effects", "Fog", "Post Processing", "Arms", "Weapon"};
        const char* droppedweapons[] = {"Text", "Glow", "Icon"};
        const char* penetrationcrosshair[] = {"Off", "Default", "Circle", "Square"};
        const char* skybox[] = {"Default", "Galaxy", "Disabled", "Custom"};
        const char* weaponflags[] = {"Icon", "Text", "Distance", "Ammo"};
        
        UI::Checkbox("Enable", Options.esp_other_enabled);
        UI::Checkbox("Bomb timer", Options.esp_other_bombtimer); //attach to radar curve
        UI::Dropdown("Penetration crosshair", penetrationcrosshair[], Options.esp_);

        UI::Checkbox("Full bright", Options.esp_);
        UI::Checkbox("World color", Options.esp_); ///
        UI::Checkbox("Prop color", Options.esp_); ///
        UI::Checkbox("Sky color", Options.esp_); ///
        UI::Dropdown("Sky box", skybox[], Options.esp_);

        UI::Dropdown("Removals", Options.esp_);
        UI::Checkbox("Third person", Options.esp_); // 
        UI::Slider("Distance", Options.esp_, 0, 300);
        UI::Checkbox("On death", Options.esp_);
        UI::Checkbox("Radar", Options.esp_);
        UI::Checkbox("Stream proof", Options.esp_);
        UI::Checkbox("Out of fov arrows", Options.esp_); ///
        UI::Slider("Menu character speed", Options.esp_, +0, +100);

        UI::BeginGroup("Grenades");
        UI::Checkbox("Molotov tracer", Options.esp_); ///
        UI::Checkbox("Smoke tracer", Options.esp_); ///
        UI::Checkbox("HE tracer", Options.esp_); ///
        UI::Checkbox("Flashbang tracer", Options.esp_); ///
        UI::Checkbox("Decoy tracer", Options.esp_); ///
        UI::Checkbox("Molotov spread", Options.esp_); ///
        UI::Checkbox("Smoke spread", Options.esp_); ///

        //Add fov crap

        UI::BeginGroup("Weapons");
        UI::Checkbox("Enable", Options.esp_);
        UI::Dropdown("Flags", Options.esp_);
        UI::Checkbox("Chams", Options.esp_);
        UI::Dropdown("Cham material", Options.esp_);

        UI::Checkbox("Grenade prediction", Options.esp_); /// 2x color pickers
        UI::Checkbox("Enemy grenade prediction", Options.esp_); /// 2x color pickers
        UI::Checkbox("Watermark", Options.esp_);
        UI::Checkbox("visualise oneway/wallbang locations", Options.esp_); //add togle visible

        //IDK WHERE TO PUT THIS
        UI::Dropdown("Hitsound", Options.esp_);
        UI::Dropdown("Hiteffect", Options.esp_);
        UI::Dropdown("Killsound", Options.esp_);
        UI::Dropdown("Killanouncer", Options.esp_);
        UI::Dropdown("Killeffect", Options.esp_);
        UI::Dropdown("Deathsound", Options.esp_);
    }
}

void RenderAntiAimTab() {
    static char* antiaim_tab_names[] = {"Legit", "Rage", "Scripting"};
    static int antiaim_tab_index = 0;

    if (antiaim_tab_index == 0) {
        ImGui::Text("Unavailable");
    }

    if (antiaim_tab_index == 1) {
        const char* xaxisanglemode[] = {"Static", "UDZ random", "Fluctuate"};
        const char* xaxisjittermode[] = {"Offset", "Random"};
        const char* yaxisanglemode[] = {"Static", "Spin", "Rotate"};
        const char* yaxisjittermode[] = {"Offset", "Random", "WASD random"};
        const char* desyncside[] = {"Off", "Left", "Right", "Random"};
        const char* freestand[] = {"Off", "Freestand", "Anti-freestand"};
        const char* fakelagtriggers[] = {"Standing", "Moving", "In air", "On shot", "On peek", "On damage", "On reload"};
        const char* slidewalk[] = {"Off", "Default", "Backwards"};

        UI::BeginGroup("X-Axis");
        UI::Checkbox("Enable", Options.antiaim_rage_xenable);
        UI::Slider("Base angle", Options.antiaim_rage_xbaseangle, -90, 90);
        UI::Dropdown("Angle mode", xaxisanglemode[], Options.antiaim_rage_xanglemode);
        UI::Slider("Angle speed", Options.antiaim_rage_xanglespeed, 0, 100);
        UI::Checkbox("Jitter", Options.antiaim_rage_xjitterenable);
        UI::Doubleslider("Jitter range", Options.antiaim_rage_xjitterrange, -90, 90);
        UI::Slider("Jitter speed", Options.antiaim_rage_xjitterspeed, 0, 100);
        UI::Dropdown("Jitter mode", xaxisjittermode[], Options.antiaim_rage_xjittermode);
        UI::EndGroup();
        UI::BeginGroup("Y-Axis");
        UI::Checkbox("Enable", Options.antiaim_rage_yenable);
        UI::Slider("Base angle", Options.antiaim_rage_ybaseangle, -180, 180);
        UI::Dropdown("Angle mode", yaxisanglemode[], Options.antiaim_rage_yanglemode);
        UI::Slider("Angle speed", Options.antiaim_rage_yanglespeed, 0, 100);
        UI::Checkbox("Jitter", Options.antiaim_rage_yjitterenable);
        UI::Doubleslider("Jitter range", Options.antiaim_rage_yjitterrange, -90, 90);
        UI::Slider("Jitter speed", Options.antiaim_rage_yjitterspeed, 0, 100);
        UI::Dropdown("Jitter mode", yaxisjittermode[], Options.antiaim_rage_yjittermode);
        UI::EndGroup();
        UI::BeginGroup("Desync");
        UI::Checkbox("Enable", Options.antiaim_rage_desyncenable);
        UI::Dropdown("Desync side", desyncside[], Options.antiaim_rage_desyncside);
        UI::Doubleslider("Desync range", Options.antiaim_rage_desyncrange, -60, 60);
        UI::Dropdown("Freestand", freestand[], Options.antiaim_rage_desyncfreestand);
        UI::Checkbox("Avoid overlap", Options.antiaim_rage_desyncavoidoverlap);
        UI::Checkbox("Dormant", Options.antiaim_rage_desyncdormant);
        UI::EndGroup();
        UI::BeginGroup("Fakelag");
        UI::Checkbox("Enable", Options.antiaim_rage_fakelagenable);
        UI::Doubleslider("Fakelag range", Options.antiaim_rage_fakelagrange, 0, 17);
        UI::Dropdown("Fakelag triggers", fakelagtriggers[], Options.antiaim_rage_fakelagtriggers);
        UI::Checkbox("Dormant", Options.antiaim_rage_fakelagdormant);
        UI::EndGroup();
        UI::BeginGroup("Other");
        UI::Checkbox("Invert", Options.antiaim_rage_invert); //
        UI::Checkbox("Target detection", Options.antiaim_rage_targetdetection);
        UI::Checkbox("Wall detection", Options.antiaim_rage_walldetection);
        UI::Checkbox("Slidewalk", slidewalk[], Options.antiaim_rage_slidewalk);
        UI::Slider("Fakeping", Options.antiaim_rage_fakeping, 0, 1000);
        UI::Checkbox("Fakeduck", Options.antiaim_rage_fakeduck); //
        UI::Checkbox("Teleport", Options.antiaim_rage_teleport); // 
        UI::Checkbox("Teleport on damage", Options.antiaim_rage_damageteleport);
        UI::Checkbox("Teleport on shot", Options.antiaim_rage_shotteleport);
        UI::Checkbox("Psuedo crimwalk", Options.antiaim_rage_crimwalk); //
        UI::Checkbox("Antibackstab", Options.antiaim_rage_antibackstab);
        UI::EndGroup();
    }

    if (antiaim_tab_index == 2) {
        ImGui::Text("Unavailable");
    }
}

void RenderModifierTab() {
    static char* modifier_tab_names[] = {"Inventory", "Models", "Unboxing"};
    static int modifier_tab_index = 0;

    if (modifier_tab_index == 0) {
        ImGui::Text("Unavailable");
    }

    if (modifier_tab_index == 1) {
        ImGui::Text("Unavailable");
    }

    if (modifier_tab_index == 2) {
        ImGui::Text("Unavailable");
        //UI::Checkbox("Broadcast unboxings", Options.modifier_unboxing_broadcast); //people in current game will see unboxing messages
    }
}

void RenderMiscTab() {
    static char* misc_tab_names[] = {"General", "Scripting", "Players", "Console"};
    static int misc_tab_index = 0;

    if (misc_tab_index == 0) {
        const char* forceregion[] = {"Off", "Australia", "Austria", "Brazil", "Chile", "Dubai", "France", "Germany", "Hong Kong", "India(Chennai)", "India(Mumbai)", "Japan", "Luxembourg", "The Nether", "Peru", "Phillipines", "Poland", "Singapore", "No Water", "Spain", "Sweden", "United Kingdom", "USA(Atlanta)", "USA(Seattle)", "USA(Chicago)", "USA(Los Angeles)", "USA(Moses Lake)", "USA(Oklahoma)", "USA(Seattle)", "USA(Washington DC)"};
        const char* namechanger[] = {"Off", "Team-Only", "Enemy-Only", "Everyone", "Corrupt", "Custom"};
        const char* informationspammer[] = {"Name", "Rank", "Weapon", "Location", "Health"};
        const char* buybotprimary[] = {"Off", "Auto", "Scout", "AWP", "Ak/M4"};
        const char* buybotsecondary[] = {"Off", "Dual-Berettas", "P250", "Five7/Tec9", "Deagle/R8"};
        const char* buybotnades[] = {"Smoke", "Flash", "Molotov", "Decoy", "HE Grenade"};
        const char* buybotother[] = {"Kevlar", "Helmet", "Defuser", "Taser", "Riot Sheild"};
        const char* buybotpriority[] = {"Off", "Primary", "Secondary", "Nades", "Other"};

        UI::Checkbox("Auto-accept", Options.misc_general_autoaccept);
        UI::Checkbox("Auto-fire", Options.misc_general_autofire);
        UI::Slider("Delay", Options.misc_general_autofiredelay, 0, 1000);
        UI::Checkbox("Preserve killfeed", Options.misc_general_preservekillfeed);
        UI::Checkbox("Auto-defuse", Options.misc_general_autodefuse);
        UI::Checkbox("Auto-smoke", Options.misc_general_autosmoke); //
        UI::Checkbox("Clantag", Options.misc_general_clantag);
        UI::Checkbox("Block bot", Options.misc_general_blockbot); //
        UI::Checkbox("Headstand bot", Options.misc_general_headstandbot); //
        UI::Dropdown("Force region", forceregion[], Options.misc_general_forceregion);
        UI::Checkbox("Reveal overwatch", Options.misc_general_revealoverwatch);
        UI::Checkbox("Reveal ranks", Options.misc_general_revealranks);
        UI::Checkbox("Slowwalk", Options.misc_general_slowwalk);
        UI::Slider("Speed", Options.misc_general_slowwalkspeed, 0, 100); //135 ups for fast walk with no sound
        UI::Checkbox("Anti-untrusted", Options.misc_general_antiuntrusted); //executed in other files not misc.cpp
        UI::Checkbox("Bypass sv_pure", Options.misc_general_bypasssvpure);
        UI::Checkbox("Infinite duck", Options.misc_general_infiniteduck);
        UI::Checkbox("Quick stop", Options.misc_general_quickstop);
        UI::Checkbox("Unlock inventory", Options.misc_general_unlockinventory);
        UI::Dropdown("Namechanger", namechanger[], Options.misc_general_namechanger);
        UI::Textbox("Command spammer", Options.misc_general_commandspammer);
        UI::Dropdown("Information spammer", informationspammer[], Options.misc_general_informationspammer);
        UI::Checkbox("Grenade helper", Options.misc_general_grenadehelper); // Add 2 select boxes (1 toggle visible, 1 toggle execute) TODO:Add programmable lineups //executed in other files not misc.cpp
        UI::Checkbox("Visible when grenade equip", Options.misc_general_grenadehelpervwge);
        UI::Checkbox("Bunnyhop", Options.misc_general_bhop);
        UI::Slider("Hitchance", Options.misc_general_bhophitchance, 0, 100);
        UI::Checkbox("Random", Options.misc_general_bhophitchancerandom);
        UI::Checkbox("Auto strafe", Options.misc_general_autostrafe);
        UI::Checkbox("Aircrouch", Options.misc_general_aircrouch);
        UI::Checkbox("Peek assist", Options.misc_general_peekassist);
        UI::BeginGroup("Buybot");
        UI::Checkbox("Enable buybot", Options.misc_buybot_enable);
        UI::Dropdown("Primary", buybotprimary[], Options.misc_buybot_primary);
        UI::Dropdown("Secondary", buybotsecondary[], Options.misc_buybot_secondary);
        UI::Dropdown("Nades", buybotnades[], Options.misc_buybot_nades);
        UI::Dropdown("Other", buybotother[], Options.misc_buybot_other);
        UI::Dropdown("Priority", buybotpriority[], Options.misc_buybot_priority);
        UI::EndGroup();
        UI::Button("Trigger ban", Options.misc_general_triggerban);
        UI::Button("Unlock achievements", Options.misc_general_unlockachievements);
        UI::Button("Unload", Options.misc_general_unload);

        UI::BeginGroup("Configuration");
        //Add box showing configs
        UI::Textbox("Name", Options.config_name);
        UI::Button("Create", Options.config_create);
        UI::Button("Save", Options.config_save);
        UI::Button("Load", Options.config_load);
        UI::Button("Delete", Options.config_delete);
        UI::Button("Reset", Options.config_reset);
        UI::EndGroup();
    }
    if (misc_tab_index == 1) {
        UI::Text("Unavailable");
    }

    if (misc_tab_index == 2) { //GOTV = null
        const char* playerhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        UI::Checkbox("Enable", Options.misc_); //wont save in config save in temp config?
        //Add player list thing here
        //BREAK HERE//
        UI::BeginGroup("Options");
        UI::Button("Steal name", Options.misc_player_stealname);
        UI::Button("Copy clantag", Options.misc_player_copyclantag);
        UI::Checkbox("Priority", Options.misc_player_priority);
        UI::Checkbox("Whitelist", Options.misc_player_whitelist); //dont shoot
        UI::Checkbox("Rage", Options.misc_player_set_rage);
        UI::Checkbox("Legit", Options.misc_player_set_legit);
        UI::Checkbox("Follow", Options.misc_player_follow);
        UI::Dropdown("Force hitboxes", playerhitboxes[], Options.misc_player_forcehitboxes);
        UI::Checkbox("Force head", Options.misc_player_forcehead);
        UI::Checkbox("Force body", Options.misc_player_forcebody);
        UI::Checkbox("Dont resolve", Options.misc_player_dontresolve);
        UI::EndGroup();
    }

    if (misc_tab_index == 3) {
        ImGui::Text("Unavailable");
    }
}

/*
AA Script Syntax TODO LATER
[HEADER]
passammounts = 2
[PASS1]
METH = false
ETH = -1/0
[PASS2]
METH = true
ETH = -23/12
[FOOTER]
repeat = true
*/

/*
INTERACTIVE PREVIEW
visuals/esp
modifiers
Antiaim
*/

// = keybinder thingy
/// = colorpicker

//TODO: add node based material system for chams (will be in loader)(idk what file format but fuck me if its json)

/* structure for tabs
ImGui::Begin();
ImGui::Columns(2);

ImGui::BeginGroup();
ImGui::Text("Text 1");
ImGui::Text("Text 2");
ImGui::EndGroup();

ImGui::NextColumn();

ImGui::BeginGroup();
ImGui::Text("Text 3");
ImGui::Text("Text 4");
ImGui::EndGroup();

ImGui::Columns(1);
ImGui::End();
*/