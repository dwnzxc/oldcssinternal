//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#if !defined( INETCHANNELINFO_H )
#define INETCHANNELINFO_H
#ifdef _WIN32
#pragma once
#endif


#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out

class INetChannelInfo
{
public:

	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};
	
	virtual const char  *GetName( void ) const = 0;	// get channel name
	virtual const char  *GetAddress( void ) const = 0; // get channel IP address as string
	virtual float		GetTime( void ) const = 0;	// current net time
	virtual float		GetTimeConnected( void ) const = 0;	// get connection time in seconds
	virtual int			GetBufferSize( void ) const = 0;	// netchannel packet history size
	virtual int			GetDataRate( void ) const = 0; // send data rate in byte/sec
	
	virtual bool		IsLoopback( void ) const = 0;	// true if loopback channel
	virtual bool		IsTimingOut( void ) const = 0;	// true if timing out
	virtual bool		IsPlayback( void ) const = 0;	// true if demo playback

	virtual float		GetLatency( int flow ) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency( int flow ) const = 0; // average packet latency in seconds
	virtual float		GetAvgLoss( int flow ) const = 0;	 // avg packet loss[0..1]
	virtual float		GetAvgChoke( int flow ) const = 0;	 // avg packet choke[0..1]
	virtual float		GetAvgData( int flow ) const = 0;	 // data flow in bytes/sec
	virtual float		GetAvgPackets( int flow ) const = 0; // avg packets/sec
	virtual int			GetTotalData( int flow ) const = 0;	 // total flow in/out in bytes
	virtual int			GetSequenceNr( int flow ) const = 0;	// last send seq number
	virtual bool		IsValidPacket( int flow, int frame_number ) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		GetPacketTime( int flow, int frame_number ) const = 0; // time when packet was send
	virtual int			GetPacketBytes( int flow, int frame_number, int group ) const = 0; // group size of this packet
	virtual bool		GetStreamProgress( int flow, int *received, int *total ) const = 0;  // TCP progress if transmitting
};

class INetChannelInfoo
{
public:

	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char  *GetName(void) const = 0;	// get channel name
	virtual const char  *GetAddress(void) const = 0; // get channel IP address as string
	virtual float		GetTime(void) const = 0;	// current net time
	virtual float		GetTimeConnected(void) const = 0;	// get connection time in seconds
	virtual int			GetBufferSize(void) const = 0;	// netchannel packet history size
	virtual int			GetDataRate(void) const = 0; // send data rate in byte/sec

	virtual bool		IsLoopback(void) const = 0;	// true if loopback channel
	virtual bool		IsTimingOut(void) const = 0;	// true if timing out
	virtual bool		IsPlayback(void) const = 0;	// true if demo playback

