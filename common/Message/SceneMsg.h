#ifndef _SCENEMSG_H_
#define _SCENEMSG_H_

#include "service/Message.h"
#include "Player/Player.h"
#include "Scene/GameInterface_Scene.h"
#include "scene/obj/Obj_March.h"

MESSAGE_DEF_BEGIN(MarchEnterSceneMsg)
	bool m_bFirstEnter;
	Obj_MarchPtr m_MarchPtr;
MESSAGE_DEF_END(MarchEnterSceneMsg)

MESSAGE_DEF_BEGIN(MarchLeaveSceneMsg)
	int64 m_guid;
PlayerPtr m_PlayerPtr;
int m_nDelResult;
MESSAGE_DEF_END(MarchLeaveSceneMsg)

MESSAGE_DEF_BEGIN(MarchMoveMsg)
	int   m_nPosCount;
int64 m_marchId;
bsvector<int> m_nPosX;
bsvector<int> m_nPoxZ;
bool   m_ismoving;
MESSAGE_DEF_END(MarchMoveMsg)

MESSAGE_DEF_BEGIN(RetMarchMoveMsg)
	int m_serverId;
	int   m_nPosCount;
	bsvector<int> m_nPosX;
	bsvector<int> m_nPoxZ;
	bsvector<int> m_nSerial;
MESSAGE_DEF_END(RetMarchMoveMsg)

MESSAGE_DEF_BEGIN(MarchReqNearListMsg)
	int64 m_marchId;
MESSAGE_DEF_END(MarchReqNearListMsg)

MESSAGE_DEF_BEGIN(MarchRetNearListMsg)
	int64 m_marchId;
bsvector<MarchBaseInfo> m_BaseMarchVec;
MESSAGE_DEF_END(MarchRetNearListMsg)

MESSAGE_DEF_BEGIN(RetMarchTeleMoveMsg)
	int m_nObjId;
	int m_nPosX;
	int m_nPoxZ;
MESSAGE_DEF_END(RetMarchTeleMoveMsg)

MESSAGE_DEF_BEGIN(MarchStopMsg)
	int m_serverId;
	tfloat32 m_fX;
	tfloat32 m_fZ;
	int m_nSerial;
MESSAGE_DEF_END(MarchStopMsg)


MESSAGE_DEF_BEGIN(RetUserSkillMsg)
	int m_nSkillId;
	int m_nSenderId;
	int m_nTargetId;
	FLString<256> m_nSkillname;
	int m_nSkillFailType;
MESSAGE_DEF_END(RetUserSkillMsg)

MESSAGE_DEF_BEGIN(Update_Animation_State)
	int m_nObjId;
	int m_nAnimationState;
	int m_nVerticalOffDis;
	int m_nHorizontalOffDis;
	int m_nStateLastTime;
	int m_nStateResortTime;
	int m_nHitTimes;
	int m_nHitInterval;
MESSAGE_DEF_END(Update_Animation_State)

MESSAGE_DEF_BEGIN(Del_MarchMsg)
	int m_nObjId;
MESSAGE_DEF_END(Del_MarchMsg)
	
MESSAGE_DEF_BEGIN(Force_SetPosMsg)
int m_nObjId;
int m_nPosX;
int m_nPoxZ;
MESSAGE_DEF_END(Force_SetPosMsg)

MESSAGE_DEF_BEGIN(AttackFlyMsg)
	int m_nObjId;//击飞的objId
	int m_nDis; //击飞水平位移
	int m_nHight;//击飞高度
	int m_nFlyTime; //击飞时间	
MESSAGE_DEF_END(AttackFlyMsg)

MESSAGE_DEF_BEGIN(Update_NeedImpactInfoMsg)
	int m_nObjId;//objId
	bsvector<int> m_nImpactId; //Buff Id
	bsvector<int> m_iImpactLogicId; //Buff 逻辑ID
	bsvector<int> m_nIsForever; //Buff 是否永久
	bsvector<int> m_nRemainTime; //Buff 剩余时间
	bsvector<int> m_nIsAdd; //添加或删除 0删除 1添加

MESSAGE_DEF_END(Update_NeedImpactInfoMsg)

MESSAGE_DEF_BEGIN(Player_EffectMsg)
	int m_nObjId;
	int m_nEffectId;
MESSAGE_DEF_END(Player_EffectMsg)


MESSAGE_DEF_BEGIN(Remove_EffectMsg)
	int m_nObjId;
int m_nEffectId;
MESSAGE_DEF_END(Remove_EffectMsg)



MESSAGE_DEF_BEGIN(KickPlayerByGuidMsg)
	int m_nReason;
MESSAGE_DEF_END(KickPlayerByGuidMsg)

MESSAGE_DEF_BEGIN(UpdateMarchBaseInfoMsg)
	MarchBaseInfo m_BaseInfo;
MESSAGE_DEF_END(UpdateMarchBaseInfoMsg)


MESSAGE_DEF_BEGIN(NoticeMsg)
	FLString<128> m_szNotice;
	int m_nIsFilterRepeat;
MESSAGE_DEF_END(NoticeMsg)


#endif
