#ifndef _OBJ_CHARACTER_H_
#define _OBJ_CHARACTER_H_

#include "Obj_Action.h"
#include "CombatStruct/GameStruct_CombatAttr.h"
#include "skill/GameStruct_Skill.h"
#include "Scene/Skill/SkillBaseLogic.h"
#include "Scene/Impact/ImpactBaseLogic.h"
#include "CombatStruct/GameStruct_Threat.h"

namespace Packets
{
	class GC_BROADCAST_ATTR_PAK;
}

#define BIND_CHILDREN_MAX (4)

enum ESkillTarCheckRet
{
	E_Skill_Tar_Effect = 0,		// 是技能所针对的目标
	E_Skill_Tar_Type_Err,		// 目标类型不符合
	E_Skill_Tar_Dis_Err,		// 与目标距离已超出技能施法距离
	E_Skill_Tar_Invalid,		// 其他类型错误
};

class Obj_Character : public Obj_Action
{
public:
	Obj_Character(void);
	virtual ~Obj_Character(void);

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

public:
	int GetCurSelectObjId(void)const {return m_nCurSelectObjId;};
	virtual void ChangeCurSelectObjId(int nId) {m_nCurSelectObjId =nId;};
protected:
	int m_nCurSelectObjId;//当前选中的目标

public:
	int	GetDataID(void) const {return m_nDataID;}
	void	SetDataID(int nDataID) {m_nDataID = nDataID;}
protected:
	int m_nDataID;

public:
	void FaceTo(ScenePos facePos);
	void FaceTo(int faceObjId);
public:
	float GetFaceDir(void) const {return m_fFaceDir;}
	void SetFaceDir(float fFaceDir);
private:
	float m_fFaceDir;
//////////////////////////////////////////////////////////////////////////
// 移动 begin
//////////////////////////////////////////////////////////////////////////
public:
	float GetMoveSpeed(void);
	bool IsMoving(void) const;
public:
	virtual void BeforeMoveTo();
	virtual bool IsCanMove();
	virtual void MoveTo(const ScenePos &rPos, float fStopRange = 0.01f);
	void StopMove(bool bNotifyClient, bool bNotifyEvent);
	virtual void TeleMoveTo(const ScenePos &targetrPos);
	void UpdateTeleMoveToClient(const ScenePos &targetrPos,bool isNeedChangeFacaTo,int nAnimalId=-1);
public:
	virtual void OnStartMove(void);
	virtual void OnEndMove(void);
public:
	virtual void SendMoveStatus(Obj_March &rMarch);
	void BroadcastMoveStatus(void);
public:
	virtual void Tick_Moving(const TimeInfo &rTimeInfo);
	void Moving(const TimeInfo &rTimeInfo);
	void Stopping(void);
protected:
	PathCont m_PathCont;
protected:
	float m_fDistanceCompensate;
	int m_fMoveTimeSeconds;
	
private:
	ScenePos m_TargetPos;
	float m_fStopRange;

//////////////////////////////////////////////////////////////////////////
// 移动 end
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////属性相关Begin////////////////////////////////////
public:
	////计算战斗属性
	virtual void CalculateFinalyAttr(void){};
	////计算战斗属性（各个子系统）
	virtual void CalculateInitalAttr(void){};		//初始		Obj_User && Obj_Npc && Obj_Fellow &&Obj_ZombieUser
	virtual void CalculateBuffRefix(void);			//Buff		Obj_User && Obj_Npc && Obj_Fellow &&Obj_ZombieUser
	virtual void CalculateSkillRefix(void);		//技能		Obj_User && Obj_Npc && Obj_Fellow &&Obj_ZombieUser
	virtual void CalculateLevelRefix(void){};		//等级		Obj_Fellow
	//获取最终战斗属性数值
	virtual int GetCombatAttrByID(int AttrId){return 0;};
	//重置计算的标记位
	virtual void MarkInitalAttrCalcDirty(void){m_InitialAttr.MarkAllCalculationDirtyFlag();};
	virtual void MarkBuffRefixCalcDirty(void){m_BuffCombatRefix.MarkAllCalculationDirtyFlag();};
	virtual void MarkSkillRefixCalcDirty(void){m_SkillCombatRefix.MarkAllCalculationDirtyFlag();};
	virtual void MarkLevelRefixCalcDirty(void){};
	//重置所有战斗属性标记
	void MarkCombatAttrCalcDirty(void);
	//心跳中计算战斗属性
	void Tick_CalculateCombatAttr();
	//!!!一般都是使用Increase接口去修正 当前血 蓝 XP能量
	void SetCurHp(int nCurHp);
	void SetCurXp(int nCurXp);
	void SetMaxHp(int nMaxHp);
	bool IsAlive(void) const;
	int GetCurHp(void) const{return m_nCurHp;}
	int IncreaseHp( int nHP, Obj_Character& rSourceObj ); //!!统一使用该接口修改HP, rSourceObj来源者，没有来源就是自己。
	int GetCurXP(void)const{return m_nCurXp;}
	int IncreaseXp( int nXp); //!!统一使用该接口修改XP
	int  GetLevel(void)const{return m_nLevel;}
	void  SetLevel(int nCurLev);
	const CHARNAME&  GetName(void)const{return m_Name;}
	void SetName(const CHARNAME& NewName);
	void SetName(const char* strName);
	//todo 目前除玩家外 默认为近战 若npc 或者伙伴等 有区分 请实现判断接口
	virtual bool IsCloseCombat(){return true;}
	virtual bool IsLongCombat() {return false;};//远程
	//势力
	int GetForceType(void) const{return m_ForceType;};
	void SetForceType(int nType) ;

