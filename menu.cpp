#include "menu.h"
#include <Windows.h>
#include <Chrono>
#include "../resources/utils/ui.h"
#include "../features/features.h"
#include "config.h"

//imgui
#define  IMGUI_MATH_OPERATORS
#include "../resources/imgui/imgui.h"
#include "../resources/imgui/imgui_freetype.h"
#include "../resources/imgui/imgui_internal.h"
#include "../resources/imgui/dx9/imgui_impl_dx9.h"
#include "../resources/imgui/win32/imgui_impl_win32.h"

static char* sidebar_tabs[] = {
    "LEGIT",
    "RAGE",
    "VISUAL",
    "ANTIAIM",
    "MODIFIER",
    "MISC"
};

#define menu_width     900.0f
#define menu_height    500.0f
#define sidebar_width  137.0f
#define sidebar_height 62.0f
//#define topbar_width Value Calculated later
#define topbar_height  26.0f
#define main_width     716.0f
#define main_height    432.0f

enum {
    TAB_LEGIT,
    TAB_RAGE,
    TAB_VISUAL,
    TAB_ANTIAIM,
    TAB_MODIFIER,
    TAB_MISC
};

void LegitTab() {
    static char* legit_tab_names[] = { "GENERAL", "TRIGGERBOT", "RCS" };
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

void RageTab() {
    static char* rage_tab_names[] = { "GENERAL", "PISTOL", "AWP", "SCOUT", "AUTO" };
    static int rage_tab_index = 0;

    if (rage_tab_index == 0) {
        const char* generalhitboxes[] = { "Head", "Chest", "Body", "Arms", "Legs" };
        const char* resolver[] = { "Default", "Random", "Psuedo learn" }

        UI::Checkbox("Enable", Options.rage_general_enable);
        UI::Slider("FOV", Options.rage_general_fov, 0, 180);
        UI::Checkbox("Autofire", Options.rage_autofire);
        UI::Checkbox("Penetration", Options.rage_general_penetration);
        UI::Checkbox("Knifebot", Options.rage_general_knifebot);
        UI::Checkbox("Zeusbot", Options.rage_general_zeusbot);
        UI::Dropdown("Resolver", Options.rage_general_resolver);
        UI::Checkbox("Resolve x-axis", Options.rage_general_resolve_xaxis);
        UI::Slider("Backtrack", Options.rage_general_backtrack, 0, 100);
        UI::Checkbox("Damage overide", Options.rage_general_dmgoveride); //
        UI::Checkbox("Hideshots", Options.rage_general_hideshots); //


    }

    if (rage_tab_index == 1) {
        const char* pistolhitboxes[] = { "Head", "Chest", "Body", "Arms", "Legs" };

        UI::Checkbox("Overide default", Options.rage_pistol_enable);
    }

    if (rage_tab_index == 2) {
        const char* awphitboxes[] = { "Head", "Chest", "Body", "Arms", "Legs" };

        UI::Checkbox("Overide default", Options.rage_awp_enable);
    }

    if (rage_tab_index == 3) {
        const char* scouthitboxes[] = { "Head", "Chest", "Body", "Arms", "Legs" };

        UI::Checkbox("Overide default", Options.rage_scout_enable);
    }

    if (rage_tab_index == 4) {
        const char* autohitboxes[] = { "Head", "Chest", "Body", "Arms", "Legs" };

        UI::Checkbox("Overide default", Options.rage_auto_enable);
    }
}

void VisualTab() {
    static char* visual_tab_names[] = { "ENEMY", "TEAM", "LOCAL", "OTHER" };
    static int visual_tab_index = 0;

    if (visual_tab_index == 0) {
        const char* boxstyle[] = { "Off", "Normal", "Cornered", "3d" };
        const char* enemyflags[] = { "Target", "Resolve Status", "Money", "Armour", "Utility", "Scope", "Reload", "Exploits", "Ping", "Bomb", "Priority", "Location" };
        const char* chamsmaterial[] = { "", "" }; //TODO: add custom materials

        UI::Checkbox("Enable", Options.visual_enemy_enabled); //
        UI::Dropdown("Box", Options.visual_enemy_); ///
        UI::Checkbox("Snaplines", Options.visual_enemy_flags); ///
        UI::Checkbox("Name", Options.visual_enemy_);
        UI::Checkbox("Health", Options.visual_enemy_);
        UI::Checkbox("Ammo", Options.visual_enemy_); ///
        UI::Dropdown("Flags", Options.visual_enemy_);
        UI::Checkbox("Sound", Options.visual_); ///
        UI::Checkbox("Line of sight", Options.visual_); ///
        UI::Checkbox("Skeleton", Options.visual_); ///
        UI::Checkbox("Outline", Options.visual_); ///

        UI::Checkbox("Chams (Backtrack)", Options.visual_); ///
        UI::Checkbox("Chams (Occluded)", Options.visual_); ///
        UI::Checkbox("Chams (Visable)", Options.visual_); ///
        UI::slider("Chams glow", Options.visual_);
        UI::Dropdown("Chams material", Options.visual_);
        UI::Textbox("Custom", Options.visual_);

        UI::Checkbox("Bullet tracers", Options.visual_enemy_); ///
        UI::Checkbox("Shot records", Options.visual_enemy_); ///
        UI::Checkbox("Dormant", Options.visual_enemy_);
    }

    if (visual_tab_index == 1) {
        ImGui::Text("Unavailable");
    }

    if (visual_tab_index == 2) {
        UI::Checkbox("Enable", Options.visual_local_enabled);

        //arms
        UI::Checkbox("", Options.visual_local_);

    }

    if (visual_tab_index == 3) {
        const char* removals[] = { "Scope overlay", "View punch", "Aim punch", "Smoke Effects", "Flash Effects", "Fog", "Post Processing", "Arms" };
        const char* droppedweapons[] = { "Text", "Glow", "Icon" };
        const char* penetrationcrosshair[] = { "Off", "Default", "Circle" };
        const char* weaponflags[] = { "Icon", "Text", "Distance", "Ammo" };
        
        UI::Checkbox("Enable", Options.visual_other_enabled);
        UI::Checkbox("Bomb timer", Options.visual_other_bombtimer); //attach to radar curve
        UI::Dropdown("Penetration crosshair", Options.visual_);

        UI::Checkbox("Full bright", Options.visual_);
        UI::Checkbox("World color", Options.visual_); ///
        UI::Checkbox("Prop color", Options.visual_); ///
        UI::Checkbox("Sky color", Options.visual_); ///

        UI::Dropdown("Removals", Options.visual_);
        UI::Checkbox("Third person", Options.visual_); // 
        UI::Slider("Distance", Options.visual_, 0, 300);
        UI::Checkbox("On death", Options.visual_);
        UI::Checkbox("Radar", Options.visual_);
        UI::Checkbox("Stream proof", Options.visual_);
        UI::Checkbox("Out of fov arrows", Options.visual_); ///
        UI::Slider("Menu character speed", Options.visual_, +0, +100);

        ImGui::BeginGroup("Grenades");
        UI::Checkbox("Molotov tracer", Options.visual_); ///
        UI::Checkbox("Smoke tracer", Options.visual_); ///
        UI::Checkbox("HE tracer", Options.visual_); ///
        UI::Checkbox("Flashbang tracer", Options.visual_); ///
        UI::Checkbox("Decoy tracer", Options.visual_); ///
        UI::Checkbox("Molotov spread", Options.visual_); ///
        UI::Checkbox("Smoke spread", Options.visual_); ///

        //Add fov crap

        ImGui::BeginGroup("Weapons");
        UI::Checkbox("Enable", Options.visual_);
        UI::Dropdown("Flags", Options.visual_);
        UI::Checkbox("Chams", Options.visual_);
        UI::Dropdown("Cham material", Options.visual_);

        UI::Checkbox("Grenade prediction", Options.visual_); /// 2x color pickers
        UI::Checkbox("Enemy grenade prediction", Options.visual_); /// 2x color pickers
        UI::Checkbox("Watermark", Options.visual_);
        UI::Checkbox("Visualise oneway/wallbang locations", Options.visual_); //add togle visable

        //IDK WHERE TO PUT THIS
        UI::Dropdown("Hitsound", Options.visual_);
        UI::Dropdown("Hiteffect", Options.visual_);
        UI::Dropdown("Killsound", Options.visual_);
        UI::Dropdown("Killanouncer", Options.visual_);
        UI::Dropdown("Killeffect", Options.visual_);
        UI::Dropdown("Deathsound", Options.visual_);
    }
}

void AntiAimTab() {
    static char* antiaim_tab_names[] = { "LEGIT", "RAGE", "SCRIPTING" };
    static int antiaim_tab_index = 0;

    if (antiaim_tab_index == 0) {
        ImGui::Text("Unavailable");
    }

    if (antiaim_tab_index == 1) {
        const char* xaxisjittermode[] = { "Offset", "Random", "UDZ random", "Fluctuate", "Step" };
        const char* yaxisanglemode[] = { "Static", "Spin", "Rotate", "Step" };
        const char* yaxisjittermode[] = { "Offset", "Random" };
        const char* desyncside[] = { "Off", "Left", "Right", "Switch" };
        const char* freestand[] = { "Off", "Freestand", "Anti-freestand" };
        const char* fakelagtriggers[] = { "Standing", "Moving", "In air", "On shot", "On peek", "On damage" };

        ImGui::BeginGroup("X-AXIS");
        UI::Checkbox("Enable", Options.antiaim_rage_xenable);
        UI::Slider("Base angle", Options.antiaim_rage_xbase_angle, -90, 90);
        UI::Checkbox("Jitter", Options.antiaim_rage_xjitter_enable);
        UI::Doubleslider("Jitter range", Options.antiaim_rage_xjitter_range, -90, 90);
        UI::Slider("Jitter speed", Options.antiaim_rage_xjitter_speed, 0, 100);
        UI:Dropdown("Jitter mode", Options.antiaim_rage_xjitter_mode);
        ImGui::EndGroup();
        ImGui::BeginGroup("Y-AXIS");
        UI::Checkbox("Enable", Options.antiaim_rage_yenable);
        UI::Slider("Base angle", Options.antiaim_rage_ybase_angle, -180, 180);
        UI:Dropdown("Angle mode", Options.antiaim_rage_yangle_mode);
        UI::Slider("Angle speed", Options.antiaim_rage_yangle_speed, 0, 100);
        UI::Checkbox("Jitter", Options.antiaim_rage_yjitter_enable);
        UI::Doubleslider("Jitter range", Options.antiaim_rage_yjitter_range, -90, 90);
        UI::Slider("Jitter speed", Options.antiaim_rage_yjitter_speed, 0, 100);
        UI:Dropdown("Jitter mode", Options.antiaim_rage_yjitter_mode);
        ImGui::EndGroup();
        ImGui::BeginGroup("DESYNC");
        UI::Checkbox("Enable", Options.antiaim_rage_desync_enable);
        UI:Dropdown("Desync side", Options.antiaim_rage_desync_side);
        UI::Doubleslider("Desync range", Options.antiaim_rage_desync_range, -60, 60);
        UI::Checkbox("Invert", Options.antiaim_rage_desync_invert); //
        UI::Checkbox("Spam invert", Options.antiaim_rage_desync_invert_spam);
        UI::Slider("Delay", Options.antiaim_rage_desync_invert_spam_delay, 0, 1000);
        UI:Dropdown("Freestand", Options.antiaim_rage_desync_freestand);
        UI::Checkbox("Avoid overlap", Options.antiaim_rage_desync_avoid_overlap);
        UI::Checkbox("Dormant", Options.antiaim_rage_desync_dormant);
        ImGui::EndGroup();
        ImGui::BeginGroup("FAKELAG");
        UI::Checkbox("Enable", Options.antiaim_rage_fakelag_enable);
        UI::Doubleslider("Fakelag range", Options.antiaim_rage_fakelag_range, 0, 17);
        UI:Dropdown("Fakelag triggers", Options.antiaim_rage_fakelag_triggers);
        UI::Checkbox("Dormant", Options.antiaim_rage_fakelag_dormant);
        ImGui::EndGroup();
        ImGui::BeginGroup("OTHER");
        UI::Checkbox("At targets", Options.antiaim_rage_other_at_targets);
        UI::Checkbox("Wall detection", Options.antiaim_rage_other_wall_detection);
        UI::Checkbox("Slidewalk", Options.antiaim_rage_other_slidewalk);
        UI::Checkbox("Slidewalk spammer", Options.antiaim_rage_other_slidewalk_spam);
        UI::Checkbox("Fakeduck", Options.antiaim_rage_other_fakeduck); //
        UI::Checkbox("Aircrouch", Options.misc_rage_other_aircrouch);
        UI::Checkbox("Teleport", Options.antiaim_rage_other_teleport); // 
        UI::Checkbox("Teleport on damage", Options.antiaim_rage_other_damage_teleport);
        UI::Checkbox("Psuedo Crim Walk", Options.antiaim_rage_other_crim_walk); //
        ImGui::EndGroup();
    }

    if (antiaim_tab_index == 2) {
        ImGui::Text("Unavailable");
    }
}

void ModifierTab() {
    static char* modifier_tab_names[] = { "SKINS", "INVENTORY", "MODELS" };
    static int modifier_tab_index = 0;

    if (modifier_tab_index == 0) {
        ImGui::Text("Unavailable");
    }

    if (modifier_tab_index == 1) {
        ImGui::Text("Unavailable");
    }

    if (modifier_tab_index == 2) {
        ImGui::Text("Unavailable");
    }
}

void MiscTab() {
    static char* misc_tab_names[] = { "GENERAL", "SCRIPTING", "PLAYERS", "CONSOLE" };
    static int misc_tab_index = 0;

    if (misc_tab_index == 0) {
        const char* chatspam[] = { "Off", "Default", "Mimmic", "Ezfrags", "Custom" };
        const char* namechanger[] = { "Off", "Team-Only", "Enemy-Only", "Everyone", "Custom" };
        const char* forceregion[] = { "Off", "Australia", "Austria", "Brazil", "Chile", "Dubai", "France", "Germany", "Hong Kong", "India(Chennai)", "India(Mumbai)", "Japan", "Luxembourg", "The Nether", "Peru", "Phillipines", "Poland", "Singapore", "No Water", "Spain", "Sweden", "United Kingdom", "USA(Atlanta)", "USA(Seattle)", "USA(Chicago)", "USA(Los Angeles)", "USA(Moses Lake)", "USA(Oklahoma)", "USA(Seattle)", "USA(Washington DC)" };
        const char* informationspammer[] = { "Name", "Rank", "Weapon", "Location", "Health" };
        const char* buybotprimary[] = { "Off", "Auto", "Scout", "AWP", "Ak/M4" };
        const char* buybotsecondary[] = { "Off", "Dual-Berettas", "P250", "Five7/Tec9", "Deagle/R8" };
        const char* buybotnades[] = { "Smoke", "Flash", "Molotov", "Decoy", "HE Grenade" };
        const char* buybotother[] = { "Kevlar", "Helmet", "Defuser", "Taser", "Riot Sheild" };
        const char* buybotpriority[] = { "Off", "Primary", "Secondary", "Nades", "Other" };

        UI::Checkbox("Enable", Options.misc_general_enable);
        UI::Checkbox("Auto-accept", Options.misc_);
        UI::Checkbox("Auto-fire", Options.misc_);
        UI::Slider("Delay", Options.misc_, 0, 500);
        UI::Checkbox("Preserve killfeed", Options.misc_);
        UI::Checkbox("Auto-defuse", Options.misc_);
        wUI::Checkbox("Clantag", Options.misc_general_clantag);
        UI::Checkbox("Block bot", Options.misc_); //
        UI::Checkbox("Headstand bot", Options.misc_); //
        UI::Dropdown("Force region", Options.misc_);
        UI::Checkbox("Reveal overwatch", Options.misc_);
        UI::Checkbox("Reveal ranks", Options.misc_);
        UI::Checkbox("Anti-untrusted", Options.misc_);
        UI::Checkbox("Bypass sv_pure", Options.misc_);
        UI::Checkbox("Hidden cvars", Options.misc_);
        UI::Dropdown("Chatspam", Options.misc_, );
        UI::Textbox("Custom", Options.misc_); //File name e.g.CUSTOM.accss
        UI::Checkbox("Infinite duck", Options.misc_);
        UI::Checkbox("Quick stop", Options.misc_);
        UI::Checkbox("Unlock inventory", Options.misc_);
        UI::Dropdown("Name changer", Options.misc_);
        UI::Slider("Speed", Options.misc_, 0, 100);
        UI::Textbox("Spam command", Options.misc_);
        UI::Dropdown("Information spammer", Options.misc_);
        UI::Checkbox("Auto grenade line ups", Options.misc_); // Add 2 select boxes (1 toggle visible, 1 toggle execute) TODO:Add programmable lineups
        UI::Checkbox("Visible when grenade equip", Options.misc_);
        UI::Checkbox("Bunny hop", Options.misc_);
        UI::Checkbox("Auto strafe", Options.misc_);
        UI::Slider("Miss ratio", Options.misc_, 0, 10);
        UI::Checkbox("Enable buybot", Options.misc_buybot_enable);
        UI::Dropdown("Primary", Options.misc_buybot_primary);
        UI::Dropdown("Secondary", Options.misc_buybot_secondary);
        UI::Dropdown("Nades", Options.misc_buybot_nades);
        UI::Dropdown("Other", Options.misc_buybot_other);
        UI::Dropdown("Priority", Options.misc_buybot_priority);
        UI::Button("Trigger VAC", Options.misc_);
        UI::Button("Unload", Options.misc_);

        ImGui::BeginGroup("Configuration");
        //Add box showing configs
        UI::Textbox("Name", Options.misc_);
        UI::Button("Create", Options.misc_);
        UI::Button("Save", Options.misc_);
        UI::Button("Load", Options.misc_);
        UI::Button("Delete", Options.misc_);
        UI::Button("Reset", Options.misc_);
        ImGui::EndGroup();
    }

    if (misc_tab_index == 1) {
        ImGui::Text("Unavailable");
    }

    if (misc_tab_index == 2) { //GOTV = null
        const char* playerhitboxes[] = { "Head", "Chest", "Body", "Arms", "Legs" };

        UI::Checkbox("Enable", Options.misc_);
        //Add player list thing here
        //BREAK HERE//
        ImGui::BeginGroup("Options");
        UI::Checkbox("Priority", Options.misc_);
        UI::Checkbox("Whitelist", Options.misc_);
        UI::Checkbox("Rage", Options.misc_);
        UI::Checkbox("Legit", Options.misc_);
        UI::Checkbox("Follow", Options.misc_);
        UI::Dropdown("Force hitboxes", Options.misc_);
        UI::Checkbox("Force head", Options.misc_);
        UI::Checkbox("Force body", Options.misc_);
        UI::Checkbox("Dont resolve", Options.misc_);
        ImGui::EndGroup();
    }

    if (misc_tab_index == 3) {
        ImGui::Text("Unavailable");
    }
}

/*
AA Script Syntax
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

//todo: add node based material system for chams

/*
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