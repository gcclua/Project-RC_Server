/********************************************************************************
 *	文件名：	SkillBaseLogic.h
 *	全路径：	\Sever\Skill\SkillBaseLogic.h
 *	创建人：	zz
 *	创建时间：2013-12-24
 *
 *	功能说明：服务器技能基类
 *	修改记录：
*********************************************************************************/
#ifndef SKILLBASELOGIC_H
#define SKILLBASELOGIC_H

#include "Base.h"
#include "skill/GameStruct_Skill.h"

class Obj_Character;
struct CombatAttr_Refix;
class TimeInfo;


class SkillBaseLogic
{
public:
	enum SKILLLOGIC
	{
		SL_SHUFA                = 0,//标准瞬发技逻辑
		SL_CHONGFENG            = 3,//冲锋技能
		SL_ZHIXIAN              = 5,//直线攻击技能
		SL_EFFECTTOSELF         = 8,//使用技能后 往自己身上加一个BUFF用来派发效果子BUFF
		SL_SNARE                = 11,//陷阱技能逻辑
		SL_TELEMOVE             = 12,//瞬移技能逻辑
		SL_MAXNUM,
	};
public:
	SkillBaseLogic();
	~SkillBaseLogic(){};
public: 
	//	virtual void MarkModifiedCombatAttrDirty(Obj_Character& rSelf)const{};
		
	//	virtual bool OnHitTarget(Obj_Character& rSelf,Obj_Character& rUnit);
	//	virtual bool OnDisturb(Obj_Character &rSelf ) ;
	//使用技能激活前的检测 给每个技能逻辑一次单独检测的机会
	virtual void OnBeforeActivate(Obj_Character& rSelf){};
	//激活技能
	virtual void OnActivate(Obj_Character& rSelf);
	//心跳 技能到时间后生效
	virtual bool Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo);
	//技能准备生效
	virtual void OnTakeEffect(Obj_Character& rSelf);
	//生效前的处理
	virtual bool OnBeforeEffect(Obj_Character& rSelf);
	//开始生效
	virtual void StarEffect(Obj_Character& rSelf);
	//技能对目标生效
	virtual void OnEffectOnUnit(Obj_Character& rSelf, Obj_Character& rUnit);
	//技能结束处理
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
	//中断技能处理
	virtual void BreakSkill(Obj_Character& rSelf);
	//离开场景前的处理
	virtual void BeforLevelScene(Obj_Character& rSelf);
	//技能对战斗属性的修正
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix){} ;
	//技能无敌
	virtual bool IsSkillGod(void){return false;};
	//受到攻击
	virtual void OnBeAttacked(Obj_Character& rSelf);
	//获取技能目标上限
	virtual int GetMaxTargetNum(void){return -1;};//-1 表示无上限需求
public:
	bool IsValid();
	bool IsEffect(){return m_bIsEffect;}
	void InitCurSkillInfo(SkillInfo_T& skillInfo){m_CurSkillInfo =skillInfo;}
	SkillInfo_T& GetCurSkillInfo(void){return m_CurSkillInfo;}
	const SkillInfo_T& GetCurSkillInfo(void) const{return m_CurSkillInfo;}
	void SwitchNextSkill(Obj_Character& rSelf,int nNextSkillId);
	//扫描
	void ScanEffectTargetList(Obj_Character& rSelf);
protected:
	SkillInfo_T m_CurSkillInfo;
	bool m_bIsActive;//是否开始激活
	bool m_bIsEffect;//是否开始生效
};
POOLDEF_DECL(SkillBaseLogic);
#endif

