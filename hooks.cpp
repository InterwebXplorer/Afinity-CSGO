#include <intrin.h>
#include <Windows.h>
#include "resources/minhook/minhook.h"
#include "resources/utils/inputsystem.h"
#include "resources/utils/consolelogging.h"
#include "resources/utils/filelogging.h"
#include "resources/utils/utils.h"
#include "resources/utils/draw.h"
#include "resources/utils/detourhook.h"
#include "resources/utils/math.h"
#include "resources/sdk/interfaces.h"
#include "features/features.h"
#include "options.h"
#include "hooks.h"
#include "menu.h"
#include "global.h"

//Options.esp_other_radarhack

bool Hooks::Setup() {
    if (MH_Initialize() != MH_OK) {
        WriteToLog("[Error] Failed to initialize minhook");
        return false;
    }

    if (!DetourHookManager::DHMReset.Create(Memory::GetVFunc(I::DirectDevice, VTABLEINDEX::RESET), &Reset)) {
        WriteToLog("[Error] Failed to hook function <RESET>");
        return false;
    }

    if (!DetourHookManager::DHMPresent.Create(Memory::GetVFunc(I::DirectDevice, VTABLEINDEX::PRESENT), &Present)) {
        WriteToLog("[Error] Failed to hook function <PRESENT>");
        return false;
    }

    if (!DetourHookManager::DHMAllocateKeyValuesMemory.Create(Memory::GetVFunc(I::KeyValuesSystem, VTABLEINDEX::ALLOCATEKEYVALUESMEMORY), &AllocateKeyValuesMemory)) {
        WriteToLog("[Error] Failed to hook function <ALLOCATEKEYVALUESMEMORY>");
        return false;
    }

    if (!DetourHookManager::DHMCreateMoveProxy.Create(Memory::GetVFunc(I::Client, VTABLEINDEX::CREATEMOVE), &CreateMoveProxy)) {
        WriteToLog("[Error] Failed to hook function <CREATEMOVE>");
        return false;
    }

    if (!DetourHookManager::DHMFrameStageNotify.Create(Memory::GetVFunc(I::Client, VTABLEINDEX::FRAMESTAGENOTIFY), &FrameStageNotify)) {
        WriteToLog("[Error] Failed to hook function <FRAMESTAGENOTIFY>");
        return false;
    }

    if (!DetourHookManager::DHMFindMaterial.Create(Memory::GetVFunc(IMaterial, VTABLEINDEX::FINDMATERIAL), &FindMaterial)) {
        WriteToLog("[Error] Failed to hook function <FINDMATERIAL>")
        return false;
    }

    if (!DetourHookManager::DHMOverrideView.Create(Memory::GetVFunc(I::ClientMode, VTABLEINDEX::OVERRIDEVIEW), &OverrideView)) {
        WriteToLog("[Error] Failed to hook function <OVERRIDEVIEW>");
        return false;
    }

    if (!DetourHookManager::DHMDoPostScreenEffects.Create(Memory::GetVFunc(I::ClientMode, VTABLEINDEX::DOPOSTSCREENEFFECTS), &DoPostScreenEffects)) {
        WriteToLog("[Error] Failed to hook function <DOPOSTSCREENEFFECTS>");
        return false;
    }

    if (!DetourHookManager::DHMIsConnected.Create(Memory::GetVFunc(I::Engine, VTABLEINDEX::ISCONNECTED), &IsConnected)) {
        WriteToLog("[Error] Failed to hook function <ISCONNECTED>");
        return false;
    }

    if (!DetourHookManager::DHMListLeavesInBox.Create(Memory::GetVFunc(I::Engine->GetBSPTreeQuery, VTABLEINDEX::LISTLEAVESINBOX), &ListLeavesInBox)) {
        WriteToLog("[Error] Failed to hook function <LISTLEAVESINBOX>");
        return false;
    }

    if (!DetourHookManager::DHMPaintTraverse.Create(Memory::GetVFunc(I::Panel, VTABLEINDEX::PAINTTRAVERSE), &PaintTraverse)) {
        WriteToLog("[Error] Failed to hook function <PAINTTRAVERSE>");
        return false;
    }

    if (!DetourHookManager::DHMDrawModel.Create(Memory::GetVFunc(I::StudioRender, VTABLEINDEX::DRAWMODEL), &DrawModel)) {
        WriteToLog("[Error] Failed to hook function <DRAWMODEL>");
        return false;
    }

    if (!DetourHookManager::DHMRenderSmokeOverlay.Create(Memory::GetVFunc(I::ViewRender, VTABLEINDEX::RENDERSMOKEOVERLAY), &RenderSmokeOverlay)) {
        WriteToLog("[Error] Failed to hook function <RENDERSMOKEOVERLAY>");
        return false;
    }

    if (!DetourHookManager::DHMRunCommand.Create(Memory::GetVFunc(I::Prediction, VTABLEINDEX::RUNCOMMAND), &RunCommand)) {
        WriteToLog("[Error] Failed to hook function <RUNCOMMAND>");
        return false;
    }

    if (!DetourHookManager::DHMSGCSendMessage.Create(Memory::GetVFunc(I::SteamGameCoordinator, VTABLEINDEX::SENDMESSAGE), &SGCSendMessage)) {
        WriteToLog("[Error] Failed to hook function <SENDMESSAGE>");
        return false;
    }

    if (!DetourHookManager::DHMRetrieveMessage.Create(Memory::GetVFunc(I::SteamGameCoordinator, VTABLEINDEX::RETRIEVEMESSAGE), &RetrieveMessage)) {
        WriteToLog("[Error] Failed to hook function <RETRIEVEMESSAGE>");
        return false;
    }

    if (!DetourHookManager::DHMLockCursor.Create(Memory::GetVFunc(I::Surface, VTABLEINDEX::LOCKCURSOR), &LockCursor)) {
        WriteToLog("[Error] Failed to hook function <LOCKCURSOR>");
        return false;
    }

    if (!DetourHookManager::DHMShouldDrawFog.Create(Memory::GetVFunc(I::ClientMode, VTABLEINDEX::SHOULDDRAWFOG), &ShouldDrawFog)) {
        WriteToLog("[Error] Failed to hook function <SHOULDDRAWFOG>");
        return false;
    }

    return true;
}

