#include <intrin.h>
#include <Windows.h>
#include "resources/minhook/minhook.h"
#include "resources/utils/inputsystem.h"
#include "resources/utils/consolelogging.h"
#include "resources/utils/filelogging.h"
#include "resources/utils/utils.h"
#include "resources/utils/detourhook.h"
#include "resources/sdk/interfaces.h"
#include "features/features.h"
#include "options.h"
#include "hooks.h"
#include "menu.h"

bool Hooks::Setup() {
    SEH_START

    if (MH_Initialize() != MH_OK) {
        WriteToLog("[Error] Failed to initialize minhook");
        return false;
    }

    if (!DetourHook::Reset.Create(Memory::GetVFunc(I::DirectDevice, VTABLE::RESET), &Reset)) {
        WriteToLog("[Error] Failed to hook function <RESET>");
        return false;
    }

    if (!DetourHook::EndScene.Create(Memory::GetVFunc(I::DirectDevice, VTABLE::ENDSCENE), &EndScene)) {
        WriteToLog("[Error] Failed to hook function <ENDSCENE>");
        return false;
    }

    if (!DetourHook::AllocateKeyValuesMemory.Create(Memory::GetVFunc(I::KeyValuesSystem, VTABLE::ALLOCATEKEYVALUESMEMORY), &AllocateKeyValuesMemory)) {
        WriteToLog("[Error] Failed to hook function <ALLOCATEKEYVALUESMEMORY>");
        return false;
    }

    if (!DetourHook::CreateMove.Create(Memory::GetVFunc(I::Client, VTABLE::CREATEMOVE), &CreateMove)) {
        WriteToLog("[Error] Failed to hook function <CREATEMOVE>");
        return false;
    }

    if (!DetourHook::FrameStageNotify.Create(Memory::GetVFunc(I::Client, VTABLE::FRAMESTAGENOTIFY), &FrameStageNotify)) {
        WriteToLog("[Error] Failed to hook function <FRAMESTAGENOTIFY>");
        return false;
    }

    if (!DetourHook::OverrideView.Create(Memory::GetVFunc(I::ClientMode, VTABLE::OVERRIDEVIEW), &OverrideView)) {
        WriteToLog("[Error] Failed to hook function <OVERRIDEVIEW>");
        return false;
    }

    if (!DetourHook::GetViewModelFOV.Create(Memory::GetVFunc(I::ClientMode, VTABLE::GETVIEWMODELFOV), &GetViewModelFOV)) {
        WriteToLog("[Error] Failed to hook function <GETVIEWMODELFOV>");
        return false;
    }

    if (!DetourHook::DoPostScreenEffects.Create(Memory::GetVFunc(I::ClientMode, VTABLE::DOPOSTSCREENEFFECTS), &DoPostScreenEffects)) {
        WriteToLog("[Error] Failed to hook function <DOPOSTSCREENEFFECTS>");
        return false;
    }

    if (!DetourHook::IsConnected.Create(Memory::GetVFunc(I::Engine, VTABLE::ISCONNECTED), &IsConnected)) {
        WriteToLog("[Error] Failed to hook function <ISCONNECTED>");
        return false;
    }

    if (!DetourHook::ListLeavesInBox.Create(Memory::GetVFunc(I::Engine->GetBSPTreeQuery, VTABLE::LISTLEAVESINBOX), &ListLeavesInBox)) {
        WriteToLog("[Error] Failed to hook function <LISTLEAVESINBOX>");
        return false;
    }

    if (!DetourHook::PaintTraverse.Create(Memory::GetVFunc(I::Panel, VTABLE::PAINTTRAVERSE), &PaintTraverse)) {
        WriteToLog("[Error] Failed to hook function <PAINTTRAVERSE>");
        return false;
    }

    if (!DetourHook::DrawModel.Create(Memory::GetVFunc(I::StudioRender, VTABLE::DRAWMODEL), &DrawModel)) {
        WriteToLog("[Error] Failed to hook function <DRAWMODEL>");
        return false;
    }

    if (!DetourHook::RenderSmokeOverlay.Create(Memory::GetVFunc(I::ViewRender, VTABLE::RENDERSMOKEOVERLAY), &RenderSmokeOverlay)) {
        WriteToLog("[Error] Failed to hook function <RENDERSMOKEOVERLAY>");
        return false;
    }

    if (!DetourHook::RunCommand.Create(Memory::GetVFunc(I::Prediction, VTABLE::RUNCOMMAND), &RunCommand)) {
        WriteToLog("[Error] Failed to hook function <RUNCOMMAND>");
        return false;
    }

    if (!DetourHook::SGCSendMessage.Create(Memory::GetVFunc(I::SteamGameCoordinator, VTABLE::SENDMESSAGE), &SGCSendMessage)) {
        WriteToLog("[Error] Failed to hook function <SENDMESSAGE>");
        return false;
    }

    if (!DetourHook::RetrieveMessage.Create(Memory::GetVFunc(I::SteamGameCoordinator, VTABLE::RETRIEVEMESSAGE), &RetrieveMessage)) {
        WriteToLog("[Error] Failed to hook function <RETRIEVEMESSAGE>");
        return false;
    }

    if (!DetourHook::LockCursor.Create(Memory::GetVFunc(I::Surface, VTABLE::LOCKCURSOR), &LockCursor)) {
        WriteToLog("[Error] Failed to hook function <LOCKCURSOR>");
        return false;
    }

    if (!DetourHook::SPlaySound.Create(Memory::GetVFunc(I::Surface, VTABLE::PLAYSOUND), &SPlaySound)) {
        WriteToLog("[Error] Failed to hook function <PLAYSOUND>");
        return false;
    }

    static CConVar* sv_cheats = I::ConVar->FindVar("sv_cheats");

    if (!DetourHook::GetBool.Create(Memory::GetVFunc(sv_cheats, VTABLE::GETBOOL), &GetBool)) {
        WriteToLog("[Error] Failed to hook function <GETBOOL>");
        return false;
    }

    return true;

    SEH_END

    return false;
}

void Hooks::Restore() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

long D3DAPI Hooks::Reset(IDirect3DDevice9* Device, D3DPRESENT_PARAMETERS* PresentParameters) {
    static auto Reset = DetourHook::Reset.GetOriginal<decltype(&Reset)>();

    if (!Draw::IsInitialized)
        return Reset(Device, PresentParameters);

    ImGui_ImplDX9_InvalidateDeviceObjects();

    const HRESULT ResetModule = Reset(Device, PresentParameters);

    if (ResetModule == D3D_OK)
        ImGui_ImplDX9_CreateDeviceObjects();

    return ResetModule;
}

long D3DAPI Hooks::EndScene(IDirect3DDevice9* Device) {
    static auto EndScene = DetourHook::EndScene.GetOriginal<decltype(&EndScene)>();
    
}

void* FASTCALL Hooks::










//

void __fastcall Hooks::DrawModelExecute(IStudioRender* thisptr, ) {

}



bool __fastcall Hooks::hkSendNetMsg(INetChannel* thisptr, int edx, INetMessage* pMessage, bool bForceReliable, bool bVoice) { //
    static auto oSendNetMsg = DTR::SendNetMsg.GetOriginal<decltype(&hkSendNetMsg)>();

    if (Options.misc_general_bypasssvpure) {
        if (pMessage->GetType() == 14)
            return false;
    }

    if (pMessage->GetGroup() == INetChannelInfo::VOICE)
		bVoice = true;

	return oSendNetMsg(thisptr, edx, pMessage, bForceReliable, bVoice);
}