	virtual float		GetLatency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float		GetAvgLoss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		GetAvgChoke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		GetAvgData(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int			GetTotalData(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			GetSequenceNr(int flow) const = 0;	// last send seq number
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		GetStreamProgress(int flow, int *received, int *total) const = 0;  // TCP progress if transmitting
	virtual float		GetTimeSinceLastReceived(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};

class INetChannell : public INetChannelInfoo
{
public:
	virtual	~INetChannell(void) {};

	virtual void	SetDataRate(float rate) = 0;
	virtual bool	RegisterMessage(void *msg) = 0;
	virtual bool	StartStreaming(unsigned int challengeNr) = 0;
	virtual void	ResetStreaming(void) = 0;
	virtual void	SetTimeout(float seconds) = 0;
	virtual void	SetDemoRecorder(void *recorder) = 0;
	virtual void	SetChallengeNr(unsigned int chnr) = 0;

	virtual void	Reset(void) = 0;
	virtual void	Clear(void) = 0;
	virtual void	Shutdown(const char *reason) = 0;

	virtual void	ProcessPlayback(void) = 0;
	virtual bool	ProcessStream(void) = 0;
	virtual void	ProcessPacket(struct netpacket_s* packet, bool bHasHeader) = 0;

	virtual bool	SendNetMsg(void* &msg, bool bForceReliable = false, bool bVoice = false) = 0;
#ifdef _LINUX
	FORCEINLINE bool SendNetMsg(INetMessage const &msg, bool bForceReliable = false, bool bVoice = false) { SendNetMsg(*((INetMessage *)&msg), bForceReliable, bVoice); }
#endif
	virtual bool	SendData(void* &msg, bool bReliable = true) = 0;
	virtual bool	SendFile(const char *filename, unsigned int transferID) = 0;
	virtual void	DenyFile(const char *filename, unsigned int transferID) = 0;
	virtual void	RequestFile_OLD(const char *filename, unsigned int transferID) = 0;	// get rid of this function when we version the 
	virtual void	SetChoked(void) = 0;
	virtual int		SendDatagram(void *data) = 0;
	virtual bool	Transmit(bool onlyReliable = false) = 0;

	virtual const void*	&GetRemoteAddress(void) const = 0;
	virtual void *GetMsgHandler(void) const = 0;
	virtual int				GetDropNumber(void) const = 0;
	virtual int				GetSocket(void) const = 0;
	virtual unsigned int	GetChallengeNr(void) const = 0;
	virtual void			GetSequenceData(int &nOutSequenceNr, int &nInSequenceNr, int &nOutSequenceNrAck) = 0;
	virtual void			SetSequenceData(int nOutSequenceNr, int nInSequenceNr, int nOutSequenceNrAck) = 0;

	virtual void	UpdateMessageStats(int msggroup, int bits) = 0;
	virtual bool	CanPacket(void) const = 0;
	virtual bool	IsOverflowed(void) const = 0;
	virtual bool	IsTimedOut(void) const = 0;
	virtual bool	HasPendingReliableData(void) = 0;

	virtual void	SetFileTransmissionMode(bool bBackgroundMode) = 0;
	virtual void	SetCompressionMode(bool bUseCompression) = 0;
	virtual unsigned int RequestFile(const char *filename) = 0;
	virtual float	GetTimeSinceLastReceived(void) const = 0;	// get time since last received packet in seconds

	virtual void	SetMaxBufferSize(bool bReliable, int nBytes, bool bVoice = false) = 0;

	virtual bool	IsNull() const = 0;
	virtual int		GetNumBitsWritten(bool bReliable) = 0;
	virtual void	SetInterpolationAmount(float flInterpolationAmount) = 0;
	virtual void	SetRemoteFramerate(float flFrameTime, float flFrameTimeStdDeviation) = 0;

	// Max # of payload bytes before we must split/fragment the packet
	virtual void	SetMaxRoutablePayloadSize(int nSplitSize) = 0;
	virtual int		GetMaxRoutablePayloadSize() = 0;
};

class CNetChannel : public INetChannell
{
public:
	explicit CNetChannel();
	~CNetChannel();

	// Methods of INetChannel
	virtual void GetConnectionState();
	virtual  void* GetRemoteAddress(void);

	void		Setup(bool serverSide, const void *remote_address, void *sendSocket, char const *name, void *handler);
	void		Reset();
	void		Clear();
	void		Shutdown(const char *reason);

	void *GetSocket();

	void		SetDataRate(float rate);
	void		SetTimeout(float seconds);

	bool		StartProcessingPacket(void *packet);
	bool		ProcessPacket(void *packet);
	void		EndProcessingPacket(void *packet);

	bool		CanSendPacket(void) const;
	void		SetChoked(void); // choke a packet
	bool		HasPendingReliableData(void);

	// Queues data for sending:

	// send a net message
	bool		AddNetMsg(void *msg, bool bForceReliable = false);

	// send a chunk of data
	bool		AddData(void *&msg, bool bReliable = true);

	// Puts data onto the wire:

	int			SendDatagram(void *data); // Adds data to unreliable payload and then calls transmits the data
	bool		Transmit(bool onlyReliable = false); // send data from buffers (calls SendDataGram( NULL ) )

	bool		IsOverflowed(void) const;
	bool		IsTimedOut(void) const;
	bool		IsTimingOut() const;

	// Info:

	const char  *GetName(void) const;
	const char  *GetAddress(void) const;
	float		GetTimeConnected(void) const;
	float		GetTimeSinceLastReceived(void) const;
	int			GetDataRate(void) const;

	float		GetLatency(int flow) const;
	float		GetAvgLatency(int flow) const;
	float		GetAvgLoss(int flow) const;
	float		GetAvgData(int flow) const;
	float		GetAvgChoke(int flow) const;
	float		GetAvgPackets(int flow) const;
	int			GetTotalData(int flow) const;

	void SetConnectionState(void* state);

public:
	int			ProcessPacketHeader(void* &buf);
	bool		ProcessControlMessage(int cmd, void* &buf);
	bool		ProcessMessages(void* &buf);

	void* m_ConnectionState;

	//unsigned char __padd[0x10];
	// last send outgoing sequence number
	int			m_nOutSequenceNr;
};

#endif // INETCHANNELINFO_H