void Hooks::Restore() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

long D3DAPI Hooks::Reset(IDirect3DDevice9* Device, D3DPRESENT_PARAMETERS* PresentParameters) {
    static auto OriginalReset = DetourHookManager::DHMReset.GetOriginal<decltype(&Reset)>();

    if (!Draw::IsInitialized)
        return OriginalReset(Device, PresentParameters);

    ImGui_ImplDX9_InvalidateDeviceObjects();

    const HRESULT ResetResult = OriginalReset(Device, PresentParameters);

    if (ResetResult == D3D_OK)
        ImGui_ImplDX9_CreateDeviceObjects();

    return ResetResult;
}

long D3DAPI Hooks::Present(IDirect3DDevice9* Device, RECT* SourceRect, RECT* DestinationRect, HWND DestinationWindowOverride, RGNDATA* DirtyRegion) {
    static auto OriginalPresent = DetourHookManager::DHMPresent.GetOriginal<decltype(&Present)>();

    if (!Draw::IsInitialized)
        Draw::Setup(Device);

    else if (Draw::IsInitialized) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //RENDER STUFF

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }

    return OriginalPresent(Device, SourceRect, DestinationRect, DestinationWindowOverride, DirtyRegion);
}

void* __fastcall Hooks::AllocateKeyValuesMemory(IKeyValuesSystem* thisptr, int edx, int Size) {
    static auto OriginalAllocateKeyValuesMemory = DetourHookManager::DHMAllocateKeyValuesMemory.GetOriginal<decltype(&AllocateKeyValuesMemory)>();

    static const std::uintptr_t AKVMEngine = Memory::GetAbsoluteAddress(Memory::FindPattern(ENGINE_DLL, "E8 ? ? ? ? 83 C4 08 84 C0 75 10 FF 75 0C") + 0x1) + 0x4A;
    static const std::uintptr_t AKVMClient = Memory::GetAbsoluteAddress(Memory::FindPattern(CLIENT_DLL, "E8 ? ? ? ? 83 C4 08 84 C0 75 10") + 0x1) + 0x3E;

    const std::uintptr_t ReturnAddress = reinterpret_cast<std::uintptr_t>(_ReturnAddress());

    if (ReturnAddress == AKVMEngine || ReturnAddress == AKVMClient)
        return nullptr;

    return OriginalAllocateKeyValuesMemory(thisptr, edx, Size);
}

