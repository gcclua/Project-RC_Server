////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：15:22 2013-11-14
//             说明：游戏中简单的存储结构
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_Impact.h"


void DBImpactStruct::CleanUp()
{
	__ENTER_FUNCTION
	m_nImpactId =invalid_id;//BuffId
	m_nSkillId =invalid_id;//技能ID
	m_nSenderObjId =invalid_id;//发送者objId
	m_fContinuTime =0.0f;//持续时间
	m_nEffectTime =0;//BUFF生效的时间
	m_nIntervalElapsed =0;//流逝的间隔
	m_nDelayTime =0;//延迟生效时间
	m_nImpactWrapCnt =0;//叠加层数
	m_nIntervalTime =0;
	m_nSenderType =-1;//obj Type Npc 玩家 伙伴 僵尸玩家
	m_SenderGuid =invalid_guid64;//玩家和伙伴有GUID
	m_nSceneClassId =-1;//BUFF发送时的场景Class ID
	m_nSceneInstanceId =-1;//BUFF发送时的场景实例 ID
	for (int i = 0; i < ImpactStruct::MAX_IMAPCT_PARAM_NUM; i++)
	{
		m_aParams[i] = 0;
	}
	__LEAVE_FUNCTION
}

void DBImpactStruct::CopyFrom(const DBImpactStruct& rSour)
{
	__ENTER_FUNCTION
	m_nImpactId =rSour.m_nImpactId;//BuffId
	m_nSkillId =rSour.m_nSkillId;//技能ID
	m_nSenderObjId =rSour.m_nSenderObjId;//发送者objId
	m_fContinuTime =rSour.m_fContinuTime;//持续时间
	m_nEffectTime =rSour.m_nEffectTime;//BUFF生效的时间
	m_nIntervalElapsed =rSour.m_nIntervalElapsed;//流逝的间隔
	m_nDelayTime =rSour.m_nDelayTime;//延迟生效时间
	m_nImpactWrapCnt =rSour.m_nImpactWrapCnt;//叠加层数
	m_nIntervalTime =rSour.m_nIntervalTime;
	m_nSenderType =rSour.m_nSenderType;//obj Type Npc 玩家 伙伴 僵尸玩家
	m_SenderGuid =rSour.m_SenderGuid;//玩家和伙伴有GUID
	m_nSceneClassId =rSour.m_nSceneClassId;//BUFF发送时的场景Class ID
	m_nSceneInstanceId =rSour.m_nSceneInstanceId;//BUFF发送时的场景实例 ID
	for (int i = 0; i < ImpactStruct::MAX_IMAPCT_PARAM_NUM; i++)
	{
		m_aParams[i] = rSour.m_aParams[i];
	}
	__LEAVE_FUNCTION
}

void DBImpact::CleanUp(void)
{
	__ENTER_FUNCTION
	for (int i = 0; i < MAX_BUFF_SIZE; i++)
	{
		m_buffList[i].CleanUp();
	}	 
	__LEAVE_FUNCTION
}

void DBImpact::InitAsCreateNewChar()
{
	__ENTER_FUNCTION
	 CleanUp();
	__LEAVE_FUNCTION
}

void DBImpact::CopyFrom(const DBImpact& rSour)
{
	__ENTER_FUNCTION
	for (int i = 0; i < MAX_BUFF_SIZE; i++)
	{
		m_buffList[i].CopyFrom(rSour.m_buffList[i]);
	}	
	__LEAVE_FUNCTION
}
