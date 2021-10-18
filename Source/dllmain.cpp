//Afinity main
#include <iostream>
#include <windows.h>
//Add more includes here
#include "offsets.hpp" //Hazedumper must be renamed to this when offsets updated

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