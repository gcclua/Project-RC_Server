#ifndef _SCENEMSG_H_
#define _SCENEMSG_H_

#include "service/Message.h"
#include "Player/Player.h"
#include "Scene/GameStruct_Scene.h"
#include "march/GameStruct_March.h"

MESSAGE_DEF_BEGIN(MarchEnterSceneMsg)
	bool m_bFirstEnter;
	March m_March;
MESSAGE_DEF_END(MarchEnterSceneMsg)

MESSAGE_DEF_BEGIN(MarchLeaveSceneMsg)
	int64 m_guid;
	March m_March;
	int m_nDelResult;
MESSAGE_DEF_END(MarchLeaveSceneMsg)

MESSAGE_DEF_BEGIN(MarchLeaveBattleMsg)
	March m_March;
MESSAGE_DEF_END(MarchLeaveBattleMsg)

MESSAGE_DEF_BEGIN(ReqMarchStartMsg)
	ScenePos m_Pos;
	March m_March;
MESSAGE_DEF_END(ReqMarchStartMsg)

MESSAGE_DEF_BEGIN(RetMarchStartMsg)
	int64 m_marchId;
	int   m_ret;
MESSAGE_DEF_END(RetMarchStartMsg)

MESSAGE_DEF_BEGIN(MarchMoveMsg)
	int   m_nPosCount;
	bsvector<int> m_nPosX;
	bsvector<int> m_nPoxZ;
	bool   m_ismoving;
MESSAGE_DEF_END(MarchMoveMsg)

MESSAGE_DEF_BEGIN(RetMarchMoveMsg)
	int m_nObjId;
	int m_nPosCount;
	bsvector<int> m_nPosX;
	bsvector<int> m_nPoxZ;
	bsvector<int> m_nSerial;
	int m_nSceneId;
MESSAGE_DEF_END(RetMarchMoveMsg)

MESSAGE_DEF_BEGIN(MarchReqNearListMsg)
	
MESSAGE_DEF_END(MarchReqNearListMsg)

MESSAGE_DEF_BEGIN(MarchRetNearListMsg)
	int m_nObjId;
	bsvector<MarchBaseInfo> m_BaseMarchVec;
	int m_nSceneId;
MESSAGE_DEF_END(MarchRetNearListMsg)

MESSAGE_DEF_BEGIN(RetMarchTeleMoveMsg)
	int m_nObjId;
	int m_nPosX;
	int m_nPoxZ;
	int m_nSceneId;
MESSAGE_DEF_END(RetMarchTeleMoveMsg)

MESSAGE_DEF_BEGIN(MarchReqFightMsg)
	int m_DestSceneID;
	int m_nType;
	int64 m_nDefenceId;
	int64 m_nAtttackId;
	int m_nSceneId;
MESSAGE_DEF_END(MarchReqFightMsg)
	
MESSAGE_DEF_BEGIN(MarchRetFightMsg)
int64 m_nMarchId;
int   m_nSceneId;
int   m_nResult;
MESSAGE_DEF_END(MarchRetFightMsg)

MESSAGE_DEF_BEGIN(MarchOpenCopySceneMsg)
	int m_DestSceneID;
	int m_nType;
	int64 m_nDefenceId;
	int64 m_nAtttackId;
	int  m_nSceneId;

MESSAGE_DEF_END(MarchOpenCopySceneMsg)

MESSAGE_DEF_BEGIN(MarchLeaveFightMsg)
	
MESSAGE_DEF_END(MarchLeaveFightMsg)

MESSAGE_DEF_BEGIN(AskJoinCopySceneMsg)
	SceneID m_DestSceneID;
	tint32 m_nCopySceneDifficulty;
	tint32 m_CopyScenelevel;
	int64  m_nAttackId;
	int64  m_nDefenceId;
MESSAGE_DEF_END(AskJoinCopySceneMsg)

MESSAGE_DEF_BEGIN(MarchStopMsg)
	int m_nX;
	int m_nZ;
	int m_nSerial;
	int m_nSceneId;
	int m_nObjId;
MESSAGE_DEF_END(MarchStopMsg)
	//修改场景要用guid，涉及到很多检测
MESSAGE_DEF_BEGIN(MarchReqChangeSceneMsg)
	SceneID m_CurSceneID;
	SceneID m_DestSceneID;
	int64   m_guid;
MESSAGE_DEF_END(MarchReqChangeSceneMsg)

MESSAGE_DEF_BEGIN(MarchAcceptChangeSceneMsg)
	SceneID m_DestSceneID;
	int64   m_guid;
MESSAGE_DEF_END(MarchAcceptChangeSceneMsg)

MESSAGE_DEF_BEGIN(MarchChangeSceneMsg)
	March m_March;
	SceneID m_DestSceneID;
MESSAGE_DEF_END(MarchChangeSceneMsg)

MESSAGE_DEF_BEGIN(Del_MarchMsg)
	int m_nObjId;
	int m_nSceneId;
	int m_nMarchObjId;
MESSAGE_DEF_END(Del_MarchMsg)

