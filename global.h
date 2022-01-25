#pragma once
#include "Resources/common.h"
#include "../Source/Resources/SDK/datatypes/vector.h"
#include "../Source/Resources/SDK/datatypes/qangle.h"
#include "../Source/Resources/SDK/datatypes/usercmd.h"
#include "../Source/Resources/SDK/entity.h"

namespace G
{
	inline HMODULE			hDll = nullptr;
	inline CBaseEntity* pLocal = nullptr;
	inline CUserCmd* pCmd = nullptr;
	inline bool				bSendPacket = true;
	inline QAngle			angRealView = { };
	inline QAngle			angStep = { };
	inline Vector			vecCamera = { };
}
