#include "menu.hpp"
#define  NOMINMAX
#include <Windows.h>
//#include <chrono>

#include "Resources/Sdk/csgostructs.hpp"
#include "Resources/Helpers/input.hpp"
#include "options.hpp"
#include "config.hpp"

//imgui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "Resources/Imgui/imgui_internal.h"
#include "Resources/Imgui/Impl/imgui_impl_dx9.h"
#include "Resources/Imgui/Impl/imgui_impl_win32.h"

//Menu style
#define WINDOW_WIDTH 820
#define	WINDOW_HEIGHT 650

//Sidebar tabs
static char* sidebar_tabs[] = {
	"LEGIT",
	"RAGE",
	"ANTIAIM",
	"VISUALS",
	"SKINCHANGER",
	"MISC"
};

constexpr static float get_sidebar_item_width() { return 0.0f; } //150.0f
constexpr static float get_sidebar_item_height() { return 0.0f; } //50.0f

enum {
	TAB_LEGIT,
	TAB_RAGE,
	TAB_ANTIAIM,
	TAB_VISUALS,
	TAB_SKINCHANGER,
	TAB_MISC
};

/* IMGUI CMD LINES 
Slider Float 	- Imgui::SliderFloat("TITLE", g_Options.NAME_NAME, 0.0f, 150.0f);
Slider INT	- Imgui::SliderInt("TITLE", g_Options.NAME_NAME, 0, 0);
Checkbox 	- ImGui::Checkbox("TITLE", g_Options.NAME_NAME);
Colour select 	- ImGuiEx::ColorEdit3("TITLE", g_Options.NAME_NAME);
*/

//Aimbot general TODO add individual weapon configs
Imgui::Checkbox("Enable", g_Options.legit_aim_enable); //Add on key
ImGui::Checkbox("Magnet", g_Options.legit_aim_magnet);
ImGui::Checkbox("Aimlock", g_Options.legit_aim_aimlock);
ImGui::SliderFloat("Hitchance", g_Options.legit_aim_hitchance, 0.0f, 100.0f);
ImGui::Checkbox("Silent", g_Options.legit_aim_silent);
Imgui::SliderFloat("FOV", g_Options.legit_aim_fov, 0.0f, 90.0f); //90d aimbot
ImGui::SliderFloat("Distant FOV", g_Options.legit_aim_distant_fov, 0.0f, 90.0f);
ImGui::Checkbox("Rectangle FOV", g_Options.legit_aim_rectangular);
ImGui::SliderFloat("Strength", g_Options.legit_aim_strength, 0.0f, 100.0f);
ImGui::SliderFloat("Speed(X)", g_Options.legit_aim_speed_x, 0.0f, 100.0f);
ImGui::SliderFloat("Speed(Y)", g_Options.legit_aim_speed_y, 0.0f, 100.0f);
ImGui::SliderFloat("Delay(ms)", g_Options.legit_aim_delay, 0.0f, 1000.0f);
ImGui::Checkbox("Auto stop", g_Options.legit_aim_auto_stop);
ImGui::Checkbox("Auto fire", g_Options.legit_aim_auto_fire);
ImGui::Checkbox("Wall penetration", g_Options.legit_aim_wall_penetration);
ImGui::Checkbox("Smoke check", g_Options.legit_aim_smoke_check);
ImGui::Checkbox("Flash check", g_Options.legit_aim_flash_check);
ImGui::Checkbox("Jump check", g_Options.legit_aim_jump_check);
ImGui::Checkbox("Enable backtrack", g_Options.legit_aim_backtrack_enable);
ImGui::SliderFloat("Backtrack amount(ms)", g_Options.legit_aim_backtrack_amount, 0.0f, 200.0f););
ImGui::Checkbox("Friendly fire", g_Options.legit_aim_friendly_fire);

//Triggerbot
ImGui::Checkbox("Enable", g_Options.legit_trigger_enable);
ImGui::SliderFloat("Hitchance", g_Options.legit_trigger_hitchance, 0.0f, 100.0f);
ImGui::SliderFloat("Delay(ms)", g_Options.legit_trigger_delay, 0.0f, 1000.0f);
ImGui::Checkbox("Auto stop", g_Options.legit_trigger_auto_stop);
ImGui::Checkbox("Wall penetration", g_Options.legit_trigger_wall_penetration);
ImGui::Checkbox("Smoke check", g_Options.legit_trigger_smoke_check);
ImGui::Checkbox("Flash check", g_Options.legit_trigger_flash_check);
ImGui::Checkbox("Jump check", g_Options.legit_trigger_jump_check);


//RCS
ImGui::Checkbox("Recoil control", g_Options.legit_rcs_enable);
ImGui::SliderFloat("Control after", g_Options.legit_rcs_delay, 0.0f, 10.0f); //Shots
ImGui::SliderFloat("X-axis", g_Options.legit_rcs_control_x, 0.0f, 100.0f);
ImGui::SliderFloat("Y-axis", g_Options.legit_rcs_control_y, 0.0f, 100.0f);


//Incomplete

