#include <array>

#include "../Source/hooks.h"
#include "../global.h"
#include "variables.h"
#include "../Source/Resources/Utils/inputsystem.h"
#include "../Source/Resources/Utils/logging.h"
#include "../Source/Resources/Utils/draw.h"
#include "../utils.h"
#include "menu.h"

//FEATURES (NO FEATURES CURRENTLY)
/*
#include "../Source/Features/lagcompensation.h"
#include "../Source/Features/prediction.h"
#include "../Source/Features/ragebot.h"
#include "../Source/Features/antiaim.h"
#include "../Source/Features/legitbot.h"
#include "../Source/Features/triggerbot.h"
#include "../Source/Features/visuals.h"
#include "../Source/Features/misc.h"
#include "../Source/Features/skinchanger.h"
*/

static constexpr std::array<const char*, 3U> arrSmokeMaterials =
{
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
};

#pragma region hooks_get
bool H::Setup()
{
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error(XorStr("failed to initialize minhook"));

	if (!DTR::Reset.Create(MEM::GetVFunc(I::DirectDevice, VTABLE::RESET), &hkReset))
		return false;

	if (!DTR::EndScene.Create(MEM::GetVFunc(I::DirectDevice, VTABLE::ENDSCENE), &hkEndScene))
		return false;

	if (!DTR::FrameStageNotify.Create(MEM::GetVFunc(I::Client, VTABLE::FRAMESTAGENOTIFY), &hkFrameStageNotify))
		return false;

	if (!DTR::OverrideView.Create(MEM::GetVFunc(I::ClientMode, VTABLE::OVERRIDEVIEW), &hkOverrideView))
		return false;

#if 0
	if (!DTR::OverrideMouseInput.Replace(MEM::GetVFunc(I::ClientMode, VTABLE::OVERRIDEMOUSEINPUT), &hkOverrideMouseInput))
		return false;
#endif

	if (!DTR::CreateMove.Create(MEM::GetVFunc(I::ClientMode, VTABLE::CREATEMOVE), &hkCreateMove))
		return false;

	if (!DTR::GetViewModelFOV.Create(MEM::GetVFunc(I::ClientMode, VTABLE::GETVIEWMODELFOV), &hkGetViewModelFOV))
		return false;

	if (!DTR::DoPostScreenEffects.Create(MEM::GetVFunc(I::ClientMode, VTABLE::DOPOSTSCREENEFFECTS), &hkDoPostScreenEffects))
		return false;

	if (!DTR::IsConnected.Create(MEM::GetVFunc(I::Engine, VTABLE::ISCONNECTED), &hkIsConnected))
		return false;

	if (!DTR::ListLeavesInBox.Create(MEM::GetVFunc(I::Engine->GetBSPTreeQuery(), VTABLE::LISTLEAVESINBOX), &hkListLeavesInBox))
		return false;

	if (!DTR::PaintTraverse.Create(MEM::GetVFunc(I::Panel, VTABLE::PAINTTRAVERSE), &hkPaintTraverse))
		return false;

	if (!DTR::DrawModel.Create(MEM::GetVFunc(I::StudioRender, VTABLE::DRAWMODEL), &hkDrawModel))
		return false;

	if (!DTR::RenderSmokeOverlay.Create(MEM::GetVFunc(I::ViewRender, VTABLE::RENDERSMOKEOVERLAY), &hkRenderSmokeOverlay))
		return false;

	if (!DTR::RunCommand.Create(MEM::GetVFunc(I::Prediction, VTABLE::RUNCOMMAND), &hkRunCommand))
		return false;

	if (!DTR::SendMessageGC.Create(MEM::GetVFunc(I::SteamGameCoordinator, VTABLE::SENDMESSAGE), &hkSendMessage))
		return false;

	if (!DTR::RetrieveMessage.Create(MEM::GetVFunc(I::SteamGameCoordinator, VTABLE::RETRIEVEMESSAGE), &hkRetrieveMessage))
		return false;

	if (!DTR::LockCursor.Create(MEM::GetVFunc(I::Surface, VTABLE::LOCKCURSOR), &hkLockCursor))
		return false;

	if (!DTR::PlaySoundSurface.Create(MEM::GetVFunc(I::Surface, VTABLE::PLAYSOUND), &hkPlaySound))
		return false;

	static CConVar* sv_cheats = I::ConVar->FindVar(XorStr("sv_cheats"));

	if (!DTR::SvCheatsGetBool.Create(MEM::GetVFunc(sv_cheats, VTABLE::GETBOOL), &hkSvCheatsGetBool))
		return false;

	return true;
}

