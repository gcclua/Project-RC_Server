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
	E_Skill_Tar_Effect = 0,		// �Ǽ�������Ե�Ŀ��
	E_Skill_Tar_Type_Err,		// Ŀ�����Ͳ�����
	E_Skill_Tar_Dis_Err,		// ��Ŀ������ѳ�������ʩ������
	E_Skill_Tar_Invalid,		// �������ʹ���
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
	int m_nCurSelectObjId;//��ǰѡ�е�Ŀ��

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
// �ƶ� begin
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
// �ƶ� end
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////�������Begin////////////////////////////////////
public:
	////����ս������
	virtual void CalculateFinalyAttr(void){};
	////����ս�����ԣ�������ϵͳ��
	virtual void CalculateInitalAttr(void){};		//��ʼ		Obj_User && Obj_Npc && Obj_Fellow &&Obj_ZombieUser
	virtual void CalculateBuffRefix(void);			//Buff		Obj_User && Obj_Npc && Obj_Fellow &&Obj_ZombieUser
	virtual void CalculateSkillRefix(void);		//����		Obj_User && Obj_Npc && Obj_Fellow &&Obj_ZombieUser
	virtual void CalculateLevelRefix(void){};		//�ȼ�		Obj_Fellow
	//��ȡ����ս��������ֵ
	virtual int GetCombatAttrByID(int AttrId){return 0;};
	//���ü���ı��λ
	virtual void MarkInitalAttrCalcDirty(void){m_InitialAttr.MarkAllCalculationDirtyFlag();};
	virtual void MarkBuffRefixCalcDirty(void){m_BuffCombatRefix.MarkAllCalculationDirtyFlag();};
	virtual void MarkSkillRefixCalcDirty(void){m_SkillCombatRefix.MarkAllCalculationDirtyFlag();};
	virtual void MarkLevelRefixCalcDirty(void){};
	//��������ս�����Ա��
	void MarkCombatAttrCalcDirty(void);
	//�����м���ս������
	void Tick_CalculateCombatAttr();
	//!!!һ�㶼��ʹ��Increase�ӿ�ȥ���� ��ǰѪ �� XP����
	void SetCurHp(int nCurHp);
	void SetCurXp(int nCurXp);
	void SetMaxHp(int nMaxHp);
	bool IsAlive(void) const;
	int GetCurHp(void) const{return m_nCurHp;}
	int IncreaseHp( int nHP, Obj_Character& rSourceObj ); //!!ͳһʹ�øýӿ��޸�HP, rSourceObj��Դ�ߣ�û����Դ�����Լ���
	int GetCurXP(void)const{return m_nCurXp;}
	int IncreaseXp( int nXp); //!!ͳһʹ�øýӿ��޸�XP
	int  GetLevel(void)const{return m_nLevel;}
	void  SetLevel(int nCurLev);
	const CHARNAME&  GetName(void)const{return m_Name;}
	void SetName(const CHARNAME& NewName);
	void SetName(const char* strName);
	//todo Ŀǰ������� Ĭ��Ϊ��ս ��npc ���߻��� ������ ��ʵ���жϽӿ�
	virtual bool IsCloseCombat(){return true;}
	virtual bool IsLongCombat() {return false;};//Զ��
	//����
	int GetForceType(void) const{return m_ForceType;};
	void SetForceType(int nType) ;

	//��ϵ
	virtual tint32 GetRelationByForceType(Obj_Character& rUnit) ;
	//������
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
	CombatAttr m_InitialAttr;//��ʼս����ֵ(������ĳɳ�ֵ)
	CombatAttr m_FinalyAttr;//����ս��ֵ
	CombatAttr_Refix m_BuffCombatRefix;//buffϵͳս����������
	CombatAttr_Refix m_SkillCombatRefix;//����ս�����������������ܵ�)
	int m_nCurHp;
	int m_nCurXp;
	int m_nLevel;
	CHARNAME m_Name;
	int m_ForceType; //����
	bool m_bDie;		//�Ƿ����� false���true����
	bool m_bIsBreedingClick;
	uint32 m_nLastBroadcastHitTime;//�ϴι㲥�ܻ�״̬��ʱ��
	//ͬ�����԰�������
	BitSet<BaseAttrSyncDirty_T::TYPE_MAXNUM> m_AttrSyncDirtyFlag; //ͬ�����԰�������
	//�㲥���԰�������
	BitSet<BaseAttrBroadDirty_T::TYPE_MAXNUM> m_AttrBroadCastDirtyFlag; //�㲥���԰�������

