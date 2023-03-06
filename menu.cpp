#include "resources/imgui/imgui.h"
#include "resources/imgui/imgui_freetype.h"
#include "resources/imgui/imgui_internal.h"
#include "resources/imgui/impl/imgui_impl_dx9.h"
#include "resources/imgui/impl/imgui_impl_win32.h"
#include "resources/utils/draw.h"
#include "resources/utils/inputsystem.h"
#include "resources/utils/filelogging.h"
#include "resources/utils/consolelogging.h"
#include "resources/sdk/interfaces.h"
#include "features/features.h"
#include "options.h"
#include "config.h"
#include "menu.h"

void Menu::Style() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(880, 465);
}

void Menu::RenderMenu() {
    static char* tabs[] = {"Legit", "Rage", "Esp", "Antiaim", "Modifier", "Misc"};
    static int activetab = 0;

    if (menuopen == true) {
        ImGui::Begin("##Afinity", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
            ImGui::SetCursorPos(ImVec2(10, 10));
            ImGui::BeginChild("##Logo", ImVec2(142, 44), false, 0); {
                //redirect to gihub when clicked
            }
            ImGui::EndChild();
            ImGui::SetCursorPos(ImVec2(10, 62));
            ImGui::BeginChild("##Tabs", ImVec2(142, 340), false, 0); {
                for (int i = 0; i < 6; i++) {
                    if (ImGui::Button(tabs[i], ImVec2(142, 44))) {
                        activetab = i;
                    }
                }
            }
            ImGui::EndChild();
            ImGui::SetCursorPos(ImVec2(10, 401));
            ImGui::BeginChild("##Info", ImVec2(142, 70), false, 0); {
                //Steam pfp
                //Steam username
                //Cheat version
                //Config Name
            }
            ImGui::EndChild();
        ImGui::End();
    }
}

if (activetab == 0) {
    static char* legitsubtabs[] = {"General", "Triggerbot", "RCS"};
    static int activelegitsubtab = 0;

    ImGui::SetCursorPos(ImVec2(161, 10));
    ImGui::BeginChild("##SubTabs", ImVec2(708, 44), false, 0); {
        for (int i = 0; i < 3; i++) {
            if (ImGui::Button(legitsubtabs[i], ImVec2(708/3, 26))) {
                activelegitsubtab = i;
            }
        }
    }
    ImGui::EndChild();

    if (activelegitsubtab == 0) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##General", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activelegitsubtab == 1) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Triggerbot", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activelegitsubtab == 2) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##RCS", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }
}

if (activetab == 1) {
    static char* ragesubtabs[] = {"Default", "Pistol", "Awp", "Scout", "Auto"};
    static int activeragesubtab = 0;

    ImGui::SetCursorPos(ImVec2(161, 10));
    ImGui::BeginChild("##SubTabs", ImVec2(708, 44), false, 0); {
        ImGui::SameLine();
        for (int i = 0; i < 6; i++) {
            if (ImGui::Button(ragesubtabs[i], ImVec2(708/6, 26))) {
                activeragesubtab = i;
            }
        }
    }
    ImGui::EndChild();

    const char* safepointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
    const char* safepointdelay[] = {"Head", "Chest", "Body", "Arms", "Legs"};
    const char* teleportmode[] = {"Normal", "Extended", "Disabled"}

    ImGui::SetCursorPos(ImVec2(161, 61));
    ImGui::BeginChild("##Global", ImVec2(354, 410), false, 0); {
        ImGui::Columns(2, NULL, false);
        UI::Checkbox("Enable", Options.rage_enable);
        UI::Slider("FOV", Options.rage_fov, 0, 180);
        UI::Checkbox("Silentaim", Options.rage_silentaim);
        UI::Checkbox("Autofire", Options.rage_autofire);
        UI::Checkbox("Autoscope", Options.rage_autoscope);
        UI::Checkbox("Autostop", Options.rage_autostop);
        UI::Checkbox("Penetration", Options.rage_penetration);
        UI::Checkbox("Knifebot", Options.rage_knifebot);
        UI::Checkbox("Zuesbot", Options.rage_zeusbot);
        UI::Checkbox("Resolver", Options.rage_resolver);
        UI::Checkbox("X-Axis", Options.rage_resolverx);
        UI::Checkbox("Z-Axis", Options.rage_resolverz);
        UI::Checkbox("Bruteforce", Options.rage_bruteforce);
        ImGui::SameLine();
        UI::KeyBind(Options.rage_bruteforcekey, Options.rage_bruteforcekeymode);
        UI::Slider("Backtrack", Options.rage_backtrack, 0, 400);
        UI::Checkbox("Hideshots", Options.rage_hideshots);
        ImGui::SameLine();
        UI::KeyBind(Options.rage_hideshotskey, Options.rage_hideshotskeymode);
        UI::Checkbox("Doubletap", Options.rage_doubletap);
        ImGui::SameLine();
        UI::KeyBind(Options.rage_doubletapkey, Options.rage_doubletapkeymode);
        UI::Checkbox("Instant doubletap", Options.rage_doubletapinstant);
        UI::Dropdownmulti("Teleport mode", teleportmode[], Options.rage_teleportmode);
        UI::Checkbox("No recoil", Options.rage_global_norecoil);
        UI::Checkbox("No spread", Options.rage_global_nospread);
        UI::Checkbox("Prepare revolver", Options.rage_revolverprep);
        UI::Checkbox("No scope prediction", Options.rage_noscope);
        UI::Checkbox("Damage override", Options.rage_damageoverride);
        ImGui::SameLine();
        UI::KeyBind(Options.rage_damageoverridekey, Options.rage_damageoverridekeymode);
        UI::Checkbox("Spasm lock", Options.rage_spasmlock);
    }
    ImGui::EndChild();

    if (activeragesubtab == 0) {
        const char* defaulthitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* defaulmultipointthitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        ImGui::SetCursorPos(ImVec2(515, 61));
        ImGui::BeginChild("##Default", ImVec2(354, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Slider("Hitchance", Options.rage_default_hitchance, 0, 100);
            UI::Dropdownmulti("Hitboxes", defaulthitboxes[], Options.rage_default_hitboxes);
            UI::Dropdownmulti("Multipoint", defaulmultipointthitboxes[], Options.rage_default_multipoint);
            UI::Slider("Min damage(Ocluded)", Options.rage_default_mindmgocluded, 0, 100);
            UI::Slider("Min damage(Visible)", Options.rage_default_mindmgvisible, 0, 100);
            UI::Slider("Delay", Options.rage_default_delay, 0, 1000);
            UI::Checkbox("Force body", Options.rage_default_forcebody);
            UI::Checkbox("Force head", Options.rage_default_forcehead);
            UI::Checkbox("Force accuracy", Options.rage_default_forceaccuracy);
            UI::Checkbox("Shoot in air", Options.rage_default_inair); //override all and focus on shots
            UI::Slider("Damage override", Options.rage_default_dmgoverride, 0, 100);
        }
        ImGui::EndChild();
    }

    if (activeragesubtab == 1) {
        const char* pistolhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* pistolmultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        ImGui::SetCursorPos(ImVec2(515, 61));
        ImGui::BeginChild("##Pistol", ImVec2(354, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Slider("Hitchance", Options.rage_pistol_hitchance, 0, 100);
            UI::Dropdownmulti("Hitboxes", pistolhitboxes[], Options.rage_pistol_hitboxes);
            UI::Dropdownmulti("Multipoint", pistolmultipointthitboxes[], Options.rage_pistol_multipoint);
            UI::Slider("Min damage(Ocluded)", Options.rage_pistol_mindmgocluded, 0, 100);
            UI::Slider("Min damage(Visible)", Options.rage_pistol_mindmgvisible, 0, 100);
            UI::Slider("Delay", Options.rage_pistol_delay, 0, 1000);
            UI::Checkbox("Force body", Options.rage_pistol_forcebody);
            UI::Checkbox("Force head", Options.rage_pistol_forcehead);
            UI::Checkbox("Force accuracy", Options.rage_pistol_forceaccuracy);
            UI::Checkbox("Shoot in air", Options.rage_pistol_inair);
            UI::Slider("Damage override", Options.rage_pistol_dmgoverride, 0, 100);
        }
        ImGui::EndChild();
    }

    if (activeragesubtab == 2) {
        const char* awphitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* awpmultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        ImGui::SetCursorPos(ImVec2(515, 61));
        ImGui::BeginChild("##Awp", ImVec2(354, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Slider("Hitchance", Options.rage_awp_hitchance, 0, 100);
            UI::Dropdownmulti("Hitboxes", awphitboxes[], Options.rage_awp_hitboxes);
            UI::Dropdownmulti("Multipoint", awpmultipointthitboxes[], Options.rage_awp_multipoint);
            UI::Slider("Min damage(Ocluded)", Options.rage_awp_mindmgocluded, 0, 100);
            UI::Slider("Min damage(Visible)", Options.rage_awp_mindmgvisible, 0, 100);
            UI::Slider("Delay", Options.rage_awp_delay, 0, 1000);
            UI::Checkbox("Force body", Options.rage_awp_forcebody);
            UI::Checkbox("Force head", Options.rage_awp_forcehead);
            UI::Checkbox("Force accuracy", Options.rage_awp_forceaccuracy);
            UI::Checkbox("Shoot in air", Options.rage_awp_inair);
            UI::Slider("Damage override", Options.rage_awp_dmgoverride, 0, 100);
        }
        ImGui::EndChild();
    }

    if (activeragesubtab == 3) {
        const char* scouthitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* scoutmultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        ImGui::SetCursorPos(ImVec2(515, 61));
        ImGui::BeginChild("##Scout", ImVec2(354, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Slider("Hitchance", Options.rage_scout_hitchance, 0, 100);
            UI::Dropdownmulti("Hitboxes", scouthitboxes[], Options.rage_scout_hitboxes);
            UI::Dropdownmulti("Multipoint", scoutmultipointthitboxes[], Options.rage_scout_multipoint);
            UI::Slider("Min damage(Ocluded)", Options.rage_scout_mindmgocluded, 0, 100);
            UI::Slider("Min damage(Visible)", Options.rage_scout_mindmgvisible, 0, 100);
            UI::Slider("Delay", Options.rage_scout_delay, 0, 1000);
            UI::Checkbox("Force body", Options.rage_scout_forcebody);
            UI::Checkbox("Force head", Options.rage_scout_forcehead);
            UI::Checkbox("Force accuracy", Options.rage_scout_forceaccuracy);
            UI::Checkbox("Shoot in air", Options.rage_scout_inair);
            UI::Slider("Damage override", Options.rage_scout_dmgoverride, 0, 100);
        }
        ImGui::EndChild();
    }

    if (activeragesubtab == 4) {
        const char* autohitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};
        const char* automultipointhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        ImGui::SetCursorPos(ImVec2(515, 61));
        ImGui::BeginChild("##Auto", ImVec2(354, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Slider("Hitchance", Options.rage_auto_hitchance, 0, 100);
            UI::Dropdownmulti("Hitboxes", autohitboxes[], Options.rage_auto_hitboxes);
            UI::Dropdownmulti("Multipoint", automultipointthitboxes[], Options.rage_auto_multipoint);
            UI::Slider("Min damage(Ocluded)", Options.rage_auto_mindmgocluded, 0, 100);
            UI::Slider("Min damage(Visible)", Options.rage_auto_mindmgvisible, 0, 100);
            UI::Slider("Delay", Options.rage_auto_delay, 0, 1000);
            UI::Checkbox("Force body", Options.rage_auto_forcebody);
            UI::Checkbox("Force head", Options.rage_auto_forcehead);
            UI::Checkbox("Force accuracy", Options.rage_auto_forceaccuracy);
            UI::Checkbox("Shoot in air", Options.rage_auto_inair);
            UI::Slider("Damage override", Options.rage_auto_dmgoverride, 0, 100);
        }
        ImGui::EndChild();
    }
}

if (activetab == 2) {
    static char* espsubtabs[] = {"Enemy", "Team", "Local", "Other"};
    static int activeespsubtab = 0;

    ImGui::SetCursorPos(ImVec2(161, 10));
    ImGui::BeginChild("##SubTabs", ImVec2(708, 44), false, 0); {
        ImGui::SameLine();
        for (int i = 0; i < 4; i++) {
            if (ImGui::Button(espsubtabs[i], ImVec2(708/4, 26))) {
                activeespsubtab = i;
            }
        }
    }
    ImGui::EndChild();

    if (activeespsubtab == 0) {
        const char* boxesp[] = {"Off", "2d", "Cornered 2d", "3d"};
        const char* snaplines[] = {"Off", "Top", "Left", "Right", "Bottom", "Center"}
        const char* enemyflags[] = {"Target", "Resolve Status", "Money", "Armour", "Utility", "Scope", "Reload", "Exploits", "Ping", "Bomb", "Priority", "Location"};
        const char* chamsmaterial[] = {"", ""}; //TODO: add materials

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Enemy", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Checkbox("Enable", Options.esp_enemy_enabled);
            ImGui::SameLine();
            UI::KeyBind(Options.esp_enemy_enabledkey, Options.esp_enemy_enabledkeymode);
            UI::Dropdown("Box", boxesp[], Options.esp_enemy_box);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_boxcolor);
            UI::Dropdown("Snaplines", snaplines[], Options.esp_enemy_snaplines); //red target, white normal
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_snaplinecolor);
            UI::Checkbox("Name", Options.esp_enemy_name);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_namecolor);
            UI::Checkbox("Health", Options.esp_enemy_health);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_healthcolor);
            UI::Checkbox("Ammo", Options.esp_enemy_ammo);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_ammocolor);
            UI::Checkbox("Weapon", Options.esp_enemy_weapon);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_weaponcolor);
            UI::Dropdownmulti("Flags", enemyflags[], Options.esp_enemy_flags);
            UI::Checkbox("Sound", Options.esp_enemy_sound);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_soundcolor);
            UI::Checkbox("Line of sight", Options.esp_enemy_lineofsight);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_lineofsightcolor);
            UI::Checkbox("Skeleton", Options.esp_enemy_skeleton);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_skeletoncolor);
            UI::Checkbox("Outline", Options.esp_enemy_outline);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_outlinecolor);
            UI::Checkbox("Chams (Backtrack)", Options.esp_enemy_chamsbacktrack);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_chamsbacktrackcolor);
            UI::Checkbox("Chams (Occluded)", Options.esp_enemy_chamsoccluded);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_chamsoccludedcolor);
            UI::Dropdown("Chams material (Occluded)", chamsmaterial[], Options.esp_enemy_occludedchamsmaterial);
            UI::Checkbox("Chams (Visible)", Options.esp_enemy_chamsvisible);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_chamsvisiblecolor);
            UI::Dropdown("Chams material (Visible)", chamsmaterial[], Options.esp_enemy_visiblechamsmaterial);
            UI::slider("Chams glow", Options.esp_enemy_chamsglow);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_chamsglowcolor);
            UI::Checkbox("Bullet tracers", Options.esp_enemy_bullettracers);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_enemy_bullettracerscolor);
            UI::Checkbox("Shade flat", Options.esp_enemy_shadeflat);
            UI::Checkbox("Dormant", Options.esp_enemy_dormant);
        }
        ImGui::EndChild();
    }

    if (activeespsubtab == 1) {
        //const char* eeeee[] = {"", "", ""};

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Team", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activeespsubtab == 2) {
        const char* boxesp[] = {"Off", "Normal", "Cornered", "3d"};

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Local", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Checkbox("Enable", Options.esp_local_enabled);
            ImGui::SameLine();
            UI::KeyBind(Options.esp_local_enabledkey, Options.esp_local_enabledkeymode);
            UI::Checkbox("Flat", Options.esp_local_flat);
            UI::Dropdown("Box", boxesp[], Options.esp_local_box);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_boxcolor);
            UI::Checkbox("Name", Options.esp_local_name);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_namecolor);
            UI::Checkbox("Health", Options.esp_local_health);
            UI::Checkbox("Ammo", Options.esp_local_ammo);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_ammocolor);
            UI::Checkbox("Weapon", Options.esp_local_weapon);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_weaponcolor);
            UI::Checkbox("Glow", Options.esp_local_glow);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_glowcolor);
            UI::Checkbox("Skeleton", Options.esp_local_skeleton);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_skeletoncolor);
            UI::Checkbox("Bullet tracers", Options.esp_local_bullettracers);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_bullettracerscolor);
            UI::Slider("Scope blend", Options.esp_local_scopeblend, 0, 100);
            UI::Checkbox("Chams (Backtrack)", Options.esp_local_chamsbacktrack);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_chamsbacktrackcolor);
            UI::Checkbox("Chams", Options.esp_local_chams);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_chamscolor);
            UI::Dropdown("Chams material", chamsmaterial[], Options.esp_enemy_chamsmaterial);
            UI::Checkbox("Chams (Desync)", Options.esp_local_desyncchams);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_desyncchamscolor);
            ImGui::NextColumn();
            UI::Checkbox("Chams (Arms)", Options.esp_local_armchams);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_armchamscolor);
            UI::Dropdown("Chams material (Arms)", chamsmaterial[], Options.esp_enemy_armchamsmaterial);
            UI::Checkbox("Draw original", Options.esp_local_armchamsdraworiginal);
            UI::Checkbox("Chams (Weapon)", Options.esp_local_weaponchams);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_local_weaponchamscolor);
            UI::Dropdown("Chams material (Weapon)", chamsmaterial[], Options.esp_enemy_weaponchamsmaterial);
            UI::Checkbox("Draw original", Options.esp_local_weaponchamsdraworiginal);
        }
        ImGui::EndChild();
    }

    if (activeespsubtab == 3) {
        const char* skybox[] = {"", ""};
        const char* removals[] = {"Scope overlay", "Scope zoom", "View punch", "Aim punch", "Smoke Effects", "Flash Effects", "Fog", "Post Processing", "Arms", "Weapon"};
        const char* droppedweapons[] = {"Text", "Glow", "Icon"};
        const char* bombflags[] = {"State", "Timer", "Location"};
        const char* weaponflags[] = {"Icon", "Text", "Distance", "Ammo"};
        const char* chamsmaterial[] = {"", ""};
        const char* hitsound[] = { "Off", "Ahhh", "Anime moan", "Bell", "Flick", "Metalic", "Minecraft", "Roblox"};
        const char* hiteffect[] = {"Off", "", ""};
        const char* killsound[] = {"Off", "Overwatch (CSGO)", "Overwatch (CSS)", "Techno"};
        const char* killanouncer[] = {"Off", "Quake (Female)", "Quake (Standard)", "Valorant", "Anime"};
        const char* deathsound[] = {"Off", "Ahhh", "Error", "Fail", "Wilhelm"};
        const char* penetrationcrosshair[] = {"Off", "Default", "Circle", "Square"};

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Other", ImVec2(708, 410), false, 0); {
        ImGui::Columns(2, NULL, false);
            UI::Checkbox("Bomb timer", Options.esp_other_bombtimer); //attach to radar curve
            UI::Checkbox("Bomb chams", Options.esp_other_bombchams);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_bombchamscolor);
            UI::Dropdown("Bomb chams material", chamsmaterial[], Options.esp_other_bombchamsmaterial);
            UI::Checkbox("Bomb glow", Options.esp_other_bombglow);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_bombglowcolor);
            UI::Dropdown("Bomb flags", bombflags[], Options.esp_other_bombflags);
            UI::Dropdown("Penetration crosshair", penetrationcrosshair[], Options.esp_other_penetrationcrosshair);
            UI::Checkbox("Full bright", Options.esp_other_fullbright);
            UI::Checkbox("World color", Options.esp_other_worldcolor);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_worldcolorcolor);
            UI::Checkbox("Prop color", Options.esp_other_propcolor);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_propcolorcolor);
            UI::Checkbox("Sky color", Options.esp_other_skycolor);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_skycolorcolor);
            UI::Dropdown("Sky box", skybox[], Options.esp_other_skybox);
            UI::TextBox("Custom", Options.esp_other_customskybox);
            UI::Dropdownmulti("Removals", removals[], Options.esp_other_removals);
            UI::Checkbox("Third person", Options.esp_other_thirdperson);
            ImGui::SameLine();
            UI::KeyBind(Options.esp_other_thirdpersonkey, Options.esp_other_thirdpersonkeymode);
            UI::Slider("Distance", Options.esp_other_thirdpersondistance, 0, 300); 
            UI::Checkbox("On death", Options.esp_other_thirdpersonondeath);
            UI::Checkbox("Disable on nade", Options.esp_other_thirdpersondisablenade);
            UI::Checkbox("Radar hack", Options.esp_other_radarhack);
            UI::Checkbox("Stream proof", Options.esp_other_streamproof);
            UI::Checkbox("OOF arrows", Options.esp_other_oofarrows);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_oofarrowscolor);
            UI::Checkbox("Incendiary tracer", Options.esp_other_incendiarytracer);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_incendiarytracercolor);
            UI::Checkbox("Smoke tracer", Options.esp_other_smoketracer);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_smoketracercolor);
            UI::Checkbox("HE tracer", Options.esp_other_hetracer);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_hetracercolor);
            UI::Checkbox("Flashbang tracer", Options.esp_other_flashbangtracer);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_flashbangtracercolor);
            UI::Checkbox("Decoy tracer", Options.esp_other_decoytracer);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_decoytracercolor);
            UI::Checkbox("Incendiary spread", Options.esp_other_incendiaryspread);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_incendiaryspreadcolor);
            UI::Checkbox("Smoke spread", Options.esp_other_smokespread);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_smokespreadcolor);
            UI::Checkbox("Dropped weapons", Options.esp_other_droppedweapons);
            UI::Dropdown("Weapon flags", weaponflags[], Options.esp_other_droppedweaponflags);
            UI::Checkbox("Chams", Options.esp_other_droppedweaponchams);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_droppedweaponchamscolor);
            UI::Dropdown("Chams material", chamsmaterial[], Options.esp_other_droppedweaponchamsmaterial);
            UI::Checkbox("Glow", Options.esp_other_droppedweaponglow);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_droppedweaponglowcolor);

            //TODO: add crates for dangerzone

            //fov crap here

            UI::Dropdown("Hitsound", hitsound[], Options.esp_other_hitsound);
            UI::Dropdown("Hiteffect", hiteffect[], Options.esp_other_hiteffect);
            UI::Dropdown("Killsound", killsound[], Options.esp_other_killsound);
            UI::Dropdown("Killanouncer", killanouncer[], Options.esp_other_killanouncer);
            UI::Dropdown("Deathsound", deathsound[], Options.esp_other_deathsound);
            UI::Checkbox("Grenade prediction", Options.esp_other_localgrenadeprediction);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_localgrenadepredictiontrailcolor);
            ImGui::SameLine(); 
            UI::ColorPicker(Options.esp_other_localgrenadepredictionbouncecolor);
            UI::Checkbox("Enemy grenade prediction", Options.esp_other_enemygrenadeprediction);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_enemygrenadepredictiontrailcolor);
            ImGui::SameLine();
            UI::ColorPicker(Options.esp_other_enemygrenadepredictionbouncecolor);
            UI::Checkbox("Watermark", Options.esp_other_watermark);
            UI::Checkbox("visualise oneway/wallbang locations", Options.esp_other_visualiseoneway);
            ImGui::SameLine();
            UI::KeyBind(Options.esp_other_visualiseonewaykey, Options.esp_other_visualiseonewaykeymode);
            UI::Checkbox("Hitmarker", Options.esp_other_hitmarker);
        }
        ImGui::EndChild();
    }
}

