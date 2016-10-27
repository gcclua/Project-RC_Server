/********************************************************************
	文件名: 	SL_Snare.h
	文件路径:	\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-5-9 15:52
	功能说明：陷阱技能(在释放者 前后左右个释放一个技能)
	参数说明:
		参数1:陷阱ID
		参数2:陷阱位置的选取方式(1 释放者脚下 2当前选中目标的脚下)
		参数3:技能停止时是否删除陷阱(0 否 1是)
	修改记录:

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
		SNAREID =0,//陷阱ID 
		SNAREPOSTYPE,//陷阱位置的选取方式
		SNAREDELTYPE,//技能停止时是否删除陷阱
	};
	enum 
	{
		POS_SELF =1,//陷阱在释放者脚下
		POS_TARGET =2,//陷阱在选择目标脚下
	};
	//开始生效
	virtual void StarEffect(Obj_Character& rSelf);
	//技能结束处理
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
private:
	tint32 m_SnareObjId;
};
POOLDEF_DECL(SL_Snare);
#endif