void H::Restore()
{
	DTR::Reset.Remove();
	DTR::EndScene.Remove();
	DTR::FrameStageNotify.Remove();
	DTR::OverrideView.Remove();
	DTR::OverrideMouseInput.Remove();
	DTR::CreateMove.Remove();
	DTR::SendNetMsg.Remove();
	DTR::SendDatagram.Remove();
	DTR::GetViewModelFOV.Remove();
	DTR::DoPostScreenEffects.Remove();
	DTR::IsConnected.Remove();
	DTR::ListLeavesInBox.Remove();
	DTR::PaintTraverse.Remove();
	DTR::DrawModel.Remove();
	DTR::RunCommand.Remove();
	DTR::SendMessageGC.Remove();
	DTR::RetrieveMessage.Remove();
	DTR::LockCursor.Remove();
	DTR::PlaySoundSurface.Remove();
	DTR::SvCheatsGetBool.Remove();

#if 0
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
#endif

	MH_Uninitialize();
}
#pragma endregion

#pragma region hooks_handlers
long D3DAPI H::hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	static auto oReset = DTR::Reset.GetOriginal<decltype(&hkReset)>();

	if (!D::bInitialized)
		return oReset(pDevice, pPresentationParameters);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	const HRESULT hReset = oReset(pDevice, pPresentationParameters);

	if (hReset == D3D_OK)
		ImGui_ImplDX9_CreateDeviceObjects();

	return hReset;
}

