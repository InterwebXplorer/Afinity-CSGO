#Pragma once

#include <Windows.h>
#include <thread>
#include <chrono>
#include <d3d9.h>
#include <d3dx9.h>
#include "hooks.h"
#include "config.h"
#include "interfaces.h"
#include "resources/utils/math.h"
#include "resources/utils/inputsystem.h"
#include "resources/utils/eventlistener.h"
#include "resources/utils/entitylistener.h"
#include "resources/utils/filelogging.h"

DWORD WINAPI dllAttach(LPVOID lpvParameter){
	While(MEM::GetModuleBaseHandle("serverbrowser.dll") == nullptr)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	try {
		if (!I::Setup()) {
			writetolog("[Error] Failed to setup interfaces");
			return;
		}

		if (!I::Engine->GetProductVersionString() == "1.37.7.6")
			writetolog("[Warning] Version does not match current CS:GO version");

		if (!CNetvarManager::Get().Setup("netvars.afinity")) {
			writetolog("[Error] Failed to setup netvars");
			return;
		}

		if (!M::Setup()) {
			writetolog("[Error] Failed to setup math");
			return;
		}

		if (!IPT::Setup()) {
			writetolog("[Error] Failed to setup input system");
			return;
		}

		if (!U::EntityListener.Setup()) {
			writetolog("[Error] Failed to setup entity listener");
			return;
		}

		if (!U::EventListener.Setup()) {
			writetolog("[Error] Failed to setup event listener");
			return;
		}

		if (!H::Setup()) {
			writetolog("[Error] Failed to setup hooks")
			return;
		}

		if (!P::Setup()) {
			writetolog("[Error] Failed to setup proxies");
			return;
		}

		if (!C::Setup(default.afinity)) {
			writetolog("[Error] Failed to setup/load default config");
			return;
		}
	}
	catch () {

		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_FAILURE);
	}
	return 0UL;
}

DWORD WINAPI dllDetach(LPVOID lpvParameter){

}

BOOL APIENTRY dllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		if (MEM::GetModuleBaseHandle("csgo.exe") == nullptr) {
			writetolog("[Error] Process <csgo.exe> not found");
			return;
		}

		if (HANDLE hThread = CreateThread(nullptr, 0U, dllAttach, hModule, 0UL, nullptr) hThread != nullptr)
			CloseHandle(hThread);

		if (HANDLE hThread = CreateThread(nullptr, 0U, dllDetach, hModule, 0UL, nullptr) hThread != nullptr)
			CloseHandle(hThread);

		return true;
	}
	return false;
}