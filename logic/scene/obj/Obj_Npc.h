#ifndef _OBJ_NPC_H_
#define _OBJ_NPC_H_

#include "Obj_Character.h"
#include "Table/Table_NpcSkillStrategy.h"
#include "Table/Table_NpcOptionalSkill.h"

class Obj_Npc : public Obj_Character
{
public:
	Obj_Npc(void);
	virtual ~Obj_Npc(void);

public:
	virtual int GetObjType(void) const {return ObjType::NPC;}

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

	virtual bool CanBeView(Obj_March &rUser);
private:
	void BeginDeadStatus_DeadBody(void);
	void BeginDeadStatus_Disappear(void);
	void Tick_DeadStatus(const TimeInfo &rTimeInfo);

public:
	void SetCorpseTime(tint32 val) { m_nCorpseTime = val; }


private:
	bool m_bDeadBody;
	int m_nDeadBodyTime;
	int m_nCorpseTime;//尸体停留时间
	//////////////////////////////////////////////////////////////////////////
// 复活 End
//////////////////////////////////////////////////////////////////////////

public:
	const ScenePos & GetRelivePos(void) const { return m_RelivePos; }
	void SetRelivePos(const ScenePos &val) { m_RelivePos = val; }

private:
	ScenePos m_RelivePos;
	
//////////////////////////////////////////////////////////////////////////
// 属性 Begin
//////////////////////////////////////////////////////////////////////////
public:
	virtual void CalculateInitalAttr(void);
	virtual void CalculateFinalyAttr(void);
	//获取最终战斗属性数值
	virtual int GetCombatAttrByID(int AttrId);
	int GetNpcType() const { return m_nNpcType; }
	void SetNpcType(int val) { m_nNpcType = val; }

	int GetNpcForceType(Obj_Character &rObj) const;		// 获取NPC势力
protected:
	int m_nNpcType;
	//////////////////////////////////////////////////////////////////////////
// 属性 end
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// AI相关Begin
//////////////////////////////////////////////////////////////////////////
public:
	//NPC的AI行为 互斥的
	enum 
	{
		AI_IDLE =0,//待机
		AI_COMBAT,//战斗
		AI_PATROL,//巡逻
		AI_FOLLOW,//跟随
		AI_TRACE,//追击
	};
	enum 
	{
		RANDMOVEINTERVALTIME =5000,//随机移动间隔时间 5s
		RANDMOVERATE =5,//随机移动的概率
	};

	//仇恨
	enum 
	{
		METHOD_NORMAL=0,//正常仇恨目标选择 模式
		METHOD_SECOND,//第二仇恨目标选择 模式
		METHOD_RAND,//随机仇恨目标选择 模式
		METHOD_FURTHEST,//最远仇恨目标选择 模式
		METHOD_CLEAR,//仇恨清空 模式
		METHOD_IMPACT,//有特定BUFF的目标
	};
	enum 
	{
		SWITCHTARGETTIME =5000,//切换目标的间隔时间 单位 毫秒
	};
	
	void ResetSwitchTargetCooldown(void){m_nSwitchTargetCooldown =Obj_Npc::SWITCHTARGETTIME;}
	virtual bool CanAcceptThreat(void) const {return true;};
	virtual bool OnThreat(Obj_Character& rAttacker,int nIncThreatNum);
	virtual void  Tick_EnemyList(const TimeInfo& rTimeInfo);
	
	//向目标发送伤害
	virtual bool OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage);
	//接受伤害
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
public:
	bool SwitchAI(int AIType);
	void ProessRandMove(void);//随机移动
	void ProessTrace(Obj_Character& rUnit,float fAttackDis);//追踪
	int SelectSkillAndTarget(void);
	float GetPathRadius(void)const{return m_fPathRadius;}
	void SetPathRadius(float fRadius){m_fPathRadius =fRadius;}
	float GetAlertRadius(void)const{return m_fAlertRadius;}
	void SetAlertRadius(float fAlertRadius){m_fAlertRadius =fAlertRadius;}
	bool IsCanRandMove(void) const{return m_bIsRandMove;}
	void SetRandMove(bool bIsRandMove){m_bIsRandMove =bIsRandMove;}
	void SetRandMoveDis(float fRandMoveDis){m_fRandMoveDis =fRandMoveDis;}
	void SetAttackTime(int val) { m_nAttackTime = val; }
	int 	GetFollowTargetObjId() const { return m_FollowTargetObjId; }
	void 	SetFollowTargetObjId(int val) { m_FollowTargetObjId = val; }
	void SetAttackDisType(int16 val) { m_nAttackDisType = val; }
	int GetSkillStrategyId() const { return m_nSkillStrategyId; }
	void SetSkillStrategyId(int val) { m_nSkillStrategyId = val; }
	//死亡
	virtual void OnDie(Obj_Character& rKiller);
	virtual bool IsCloseCombat(); //是否是近战
	virtual bool IsLongCombat();//是否是远程
	virtual bool IsPysicalAttack();//物攻 
	virtual bool IsMagicalAttack();//魔攻
	virtual void ChangeCurSelectObjId(int nId);
	
