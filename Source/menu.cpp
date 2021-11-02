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

/* Legit interactives
Imgui::Checkbox("Enable", g_Options.enable_legit_aimbot);
Imgui::SliderFloat("FOV", g_Options.aimbot_fov, 0.0f, 90.0f); //90d aimbot
ImGui::CHeckbox("Use rectangle FOV", g_Options.aimbot_fov_rectangular);
*/

//Incomplete

