#pragma once
// used: winapi includes
#include "common.h"
// used: vector
#include "../Source/Resources/SDK/datatypes/vector.h"
// used: qangle
#include "../Source/Resources/SDK/datatypes/qangle.h"
// used: usercmd
#include "../Source/Resources/SDK/datatypes/usercmd.h"
// used: baseentity
#include "../Source/Resources/SDK/entity.h"

/*
 * GLOBALS
 * globally defined values
 * may used in any source/header file what includes in
 */
namespace G
{
	// current module
	inline HMODULE			hDll = nullptr;
	// last localplayer pointer
	inline CBaseEntity*		pLocal = nullptr;
	// last cmd pointer
	inline CUserCmd*		pCmd = nullptr;
	// last sendpacket state
	inline bool				bSendPacket = true;
	// last viewangles with allowed sendpacket
	inline QAngle			angRealView = { };
	// last aimstep restriction
	inline QAngle			angStep = { };
	// camera origin
	inline Vector			vecCamera = { };
}
