#pragma once
#include "../datatypes/matrix.h"
#include "../datatypes/qangle.h"

#pragma region engineclient_enumerations
enum EClientFrameStage : int {
	FRAME_UNDEFINED = -1,
	FRAME_START,

	FRAME_NET_UPDATE_START,

	FRAME_NET_UPDATE_POSTDATAUPDATE_START,

	FRAME_NET_UPDATE_POSTDATAUPDATE_END,

	FRAME_NET_UPDATE_END,

	FRAME_RENDER_START,

	FRAME_RENDER_END,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE
};

enum ERenderViewInfo : int {
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2)
};
#pragma endregion

struct PlayerInfo_t {
	std::uint64_t ullVersion = 0ULL;
	union {
		std::uint64_t ullXuid;
		struct {
			std::uint32_t nXuidLow;
			std::uint32_t nXuidHigh;
		};
	};

	char szName[128];
	int nUserID;
	char szSteamID[33];
	std::uint32_t nFriendsID;
	char szFriendsName[128];
	bool bFakePlayer;
	bool bIsHLTV;
	CRC32_t uCustomFiles[4];
	std::uint8_t dFilesDownloaded;
};

struct AudioState_t {
	Vector vecOrigin;
	QAngle angAngles;
	bool bIsUnderwater;
};

struct Model_t;
struct SteamAPIContext_t;
struct ClientTextMessage_t;
struct SurfInfo_t;
class CSentence;
class CAudioSource;
class CPhysCollide;
class CGamestatsData;
class ICollideable;
class ISpatialQuery;
class ISPSharedMemory;
class IAchievementMgr;
class IMaterial;
class IMaterialSystem;

class IEngineClient {
public:
	void GetScreenSize(int &iWidth, int &iHeight) {
		MEM::CallVFunc<void>(this, 5, std::ref(iWidth), std::ref(iHeight));
	}

	bool GetPlayerInfo(int nEntityIndex, PlayerInfo_t *pInfo) {
		return MEM::CallVFunc<bool>(this, 8, nEntityIndex, pInfo);
	}

	int GetPlayerForUserID(int nUserID) {
		return MEM::CallVFunc<int>(this, 9, nUserID);
	}

	bool IsConsoleVisible() {
		return MEM::CallVFunc<bool>(this, 11);
	}

	int GetLocalPlayer() {
		return MEM::CallVFunc<int>(this, 12);
	}

	float GetLastTimeStamp() {
		return MEM::CallVFunc<float>(this, 14);
	}

	void GetViewAngles(QAngle &angView) {
		MEM::CallVFunc<void>(this, 18, std::ref(angView));
	}

	void SetViewAngles(QAngle &angView) {
		MEM::CallVFunc<void>(this, 19, std::ref(angView));
	}

	int GetMaxClients() {
		return MEM::CallVFunc<int>(this, 20);
	}

	bool IsInGame() {
		return MEM::CallVFunc<bool>(this, 26);
	}

	bool IsConnected() {
		return MEM::CallVFunc<bool>(this, 27);
	}

	bool IsDrawingLoadingImage() {
		return MEM::CallVFunc<bool>(this, 28);
	}

	const ViewMatrix_t &WorldToScreenMatrix() {
		return MEM::CallVFunc<const ViewMatrix_t &>(this, 37);
	}

	void *GetBSPTreeQuery() {
		return MEM::CallVFunc<void *>(this, 43);
	}

	const char *GetLevelName() {
		return MEM::CallVFunc<const char *>(this, 52);
	}

	const char *GetLevelNameShort() {
		return MEM::CallVFunc<const char *>(this, 53);
	}

	INetChannelInfo *GetNetChannelInfo() {
		return MEM::CallVFunc<INetChannelInfo *>(this, 78);
	}

	bool IsPlayingDemo() {
		return MEM::CallVFunc<bool>(this, 82);
	}

	bool IsRecordingDemo() {
		return MEM::CallVFunc<bool>(this, 83);
	}

	bool IsPlayingTimeDemo() {
		return MEM::CallVFunc<bool>(this, 84);
	}

	bool IsTakingScreenshot() {
		return MEM::CallVFunc<bool>(this, 92);
	}

	bool IsHLTV() {
		return MEM::CallVFunc<bool>(this, 93);
	}

	unsigned int GetEngineBuildNumber() {
		return MEM::CallVFunc<unsigned int>(this, 104);
	}

	const char *GetProductVersionString() {
		return MEM::CallVFunc<const char *>(this, 105);
	}

	void ExecuteClientCmd(const char *szCmdString) {
		MEM::CallVFunc<void>(this, 108, szCmdString);
	}

	void ClientCmdUnrestricted(const char *szCmdString, bool bFromConsoleOrKeybind = false) {
		MEM::CallVFunc<void>(this, 114, szCmdString, bFromConsoleOrKeybind);
	}

	SteamAPIContext_t *GetSteamAPIContext() {
		return MEM::CallVFunc<SteamAPIContext_t *>(this, 185);
	}

	bool IsVoiceRecording() {
		return MEM::CallVFunc<bool>(this, 224);
	}
};
