/********************************************************************
	文件名: 	SL_TeleMove.h
	文件路径:	\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-5-9 15:38
	功能说明：瞬移
	参数说明:
		参数1：瞬移距离
		参数2：瞬移时间
		参数3：偏移角度值
		参数4:最大攻击目标（-1表示无最大攻击目标需求）
	修改记录:

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
		DISTANCE =0,//瞬移距离
		TIME =1,//瞬移时间
		ANGLE =2,//偏移角度值
		MAXTARGETNUM =3,//最大攻击目标（-1表示无最大攻击目标需求）
	};
	virtual void OnActivate(Obj_Character& rSelf);
	//开始生效
	virtual void StarEffect(Obj_Character& rSelf);
	//获取技能目标上限
	virtual int GetMaxTargetNum(void);//-1 表示无上限需求
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix);
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
private:
	int m_nNeedIncSpeed;
};
POOLDEF_DECL(SL_TeleMove);
#endif