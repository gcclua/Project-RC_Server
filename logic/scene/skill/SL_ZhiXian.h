/********************************************************************
	文件名: 	SL_ZhiXian.h
	文件路径:\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-3-3 10:19
	功能说明：直线攻击技能 有几率刺穿一条直线上的敌人
	参数说明:
		参数1:打出直线攻击的权重(20表示 20%)
		参数2:四边形的宽度范围
		参数3:四边形的长度范围
		参数4:最大目标上限
	修改记录:

*********************************************************************/
#ifndef SL_ZHIXIAN_H
#define SL_ZHIXIAN_H
#include "SkillBaseLogic.h"

class SL_ZhiXian:public SkillBaseLogic
{
public:
	SL_ZhiXian (){};
	~SL_ZhiXian(){};
	enum 
	{
		ZHIXIANRATE =0,//直线的宽度
		ZHIXIANSCOPE,//四边形的宽度范围
		ZHIXIANLENGTH,//四边形的长度范围
		MAXTARGETNUM,//最大目标上限
	};
	//开始生效
	virtual void StarEffect(Obj_Character& rSelf);
private:
};
POOLDEF_DECL(SL_ZhiXian);
#endif