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
    void Style();
    void RenderMenu();
}

/*--------------------Update Target Option State--------------------*/

IPT::UpdateTargetOptionState(Options.rage_bruteforce, Options.rage_bruteforcekey, Options.rage_bruteforcekeymode);
IPT::UpdateTargetOptionState(Options.rage_hideshots, Options.rage_hideshotskey, Options.rage_hideshotskeymode);
IPT::UpdateTargetOptionState(Options.rage_doubletap, Options.rage_doubletapkey, Options.rage_doubletapkeymode);
IPT::UpdateTargetOptionState(Options.rage_damageoverride, Options.rage_damageoverridekey, Options.rage_damageoverridekeymode);
IPT::UpdateTargetOptionState(Options.esp_enemy_enabled, Options.esp_enemy_enabledkey, Options.esp_enemy_enabledkeymode);
IPT::UpdateTargetOptionState(Options.esp_local_enabled, Options.esp_local_enabledkey, Options.esp_local_enabledkeymode);
IPT::UpdateTargetOptionState(Options.esp_other_thirdperson, Options.esp_other_thirdpersonkey, Options.esp_other_thirdpersonkeymode);
IPT::UpdateTargetOptionState(Options.esp_other_visualiseoneway, Options.esp_other_visualiseonewaykey, Options.esp_other_visualiseonewaykeymode);
IPT::UpdateTargetOptionState(Options.antiaim_rage_invert, Options.antiaim_rage_invertkey, Options.antiaim_rage_invertkeymode);
IPT::UpdateTargetOptionState(Options.antiaim_rage_fakeduck, Options.antiaim_rage_fakeduckkey, Options.antiaim_rage_fakeduckkeymode);
IPT::UpdateTargetOptionState(Options.antiaim_rage_teleport, Options.antiaim_rage_teleportkey, Options.antiaim_rage_teleportkeymode);
IPT::UpdateTargetOptionState(Options.antiaim_rage_crimwalk, Options.antiaim_rage_crimwalkkey, Options.antiaim_rage_crimwalkkeymode);
IPT::UpdateTargetOptionState(Options.misc_general_blockbot, Options.misc_general_blockbotkey, Options.misc_general_blockbotkeymode);
IPT::UpdateTargetOptionState(Options.misc_general_headstandbot, Options.misc_general_headstandbotkey, Options.misc_general_headstandbotkeymode);
IPT::UpdateTargetOptionState(Options.misc_general_grenadehelpervisible, Options.misc_general_grenadehelpervisiblekey, Options.misc_general_grenadehelpervisiblekeymode);
IPT::UpdateTargetOptionState(Options.misc_general_peekassist, Options.misc_general_peekassistkey, Options.misc_general_peekassistkeymode);