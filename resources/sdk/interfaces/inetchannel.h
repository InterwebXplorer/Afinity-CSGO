#pragma once
#include "../bitbuf.h"

#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define MAX_FLOWS 2

class INetChannelInfo
{
public:
	enum
	{
		GENERIC = 0,
		LOCALPLAYER,
		OTHERPLAYERS,
		ENTITIES,
		SOUNDS,
		EVENTS,
		TEMPENTS,
		USERMESSAGES,
		ENTMESSAGES,
		VOICE,
		STRINGTABLE,
		MOVE,
		STRINGCMD,
		SIGNON,
		PAINTMAP,
		ENCRYPTED,
		TOTAL,
	};

	virtual const char *GetName() const = 0;
	virtual const char *GetAddress() const = 0;
	virtual float GetTime() const = 0;
	virtual float GetTimeConnected() const = 0;
	virtual int GetBufferSize() const = 0;
	virtual int GetDataRate() const = 0;

	virtual bool IsLoopback() const = 0;
	virtual bool IsTimingOut() const = 0;
	virtual bool IsPlayback() const = 0;
	virtual float GetLatency(int iFlow) const = 0;
	virtual float GetAvgLatency(int iFlow) const = 0;
	virtual float GetAvgLoss(int iFlow) const = 0;
	virtual float GetAvgChoke(int iFlow) const = 0;
	virtual float GetAvgData(int iFlow) const = 0;
	virtual float GetAvgPackets(int iFlow) const = 0;
	virtual int GetTotalData(int iFlow) const = 0;
	virtual int GetTotalPackets(int iFlow) const = 0;
	virtual int GetSequenceNr(int iFlow) const = 0;
	virtual bool IsValidPacket(int iFlow, int nFrame) const = 0;
	virtual float GetPacketTime(int iFlow, int nFrame) const = 0;
	virtual int GetPacketBytes(int iFlow, int nFrame, int group) const = 0;
	virtual bool GetStreamProgress(int iFlow, int *piReceived, int *piTotal) const = 0;
	virtual float GetTimeSinceLastReceived() const = 0;
	virtual float GetCommandInterpolationAmount(int iFlow, int nFrame) const = 0;
	virtual void GetPacketResponseLatency(int iFlow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation, float *pflFrameStartTimeStdDeviation) const = 0;
	virtual float GetTimeoutSeconds() const = 0;
};

class INetChannel
{
public:
	std::byte pad0[0x14];
	bool bProcessingMessages;
	bool bShouldDelete;
	bool bStopProcessing;
	std::byte pad1[0x1];
	int iOutSequenceNr;
	int iInSequenceNr;
	int iOutSequenceNrAck;
	int iOutReliableState;
	int iInReliableState;
	int iChokedPackets;
	std::byte pad2[0x414];

	int SendDatagram(bf_write *pDatagram)
	{
		return MEM::CallVFunc<int>(this, 46, pDatagram);
	}

	bool Transmit(bool bOnlyReliable = false)
	{
		return MEM::CallVFunc<bool>(this, 49, bOnlyReliable);
	}
};

class INetMessage
{
public:
	virtual ~INetMessage() {}
	virtual void SetNetChannel(void *pNetChannel) = 0;
	virtual void SetReliable(bool bState) = 0;
	virtual bool Process() = 0;
	virtual bool ReadFromBuffer(bf_read &buffer) = 0;
	virtual bool WriteToBuffer(bf_write &buffer) = 0;
	virtual bool IsReliable() const = 0;
	virtual int GetType() const = 0;
	virtual int GetGroup() const = 0;
	virtual const char *GetName() const = 0;
	virtual INetChannel *GetNetChannel() const = 0;
	virtual const char *ToString() const = 0;
	virtual std::size_t GetSize() const = 0;
};

class CCLCMsg_Move
{
private:
	std::byte pad0[0x8];

public:
	int nBackupCommands;
	int nNewCommands;
};

template <typename T>
class CNetMessagePB : public INetMessage, public T
{
};
using CCLCMsg_Move_t = CNetMessagePB<CCLCMsg_Move>;

class INetChannelHandler
{
public:
	virtual ~INetChannelHandler() {}
	virtual void ConnectionStart(INetChannel *pChannel) = 0;
	virtual void ConnectionStop() = 0;
	virtual void ConnectionClosing(const char *szReason) = 0;
	virtual void ConnectionCrashed(const char *szReason) = 0;
	virtual void PacketStart(int iIncomingSequence, int iOutgoingAcknowledged) = 0;
	virtual void PacketEnd() = 0;
	virtual void FileRequested(const char *szFileName, unsigned int uTransferID, bool bReplayDemoFile) = 0;
	virtual void FileReceived(const char *szFileName, unsigned int uTransferID, bool bReplayDemoFile) = 0;
	virtual void FileDenied(const char *szFileName, unsigned int uTransferID, bool bReplayDemoFile) = 0;
	virtual void FileSent(const char *szFileName, unsigned int uTransferID, bool bReplayDemoFile) = 0;
	virtual bool ChangeSplitscreenUser(int nSplitScreenUserSlot) = 0;
};