MESSAGE_DEF_BEGIN(UserSkillMsg)
	int m_nSkillId;
	int m_nTargetId;
	int m_nSenderId;
MESSAGE_DEF_END(UserSkillMsg)
	

MESSAGE_DEF_BEGIN(RetUserSkillMsg)
	int m_nSkillId;
	int m_nTargetId;
	int m_nSenderId;
	FLString<256> m_nSkillname;
	int m_nSkillFailType;
	int m_nSceneId;
MESSAGE_DEF_END(RetUserSkillMsg)

MESSAGE_DEF_BEGIN(ReqBattleInfoMsg)
	int m_nSceneId;
MESSAGE_DEF_END(ReqBattleInfoMsg)

MESSAGE_DEF_BEGIN(RetBattleInfoMsg)
	int m_nSceneId;
	bsvector<SceneObj> m_objList;
MESSAGE_DEF_END(RetBattleInfoMsg)

MESSAGE_DEF_BEGIN(ReqObjListMsg)
	int m_nSceneId;
MESSAGE_DEF_END(ReqObjListMsg)

MESSAGE_DEF_BEGIN(RetObjListMsg)
	int m_nSceneId;
	bsvector<ObjInfo> m_objList;
MESSAGE_DEF_END(RetObjListMsg)

MESSAGE_DEF_BEGIN(Update_Animation_State)
	int m_nAnimationState;
	int m_nVerticalOffDis;
	int m_nHorizontalOffDis;
	int m_nStateLastTime;
	int m_nStateResortTime;
	int m_nHitTimes;
	int m_nHitInterval;
	int m_nObjId;
	int m_nSceneId;
MESSAGE_DEF_END(Update_Animation_State)
	
MESSAGE_DEF_BEGIN(Force_SetPosMsg)
int m_nPosX;
int m_nPoxZ;
int m_nObjId;
int m_nSceneId;
MESSAGE_DEF_END(Force_SetPosMsg)

MESSAGE_DEF_BEGIN(AttackFlyMsg)
	int m_nDis; //击飞水平位移
	int m_nHight;//击飞高度
	int m_nFlyTime; //击飞时间
	int m_nObjId;
	int m_nSceneId;
MESSAGE_DEF_END(AttackFlyMsg)

MESSAGE_DEF_BEGIN(Update_NeedImpactInfoMsg)
	bsvector<int> m_nImpactId; //Buff Id
	bsvector<int> m_iImpactLogicId; //Buff 逻辑ID
	bsvector<int> m_nIsForever; //Buff 是否永久
	bsvector<int> m_nRemainTime; //Buff 剩余时间
	bsvector<int> m_nIsAdd; //添加或删除 0删除 1添加
	int m_nObjId;
	int m_nSceneId;
MESSAGE_DEF_END(Update_NeedImpactInfoMsg)

MESSAGE_DEF_BEGIN(Player_EffectMsg)
	int m_nEffectId;
	int m_nObjId;
	int m_nSceneId;
MESSAGE_DEF_END(Player_EffectMsg)


MESSAGE_DEF_BEGIN(Remove_EffectMsg)
int m_nEffectId;
int m_nObjId;
int m_nSceneId;
MESSAGE_DEF_END(Remove_EffectMsg)

MESSAGE_DEF_BEGIN(ReqSetRobotOpenMsg)
	bool m_bOpen; 
	int m_nSceneId;
MESSAGE_DEF_END(ReqSetRobotOpenMsg)

MESSAGE_DEF_BEGIN(RetSetRobotOpenMsg)
	int m_nSceneId;
	int m_nRet;
MESSAGE_DEF_END(RetSetRobotOpenMsg)

MESSAGE_DEF_BEGIN(KickPlayerByGuidMsg)
	int m_nReason;
MESSAGE_DEF_END(KickPlayerByGuidMsg)

MESSAGE_DEF_BEGIN(UpdateMarchBaseInfoMsg)
	MarchBaseInfo m_BaseInfo;
MESSAGE_DEF_END(UpdateMarchBaseInfoMsg)

MESSAGE_DEF_BEGIN(ObjTrackTargetMsg)
	int m_nSceneId;
	int m_nObjId;
	int m_nTargetId;
MESSAGE_DEF_END(ObjTrackTargetMsg)

MESSAGE_DEF_BEGIN(UpdateMarchMsg)
	March m_rMarch;
MESSAGE_DEF_END(UpdateMarchMsg)

MESSAGE_DEF_BEGIN(ObjAttackTargetMsg)
	int m_nSceneId;
	int m_nObjId;
	int m_nTargetId;
MESSAGE_DEF_END(ObjAttackTargetMsg)
	
MESSAGE_DEF_BEGIN(ObjHurtMsg)
int m_nSceneId;
int m_nObjId;
int m_nAttackId;
int m_damage;
int m_IsDie;
int m_DeadCount;
MESSAGE_DEF_END(ObjHurtMsg);


MESSAGE_DEF_BEGIN(NoticeMsg)
	FLString<128> m_szNotice;
	int m_nIsFilterRepeat;
MESSAGE_DEF_END(NoticeMsg)


#endif