////////////////////////////////////�������End////////////////////////////////////
	

////////////////////////////////////����Begin////////////////////////////////////
public:
	//ʹ�ü���
	bool UseSkill(SkillInfo_T& skillInfo);
	//ʹ�ü���
	bool UseSkill(int nSkillId,int nTargetId);
	//����ʹ�ü��
	bool CanActivateSkill(SkillInfo_T& skillInfo) ;
	//����ʹ��ǰ����
	void BeforActiveSkill(SkillInfo_T& skillInfo) ;
	//ʹ�ü���
	void ActivateSkill(SkillInfo_T& skillInfo) ;
	//��ȴʱ�� ���
	bool CooldownCheck(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);
	//���ܱ��� ���
	bool SkillCheck(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx) ;
	//���ܼ���������
	bool SelfCheck_Activate(Table_SkillBase const&  rSkillBase,Table_SkillEx const& rSkillEx) ;
	//���ܼ���Ŀ����
	bool TargetCheck_Activate(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx, int nTargetId) ;
	//�Ƿ��Ǽ�������Ե�Ŀ�꣬���� ESkillTarCheckRet������ѡ�е����ѷ�Ŀ�굫�Ǿ�����ʩ�������ڣ����Ѱ·ȥ���ѷ�Ŀ����������
	ESkillTarCheckRet Skill_IsWantedUnit(Table_SkillBase const&  rSkillBase,Table_SkillEx const& rSkillEx,Obj_Character& rUnit) ;
	//�жϼ���
	void BreakCurSkill();
	//���ļ��
	bool CanDeplete(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);
	bool IsDepleteEnough(int nSKillDelType,int nSkillDelValue);
	bool SkillDeplete(int nSKillDelType,int nSkillDelValue,Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);
	void SkillGain(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx);//��������
	SkillBaseLogicPtr CreateSkillInstanceById(int nLogicId);//��ʱ��switch case��ʾ
	SkillBaseLogicPtr GetCurSkillInstance(void){return m_CurSkillLogicPtr;}
	int GetOwnSkillByIndex(int nIndex) const;
	//����ӵ�еļ���
	bool SetOwnSkill(int nSkillId,int nSkillIndex);
	bool DeleteSkill(int nSkillIndex);
	bool IsHaveSkill(int nSkillId);
	int GetSkillIndexById(int nSkillId);
	bool IsUsingSkill(void);
	virtual void OnSkillFinish();
	uint32 GetLastUseSkillTime() const { return m_nLastUseSkillTime; }
	//���ͱ�������buff
	void SendPassiveSkillBuff(int nSkillId);
	//�����������buff
	void ClearPassiveSkillBuff(int nSkillId);
	//�Ƿ񱻶�����
	bool IsPassiveSkill(int nSkillId);
protected:
	void Tick_Skill(const TimeInfo &rTimeInfo);
	SkillBaseLogicPtr m_CurSkillLogicPtr;
	bsarray<int, MAXOWNSKILL> m_OwnSkillList;
	uint32 m_nLastUseSkillTime;
	////////////////////////////////////�������End////////////////////////////////////

////////////////////////////////////��ȴʱ�����Begin////////////////////////////////////
public:
	bool IsCoolDowning(const int16 nCDId)const{return m_CoolDownList.IsSlotCooldowned(nCDId);}
	CooldownList_T&  GetCooldownList(void){return m_CoolDownList;}
	CooldownList_T const& GetCooldownList(void)const{return m_CoolDownList;}
	bool AddCoolDownToList(int16 nCoolDownId);
	bool UpdateCooldownList(int16 nID, int nTotalTime,int nElapsed);
	void Tick_CooldownList(const TimeInfo& rTimeInfo);
protected:
	CooldownList_T m_CoolDownList;//��ȴʱ��
