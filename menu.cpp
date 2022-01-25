#include "menu.h"
#define NOMINMAX
#include <Windows.h>
#include <chrono>
#include "global.h"
#include "config.h"
#include "options.h"
#include "interfaces.h"
#include "Resources/Utils/draw.h"
#include "Resources/Utils/logging.h"

//Imgui crap
#define IMGUI_MATH_OPERATORS
#include "Resources/Imgui/imgui_stdlib.h"
#include "Resources/Imgui/imgui_internal.h"
#include "Resources/Imgui/Impl/imgui_impl_dx9.h"
#include "Resources/Imgui/Impl/imgui_impl_win32.h"

/*
visuals.h
skinchanger.h
*/

static char* sidebar_tabs[] = {
	"LEGIT",
	"RAGE",
	"VISUAL",
	"SHRUG",
	"MISC"
};

constexpr static float get_sidebar_item_width() { return 200.0f; }
constexpr static float get_sidebar_item_height() { return  80.0f; }

enum {
	TAB_LEGIT,
	TAB_RAGE,
	TAB_VISUAL,
	TAB_SHRUG,
	TAB_MISC
};

namespace ImGuiEx
{
    inline bool ColorEdit4(const char* label, Color* v, bool show_alpha = true)
    {
        auto clr = ImVec4{
            v->r() / 255.0f,
            v->g() / 255.0f,
            v->b() / 255.0f,
            v->a() / 255.0f
        };

        if (ImGui::ColorEdit4(label, &clr.x, show_alpha)) {
            v->SetColor(clr.x, clr.y, clr.z, clr.w);
            return true;
        }
        return false;
    }
    inline bool ColorEdit3(const char* label, Color* v)
    {
        return ColorEdit4(label, v, false);
    }
}

template<size_t N>
void render_tabs(char* (&names)[N], int& activetab, float w, float h, bool sameline)
{
    bool values[N] = { false };

    values[activetab] = true;

    for (auto i = 0; i < N; ++i) {
        if (ImGui::ToggleButton(names[i], &values[i], ImVec2{ w, h })) {
            activetab = i;
        }
        if (sameline && i < N - 1)
            ImGui::SameLine();
    }
}

ImVec2 get_sidebar_size()
{
    constexpr float padding = 10.0f;
    constexpr auto size_w = padding * 2.0f + get_sidebar_item_width();
    constexpr auto size_h = padding * 2.0f + (sizeof(sidebar_tabs) / sizeof(char*)) * get_sidebar_item_height();

    return ImVec2{ size_w, ImMax(325.0f, size_h) };
}

