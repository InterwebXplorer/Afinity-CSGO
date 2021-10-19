//Afinity Main
#define     NOMINMAX
#include    <windows.h>
#include    <clocale>
#include    "pch.h"

//Add SDK/UTILS

#include "hooks.hpp"
#include "menu.hpp"
//#include "offsets.hpp" //always rename offsets to "offsets.hpp" on update

BOOL WINAPI DllMain(
    HMODULE modulehandle,
    DWORD   reasoncall,
    LPVOID  reserved
)
{
    switch (reasoncall)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
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