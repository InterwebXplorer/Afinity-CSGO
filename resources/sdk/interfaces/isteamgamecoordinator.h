#pragma once

enum EGCResults {
	EGCResultOK = 0,
	EGCResultNoMessage = 1,
	EGCResultBufferTooSmall = 2,
	EGCResultNotLoggedOn = 3,
	EGCResultInvalidMessage = 4,
};

class ISteamGameCoordinator {
public:
	virtual EGCResults SendMessageGC(std::uint32_t uMsgType, const void *pData, std::uint32_t uData) = 0;
	virtual bool IsMessageAvailable(std::uint32_t *puMsgSize) = 0;
	virtual EGCResults RetrieveMessageGC(std::uint32_t *puMsgType, void *pDest, std::uint32_t uDest, std::uint32_t *puMsgSize) = 0;
};
