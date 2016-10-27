#ifndef _SERVERPLAYER_H_
#define _SERVERPLAYER_H_

#include "Base.h"
#include "LibNetwork.h"
#include "ServerPlayerDefine.h"
#include "Service/TimeInfo.h"
#include "Packet/Packet/PBMessage.pb.h"

class ServerPlayer
{
public:
	ServerPlayer(void);
	~ServerPlayer(void);
private:
	ServerPlayer(const ServerPlayer &);
	ServerPlayer& operator=(const ServerPlayer &);

public:
	const ServerPlayerBaseInfo & GetBaseInfo(void) const {return m_BaseInfo;}
	void SetBaseInfo(const ServerPlayerBaseInfo &rInfo) {m_BaseInfo = rInfo;}
private:
	ServerPlayerBaseInfo m_BaseInfo;

public:
	bool ProcessInput(void);
	bool ProcessOutput(void);
	bool ProcessCommand(void);
	bool ProcessConnection(time_t nAnsiTime);
	void SendPacket(const Packet &rPacket);

private:
	tint32 m_nHealthLevel;

public:
	//////////////////////////////////////////////////////////////////////////
	//Login期间消息
	HANDLEPACKET_SERVERPLAYER_EMPTY(::CG_LOGIN)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_LOGIN_RET)
	

	//////////////////////////////////////////////////////////////////////////
	//Scene期间消息
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_NOTICE)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::CG_REQ_NEAR_LIST)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_NEAR_MARCHLIST)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::CG_CONNECTED_HEARTBEAT)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_CONNECTED_HEARTBEAT)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::CG_CHAT)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_CHAT)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_UPDATE_SCENE_INSTACTIVATION)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::CG_MOVE)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_MOVE)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_STOP)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_TELEMOVE)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_RET_USE_SKILL)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_UPDATE_ANIMATION_STATE)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_DELETE_OBJ)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_FORCE_SETPOS)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_ATTACKFLY)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_UPDATE_NEEDIMPACTINFO)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_PLAY_EFFECT)
	HANDLEPACKET_SERVERPLAYER_EMPTY(::GC_REMOVEEFFECT)

	//CG、GC消息包放到上面，GS、SG消息包放到下面
	tuint32 HandlePacket(::GS_CONNECTED_HEARTBEAT &rPacket);
	tuint32 HandlePacket(::SG_CONNECTED_HEARTBEAT &rPacket);


public:
	void Disconnect(void);
public:
	Socket& GetSocket(void) {return m_Socket;}
private:
	Socket m_Socket;
private:
	SocketInputStream	m_SocketInputStream;
	SocketOutputStream	m_SocketOutputStream;
};

POOLDEF_DECL(ServerPlayer);

typedef std::list<ServerPlayerPtr> ServerPlayerPtrList;

#endif
