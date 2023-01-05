#pragma once
#include "../sdk/convar.h"

#include "../sdk/interfaces/ibaseclientdll.h"
#include "../sdk/interfaces/icliententitylist.h"
#include "../sdk/interfaces/isurface.h"
#include "../sdk/interfaces/iclientmodeshared.h"
#include "../sdk/interfaces/iconvar.h"
#include "../sdk/interfaces/ieffects.h"
#include "../sdk/interfaces/inetchannel.h"
#include "../sdk/interfaces/iengineclient.h"
#include "../sdk/interfaces/ienginetrace.h"
#include "../sdk/interfaces/ienginevgui.h"
#include "../sdk/interfaces/ienginesound.h"
#include "../sdk/interfaces/igameconsole.h"
#include "../sdk/interfaces/igameeventmanager.h"
#include "../sdk/interfaces/ivpanel.h"
#include "../sdk/interfaces/igameui.h"
#include "../sdk/interfaces/iglobalvars.h"
#include "../sdk/interfaces/iservergamedll.h"
#include "../sdk/interfaces/iinput.h"
#include "../sdk/interfaces/iinputsystem.h"
#include "../sdk/interfaces/ilocalize.h"
#include "../sdk/interfaces/imatchframework.h"
#include "../sdk/interfaces/igametypes.h"
#include "../sdk/interfaces/imaterialsystem.h"
#include "../sdk/interfaces/imdlcache.h"
#include "../sdk/interfaces/imemalloc.h"
#include "../sdk/interfaces/inetworkstring.h"
#include "../sdk/interfaces/iphysicssurfaceprops.h"
#include "../sdk/interfaces/iprediction.h"
#include "../sdk/interfaces/isteamclient.h"
#include "../sdk/interfaces/isteamgamecoordinator.h"
#include "../sdk/interfaces/istudiorender.h"
#include "../sdk/interfaces/ivdebugoverlay.h"
#include "../sdk/interfaces/ivengineeffects.h"
#include "../sdk/interfaces/iglowmanager.h"
#include "../sdk/interfaces/iviewrender.h"
#include "../sdk/interfaces/iviewrenderbeams.h"
#include "../sdk/interfaces/ivmodelinfo.h"
#include "../sdk/interfaces/ivmodelrender.h"
#include "../sdk/interfaces/ivrenderview.h"
#include "../sdk/interfaces/iweaponsystem.h"
#include "../sdk/interfaces/ikeyvaluessystem.h"

class CInterfaceRegister {
public:
	InstantiateInterfaceFn pCreateFn;
	const char *szName;
	CInterfaceRegister *pNext;
};

namespace I {
	bool Setup();

	template <typename T>
	T *Capture(const std::string_view szModuleName, const std::string_view szInterface);

	inline IBaseClientDll *Client;
	inline IClientEntityList *ClientEntityList;
	inline IEffects *Effects;
	inline IGameMovement *GameMovement;
	inline IMoveHelper *MoveHelper;
	inline IPrediction *Prediction;
	inline IGameConsole *GameConsole;
	inline IGameUI *GameUI;
	inline IEngineClient *Engine;
	inline IEngineVGui *EngineVGui;
	inline IEngineTrace *EngineTrace;
	inline IEngineSound *EngineSound;
	inline INetworkContainer *NetworkContainer;
	inline IGameEventManager2 *GameEvent;
	inline IVRenderView *RenderView;
	inline IVDebugOverlay *DebugOverlay;
	inline IVEngineEffects *EngineEffects;
	inline IVModelInfo *ModelInfo;
	inline IVModelRender *ModelRender;
	inline IMDLCache *MDLCache;
	inline IStudioRender *StudioRender;
	inline IConVar *ConVar;
	inline IPhysicsSurfaceProps *PhysicsProps;
	inline IMaterialSystem *MaterialSystem;
	inline ISurface *Surface;
	inline IVPanel *Panel;
	inline IInputSystem *InputSystem;
	inline ILocalize *Localize;
	inline IMatchFramework *MatchFramework;
	inline IGameTypes *GameTypes;
	inline IServerGameDLL *Server;
	inline ISteamClient *SteamClient;
	inline ISteamUser *SteamUser;
	inline ISteamGameCoordinator *SteamGameCoordinator;
	inline IClientModeShared *ClientMode;
	inline IGlobalVarsBase *Globals;
	inline IMemAlloc *MemAlloc;
	inline IKeyValuesSystem *KeyValuesSystem;
	inline IDirect3DDevice9 *DirectDevice;
	inline IViewRender *ViewRender;
	inline IViewRenderBeams *ViewRenderBeams;
	inline IInput *Input;
	inline IClientState *ClientState;
	inline IWeaponSystem *WeaponSystem;
	inline IGlowObjectManager *GlowManager;
}
