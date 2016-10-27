////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺13:34 2014-3-3
//             ˵����Ч�����ݴ洢
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