if (activetab == 3) {
    static char* antiaimsubtabs[] = {"Legit", "Rage", "Scripting"};
    static int activeantiaimsubtab = 0;

    ImGui::SetCursorPos(ImVec2(161, 10));
    ImGui::BeginChild("##SubTabs", ImVec2(708, 44), false, 0); {
        for (int i = 0; i < 3; i++) {
            if (ImGui::Button(antiaimsubtabs[i], ImVec2(708/3, 26))) {
                activeantiaimsubtab = i;
            }
        }
    }
    ImGui::EndChild();

    if (activeantiaimsubtab == 0) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Legit", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activeantiaimsubtab == 1) {
        const char* xaxisanglemode[] = {"Static", "UDZ random", "Fluctuate"};
        const char* xaxisjittermode[] = {"Offset", "Random"};
        const char* yaxisanglemode[] = {"Static", "Spin", "WASD random"};
        const char* yaxisjittermode[] = {"Offset", "Random"};
        const char* desyncside[] = {"Off", "Left", "Right", "Random"};
        const char* freestand[] = {"Off", "Freestand", "Anti-freestand"};
        const char* maxfakelagtriggers[] = {"Standing", "Moving", "In air", "On shot", "On peek", "On damage", "On reload"};

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Rage", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Header("X-Axis");
                UI::Checkbox("Enable", Options.antiaim_rage_xenable);
                UI::Slider("Base angle", Options.antiaim_rage_xbaseangle, -90, 90);
                UI::Dropdown("Angle mode", xaxisanglemode[], Options.antiaim_rage_xanglemode);
                UI::Checkbox("Jitter", Options.antiaim_rage_xjitterenable);
                UI::Doubleslider("Jitter range", Options.antiaim_rage_xjitterrangemin, Options.antiaim_rage_xjitterrangemax, -90, 90);
                UI::Dropdown("Jitter mode", xaxisjittermode[], Options.antiaim_rage_xjittermode);
                
            ImGui::Spacing();

            UI::Header("Y-Axis");
                UI::Checkbox("Enable", Options.antiaim_rage_yenable);
                UI::Slider("Base angle", Options.antiaim_rage_ybaseangle, -180, 180);
                UI::Dropdown("Angle mode", yaxisanglemode[], Options.antiaim_rage_yanglemode);
                UI::Checkbox("Jitter", Options.antiaim_rage_yjitterenable);
                UI::Doubleslider("Jitter range", Options.antiaim_rage_yjitterrangemin, Options.antiaim_rage_yjitterrangemax, -90, 90);
                UI::Dropdown("Jitter mode", yaxisjittermode[], Options.antiaim_rage_yjittermode);

            ImGui::NextColumn();

            UI::Header("Desync");
                UI::Checkbox("Enable", Options.antiaim_rage_desyncenable);
                UI::Dropdown("Desync side", desyncside[], Options.antiaim_rage_desyncside);
                UI::Doubleslider("Desync range", Options.antiaim_rage_desyncrangeleft, Options.antiaim_rage_desyncrangeright, -60, 60);
                UI::Dropdown("Freestand", freestand[], Options.antiaim_rage_desyncfreestand);
                UI::Checkbox("Avoid overlap", Options.antiaim_rage_desyncavoidoverlap);
                UI::Checkbox("Dormant", Options.antiaim_rage_desyncdormant);

            ImGui::Spacing();

            UI::Header("Fakelag");
                UI::Checkbox("Enable", Options.antiaim_rage_fakelagenable);
                UI::Doubleslider("Fakelag range", Options.antiaim_rage_fakelagrangemin, Options.antiaim_rage_fakelagrangemax, 0, 17);
                UI::Dropdown("Max fakelag triggers", maxfakelagtriggers[], Options.antiaim_rage_maxfakelagtriggers);
                UI::Checkbox("Dormant", Options.antiaim_rage_fakelagdormant);

            ImGui::Spacing();

            UI::Header("Other");
                UI::Checkbox("Invert", Options.antiaim_rage_invert);
                ImGui::SameLine();
                UI::KeyBind(Options.antiaim_rage_invertkey, Options.antiaim_rage_invertkeymode);
                UI::Checkbox("Target detection", Options.antiaim_rage_targetdetection);
                UI::Checkbox("Wall detection", Options.antiaim_rage_walldetection);
                UI::Checkbox("Slidewalk", Options.antiaim_rage_slidewalk);
                UI::Checkbox("Fakeduck", Options.antiaim_rage_fakeduck);
                ImGui::SameLine();
                UI::KeyBind(Options.antiaim_rage_fakeduckkey, Options.antiaim_rage_fakeduckkeymode);
                UI::Checkbox("Psuedo crimwalk", Options.antiaim_rage_crimwalk);
                ImGui::SameLine();
                UI::KeyBind(Options.antiaim_rage_crimwalkkey, Options.antiaim_rage_crimwalkkeymode);
                UI::Checkbox("Antibackstab", Options.antiaim_rage_antibackstab);
        }
        ImGui::EndChild();
    }

    if (activeantiaimsubtab == 2) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Scripting", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }
}

