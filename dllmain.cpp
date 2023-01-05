#include <Windows.h>
#include <thread>
#include <chrono>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "hooks.h"
#include "config.h"
#include "resources/sdk/interfaces.h"
#include "resources/utils/math.h"
#include "resources/utils/inputsystem.h"
#include "resources/utils/eventlistener.h"
#include "resources/utils/entitylistener.h"
#include "resources/utils/filelogging.h"
#include "global.h"

DWORD WINAPI dllAttach(LPVOID lpvParameter){
	while (MEM::GetModuleBaseHandle("serverbrowser.dll") == nullptr)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	try {
		std::string appdatapath = getpathtoroamingappdata();
		CreateDirectory((appdatapath + "Afinity\\").c_str(), NULL);
		CreateDirectory((appdatapath + "Afinity\\CSGO\\").c_str(), NULL);
		CreateDirectory((appdatapath + "Afinity\\CSGO\\Configs\\").c_str(), NULL);
		CreateDirectory((appdatapath + "Afinity\\CSGO\\Logs\\").c_str(), NULL);
		CreateDirectory((appdatapath + "Afinity\\CSGO\\Misc\\").c_str(), NULL);
		CreateDirectory((appdatapath + "Afinity\\CSGO\\Scripts\\").c_str(), NULL);

		if (!createlogfile())
			return;

		writetolog("Initializing...");

		if (!initializeconcolelogging()) {
			writetolog("[Error] Failed to initialize console logging")
			return;
		}

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

		if (!CEntityListener::Setup()) {
			writetolog("[Error] Failed to setup entity listener");
			return;
		}

		if (!CEventListener::Setup({"round_start", "round_end"})) {
			writetolog("[Error] Failed to setup event listener");
			return;
		}

		if (!Hooks::Setup()) {
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
	catch (const std::exception& exception) {
		writetolog("[Error] {}", exception.what());
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpvParameter), EXIT_FAILURE);
	}
	return 0UL;
}

DWORD WINAPI dllDetach(LPVOID lpvParameter){
	while (!Options.misc_general_unload)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	IPT::Restore();

	CEntityListener::Destroy();

	CEventListener::Destroy();

	Hooks::Restore();

	P::Restore();

	//destroy render

	writetolog("Afinity successfully unloaded");
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpvParameter), EXIT_SUCCESS);
}

BOOL APIENTRY dllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		if (!MEM::GetModuleBaseHandle("csgo.exe")) {
			writetolog("[Error] Process <csgo.exe> not found");
			return;
		}

		Global::hDll = hModule;

		if (HANDLE hThread = CreateThread(nullptr, 0U, dllAttach, hModule, 0UL, nullptr) hThread != nullptr)
			CloseHandle(hThread);

		if (HANDLE hThread = CreateThread(nullptr, 0U, dllDetach, hModule, 0UL, nullptr) hThread != nullptr)
			CloseHandle(hThread);

		return true;
	}
	return false;
}

std::string getpathtoroamingappdata() {
    char path[MAX_PATH];

    if (SHGetSpecialFolderPathA(NULL, path, CSIDL_APPDATA, FALSE))
        return path + std::string("\\Roaming\\");  
    return "";
}