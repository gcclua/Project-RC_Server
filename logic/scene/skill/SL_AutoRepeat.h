/********************************************************************************
 *	�ļ�����	SL_AutoRepeat.h
 *	ȫ·����	\Sever\Skill\SL_AutoRepeat.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-1-12
 *
 *	����˵�����Զ��������߼�
 *	�޸ļ�¼��
*********************************************************************************/
#ifndef SL_AUTOREPEAT_H
#define SL_AUTOREPEAT_H

#include "SkillBaseLogic.h"

class SL_AutoRepeat:public SkillBaseLogic
{
public:
	SL_AutoRepeat (){};
	~SL_AutoRepeat(){};

	
	//��ʼ��Ч
	virtual void StarEffect(Obj_Character& rSelf);
	//�жϼ��ܴ���
	virtual void BreakSkill(Obj_Character& rSelf);
	//���� ���ܵ�ʱ�����Ч
	virtual bool Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo);
	
	//���ܽ�������
//	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
	//bool UseNextSkill(Obj_Character& rSelf,int nNextSkillId);
private:

};
POOLDEF_DECL(SL_AutoRepeat);

#endif