if (activetab == 4) {
    static char* modifiersubtabs[] = {"Inventory", "Models", "Unboxing"};
    static int activemodifiersubtab = 0;

    ImGui::SetCursorPos(ImVec2(161, 10));
    ImGui::BeginChild("##SubTabs", ImVec2(708, 44), false, 0); {
        for (int i = 0; i < 3; i++) {
            if (ImGui::Button(modifiersubtabs[i], ImVec2(708/3, 26))) {
                activemodifiersubtab = i;
            }
        }
    }
    ImGui::EndChild();

    if (activemodifiersubtab == 0) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Inventory", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activemodifiersubtab == 1) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Models", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activemodifiersubtab == 2) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Unboxing", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
            //UI::Checkbox("Broadcast unboxings", Options.modifier_unboxing_broadcast); //people in current game will see unboxing messages
        }
        ImGui::EndChild();
    }
}

if (activetab == 5) {
    static char* miscsubtabs[] = {"General", "Scripting", "Players", "Console"};
    static int activemiscsubtab = 0;

    ImGui::SetCursorPos(ImVec2(161, 10));
    ImGui::BeginChild("##SubTabs", ImVec2(708, 44), false, 0); {
        for (int i = 0; i < 3; i++) {
            if (ImGui::Button(miscsubtabs[i], ImVec2(708/4, 26))) {
                activemiscsubtab = i;
            }
        }
    }
    ImGui::EndChild();

    if (activemiscsubtab == 0) {
        const char* forceregion[] = {"Off", "Australia", "Austria", "Brazil", "Chile", "Dubai", "France", "Germany", "Hong Kong", "India(Chennai)", "India(Mumbai)", "Japan", "Luxembourg", "The Nether", "Peru", "Phillipines", "Poland", "Singapore", "No Water", "Spain", "Sweden", "United Kingdom", "USA(Atlanta)", "USA(Chicago)", "USA(Los Angeles)", "USA(Moses Lake)", "USA(Oklahoma)", "USA(Seattle)", "USA(Washington DC)"};
        const char* namechanger[] = {"Off", "Team-Only", "Enemy-Only", "Everyone", "Corrupt"};
        const char* informationspammer[] = {"Name", "Rank", "Weapon", "Location", "Health"};
        const char* buybotprimary[] = {"Off", "Auto", "Scout", "AWP", "Ak/M4"};
        const char* buybotsecondary[] = {"Off", "Dual-Berettas", "P250", "Five7/Tec9", "Deagle/R8"};
        const char* buybotnades[] = {"Smoke", "Flash", "Incendiary", "Decoy", "HE Grenade"};
        const char* buybotother[] = {"Kevlar", "Helmet", "Defuser", "Taser", "Riot Sheild"};

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##General", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            UI::Checkbox("Auto-accept", Options.misc_general_autoaccept);
            UI::Checkbox("Auto-pistol", Options.misc_general_autopisol);
            UI::Slider("Delay", Options.misc_general_autopistoldelay, 0, 1000);
            UI::Checkbox("Preserve killfeed", Options.misc_general_preservekillfeed);
            UI::Checkbox("Auto-defuse", Options.misc_general_autodefuse);
            UI::Checkbox("Auto-extinguish incendiarys", Options.misc_general_autoextinguishincendiarys);
            UI::Checkbox("Fakeping", Options.misc_general_fakeping)
            UI::Slider("Fakeping amount", Options.misc_general_fakepingamount, 0, 1000);
            UI::Checkbox("Clantag", Options.misc_general_clantag);
            UI::Checkbox("Block bot", Options.misc_general_blockbot);
            ImGui::SameLine();
            UI::KeyBind(Options.misc_general_blockbotkey, Options.misc_general_blockbotkeymode);
            UI::Checkbox("Headstand bot", Options.misc_general_headstandbot);
            ImGui::SameLine();
            UI::KeyBind(Options.misc_general_headstandbotkey, Options.misc_general_headstandbotkeymode);
            UI::Dropdown("Force region", forceregion[], Options.misc_general_forceregion);
            UI::Checkbox("Reveal overwatch", Options.misc_general_revealoverwatch);
            UI::Checkbox("Reveal ranks", Options.misc_general_revealranks);
            UI::Checkbox("Slowwalk", Options.misc_general_slowwalk);
            UI::Slider("Speed", Options.misc_general_slowwalkspeed, 0, 100);
            UI::Checkbox("Anti-untrusted", Options.misc_general_antiuntrusted);
            UI::Checkbox("Bypass sv_pure", Options.misc_general_bypasssvpure);
            UI::Checkbox("Infinite duck", Options.misc_general_infiniteduck);
            UI::Checkbox("Quick stop", Options.misc_general_quickstop);
            UI::Checkbox("Unlock inventory", Options.misc_general_unlockinventory);
            UI::Dropdown("Namechanger", namechanger[], Options.misc_general_namechanger);
            UI::Textbox("Command spammer", Options.misc_general_commandspammer);
            UI::Dropdown("Information spammer", informationspammer[], Options.misc_general_informationspammer);
            UI::Checkbox("Grenade helper", Options.misc_general_grenadehelper);
            ImGui::SameLine();
            UI::KeyBind(Options.misc_general_grenadehelpervisiblekey, Options.misc_general_grenadehelpervisiblekeymode);
            ImGui::SameLine();
            UI::KeyBind(Options.misc_general_grenadehelperexecutekey, Options.misc_general_grenadehelperexecutekeymode);
            UI::Checkbox("Visible when grenade equip", Options.misc_general_grenadehelpervwge);
            UI::Checkbox("Bunnyhop", Options.misc_general_bhop);
            UI::Slider("Hitchance", Options.misc_general_bhophitchance, 0, 100);
            UI::Checkbox("Random", Options.misc_general_bhophitchancerandom);
            UI::Checkbox("Auto strafe", Options.misc_general_autostrafe);
            UI::Checkbox("Aircrouch", Options.misc_general_aircrouch);
            UI::Checkbox("Peek assist", Options.misc_general_peekassist);
            ImGui::SameLine();
            UI::KeyBind(Options.misc_general_peekassistkey, Options.misc_general_peekassistkeymode);
            UI::Header("Buybot");
            UI::Checkbox("Enable buybot", Options.misc_buybot_enable);
            UI::Dropdown("Primary", buybotprimary[], Options.misc_buybot_primary);
            UI::Dropdown("Secondary", buybotsecondary[], Options.misc_buybot_secondary);
            UI::Dropdown("Nades", buybotnades[], Options.misc_buybot_nades);
            UI::Dropdown("Other", buybotother[], Options.misc_buybot_other);
            ImGui::Button("Trigger ban", ImVec2(276, 30), Options.misc_general_triggerban);
            ImGui::Button("Unlock achievements", ImVec2(276, 30), Options.misc_general_unlockachievements);
            ImGui::Button("Unload", ImVec2(276, 30), Options.misc_general_unload);

            UI::Header("Configuration");
            //config list
            ImGui::BeginListBox();
    
            ImGui::EndListBox();
            UI::Textbox("Name", Options.config_name);
            ImGui::Button("Create", ImVec2(276, 30), Options.config_create);
            ImGui::Button("Save", ImVec2(276, 30), Options.config_save);
            ImGui::Button("Load", ImVec2(276, 30), Options.config_load);
            ImGui::Button("Delete", ImVec2(276, 30), Options.config_delete);
            ImGui::Button("Reset", ImVec2(276, 30), Options.config_reset);
            ImGui::Button("Refresh", ImVec2(276, 30), Options.config_refresh);
        }
        ImGui::EndChild();
    }

    if (activemiscsubtab == 1) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Scripting", ImVec2(708, 410), false, 0); {
            ImGui::Columns(2, NULL, false);
            ImGui::Text("Unavailable");
        }
        ImGui::EndChild();
    }

    if (activemiscsubtab == 2) { //GOTV = null
        const char* playerhitboxes[] = {"Head", "Chest", "Body", "Arms", "Legs"};

        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Players", ImVec2(708, 410), false, 0); {
            
            UI::Checkbox("Enable", Options.misc_player_enable);
            //player list

            //options
            UI::Header("Options");
            ImGui::Button("Steal name", ImVec2(276, 30), PlayerOptions.stealname);
            ImGui::Button("Copy clantag", ImVec2(276, 30), PlayerOptions.copyclantag);
            UI::Checkbox("Priority", PlayerOptions.priority);
            UI::Checkbox("Whitelist", PlayerOptions.whitelist); //dont shoot
            UI::Checkbox("Rage", PlayerOptions.set_rage);
            UI::Checkbox("Legit", PlayerOptions.set_legit);
            UI::Checkbox("Follow", PlayerOptions.follow);
            UI::Dropdown("Force hitboxes", playerhitboxes[], PlayerOptions.forcehitboxes);
            UI::Checkbox("Force head", PlayerOptions.forcehead);
            UI::Checkbox("Force body", PlayerOptions.forcebody);
            UI::Checkbox("Dont resolve", PlayerOptions.dontresolve);
            ImGui::Button("Reset options", ImVec2(276, 30), PlayerOptions.resetoptions);
        }
        ImGui::EndChild();
    }

    if (activemiscsubtab == 3) {
        ImGui::SetCursorPos(ImVec2(161, 61));
        ImGui::BeginChild("##Console", ImVec2(708, 410), false, 0); {
            //text

            //input line
        }
        ImGui::EndChild();
    }
}