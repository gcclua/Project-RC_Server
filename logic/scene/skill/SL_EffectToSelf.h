/********************************************************************
	文件名: 	SL_EffectToSelf.h
	文件路径:\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-3-15 19:09
	功能说明：使用技能后 往自己身上加一个BUFF用来派发效果子BUFF
	参数说明:
	修改记录:

*********************************************************************/
#ifndef SL_EFFCTTOSELF_H
#define SL_EFFCTTOSELF_H

#include "SkillBaseLogic.h"

class SL_EffectToSelf:public SkillBaseLogic
{
public:
	SL_EffectToSelf(){};
	~SL_EffectToSelf(){};

	
	//开始生效
	virtual void StarEffect(Obj_Character& rSelf);
	//中断技能处理
	virtual void BreakSkill(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(SL_EffectToSelf);

#endif