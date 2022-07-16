#pragma once

class CBaseServer
{
public:
	char *szNetworkName;
	void *pTable;
	CBaseServer *pNext;
	int iClassID;
	int nInstanceBaselineIndex;
};

class CSaveRestoreData;
class IServerGameDLL
{
public:
	virtual bool DLLInit(CreateInterfaceFn fnEngineFactory, CreateInterfaceFn fnPhysicsFactory, CreateInterfaceFn fnFileSystemFactory, IGlobalVars *pGlobals) = 0;
	virtual void DLLShutdown() = 0;
	virtual bool ReplayInit(CreateInterfaceFn fnReplayFactory) = 0;
	virtual float GetTickInterval() const = 0;
	virtual bool GameInit() = 0;
	virtual void GameShutdown() = 0;
	virtual bool LevelInit(char const *szMapName, char const *szMapEntities, char const *szOldLevel, char const *szLandmarkName, bool bLoadGame, bool bBackground) = 0;
	virtual void ServerActivate(void *pEdictList, int nEdictCount, int nClientMax) = 0;
	virtual void LevelShutdown() = 0;
	virtual void GameFrame(bool bSimulating) = 0;
	virtual void PreClientUpdate(bool bSimulating) = 0;
	virtual CBaseServer *GetAllClasses() = 0;
	virtual const char *GetGameDescription() = 0;
	virtual void CreateNetworkStringTables() = 0;
	virtual CSaveRestoreData *SaveInit(int nSize) = 0;
	virtual void SaveWriteFields(CSaveRestoreData *, const char *, void *, DataMap_t *, TypeDescription_t *, int) = 0;
	virtual void SaveReadFields(CSaveRestoreData *, const char *, void *, DataMap_t *, TypeDescription_t *, int) = 0;
	virtual void SaveGlobalState(CSaveRestoreData *) = 0;
	virtual void RestoreGlobalState(CSaveRestoreData *) = 0;
	virtual void PreSave(CSaveRestoreData *) = 0;
	virtual void Save(CSaveRestoreData *) = 0;
	virtual void GetSaveComment(char *szComment, int nMaxLength, float flMinutes, float flSeconds, bool bNoTime = false) = 0;
	virtual void WriteSaveHeaders(CSaveRestoreData *) = 0;
	virtual void ReadRestoreHeaders(CSaveRestoreData *) = 0;
	virtual void Restore(CSaveRestoreData *, bool) = 0;
	virtual bool IsRestoring() = 0;
	virtual int CreateEntityTransitionList(CSaveRestoreData *, int) = 0;
	virtual void BuildAdjacentMapList() = 0;
	virtual bool GetUserMessageInfo(int iMsgType, char *szName, int nMaxNameLength, int &iSize) = 0;
	virtual void *GetStandardSendProxies() = 0;
	virtual void PostInit() = 0;
	virtual void Think(bool finalTick) = 0;
	virtual void PreSaveGameLoaded(char const *szSaveName, bool bCurrentlyInGame) = 0;
	virtual bool ShouldHideServer() = 0;
	virtual void InvalidateMdlCache() = 0;
	virtual void OnQueryCvarValueFinished(void *iCookie, void *pPlayerEntity, int eStatus, const char *pCvarName, const char *pCvarValue) = 0;
	virtual void GameServerSteamAPIActivated() = 0;
	virtual void GameServerSteamAPIShutdown() = 0;
	virtual void SetServerHibernation(bool bHibernating) = 0;
	virtual void *GetServerGCLobby() = 0;
	virtual const char *GetServerBrowserMapOverride() = 0;
	virtual const char *GetServerBrowserGameData() = 0;
};
