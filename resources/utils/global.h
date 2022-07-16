#pragma once
#include <windows.h>
#include "../sdk/datatypes/vector.h"
#include "../sdk/datatypes/qangle.h"
#include "../sdk/datatypes/usercmd.h"
#include "../sdk/entity.h"

namespace G {
	inline HMODULE hDll = nullptr;
	inline CBaseEntity *pLocal = nullptr;
	inline CUserCmd *pCmd = nullptr;
	inline bool bSendPacket = true;
	inline QAngle angRealView = {};
	inline QAngle angStep = {};
	inline Vector vecCamera = {};
}
