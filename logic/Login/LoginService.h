
#ifndef _LOGINSERVICE_H_
#define _LOGINSERVICE_H_

#include "Base.h"
#include "service/Invoker.h"
#include "service/Service.h"
#include "player/LoginPlayerManager.h"

class SavePlayerDataMsg;
class PlayerLeaveWorldMsg;

class LoginService :public Service
{
public:
	explicit LoginService(uint32 port);
	virtual ~LoginService(void);

public:
	friend class LoginPlayerManager;

public:
	virtual int GetServiceID(void){return ServiceID::LOGIN;}

public:
	virtual void Init(void);
	virtual void Tick(const TimeInfo &rTimeInfo);

private:
	void Tick_Transport(const TimeInfo &rTimeInfo);
	void TickShutDown(const TimeInfo &rTimeInfo);

private:
	int m_nShutDownTime;

public:
	void HandleMessage(const SavePlayerDataMsg &rMsg);
    void HandleMessage(const PlayerLeaveWorldMsg &rMsg);

private:
	// 检测用户是否排队，是否在在线列表中
	int  OLCheckPlayer(const ACCOUNTNAME & szAccount) const;
	bool OLIsHavePlayer(const ACCOUNTNAME & szAccount) const;
	// 将用户添加到队列中
	bool OLQueuePlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID,int nQueuingLevel);
	// 更新玩家的排队权重
	void OLQueuePlayerUpdateRechargeValue(const ACCOUNTNAME & szAccount,int64 nPlayerID,int nRechargeValue);
	// 将用户从排队列表转移到登录列表中
	void OLLoginPlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID);
	// 用户重新登录，从游戏列表转移到登录列表
	void OLReLoginPlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID);
	// 用户登录，从登录列表转移到游戏列表中
	void OLPlayPlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID);

	// 将账号踢下线
	void OLDelPlayer(const ACCOUNTNAME & szAccount);

private:

	void Tick_OLQueuing(const TimeInfo &rTimeInfo);

	void Tick_OLQueuingUpdateIndex(const TimeInfo &rTimeInfo);

	bool OlQueuFinishOne(void);

	// 根据账号将玩家踢下线
	void OLKickPlayerByAccount(const ACCOUNTNAME& szAccount,int nReason);

private:
	int  m_nOLQueuingUpdateIndexTime;

private:
	typedef std::list<PlayerQueuingData> OLLoginQueuingPlayerList;
	OLLoginQueuingPlayerList m_OlLoginQueuingPlayerList;

private:
	typedef std::map<ACCOUNTNAME, int64> OLLoginPlayingPlayerMap;
	OLLoginPlayingPlayerMap  m_OLLoginPlayingPlayerMap;

private:
	typedef std::map<ACCOUNTNAME ,int64> OLGamePlayingPlayerMap;
	OLGamePlayingPlayerMap  m_OLGamePlayingPlayerMap;

private:
	bool PCDIsHave(int64 guid) const;
	bool PCDLoad(int64 guid,DBFullUserData &rUserData) const;
	void PCDOnPlayerEnterWorld(Player &rPlayer);
	void PCDOnPlayerLeaveWorld(Player &rPlayer);
	void PCDOnPlayerDataUpdate(int64 guid,const DBFullUserData &rUserData,bool bImmediateSave);
	bool PDCOnPlayerDataSaveRet(int64 guid,int nResult, bool bFinalSave);
	void PCDRemove(time_t nAnsiTime,time_t nOverTime);
	void Tick_PCD(const TimeInfo &rTimeInfo);

private:
	struct PlayerCacheData 
	{
		bool           m_bOnline;
		bool           m_bFinalSaveProcess;
		bool           m_bFinalSaveOk;
		time_t         m_bFinalSaveTime;
		DBFullUserData m_DBFullUserData;
	};

	typedef std::map<int64,PlayerCacheData> PCDMap;
	PCDMap  m_PCDMap;

private:
	enum 
	{
		ACCEPT_TICK_MIN =8,
		ACCEPT_TICK_MAX = 80,
	};

private:
	void Tick_Accept(const TimeInfo &rTimeInfo);
	bool IsHaveNewPlayer(void);
	bool AcceptNewPlayer(void);

private:
	ServerSocket m_ServerSocket;

public:
	void  SetCurPlayerCount(int nCurPlayerCount){m_nCurPlayerCount=nCurPlayerCount;}
	int   GetCurPlayerCount(void) const {return m_nCurPlayerCount;}

private:
	int  m_nCurPlayerCount;

private:

	LoginPlayerManager m_PlayerManager;

	
};

typedef GeneralInvoker<LoginService,200,200> LoginInvoker;


#endif