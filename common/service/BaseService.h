
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

class PlayerEnterWorldMsg;
class PlayerLeaveWorldMsg;
class MarchEnterSceneMsg;
class MarchLeaveSceneMsg;
class KickPlayerByGuidMsg;
class UpdateMarchBaseInfoMsg;
class NoticeMsg;
class MarchReqNearListMsg;

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

	virtual void HandleMessage(const MarchEnterSceneMsg &rMsg) {};
	virtual void HandleMessage(const MarchLeaveSceneMsg &rMsg) {};
	virtual void HandleMessage(const KickPlayerByGuidMsg &rMsg) {};
	virtual void HandleMessage(const UpdateMarchBaseInfoMsg &rMsg) {};
	virtual void HandleMessage(const NoticeMsg &rMsg) {};
	virtual void HandleMessage(const MarchReqNearListMsg &rMsg){};

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
	

protected:
	bool IsHaveUnHandleMessage(void);

private:
	void HandleAllMessage(void);

private: ConstMessagePtrTSList m_ConstMessagePtrTsList;

};



#endif