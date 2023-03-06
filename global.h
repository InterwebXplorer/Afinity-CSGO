#pragma once

#include <Windows.h>
#include <string>
#include "resources/sdk/datatypes/vector.h"
#include "resources/sdk/datatypes/qangle.h"
#include "resources/sdk/datatypes/usercmd.h"
#include "resources/sdk/entity.h"

namespace Global {
    inline std::string LogFileName = nullptr;
    inline HMODULE Dll = nullptr;
    inline bool MenuOpen = false;
    inline CBaseEntity* LocalPlayer = nullptr;
    inline CBaseEntity* TargetPlayer = nullptr;
    inline CUserCmd* Cmd = nullptr;
    inline bool SendPacket = true;
    inline QAngle RealView = {};
    inline QAngle AimStep = {};
    inline Vector CameraOrigin = {};
    inline bool DoubleTap = false;
    inline bool HideShots = false;
    inline bool FakeDuck = false;
    inline ImVec2 WindowSize = ImVec2(0, 0);
}