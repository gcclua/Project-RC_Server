#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Base.h"
#include "LibNeTwork.h"
#include "PlayerDefine.h"
#include "Login/Obj_Login.h"
#include "../user/User.h"
#include "packet/Packet/PacketDefine.h"

//Login期间消息
class CG_LOGIN;
class GC_LOGIN_RET;

//world期间消息
class CG_CONNECTED_HEARTBEAT;
class  GC_CONNECTED_HEARTBEAT;
class CG_REQ_NEAR_LIST;
class GC_NEAR_MARCHLIST;
class CG_CHAT;
class GC_CHAT;
class GC_NOTICE;
class GC_UPDATE_SCENE_INSTACTIVATION;
class CG_MOVE;
class GC_MOVE;
class GC_STOP;
class GC_TELEMOVE;
class GC_RET_USE_SKILL;
class GC_UPDATE_ANIMATION_STATE;
class GC_ATTACKFLY;
class GC_DELETE_OBJ;
class GC_FORCE_SETPOS;
class GC_UPDATE_NEEDIMPACTINFO;
class GC_PLAY_EFFECT;
class GC_REMOVEEFFECT;

class GS_CONNECTED_HEARTBEAT;
class SG_CONNECTED_HEARTBEAT;

class Player
{
public:

    Player();
    ~Player();

public:
	int64 GetID(void) const {return m_UserObj.GetGuid();}

public:

	bool	ProcessInput(void ) ;
	bool	ProcessOutput( void) ;
	bool	ProcessCommand(void ) ;
	bool    ProcessConnection(time_t nAnsiTime);
	bool    Tick_InLogin(const TimeInfo& rTimeInfo);
	void    SendPacket(const Packet &rPacket);
	
private:
	
	// 网络连接句柄
	Socket      m_Socket;

	// 输入输出数据缓冲
	SocketInputStream  m_SocketInputStream;
	SocketOutputStream m_SocketOutputStream;

public:
	void KickMe(int nReason);
private:

	bool       m_bKickMe;

public:
	Socket& GetSocket(void) {return m_Socket;}
	bool    IsValid(void) const {return m_Socket.isValid();}
	void    Disconnect(void);

public:
	void    SetStatus(int nStatus){m_nStatus=nStatus;}
	int     GetStatus(void) const {return m_nStatus;}

private:
	int m_nStatus;

protected:
	void OnReceivePacket(int nPacketId,int64 nPacketSize);
	void OnSendPacket(int nPacketId,int64 nPacketSize);

public:
	//Login期间消息
	HANDLEPACKET_LOGIN(::CG_LOGIN, PlayerStatus::CONNECTED)
	HANDLEPACKET_EMPTY(::GC_LOGIN_RET)

	// World期间消息
	tuint32 HandlePacket(::CG_CONNECTED_HEARTBEAT &rPacket);
	HANDLEPACKET_EMPTY(::GC_CONNECTED_HEARTBEAT)
	HANDLEPACKET_USER(::CG_REQ_NEAR_LIST)
	HANDLEPACKET_EMPTY(::GC_NEAR_MARCHLIST)
	HANDLEPACKET_USER(::CG_CHAT)
	HANDLEPACKET_EMPTY(::GC_CHAT)
	HANDLEPACKET_EMPTY(::GC_NOTICE)
	HANDLEPACKET_EMPTY(::GC_UPDATE_SCENE_INSTACTIVATION)
	HANDLEPACKET_USER(::CG_MOVE)
	HANDLEPACKET_EMPTY(::GC_MOVE)
	HANDLEPACKET_EMPTY(::GC_STOP)
	HANDLEPACKET_EMPTY(::GC_TELEMOVE)
	HANDLEPACKET_EMPTY(::GC_RET_USE_SKILL)
	HANDLEPACKET_EMPTY(::GC_UPDATE_ANIMATION_STATE)
	HANDLEPACKET_EMPTY(::GC_DELETE_OBJ)
	HANDLEPACKET_EMPTY(::GC_FORCE_SETPOS)
	HANDLEPACKET_EMPTY(::GC_ATTACKFLY)
	HANDLEPACKET_EMPTY(::GC_UPDATE_NEEDIMPACTINFO)
	HANDLEPACKET_EMPTY(::GC_PLAY_EFFECT)
	HANDLEPACKET_EMPTY(::GC_REMOVEEFFECT)

	//CG、GC消息包放到上面，GS、SG消息包放到下面
	HANDLEPACKET_EMPTY(::GS_CONNECTED_HEARTBEAT);
	HANDLEPACKET_EMPTY(::SG_CONNECTED_HEARTBEAT);

private:
	bsarray<PacketStat,Packets::PACKET_MAX> m_PacketStat;

public:
	void PushRecPacketId(int nPacketId);
	void PushSendPacketId(int nPacketId);

private:

	bsarray<int,MAX_LASTPACKETSIZE> m_lastRecPacketId;
	bsarray<int,MAX_LASTPACKETSIZE> m_lastSendPacketId;

public:
	static bool isCryptoPacket(PacketID_t nPacketID);

public:
	Obj_Login& GetObjLogin(void){return m_LoginObj;}
	User&  GetObjUser(void){return m_UserObj;}

private:
	Obj_Login m_LoginObj;
	User  m_UserObj;
private:
	tint32 m_nHealthLevel;

};

POOLDEF_DECL(Player);
typedef std::list<PlayerPtr> PlayerPtrList;


#endif

