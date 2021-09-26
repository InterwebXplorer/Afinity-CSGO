' 2021-08-18 15:33:05.070275200 UTC

Namespace hazedumper
    Public Const timestamp as Integer = &H611D2831
    Public Shared Class netvars
        Public Const cs_gamerules_data as Integer = &H0
        Public Const m_ArmorValue as Integer = &HB37C
        Public Const m_Collision as Integer = &H320
        Public Const m_CollisionGroup as Integer = &H474
        Public Const m_Local as Integer = &H2FBC
        Public Const m_MoveType as Integer = &H25C
        Public Const m_OriginalOwnerXuidHigh as Integer = &H31C4
        Public Const m_OriginalOwnerXuidLow as Integer = &H31C0
        Public Const m_SurvivalGameRuleDecisionTypes as Integer = &H1328
        Public Const m_SurvivalRules as Integer = &HD00
        Public Const m_aimPunchAngle as Integer = &H302C
        Public Const m_aimPunchAngleVel as Integer = &H3038
        Public Const m_angEyeAnglesX as Integer = &HB380
        Public Const m_angEyeAnglesY as Integer = &HB384
        Public Const m_bBombDefused as Integer = &H29B0
        Public Const m_bBombPlanted as Integer = &H9A5
        Public Const m_bBombTicking as Integer = &H2980
        Public Const m_bFreezePeriod as Integer = &H20
        Public Const m_bGunGameImmunity as Integer = &H3944
        Public Const m_bHasDefuser as Integer = &HB38C
        Public Const m_bHasHelmet as Integer = &HB370
        Public Const m_bInReload as Integer = &H32A5
        Public Const m_bIsDefusing as Integer = &H3930
        Public Const m_bIsQueuedMatchmaking as Integer = &H74
        Public Const m_bIsScoped as Integer = &H3928
        Public Const m_bIsValveDS as Integer = &H7C
        Public Const m_bSpotted as Integer = &H93D
        Public Const m_bSpottedByMask as Integer = &H980
        Public Const m_bStartedArming as Integer = &H33F0
        Public Const m_bUseCustomAutoExposureMax as Integer = &H9D9
        Public Const m_bUseCustomAutoExposureMin as Integer = &H9D8
        Public Const m_bUseCustomBloomScale as Integer = &H9DA
        Public Const m_clrRender as Integer = &H70
        Public Const m_dwBoneMatrix as Integer = &H26A8
        Public Const m_fAccuracyPenalty as Integer = &H3330
        Public Const m_fFlags as Integer = &H104
        Public Const m_flC4Blow as Integer = &H2990
        Public Const m_flCustomAutoExposureMax as Integer = &H9E0
        Public Const m_flCustomAutoExposureMin as Integer = &H9DC
        Public Const m_flCustomBloomScale as Integer = &H9E4
        Public Const m_flDefuseCountDown as Integer = &H29AC
        Public Const m_flDefuseLength as Integer = &H29A8
        Public Const m_flFallbackWear as Integer = &H31D0
        Public Const m_flFlashDuration as Integer = &HA420
        Public Const m_flFlashMaxAlpha as Integer = &HA41C
        Public Const m_flLastBoneSetupTime as Integer = &H2924
        Public Const m_flLowerBodyYawTarget as Integer = &H3A90
        Public Const m_flNextAttack as Integer = &H2D70
        Public Const m_flNextPrimaryAttack as Integer = &H3238
        Public Const m_flSimulationTime as Integer = &H268
        Public Const m_flTimerLength as Integer = &H2994
        Public Const m_hActiveWeapon as Integer = &H2EF8
        Public Const m_hBombDefuser as Integer = &H29B4
        Public Const m_hMyWeapons as Integer = &H2DF8
        Public Const m_hObserverTarget as Integer = &H338C
        Public Const m_hOwner as Integer = &H29CC
        Public Const m_hOwnerEntity as Integer = &H14C
        Public Const m_hViewModel as Integer = &H32F8
        Public Const m_iAccountID as Integer = &H2FC8
        Public Const m_iClip1 as Integer = &H3264
        Public Const m_iCompetitiveRanking as Integer = &H1A84
        Public Const m_iCompetitiveWins as Integer = &H1B88
        Public Const m_iCrosshairId as Integer = &HB3E8
        Public Const m_iDefaultFOV as Integer = &H332C
        Public Const m_iEntityQuality as Integer = &H2FAC
        Public Const m_iFOVStart as Integer = &H31E8
        Public Const m_iGlowIndex as Integer = &HA438
        Public Const m_iHealth as Integer = &H100
        Public Const m_iItemDefinitionIndex as Integer = &H2FAA
        Public Const m_iItemIDHigh as Integer = &H2FC0
        Public Const m_iMostRecentModelBoneCounter as Integer = &H2690
        Public Const m_iObserverMode as Integer = &H3378
        Public Const m_iShotsFired as Integer = &HA390
        Public Const m_iState as Integer = &H3258
        Public Const m_iTeamNum as Integer = &HF4
        Public Const m_lifeState as Integer = &H25F
        Public Const m_nBombSite as Integer = &H2984
        Public Const m_nFallbackPaintKit as Integer = &H31C8
        Public Const m_nFallbackSeed as Integer = &H31CC
        Public Const m_nFallbackStatTrak as Integer = &H31D4
        Public Const m_nForceBone as Integer = &H268C
        Public Const m_nTickBase as Integer = &H3430
        Public Const m_nViewModelIndex as Integer = &H29C0
        Public Const m_rgflCoordinateFrame as Integer = &H444
        Public Const m_szCustomName as Integer = &H303C
        Public Const m_szLastPlaceName as Integer = &H35B4
        Public Const m_thirdPersonViewAngles as Integer = &H31D8
        Public Const m_vecOrigin as Integer = &H138
        Public Const m_vecVelocity as Integer = &H114
        Public Const m_vecViewOffset as Integer = &H108
        Public Const m_viewPunchAngle as Integer = &H3020
        Public Const m_zoomLevel as Integer = &H33D0
    End Class
    Public Shared Class signatures
        Public Const anim_overlays as Integer = &H2980
        Public Const clientstate_choked_commands as Integer = &H4D30
        Public Const clientstate_delta_ticks as Integer = &H174
        Public Const clientstate_last_outgoing_command as Integer = &H4D2C
        Public Const clientstate_net_channel as Integer = &H9C
        Public Const convar_name_hash_table as Integer = &H2F0F8
        Public Const dwClientState as Integer = &H588FEC
        Public Const dwClientState_GetLocalPlayer as Integer = &H180
        Public Const dwClientState_IsHLTV as Integer = &H4D48
        Public Const dwClientState_Map as Integer = &H28C
        Public Const dwClientState_MapDirectory as Integer = &H188
        Public Const dwClientState_MaxPlayer as Integer = &H388
        Public Const dwClientState_PlayerInfo as Integer = &H52C0
        Public Const dwClientState_State as Integer = &H108
        Public Const dwClientState_ViewAngles as Integer = &H4D90
        Public Const dwEntityList as Integer = &H4DA31EC
        Public Const dwForceAttack as Integer = &H31D3714
        Public Const dwForceAttack2 as Integer = &H31D3720
        Public Const dwForceBackward as Integer = &H31D375C
        Public Const dwForceForward as Integer = &H31D3768
        Public Const dwForceJump as Integer = &H524CFDC
        Public Const dwForceLeft as Integer = &H31D3780
        Public Const dwForceRight as Integer = &H31D3774
        Public Const dwGameDir as Integer = &H627780
        Public Const dwGameRulesProxy as Integer = &H52C02CC
        Public Const dwGetAllClasses as Integer = &HDB202C
        Public Const dwGlobalVars as Integer = &H588CF0
        Public Const dwGlowObjectManager as Integer = &H52EB658
        Public Const dwInput as Integer = &H51F47B0
        Public Const dwInterfaceLinkList as Integer = &H945344
        Public Const dwLocalPlayer as Integer = &HD8A2DC
        Public Const dwMouseEnable as Integer = &HD8FE28
        Public Const dwMouseEnablePtr as Integer = &HD8FDF8
        Public Const dwPlayerResource as Integer = &H31D1AA0
        Public Const dwRadarBase as Integer = &H51D7F64
        Public Const dwSensitivity as Integer = &HD8FCC4
        Public Const dwSensitivityPtr as Integer = &HD8FC98
        Public Const dwSetClanTag as Integer = &H8A1B0
        Public Const dwViewMatrix as Integer = &H4D94B04
        Public Const dwWeaponTable as Integer = &H51F5270
        Public Const dwWeaponTableIndex as Integer = &H325C
        Public Const dwYawPtr as Integer = &HD8FA88
        Public Const dwZoomSensitivityRatioPtr as Integer = &HD94D28
        Public Const dwbSendPackets as Integer = &HD779A
        Public Const dwppDirect3DDevice9 as Integer = &HA7050
        Public Const find_hud_element as Integer = &H2E75F720
        Public Const force_update_spectator_glow as Integer = &H3AF66A
        Public Const interface_engine_cvar as Integer = &H3E9EC
        Public Const is_c4_owner as Integer = &H3BC2C0
        Public Const m_bDormant as Integer = &HED
        Public Const m_flSpawnTime as Integer = &HA370
        Public Const m_pStudioHdr as Integer = &H294C
        Public Const m_pitchClassPtr as Integer = &H51D8200
        Public Const m_yawClassPtr as Integer = &HD8FA88
        Public Const model_ambient_min as Integer = &H58C064
        Public Const set_abs_angles as Integer = &H1E0AC0
        Public Const set_abs_origin as Integer = &H1E0900
    End Class
End Namespace