protected:   
	struct CanUseSkillSkillInfo //NPC可释放的 可选技能的数据结构
	{
	public:
		CanUseSkillSkillInfo(){CleanUp();}
		int m_nSkillId;//技能ID
		int m_SeleTargetLogic;//选择目标逻辑
		int m_SelectParam1;//逻辑参数1
		int m_nSelectParam2;//逻辑参数2
		int m_nUseType;//技能使用方式
		int m_nWeight;//技能权重
		int m_nActivateLogic;//技能激活逻辑
		int m_nActivateParam1;//逻辑参数1
		int m_nActivateParam2;//逻辑参数2
		int m_nSeleObjId;//技能选择的目标
		int m_nPriority;//技能选择优先级
		void CleanUp()
		{
			m_nSkillId =-1;
			m_SeleTargetLogic =-1;
			m_SelectParam1 =-1;
			m_nSelectParam2 =-1;
			m_nUseType =-1;
			m_nWeight =-1;
			m_nActivateLogic =-1;
			m_nActivateParam1 =-1;
			m_nActivateParam2 =-1;
			m_nSeleObjId =-1;
			m_nPriority =-1;
		}
	};
	//NPC 技能激活逻辑
	enum 
	{
		SKILL_ATTACKTIME =0,//攻击频率限制
		SKILL_HPLESSTHEN, //血量少于某个百分比
		SKILL_TARGETHPLESSTHEN, //目标血量少于某个百分比
		SKILL_HAVEIMPACT, //有某个特定的BUFF
		SKILL_TARGETHAVEIMPACT,//目标有某个特定的BUFF
		SKILL_COMBATTIME,//战斗时长 单位毫秒
		SKILL_SCRIPTCHECK,//副本检测
		SKILL_NOCHECK , //无限制条件
	};
	//NPC 技能的使用方式
	enum 
	{
		SKILLUSE_CD =0,//冷却到了就释放
		SKILLUSE_WEIGHT,//权重控制
	};
	void Tick_AI(TimeInfo const& rTimeInfo);
	void Tick_AI_Idle(TimeInfo const& rTimeInfo);
	void Tick_AI_Patrol(TimeInfo const& rTimeInfo);
	void Tick_AI_Combat(TimeInfo const& rTimeInfo);
	void Tick_AI_Follow(TimeInfo const& rTimeInfo);
	void Tick_AI_Trace(TimeInfo const& rTimeInfo);

	void FindUserTarget();

	bool SelectCanAttackObj();
	virtual void EnterCombat(void);
	virtual void LeaveCombat(void);
	//npc 选择目标方式
	int SelectNewTarget(int SelMethod,int nParam1, int nParam2);
	int SelectMethod_Normal(int nParam1 =-1, int nParam2 =-1);
	int SelectMethod_Sencond(int nParam1 =-1, int nParam2 =-1);
	int SelectMethod_Rand(int nParam1 =-1, int nParam2 =-1);
	int SelectMethod_Furthest(int nParam1 =-1, int nParam2 =-1);
	int SelectMethod_Clear(int nParam1 =-1, int nParam2 =-1);
	int SelectMethod_Impact(int nParam1 =-1, int nParam2 =-1);
	bool   IsCanSelectSkill_AttackTime();
	bool   IsCanSelectSkill_HpLessThen(Table_NpcOptionalSkill const& rNpcOptionalSkill);
	bool   IsCanSelectSkill_TargetHpLessThen(Table_NpcOptionalSkill const& rNpcOptionalSkill,int TargetId);
	bool   IsCanSelectSkill_HaveImpact(Table_NpcOptionalSkill const& rNpcOptionalSkill);
	bool   IsCanSelectSkill_TargetHaveImpact(Table_NpcOptionalSkill const& rNpcOptionalSkill,int TargetId);
	bool   IsCanSelectSkill_CombatTime(Table_NpcOptionalSkill const& rNpcOptionalSkill);
	bool   IsCanSelectSkill_ScriptCheck(Table_NpcOptionalSkill const& rNpcOptionalSkill,int const nCheckSkillId);
	bool   Script_CheckUseSkill(int nSkillId);
	int m_curAIType;
	int m_nLastRandMoveTime;//上次随机移动的时间 单位：毫秒
	int m_nSwitchTargetCooldown;
	float m_fPathRadius;//脱战范围
	float m_fAlertRadius;//警戒范围
	bool	 m_bIsRandMove;//是否随机游荡
	float m_fRandMoveDis;//随机游荡范围
	int m_FollowTargetObjId;//跟随目标ObjId
	int m_nLastAttackTime;//上次攻击的时间
	int m_nAttackTime;//攻击的频率
	ScenePos m_lastTracePos;//上一次追踪的位置
	float m_fTraceStopDis;//追踪停止距离
	int m_nLastTraceTime;//上次追踪时间
	int m_nTraceTime;//追踪的时间
	int16 m_nAttackDisType;//攻击距离类型 近战还是远程
	int m_nSkillStrategyId;//技能使用策略Id
	uint32 m_nEnterCombatTime;//进入战斗的时间
	bool	m_bIsJustEnterCombat;//是否刚刚进入战斗
	//////////////////////////////////////////////////////////////////////////
