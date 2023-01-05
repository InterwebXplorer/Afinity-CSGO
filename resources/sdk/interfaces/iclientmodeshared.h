#pragma once
#include "../datatypes/qangle.h"

#pragma region clientmode_definitions
#define SIGNONSTATE_NONE 0
#define SIGNONSTATE_CHALLENGE 1
#define SIGNONSTATE_CONNECTED 2
#define SIGNONSTATE_NEW 3
#define SIGNONSTATE_PRESPAWN 4
#define SIGNONSTATE_SPAWN 5
#define SIGNONSTATE_FULL 6
#define SIGNONSTATE_CHANGELEVEL 7
#pragma endregion

class CViewSetup {
public:
	int iX;
	int iUnscaledX;
	int iY;
	int iUnscaledY;
	int iWidth;
	int iUnscaledWidth;
	int iHeight;
	int iUnscaledHeight;
	bool bOrtho;
	float flOrthoLeft;
	float flOrthoTop;
	float flOrthoRight;
	float flOrthoBottom;
	std::byte pad0[0x7C];
	float flFOV;
	float flViewModelFOV;
	Vector vecOrigin;
	QAngle angView;
	float flNearZ;
	float flFarZ;
	float flNearViewmodelZ;
	float flFarViewmodelZ;
	float flAspectRatio;
	float flNearBlurDepth;
	float flNearFocusDepth;
	float flFarFocusDepth;
	float flFarBlurDepth;
	float flNearBlurRadius;
	float flFarBlurRadius;
	float flDoFQuality;
	int nMotionBlurMode;
	float flShutterTime;
	Vector vecShutterOpenPosition;
	QAngle vecShutterOpenAngles;
	Vector vecShutterClosePosition;
	QAngle vecShutterCloseAngles;
	float flOffCenterTop;
	float flOffCenterBottom;
	float flOffCenterLeft;
	float flOffCenterRight;
	bool bOffCenter : 1;
	bool bRenderToSubrectOfLargerScreen : 1;
	bool bDoBloomAndToneMapping : 1;
	bool bDoDepthOfField : 1;
	bool bHDRTarget : 1;
	bool bDrawWorldNormal : 1;
	bool bCullFontFaces : 1;
	bool bCacheFullSceneState : 1;
	bool bCSMView : 1;
};

class IHudChat;
class IClientModeShared {
public:
	std::byte pad0[0x1B];
	void *pViewport;
	IHudChat *pChatElement;
	HCursor hCursorNone;
	void *pWeaponSelection;
	int nRootSize[2];
};

class IAppSystem {
private:
	virtual void function0() = 0;
	virtual void function1() = 0;
	virtual void function2() = 0;
	virtual void function3() = 0;
	virtual void function4() = 0;
	virtual void function5() = 0;
	virtual void function6() = 0;
	virtual void function7() = 0;
	virtual void function8() = 0;
};

class CEventInfo {
public:
	short nClassID;
	float flFireDelay;
	const void *pSendTable;
	const CBaseClient *pClientClass;
	void *pData;
	std::intptr_t iPackedBits;
	int iFlags;
	std::byte pad0[0x16];
};

class INetChannel;
class IClientState {
public:
	std::byte pad0[0x9C];
	INetChannel *pNetChannel;
	int iChallengeNr;
	std::byte pad1[0x64];
	int iSignonState;
	std::byte pad2[0x8];
	float flNextCmdTime;
	int nServerCount;
	int iCurrentSequence;
	std::byte pad3[0x54];
	int iDeltaTick;
	bool bPaused;
	std::byte pad4[0x7];
	int iViewEntity;
	int iPlayerSlot;
	char szLevelName[MAX_PATH];
	char szLevelNameShort[80];
	char szMapGroupName[80];
	char szLastLevelNameShort[80];
	std::byte pad5[0xC];
	int nMaxClients;
	std::byte pad6[0x498C];
	float flLastServerTickTime;
	bool bInSimulation;
	std::byte pad7[0x3];
	int iOldTickcount;
	float flTickRemainder;
	float flFrameTime;
	int iLastOutgoingCommand;
	int nChokedCommands;
	int iLastCommandAck;
	int iCommandAck;
	int iSoundSequence;
	std::byte pad8[0x50];
	QAngle angViewPoint;
	std::byte pad9[0xD0];
	CEventInfo *pEvents;
};