static void __stdcall Hooks::CreateMove(int SequenceNumber, float InputSampleFrametime, bool IsActive, bool& SendPacket) {
    static auto OriginalCreateMove = DetourHookManager::DHMCreateMoveProxy.GetOriginal<decltype(&CreateMoveProxy)>();
    
    OriginalCreateMove(I::Client, 0, SequenceNumber, InputSampleFrametime, SendPacket);

    CUserCmd* Cmd = I::Input->GetUserCmd(SequenceNumber);
    CVerifiedUserCmd* VerifiedCmd = I::Input->GetVerifiedCmd(SequenceNumber);

    if (!Cmd || !VerifiedCmd || !IsActive)
        return;

    Global::Cmd = Cmd;
    CBaseEntity* LocalPlayer = CBaseEntity::GetLocalPlayer();
    Global::LocalPlayer = LocalPlayer;

    INetChannel* NetChannel = I::ClientState->pNetChannel;
    QAngle OldViewAngle = Cmd->angViewPoint;

    //bunnyhop and other movements
    //CMiscellaneous::Get().Run(pCmd, pLocal, bSendPacket);

    if (I::ClientState->iDeltaTick > 0)
        I::Prediction->Update(I::ClientState->iDeltaTick,  I::ClientState->iDeltaTick > 0, I::ClientState->iLastCommandAck, I::ClientState->iLastOutgoingCommand + I::ClientState->nChokedCommands);

    /*
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
    */

   /*
	if (pLocal->IsAlive())
		CMiscellaneous::Get().MovementCorrection(pCmd, angOldViewPoint);
   */

    if (Options.misc_general_antiuntrusted) {
        Cmd->angViewPoint.Normalize();
        Cmd->angViewPoint.Clamp();
    }

    if (Options.misc_general_fakeping) {
        /*
        void misc::fakeping() { //TODO
            if (!Options.misc_general_fakeping)
                return;

            //Options.misc_general_fakepingamount
        }
        */
    }
    /*
        CLagCompensation::Get().UpdateIncomingSequences(pNetChannel);
	else
		CLagCompensation::Get().ClearIncomingSequences();
    */

    if (!NetChannel) {
        if (!DetourHookManager::DHMSendNetMsg.IsHooked())
            DetourHookManager::DHMSendNetMsg.Create(Memory::GetVFunc(NetChannel, VTABLEINDEX::SENDNETMSG), &SendNetMsg);

        if (!DetourHookManager::DHMSendDatagram.IsHooked())
            DetourHookManager::DHMSendDatagram.Create(Memory::GetVFunc(NetChannel, VTABLEINDEX::SENDDATAGRAM), &SendDatagram);
    }

    Global::RealView = Cmd->angViewPoint;
    Global::SendPacket = SendPacket;

    VerifiedCmd->userCmd = *Cmd;
    VerifiedCmd->uHashCRC = Cmd->GetChecksum();
}

__declspec(naked) void __fastcall Hooks::CreateMoveProxy(IBaseClientDll* thisptr, int edx, int SequenceNumber, float InputSampleFrameTime, bool IsActive) {
    __asm {
        push    ebp
		mov		ebp, esp;
		push	ebx;
		push	esp;
		push	dword ptr[IsActive];
		push	dword ptr[InputSampleFrametime];
		push	dword ptr[SequenceNumber];
		call	CreateMove;
		pop		ebx;
		pop		ebp;
		retn	0Ch;
    }
}