void RenderLegitTab() //Legit tab
{
    static char* legit_tab_names[] = { "GENERAL", "TRIGGERBOT", "RCS" };
    static int   active_legit_tab = 0;

    bool placeholder_true = true;

    auto& style = ImGui::GetStyle();
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    {
        render_tabs(legit_tab_names, active_legit_tab, group_w / _countof(legit_tab_names), 25.0f, true);
    }
    ImGui::PopStyleVar();
    ImGui::BeginGroupBox("##body_content");
    {
        if (active_legit_tab == 0) { //General
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);

            //ImGui::SliderInt("", g_Options., 0, 100);
            //ImGui::Checkbox("", g_Options.);

            ImGui::Checkbox("Enable", g_Options.legit_enabled); //Add on key

            const char* items[] = { "Head", "Chest", "Stomach", "Pelvis", "Arms", "Legs", "Feet" }
            static const char* current_item = NULL;

            if (ImGui::BeginCombo("Hitbox", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n])
                        if (ImGui::Selectable(items[n], is_selected)
                            current_item = items[n];
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            const char* items[] = { "Closest", "Body", "Head", "MostDamage" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Priority", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

            ImGui::SliderInt("FOV", g_Options.legit_fov, 0, 90);
            ImGui::SliderInt("DistantFOV", g_Options.legit_distantfov, 0, 30); 
            ImGui::SliderInt("HitChance", g_Options.legit_hitchance, 0, 100);
            ImGui::SliderInt("InAirHitChance", g_Options.legit_inairhitchance, 0, 100);
            ImGui::SliderInt("MinDamage", g_Options.legit_mindamage, 0, 100);
            ImGui::SliderInt("SwitchTargetSpeed", g_Options.legit_switchtargetspeed, 0, 100);
            ImGui::SliderInt("Reaction Time", g_Options.legit_reactiontime, 0, 1000);
            ImGui::SliderInt("MissShots", g_Options.legit_missshots, 0, 8);
            ImGui::Checkbox("FriendlyFire", g_Options.legit_friendlyfire);
            ImGui::Checkbox("SmokeCheck", g_Options.legit_smokecheck);
            ImGui::Checkbox("MolotovCheck", g_Options.legit_molotovcheck);
            ImGui::Checkbox("FlashCheck", g_Options.legit_flashcheck);
            ImGui::Checkbox("JumpCheck", g_Options.legit_jumpcheck);
            ImGui::SliderInt("Strength", g_Options.legit_strength, 0, 100);
            ImGui::Checkbox("AutoShoot", g_Options.legit_autoshoot);
            ImGui::Checkbox("AutoScope", g_Options.legit_autoscope);
            ImGui::Checkbox("AutoStop", g_Options.legit_autostop);
            ImGui::Checkbox("Resolver", g_Options.legit_resolver);
            ImGui::SliderInt("Smooth", g_Options.legit_smooth, 0, 100);
            ImGui::Checkbox("EnableBacktrack", g_Options.legit_enablebacktrack);
            ImGui::SliderInt("BacktrackAmmount", g_Options.legit_backtrackammount, 0, 200); //ms
        }
        else if (active_legit_tab == 1) { //Triggerbot
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);

            ImGui::Checkbox("Enable", g_Options.trigger_enable);

            const char* items[] = { "Head", "Chest", "Stomach", "Pelvis", "Arms", "Legs", "Feet" }
            static const char* current_item = NULL;

            if (ImGui::BeginCombo("Hitbox", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n])
                        if (ImGui::Selectable(items[n], is_selected)
                            current_item = items[n];
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::Checkbox("FriendlyFire", g_Options.trigger_friendlyfire);
            ImGui::Checkbox("TeamCheck", g_Options.trigger_teamcheck);
            ImGui::Checkbox("SmokeCheck", g_Options.trigger_smokecheck);
            ImGui::Checkbox("MolotovCheck", g_Options.trigger_molotovcheck);
            ImGui::Checkbox("FlashCkeck", g_Options.trigger_flashcheck);
            ImGui::Checkbox("JumpCheck", g_Options.trigger_jumpcheck);
            ImGui::SliderInt("HitChance", g_Options.trigger_hitchance, 0, 100);
            ImGui::SliderInt("InAirHitChance", g_Options.trigger_inairhitchance, 0, 100);
            ImGui::SliderInt("MinDamage", g_Options.trigger_mindamage, 0, 100);
            ImGui::SliderInt("ReactionTime", g_Options.trigger_rectiontime, 0, 1000);
        }
        else if (active_legit_tab == 2) { //RCS(Recoil Control System)
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);

            ImGui::Checkbox("Enable", g_Options.rcs_enable);

            const char* items[] = { "Methyl", "Ethyl", "Propyl" } //Making three methods will brainfuck me
            static const char* current_item = NULL;

            if (ImGui::BeginCombo("Method", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n])
                        if (ImGui::Selectable(items[n], is_selected)
                            current_item = items[n];
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::SliderInt("X-Axis", g_Options.rcs_xaxis, 0, 100);
            ImGui::SliderInt("Y-Axis", g_Options.rcs_yaxis, 0, 100);
        }
        ImGui::EndGroupBox();

        ImGui::Columns(1, nullptr, false);
        ImGui::PopStyleVar();
        }
    }
    ImGui::EndGroupBox();
}

