////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：13:34 2014-3-3
//             说明：效果数据存储
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBSTRUCTIMPACT_H__
#define __DBSTRUCTIMPACT_H__

#include "Base.h"
#include "ImpactStruct/GameStruct_Impact.h"
#include "Scene/GameDefine_Scene.h"

struct  DBImpactStruct
{
public:
	void				CleanUp();
	void				CopyFrom(const DBImpactStruct& rSour);
public:
	int m_nImpactId;//BuffId
	int m_nSkillId;//技能ID
	int m_nSenderType;//obj Type Npc 玩家 伙伴 僵尸玩家
	int64 m_SenderGuid;//玩家和伙伴有GUID
	int m_nSceneClassId;//BUFF发送时的场景Class ID
	int m_nSceneInstanceId;//BUFF发送时的场景实例 ID
	int m_nSenderObjId;//发送者objId
	float m_fContinuTime;//持续时间(单位:秒)
	time_t m_nEffectTime;//BUFF生效的时间(单位:秒)
	int m_nIntervalTime;//间隔触发时间(单位:毫秒)
	int m_nIntervalElapsed;//流逝的间隔(单位:毫秒)
	int m_nDelayTime;//延迟生效
	uint8 m_nImpactWrapCnt;//叠加层数

	int m_aParams[ImpactStruct::MAX_IMAPCT_PARAM_NUM];
};
struct DBImpact
{
public:
	DBImpact(void) {CleanUp();}
	~DBImpact(void) {}
	void CleanUp(void);
	void InitAsCreateNewChar();
	void CopyFrom(const DBImpact& rSour);
public:
	DBImpactStruct   m_buffList[MAX_BUFF_SIZE];
};
#endif