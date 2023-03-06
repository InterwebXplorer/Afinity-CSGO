#include <format>
#include "interfaces.h"
#include "../utils/filelogging.h"

bool I::Setup() {
	Client =			Capture<IBaseClientDll>(CLIENT_DLL, "VClient");
	ClientEntityList =	Capture<IClientEntityList>(CLIENT_DLL, "VClientEntityList");
	Effects =			Capture<IEffects>(CLIENT_DLL, "IEffects");
	GameMovement =		Capture<IGameMovement>(CLIENT_DLL, "GameMovement");
	Prediction =		Capture<IPrediction>(CLIENT_DLL, "VClientPrediction");
	GameConsole =		Capture<IGameConsole>(CLIENT_DLL, "GameConsole");
	GameUI =			Capture<IGameUI>(CLIENT_DLL, "GameUI");
	Engine =			Capture<IEngineClient>(ENGINE_DLL, "VEngineClient");
	EngineVGui =		Capture<IEngineVGui>(ENGINE_DLL, "VEngineVGui");
	EngineTrace =		Capture<IEngineTrace>(ENGINE_DLL, "EngineTraceClient");
	EngineSound =		Capture<IEngineSound>(ENGINE_DLL, "IEngineSoundClient");
	NetworkContainer =	Capture<INetworkContainer>(ENGINE_DLL, "VEngineClientStringTable");
	GameEvent =			Capture<IGameEventManager2>(ENGINE_DLL, "GAMEEVENTSMANAGER002");
	RenderView =		Capture<IVRenderView>(ENGINE_DLL, "VEngineRenderView");
	DebugOverlay =		Capture<IVDebugOverlay>(ENGINE_DLL, "VDebugOverlay");
	EngineEffects =		Capture<IVEngineEffects>(ENGINE_DLL, "VEngineEffects");
	ModelInfo =			Capture<IVModelInfo>(ENGINE_DLL, "VModelInfoClient");
	ModelRender =		Capture<IVModelRender>(ENGINE_DLL, "VEngineModel");
	MDLCache =			Capture<IMDLCache>(DATACACHE_DLL, "MDLCache");
	StudioRender =		Capture<IStudioRender>(STUDIORENDER_DLL, "VStudioRender");
	ConVar =			Capture<IConVar>(VSTDLIB_DLL, "VEngineCvar");
	PhysicsProps =		Capture<IPhysicsSurfaceProps>(PHYSICS_DLL, "VPhysicsSurfaceProps");
	MaterialSystem =	Capture<IMaterialSystem>(MATERIALSYSTEM_DLL, "VMaterialSystem");
	Surface =			Capture<ISurface>(VGUI_DLL, "VGUI_Surface");
	Panel =				Capture<IVPanel>(VGUI2_DLL, "VGUI_Panel");
	InputSystem =		Capture<IInputSystem>(INPUTSYSTEM_DLL, "InputSystemVersion");
	Localize =			Capture<ILocalize>(LOCALIZE_DLL, "Localize_");
	MatchFramework =	Capture<IMatchFramework>(MATCHMAKING_DLL, "MATCHFRAMEWORK_");
	GameTypes =			Capture<IGameTypes>(MATCHMAKING_DLL, "VENGINE_GAMETYPES_VERSION");
	Server =			Capture<IServerGameDLL>(SERVER_DLL, "ServerGameDLL");

	SteamClient = Engine->GetSteamAPIContext()->pSteamClient;
	if (SteamClient == nullptr)
		return false;

	SteamUser =	Engine->GetSteamAPIContext()->pSteamUser;
	if (SteamUser == nullptr)
		return false;

	const void* hSteamAPI = MEM::GetModuleBaseHandle(STEAM_API_DLL);
	const HSteamUser hSteamUser = reinterpret_cast<std::add_pointer_t<HSteamUser()>>(MEM::GetExportAddress(hSteamAPI, "SteamAPI_GetHSteamUser"))();
	const HSteamPipe hSteamPipe = reinterpret_cast<std::add_pointer_t<HSteamPipe()>>(MEM::GetExportAddress(hSteamAPI, "SteamAPI_GetHSteamPipe"))();

	SteamGameCoordinator = static_cast<ISteamGameCoordinator*>(SteamClient->GetISteamGenericInterface(hSteamUser, hSteamPipe, "SteamGameCoordinator001"));
	if (SteamGameCoordinator == nullptr)
		return false;

	ClientMode = **reinterpret_cast<IClientModeShared***>(MEM::GetVFunc<std::uintptr_t>(Client, 10) + 0x5);
	if (ClientMode == nullptr)
		return false;

	Globals = **reinterpret_cast<IGlobalVarsBase***>(MEM::GetVFunc<std::uintptr_t>(Client, 11) + 0xA);
	if (Globals == nullptr)
		return false;

	MemAlloc = *static_cast<IMemAlloc**>(MEM::GetExportAddress(MEM::GetModuleBaseHandle(TIER0_DLL), "g_pMemAlloc"));
	if (MemAlloc == nullptr)
		return false;

	KeyValuesSystem = reinterpret_cast<KeyValuesSystemFn>(MEM::GetExportAddress(MEM::GetModuleBaseHandle(VSTDLIB_DLL), "KeyValuesSystem"))();
	if (KeyValuesSystem == nullptr)
		return false;

	DirectDevice = **reinterpret_cast<IDirect3DDevice9***>(MEM::FindPattern(SHADERPIDX9_DLL, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);
	if (DirectDevice == nullptr)
		return false;

	ViewRender = **reinterpret_cast<IViewRender***>(MEM::FindPattern(CLIENT_DLL, "8B 0D ? ? ? ? FF 75 0C 8B 45 08") + 0x2);
	if (ViewRender == nullptr)
		return false;

	ViewRenderBeams = *reinterpret_cast<IViewRenderBeams**>(MEM::FindPattern(CLIENT_DLL, "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9") + 0x1);
	if (ViewRenderBeams == nullptr)
		return false;

	Input =	*reinterpret_cast<IInput**>(MEM::FindPattern(CLIENT_DLL, "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 0x1);
	if (Input == nullptr)
		return false;

	ClientState = **reinterpret_cast<IClientState***>(MEM::FindPattern(ENGINE_DLL, "A1 ? ? ? ? 8B 88 ? ? ? ? 85 C9 75 07") + 0x1);
	if (ClientState == nullptr)
		return false;

	WeaponSystem = *reinterpret_cast<IWeaponSystem**>(MEM::FindPattern(CLIENT_DLL, "8B 35 ? ? ? ? FF 10 0F B7 C0") + 0x2);
	if (WeaponSystem == nullptr)
		return false;

	GlowManager = *reinterpret_cast<IGlowObjectManager**>(MEM::FindPattern(CLIENT_DLL, "0F 11 05 ? ? ? ? 83 C8 01") + 0x3);
	if (GlowManager == nullptr)
		return false;

	return true;
}

template <typename T>
T* I::Capture(const std::string_view szModuleName, const std::string_view szInterface) {
	const auto GetRegisterList = [&szModuleName]() -> CInterfaceRegister* {
		void* oCreateInterface = nullptr;

		if (const auto hModule = MEM::GetModuleBaseHandle(szModuleName); hModule != nullptr)
			oCreateInterface = MEM::GetExportAddress(hModule, "CreateInterface");

		if (oCreateInterface == nullptr) {
			WriteToLog("[Error] Failed to get <CreateInterface> address")
			return;
		}

		const std::uintptr_t uCreateInterfaceRelative = reinterpret_cast<std::uintptr_t>(oCreateInterface) + 0x5;
		const std::uintptr_t uCreateInterface = uCreateInterfaceRelative + 4U + *reinterpret_cast<std::int32_t*>(uCreateInterfaceRelative);
		return **reinterpret_cast<CInterfaceRegister***>(uCreateInterface + 0x6);
	};

	for (auto pRegister = GetRegisterList(); pRegister != nullptr; pRegister = pRegister->pNext) {
		if ((std::string_view(pRegister->szName).compare(0U, szInterface.length(), szInterface) == 0 && std::atoi(pRegister->szName + szInterface.length()) > 0) || szInterface.compare(pRegister->szName) == 0) {
			auto pInterface = pRegister->pCreateFn();

			WriteToLog(std::format("Captured {} interface -> {:#08X}", pRegister->szName), reinterpret_cast<std::uintptr_t>(pInterface))

			return static_cast<T*>(pInterface);
		}
	}

	return nullptr;
}