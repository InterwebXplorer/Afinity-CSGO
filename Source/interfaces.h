#pragma once
// used: iconvar forward declaration
#include "../Source/Resources/SDK/convar.h"

#include "../Source/Resources/SDK/interfaces/ibaseclientdll.h"
#include "../Source/Resources/SDK/interfaces/icliententitylist.h"
#include "../Source/Resources/SDK/interfaces/isurface.h"
#include "../Source/Resources/SDK/interfaces/iclientmodeshared.h"
#include "../Source/Resources/SDK/interfaces/iconvar.h"
#include "../Source/Resources/SDK/interfaces/ieffects.h"
#include "../Source/Resources/SDK/interfaces/inetchannel.h"
#include "../Source/Resources/SDK/interfaces/iengineclient.h"
#include "../Source/Resources/SDK/interfaces/ienginetrace.h"
#include "../Source/Resources/SDK/interfaces/ienginevgui.h"
#include "../Source/Resources/SDK/interfaces/ienginesound.h"
#include "../Source/Resources/SDK/interfaces/igameconsole.h"
#include "../Source/Resources/SDK/interfaces/igameeventmanager.h"
#include "../Source/Resources/SDK/interfaces/ivpanel.h"
#include "../Source/Resources/SDK/interfaces/igameui.h"
#include "../Source/Resources/SDK/interfaces/iglobalvars.h"
#include "../Source/Resources/SDK/interfaces/iservergamedll.h"
#include "../Source/Resources/SDK/interfaces/iinput.h"
#include "../Source/Resources/SDK/interfaces/iinputsystem.h"
#include "../Source/Resources/SDK/interfaces/ilocalize.h"
#include "../Source/Resources/SDK/interfaces/imatchframework.h"
#include "../Source/Resources/SDK/interfaces/igametypes.h"
#include "../Source/Resources/SDK/interfaces/imaterialsystem.h"
#include "../Source/Resources/SDK/interfaces/imdlcache.h"
#include "../Source/Resources/SDK/interfaces/imemalloc.h"
#include "../Source/Resources/SDK/interfaces/inetworkstring.h"
#include "../Source/Resources/SDK/interfaces/iphysicssurfaceprops.h"
#include "../Source/Resources/SDK/interfaces/iprediction.h"
#include "../Source/Resources/SDK/interfaces/isteamclient.h"
#include "../Source/Resources/SDK/interfaces/isteamgamecoordinator.h"
#include "../Source/Resources/SDK/interfaces/istudiorender.h"
#include "../Source/Resources/SDK/interfaces/ivdebugoverlay.h"
#include "../Source/Resources/SDK/interfaces/ivengineeffects.h"
#include "../Source/Resources/SDK/interfaces/iglowmanager.h"
#include "../Source/Resources/SDK/interfaces/iviewrender.h"
#include "../Source/Resources/SDK/interfaces/iviewrenderbeams.h"
#include "../Source/Resources/SDK/interfaces/ivmodelinfo.h"
#include "../Source/Resources/SDK/interfaces/ivmodelrender.h"
#include "../Source/Resources/SDK/interfaces/ivrenderview.h"
#include "../Source/Resources/SDK/interfaces/iweaponsystem.h"

class CInterfaceRegister
{
public:
	InstantiateInterfaceFn	pCreateFn;		//0x0
	const char*				szName;			//0x4
	CInterfaceRegister*		pNext;			//0x8
};

/*
 * INTERFACES
 * global pointers of source-sdk interfaces declared in game libraries
 * have different functions which we can call and/or hook
 */
namespace I
{
	// Get
	bool Setup();
	/* search and returns a pointer of specific interface given */
	template <typename T>
	T* Capture(const char* szModule, std::string_view szInterface);

	// Values
	inline IBaseClientDll*			Client;
	inline IClientEntityList*		ClientEntityList;
	inline IEffects*				Effects;
	inline IGameMovement*			GameMovement;
	inline IMoveHelper*				MoveHelper;
	inline IPrediction*				Prediction;
	inline IGameConsole*			GameConsole;
	inline IGameUI*					GameUI;
	inline IEngineClient*			Engine;
	inline IEngineVGui*				EngineVGui;
	inline IEngineTrace*			EngineTrace;
	inline IEngineSound*			EngineSound;
	inline INetworkContainer*		NetworkContainer;
	inline IGameEventManager2*		GameEvent;
	inline IVRenderView*			RenderView;
	inline IVDebugOverlay*			DebugOverlay;
	inline IVEngineEffects*			EngineEffects;
	inline IVModelInfo*				ModelInfo;
	inline IVModelRender*			ModelRender;
	inline IMDLCache*				MDLCache;
	inline IStudioRender*			StudioRender;
	inline IConVar*					ConVar;
	inline IPhysicsSurfaceProps*	PhysicsProps;
	inline IMaterialSystem*			MaterialSystem;
	inline ISurface*				Surface;
	inline IVPanel*					Panel;
	inline IInputSystem*			InputSystem;
	inline ILocalize*				Localize;
	inline IMatchFramework*			MatchFramework;
	inline IGameTypes*				GameTypes;
	inline IServerGameDLL*			Server;
	inline ISteamClient*			SteamClient;
	inline ISteamUser*				SteamUser;
	inline ISteamGameCoordinator*	SteamGameCoordinator;
	inline IClientModeShared*		ClientMode;
	inline IGlobalVarsBase*			Globals;
	inline IMemAlloc*				MemAlloc;
	inline IDirect3DDevice9*		DirectDevice;
	inline IViewRender*				ViewRender;
	inline IViewRenderBeams*		ViewRenderBeams;
	inline IInput*					Input;
	inline IClientState*			ClientState;
	inline IWeaponSystem*			WeaponSystem;
	inline IGlowObjectManager*		GlowManager;
}