long D3DAPI H::hkEndScene(IDirect3DDevice9* pDevice)
{
	static auto oEndScene = DTR::EndScene.GetOriginal<decltype(&hkEndScene)>();
	static void* pUsedAddress = nullptr;

	SEH_START

		if (pUsedAddress == nullptr)
		{
			MEMORY_BASIC_INFORMATION memInfo;
			VirtualQuery(_ReturnAddress(), &memInfo, sizeof(MEMORY_BASIC_INFORMATION));

			char chModuleName[MAX_PATH];
			GetModuleFileName(static_cast<HMODULE>(memInfo.AllocationBase), chModuleName, MAX_PATH);

			if (strstr(chModuleName, GAMEOVERLAYRENDERER_DLL) != nullptr)
				pUsedAddress = _ReturnAddress();
		}

	//STREAM PROOF ESP HERE UwU
	if (_ReturnAddress() == pUsedAddress)
	{
		if (!D::bInitialized)
			D::Setup(pDevice);

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		W::MainWindow(pDevice);

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	SEH_END

		return oEndScene(pDevice);
}

bool FASTCALL H::hkCreateMove(IClientModeShared* thisptr, int edx, float flInputSampleTime, CUserCmd* pCmd)
{
	static auto oCreateMove = DTR::CreateMove.GetOriginal<decltype(&hkCreateMove)>();

	CBaseEntity* pLocal = G::pLocal = CBaseEntity::GetLocalPlayer();

	if (pCmd->iCommandNumber == 0)
		return oCreateMove(thisptr, edx, flInputSampleTime, pCmd);

	if (oCreateMove(thisptr, edx, flInputSampleTime, pCmd))
		I::Prediction->SetLocalViewAngles(pCmd->angViewPoint);

	G::pCmd = pCmd;

	if (I::ClientState == nullptr || I::Engine->IsPlayingDemo())
		return oCreateMove(thisptr, edx, flInputSampleTime, pCmd);

	INetChannel* pNetChannel = I::ClientState->pNetChannel;

	const volatile auto vlBaseAddress = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) - sizeof(std::uintptr_t));

	bool& bSendPacket = *reinterpret_cast<bool*>(vlBaseAddress - 0x1C);

	QAngle angOldViewPoint = pCmd->angViewPoint;

	SEH_START

		CMiscellaneous::Get().Run(pCmd, pLocal, bSendPacket);


	//https://github.com/VSES/SourceEngine2007/blob/master/se2007/engine/cl_pred.cpp#L41
	if (I::ClientState->iDeltaTick > 0)
		I::Prediction->Update(I::ClientState->iDeltaTick, I::ClientState->iDeltaTick > 0, I::ClientState->iLastCommandAck, I::ClientState->iLastOutgoingCommand + I::ClientState->nChokedCommands);

	CPrediction::Get().Start(pCmd, pLocal);
	{
		if (C::Get<bool>(Vars.bMiscAutoPistol))
			CMiscellaneous::Get().AutoPistol(pCmd, pLocal);

		if (C::Get<bool>(Vars.bMiscFakeLag) || C::Get<bool>(Vars.bAntiAim))
			CMiscellaneous::Get().FakeLag(pLocal, bSendPacket);

		if (C::Get<bool>(Vars.bRage))
			CRageBot::Get().Run(pCmd, pLocal, bSendPacket);

		if (C::Get<bool>(Vars.bLegit))
			CLegitBot::Get().Run(pCmd, pLocal, bSendPacket);

		if (C::Get<bool>(Vars.bTrigger))
			CTriggerBot::Get().Run(pCmd, pLocal);

		if (C::Get<bool>(Vars.bAntiAim))
			CAntiAim::Get().UpdateServerAnimations(pCmd, pLocal);

		if (C::Get<bool>(Vars.bAntiAim))
			CAntiAim::Get().Run(pCmd, pLocal, bSendPacket);
	}
	CPrediction::Get().End(pCmd, pLocal);

	if (pLocal->IsAlive())
		CMiscellaneous::Get().MovementCorrection(pCmd, angOldViewPoint);

	if (C::Get<bool>(Vars.bMiscAntiUntrusted))
	{
		pCmd->angViewPoint.Normalize();
		pCmd->angViewPoint.Clamp();
	}

	if (C::Get<bool>(Vars.bMiscPingSpike))
		CLagCompensation::Get().UpdateIncomingSequences(pNetChannel);
	else
		CLagCompensation::Get().ClearIncomingSequences();

	if (pNetChannel != nullptr)
	{
		if (!DTR::SendNetMsg.IsHooked())
			DTR::SendNetMsg.Create(MEM::GetVFunc(pNetChannel, VTABLE::SENDNETMSG), &hkSendNetMsg);

		if (!DTR::SendDatagram.IsHooked())
			DTR::SendDatagram.Create(MEM::GetVFunc(pNetChannel, VTABLE::SENDDATAGRAM), &hkSendDatagram);
	}

	G::angRealView = pCmd->angViewPoint;

	G::bSendPacket = bSendPacket;

	//DONT SET/CLAMP ANGLES HERE

	SEH_END

		return false;
}

void FASTCALL H::hkPaintTraverse(ISurface* thisptr, int edx, unsigned int uPanel, bool bForceRepaint, bool bForce)
{
	static auto oPaintTraverse = DTR::PaintTraverse.GetOriginal<decltype(&hkPaintTraverse)>();
	const FNV1A_t uPanelHash = FNV1A::Hash(I::Panel->GetName(uPanel));

	if (!I::Engine->IsTakingScreenshot() && C::Get<bool>(Vars.bWorld) && C::Get<std::vector<bool>>(Vars.vecWorldRemovals).at(REMOVAL_SCOPE) && uPanelHash == FNV1A::HashConst("HudZoom"))
		return;

	oPaintTraverse(thisptr, edx, uPanel, bForceRepaint, bForce);

	if (uPanelHash == FNV1A::HashConst("FocusOverlayPanel"))
	{
		SEH_START

			D::ClearDrawData();

		CVisuals::Get().Store();

		D::SwapDrawData();

		SEH_END
	}
}

