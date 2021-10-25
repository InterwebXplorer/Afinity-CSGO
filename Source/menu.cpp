#include "menu.hpp"
#define  NOMINMAX
#include <Windows.h>
//#include <chrono>

#include "Resources/Sdk/csgostructs.hpp"
#include "Resources/Helpers/input.hpp"
#include "options.hpp"
//#include "ui.hpp"
#include "configuration.hpp"

//imgui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "Resources/Imgui/imgui_internal.h"
#include "Resources/Imgui/Impl/imgui_impl_dx9.h"
#include "Resources/Imgui/Impl/imgui_impl_win32.h"

//Menu style
#define WINDOW_WIDTH 800 //575
#define	WINDOW_HEIGHT 600 //510/507

/*====================================================================
							Sidebar tabs
====================================================================*/
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

//INCOMPLETE