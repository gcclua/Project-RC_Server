/********************************************************************
	�ļ���: 	SL_EffectToSelf.h
	�ļ�·��:\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-3-15 19:09
	����˵����ʹ�ü��ܺ� ���Լ����ϼ�һ��BUFF�����ɷ�Ч����BUFF
	����˵��:
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_EFFCTTOSELF_H
#define SL_EFFCTTOSELF_H

#include "SkillBaseLogic.h"

class SL_EffectToSelf:public SkillBaseLogic
{
public:
	SL_EffectToSelf(){};
	~SL_EffectToSelf(){};

	
	//��ʼ��Ч
	virtual void StarEffect(Obj_Character& rSelf);
	//�жϼ��ܴ���
	virtual void BreakSkill(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(SL_EffectToSelf);

#endif