void FASTCALL H::hkPlaySound(ISurface* thisptr, int edx, const char* szFileName)
{
	static auto oPlaySound = DTR::PlaySoundSurface.GetOriginal<decltype(&hkPlaySound)>();
	oPlaySound(thisptr, edx, szFileName);
}

void FASTCALL H::hkLockCursor(ISurface* thisptr, int edx)
{
	static auto oLockCursor = DTR::LockCursor.GetOriginal<decltype(&hkLockCursor)>();

	if (W::bMainOpened)
	{
		I::Surface->UnLockCursor();
		return;
	}

	oLockCursor(thisptr, edx);
}

void FASTCALL H::hkFrameStageNotify(IBaseClientDll* thisptr, int edx, EClientFrameStage stage)
{
	static auto oFrameStageNotify = DTR::FrameStageNotify.GetOriginal<decltype(&hkFrameStageNotify)>();

	SEH_START

		if (!I::Engine->IsInGame())
		{
			CLagCompensation::Get().ClearIncomingSequences();
			return oFrameStageNotify(thisptr, edx, stage);
		}

	if (I::Engine->IsTakingScreenshot())
		return oFrameStageNotify(thisptr, edx, stage);

	CBaseEntity* pLocal = CBaseEntity::GetLocalPlayer();

	if (pLocal == nullptr)
		return oFrameStageNotify(thisptr, edx, stage);

	static QAngle angOldAimPunch = { }, angOldViewPunch = { };

	switch (stage)
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
	{
		break;
	}
	case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
	{
		break;
	}
	case FRAME_NET_UPDATE_END:
	{
		break;
	}
	case FRAME_RENDER_START:
	{
		*pLocal->GetFlashMaxAlpha() = C::Get<bool>(Vars.bWorld) ? C::Get<int>(Vars.iWorldMaxFlash) * 2.55f : 255.f;

		for (auto szSmokeMaterial : arrSmokeMaterials)
		{
			IMaterial* pMaterial = I::MaterialSystem->FindMaterial(szSmokeMaterial, TEXTURE_GROUP_OTHER);

			if (pMaterial != nullptr && !pMaterial->IsErrorMaterial())
				pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, (C::Get<bool>(Vars.bWorld) && C::Get<std::vector<bool>>(Vars.vecWorldRemovals).at(REMOVAL_SMOKE)) ? true : false);
		}

		if (pLocal->IsAlive() && C::Get<bool>(Vars.bWorld))
		{
			angOldViewPunch = pLocal->GetViewPunch();
			angOldAimPunch = pLocal->GetPunch();

			if (C::Get<std::vector<bool>>(Vars.vecWorldRemovals).at(REMOVAL_PUNCH))
			{
				pLocal->GetViewPunch() = QAngle(0, 0, 0);
				pLocal->GetPunch() = QAngle(0, 0, 0);
			}
		}

		if (C::Get<bool>(Vars.bWorld) && C::Get<int>(Vars.iWorldThirdPersonKey) > 0)
		{
			static bool bThirdPerson = false;

			if (!I::Engine->IsConsoleVisible() && IPT::IsKeyReleased(C::Get<int>(Vars.iWorldThirdPersonKey)))
				bThirdPerson = !bThirdPerson;

			I::Input->bCameraInThirdPerson = bThirdPerson && pLocal->IsAlive() && !I::Engine->IsTakingScreenshot();
			I::Input->vecCameraOffset.z = bThirdPerson ? C::Get<float>(Vars.flWorldThirdPersonOffset) : 150.f;
		}

		break;
	}
	case FRAME_RENDER_END:
	{
		if (pLocal->IsAlive() && C::Get<bool>(Vars.bWorld) && C::Get<std::vector<bool>>(Vars.vecWorldRemovals).at(REMOVAL_PUNCH))
		{
			pLocal->GetViewPunch() = angOldViewPunch;
			pLocal->GetPunch() = angOldAimPunch;
		}

		break;
	}
	default:
		break;
	}

	SEH_END

		oFrameStageNotify(thisptr, edx, stage);
}