void __fastcall Hooks::FrameStageNotify(IBaseClientDll* thisptr, int edx, EClientFrameStage Stage) {
    static auto OriginalFrameStageNotify = DetourHookManager::DHMFrameStageNotify.GetOriginal<decltype(&FrameStageNotify)>();

    if (!I::Engine->IsInGame()) {
        //CLagCompensation::Get().ClearIncomingSequences();
        return OriginalFrameStageNotify(thisptr, edx, Stage);
    }

    if (I::Engine->IsTakingScreenshot() && Options.esp_other_streamproof)
        return OriginalFrameStageNotify(thisptr, edx, Stage);

    CBaseEntity* LocalPlayer = CBaseEntity::GetLocalPlayer();   

    if (!LocalPlayer)
        return OriginalFrameStageNotify(thisptr, edx, Stage);

    static QAngle OldAimPunch = {};
    static QAngle OldViewPunch = {};

    switch (Stage) {
        case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
            if (Options.misc_general_preservekillfeed) {

            }
        break;

        case FRAME_NET_UPDATE_POSTDATAUPDATE_END:

        break;

        case FRAME_NET_UPDATE_END:

        break;

        case FRAME_RENDER_START:
            switch (Options.esp_other_removals) {
                case SCOPEOVERLAY:
                    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon;

                    if (!ActiveWeapon)
                        return OriginalFrameStageNotify(thisptr, edx, Stage);
        
	                const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
	                const CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

                    if (!ActiveWeaponData)
                        return OriginalFrameStageNotify(thisptr, edx, Stage);

                    if (!ActiveWeaponData->nWeaponType == WEAPONTYPE_SNIPER)
                        return OriginalFrameStageNotify(thisptr, edx, Stage);

                    if (LocalPlayer->IsScoped()) {
                        I::ConVar->FindVar("cl_drawhud")->SetValue(0);
                        ImDrawList::AddLine(ImVec2(0, Global::WindowSize.y / 2), ImVec2(Global::WindowSize.x, Global::WindowSize.y / 2), ImVec4(0, 0, 0, 255))
                        ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2, 0), ImVec2(Global::WindowSize.x / 2, Global::WindowSize.y), ImVec4(0, 0, 0, 255))
                    }
                    else
                        I::ConVar->FindVar("cl_drawhud")->SetValue(1);

                    MiscSettings::REMOVEScopeOverlay = true;
                break;

                case SCOPEZOOM:
                    MiscSettings::REMOVEScopeZoom = true;
                break;

                case VIEWPUNCH:
                    if (LocalPlayer->IsAlive()) {
                        OldViewPunch = LocalPlayer->GetViewPunch();
                        LocalPlayer->GetViewPunch() = QAngle{};
                    }
                break;

                case AIMPUNCH:
                    if (LocalPlayer->IsAlive()) {
                        OldAimPunch = LocalPlayer->GetPunch();
                        LocalPlayer->GetPunch() = QAngle{};
                    }
                break;

                case SMOKEEFFECTS:
                    static const std::array<const char*, 4U> SmokeMaterials = {
                        "particle/vistasmokev1/vistasmokev1_fire",
                        "particle/vistasmokev1/vistasmokev1_smokegrenade",
	                    "particle/vistasmokev1/vistasmokev1_emods",
	                    "particle/vistasmokev1/vistasmokev1_emods_impactdust"
                    };

                    for (const auto& SmokeMaterial : SmokeMaterials) {
                        if (IMaterial* Material = I::MaterialSystem->FindMaterial(SmokeMaterial, TEXTURE_GROUP_OTHER); Material != nullptr && !Material->IsErrorMaterial())
                            Material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
                    }

                    MiscSettings::REMOVESmoke = true;
                break;

                case FLASHEFFECTS:
                    LocalPlayer->GetFlashAlpha() = 0.0f;
                break;
                
                case FOG:
                    MiscSettings::REMOVEFog = true;
                break;

                case POSTPROCESSING:
                    CConVar* PostProcessingCVar = I::ConVar->FindVar("mat_postprocess_enable");

                    if (PostProcessingCVar->flValue != 0)
                        PostProcessingCVar->SetValue(0);
                break;

                case ARMS:
                    MiscSettings::REMOVEArms = true;
                break;

                case WEAPON:
                    MiscSettings::REMOVEWeapon = true;
                break;
            }
        break;

        case FRAME_RENDER_END:

        break;
    }

    OriginalFrameStageNotify(thisptr, edx, Stage);
}

