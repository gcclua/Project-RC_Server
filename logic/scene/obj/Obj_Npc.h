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

	virtual void Tick_Moving(const TimeInfo &rTimeInfo);

	virtual bool CanBeView(Obj_Npc &rNpc);
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

	int GetNpcForceType() const;		// 获取NPC势力

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
		AI_MARCH,//行军
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
		METHOD_NORMAL=0,// 近战仇恨目标选择 模式
		METHOD_NEAREST=1, //最近距离目标
	};

	virtual bool CanAcceptThreat(void) const {return true;};
	virtual bool OnThreat(Obj_Character& rAttacker,int nIncThreatNum);
	virtual void  Tick_EnemyList(const TimeInfo& rTimeInfo);
	
	//向目标发送伤害
	virtual bool OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage);
	//接受伤害
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
public:
	bool InCombat(){return m_curAIType == AI_COMBAT;}
	void EnterMarch();
	void EnterTrace();
	bool SwitchAI(int AIType);
	void ProessTrace(Obj_Character& rUnit,float fAttackDis);//追踪
	// 在战斗状态下选择一个技能
	void SelectSkillAndTarget(int& nSelSkillId,int& nSelObjectId);
	// 在追踪状态下释放的技能
	int  SelectSkillAndTargetInTrace();
	tfloat32 GetAlertRadius(void)const{return m_fAlertRadius;}
	void SetAlertRadius(tfloat32 fAlertRadius){m_fAlertRadius =fAlertRadius;}
	void SetAttackTime(int val) { m_nAttackTime = val; }
	void SetXpSpeed(int val){m_nXpSpeed = val;}
	void SetAttackDisType(int16 val) { m_nAttackDisType = val; }
	int16  GetAttackDisType() const {return m_nAttackDisType;}
	int GetSkillStrategyId() const { return m_nSkillStrategyId; }
	void SetSkillStrategyId(int val) { m_nSkillStrategyId = val; }
	bool GetRobot(){return m_bRobot;}
	void SetRobot(bool val){m_bRobot = val;}
	//死亡
	virtual void OnDie(Obj_Character& rKiller);
	virtual void ChangeCurSelectObjId(int nId);

	// 设置移动路线
	void MoveAppend(const ScenePos &rPos);

	// 初始行军路线设置
	virtual void   SelectTargetForMarch(bool bAttack);
	virtual void   InitPassiveSkill();
	
protected:   

	//NPC 技能的使用方式
	enum 
	{
		SKILLUSE_CD =0,//冷却到了就释放
		SKILLUSE_WEIGHT,//权重控制
	};
	void Tick_AI(TimeInfo const& rTimeInfo);
	void Tick_AI_Idle(TimeInfo const& rTimeInfo);
	void Tick_AI_March(TimeInfo const& rTimeInfo);
	void Tick_AI_Combat(TimeInfo const& rTimeInfo);
	void Tick_AI_Trace(TimeInfo const& rTimeInfo);

	bool SelectCanAttackObj();
	virtual void EnterCombat(void);
	virtual void LeaveCombat(void);

	//npc 选择目标方式
	int SelectNewTarget(int SelMethod);
	int SelectMethod_Sencond();
	int SelectMethod_Rand();
	int SelectMethod_March();
	// 根据技能的目标和选择逻辑，以及距离选择
	int SelectNewSkillTarget(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx);
	

	int m_curAIType;
	tfloat32 m_fAlertRadius;//警戒范围
	int m_nLastAttackTime;//上次攻击的时间
	int m_nAttackTime;//攻击的频率
	ScenePos m_lastTracePos;//上一次追踪的位置
	float m_fTraceStopDis;//追踪停止距离
	int m_nLastTraceTime;//上次追踪时间
	int m_nTraceTime;//追踪的时间
	int16 m_nAttackDisType;//攻击距离类型 近战还是远程
	int m_nSkillStrategyId;//技能使用策略Id
	int    m_nXpSpeed; // 战意回复速度
	bool   m_bRobot;    // 是否托管，自动释放技能
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


public:
	virtual	int	GetSceneNpcID(void) const {return m_nSceneNpcID;}
	virtual	void	SetSceneNpcID(int nSceneNpcID) {m_nSceneNpcID = nSceneNpcID;}
	virtual void	SetMutexID(int nMutexID){ m_nMutexID = nMutexID;}
	virtual int	GetMutexID(){ return m_nMutexID;}

protected:

	int m_nSceneNpcID;
	int m_nMutexID;

public:
	int   GetArrangeIndex() const {return m_nArrangeIndex;}
	void  SetArrangeIndex(int val) {m_nArrangeIndex = val;}

private:
	int     m_nArrangeIndex; // 队形的位置

	bsvector<int64>  m_vecMarchTarget;

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
