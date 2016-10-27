/********************************************************************************
 *	文件名：	SL_AutoRepeat.h
 *	全路径：	\Sever\Skill\SL_AutoRepeat.h
 *	创建人：	zz
 *	创建时间：2013-1-12
 *
 *	功能说明：自动连续技逻辑
 *	修改记录：
*********************************************************************************/
#ifndef SL_AUTOREPEAT_H
#define SL_AUTOREPEAT_H

#include "SkillBaseLogic.h"

class SL_AutoRepeat:public SkillBaseLogic
{
public:
	SL_AutoRepeat (){};
	~SL_AutoRepeat(){};

	
	//开始生效
	virtual void StarEffect(Obj_Character& rSelf);
	//中断技能处理
	virtual void BreakSkill(Obj_Character& rSelf);
	//心跳 技能到时间后生效
	virtual bool Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo);
	
	//技能结束处理
//	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
	//bool UseNextSkill(Obj_Character& rSelf,int nNextSkillId);
private:

};
POOLDEF_DECL(SL_AutoRepeat);

#endif