IMaterial* __fastcall Hooks::FindMaterial(void* thisptr, void*, const char* MaterialName, const char* TextureGroupName, bool Complain, bool ComplainPrefix) {
    static auto OriginalFindMaterial = DetourHookManager::DHMFindMaterial.GetOriginal<decltype(&FindMaterial)>();

    if (strcmp(MaterialName, "dev/scope_blurovgerlay") == 0 && MiscSettings::REMOVEScopeOverlay) {
        static auto NoMaterial = OriginalFindMaterial(thisptr, "dev/clearalpha", nullptr, Complain, ComplainPrefix);
        return NoMaterial;
    }

    //repace world material with grey material

    return OriginalFindMaterial(thisptr, MaterialName, TextureGroupName, Complain, ComplainPrefix);
}

void __fastcall Hooks::OverrideView(IClientModeShared* thisptr, int edx, CViewSetup* ViewSetup) {
    static auto OriginalOverrideView =  DetourHookManager::DHMOverrideView.GetOriginal<decltype(&OverrideView)>();
    
    if (I::Engine->IsInGame() || I::Engine->IsTakingScreenshot && Options.esp_other_streamproof)
        return OriginalOverrideView(thisptr, edx, ViewSetup);
    
    CBaseEntity* LocalPLayer = CBaseEntity::GetLocalPlayer();

    if (!LocalPLayer)
        return OriginalOverrideView(thisptr, edx, ViewSetup);

    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

    if (!ActiveWeapon)
        return OriginalOverrideView(thisptr, edx, ViewSetup);

    const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
    CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

    if (!ActiveWeaponData)
		return OriginalOverrideView(thisptr, edx, ViewSetup);

    if (Options.esp_other_thirdperson) {
        bool ThirdPerson = true;
        float Distance = reinterpret_cast<float>(Options.esp_other_thirdpersondistance);

        if (!LocalPLayer->IsAlive() && Options.esp_other_thirdpersonondeath)
            ThirdPerson = true;

        if (ActiveWeaponData->nWeaponType == WEAPONTYPE_GRENADE && Options.esp_other_thirdpersondisablenade)
            ThirdPerson = false;

        if (I::Input->bCameraInThirdPerson)
            return OriginalOverrideView(thisptr, edx, ViewSetup);

        QAngle ViewAngles = {};
        I::Engine->GetViewAngles(ViewAngles);
        ViewAngles.z = 0.0f;
        Vector Forward = Math::AngleVectors(ViewAngles);
        Vector EyePosition = LocalPLayer->GetEyePosition();
        
        Vector Max = {16.0f, 16.0f, 16.0f};
        Ray_t Ray(EyePosition, EyePosition - Forward * Distance, -Max, Max);
        CTraceFilter* Filter = LocalPLayer;
        Trace_t Trace;
        I::EngineTrace->TraceRay(Ray, MASK_SOLID, &Filter, &Trace);

        if (Trace.flFraction < 1.0f)
            Distance *= Trace.flFraction;

        ViewAngles.z = Distance;

        I::Input->bCameraInThirdPerson = true;
        I::Input->vecCameraOffset = ViewAngles;

        I::ConVar->FindVar("cl_updatevisibility")->SetValue(1);
    }

    if (MiscSettings::REMOVEScopeZoom) {
	    if (!ActiveWeaponData->nWeaponType == WEAPONTYPE_SNIPER)
		    return OriginalOverrideView(thisptr, edx, ViewSetup);

        if (LocalPLayer->IsScoped())
            ViewSetup->flFOV = 90.0f;
    }

    OriginalOverrideView(thisptr, edx, ViewSetup);
}