////////////////////////////////////��ȴʱ�����End////////////////////////////////////

////////////////////////////////////BUFF ���Begin////////////////////////////////////
public:
	bool IsHaveImpact(int nImpactId) const;
	void CleanAllImpact(void);
	bool RemoveImpactById(int nImpactId);
	void SendImpactToUnit(Obj_Character& rTarget,int nImpactId,int nSkillId);//����ID ������-1
	void ReceiveImpact(int nImpactId,int nSkillId,Obj_Character& rSender);//����ID ������-1
	ImpactBaseLogicPtr CreateImpactInstanceById(int nLogicId);
	ImpactPtrList const& GetBuffList() const { return m_buffList; }
	ImpactPtrList& GetBuffList() { return m_buffList; }
	bool IsHaveImpactFadeoutReceiveDamage(void);
protected:
	//!! ע�� �������ط� ���buff��������ϵ�BuffList ������ӿ�
	void AddImpact(ImpactBaseLogicPtr InstancePtr);
	//��ʽ�������buff�ӵ�������ϵ�List
	void _AddImpactImmediate(ImpactBaseLogicPtr Ptr);
	//��������ϵ�Listɾ��BUFF
	ImpactPtrList::iterator _DelImpactImmediate(ImpactPtrList::iterator itRemove);
	void Tick_Impact(const TimeInfo &rTimeInfo);
	void Tick_ImpactAdd(void);
	void Tick_ImpactClean(void);
	void Tick_ImapctRun(const TimeInfo &rTimeInfo);
	void CleanUpImpactOnLogin(void);//�������Ҫ�ڵ�¼ʱ�����BUFF
protected:
	ImpactPtrList m_buffList;//������ϵ�buff List	//��stl��
	ImpactPtrList m_CachebuffList;//������ʱ����� ��һ����������ȥ	//��stl��
////////////////////////////////////BUFF ���End////////////////////////////////////


////////////////////////////////////ս�� ���Begin////////////////////////////////////
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
	virtual void InAttacked(Obj_Character& rActtacker){};	// ������
protected:
	EnemyDataInfo_T m_enemyInfo;
	bool m_bIsInCombat;
	bsarray<bool, MAXTRACEPOINTNUM> m_IsTrackPointUsed;		//��¼��׷��ʱ ��Χ��׷�ٵ��Ƿ�ռ��
////////////////////////////////////ս�� ���End////////////////////////////////////


////////////////////////////////////�˺� ���Begin////////////////////////////////////
public:
	//��Ŀ�귢���˺�
	virtual bool OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage);
	//�����˺�
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
	//�����˺�����
	void OnTypeDamage(DamagesInof_T& rDamage);
	//�����������˺���  ���ܳ��������˺����� ���յĵ�Ѫ
	void OnNoTypeDamage(DamagesInof_T& rDamage);
	//�˺�����
	void RefixTypeDamage(DamagesInof_T& rDamage);
	void RefixNoTypeDamage(DamagesInof_T& rDamage);
	void RefixSendAllDamage(Obj_Character& rTarget, DamagesInof_T& rDamage); // �������ͳ��������˺�
	//�˺�����
	void IgnoreTypeDamage(DamagesInof_T& rDamage);
	void IgnoreNoTypeDamage(DamagesInof_T& rDamage);
	//�˺����շ���
	void AbsorbAndReflexTypeDamage(DamagesInof_T& rDamage);
	void AbsorbAndReflexNoTypeDamage(DamagesInof_T& rDamage);
	//����
	virtual void  OnDie(Obj_Character& rKiller);

	bool IsDie();
	void Tick_Damage(const TimeInfo &rTimeInfo);
	bool IsInEscape(void);
	void ResetEscape(void);
protected:
	void SetDie(bool bDie);
private:
	int m_EscapeCountDown;
////////////////////////////////////�˺� ���End////////////////////////////////////

public:
	//�����趨λ�����
	virtual void DelFromScene(void);	
//���������
//////////////////////////////////////////////////////////////////////////

public:
	//�ο��ֵ��ʽ�ο� DictionaryFormat::FormatDictionary���� IsFilterRepeat : trueʱ����ˣ�false�����ˡ�
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
