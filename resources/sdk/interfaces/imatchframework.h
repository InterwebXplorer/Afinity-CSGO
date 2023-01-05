#pragma once

class IPlayerLocal {
public:
	int GetXUIDLow() {
		return *reinterpret_cast<int *>(reinterpret_cast<std::uintptr_t>(this) + 0x8);
	}

	int GetXUIDHigh() {
		return *reinterpret_cast<int *>(reinterpret_cast<std::uintptr_t>(this) + 0xC);
	}

	const char *GetName() {
		return MEM::CallVFunc<const char *>(this, 2);
	}
};

class IPlayerManager {
public:
	IPlayerLocal *GetLocalPlayer(int nIndex) {
		return MEM::CallVFunc<IPlayerLocal *>(this, 1, nIndex);
	}
};

class IMatchExtensions;
class IMatchEventsSubscription;
class IMatchTitle;
class IMatchNetworkMsgController;

class IMatchSession {
public:
	virtual CKeyValues *GetSessionSystemData() = 0;
	virtual CKeyValues *GetSessionSettings() = 0;
	virtual void UpdateSessionSettings(CKeyValues *pSettings) = 0;
	virtual void Command(CKeyValues *pCommand) = 0;
};

class IMatchSystem {
public:
	virtual IPlayerManager *GetPlayerManager() = 0;
};

class IMatchFramework : public IAppSystem {
public:
	virtual void RunFrame() = 0;
	virtual IMatchExtensions *GetMatchExtensions() = 0;
	virtual IMatchEventsSubscription *GetEventsSubscription() = 0;
	virtual IMatchTitle *GetMatchTitle() = 0;
	virtual IMatchSession *GetMatchSession() = 0;
	virtual IMatchNetworkMsgController *GetMatchNetworkMsgController() = 0;
	virtual IMatchSystem *GetMatchSystem() = 0;
	virtual void CreateSession(CKeyValues *pSettings) = 0;
	virtual void MatchSession(CKeyValues *pSettings) = 0;
	virtual void AcceptInvite(int iController) = 0;
	virtual void CloseSession() = 0;
};