int __fastcall Hooks::DoPostScreenEffects(IClientModeShared* thisptr, int edx, CViewSetup* Setup) { //
    static auto OriginalDoPostScreenEffects = DetourHookManager::DHMDoPostScreenEffects.GetOriginal<decltype(&DoPostScreenEffects)>();


    return OriginalDoPostScreenEffects
}

bool __fastcall Hooks::IsConnected(IEngineClient* thisptr, int edx) {
    static auto OriginalIsConnected = DetourHookManager::DHMIsConnected.GetOriginal<decltype(&IsConnected)>();
    static const std::uintptr_t LoadoutAllowed = Memory::FindPattern(CLIENT_DLL, "84 C0 75 05 B0 01 5F");

    if (reinterpret_cast<std::uintptr_t>(_ReturnAddress()) == LoadoutAllowed && Options.misc_general_unlockinventory)
        return false;

    return OriginalIsConnected(thisptr, edx);
}

int __fastcall Hooks::ListLeavesInBox(void* thisptr, int edx, const Vector& Mins, const Vector& Maxs, unsigned short* List, int ListMax) {
    static auto OriginalListLeavesInBox = DetourHookManager::DHMListLeavesInBox.GetOriginal<decltype(&ListLeavesInBox)>();
    static std::uintptr_t InsertIntoTree = (Memory::FindPattern(CLIENT_DLL, "56 52 FF 50 18") + 0x5);

    if (Options.esp_enemy_enabled && Options.esp_enemy_disableoocclusion) {
        const auto Info = *reinterpret_cast<RenderableInfo_t**>(reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) + 0x14);
        if (!Info) {
            const auto Renderable = Info->pRenderable;
            if (!Renderable) {
                const auto Entity = Renderable->GetIClientUnknown()->GetBaseEntity();
                if (!Entity && Entity->IsPlayer()) {
                    Info->uFlags &=  ~RENDER_FLAGS_FORCE_OPAQUE_PASS;
                    Info->uFlags2 |= RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE;

                    constexpr Vector MapMin(MIN_COORD_FLOAT, MIN_COORD_FLOAT, MIN_COORD_FLOAT);
                    constexpr Vector MapMax(MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT);
                    return OriginalListLeavesInBox(thisptr, edx, MapMin, MapMax, List, ListMax);
                }
            }
        }
    }

    return OriginalListLeavesInBox(thisptr, edx, Mins, Maxs, List, ListMax);
}

void __fastcall Hooks::PaintTraverse(ISurface* thisptr, int edx, unsigned int Panel, bool ForceRepaint, bool force) { //
    static auto OrignalPaintTraverse = DetourHookManager::DHMPaintTraverse.GetOriginal<decltype(&PaintTraverse)>();
}

