
#ifndef _USER_H_
#define _USER_H_

#include "Base.h"
#include "Service/TimeInfo.h"
#include "DBStruct/DBStruct_User.h"
#include "user/GameDefine_User.h"
#include "Chat/GameStruct_TextChat.h"

class Player;
class BaseManager;
typedef boost::shared_ptr<BaseManager> BaseManagerPtr;

class CG_REQ_NEAR_LIST;
class CG_CHAT;
class CG_MOVE;
class MarchRetNearListMsg;
class RetMarchMoveMsg;
class MarchStopMsg;
class RetMarchTeleMoveMsg;
class RetUserSkillMsg;
class Update_Animation_State;
class Del_MarchMsg;
class Force_SetPosMsg;
class AttackFlyMsg;
class Player_EffectMsg;
class Remove_EffectMsg;
class Update_NeedImpactInfoMsg;
class NoticeMsg;

class User
{
public:
	User(Player* pPlayer);
	virtual ~User(void){};

private:

	Player* m_pPlayer;

public:
	int64 GetGuid(void) const {return m_guid;}
	void  SetGuid(int64 val){m_guid = val;}

	const CHARNAME&  GetName(void)const{return m_Name;}
	void SetName(const CHARNAME& NewName);
	void SetName(const tchar* strName);

public:
	void SerializeToDB(DBFullUserData& rDest);// ���ݿ������洢�ṹ��
	void SerializeFromDB(const DBFullUserData& rSour);// �洢�ṹ�����ݿ���
	void Init(void);
	void OnLogin(void);
	void Tick(const TimeInfo& rTimeInfo);

public:
	void SendPacket(const Packet &rPacket);

public:
	//�ο��ֵ��ʽ�ο� DictionaryFormat::FormatDictionary���� IsFilterRepeat : trueʱ����ˣ�false�����ˡ�
	void SendNotice(const char* szNotice,bool IsFilterRepeat = false);

private:
	void Tick_Save(const TimeInfo& rTimeInfo);

private:
	int m_nSaveTimeInterval;

private:
	BaseManagerPtr GetBaseManager(int nType);

private:
	
	typedef std::map<int,BaseManagerPtr> BaseManagerPtrMap;
	BaseManagerPtrMap m_mapBaseManager;

private:
	int64  m_guid;
	CHARNAME  m_Name;
	int    m_nLevel;
	int    m_nExp;

public:
	tuint32 HandlePacket(::CG_REQ_NEAR_LIST &rPacket);		//����ͻ��˷��������󸽽������Ϣ
	tuint32 HandlePacket(::CG_CHAT &rPacket);
	tuint32 HandlePacket(::CG_MOVE &rPacket);
	bool	IsNoneInvalidText(CG_CHAT &rPacket);
	void	HandleChatInfo(const TextChat& textchat, tint32 nVoiceIndex = invalid_id);

public:

	void HandleMessage(const MarchRetNearListMsg& rMsg);
	void HandleMessage(const MarchStopMsg &rMsg);
	void HandleMessage(const RetMarchMoveMsg &rMsg);
	void HandleMessage(const RetMarchTeleMoveMsg &rMsg);
	void HandleMessage(const RetUserSkillMsg &rMsg);
	void HandleMessage(const Update_Animation_State &rMsg);
	void HandleMessage(const Del_MarchMsg& rMsg);
	void HandleMessage(const Force_SetPosMsg& rMsg);
	void HandleMessage(const AttackFlyMsg &rMsg);
	void HandleMessage(const Player_EffectMsg &rMsg);
	void HandleMessage(const Update_NeedImpactInfoMsg& rMsg);
	void HandleMessage(const Remove_EffectMsg& rMsg);
	void HandleMessage(const NoticeMsg& rMsg);
	// ���Խ��ʱ��start
	//////////////////////////////////////////////////////////////////////////
public:
	time_t GetUnForbidTalkTime()const{return m_UnForbidTalkTime;}
	void   SetUnForbidTalkTime(time_t val){m_UnForbidTalkTime = val;}
private:
	time_t m_UnForbidTalkTime; //���Խ��ʱ��
	/////////////////////////////////////////////////////////////////////////
	// ���Խ��ʱ��end

};

typedef boost::shared_ptr<User> UserPtr;
typedef std::map<int64,UserPtr> UserPtrMap;

#endif