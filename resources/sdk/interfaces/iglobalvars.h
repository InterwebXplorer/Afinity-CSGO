#pragma once

class IGlobalVarsBase {
public:
	float flRealTime;
	int iFrameCount;
	float flAbsFrameTime;
	float flAbsFrameStartTime;
	float flCurrentTime;
	float flFrameTime;
	int nMaxClients;
	int iTickCount;
	float flIntervalPerTick;
	float flInterpolationAmount;
	int nFrameSimulationTicks;
	int iNetworkProtocol;
	void *pSaveData;
	bool bClient;
	bool bRemoteClient;
	int iTimestampNetworkingBase;
	int iTimestampRandomizeWindow;
};

class IGlobalVars : public IGlobalVarsBase {
public:
	string_t szMapName;
	string_t szMapGroupName;
	int iMapVersion;
	string_t szStartSpot;
	int nLoadType;
	bool bMapLoadFailed;
	bool bDeathmatch;
	bool bCooperative;
	bool bTeamplay;
	int nMaxEntities;
	int nServerCount;
	void *pEdicts;
};
