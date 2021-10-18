//Afinity main
#include <iostream>
#include <windows.h>
#include "pch.h"
//#include "offsets.hpp" //Hazedumper must be renamed to this when offsets updated

//Fetch display resolution
const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN); const int xhairx = SCREEN_WIDTH / 2; //X-Axis (Width)
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN); const int xhairy = SCREEN_HEIGHT / 2; //Y-Axis (Height) 

//Global Variables
HWND hwnd;
DWORD procID;
HANDLE hProcess;
uintptr_t moduleBase;
HDC hdc;
int closest;

/*
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