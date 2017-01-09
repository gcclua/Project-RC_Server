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
class CG_CREATEROLE;
class GC_CREATEROLE_RET;
class GC_LOGIN_QUEUE_STATUS;
class GC_SELECTROLE_RET;


//world期间消息
class CG_CONNECTED_HEARTBEAT;

class CG_REQ_NEAR_LIST;
class CG_MOVE;
class CG_ROBOT_OPEN;
class CG_ASSIGN_HERO;
class GC_NEAR_MARCHLIST;
class CG_CHAT;
class GC_CHAT;
class GC_NOTICE;
class GC_UPDATE_SCENE_INSTACTIVATION;
class CG_FIGHT;
class CG_LEAVE_COPYSCENE;
class CG_ASSIGN_HERO;
class CG_SEND_MARCH;
class CG_SKILL_USE;
class CG_BATTLEINFOR;
class GC_BATTLEINFOR;
class GC_OBJINFOR;
class CG_OBJPOSLIST;
class GC_OBJPOSLIST;
class GC_OBJCOMMANDPURSUE;
class GC_OBJPREPAREFORATTACK;
class GC_OBJGETHURT;

class GC_MOVE;
class GC_CONNECTED_HEARTBEAT;
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
class GC_ROBOT_OPEN;
class GC_ASSIGN_HERO;
class GC_SEND_MARCH;
class GC_FIGHT;



class GS_CONNECTED_HEARTBEAT;
class SG_CONNECTED_HEARTBEAT;

class Player
{
public:

    Player();
    ~Player();

public:
	tint32 GetID(void) const {return m_nID;}

	int64  GetUserId() const {return m_UserObj.GetGuid();}

private:
	tint32 m_nID;

private:
	static tint32 m_nIDGenerator;

public:

	bool	ProcessInput(void ) ;
	bool	ProcessOutput( void) ;
	bool	ProcessCommand(void ) ;
	bool    ProcessConnection(time_t nAnsiTime);
	bool    Tick_InLogin(const TimeInfo& rTimeInfo);
	bool    Tick_InGame(const TimeInfo &rTimeInfo);
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
	HANDLEPACKET_EMPTY(::GC_LOGIN_QUEUE_STATUS)
	HANDLEPACKET_LOGIN(::CG_CREATEROLE, PlayerStatus::LOGIN_READYTONEXT)

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
	HANDLEPACKET_USER(::CG_FIGHT)
	HANDLEPACKET_USER(::CG_LEAVE_COPYSCENE)
	HANDLEPACKET_USER(::CG_ROBOT_OPEN)
	HANDLEPACKET_USER(::CG_ASSIGN_HERO)
	HANDLEPACKET_USER(::CG_SEND_MARCH)
	HANDLEPACKET_USER(::CG_SKILL_USE)
	HANDLEPACKET_USER(::CG_BATTLEINFOR)
	HANDLEPACKET_USER(::CG_OBJPOSLIST);
	

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
	HANDLEPACKET_EMPTY(::GC_ROBOT_OPEN)
	HANDLEPACKET_EMPTY(::GC_ASSIGN_HERO)
	HANDLEPACKET_EMPTY(::GC_SEND_MARCH)
	HANDLEPACKET_EMPTY(::GC_CREATEROLE_RET)
	HANDLEPACKET_EMPTY(::GC_SELECTROLE_RET)
	HANDLEPACKET_EMPTY(::GC_BATTLEINFOR)
	HANDLEPACKET_EMPTY(::GC_OBJINFOR)
	HANDLEPACKET_EMPTY(::GC_OBJPOSLIST)
	HANDLEPACKET_EMPTY(::GC_OBJCOMMANDPURSUE)
	HANDLEPACKET_EMPTY(::GC_OBJPREPAREFORATTACK)
	HANDLEPACKET_EMPTY(::GC_OBJGETHURT)
	HANDLEPACKET_EMPTY(::GC_FIGHT)


	//CG、GC消息包放到上面，GS、SG消息包放到下面
	HANDLEPACKET_EMPTY(::GS_CONNECTED_HEARTBEAT);
	HANDLEPACKET_EMPTY(::SG_CONNECTED_HEARTBEAT);

private:
	bsarray<PacketStat,Packets::PACKET_MAX> m_PacketStat;

public:
	void PushRecPacketId(int nPacketId);
	void PushSendPacketId(int nPacketId);
	void PrintLastPacketLog(const tchar* szPrintType);

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