void FASTCALL H::hkDrawModel(IStudioRender* thisptr, int edx, DrawModelResults_t* pResults, const DrawModelInfo_t& info, matrix3x4_t* pBoneToWorld, float* flFlexWeights, float* flFlexDelayedWeights, const Vector& vecModelOrigin, int nFlags)
{
	static auto oDrawModel = DTR::DrawModel.GetOriginal<decltype(&hkDrawModel)>();

	if (!I::Engine->IsInGame() || I::Engine->IsTakingScreenshot())
		return oDrawModel(thisptr, edx, pResults, info, pBoneToWorld, flFlexWeights, flFlexDelayedWeights, vecModelOrigin, nFlags);

	bool bClearOverride = false;

	if (G::pLocal != nullptr && C::Get<bool>(Vars.bEsp) && C::Get<bool>(Vars.bEspChams))
		bClearOverride = CVisuals::Get().Chams(G::pLocal, pResults, info, pBoneToWorld, flFlexWeights, flFlexDelayedWeights, vecModelOrigin, nFlags);

	oDrawModel(thisptr, edx, pResults, info, pBoneToWorld, flFlexWeights, flFlexDelayedWeights, vecModelOrigin, nFlags);

	if (bClearOverride)
		I::StudioRender->ForcedMaterialOverride(nullptr);
}

void FASTCALL H::hkRenderSmokeOverlay(IViewRender* thisptr, int edx, bool bPreViewModel)
{
	static auto oRenderSmokeOverlay = DTR::RenderSmokeOverlay.GetOriginal<decltype(&hkRenderSmokeOverlay)>();

	if (C::Get<bool>(Vars.bWorld) && C::Get<std::vector<bool>>(Vars.vecWorldRemovals).at(REMOVAL_SMOKE))
		*reinterpret_cast<float*>(reinterpret_cast<std::uintptr_t>(thisptr) + 0x588) = 0.0f;
	else
		oRenderSmokeOverlay(thisptr, edx, bPreViewModel);
}

int FASTCALL H::hkListLeavesInBox(void* thisptr, int edx, const Vector& vecMins, const Vector& vecMaxs, unsigned short* puList, int nListMax)
{
	static auto oListLeavesInBox = DTR::ListLeavesInBox.GetOriginal<decltype(&hkListLeavesInBox)>();

	//https://www.unknowncheats.me/forum/counterstrike-global-offensive/330483-disable-model-occulusion-3.html

	//https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L674
	static std::uintptr_t uInsertIntoTree = (MEM::FindPattern(CLIENT_DLL, XorStr("56 52 FF 50 18")) + 0x5);

	if (C::Get<bool>(Vars.bEsp) && C::Get<bool>(Vars.bEspChams) && C::Get<bool>(Vars.bEspChamsDisableOcclusion) && (C::Get<bool>(Vars.bEspChamsEnemies) || C::Get<bool>(Vars.bEspChamsAllies)) && reinterpret_cast<std::uintptr_t>(_ReturnAddress()) == uInsertIntoTree)
	{
		//https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L1470
		if (const auto pInfo = *reinterpret_cast<RenderableInfo_t**>(reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) + 0x14); pInfo != nullptr)
		{
			if (const auto pRenderable = pInfo->pRenderable; pRenderable != nullptr)
			{
				if (const auto pEntity = pRenderable->GetIClientUnknown()->GetBaseEntity(); pEntity != nullptr && pEntity->IsPlayer())
				{
					//https://www.unknowncheats.me/forum/2429206-post15.html
					//https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L2473
					pInfo->uFlags &= ~RENDER_FLAGS_FORCE_OPAQUE_PASS;
					pInfo->uFlags2 |= RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE;

					//https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L707
					constexpr Vector vecMapMin(MIN_COORD_FLOAT, MIN_COORD_FLOAT, MIN_COORD_FLOAT);
					constexpr Vector vecMapMax(MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT);
					return oListLeavesInBox(thisptr, edx, vecMapMin, vecMapMax, puList, nListMax);
				}
			}
		}
	}

	return oListLeavesInBox(thisptr, edx, vecMins, vecMaxs, puList, nListMax);
}

