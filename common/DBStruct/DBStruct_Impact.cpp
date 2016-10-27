////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺15:22 2013-11-14
//             ˵������Ϸ�м򵥵Ĵ洢�ṹ
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_Impact.h"


void DBImpactStruct::CleanUp()
{
	__ENTER_FUNCTION
	m_nImpactId =invalid_id;//BuffId
	m_nSkillId =invalid_id;//����ID
	m_nSenderObjId =invalid_id;//������objId
	m_fContinuTime =0.0f;//����ʱ��
	m_nEffectTime =0;//BUFF��Ч��ʱ��
	m_nIntervalElapsed =0;//���ŵļ��
	m_nDelayTime =0;//�ӳ���Чʱ��
	m_nImpactWrapCnt =0;//���Ӳ���
	m_nIntervalTime =0;
	m_nSenderType =-1;//obj Type Npc ��� ��� ��ʬ���
	m_SenderGuid =invalid_guid64;//��Һͻ����GUID
	m_nSceneClassId =-1;//BUFF����ʱ�ĳ���Class ID
	m_nSceneInstanceId =-1;//BUFF����ʱ�ĳ���ʵ�� ID
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
	m_nSkillId =rSour.m_nSkillId;//����ID
	m_nSenderObjId =rSour.m_nSenderObjId;//������objId
	m_fContinuTime =rSour.m_fContinuTime;//����ʱ��
	m_nEffectTime =rSour.m_nEffectTime;//BUFF��Ч��ʱ��
	m_nIntervalElapsed =rSour.m_nIntervalElapsed;//���ŵļ��
	m_nDelayTime =rSour.m_nDelayTime;//�ӳ���Чʱ��
	m_nImpactWrapCnt =rSour.m_nImpactWrapCnt;//���Ӳ���
	m_nIntervalTime =rSour.m_nIntervalTime;
	m_nSenderType =rSour.m_nSenderType;//obj Type Npc ��� ��� ��ʬ���
	m_SenderGuid =rSour.m_SenderGuid;//��Һͻ����GUID
	m_nSceneClassId =rSour.m_nSceneClassId;//BUFF����ʱ�ĳ���Class ID
	m_nSceneInstanceId =rSour.m_nSceneInstanceId;//BUFF����ʱ�ĳ���ʵ�� ID
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
