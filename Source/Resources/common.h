#pragma once

//   CREDITS TO Sergey Fursa/qo0	//
//       for the cheat base         //
//                       ____       //
//       ______  ____   / __ \      //
//      / __  / / __ \ / / / /      //
//     / /_/ / / /_/ // /_/ /       //
//     \__  /  \____/ \____/        //
//       /_/ CHEAT BASE				//


#include <windows.h>

#include <d3d9.h>
#include "Utils/d3dx9.h" //Temp fix
//#include <d3dx9.h> //wont locate yay

//https://github.com/ocornut/imgui
#include "../Source/Resources/Imgui/imgui.h"
#include "../Source/Resources/Imgui/imgui_freetype.h"

#include "../Source/Resources/Imgui/imgui_internal.h"
#include "../Source/Resources/Imgui/Impl/imgui_impl_dx9.h"
#include "../Source/Resources/Imgui/Impl/imgui_impl_win32.h"

//https://github.com/fmtlib/fmt/
#define FMT_HEADER_ONLY
#include "../Source/Resources/FMT/format.h"
#include "../Source/Resources/FMT/chrono.h"

using namespace std::chrono_literals;

#include "../Source/Resources/Utils/xorstr.h"
//https://github.com/JustasMasiulis/lazy_importer

#include "../Source/Resources/Utils/memory.h"