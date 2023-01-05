#pragma once

#include <Windows.h>
#include <string>
#include "resources/sdk/datatypes/vector.h"
#include "resources/sdk/datatypes/qangle.h"
#include "resources/sdk/datatypes/usercmd.h"
#include "resources/sdk/entity.h"

namespace Global {
    inline std::string logfilename = nullptr;
    inline HMODULE hDll = nullptr;
    inline CBaseEntity* pLocal = nullptr;
    inline CBaseEntity* pTarget = nullptr;
    inline CUserCmd* pCmd = nullptr;
    inline bool bSendPacket = true;
    inline QAngle angRealView = {};
    inline Qangle angStep = {};
    inline Vector vecCamera = {};
    inline bool doubletap = false;
    inline bool hideshots = false;
    inline bool fakeduck = false;
    inline bool teleport = false;
}