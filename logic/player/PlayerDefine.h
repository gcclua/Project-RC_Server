#ifndef __PLAYERDEFINE_H__
#define __PLAYERDEFINE_H__

#include "Base.h"
#include "Scene/GameDefine_Scene.h"
class PlayerStatus
{
public:
	enum 
	{
		//初始值
		EMPTY = 0,
		
		//已成功建立连接
		//处于此状态时可接受玩家的登陆请求
		CONNECTED,

		// 准备进入游戏世界
		LOGIN_READYENTERWORLD,

		//
		GAME_ENTERINGWORLD,

		//已进入游戏
		GAME_PLAYERING,



	};
};

#define  HANDLEPACKET_EMPTY(PACKETCLASS) \
uint32 HandlePacket(PACKETCLASS &rPacket) \
{\
	return PACKET_EXE_CONTINUE; \
}

#define  HANDLEPACKET_LOGIN(PACKETCLASS,PLAYERSTATUS) \
uint32 HandlePacket(PACKETCLASS &rPacket) \
{\
	if (GetStatus() == PLAYERSTATUS) \
{\
	return m_LoginObj.HandlePacket(rPacket);\
}\
	else\
{\
	CACHE_LOG("waring","handle packet exception,handletype(login),playerstatus("<<GetStatus()<<"),packetclass("#PACKETCLASS",playerstatus"<<PLAYERSTATUS);\
	return PACKET_EXE_CONTINUE; \
}\
}

#define  HANDLEPACKET_USER(PACKETCLASS) \
	uint32 HandlePacket(PACKETCLASS &rPacket) \
{\
	if (GetStatus() == PlayerStatus::GAME_PLAYERING) \
{\
	return m_UserObj.HandlePacket(rPacket);\
}\
	else\
{\
	CACHE_LOG("waring","handle packet exception,handletype(login),playerstatus("<<GetStatus()<<"),packetclass("#PACKETCLASS",playerstatus"<<PlayerStatus::GAME_PLAYERING);\
	return PACKET_EXE_CONTINUE; \
}\
}

#define  MAX_LASTPACKETSIZE 3

class PacketStat
{
public:
	PacketStat()
	{
		m_nReceiveCount = 0;
		m_nReceiveSize  = 0;
		m_nSendCount    = 0;
		m_nSendSize     = 0;
	}

public:
	int64 m_nReceiveCount;
	int64 m_nReceiveSize;
	int64 m_nSendCount;
	int64 m_nSendSize;

};

class PlayerQueuingData
{
public:
	enum
	{
		QUEUINGLEVEL_GM = 0,
		QUEUINGLEVEL_RECONNECTION,
		QUEUINGLEVEL_NORMAL,
	};

public:
	ACCOUNTNAME m_szAccount;
	int64  m_nPlayerID;
	int    m_nQueuingLevel;
	int    m_nRechargeValue;

public:
	PlayerQueuingData(void)
	{
		m_szAccount      = "";
		m_nPlayerID      = INVALID_ID;
		m_nQueuingLevel  = QUEUINGLEVEL_NORMAL;
		m_nRechargeValue = 0;
	}

	PlayerQueuingData(const ACCOUNTNAME& szAccount,int64 nPlayerID,int nQueuingLevel,int nRechargeValue)
	{
		m_szAccount      = szAccount;
		m_nPlayerID      = nPlayerID;
		m_nQueuingLevel  = nQueuingLevel;
		m_nRechargeValue = nRechargeValue;
	}
	~PlayerQueuingData()
	{

	}
public:
	PlayerQueuingData(const PlayerQueuingData& rData)
	{
		m_szAccount      = rData.m_szAccount;
		m_nPlayerID      = rData.m_nPlayerID;
		m_nQueuingLevel  = rData.m_nQueuingLevel;
		m_nRechargeValue = rData.m_nRechargeValue;
	}

	PlayerQueuingData& operator = (const PlayerQueuingData& rData)
	{
		if (this != &rData)
		{
			m_szAccount      = rData.m_szAccount;
			m_nPlayerID      = rData.m_nPlayerID;
			m_nQueuingLevel  = rData.m_nQueuingLevel;
			m_nRechargeValue = rData.m_nRechargeValue;
		}
		return *this;
	}

public:
	bool operator < (const PlayerQueuingData& rData) const
	{
		switch (m_nQueuingLevel)
		{
		case QUEUINGLEVEL_GM:
			{
				if (rData.m_nQueuingLevel == QUEUINGLEVEL_GM)
				{
					return false;
				}
				else if (rData.m_nQueuingLevel == QUEUINGLEVEL_RECONNECTION)
				{
					return true;
				}
				return true;
			}
			break;
		case QUEUINGLEVEL_RECONNECTION:
			{
				if (rData.m_nQueuingLevel == QUEUINGLEVEL_GM)
				{
					return false;
				}
				else if (rData.m_nQueuingLevel == QUEUINGLEVEL_RECONNECTION)
				{
					return false;
				}
				return true;
			}
			break;
		default:
			{
				if (rData.m_nQueuingLevel == QUEUINGLEVEL_GM)
				{
					return false;
				}
				else if (rData.m_nQueuingLevel == QUEUINGLEVEL_RECONNECTION)
				{
					return false;
				}
				else
				{
					if (m_nRechargeValue <= rData.m_nRechargeValue)
					{
						return false;
					}
					else 
					{
						return true;
					}
				}
			}
			break;
		}
	}

};


#endif

