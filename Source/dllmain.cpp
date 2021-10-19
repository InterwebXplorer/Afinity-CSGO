//Afinity Main
#define     NOMINMAX
#include    <windows.h>
#include    "pch.h"

#include    "Resources/Sdk/sdk.hpp"
#include    "Resources/Helpers/utils.hpp"
#include    "Resources/Helpers/input.hpp"

#include    "hooks.hpp"
#include    "menu.hpp"
#include    "options.hpp"
#include    "render.hpp"
#include    "offsets.hpp" //always rename offsets to "offsets.hpp" on update

DWORD WINAPI OnDllAttach(LPVOID base)
{
    while (!GetModuleHandle(""))
        sleep(1000);

#ifdef DEBUG
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

    }


/* ARCHIVE OF DEFAULT DLL MAIN
// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
*/