void RenderRageTab() //Rage tab
{
    static char* rage_tab_names[] = { "General", "", "" };
    static int   active_rage_tab = 0;

    bool placeholder_true = true;

    auto& style = ImGui::GetStyle();
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    {
        render_tabs(rage_tab_names, active_rage_tab, group_w / _countof(rage_tab_names), 25.0f, true);
    }
    ImGui::PopStyleVar();
    ImGui::BeginGroupBox("##body_content");
    {
        if (active_rage_tab == 0) { //General
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);
        }
        else if (active_rage_tab == 1) {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);
        }
        else if (active_rage_tab == 2) {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);
        }
        ImGui::EndGroupBox();

        ImGui::Columns(1, nullptr, false);
        ImGui::PopStyleVar();
    }
}
ImGui::EndGroupBox();
}

void RenderAntiaimTab() //Antiaim tab
{
    static char* antiaim_tab_names[] = { "Legit", "Rage", "Scripting" };
    static int   active_antiaim_tab = 0;

    bool placeholder_true = true;

    auto& style = ImGui::GetStyle();
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    {
        render_tabs(antiaim_tab_names, active_antiaim_tab, group_w / _countof(antiaim_tab_names), 25.0f, true);
    }
    ImGui::PopStyleVar();
    ImGui::BeginGroupBox("##body_content");
    {
        if (active_antiaim_tab == 0) { //Legit AA
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);

            ImGui::Checkbox("Enable", g_Options.);
            ImGui::SliderInt("Desync", g_Options., 0, 60);
            ImGui::SliderInt("Jitter", g_Options., 0, 100);
            ImGui::SliderInt("Jitter Range", g_Options., -180, 180);
        }
        else if (active_antiaim_tab == 1) { //Rage AA
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);

            ImGui::Checkbox("Enable", g_Options.);
            const char* items[] = { "Low-Delta", "Extended", "Random", "Spinbot" }
            static const char* current_item = NULL;

            if (ImGui::BeginCombo("Preset", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n])
                        if (ImGui::Selectable(items[n], is_selected)
                            current_item = items[n];
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::SliderInt("Y-Axis", g_Options., -90, 90);
            ImGui::SliderInt("Z-Axis", g_Options., -180, 180);
            const char* items[] = { "Static", "Spin" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Z-Axis mode", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            ImGui::Checkbox("Desync", g_Options.);
            const char* items[] = { "Left", "Right" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Desync Angle", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            ImGui::SliderInt("Ammount", g_Options., 0, 60);
            ImGui::Checkbox("Invert", g_Options.); //Add on key
            ImGui::SliderInt("Jitter", g_Options., 0, 100);
            ImGui::SliderInt("Jitter Range", g_Options., -180, 180);
            ImGui::Checkbox("Fake Lag", g_Options.);
            ImGui::SliderInt("Min", g_Options., 0, 12 );
            ImGui::SliderInt("Max", g_Options., 0, 12 );
            const char* items[] = { "Dormant", "Velocity-Change", "In-Air", "Peek" }
            static const char* current_item = NULL;

            if (ImGui::BeginCombo("Triggers", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n])
                        if (ImGui::Selectable(items[n], is_selected)
                            current_item = items[n];
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
        else if (active_antiaim_tab == 2) { //Scripting
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(3, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, group_w);

            ImGui::Text("Unavailable");
        } 
        ImGui::EndGroupBox();

        ImGui::Columns(1, nullptr, false);
        ImGui::PopStyleVar();
    }
}
ImGui::EndGroupBox();
}

void RenderVisualTab() //Visual tab
{
    static char* visual_tab_names[] = { "Player", "Team", "Enemy", "World" };
    static int   active_visual_tab = 0;

    bool placeholder_true = true;

    auto& style = ImGui::GetStyle();
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    {
        render_tabs(visual_tab_names, active_visual_tab, group_w / _countof(visual_tab_names), 25.0f, true);
    }
    ImGui::PopStyleVar();
    ImGui::BeginGroupBox("##body_content");
    {
        if (active_visual_tab == 0) { //Player
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);
        }
        else if (active_visual_tab == 1) { //Team
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);
        }
        else if (active_visual_tab == 2) { //Enemy
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);
        }
        else if (active_visual_tab == 3) { //World
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);
        }
        ImGui::EndGroupBox();

        ImGui::Columns(1, nullptr, false);
        ImGui::PopStyleVar();
    }
}
ImGui::EndGroupBox();
}