bool FASTCALL H::hkIsConnected(IEngineClient* thisptr, int edx)
{
	static auto oIsConnected = DTR::IsConnected.GetOriginal<decltype(&hkIsConnected)>();

	static const std::uintptr_t uLoadoutAllowedReturn = MEM::FindPattern(CLIENT_DLL, XorStr("84 C0 75 05 B0 01 5F"));

	if (reinterpret_cast<std::uintptr_t>(_ReturnAddress()) == uLoadoutAllowedReturn && C::Get<bool>(Vars.bMiscUnlockInventory))
		return false;

	return oIsConnected(thisptr, edx);
}

bool FASTCALL H::hkSendNetMsg(INetChannel* thisptr, int edx, INetMessage* pMessage, bool bForceReliable, bool bVoice)
{
	static auto oSendNetMsg = DTR::SendNetMsg.GetOriginal<decltype(&hkSendNetMsg)>();

	if (pMessage->GetType() == 14)
		return false;

	if (pMessage->GetGroup() == INetChannelInfo::VOICE)
		bVoice = true;

	return oSendNetMsg(thisptr, edx, pMessage, bForceReliable, bVoice);
}

int FASTCALL H::hkSendDatagram(INetChannel* thisptr, int edx, bf_write* pDatagram)
{
	static auto oSendDatagram = DTR::SendDatagram.GetOriginal<decltype(&hkSendDatagram)>();

	INetChannelInfo* pNetChannelInfo = I::Engine->GetNetChannelInfo();
	static CConVar* sv_maxunlag = I::ConVar->FindVar(XorStr("sv_maxunlag"));

	if (!I::Engine->IsInGame() || !C::Get<bool>(Vars.bMiscPingSpike) || pDatagram != nullptr || pNetChannelInfo == nullptr || sv_maxunlag == nullptr)
		return oSendDatagram(thisptr, edx, pDatagram);

	const int iOldInReliableState = thisptr->iInReliableState;
	const int iOldInSequenceNr = thisptr->iInSequenceNr;

	const float flMaxLatency = std::max(0.f, std::clamp(C::Get<float>(Vars.flMiscLatencyFactor), 0.f, sv_maxunlag->GetFloat()) - pNetChannelInfo->GetLatency(FLOW_OUTGOING));
	CLagCompensation::Get().AddLatencyToNetChannel(thisptr, flMaxLatency);

	const int iReturn = oSendDatagram(thisptr, edx, pDatagram);

	thisptr->iInReliableState = iOldInReliableState;
	thisptr->iInSequenceNr = iOldInSequenceNr;

	return iReturn;
}

