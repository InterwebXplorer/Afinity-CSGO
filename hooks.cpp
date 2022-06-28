#include "hooks.h"
#include <intrin.h>
#include <stdexcept>
#include "resources/minhook/minhook.h"
#include "resources/imgui/imgui.h"
#include "resources/imgui/imgui_freetype.h"
#include "resources/imgui/imgui_internal.h"
#include "resources/imgui/impl/imgui_impl_dx9.h"
#include "resources/imgui/impl/imgui_impl_win32.h"

void hooks::setup() {
    if (MH_Initialize())
        throw std::runtime_error("Failed to initialize minhook");

    if (MH_CreateHook(virtualfunction(render::device, 42), &endscene, reinterpret_cast<void**>(&endsceneoriginal)))
        throw std::runtime_error("Failed to create endscene hook");

    if (MH_CreateHook(virtualfunction(render::device, 16), &reset, reinterpret_cast<void**>(&resetoriginal)))
        throw std::runtime_error("Failed to create reset hook");

    if (MH_EnableHook(MH_ALL_HOOKS))
        throw std::runtime_error("Failed to enable hooks");

    render::destroydirectx();
}

void hooks::destroy() noexcept {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

long __stdcall hooks::endscene(IDirect3DDevice9* device) noexcept {
    static const auto returnaddress = _ReturnAddress();

    const auto result = endsceneoriginal(device, device);

    if (_ReturnAddress() == returnaddress)
        return result;

    if (!render::setup)
        render::setupmenu(device);

    if (render::show)
        render::render();

    return result;
}

HRESULT __stdcall hooks::reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept {
    ImGui_ImplDX9_InvalidateDeviceObjects();
    const auto result = resetoriginal(device, device, params);
    ImGui_ImplDX9_CreateDeviceObjects();
    return result;
}