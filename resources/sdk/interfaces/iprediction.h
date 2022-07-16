#pragma once
#include "../datatypes/vector.h"
#include "../datatypes/qangle.h"
#include "../datatypes/usercmd.h"
#include "icliententitylist.h"

class CMoveData
{
public:
	bool bFirstRunOfFunctions : 1;
	bool bGameCodeMovedPlayer : 1;
	bool bNoAirControl : 1;
	std::uintptr_t hPlayerHandle;
	int nImpulseCommand;
	QAngle angViewAngles;
	QAngle angAbsViewAngles;
	int nButtons;
	int nOldButtons;
	float flForwardMove;
	float flSideMove;
	float flUpMove;
	float flMaxSpeed;
	float flClientMaxSpeed;
	Vector vecVelocity;
	Vector vecTrailingVelocity;
	float flTrailingVelocityTime;
	Vector vecAngles;
	Vector vecOldAngles;
	float flOutStepHeight;
	Vector vecOutWishVel;
	Vector vecOutJumpVel;
	Vector vecConstraintCenter;
	float flConstraintRadius;
	float flConstraintWidth;
	float flConstraintSpeedFactor;
	bool bConstraintPastRadius;
	Vector vecAbsOrigin;
};

class CBaseEntity;
class IPhysicsSurfaceProps;
class CGameTrace;
enum ESoundLevel;
class IMoveHelper
{
public:
	virtual const char *GetName(void *hEntity) const = 0;
	virtual void SetHost(CBaseEntity *pHost) = 0;
	virtual void ResetTouchList() = 0;
	virtual bool AddToTouched(const CGameTrace &trace, const Vector &vecImpactVelocity) = 0;
	virtual void ProcessImpacts() = 0;
	virtual void Con_NPrintf(int nIndex, char const *fmt, ...) = 0;
	virtual void StartSound(const Vector &vecOrigin, int iChannel, char const *szSample, float flVolume, ESoundLevel soundlevel, int fFlags, int iPitch) = 0;
	virtual void StartSound(const Vector &vecOrigin, const char *soundname) = 0;
	virtual void PlaybackEventFull(int fFlags, int nClientIndex, unsigned short uEventIndex, float flDelay, Vector &vecOrigin, Vector &vecAngles, float flParam1, float flParam2, int iParam1, int iParam2, int bParam1, int bParam2) = 0;
	virtual bool PlayerFallingDamage() = 0;
	virtual void PlayerSetAnimation(int playerAnimation) = 0;
	virtual IPhysicsSurfaceProps *GetSurfaceProps() = 0;
	virtual bool IsWorldEntity(const unsigned long &hEntity) = 0;
};

class IGameMovement
{
public:
	virtual ~IGameMovement() {}
	virtual void ProcessMovement(CBaseEntity *pEntity, CMoveData *pMove) = 0;
	virtual void Reset() = 0;
	virtual void StartTrackPredictionErrors(CBaseEntity *pEntity) = 0;
	virtual void FinishTrackPredictionErrors(CBaseEntity *pEntity) = 0;
	virtual void DiffPrint(char const *fmt, ...) = 0;
	virtual Vector const &GetPlayerMins(bool bDucked) const = 0;
	virtual Vector const &GetPlayerMaxs(bool bDucked) const = 0;
	virtual Vector const &GetPlayerViewOffset(bool bDucked) const = 0;
	virtual bool IsMovingPlayerStuck() const = 0;
	virtual CBaseEntity *GetMovingPlayer() const = 0;
	virtual void UnblockPusher(CBaseEntity *pEntity, CBaseEntity *pPusher) = 0;
	virtual void SetupMovementBounds(CMoveData *pMove) = 0;
};

class IPrediction
{
public:
	std::byte pad0[0x4];
	std::uintptr_t hLastGround;
	bool bInPrediction;
	bool bIsFirstTimePredicted;
	bool bEnginePaused;
	bool bOldCLPredictValue;
	int iPreviousStartFrame;
	int nIncomingPacketNumber;
	float flLastServerWorldTimeStamp;

	struct Split_t
	{
		bool bIsFirstTimePredicted;
		std::byte pad0[0x3];
		int nCommandsPredicted;
		int nServerCommandsAcknowledged;
		int iPreviousAckHadErrors;
		float flIdealPitch;
		int iLastCommandAcknowledged;
		bool bPreviousAckErrorTriggersFullLatchReset;
		CUtlVector<CBaseHandle> vecEntitiesWithPredictionErrorsInLastAck;
		bool bPerformedTickShift;
	};

	Split_t Split[1];

public:
	void Update(int iStartFrame, bool bValidFrame, int nIncomingAcknowledged, int nOutgoingCommand)
	{
		MEM::CallVFunc<void>(this, 3, iStartFrame, bValidFrame, nIncomingAcknowledged, nOutgoingCommand);
	}

	void GetLocalViewAngles(QAngle &angView)
	{
		MEM::CallVFunc<void>(this, 12, std::ref(angView));
	}

	void SetLocalViewAngles(QAngle &angView)
	{
		MEM::CallVFunc<void>(this, 13, std::ref(angView));
	}

	void CheckMovingGround(CBaseEntity *pEntity, double dbFrametime)
	{
		MEM::CallVFunc<void>(this, 18, pEntity, dbFrametime);
	}

	void SetupMove(CBaseEntity *pEntity, CUserCmd *pCmd, IMoveHelper *pHelper, CMoveData *pMoveData)
	{
		MEM::CallVFunc<void>(this, 20, pEntity, pCmd, pHelper, pMoveData);
	}

	void FinishMove(CBaseEntity *pEntity, CUserCmd *pCmd, CMoveData *pMoveData)
	{
		MEM::CallVFunc<void>(this, 21, pEntity, pCmd, pMoveData);
	}
};