void __fastcall Hooks::DrawModel(IStudioRender* thisptr, int edx, DrawModelResults_t* Results, const DrawModelInfo_t& ModelInfo, matrix3x4_t* BoneToWorld, float* FlexWeights, float* FlexDelayedWeights, const Vector& ModelOrigin, int Flags) {
    static auto OriginalDrawModel = DetourHookManager::DHMDrawModel.GetOriginal<decltype(&DrawModel)>();

    if (!I::Engine->IsInGame() || I::Engine->IsTakingScreenshot() && Options.esp_other_streamproof)
        return OriginalDrawModel(thisptr, edx, Results, ModelInfo, BoneToWorld, FlexWeights, FlexDelayedWeights, ModelOrigin, Flags);

    
    //enemy chams
    if (Options.esp_enemy_enabled) {
        static IMaterial* EnemyVisibleMaterial = I::MaterialSystem->FindMaterial(Utils::GetChamsMaterialFromOption(Options.esp_enemy_visiblechamsmaterial), nullptr);
        static IMaterial* EnemyOccludedMaterial = I::MaterialSystem->FindMaterial(Utils::GetChamsMaterialFromOption(Options.esp_enemy_occludedchamsmaterial), nullptr);
        static IMaterial* EnemyBacktrackMaterial = I::MaterialSystem->FindMaterial("", TEXTURE_GROUP_OTHER);

        if (Options.esp_enemy_chamsvisible) {
            //Options.esp_enemy_chamsbacktrackcolor
        }

        if (Options.esp_enemy_chamsoccluded) {
            //Options.esp_enemy_chamsoccludedcolor
        }

        if (Options.esp_enemy_chamsbacktrack) {
            //Options.esp_enemy_chamsbacktrackcolor
        }
    }

/*
    if (Options.esp_enemy_chamsglow) { //bloom
        //Options.esp_enemy_chamsglowcolor
    }

    if (Options.esp_enemy_outline) {
        //Options.esp_enemy_outlinecolor
    }
*/

    //local chams
    if (Options.esp_local_enabled) {
        static IMaterial* LocalMaterial = I::MaterialSystem->FindMaterial(Utils::GetChamsMaterialFromOption(Options.esp_local_chamsmaterial), nullptr);
        static IMaterial* LocalDesyncMaterial = I::MaterialSystem->FindMaterial("", TEXTURE_GROUP_OTHER);
        static IMaterial* LocalBacktrackMaterial = I::MaterialSystem->FindMaterial("", TEXTURE_GROUP_OTHER);
        static IMaterial* LocalArmsMaterial = I::MaterialSystem->FindMaterial(Utils::GetChamsMaterialFromOption(Options.esp_local_armchamsmaterial), nullptr);
        static IMaterial* LocalArmsMaterial = I::MaterialSystem->FindMaterial(Utils::GetChamsMaterialFromOption(Options.esp_local_weaponchamsmaterial), nullptr);

        //Options.esp_local_scopeblend

        if (Options.esp_local_chamsbacktrack) {
            //Options.esp_local_chamsbacktrackcolor
        }

        if (Options.esp_local_chams) {
            //Options.esp_local_chamscolor
        }

        if (Options.esp_local_desyncchams) {
            //Options.esp_local_desyncchamscolor
        }

        if (Options.esp_local_armchams) {
            //Options.esp_local_armchamscolor
        }

        if (Options.esp_local_weaponchams) {
            //Options.esp_local_weaponchamscolor
        }
    }

/*
        OPTION(bool, Options.esp_local_glow, false);  //bloom
        OPTION(ImVec4, Options.esp_local_glowcolor, ImVec4(0, 0, 0, 0));
*/

    if (Options.esp_other_bombchams) {
        static IMaterial* BombChamsMaterial = Utils::GetChamsMaterialFromOption(Options.esp_other_bombchamsmaterial);
        //Options.esp_other_bombchamscolor
    }
/*
        //Options.esp_other_bombchamscolor

    if (Options.esp_other_bombglow) {
        //Options.esp_other_bombglowcolor
    }

    if (Options.esp_other_droppedweaponchams) {
        //Options.esp_other_droppedweaponchamscolor
    
        switch (Options.esp_other_droppedweaponchamsmateria) {
            case MAT1:

                break;

            case MAT2:

                break;
        }
    }

    if (Options.esp_other_droppedweaponglow) {
        //Options.esp_other_droppedweaponglowcolor
    }
}

*/


    OriginalDrawModel(thisptr, edx, Results, ModelInfo, BoneToWorld, FlexWeights, FlexDelayedWeights, ModelOrigin, Flags);
}

void __fastcall Hooks::RenderSmokeOverlay(IViewRender* thisptr, int edx, bool PreviewModel) {
    static auto OriginalRenderSmokeOverlay = DetourHookManager::DHMRenderSmokeOverlay.GetOriginal<decltype(&RenderSmokeOverlay)>();

    if (MiscSettings::REMOVESmoke)
        *reinterpret_cast<float*>(reinterpret_cast<std::uintptr_t>(thisptr) + 0x588) = 0.0f;
    else
        OriginalRenderSmokeOverlay(thisptr, edx, PreviewModel);
}