void RenderShrugTab() //Shrug tab
{
    static char* shrug_tab_names[] = { "InventoryChanger", "ModelChanger" };
    static int   active_shrug_tab = 0;

    bool placeholder_true = true;

    auto& style = ImGui::GetStyle();
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    {
        render_tabs(shrug_tab_names, active_shrug_tab, group_w / _countof(shrug_tab_names), 25.0f, true);
    }
    ImGui::PopStyleVar();
    ImGui::BeginGroupBox("##body_content");
    {
        if (active_shrug_tab == 0) { //InventoryChanger
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, group_w);
        }
        else if (active_shrug_tab == 1) { //ModelChanger
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, group_w);
        }
        ImGui::EndGroupBox();

        ImGui::Columns(1, nullptr, false);
        ImGui::PopStyleVar();
    }
}
ImGui::EndGroupBox();
}

void RenderMiscTab() //Misc tab
{
    static char* misc_tab_names[] = { "General", "Players", "Scripting", "Console" };
    static int   active_misc_tab = 0;

    bool placeholder_true = true;

    auto& style = ImGui::GetStyle();
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    {
        render_tabs(misc_tab_names, active_misc_tab, group_w / _countof(misc_tab_names), 25.0f, true);
    }
    ImGui::PopStyleVar();
    ImGui::BeginGroupBox("##body_content");
    {
        if (active_misc_tab == 0) { //General
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);

            ImGui::Checkbox("Name-Steal", g_Options.);
            ImGui::Checkbox("Slide-Walk", g_Options.);
            ImGui::Checkbox("Bhop", g_Options.);
            ImGui::SliderInt("Miss Ratio", g_Options., 0, 10);
            const char* items[] = { "Legit", "Rage", "Directional" }
            static const char* current_item = NULL;

            if (ImGui::BeginCombo("Method", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n])
                        if (ImGui::Selectable(items[n], is_selected)
                            current_item = items[n];
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::Checkbox("Auto-Accept", g_Options.);
            ImGui::Checkbox("Clantag", g_Options.);
            const char* items[] = { "Aimwhere", "Notap", "Afinity", "Gamefence" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Tag", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            ImGui::Checkbox("Auto-Fire", g_Options.);
            ImGui::Checkbox("Infinite-Duck", g_Options.);
            ImGui::Checkbox("Quick-Stop", g_Options.);
            ImGui::Checkbox("Buy-Bot", g_Options.);
            const char* items[] = { "Auto", "Scout", "Awp", "Ak/M4" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Primary", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            const char* items[] = { "Deagle/R8", "Dual", "P250", "Five7/Tec9" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Secondary", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            const char* items[] = { "Smoke", "Grenade", "Molotov", "Flashbang", "Decoy" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Util", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            const char* items[] = { "Kevlar", "Helmet", "Diffuser", "Taser" }
            static const char* current_item = NULL;

                if (ImGui::BeginCombo("Equipment", current_item))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item == items[n])
                            if (ImGui::Selectable(items[n], is_selected)
                                current_item = items[n];
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
        }
        else if (active_misc_tab == 1) { //Players
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);

            ImGui::Text("Unavailable");
        }
        else if (active_misc_tab == 2) { //Scripting
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);

            ImGui::Text("Unavailable");
        }
        else if (active_misc_tab == 3) { //Console
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
            ImGui::Columns(4, nullptr, false);
            ImGui::SetColumnOffset(1, group_w / 3.0f);
            ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
            ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);
            ImGui::SetColumnOffset(4, group_w);

            ImGui::Text("Unavailable");
        }
        ImGui::EndGroupBox();

        ImGui::Columns(1, nullptr, false);
        ImGui::PopStyleVar();
    }
}
ImGui::EndGroupBox();
}