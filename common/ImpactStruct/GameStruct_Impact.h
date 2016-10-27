/********************************************************************************
 *	�ļ�����	GameStruct_Impact.h
 *	ȫ·����	\Server\Common\ImpactStruct\GameStruct_Impact.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-1-8
 *
 *	����˵����BUFF������ݽṹ
 *	�޸ļ�¼��
*********************************************************************************/

#ifndef GAMESTRUCT_IMPACT_H
#define GAMESTRUCT_IMPACT_H

#include "Base.h"
#include "GameDefine_Impact.h"

struct  DBImpactStruct;
class Table_Impact;

struct ImpactStruct
{
public:
	enum 
	{
		MAX_IMAPCT_PARAM_NUM =8,
		MAX_WRAPCNT =256,
	};
	ImpactStruct()
	{
		CleanUp();
	}
	void CleanUp()
	{
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
		m_pImpactDataInfo =null_ptr;
		for (int i=0;i<MAX_IMAPCT_PARAM_NUM;i++)
		{
			m_aParams[i] =0;
		}
	}
	bool IsVaild() const {return (m_pImpactDataInfo !=null_ptr);};
	int GetParamByIndex(int nIndex)
	{
		if (nIndex<0 || nIndex>=MAX_IMAPCT_PARAM_NUM)
		{
			return invalid_id;
		}
		return m_aParams[nIndex];
	}

	void SetParamByIndex(int nIndex,int nValue)
	{
		if (nIndex<0 || nIndex>=MAX_IMAPCT_PARAM_NUM)
		{
			return;
		}
		m_aParams[nIndex] =nValue;
	}
public:
	bool SerializeToDB(DBImpactStruct& rDest);//���ݿ������洢�ṹ��
	bool SerializeFromDB(const DBImpactStruct& rSour);//�洢�ṹ�����ݿ���
public:
	int m_nImpactId;//BuffId
	int m_nSkillId;//����ID
	int m_nSenderType;//obj Type Npc ��� ��� ��ʬ���
	int64 m_SenderGuid;//��Һͻ����GUID
	int m_nSceneClassId;//BUFF����ʱ�ĳ���Class ID
	int m_nSceneInstanceId;//BUFF����ʱ�ĳ���ʵ�� ID
	int m_nSenderObjId;//������objId
	float m_fContinuTime;//����ʱ��(��λ:��)
	time_t m_nEffectTime;//BUFF��Ч��ʱ��(��λ:��)
	int m_nIntervalTime;//�������ʱ��(��λ:����)
	int m_nIntervalElapsed;//���ŵļ��(��λ:����)
	int m_nDelayTime;//�ӳ���Ч
	uint8 m_nImpactWrapCnt;//���Ӳ���
	Table_Impact const* m_pImpactDataInfo;
private:
	bsarray<int, MAX_IMAPCT_PARAM_NUM> m_aParams;
};


#endif