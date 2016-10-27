/********************************************************************
	文件名: 	SL_ChongFeng.h
	文件路径:	\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-3-3 10:15
	功能说明：冲锋技能
	参数说明:
		参数1：冲锋速度
		参数2：冲锋停止的距离
	修改记录:

*********************************************************************/
#ifndef SL_CHONGFENG_H
#define SL_CHONGFENG_H
#include "SkillBaseLogic.h"

class SL_ChongFeng:public SkillBaseLogic
{
public:
	SL_ChongFeng();
	~SL_ChongFeng(){};
	enum 
	{
		SPEED =0,//参数1:冲锋的速度
		STOPDIS =1,//参数2：冲锋停止的距离
	};
	//技能激活
	virtual void OnActivate(Obj_Character& rSelf);
	//技能属性修正
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix);
	//技能结束
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
private:
	tint32 m_nNeedIncSpeed;
private:

};
POOLDEF_DECL(SL_ChongFeng);
#endif 