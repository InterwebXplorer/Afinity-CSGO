#pragma once
#include "render.h"

namespace hooks {
	void setup();
    void destroy() noexcept;

    constexpr void* virtualfunction(void* thisptr, size_t index) noexcept {
        return (*static_cast<void***>(thisptr))[index];
    }

    using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
    inline EndSceneFn endsceneoriginal = nullptr;
    long __stdcall endscene(IDirect3DDevice9* device) noexcept;

    using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
    inline ResetFn resetoriginal = nullptr;
    HRESULT __stdcall reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;
}