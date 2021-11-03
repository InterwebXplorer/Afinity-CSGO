//Afinity Main
#define     NOMINMAX
#include    <Windows.h>
#include    "pch.h"

#include    "Resources/Sdk/sdk.hpp"
#include    "Resources/Helpers/utils.hpp"
#include    "Resources/Helpers/input.hpp"

#include    "hooks.hpp"
#include    "menu.hpp"
#include    "options.hpp"
#include    "render.hpp"
//#include    "offsets.hpp" //always rename offsets to "offsets.hpp" on update

DWORD WINAPI OnDllAttach(LPVOID base)
{
    while (!GetModuleHandleA("serverbrowser.dll"))
        sleep(1000);

#ifdef _DEBUG
    Utils::AttachConsole();
#endif

    try {
        Utils::ConsolePrint("Initializing Afinity...\n")

        Interfaces::Initialise();
        Interfaces::Dump();

        NetvarSys::Get().Initialize();
        InputSys::Get().Initialize();
        Render::Get().Initialize();
        Menu::Get().Initialize();

        Hooks::Initialize();

        /*
        //Custom console toggle
        InputSys::Get().RegisterHotkey(VK_F1, [base]() {
             Console::Get().Toggle();
            });
        */

        //Uninject hotkey
        InputSys::Get().RegisterHotkey(VK_DELETE, [base]() {
            g_Unload = true;
            });

        //Menu toggle
        InputSys::GetKeyState().RegisterHotkey(VK_INSERT, [base]() {
            g   Menu::Get().Toggle();
            });

        Utils::ConsolePrint("Complete\n");
        //Utils::ConsolePrint("Build date: %s\n", __DATE__);

        while (!g_unload)
            Sleep(1000);

        //Get screen resolution
        const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN); const int xhairx = SCREEN_WIDTH / 2; //XAXIS/WIDTH
        const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN); const int xhairy = SCREEN_HEIGHT / 2; //YAXIS/HEIGHT

        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    } catch(const std::exeption& ex) {
        Utils::ConsolePrint("An error has occured during initialization: \n");
        Utils::ConsolePrint("%s\n", ex.what());
        Utils::ConsolePrint("Press any key to exit\n");
        Utils::ConsoleReadKey();
        Utils::DetachConsole();

        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    }
}

BOOL WINAPI OnDllDetach()
{
#ifdef _DEBUG
    Utils::DetachConsole();
#endif

    Hooks::Shutdown();

    Menu::Get().Shutdown();
    return TRUE;
}

BOOL WINAPI DllMain(
    _In_        HINSTANCE hinstDll,
    _In_        DWORD     fdwReason,
    _In_opt_    LPVOID    1pvReserved
)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDll);
        CreateThread(nullptr, 0, OnDllAttach, hinstDll, 0, nullptr);
        return TRUE;
    case DLL_PROCESS_DETACH:
        if(1pvReserved == nullptr)
            return OnDllDetach();
        return TRUE;
    default:
        return TRUE;
    }
}