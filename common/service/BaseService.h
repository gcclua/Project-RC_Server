
#ifndef _BASESERVICE_H_
#define _BASESERVICE_H_

#include "Base.h"
#include "Message.h"
#include "TimeInfo.h"

class DBAssignTaskMsg;
class DBCheckConnectMsg;
class DBLoadUserMsg;
class DBRetLoadUserMsg;
class DBSaveUserMsg;
class DBRetSaveUserMsg;
class DBCreateCharMsg;
class DBRetCreateCharMsg;
class DBOpRetMsg;
class DBReqLoadTileDataMsg;
class DBRetLoadTileDataMsg;
class DBReqSaveTileDataMsg;
class DBRetSaveTileDataMsg;
class DBReqSaveCityDataMsg;
class QueueFinishMsg;
class SavePlayerDataMsg;
class DBReqSaveGuidMsg;
class DBAskCharListMsg;
class DBRetAskCharListMsg;
class DBReqLoadMapMarchMsg;
class DBRetLoadMapMarchMsg;


class PlayerEnterWorldMsg;
class PlayerLeaveWorldMsg;
class PlayerQuitGameMsg;
class MarchEnterSceneMsg;
class MarchLeaveSceneMsg;
class MarchLeaveBattleMsg;
class KickPlayerByGuidMsg;
class UpdateMarchBaseInfoMsg;
class NoticeMsg;
class MarchReqNearListMsg;
class ReqSetTileOwerMsg;
class ReqMarchSetPosMsg;
class RetMarchSetPosMsg;
class RetBattleEndMsg;
class RetBattleStartMsg;

class BroadcastChatMsg;
class SendTellChatMsg;
class SendTellChatSelfMsg;
class SendFriendChatMsg;
class SendFriendChatAskVipMsg;
class SendFriendChatSelfMsg;
class BroadcastNoticeMsg;
class BroadcastRollNoticeMsg;
class BroadcastLoudSpeakerMsg;

class TransportToMarch;
class TransportToAllScene;
class TransportToSceneClass;
class TransportToSceneInst;

// 发送给玩家的消息
class TransportToUser;
class MarchMoveMsg;
class MarchStopMsg;
class RetMarchMoveMsg;
class RetMarchTeleMoveMsg;
class RetUserSkillMsg;
class Update_Animation_State;
class Del_MarchMsg;
class Force_SetPosMsg;
class AttackFlyMsg;
class Player_EffectMsg;
class Remove_EffectMsg;
class Update_NeedImpactInfoMsg;
class MarchRetNearListMsg;
class AskJoinCopySceneMsg;
class MarchReqFightMsg;
class MarchRetFightMsg;
class MarchLeaveFightMsg;
class UpdateMarchMsg;
class MarchReqChangeSceneMsg;
class MarchAcceptChangeSceneMsg;
class MarchChangeSceneMsg;
class MarchOpenCopySceneMsg;
class ReqSetRobotOpenMsg;
class RetSetRobotOpenMsg;
class ReqMarchStartMsg;
class RetMarchStartMsg;


class UserSkillMsg;
class ReqBattleInfoMsg;
class RetBattleInfoMsg;
class ReqObjListMsg;
class RetObjListMsg;
class ObjTrackTargetMsg;
class ObjAttackTargetMsg;
class ObjHurtMsg;
class ReqArrangChangeMsg;
class RetArrangChangeMsg;


// 玩家城市中的消息
class DBReqCreateBuildMsg;
class DBRetCreateBuildMsg;
class DBReqSaveMarchDataMsg;


class KickPlayerByAccountMsg;
class AskModifyVipCostMsg;
class AccountStateCheckMsg;
class AccountOfflineMsg;
class ReqIdleTileMsg;
class RetIdleTileMsg;
class DBReqLoadRandomNameMsg;
class DBRetReqLoadRandomNameMsg;
class DBReqCreateCityMsg;
class DBRetCreateCityMsg;

class TrainTroopOverMsg;
class DBReqSaveTroopTrainMsg;
class DBReqSaveHeroMsg;