//AI相关End
//////////////////////////////////////////////////////////////////////////

	//模仿人物模型NPC
public:
	void		SetModelVisualID(int nModeId){m_nModelVisualID = nModeId;}
	int		GetModelVisualID()const{return m_nModelVisualID;}
	void		SetWeaponDataID(int nWeaponDataID){m_nWeaponDataID = nWeaponDataID;}
	int		GetWeaponDataID()const{return m_nWeaponDataID;}
	void		SetKylinValue(int nKylinValue){m_nKylinValue = nKylinValue;}
	int		GetKylinValue()const{return m_nKylinValue;}
private:
	int m_nModelVisualID;		// 模型ID
	int m_nWeaponDataID;			// 武器ID
	int m_nKylinValue;			// 战力值（假的）
//////////////////////////////////////////////////////////////////////////
//巡逻相关
public:
	enum 
	{
		PATROL_OVER			= 0,//直接结束
		PATROL_OVER_DELETE	= -1,//结束后自杀
	};
	enum 
	{
		PATROL_EVENT_SLEEP	= 1,//停顿
		PATROL_EVENT_BUFF	= 2,//给自己加buff
	};
	enum  //楼上功能用到的参数位，范围[0,2]
	{
		PATROL_PARAM_SLEEPTIME	= 0,
		PATROL_PARAM_BUFFID		= 0,
	};
private:
	//巡逻路线索引
	int m_nCurPatrolStep;
	//巡逻用计时
	int m_nPatrolCountDown;
private:
	bool	IsNeedPatrol();
public:
	void	StartPatrol(Obj_Character& rChar, int nStartID);
//巡逻结束
//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 自动回复Start
public:
	void Tick_AutoCure(TimeInfo const& rTimeInfo);
private:
	int m_nCureTime;
	int m_nIncHp;
	int m_nIncMp;
	// 自动回复End
	//////////////////////////////////////////////////////////////////////////

public:
	virtual	int	GetSceneNpcID(void) const {return m_nSceneNpcID;}
	virtual	void	SetSceneNpcID(int nSceneNpcID) {m_nSceneNpcID = nSceneNpcID;}
	virtual void	SetMutexID(int nMutexID){ m_nMutexID = nMutexID;}
	virtual int	GetMutexID(){ return m_nMutexID;}

protected:

	int m_nSceneNpcID;
	int m_nMutexID;

};

POOLDEF_DECL(Obj_Npc);

typedef GeneralObjRefCont<Obj_Npc, 256> NpcRefCont;

struct SceneNpcIDAndMutxID
{
	SceneNpcIDAndMutxID(void)
	{
		m_nSceneNpcID = invalid_id;
		m_nMutexID = invalid_id;
	}
	SceneNpcIDAndMutxID(int nSceneNpcID, int nMutexID)
	{
		m_nSceneNpcID = nSceneNpcID;
		m_nMutexID = nMutexID;
	}
	int	m_nSceneNpcID;
	int	m_nMutexID;
};

typedef bsvector<int> SceneNpcIDVector;
typedef bsvector<SceneNpcIDAndMutxID> SceneNpcIDAndMutexIDVector;

#endif