void FASTCALL H::hkOverrideView(IClientModeShared* thisptr, int edx, CViewSetup* pSetup)
{
	static auto oOverrideView = DTR::OverrideView.GetOriginal<decltype(&hkOverrideView)>();

	if (!I::Engine->IsInGame() || I::Engine->IsTakingScreenshot())
		return oOverrideView(thisptr, edx, pSetup);

	G::vecCamera = pSetup->vecOrigin;

	if (G::pLocal == nullptr || !G::pLocal->IsAlive())
		return oOverrideView(thisptr, edx, pSetup);

	CBaseCombatWeapon* pWeapon = G::pLocal->GetWeapon();

	if (pWeapon == nullptr)
		return oOverrideView(thisptr, edx, pSetup);

	if (CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(pWeapon->GetItemDefinitionIndex());
		pWeaponData != nullptr && C::Get<bool>(Vars.bScreen) && std::fpclassify(C::Get<float>(Vars.flScreenCameraFOV)) != FP_ZERO &&
		(pWeaponData->nWeaponType == WEAPONTYPE_SNIPER ? !G::pLocal->IsScoped() : true))
		pSetup->flFOV += C::Get<float>(Vars.flScreenCameraFOV);

	oOverrideView(thisptr, edx, pSetup);
}

void FASTCALL H::hkOverrideMouseInput(IClientModeShared* thisptr, int edx, float* x, float* y)
{
	static auto oOverrideMouseInput = DTR::OverrideMouseInput.GetOriginal<decltype(&hkOverrideMouseInput)>();

	if (!I::Engine->IsInGame())
		return oOverrideMouseInput(thisptr, edx, x, y);

	oOverrideMouseInput(thisptr, edx, x, y);
}

float FASTCALL H::hkGetViewModelFOV(IClientModeShared* thisptr, int edx)
{
	static auto oGetViewModelFOV = DTR::GetViewModelFOV.GetOriginal<decltype(&hkGetViewModelFOV)>();

	if (!I::Engine->IsInGame() || I::Engine->IsTakingScreenshot())
		return oGetViewModelFOV(thisptr, edx);

	if (G::pLocal != nullptr && G::pLocal->IsAlive() && C::Get<bool>(Vars.bScreen) && std::fpclassify(C::Get<float>(Vars.flScreenViewModelFOV)) != FP_ZERO)
		return oGetViewModelFOV(thisptr, edx) + C::Get<float>(Vars.flScreenViewModelFOV);

	return oGetViewModelFOV(thisptr, edx);
}

int FASTCALL H::hkDoPostScreenEffects(IClientModeShared* thisptr, int edx, CViewSetup* pSetup)
{
	static auto oDoPostScreenEffects = DTR::DoPostScreenEffects.GetOriginal<decltype(&hkDoPostScreenEffects)>();

	if (!I::Engine->IsInGame() || I::Engine->IsTakingScreenshot())
		return oDoPostScreenEffects(thisptr, edx, pSetup);

	if (G::pLocal != nullptr && C::Get<bool>(Vars.bEsp) && C::Get<bool>(Vars.bEspGlow))
		CVisuals::Get().Glow(G::pLocal);

	return oDoPostScreenEffects(thisptr, edx, pSetup);
}

void FASTCALL H::hkRunCommand(IPrediction* thisptr, int edx, CBaseEntity* pEntity, CUserCmd* pCmd, IMoveHelper* pMoveHelper)
{
	static auto oRunCommand = DTR::RunCommand.GetOriginal<decltype(&hkRunCommand)>();

	oRunCommand(thisptr, edx, pEntity, pCmd, pMoveHelper);

	I::MoveHelper = pMoveHelper;
}

int FASTCALL H::hkSendMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t uMsgType, const void* pData, std::uint32_t uData)
{
	static auto oSendMessage = DTR::SendMessageGC.GetOriginal<decltype(&hkSendMessage)>();

	std::uint32_t uMessageType = uMsgType & 0x7FFFFFFF;
	void* pDataMutable = const_cast<void*>(pData);

	const int iStatus = oSendMessage(thisptr, edx, uMsgType, pDataMutable, uData);

	if (iStatus != EGCResultOK)
		return iStatus;

#ifdef DEBUG_CONSOLE
	L::PushConsoleColor(FOREGROUND_INTENSE_GREEN | FOREGROUND_RED);
	L::Print(fmt::format(XorStr("[<-] Message sent to GC {:d}!"), uMessageType));
	L::PopConsoleColor();
#endif

	return iStatus;
}