class BaseService
{
public:
	BaseService(void);
	virtual ~BaseService(void);

public:
	enum 
	{
		RUNSTATE_NORMAL = 0,
		RUNSTATE_SLOWLY,
		RUNSTATE_PAUSE,
	};

public:
	virtual int GetRunState(void) {return RUNSTATE_NORMAL;}

public:
	virtual void Tick( const TimeInfo &rTimeInfo);
public:
	void ReceiveMessage(ConstMessagePtr ConstPtr);

public:
	virtual void HandleMessage(const DBAssignTaskMsg &rMsg){};
	virtual void HandleMessage(const DBCheckConnectMsg &rMsg){};
	virtual void HandleMessage(const DBLoadUserMsg &rMsg){};
	virtual void HandleMessage(const DBRetLoadUserMsg &rMsg){};
	virtual void HandleMessage(const DBSaveUserMsg &rMsg){};
	virtual void HandleMessage(const DBRetSaveUserMsg &rMsg){};
	virtual void HandleMessage(const DBCreateCharMsg &rMsg){};
	virtual void HandleMessage(const DBRetCreateCharMsg &rMsg){};
	virtual void HandleMessage(const DBOpRetMsg &rMsg){};
	virtual void HandleMessage(const DBReqLoadTileDataMsg &rMsg){};
	virtual void HandleMessage(const DBRetLoadTileDataMsg &rMsg){};
	virtual void HandleMessage(const DBReqSaveTileDataMsg &rMsg){};
	virtual void HandleMessage(const DBRetSaveTileDataMsg &rMsg){};
	virtual void HandleMessage(const DBReqSaveCityDataMsg &rMsg){};
	virtual void HandleMessage(const QueueFinishMsg &rMsg){};
	virtual void HandleMessage(const SavePlayerDataMsg &rMsg){};
	virtual void HandleMessage(const PlayerEnterWorldMsg &rMsg) {};
	virtual void HandleMessage(const PlayerLeaveWorldMsg &rMsg) {};
	virtual void HandleMessage(const PlayerQuitGameMsg &rMsg) {};
	
	virtual void HandleMessage(const ReqSetTileOwerMsg &rMsg) {};
	virtual void HandleMessage(const DBRetLoadMapMarchMsg &rMsg){};
	virtual void HandleMessage(const DBReqLoadMapMarchMsg &rMsg){};
	virtual void HandleMessage(const DBReqSaveMarchDataMsg& rMsg){};

	virtual void HandleMessage(const MarchEnterSceneMsg &rMsg) {};
	virtual void HandleMessage(const MarchLeaveSceneMsg &rMsg) {};
	virtual void HandleMessage(const KickPlayerByGuidMsg &rMsg) {};
	virtual void HandleMessage(const UpdateMarchBaseInfoMsg &rMsg) {};
	virtual void HandleMessage(const NoticeMsg &rMsg) {};
	virtual void HandleMessage(const MarchReqNearListMsg &rMsg){};
	virtual void HandleMessage(const RetBattleEndMsg &rMsg){};
	virtual void HandleMessage(const RetBattleStartMsg &rMsg){};

	virtual void HandleMessage(const BroadcastChatMsg &rMsg) {};
	virtual void HandleMessage(const SendTellChatMsg &rMsg) {};
	virtual void HandleMessage(const SendTellChatSelfMsg &rMsg) {};
	virtual void HandleMessage(const SendFriendChatMsg &rMsg) {};
	virtual void HandleMessage(const SendFriendChatAskVipMsg &rMsg) {};
	virtual void HandleMessage(const BroadcastNoticeMsg &rMsg) {};
	virtual void HandleMessage(const SendFriendChatSelfMsg &rMsg) {};
	virtual void HandleMessage(const BroadcastRollNoticeMsg &rMsg) {};
	virtual void HandleMessage(const BroadcastLoudSpeakerMsg &rMsg) {};


	virtual void HandleMessage(const TransportToMarch &rMsg) {};
	virtual void HandleMessage(const TransportToAllScene &rMsg) {};
	virtual void HandleMessage(const TransportToSceneClass &rMsg) {};
	virtual void HandleMessage(const TransportToSceneInst &rMsg) {};