void __fastcall Hooks::RunCommand(IPrediction* thisptr, int edx, CBaseEntity* Entity, CUserCmd* Cmd, IMoveHelper* MoveHelper) { //
    static auto OriginalRunCommand = DetourHookManager::DHMRunCommand.GetOriginal<decltype(&RunCommand)>();

}

void __fastcall Hooks::SGCSendMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t MsgType, const void* Data, std::uint32_t Data) {
    static auto OriginalSGCSendMessage = DetourHookManager::DHMSGCSendMessage.GetOriginal<decltype(&SGCSendMessage)>();

    std::uint32_t MessageType = MsgType & 0x7FFFFFFF;
    void* DataMutable = const_cast<void*>(Data);

    const int Status = OriginalSGCSendMessage(thisptr, edx, MsgType, DataMutable, Data);

    if (Status != EGCResultOK)
		return Status;

    return Status;
}

int __fastcall Hooks::RetrieveMessage(ISteamGameCoordinator* thisptr, int edx, std::uint32_t* MsgType, void* DestinationBufferPtr, std::uint32_t DestinationBufferSize, std::uint32_t* MsgSize) {
    static auto OriginalRetrieveMessage = DetourHookManager::DHMRetrieveMessage.GetOriginal<decltype(&RetrieveMessage)>();
    const int Status = OriginalRetrieveMessage(thisptr, edx, MsgType, DestinationBufferPtr, DestinationBufferSize, MsgSize);

    if (Status != EGCResultOK)    
        return Status;

    const std::uint32_t MessageType = *MsgType & 0x7FFFFFFF;

    if (Options.misc_general_autoaccept && MessageType == 9177) {
        Utils::SetLocalPlayerReady();
        Beep(500, 800);
        FLASHWINFO.cbSize = sizeof(FLASHWINFO);
        FLASHWINFO.hwnd = InputSystem::Window;
        FLASHWINFO.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
        FLASHWINFO.uCount = 0;
        FLASHWINFO.dwTimeout = 0;
        FlashWindowEx(FLASHWINFO);
    }

    return Status;
}   

void __fastcall Hooks::LockCursor(ISurface* thisptr, int edx) {
    static auto OriginalLockCursor = DetourHookManager::DHMLockCursor.GetOriginal<decltype(&LockCursor)>();

    if (Menu::IsOpen) {
        I::Surface->UnLockCursor();
        return;
    }

    OriginalLockCursor(thisptr, edx);
}

bool __fastcall Hooks::SendNetMsg(INetChannel* thisptr, int edx, INetMessage* Message, bool ForceReliable, bool Voice) {
    static auto OriginalSendNetMsg = DetourHookManager::DHMSendNetMsg.GetOriginal<decltype(&SendNetMsg)>();

    if (Options.misc_general_bypasssvpure) {
        if (Message->GetType() == 14)
            return false;
    }

    if (Message->GetGroup() == INetChannelInfo::VOICE)
		Voice = true;

    return OriginalSendNetMsg(thisptr, edx, Message, ForceReliable, Voice);
}

bool __fastcall Hooks::ShouldDrawFog(std::uintptr_t ecx, std::uintptr_t edx) {
    static auto OriginalShouldDrawFog = DetourHookManager::DHMShouldDrawFog.GetOriginal<decltype(&ShouldDrawFog)>();
    static const std::uintptr_t ShouldDrawFogAddress = Memory::GetAbsoluteAddress(Memory::FindPattern(CLIENT_DLL, "E8 ? ? ? ? 8B 0D ? ? ? ? 0F B6 D0") + 0x1) + 0x52;

    const std::uintptr_t ReturnAddress = reinterpret_cast<std::uintptr_t>(_ReturnAddress());

    if (ReturnAddress == ShouldDrawFogAddress && MiscSettings::REMOVEFog)
        return false;

    return OriginalShouldDrawFog(ecx, edx);
}