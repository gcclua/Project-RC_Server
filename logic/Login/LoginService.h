
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

protected:
	virtual void Openup(void);
	virtual void Shutdown(void);

private:
	void Tick_Transport(const TimeInfo &rTimeInfo);
	void TickShutDown(const TimeInfo &rTimeInfo);
private:
	tint32 m_nShutdownTime;

private:
	void KickAllUser(void);

public:
	virtual void HandleMessage(const SavePlayerDataMsg &rMsg);
    virtual void HandleMessage(const PlayerQuitGameMsg &rMsg);
	virtual void HandleMessage(const KickPlayerByAccountMsg &rMsg);
	virtual void HandleMessage(const AccountStateCheckMsg &rMsg);
	virtual void HandleMessage(const AccountOfflineMsg &rMsg);
	virtual void HandleMessage(const DBRetLoadUserMsg &rMsg);
	virtual void HandleMessage(const DBLoadUserMsg &rMsg);
	virtual void HandleMessage(const DBRetCreateCharMsg &rMsg);
	virtual void HandleMessage(const DBRetReqLoadRandomNameMsg &rMsg);
	virtual void HandleMessage(const RetIdleTileMsg &rMsg);
	virtual void HandleMessage(const DBRetCreateCityMsg &rMsg);
	virtual void HandleMessage(const QueueFinishMsg &rMsg);
	virtual void HandleMessage(const DBRetAskCharListMsg &rMsg);
private:
	// ����û��Ƿ��Ŷӣ��Ƿ��������б���
	int  OLCheckPlayer(const ACCOUNTNAME & szAccount) const;
	bool OLIsHavePlayer(const ACCOUNTNAME & szAccount) const;
	// ���û���ӵ�������
	bool OLQueuePlayer(const ACCOUNTNAME & szAccount,int nPlayerID,int nQueuingLevel);
	// ������ҵ��Ŷ�Ȩ��
	void OLQueuePlayerUpdateRechargeValue(const ACCOUNTNAME & szAccount,int nPlayerID,int nRechargeValue);
	// ���û����Ŷ��б�ת�Ƶ���¼�б���
	void OLLoginPlayer(const ACCOUNTNAME & szAccount,int nPlayerID);
	// �û����µ�¼������Ϸ�б�ת�Ƶ���¼�б�
	void OLReLoginPlayer(const ACCOUNTNAME & szAccount,int nPlayerID);
	// �û���¼���ӵ�¼�б�ת�Ƶ���Ϸ�б���
	void OLPlayPlayer(const ACCOUNTNAME & szAccount,int nPlayerID,int64 userId);

	// ���˺�������
	void OLDelPlayer(const ACCOUNTNAME & szAccount);

private:

	void Tick_OLQueuing(const TimeInfo &rTimeInfo);

	void Tick_OLQueuingUpdateIndex(const TimeInfo &rTimeInfo);

	bool OlQueuFinishOne(void);

	// �����˺Ž����������
	void OLKickPlayerByAccount(const ACCOUNTNAME& szAccount,int nReason);

private:
	int  m_nOLQueuingUpdateIndexTime;

private:
	typedef std::list<PlayerQueuingData> OLLoginQueuingPlayerList;
	OLLoginQueuingPlayerList m_OlLoginQueuingPlayerList;

private:
	typedef std::map<ACCOUNTNAME, int> OLLoginPlayingPlayerMap;
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

	//////////////////////////////////////////////////////////////////////////
	//�������������
private:
	typedef std::map<CHARNAME,int> RandomIndexMap;
	typedef std::map<int,CHARNAME> RandomNamesMap;
	typedef std::pair<CHARNAME,int> RandomIndexPair;
	typedef std::pair<int,CHARNAME> RandomNamesPair;
	tint32				m_nRandomIndex;		//���ڸ�ÿ�β�ѯ��ͬ�׶ε�����
	RandomIndexMap		m_RandomIndexMap;	//������ŵĲ���	//��stl��
	RandomNamesMap		m_RandomNamesMap;	//������ŵı�����ɾ��	//��stl��
public:
	void		RemoveNameFromSet(const tchar* szName);
	void		GetRandomNames(bsarray<CHARNAME, RANDOM_NAME_SEND_COUNT> &aNames, tint8 length);

private:
	int  m_nCurPlayerCount;

private:

	LoginPlayerManager m_PlayerManager;

	
};

typedef GeneralInvoker<LoginService,200,200> LoginInvoker;


#endif