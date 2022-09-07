#pragma once
#include <functional>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resources/imgui/imgui.h"
#include "resources/imgui/imgui_freetype.h"
#include "resources/imgui/imgui_internal.h"
#include "resources/imgui/impl/imgui_impl_dx9.h"
#include "resources/imgui/impl/imgui_impl_win32.h"

namespace Window {
    void MainWindow(IDirect3DDevice9* pDevice);

    inline bool menuopen = false;
    inline int sidebar_tab_index = 0;
}

namespace Tabs {
    void RenderMenu(bool menuopen, int& activetab);

    void RenderLegitTab();
    void RenderRageTab();
    void RenderEspTab();
    void RenderAntiAimTab();
    void RenderModifierTab();
    void RenderMiscTab();

    inline int legit_tab_index = 0;
    inline int rage_tab_index = 0;
    inline int esp_tab_index = 0;
    inline int antiaim_tab_index = 0;
    inline int modifier_tab_index = 0;
    inline int misc_tab_index = 0;
}