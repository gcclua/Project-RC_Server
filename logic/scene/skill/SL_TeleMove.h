/********************************************************************
	�ļ���: 	SL_TeleMove.h
	�ļ�·��:	\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-5-9 15:38
	����˵����˲��
	����˵��:
		����1��˲�ƾ���
		����2��˲��ʱ��
		����3��ƫ�ƽǶ�ֵ
		����4:��󹥻�Ŀ�꣨-1��ʾ����󹥻�Ŀ������
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_TELEMOVE_H
#define SL_TELEMOVE_H
#include "SkillBaseLogic.h"

class SL_TeleMove:public SkillBaseLogic
{
public:
	SL_TeleMove ();
	~SL_TeleMove(){};
	enum 
	{
		DISTANCE =0,//˲�ƾ���
		TIME =1,//˲��ʱ��
		ANGLE =2,//ƫ�ƽǶ�ֵ
		MAXTARGETNUM =3,//��󹥻�Ŀ�꣨-1��ʾ����󹥻�Ŀ������
	};
	virtual void OnActivate(Obj_Character& rSelf);
	//��ʼ��Ч
	virtual void StarEffect(Obj_Character& rSelf);
	//��ȡ����Ŀ������
	virtual int GetMaxTargetNum(void);//-1 ��ʾ����������
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix);
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
private:
	int m_nNeedIncSpeed;
};
POOLDEF_DECL(SL_TeleMove);
#endif