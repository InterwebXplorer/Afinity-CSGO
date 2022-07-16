#pragma once
#include "../hash/crc32.h"
#include "vector.h"
#include "qangle.h"

#pragma region usercmd_enumerations

enum ECommandButtons : int
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_SECOND_ATTACK = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_LEFT_ALT = (1 << 14),
	IN_RIGHT_ALT = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_FIRST_WEAPON = (1 << 20),
	IN_SECOND_WEAPON = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_FIRST_GRENADE = (1 << 23),
	IN_SECOND_GRENADE = (1 << 24),
	IN_MIDDLE_ATTACK = (1 << 25),
	IN_USE_OR_RELOAD = (1 << 26)
};
#pragma endregion

#pragma pack(push, 4)
class CUserCmd
{
public:
	virtual ~CUserCmd() {}
	int iCommandNumber;
	int iTickCount;
	QAngle angViewPoint;
	Vector vecAimDirection;
	float flForwardMove;
	float flSideMove;
	float flUpMove;
	int iButtons;
	std::uint8_t uImpulse;
	int iWeaponSelect;
	int iWeaponSubType;
	int iRandomSeed;
	short sMouseDeltaX;
	short sMouseDeltaY;
	bool bHasBeenPredicted;
	Vector vecHeadAngles;
	Vector vecHeadOffset;

	[[nodiscard]] CRC32_t GetChecksum() const
	{
		CRC32_t uHashCRC = 0UL;

		CRC32::Init(&uHashCRC);
		CRC32::ProcessBuffer(&uHashCRC, &iCommandNumber, sizeof(iCommandNumber));
		CRC32::ProcessBuffer(&uHashCRC, &iTickCount, sizeof(iTickCount));
		CRC32::ProcessBuffer(&uHashCRC, &angViewPoint, sizeof(angViewPoint));
		CRC32::ProcessBuffer(&uHashCRC, &vecAimDirection, sizeof(vecAimDirection));
		CRC32::ProcessBuffer(&uHashCRC, &flForwardMove, sizeof(flForwardMove));
		CRC32::ProcessBuffer(&uHashCRC, &flSideMove, sizeof(flSideMove));
		CRC32::ProcessBuffer(&uHashCRC, &flUpMove, sizeof(flUpMove));
		CRC32::ProcessBuffer(&uHashCRC, &iButtons, sizeof(iButtons));
		CRC32::ProcessBuffer(&uHashCRC, &uImpulse, sizeof(uImpulse));
		CRC32::ProcessBuffer(&uHashCRC, &iWeaponSelect, sizeof(iWeaponSelect));
		CRC32::ProcessBuffer(&uHashCRC, &iWeaponSubType, sizeof(iWeaponSubType));
		CRC32::ProcessBuffer(&uHashCRC, &iRandomSeed, sizeof(iRandomSeed));
		CRC32::ProcessBuffer(&uHashCRC, &sMouseDeltaX, sizeof(sMouseDeltaX));
		CRC32::ProcessBuffer(&uHashCRC, &sMouseDeltaY, sizeof(sMouseDeltaY));
		CRC32::Final(&uHashCRC);

		return uHashCRC;
	}
};
static_assert(sizeof(CUserCmd) == 0x64);

class CVerifiedUserCmd
{
public:
	CUserCmd userCmd;
	CRC32_t uHashCRC;
};
static_assert(sizeof(CVerifiedUserCmd) == 0x68);
#pragma pack(pop)
