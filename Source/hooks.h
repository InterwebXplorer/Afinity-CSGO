#pragma once
#include "Resources/common.h"
#include "../Source/Resources/Utils/detourhook.h"
#include "netvar.h"
#include "interfaces.h"

#ifndef FASTCALL
#define FASTCALL __fastcall
#endif

namespace VTABLE
{
	enum
	{
		RESET = 16,
		ENDSCENE = 42,
		RESETEX = 132,
		FRAMESTAGENOTIFY = 37,
		PAINTTRAVERSE = 41,
		OVERRIDEVIEW = 18,
		OVERRIDEMOUSEINPUT = 23,
		CREATEMOVE = 24,
		GETVIEWMODELFOV = 35,
		DOPOSTSCREENEFFECTS = 44,
		DRAWMODELEXECUTE = 21,
		DRAWMODEL = 29,
		RENDERSMOKEOVERLAY = 41,
		ISCONNECTED = 27,
		LISTLEAVESINBOX = 6,
		RUNCOMMAND = 19,
		SENDMESSAGE = 0,
		RETRIEVEMESSAGE = 2,
		EMITSOUND = 5,
		OVERRIDECONFIG = 21,
		SCENEEND = 9,
		LOCKCURSOR = 67,
		PLAYSOUND = 82,
		FIREEVENT = 9,
		GETBOOL = 13,
		SENDNETMSG = 40,
		SENDDATAGRAM = 46
	};
}

namespace DTR
{
	inline CDetourHook Reset;
	inline CDetourHook EndScene;
	inline CDetourHook FrameStageNotify;
	inline CDetourHook OverrideView;
	inline CDetourHook OverrideMouseInput;
	inline CDetourHook CreateMove;
	inline CDetourHook SendNetMsg;
	inline CDetourHook SendDatagram;
	inline CDetourHook GetViewModelFOV;
	inline CDetourHook DoPostScreenEffects;
	inline CDetourHook IsConnected;
	inline CDetourHook RenderSmokeOverlay;
	inline CDetourHook ListLeavesInBox;
	inline CDetourHook PaintTraverse;
	inline CDetourHook DrawModel;
	inline CDetourHook RunCommand;
	inline CDetourHook SendMessageGC;
	inline CDetourHook RetrieveMessage;
	inline CDetourHook LockCursor;
	inline CDetourHook PlaySoundSurface;
	inline CDetourHook SvCheatsGetBool;
}

namespace H
{
	bool	Setup();
	void	Restore();

	long	D3DAPI		hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	long	D3DAPI		hkEndScene(IDirect3DDevice9* pDevice);
	bool	FASTCALL	hkCreateMove(IClientModeShared* thisptr, int edx, float flInputSampleTime, CUserCmd* pCmd);
	void	FASTCALL	hkPaintTraverse(ISurface* thisptr, int edx, unsigned int uPanel, bool bForceRepaint, bool bForce);
	void	FASTCALL	hkPlaySound(ISurface* thisptr, int edx, const char* szFileName);
	void	FASTCALL	hkLockCursor(ISurface* thisptr, int edx);
	void	FASTCALL	hkFrameStageNotify(IBaseClientDll* thisptr, int edx, EClientFrameStage stage);
	void	FASTCALL	hkDrawModel(IStudioRender* thisptr, int edx, DrawModelResults_t* pResults, const DrawModelInfo_t& info, matrix3x4_t* pBoneToWorld, float* flFlexWeights, float* flFlexDelayedWeights, const Vector& vecModelOrigin, int nFlags);
	void	FASTCALL	hkRenderSmokeOverlay(IViewRender* thisptr, int edx, bool bPreViewModel);
	int		FASTCALL	hkListLeavesInBox(void* thisptr, int edx, const Vector& vecMins, const Vector& vecMaxs, unsigned short* puList, int nListMax);
	bool	FASTCALL	hkIsConnected(IEngineClient* thisptr, int edx);
	bool	FASTCALL	hkSendNetMsg(INetChannel* thisptr, int edx, INetMessage* pMessage, bool bForceReliable, bool bVoice);
	int		FASTCALL	hkSendDatagram(INetChannel* thisptr, int edx, bf_write* pDatagram);
	void	FASTCALL	hkOverrideView(IClientModeShared* thisptr, int edx, CViewSetup* pSetup);
	void	FASTCALL	hkOverrideMouseInput(IClientModeShared* thisptr, int edx, float* x, float* y);
	float	FASTCALL	hkGetViewModelFOV(IClientModeShared* thisptr, int edx);
	int		FASTCALL	hkDoPostScreenEffects(IClientModeShared* thisptr, int edx, CViewSetup* pSetup);
	void	FASTCALL	hkRunCommand(IPrediction* thisptr, int edx, CBaseEntity* pEntity, CUserCmd* pCmd, IMoveHelper* pMoveHelper);
	int		FASTCALL	hkSendMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t uMsgType, const void* pData, std::uint32_t uData);
	int		FASTCALL	hkRetrieveMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t* puMsgType, void* pDest, std::uint32_t uDest, std::uint32_t* puMsgSize);
	bool	FASTCALL	hkSvCheatsGetBool(CConVar* thisptr, int edx);
	long	CALLBACK	hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

namespace RVP
{
	inline std::shared_ptr<CRecvPropHook> SmokeEffectTickBegin;
}

namespace P
{
	bool	Setup();
	void	Restore();

	void	SmokeEffectTickBegin(const CRecvProxyData* pData, void* pStruct, void* pOut);
}
