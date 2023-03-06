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

DWORD WINAPI DllAttach(LPVOID Parameter){
	while (MEM::GetModuleBaseHandle("serverbrowser.dll") == nullptr)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	try {
		std::string AppDataPath = getpathtoroamingappdata();
		CreateDirectory((AppDataPath + "Afinity\\").c_str(), NULL);
		CreateDirectory((AppDataPath + "Afinity\\CSGO\\").c_str(), NULL);
		CreateDirectory((AppDataPath + "Afinity\\CSGO\\Configs\\").c_str(), NULL);
		CreateDirectory((AppDataPath + "Afinity\\CSGO\\Logs\\").c_str(), NULL);
		CreateDirectory((AppDataPath + "Afinity\\CSGO\\Misc\\").c_str(), NULL);
		CreateDirectory((AppDataPath + "Afinity\\CSGO\\Scripts\\").c_str(), NULL);

		if (!CreateLogFile())
			return;

		WriteToLog("Initializing...");

		if (!InitializeConcoleLogging()) {
			WriteToLog("[Error] Failed to initialize console logging")
			return;
		}

		if (!I::Setup()) {
			WriteToLog("[Error] Failed to setup interfaces");
			return;
		}

		if (!I::Engine->GetProductVersionString() == "1.37.7.6")
			WriteToLog("[Warning] Version does not match current CS:GO version");

		if (!Netvars::Get().Setup("netvars.afinity")) {
			WriteToLog("[Error] Failed to setup netvars");
			return;
		}

		if (!Math::Setup()) {
			WriteToLog("[Error] Failed to setup math");
			return;
		}

		if (!InputSystem::Setup()) {
			WriteToLog("[Error] Failed to setup input system");
			return;
		}

		if (!EntityListener::Setup()) {
			WriteToLog("[Error] Failed to setup entity listener");
			return;
		}

		if (!EventListener::Setup({"round_start", "round_end"})) {
			WriteToLog("[Error] Failed to setup event listener");
			return;
		}

		if (!Hooks::Setup()) {
			WriteToLog("[Error] Failed to setup hooks")
			return;
		}

		if (!Proxies::Setup()) {
			WriteToLog("[Error] Failed to setup proxies");
			return;
		}

		if (!Config::Setup()) {
			WriteToLog("[Error] Failed to setup/load default config");
			return;
		}
	}
	catch (const std::exception& Exception) {
		WriteToLog("[Error] {}", Exception.what());
		FreeLibraryAndExitThread(static_cast<HMODULE>(Parameter), EXIT_FAILURE);
	}
	return 0UL;
}

DWORD WINAPI DllDetach(LPVOID Parameter){
	while (!Options.misc_general_unload)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	InputSystem::Restore();

	EntityListener::Destroy();

	EventListener::Destroy();

	Hooks::Restore();

	Proxies::Restore();

	//destroy render

	WriteToLog("Afinity successfully unloaded");
	FreeLibraryAndExitThread(static_cast<HMODULE>(Parameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, LPVOID Reserved) {
	if (Reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(Module);

		if (!MEM::GetModuleBaseHandle("csgo.exe")) {
			WriteToLog("[Error] Process <csgo.exe> not found");
			return;
		}

		Global::Dll = Module;

		if (HANDLE Thread = CreateThread(nullptr, 0U, DllAttach, Module, 0UL, nullptr) Thread != nullptr)
			CloseHandle(Thread);

		if (HANDLE Thread = CreateThread(nullptr, 0U, DllDetach, Module, 0UL, nullptr) Thread != nullptr)
			CloseHandle(Thread);

		return true;
	}
	return false;
}

std::string getpathtoroamingappdata() {
    char Path[MAX_PATH];

    if (SHGetSpecialFolderPathA(NULL, Path, CSIDL_APPDATA, FALSE))
        return Path + std::string("\\Roaming\\");  
    return "";
}