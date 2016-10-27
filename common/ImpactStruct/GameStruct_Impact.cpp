#include "GameStruct_Impact.h"
#include "DBStruct/DBStruct_Impact.h"
#include "Table/Table_Impact.h"

bool ImpactStruct::SerializeToDB(DBImpactStruct& rDest)
{
	__ENTER_FUNCTION
	rDest.m_nImpactId =m_nImpactId;//BuffId
	rDest.m_nSkillId =m_nSkillId;//����ID
	rDest.m_nSenderType =m_nSenderType;//obj Type Npc ��� ��� ��ʬ���
	rDest.m_SenderGuid =m_SenderGuid;//��Һͻ����GUID
	rDest.m_nSceneClassId =m_nSceneClassId;//BUFF����ʱ�ĳ���Class ID
	rDest.m_nSceneInstanceId =m_nSceneInstanceId;//BUFF����ʱ�ĳ���ʵ�� ID
	rDest.m_nSenderObjId =m_nSenderObjId;//������objId
	rDest.m_fContinuTime =m_fContinuTime;//����ʱ��(��λ:��)
	rDest.m_nEffectTime =m_nEffectTime;//BUFF��Ч��ʱ��(��λ:��)
	rDest.m_nIntervalTime =m_nIntervalTime;//�������ʱ��(��λ:����)
	rDest.m_nIntervalElapsed =m_nIntervalElapsed;//���ŵļ��(��λ:����)
	rDest.m_nDelayTime =m_nDelayTime;//�ӳ���Ч
	rDest.m_nImpactWrapCnt =m_nImpactWrapCnt;//���Ӳ���
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
	m_nSkillId =rSour.m_nSkillId;//����ID
	m_nSenderType =rSour.m_nSenderType;//obj Type Npc ��� ��� ��ʬ���
	m_SenderGuid =rSour.m_SenderGuid;//��Һͻ����GUID
	m_nSceneClassId =rSour.m_nSceneClassId;//BUFF����ʱ�ĳ���Class ID
	m_nSceneInstanceId =rSour.m_nSceneInstanceId;//BUFF����ʱ�ĳ���ʵ�� ID
	m_nSenderObjId =rSour.m_nSenderObjId;//������objId
	m_fContinuTime =rSour.m_fContinuTime;//����ʱ��(��λ:��)
	m_nEffectTime =rSour.m_nEffectTime;//BUFF��Ч��ʱ��(��λ:��)
	m_nIntervalTime =rSour.m_nIntervalTime;//�������ʱ��(��λ:����)
	m_nIntervalElapsed =rSour.m_nIntervalElapsed;//���ŵļ��(��λ:����)
	m_nDelayTime =rSour.m_nDelayTime;//�ӳ���Ч
	m_nImpactWrapCnt =rSour.m_nImpactWrapCnt;//���Ӳ���
 	for (int i = 0;i < MAX_IMAPCT_PARAM_NUM; i++)
 	{
 		m_aParams[i] = rSour.m_aParams[i];
 	}
	return true;
	__LEAVE_FUNCTION
		return false;
}
