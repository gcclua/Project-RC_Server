
#ifndef _USER_H_
#define _USER_H_

#include "Base.h"
#include "Service/TimeInfo.h"
#include "DBStruct/DBStruct_User.h"
#include "user/GameDefine_User.h"
#include "Chat/GameStruct_TextChat.h"

class Player;
class BaseManager;
class Packet;


class CG_REQ_NEAR_LIST;
class CG_CHAT;
class CG_MOVE;
class CG_FIGHT;
class CG_LEAVE_COPYSCENE;
class CG_ROBOT_OPEN;
class CG_ASSIGN_HERO;
class CG_SEND_MARCH;
class GC_LOGIN_RET;
class CG_SKILL_USE;
class CG_BATTLEINFOR;
class CG_OBJPOSLIST;
class CG_BATTLEPREPARE;
class CG_Building_LevelUp;
class CG_Troop_Train;
class CG_MARCH_MOVE;


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
class RetSetRobotOpenMsg;
class RetMarchStartMsg;
class RetBattleInfoMsg;
class RetObjListMsg;
class ObjTrackTargetMsg;
class ObjAttackTargetMsg;
class ObjHurtMsg;
class KickPlayerByGuidMsg;
class MarchRetFightMsg;
class UpdateMarchMsg;
class RetArrangChangeMsg;
class RetBattleEndMsg;
class RetBattleStartMsg;


class TrainTroopOverMsg;


class User
{
public:
	User(Player* pPlayer);
	virtual ~User(void){};

	User(ACCOUNTNAME name);

private:

	Player* m_pPlayer;

public:
	int64 GetGuid(void) const {return m_guid;}
	void  SetGuid(int64 val){m_guid = val;}

	const CHARNAME&  GetName(void)const{return m_Name;}
	void SetName(const CHARNAME& NewName);
	void SetName(const tchar* strName);

	const ACCOUNTNAME GetAccount() const {return m_szAccount;}

	int   GetWorldId() const {return m_nWorldId;}
	void  SetWorldId(int val) {m_nWorldId = val;}

public:
	void SerializeToDB(DBFullUserData& rDest);// 数据拷贝到存储结构中
	void SerializeFromDB(const DBFullUserData& rSour);// 存储结构中数据拷贝
	void Init(void);
	void InitAsCreateNewChar(int nTileId,int nX,int nZ);
	void InitManage(void);
	// 登录的时候，结算下该结算的东西是否完成
	void OnLogin(void);
	void Tick(const TimeInfo& rTimeInfo);

public:
	bool SendMarchIntoMap(int64 nMarchId);
private:
	bool UpdateMarchState(int64 nMarchId,int nState);
public:

	bool AssignHeroToMarch(int64 nMarchId,int64 nHeroId);

public:
	void SendPacket(const Packet &rPacket);

public:
	//参考字典格式参考 DictionaryFormat::FormatDictionary函数 IsFilterRepeat : true时候过滤，false不过滤。
	void SendNotice(const char* szNotice,bool IsFilterRepeat = false);

private:
	void Tick_Save(const TimeInfo& rTimeInfo);

private:
	int m_nSaveTimeInterval;

private:
	BaseManager* GetBaseManager(int nType);

private:
	
	typedef std::map<int,BaseManager*> BaseManagerPtrMap;
	BaseManagerPtrMap m_mapBaseManager;

private:
	int64  m_guid;
	CHARNAME  m_Name;
	int    m_nLevel;
	int    m_Gender;
	int    m_nWorldId; //玩家所属服务器
	int64  m_nCityId;
	ACCOUNTNAME m_szAccount;

public:
	tuint32 HandlePacket(::CG_REQ_NEAR_LIST &rPacket);		//处理客户端发来的请求附近玩家消息
	tuint32 HandlePacket(::CG_CHAT &rPacket);
	tuint32 HandlePacket(::CG_MOVE &rPacket);
	tuint32 HandlePacket(::CG_FIGHT & rPacket);
	tuint32 HandlePacket(::CG_LEAVE_COPYSCENE & rPacket);
	tuint32 HandlePacket(::CG_ROBOT_OPEN &rPacket);
	tuint32 HandlePacket(::CG_ASSIGN_HERO &rPacket);
	tuint32 HandlePacket(::CG_SEND_MARCH &rPacket);
	tuint32 HandlePacket(::CG_SKILL_USE &rPacket);
	tuint32 HandlePacket(::CG_BATTLEINFOR &rPacket);
	tuint32 HandlePacket(::CG_OBJPOSLIST &rPacket);
	tuint32 HandlePacket(::CG_Building_LevelUp &rPacket);
	tuint32 HandlePacket(::CG_Troop_Train &rPacket);
	tuint32 HandlePacket(::CG_BATTLEPREPARE &rPacket);
	tuint32 HandlePacket(::CG_MARCH_MOVE &rPacket);
	void    FillGCLogin(::GC_LOGIN_RET &rPacket);
	bool	IsNoneInvalidText(CG_CHAT &rPacket);
	void	HandleChatInfo(const TextChat& textchat, tint32 nVoiceIndex = invalid_id);

public:

	void HandleMessage(const MarchRetNearListMsg &rMsg);
	void HandleMessage(const MarchStopMsg &rMsg);
	void HandleMessage(const RetMarchMoveMsg &rMsg);
	void HandleMessage(const RetMarchTeleMoveMsg &rMsg);
	void HandleMessage(const RetUserSkillMsg &rMsg);
	void HandleMessage(const RetArrangChangeMsg &rMsg);
	void HandleMessage(const Update_Animation_State &rMsg);
	void HandleMessage(const ObjTrackTargetMsg &rMsg);
	void HandleMessage(const ObjAttackTargetMsg &rMsg);
	void HandleMessage(const ObjHurtMsg &rMsg);
	void HandleMessage(const Del_MarchMsg &rMsg);
	void HandleMessage(const Force_SetPosMsg &rMsg);
	void HandleMessage(const AttackFlyMsg &rMsg);
	void HandleMessage(const Player_EffectMsg &rMsg);
	void HandleMessage(const Update_NeedImpactInfoMsg &rMsg);
	void HandleMessage(const Remove_EffectMsg &rMsg);
	void HandleMessage(const NoticeMsg &rMsg);
	void HandleMessage(const RetSetRobotOpenMsg& rMsg);
	void HandleMessage(const RetMarchStartMsg& rMsg);
	void HandleMessage(const RetBattleInfoMsg& rMsg);
	void HandleMessage(const RetObjListMsg &rMsg);
	void HandleMessage(const KickPlayerByGuidMsg &rMsg);
	void HandleMessage(const MarchRetFightMsg &rMsg);
	void HandleMessage(const UpdateMarchMsg &rMsg);
	void HandleMessage(const RetBattleEndMsg& rMsg);
	void HandleMessage(const RetBattleStartMsg& rMsg);

	void HandleMessage(const TrainTroopOverMsg& rMsg);

	// 禁言解禁时间start
	//////////////////////////////////////////////////////////////////////////
public:
	time_t GetUnForbidTalkTime()const{return m_UnForbidTalkTime;}
	void   SetUnForbidTalkTime(time_t val){m_UnForbidTalkTime = val;}
private:
	time_t m_UnForbidTalkTime; //禁言解禁时间
	/////////////////////////////////////////////////////////////////////////
	// 禁言解禁时间end

};

//typedef boost::shared_ptr<User> UserPtr;
typedef std::map<int64,User> UserMap;

#endif