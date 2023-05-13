#pragma once
#include <functional>
#include <Windows.h>
#include <d3d9.h>
#include "resources/imgui/imgui.h"
#include "resources/imgui/imgui_freetype.h"
#include "resources/imgui/imgui_internal.h"
#include "resources/imgui/impl/imgui_impl_dx9.h"
#include "resources/imgui/impl/imgui_impl_win32.h"
#include "resources/utils/inputsystem.h"

namespace Menu {
    void RenderMenu(IDirect3DDevice9* Device);
}

/*--------------------Update Target Option State--------------------*/

InputSystem::UpdateTargetOptionState(Options.rage_bruteforce, Options.rage_bruteforcekey, Options.rage_bruteforcekeymode);
InputSystem::UpdateTargetOptionState(Options.rage_hideshots, Options.rage_hideshotskey, Options.rage_hideshotskeymode);
InputSystem::UpdateTargetOptionState(Options.rage_doubletap, Options.rage_doubletapkey, Options.rage_doubletapkeymode);
InputSystem::UpdateTargetOptionState(Options.rage_damageoverride, Options.rage_damageoverridekey, Options.rage_damageoverridekeymode);
InputSystem::UpdateTargetOptionState(Options.esp_enemy_enabled, Options.esp_enemy_enabledkey, Options.esp_enemy_enabledkeymode);
InputSystem::UpdateTargetOptionState(Options.esp_local_enabled, Options.esp_local_enabledkey, Options.esp_local_enabledkeymode);
InputSystem::UpdateTargetOptionState(Options.esp_other_thirdperson, Options.esp_other_thirdpersonkey, Options.esp_other_thirdpersonkeymode);
InputSystem::UpdateTargetOptionState(Options.esp_other_visualiseoneway, Options.esp_other_visualiseonewaykey, Options.esp_other_visualiseonewaykeymode);
InputSystem::UpdateTargetOptionState(Options.antiaim_rage_invert, Options.antiaim_rage_invertkey, Options.antiaim_rage_invertkeymode);
InputSystem::UpdateTargetOptionState(Options.antiaim_rage_fakeduck, Options.antiaim_rage_fakeduckkey, Options.antiaim_rage_fakeduckkeymode);
InputSystem::UpdateTargetOptionState(Options.antiaim_rage_teleport, Options.antiaim_rage_teleportkey, Options.antiaim_rage_teleportkeymode);
InputSystem::UpdateTargetOptionState(Options.antiaim_rage_crimwalk, Options.antiaim_rage_crimwalkkey, Options.antiaim_rage_crimwalkkeymode);
InputSystem::UpdateTargetOptionState(Options.misc_general_blockbot, Options.misc_general_blockbotkey, Options.misc_general_blockbotkeymode);
InputSystem::UpdateTargetOptionState(Options.misc_general_headstandbot, Options.misc_general_headstandbotkey, Options.misc_general_headstandbotkeymode);
InputSystem::UpdateTargetOptionState(Options.misc_general_grenadehelpervisible, Options.misc_general_grenadehelpervisiblekey, Options.misc_general_grenadehelpervisiblekeymode);
InputSystem::UpdateTargetOptionState(Options.misc_general_peekassist, Options.misc_general_peekassistkey, Options.misc_general_peekassistkeymode);