	virtual void HandleMessage(const TransportToUser &rMsg) {};
	virtual void HandleMessage(const MarchMoveMsg &rMsg) {};
	virtual void HandleMessage(const RetMarchMoveMsg &rMsg) {};
	virtual void HandleMessage(const RetMarchTeleMoveMsg &rMsg){};
	virtual void HandleMessage(const RetUserSkillMsg &rMsg){};
	virtual void HandleMessage(const Update_Animation_State &rMsg){};
	virtual void HandleMessage(const Del_MarchMsg &rMsg){};
	virtual void HandleMessage(const Force_SetPosMsg &rMsg) {};
	virtual void HandleMessage(const AttackFlyMsg &rMsg){};
	virtual void HandleMessage(const Update_NeedImpactInfoMsg &rMsg){};
	virtual void HandleMessage(const Remove_EffectMsg &rMsg){};
	virtual void HandleMessage(const Player_EffectMsg &rMsg){};
	virtual void HandleMessage(const MarchStopMsg &rMsg){};
	virtual void HandleMessage(const MarchRetNearListMsg &rMsg){};
	virtual void HandleMessage(const AskJoinCopySceneMsg &rMsg){};
	virtual void HandleMessage(const MarchReqFightMsg &rMsg){};
	virtual void HandleMessage(const MarchRetFightMsg &rMsg){};
	virtual void HandleMessage(const MarchLeaveFightMsg &rMsg){};
	virtual void HandleMessage(const MarchLeaveBattleMsg &rMsg){};
	virtual void HandleMessage(const MarchReqChangeSceneMsg &rMsg){};
	virtual void HandleMessage(const MarchAcceptChangeSceneMsg &rMsg){};
	virtual void HandleMessage(const MarchChangeSceneMsg &rMsg){};
	virtual void HandleMessage(const MarchOpenCopySceneMsg &rMsg){};
	virtual void HandleMessage(const UpdateMarchMsg &rMsg){};
	virtual void HandleMessage(const ReqSetRobotOpenMsg &rMsg){};
	virtual void HandleMessage(const RetSetRobotOpenMsg &rMsg){};
	virtual void HandleMessage(const ReqMarchStartMsg &rMsg){};
	virtual void HandleMessage(const RetMarchStartMsg &rMsg){};
	virtual void HandleMessage(const UserSkillMsg &rMsg){};
	virtual void HandleMessage(const RetBattleInfoMsg &rMsg){};
	virtual void HandleMessage(const ReqBattleInfoMsg &rMsg){};
	virtual void HandleMessage(const RetObjListMsg &rMsg){};
	virtual void HandleMessage(const ReqObjListMsg &rMsg){};
	virtual void HandleMessage(const ObjTrackTargetMsg &rMsg){};
	virtual void HandleMessage(const ObjAttackTargetMsg &rMsg){};
	virtual void HandleMessage(const ObjHurtMsg &rMsg){};
	

	virtual void HandleMessage(const DBReqCreateBuildMsg &rMsg){};
	virtual void HandleMessage(const DBRetCreateBuildMsg &rMsg){};
	virtual void HandleMessage(const DBReqSaveGuidMsg &rMsg){};
	virtual void HandleMessage(const DBReqSaveTroopTrainMsg &rMsg){};
	virtual void HandleMessage(const DBReqSaveHeroMsg &rMsg){};
	
	virtual void HandleMessage(const KickPlayerByAccountMsg &rMsg){};
	virtual void HandleMessage(const AskModifyVipCostMsg &rMsg){};
	virtual void HandleMessage(const AccountStateCheckMsg &rMsg){};
	virtual void HandleMessage(const DBAskCharListMsg &rMsg){};
	virtual void HandleMessage(const DBRetAskCharListMsg &rMsg){};
	virtual void HandleMessage(const AccountOfflineMsg &rMsg){};
	virtual void HandleMessage(const ReqIdleTileMsg &rMsg){};
	virtual void HandleMessage(const RetIdleTileMsg &rMsg){};
	virtual void HandleMessage(const DBReqLoadRandomNameMsg &rMsg){};
	virtual void HandleMessage(const DBRetReqLoadRandomNameMsg &rMsg){};
	virtual void HandleMessage(const DBReqCreateCityMsg &rMsg){};
	virtual void HandleMessage(const DBRetCreateCityMsg &rMsg){};


	virtual void HandleMessage(const TrainTroopOverMsg &rMsg){};
	virtual void HandleMessage(const ReqArrangChangeMsg &rMsg){};
	virtual void HandleMessage(const RetArrangChangeMsg &rMsg){};
	virtual void HandleMessage(const RetMarchSetPosMsg &rMsg){};
	virtual void HandleMessage(const ReqMarchSetPosMsg &rMsg){};
	
	
protected:
	bool IsHaveUnHandleMessage(void);

private:
	void HandleAllMessage(void);

private: ConstMessagePtrTSList m_ConstMessagePtrTsList;

};



#endif