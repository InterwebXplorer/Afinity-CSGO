#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resources/imgui/imgui_freetype.h"
#include "resources/sdk/interfaces.h"
#include "resources/utils/detourhook.h"

namespace VTABLEINDEX {
	int RESET = 16,
	int PRESENT = 17;
	//int ENDSCENE = 42,
	int RESETEX = 132,
	int ALLOCATEKEYVALUESMEMORY = 2,
	int CREATEMOVE = 22,
	int FRAMESTAGENOTIFY = 37,
	int FINDMATERIAL = 84;
	int PAINTTRAVERSE = 41,
	int OVERRIDEVIEW = 18,
	//int GETVIEWMODELFOV = 35,
	int DOPOSTSCREENEFFECTS = 44,
	int DRAWMODELEXECUTE = 21,
	int DRAWMODEL = 29,
	int RENDERSMOKEOVERLAY = 41,
	int ISCONNECTED = 27,
	int LISTLEAVESINBOX = 6,
	int RUNCOMMAND = 19,
	int SENDMESSAGE = 0,
	int RETRIEVEMESSAGE = 2,
	int EMITSOUND = 5,
	int OVERRIDECONFIG = 21,
	int SCENEEND = 9,
	int LOCKCURSOR = 67,
	//int PLAYSOUND = 82,
	int FIREEVENT = 9,
	//int GETBOOL = 13,
	int SENDNETMSG = 40,
	int SENDDATAGRAM = 46,
	int SHOULDDRAWFOG = 17,
}

namespace DetourHookManager {
	inline DetourHook DHMReset;
	inline DetourHook DHMPresent;
	inline DetourHook DHMAllocateKeyValuesMemory;
    inline DetourHook DHMCreateMoveProxy;
    inline DetourHook DHMFrameStageNotify;
	inline DetourHook DHMFindMaterial;
    inline DetourHook DHMOverrideView;
    inline DetourHook DHMDoPostScreenEffects;
    inline DetourHook DHMIsConnected;
    inline DetourHook DHMListLeavesInBox;
    inline DetourHook DHMPaintTraverse;
    inline DetourHook DHMDrawModel;
    inline DetourHook DHMRenderSmokeOverlay;
    inline DetourHook DHMRunCommand;
    inline DetourHook DHMSGCSendMessage;
    inline DetourHook DHMRetrieveMessage;
    inline DetourHook DHMLockCursor;
    inline DetourHook DHMSendNetMsg;
	inline DetourHook DHMSendDatagram;
	inline DetourHook DHMShouldDrawFog;
}

namespace MiscSettings {
	inline bool REMOVEScopeOverlay = false;
	inline bool REMOVEArms = false;
	inline bool REMOVESmoke = false;
	inline bool REMOVEScopeZoom = false;
	inline bool REMOVEFog = false;
	inline bool REMOVEWeapon = false;
}

namespace Hooks {
	bool Setup();
	void Restore();

	long D3DAPI Reset(IDirect3DDevice9* Device, D3DPRESENT_PARAMETERS* PresentParameters);
	long D3DAPI Present(IDirect3DDevice9* Device, RECT* SourceRect, RECT* DestinationRect, HWND DestinationWindowOverride, RGNDATA* DirtyRegion);
	void* __fastcall AllocateKeyValuesMemory(IKeyValuesSystem* thisptr, int edx, int Size);
	void __fastcall CreateMoveProxy(IBaseClientDll* thisptr, int edx, int SequenceNumber, float InputSampleFrameTime, bool IsActive);
	void __fastcall FrameStageNotify(IBaseClientDll* thisptr, int edx, EClientFrameStage Stage);
	IMaterial* __fastcall FindMaterial(void* thisptr, void*, const char* MaterialName, const char* TextureGroupName, bool Complain, bool ComplainPrefix);
	void __fastcall OverrideView(IClientModeShared* thisptr, int edx, CViewSetup* Setup);
	int __fastcall DoPostScreenEffects(IClientModeShared* thisptr, int edx, CViewSetup* Setup);
	bool __fastcall IsConnected(IEngineClient* thisptr, int edx);
	int __fastcall ListLeavesInBox(void* thisptr, int edx, const Vector& Mins, const Vector& Maxs, unsigned short* List, int ListMax);
	void __fastcall PaintTraverse(ISurface* thisptr, int edx, unsigned int Panel, bool ForceRepaint, bool force);
	void __fastcall DrawModel(IStudioRender* thisptr, int edx, DrawModelResults_t* Results, const DrawModelInfo_t& ModelInfo, matrix3x4_t* BoneToWorld, float* FlexWeights, float* FlexDelayedWeights, const Vector& ModelOrigin, int Flags);
	void __fastcall RenderSmokeOverlay(IViewRender* thisptr, int edx, bool PreviewModel);
	void __fastcall RunCommand(IPrediction* thisptr, int edx, CBaseEntity* Entity, CUserCmd* Cmd, IMoveHelper* MoveHelper);
	void __fastcall SGCSendMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t MsgType, const void* Data, std::uint32_t Data);
	int __fastcall RetrieveMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t* MsgType, void* DestinationBufferPtr, std::uint32_t DestinationBufferSize, std::uint32_t* MsgSize);
	void __fastcall LockCursor(ISurface* thisptr, int edx);
	bool __fastcall SendNetMsg(INetChannel* thisptr, int edx, INetMessage* Message, bool ForceReliable, bool Voice);
	bool __fastcall ShouldDrawFog(std::uintptr_t ecx, std::uintptr_t edx);
}