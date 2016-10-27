/********************************************************************
	文件名: 	SL_ShunFa.h
	文件路径:	\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-3-3 9:55
	功能说明：标准瞬发技逻辑
	参数说明:
	参数1：技能目标上限(-1 表示无上限需求)
	修改记录:

*********************************************************************/
#ifndef SL_SHUFA_H
#define SL_SHUFA_H
#include "SkillBaseLogic.h"

class SL_ShunFa:public SkillBaseLogic
{
public:
	SL_ShunFa (){};
	~SL_ShunFa(){};
public:
	enum 
	{
		MAXTARGETNUM =0,
	};
	//获取技能目标上限
	virtual int GetMaxTargetNum(void);//-1 表示无上限需求
private:
};
POOLDEF_DECL(SL_ShunFa);
#endif