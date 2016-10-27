#include "GameStruct_Impact.h"
#include "DBStruct/DBStruct_Impact.h"
#include "Table/Table_Impact.h"

bool ImpactStruct::SerializeToDB(DBImpactStruct& rDest)
{
	__ENTER_FUNCTION
	rDest.m_nImpactId =m_nImpactId;//BuffId
	rDest.m_nSkillId =m_nSkillId;//技能ID
	rDest.m_nSenderType =m_nSenderType;//obj Type Npc 玩家 伙伴 僵尸玩家
	rDest.m_SenderGuid =m_SenderGuid;//玩家和伙伴有GUID
	rDest.m_nSceneClassId =m_nSceneClassId;//BUFF发送时的场景Class ID
	rDest.m_nSceneInstanceId =m_nSceneInstanceId;//BUFF发送时的场景实例 ID
	rDest.m_nSenderObjId =m_nSenderObjId;//发送者objId
	rDest.m_fContinuTime =m_fContinuTime;//持续时间(单位:秒)
	rDest.m_nEffectTime =m_nEffectTime;//BUFF生效的时间(单位:秒)
	rDest.m_nIntervalTime =m_nIntervalTime;//间隔触发时间(单位:毫秒)
	rDest.m_nIntervalElapsed =m_nIntervalElapsed;//流逝的间隔(单位:毫秒)
	rDest.m_nDelayTime =m_nDelayTime;//延迟生效
	rDest.m_nImpactWrapCnt =m_nImpactWrapCnt;//叠加层数
 	for (int i=0;i<MAX_IMAPCT_PARAM_NUM;i++)
 	{
 		rDest.m_aParams[i] = m_aParams[i];
 	}
	return true;
	__LEAVE_FUNCTION
		return false;
}

bool ImpactStruct::SerializeFromDB(const DBImpactStruct& rSour)
{
	__ENTER_FUNCTION
	m_nImpactId =rSour.m_nImpactId;//BuffId
	m_nSkillId =rSour.m_nSkillId;//技能ID
	m_nSenderType =rSour.m_nSenderType;//obj Type Npc 玩家 伙伴 僵尸玩家
	m_SenderGuid =rSour.m_SenderGuid;//玩家和伙伴有GUID
	m_nSceneClassId =rSour.m_nSceneClassId;//BUFF发送时的场景Class ID
	m_nSceneInstanceId =rSour.m_nSceneInstanceId;//BUFF发送时的场景实例 ID
	m_nSenderObjId =rSour.m_nSenderObjId;//发送者objId
	m_fContinuTime =rSour.m_fContinuTime;//持续时间(单位:秒)
	m_nEffectTime =rSour.m_nEffectTime;//BUFF生效的时间(单位:秒)
	m_nIntervalTime =rSour.m_nIntervalTime;//间隔触发时间(单位:毫秒)
	m_nIntervalElapsed =rSour.m_nIntervalElapsed;//流逝的间隔(单位:毫秒)
	m_nDelayTime =rSour.m_nDelayTime;//延迟生效
	m_nImpactWrapCnt =rSour.m_nImpactWrapCnt;//叠加层数
 	for (int i = 0;i < MAX_IMAPCT_PARAM_NUM; i++)
 	{
 		m_aParams[i] = rSour.m_aParams[i];
 	}
	return true;
	__LEAVE_FUNCTION
		return false;
}
