/********************************************************************************
 *	文件名：  Obj_ZombieUser.h
 *	全路径：  E:\Code\Server\Server\Server\Server\Scene\Obj\Obj_ZombieUser.h
 *	创建人：  mwh
 *	创建时间：2014/03/05
 *
 *	功能说明：托管的僵尸玩家
 *	修改记录：
*********************************************************************************/

#ifndef __OBJ_ZOMBIE_USER_H__
#define __OBJ_ZOMBIE_USER_H__

#include "Obj_Character.h"
#include "Scene/AI/AIController.h"

class Obj_User;
typedef boost::shared_ptr<Obj_User> Obj_UserPtr;

class Obj_ZombieUser : public Obj_Character
{
	friend class AIController;
public:
	Obj_ZombieUser( );
	virtual ~Obj_ZombieUser( );
public:
	virtual void OnEnterScene(void);
public:
	//...
	virtual void SendBaseAttr(Obj_User &rUser);
	virtual tint32 GetObjType(void) const {return ObjType::ZOMBIEUSER;}

	//物攻
	virtual bool IsPysicalAttack();
	//魔攻
	virtual bool IsMagicalAttack();
	//近战
	virtual bool IsCloseCombat();
	//远程
	virtual bool IsLongCombat();

	// 死亡
	virtual void OnDie(Obj_Character& rKiller);
	// 接受伤害
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
	
	// 计算战斗属性
	virtual void CalculateFinalyAttr(void);
	// 计算初始属性
	virtual void CalculateInitalAttr(void);
	// 武道巅峰僵尸玩家属性修正
	virtual void CalculateZombieUserRefix(void);
	// 获取最终战斗属性数值
	virtual tint32 GetCombatAttrByID(tint32 AttrId);
	virtual void MarkZombieUserCalcDirty(void)
	{
		m_ZombieUserCombatRefix.MarkAllCalculationDirtyFlag();
	}

	// 阵营
	virtual tint32 GetRelationByForceType(Obj_Character& rUnit);

	virtual bool CanAcceptThreat(void) const {return true;};
	virtual bool OnThreat(Obj_Character& rAttacker,tint32 nIncThreatNum);
	
public:
	tint32 GetProfession( ) const { return GetMemberBase().GetProfession(); }
private:
	tint32 GetInitialCombatAttrTableIndex(tint32 nProfessoin,tint32 nLev) const;
private:
	CombatAttr_Refix m_ZombieUserCombatRefix;
public:
	//--------------------------------------------------------------------------
	// 初始化
	//--------------------------------------------------------------------------
	void					Init( const ChallRankMember& rMember, tfloat32 fPropertyPer = 1.0f, tint32 nCase = 0, tint32 nCreatorProfession = -1 );
	void					Init( const ChallRankMember& rMember, const ZombieAIConfig& za, tint32 nIndex, tfloat32 fPropertyPer = 1.0f);
	void					InitSkillDbg( );

	// 初始化为技能的召唤物
	void InitAsSkillSummoned(const ChallRankMember& rMember, tint32 nLifeMillSeconds, tfloat32 fAttackFactor, tfloat32 fDefendFactor);

	void InitLimitSkills(tint32 nSkillNum);
	//--------------------------------------------------------------------------
	// 更新
	//--------------------------------------------------------------------------
	
	void					SetAIStop( bool stop ) { m_bStopAI = stop; }
	

	void					SetAutoReviveable(bool b) { m_bCanAutoRevive = b; }

	void					CallFellow( );

	void					AddTitle(tint32 titleID);

	tint32					SelectSkill();
	AIController&			GetAIController( ) { return m_AIController; }

private:
	//--------------------------------------------------------------------------
	// 初始化
	//--------------------------------------------------------------------------
	void					InitAI( );
	void					InitAttr( );

	//--------------------------------------------------------------------------
	// 心跳
	//------------------------------------------------------------------------
	virtual void Tick(const TimeInfo &rTimeInfo);
	void TickAI( const TimeInfo &rTimeInfo );
	void Tick_AliveStatus(const TimeInfo &rTimeInfo);
	void Tick_DeadStatus(const TimeInfo& rTimeInfo);
	
	ChallMemberBase& GetMemberBase( ) { return m_MemberBase; }
	ChallMemberAttr& GetMemberAttr( ) { return m_MemberAttr; }
	ChallMemberFellow& GetMemberFellow( ) { return m_MemberFellow; }

	const ChallMemberBase& GetMemberBase( ) const  { return m_MemberBase; }
	const ChallMemberAttr& GetMemberAttr( ) const  { return m_MemberAttr; }
	const ChallMemberFellow& GetMemberFellow( ) const  { return m_MemberFellow; }
private:
	void AutoRevive( );
private:
	tfloat32 m_fPropertyPer;
	tint32 m_nChallengeCase; // 三分校场匹配模式(用来计算属性系数)
	tint32 m_nCreatorProfession; // 创建者的职业,,例如,我是梦舞,我在三分校场打飞云,,创建者职业就是梦舞
	ZombieAIConfig m_AIProto;

	ChallMemberBase m_MemberBase;
	ChallMemberAttr m_MemberAttr;
	ChallMemberFellow m_MemberFellow;

	AIController m_AIController;
	bool m_bStopAI;

	bool m_bCanAutoRevive; // 是否可以自动复活
	tint32 m_nAutoReviveMillsecond; // 自动复活倒计时毫秒数
	tint32 m_nCorpseTime; // 镜像尸体存在时间

public:
	tint32 GetLifeTime() const { return m_nLifeTime; }
	void SetLifeTime(tint32 val) { m_nLifeTime = val; }
	bool IsSummoned() const { return m_AIProto.eAIAction == ATAT_SUMMONED; }
	void SetOwnerObjID(tint32 nObjId) { m_nOwnerId = nObjId; }
	tint32 GetOwnerObjID() const { return m_nOwnerId; }
	Obj_CharacterPtr GetOwnerCharacter();
	Obj_UserPtr GetOwnerUser();

private:
	tint32 m_nLifeTime;	// 生命时长 毫秒 -1表示无限
	tfloat32 m_fAttackFactor;  // 攻击力修正系数
	tfloat32 m_fDefendFactor;  // 防御力修正系数
	tint32 m_nCurSkillIndex;   // 当前选择的技能索引
	tint32 m_nOwnerId;			// 所有者的ID
};

POOLDEF_DECL(Obj_ZombieUser);

typedef boost::shared_ptr<Obj_ZombieUser> Obj_ZombieUserPtr;

#endif // __OBJ_ZOMBIE_USER_H__
