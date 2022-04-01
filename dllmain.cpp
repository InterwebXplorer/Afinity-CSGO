#define NOMINMAX
#include <Windows.h>
#include "options.h"
#include "hooks.h"

DWORD WINAPI OnDllAttach(LPVOID lpParameter) {
    while (!GetModuleHandleA("serverbrowser.dll"))
        Sleep(200);
    try {
      hooks::initialize();
    }
};

DWORD WINAPI OnDllDetach() {
    hooks::shutdown();
    return true;
};

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDll);
            CreateThread(nullptr, 0, OnDllAttach, hinstDll, 0, nullptr);
            return true;
        case DLL_PROCESS_DETACH:
            if(lpvReserved == nullptr)
            return OnDllDetach();
        return true;
    }
};