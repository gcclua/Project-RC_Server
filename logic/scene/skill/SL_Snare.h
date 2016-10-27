/********************************************************************
	�ļ���: 	SL_Snare.h
	�ļ�·��:	\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-5-9 15:52
	����˵�������弼��(���ͷ��� ǰ�����Ҹ��ͷ�һ������)
	����˵��:
		����1:����ID
		����2:����λ�õ�ѡȡ��ʽ(1 �ͷ��߽��� 2��ǰѡ��Ŀ��Ľ���)
		����3:����ֹͣʱ�Ƿ�ɾ������(0 �� 1��)
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_SNARE_H
#define SL_SNARE_H
#include "SkillBaseLogic.h"

class SL_Snare:public SkillBaseLogic
{
public:
	SL_Snare ();
	~SL_Snare(){};
	enum 
	{
		SNAREID =0,//����ID 
		SNAREPOSTYPE,//����λ�õ�ѡȡ��ʽ
		SNAREDELTYPE,//����ֹͣʱ�Ƿ�ɾ������
	};
	enum 
	{
		POS_SELF =1,//�������ͷ��߽���
		POS_TARGET =2,//������ѡ��Ŀ�����
	};
	//��ʼ��Ч
	virtual void StarEffect(Obj_Character& rSelf);
	//���ܽ�������
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
private:
	tint32 m_SnareObjId;
};
POOLDEF_DECL(SL_Snare);
#endif