int FASTCALL H::hkRetrieveMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t* puMsgType, void* pDest, std::uint32_t uDest, std::uint32_t* puMsgSize)
{
	static auto oRetrieveMessage = DTR::RetrieveMessage.GetOriginal<decltype(&hkRetrieveMessage)>();
	const int iStatus = oRetrieveMessage(thisptr, edx, puMsgType, pDest, uDest, puMsgSize);

	if (iStatus != EGCResultOK)
		return iStatus;

	std::uint32_t uMessageType = *puMsgType & 0x7FFFFFFF;

#ifdef DEBUG_CONSOLE
	L::PushConsoleColor(FOREGROUND_INTENSE_GREEN | FOREGROUND_RED);
	L::Print(fmt::format(XorStr("[->] Message received from GC {:d}!"), uMessageType));
	L::PopConsoleColor();
#endif

	if (C::Get<bool>(Vars.bMiscAutoAccept) && uMessageType == 9177)
	{
		U::SetLocalPlayerReady();
		Beep(500, 800);
		U::FlashWindow(IPT::hWindow);
	}

	return iStatus;
}

bool FASTCALL H::hkSvCheatsGetBool(CConVar* thisptr, int edx)
{
	static auto oSvCheatsGetBool = DTR::SvCheatsGetBool.GetOriginal<decltype(&hkSvCheatsGetBool)>();
	static std::uintptr_t uCAM_ThinkReturn = (MEM::FindPattern(CLIENT_DLL, XorStr("85 C0 75 30 38 86")));

	if (reinterpret_cast<std::uintptr_t>(_ReturnAddress()) == uCAM_ThinkReturn && C::Get<bool>(Vars.bWorld) && C::Get<int>(Vars.iWorldThirdPersonKey) > 0)
		return true;

	return oSvCheatsGetBool(thisptr, edx);
}

long CALLBACK H::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	IPT::Process(uMsg, wParam, lParam);

	if (C::Get<int>(Vars.iMenuKey) > 0 && IPT::IsKeyReleased(C::Get<int>(Vars.iMenuKey)))
		W::bMainOpened = !W::bMainOpened;

	I::InputSystem->EnableInput(!W::bMainOpened);

	if (D::bInitialized && W::bMainOpened && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1L;

	return CallWindowProcW(IPT::pOldWndProc, hWnd, uMsg, wParam, lParam);
}
#pragma endregion

#pragma region proxies_get
bool P::Setup()
{
#if 0
	RecvProp_t* pSmokeEffectTickBegin = CNetvarManager::Get().mapProps[FNV1A::HashConst("CSmokeGrenadeProjectile->m_nSmokeEffectTickBegin")].pRecvProp;
	if (pSmokeEffectTickBegin == nullptr)
		return false;

	RVP::SmokeEffectTickBegin = std::make_shared<CRecvPropHook>(pSmokeEffectTickBegin, P::SmokeEffectTickBegin);
#endif

	return true;
}

void P::Restore()
{
#if 0
	RVP::SmokeEffectTickBegin->Restore();
#endif
}
#pragma endregion

#pragma region proxies_handlers
void P::SmokeEffectTickBegin(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
	static auto oSmokeEffectTickBegin = RVP::SmokeEffectTickBegin->GetOriginal();

	if (C::Get<bool>(Vars.bWorld) && C::Get<std::vector<bool>>(Vars.vecWorldRemovals).at(REMOVAL_SMOKE))
	{
		if (auto pEntity = static_cast<CBaseEntity*>(pStruct); pEntity != nullptr)
			pEntity->GetOrigin() = Vector(MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT);
	}

	oSmokeEffectTickBegin(pData, pStruct, pOut);
}
#pragma endregion