	//关系
	virtual tint32 GetRelationByForceType(Obj_Character& rUnit) ;
	//隐身级别
	virtual void SetStealthLev(int val);
	virtual bool IsWantedTypeUnit(int nWantedType,Obj_Character& rTargetUnit);
	void BroadCastAnimState(int AnimState,
							int verOff=-1,
							int horOff=-1,
							int lastTime=-1, 
							int resortTime=-1,
							int hitTimes=-1,
							int hitInterval=-1);
protected:
	CombatAttr m_InitialAttr;//初始战斗数值(表里配的成长值)
	CombatAttr m_FinalyAttr;//最终战斗值
	CombatAttr_Refix m_BuffCombatRefix;//buff系统战斗属性修正
	CombatAttr_Refix m_SkillCombatRefix;//技能战斗属性修正被动技能等)
	int m_nCurHp;
	int m_nCurXp;
	int m_nLevel;
	CHARNAME m_Name;
	int m_ForceType; //势力
	bool m_bDie;		//是否死亡 false：活，true：死
	bool m_bIsBreedingClick;
	uint32 m_nLastBroadcastHitTime;//上次广播受击状态的时间
	//同步属性包的脏标的
	BitSet<BaseAttrSyncDirty_T::TYPE_MAXNUM> m_AttrSyncDirtyFlag; //同步属性包的脏标记
	//广播属性包的脏标的
	BitSet<BaseAttrBroadDirty_T::TYPE_MAXNUM> m_AttrBroadCastDirtyFlag; //广播属性包的脏标记

////////////////////////////////////属性相关End////////////////////////////////////
	

////////////////////////////////////技能Begin////////////////////////////////////
public:
	//使用技能
	bool UseSkill(SkillInfo_T& skillInfo);
	//使用技能
	bool UseSkill(int nSkillId,int nTargetId);
	//技能使用检测
	bool CanActivateSkill(SkillInfo_T& skillInfo) ;
	//技能使用前操作
	void BeforActiveSkill(SkillInfo_T& skillInfo) ;
	//使用技能
	void ActivateSkill(SkillInfo_T& skillInfo) ;
	//冷却时间 检测
	bool CooldownCheck(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);
	//技能本身 检测
	bool SkillCheck(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx) ;
	//技能激活自身检测
	bool SelfCheck_Activate(Table_SkillBase const&  rSkillBase,Table_SkillEx const& rSkillEx) ;
	//技能激活目标检测
	bool TargetCheck_Activate(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx, int nTargetId) ;
	//是否是技能所针对的目标，返回 ESkillTarCheckRet，避免选中的是友方目标但是距离在施法距离内，玩家寻路去了友方目标那里的情况
	ESkillTarCheckRet Skill_IsWantedUnit(Table_SkillBase const&  rSkillBase,Table_SkillEx const& rSkillEx,Obj_Character& rUnit) ;
	//中断技能
	void BreakCurSkill();
	//消耗检测
	bool CanDeplete(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);
	bool IsDepleteEnough(int nSKillDelType,int nSkillDelValue);
	bool SkillDeplete(int nSKillDelType,int nSkillDelValue,Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);
	void SkillGain(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);//技能收益
	SkillBaseLogicPtr CreateSkillInstanceById(int nLogicId);//临时用switch case表示
	SkillBaseLogicPtr GetCurSkillInstance(void){return m_CurSkillLogicPtr;}
	int GetOwnSkillByIndex(int nIndex) const;
	//设置拥有的技能
	bool SetOwnSkill(int nSkillId,int nSkillIndex);
	bool DeleteSkill(int nSkillIndex);
	bool IsHaveSkill(int nSkillId);
	int GetSkillIndexById(int nSkillId);
	bool IsUsingSkill(void);
	virtual void OnSkillFinish();
	uint32 GetLastUseSkillTime() const { return m_nLastUseSkillTime; }
	//发送被动技能buff
	void SendPassiveSkillBuff(int nSkillId);
	//清除被动技能buff
	void ClearPassiveSkillBuff(int nSkillId);
	//是否被动技能
	bool IsPassiveSkill(int nSkillId);
protected:
	void Tick_Skill(const TimeInfo &rTimeInfo);
	SkillBaseLogicPtr m_CurSkillLogicPtr;
	bsarray<int, MAXOWNSKILL> m_OwnSkillList;
	uint32 m_nLastUseSkillTime;
	////////////////////////////////////技能相关End////////////////////////////////////

////////////////////////////////////冷却时间相关Begin////////////////////////////////////
public:
	bool IsCoolDowning(const int16 nCDId)const{return m_CoolDownList.IsSlotCooldowned(nCDId);}
	CooldownList_T&  GetCooldownList(void){return m_CoolDownList;}
	CooldownList_T const& GetCooldownList(void)const{return m_CoolDownList;}
	bool AddCoolDownToList(int16 nCoolDownId);
	bool UpdateCooldownList(int16 nID, int nTotalTime,int nElapsed);
	void Tick_CooldownList(const TimeInfo& rTimeInfo);
protected:
	CooldownList_T m_CoolDownList;//冷却时间
////////////////////////////////////冷却时间相关End////////////////////////////////////

////////////////////////////////////BUFF 相关Begin////////////////////////////////////
public:
	bool IsHaveImpact(int nImpactId) const;
	void CleanAllImpact(void);
	bool RemoveImpactById(int nImpactId);
	void SendImpactToUnit(Obj_Character& rTarget,int nImpactId,int nSkillId);//技能ID 无则填-1
	void ReceiveImpact(int nImpactId,int nSkillId,Obj_Character& rSender);//技能ID 无则填-1
	ImpactBaseLogicPtr CreateImpactInstanceById(int nLogicId);
	ImpactPtrList const& GetBuffList() const { return m_buffList; }
	ImpactPtrList& GetBuffList() { return m_buffList; }
	bool IsHaveImpactFadeoutReceiveDamage(void);
protected:
	//!! 注意 在其他地方 添加buff到玩家身上的BuffList 用这个接口
	void AddImpact(ImpactBaseLogicPtr InstancePtr);
	//正式将缓存的buff加到玩家身上的List
	void _AddImpactImmediate(ImpactBaseLogicPtr Ptr);
	//从玩家身上的List删除BUFF
	ImpactPtrList::iterator _DelImpactImmediate(ImpactPtrList::iterator itRemove);
	void Tick_Impact(const TimeInfo &rTimeInfo);
	void Tick_ImpactAdd(void);
	void Tick_ImpactClean(void);
	void Tick_ImapctRun(const TimeInfo &rTimeInfo);
	void CleanUpImpactOnLogin(void);//清除下需要在登录时清除的BUFF
protected:
	ImpactPtrList m_buffList;//玩家身上的buff List	//【stl】
	ImpactPtrList m_CachebuffList;//用来暂时缓存的 下一次心跳加上去	//【stl】
////////////////////////////////////BUFF 相关End////////////////////////////////////


////////////////////////////////////战斗 相关Begin////////////////////////////////////
public:
	bool IsHit(Obj_Character& rDefenser);
	bool IsCritical(Obj_Character& rDefenser);
	void CalculateAttackDamage(Obj_Character& rDefenser,bool& bIsHit ,float fDamageRefix ,int nAttackAdd,DamagesInof_T& AttackDamage);
	virtual bool CanAcceptThreat(void) const {return false;};
	virtual bool OnThreat(Obj_Character& rAttacker,int nIncThreatNum);
	virtual void Tick_EnemyList(const TimeInfo& rTimeInfo){};
	virtual int IncreaseUnitThreat(Obj_Character& rUnit, int nThreat);
	virtual int GetUnitThreat(Obj_Character& rUnit);
	virtual bool IsInEnemyList(Obj_Character& rUnit);
	virtual int ClearUnitThreat(Obj_Character & rUnit);
	virtual int ClearFullThreat(void);
	virtual EnemyDataInfo_T& GetEnemyData(void) {return m_enemyInfo;}
	virtual EnemyDataInfo_T const& GetEnemyData(void) const {return m_enemyInfo;}
	virtual int	GetEnemyCount(void) const;
	virtual void EnterCombat(void);
	virtual void LeaveCombat(void);
	virtual void OnEnterCombat(void);
	virtual void OnLeaveCombat(void);
	bool IsInCombat(){return m_bIsInCombat;}
	bool IsTrackPointUsed(int nPointIndex);
	void SetTrackPointFlag(int nPointIndex,bool bFlag);
	void CleanUpAllTrackPointFlag(void);
	virtual void InAttacked(Obj_Character& rActtacker){};	// 被攻击
protected:
	EnemyDataInfo_T m_enemyInfo;
	bool m_bIsInCombat;
	bsarray<bool, MAXTRACEPOINTNUM> m_IsTrackPointUsed;		//记录被追踪时 周围的追踪点是否被占用
////////////////////////////////////战斗 相关End////////////////////////////////////


////////////////////////////////////伤害 相关Begin////////////////////////////////////
public:
	//向目标发送伤害
	virtual bool OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage);
	//接受伤害
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
	//类型伤害处理
	void OnTypeDamage(DamagesInof_T& rDamage);
	//处理完类型伤害后  汇总成无类型伤害处理 最终的掉血
	void OnNoTypeDamage(DamagesInof_T& rDamage);
	//伤害修正
	void RefixTypeDamage(DamagesInof_T& rDamage);
	void RefixNoTypeDamage(DamagesInof_T& rDamage);
	void RefixSendAllDamage(Obj_Character& rTarget, DamagesInof_T& rDamage); // 修正发送出的所有伤害
	//伤害免疫
	void IgnoreTypeDamage(DamagesInof_T& rDamage);
	void IgnoreNoTypeDamage(DamagesInof_T& rDamage);
	//伤害吸收反射
	void AbsorbAndReflexTypeDamage(DamagesInof_T& rDamage);
	void AbsorbAndReflexNoTypeDamage(DamagesInof_T& rDamage);
	//死亡
	virtual void  OnDie(Obj_Character& rKiller);

	bool IsDie();
	void Tick_Damage(const TimeInfo &rTimeInfo);
	bool IsInEscape(void);
	void ResetEscape(void);
protected:
	void SetDie(bool bDie);
private:
	int m_EscapeCountDown;
////////////////////////////////////伤害 相关End////////////////////////////////////

public:
	//重载设定位置入口
	virtual void DelFromScene(void);	
//绑定相关内容
//////////////////////////////////////////////////////////////////////////

public:
	//参考字典格式参考 DictionaryFormat::FormatDictionary函数 IsFilterRepeat : true时候过滤，false不过滤。
	void SendNotice(const tchar* szNotice,bool IsFilterRepeat = false);

public:
	int64 GetPlayerId() const {return m_nPlayerId;}
	void  SetPlayerId(int64 nVal) {m_nPlayerId = nVal;}
private:
	int64 m_nPlayerId;
};

typedef boost::shared_ptr<Obj_Character> Obj_CharacterPtr;

typedef GeneralObjRefCont<Obj_Character, 256> CharacterRefCont;


#endif
