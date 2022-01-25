#include <thread>

#include "Resources/common.h"
#include "global.h"
#include "options.h"
#include "utils.h"
#include "Resources/Utils/logging.h"
#include "Resources/Utils/math.h"
#include "Resources/Utils/inputsystem.h"
#include "Resources/Utils/draw.h"
#include "netvar.h"
#include "config.h"
#include "hooks.h"

DWORD WINAPI OnDllAttach(LPVOID lpParameter)
{
	try
	{
		while (GetModuleHandle(SERVERBROWSER_DLL) == nullptr)
			std::this_thread::sleep_for(1000ms);

		#ifdef DEBUG_CONSOLE
		if (!L::Attach(XorStr("Afinity developer-mode")))
			throw std::runtime_error(XorStr("failed to attach console"));

		L::Print(XorStr("console opened"));
		#else
		L::ofsFile.open(C::GetWorkingPath().append(XorStr("Afinity.log")), std::ios::out | std::ios::trunc);
		#endif

		if (!I::Setup())
			throw std::runtime_error(XorStr("failed to capture interfaces"));

		L::Print(XorStr("interfaces captured"));

		#ifdef DEBUG_CONSOLE
		if (strcmp(I::Engine->GetProductVersionString(), XorStr("1.37.7.6")) != 0)
		{
			L::PushConsoleColor(FOREGROUND_YELLOW);
			L::Print(fmt::format(XorStr("[warning] afinity version doesnt match current csgo version: {}"), I::Engine->GetProductVersionString()));
			L::PopConsoleColor();
		}
		#endif

		if (!CNetvarManager::Get().Setup(XorStr("netvars.afinity")))
			throw std::runtime_error(XorStr("failed to initialize netvars"));

		L::Print(fmt::format(XorStr("found [{:d}] props in [{:d}] tables"), CNetvarManager::Get().iStoredProps, CNetvarManager::Get().iStoredTables));

		if (!M::Setup())
			throw std::runtime_error(XorStr("failed to get math exports"));

		L::Print(XorStr("math exports loaded"));

		if (!IPT::Setup())
			throw std::runtime_error(XorStr("failed to set window messages processor"));

		L::Print(XorStr("inputsystem setup complete"));

		#if 0
		U::EntityListener.Setup();
		L::Print(XorStr("entity listener initialized"));
		#endif

		//https://wiki.alliedmods.net/Counter-Strike:_Global_Offensive_Events
		U::EventListener.Setup({ XorStr("player_hurt"), XorStr("round_prestart"), XorStr("round_freeze_end") });
		L::Print(XorStr("events registered"));

		if (!H::Setup())
			throw std::runtime_error(XorStr("failed initialize hooks"));

		L::Print(XorStr("hooks setup complete"));

		if (!P::Setup())
			throw std::runtime_error(XorStr("failed initialize proxies"));

		L::Print(XorStr("proxies applied"));

		if (!C::Setup(XorStr("default.afinity")))
		{
			L::PushConsoleColor(FOREGROUND_RED);
			L::Print(XorStr("[error] failed setup and/or load default configuration"));
			L::PopConsoleColor();
		}
		else
			L::Print(XorStr("default config loaded"));

		L::PushConsoleColor(FOREGROUND_MAGENTA);
		L::Print(XorStr("Afinity successfully loaded"));
		L::PopConsoleColor();
		I::GameConsole->Clear();
		I::ConVar->ConsoleColorPrintf(Color(255, 50, 255, 255), XorStr("Afinity successfully loaded.\nbuild date: %s / %s\n"), __DATE__, __TIME__);
	}
	catch (const std::exception& ex)
	{
		L::PushConsoleColor(FOREGROUND_INTENSE_RED);
		L::Print(fmt::format(XorStr("[error] {}"), ex.what()));
		L::PopConsoleColor();

		#ifdef _DEBUG
		_RPT0(_CRT_ERROR, ex.what());
		#else
	
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_FAILURE);
		#endif
	}

	return 1UL;
}

DWORD WINAPI OnDllDetach(LPVOID lpParameter)
{
	U::EventListener.Destroy();

	I::ConVar->FindVar(XorStr("crosshair"))->SetValue(true);

	P::Restore();

	H::Restore();

	IPT::Restore();

	D::Destroy();

	#ifdef DEBUG_CONSOLE
	L::Detach();
	#else
	if (L::ofsFile.is_open())
		L::ofsFile.close();
	#endif

	FreeLibraryAndExitThread((HMODULE)lpParameter, EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		if (GetModuleHandle(XorStr("csgo.exe")) == nullptr)
		{
			MessageBox(nullptr, XorStr("this cannot be injected in another process\nopen <csgo.exe> to inject"), XorStr("Afinity"), MB_OK);
			return FALSE;
		}

		G::hDll = hModule;

		if (auto hThread = CreateThread(nullptr, 0U, OnDllAttach, hModule, 0UL, nullptr); hThread != nullptr)
			CloseHandle(hThread);

		if (auto hThread = CreateThread(nullptr, 0U, OnDllDetach, hModule, 0UL, nullptr); hThread != nullptr)
			CloseHandle(hThread);

		return TRUE;
	}

	return FALSE;
}
