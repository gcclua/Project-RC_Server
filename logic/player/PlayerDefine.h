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

		//正在进行登陆验证
		LOGIN_VALIDATING,
		//登陆验证成功
		//验证账户状态
		LOGIN_VALIDATE_OK,
		//登陆验证失败
		//重置为CONNECTED状态
		LOGIN_VALIDATE_FAILED,

		//正在验证账户状态
		LOGIN_ACCOUNTSTATECHECKING,
		//账户状态验证成功
		//查询角色列表
		LOGIN_ACCOUNTSTATECHECK_OK,
		//账户状态验证失败
		//重置为CONNECTED状态
		LOGIN_ACCOUNTSTATECHECK_FAILED,

		//正在排队
		LOGIN_QUEUING,
		//排队完成
		LOGIN_QUEUE_FINISH,

		//正在查询角色列表
		LOGIN_QUERYING_CHARLIST,
		//查询角色列表成功
		//等待玩家选择或创建角色
		LOGIN_QUERY_CHARLIST_OK,
		//查询角色列表失败
		//重置为CONNECTED状态
		LOGIN_QUERY_CHARLIST_FAILED,


		//正在创建角色
		LOGIN_CREATING_CHAR,
		//创建角色成功
		//准备进入场景
		LOGIN_CREATE_CHAR_OK,
		//创建角色失败
		//重置为CONNECTED状态
		LOGIN_CREATE_CHAR_FAILED,

		//等待玩家创建角色或是选择角色的命令
		LOGIN_READYTONEXT,

		//正在加载角色
		LOGIN_LOADING_CHAR,
		//加载角色成功
		//准备进入场景
		LOGIN_LOAD_CHAR_OK,
		//加载角色失败
		//重置为CONNECTED状态
		LOGIN_LOAD_CHAR_FAILED,

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

#define HANDLEPACKET_LOGIN(PACKETCLASS, PLAYERSTATUS) \
	tuint32 HandlePacket(PACKETCLASS &rPacket) \
{ \
	if (GetStatus() == PLAYERSTATUS) \
{ \
	return m_LoginObj.HandlePacket(rPacket); \
} \
	else \
{ \
	CacheLog(LOGDEF_INST(Warning), "handle packet exception, handletype(%s), playerstatus(%d), packetclass(%s), packetexpectplayerstatus(%d)", "login", GetStatus(), #PACKETCLASS, (tint32)PLAYERSTATUS); \
	return PACKET_EXE_CONTINUE; \
} \
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
	CacheLog(LOGDEF_INST(Warning), "handle packet exception, handletype(%s), playerstatus(%d), packetclass(%s), packetexpectplayerstatus(%d)", "user", GetStatus(), #PACKETCLASS, (tint32)PlayerStatus::GAME_PLAYERING); \
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

class PlayerKickReason
{
public:
	enum
	{
		GMTOOLS = 0,	//GM工具踢人
		PAYTEST,		//充值功能测试踢人
		BLOCKROLE,		//封角色踢人
		REPEATLOGINREPLACE,	//重复登录时踢人
		MODIFYVIPCOST,		//修改Vip等级时踢人
		CHANGEWORLD,	//切世界踢人
	};
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
	int    m_nPlayerID;
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

	PlayerQueuingData(const ACCOUNTNAME& szAccount,int nPlayerID,int nQueuingLevel,int nRechargeValue)
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

