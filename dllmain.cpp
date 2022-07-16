#include <windows.h>
#include <d3d.h>
#include <d3dx9.h>
#include <thread>
#include <chrono>
#include "resources/utils/memory.h"
#include "resources/"



DWORD WINAPI OnDllAttach(LPVOID lpParameter) {
    while (MEM::GetModuleBaseHandle("serverbrowser.dll") == nullptr)
        std::this_thread::sleep_for(200ms);
    
    try {
        //initialize crap
    }

    catch (const std::exception& stdExcept) {
        FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter));
    }
        return true;
}

DWORD WINAPI OnDllDetach(LPVOID lpParameter) {
    //deinitialize crap
    FreeLibraryAndExitThread((HMODULE)lpParameter);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
        global::hDll = hModule;

        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(nullptr, 0, OnDllAttach, hModule, 0, nullptr);
            return true;

        case DLL_PROCESS_DETACH:
            if(lpReserved == nullptr)
                return OnDllDetach();
            return true;
    }
        return false;
}