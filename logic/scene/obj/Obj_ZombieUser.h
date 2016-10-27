/********************************************************************************
 *	�ļ�����  Obj_ZombieUser.h
 *	ȫ·����  E:\Code\Server\Server\Server\Server\Scene\Obj\Obj_ZombieUser.h
 *	�����ˣ�  mwh
 *	����ʱ�䣺2014/03/05
 *
 *	����˵�����йܵĽ�ʬ���
 *	�޸ļ�¼��
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

	//�﹥
	virtual bool IsPysicalAttack();
	//ħ��
	virtual bool IsMagicalAttack();
	//��ս
	virtual bool IsCloseCombat();
	//Զ��
	virtual bool IsLongCombat();

	// ����
	virtual void OnDie(Obj_Character& rKiller);
	// �����˺�
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
	
	// ����ս������
	virtual void CalculateFinalyAttr(void);
	// �����ʼ����
	virtual void CalculateInitalAttr(void);
	// ����۷彩ʬ�����������
	virtual void CalculateZombieUserRefix(void);
	// ��ȡ����ս��������ֵ
	virtual tint32 GetCombatAttrByID(tint32 AttrId);
	virtual void MarkZombieUserCalcDirty(void)
	{
		m_ZombieUserCombatRefix.MarkAllCalculationDirtyFlag();
	}

	// ��Ӫ
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
	// ��ʼ��
	//--------------------------------------------------------------------------
	void					Init( const ChallRankMember& rMember, tfloat32 fPropertyPer = 1.0f, tint32 nCase = 0, tint32 nCreatorProfession = -1 );
	void					Init( const ChallRankMember& rMember, const ZombieAIConfig& za, tint32 nIndex, tfloat32 fPropertyPer = 1.0f);
	void					InitSkillDbg( );

	// ��ʼ��Ϊ���ܵ��ٻ���
	void InitAsSkillSummoned(const ChallRankMember& rMember, tint32 nLifeMillSeconds, tfloat32 fAttackFactor, tfloat32 fDefendFactor);

	void InitLimitSkills(tint32 nSkillNum);
	//--------------------------------------------------------------------------
	// ����
	//--------------------------------------------------------------------------
	
	void					SetAIStop( bool stop ) { m_bStopAI = stop; }
	

	void					SetAutoReviveable(bool b) { m_bCanAutoRevive = b; }

	void					CallFellow( );

	void					AddTitle(tint32 titleID);

	tint32					SelectSkill();
	AIController&			GetAIController( ) { return m_AIController; }

private:
	//--------------------------------------------------------------------------
	// ��ʼ��
	//--------------------------------------------------------------------------
	void					InitAI( );
	void					InitAttr( );

	//--------------------------------------------------------------------------
	// ����
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
	tint32 m_nChallengeCase; // ����У��ƥ��ģʽ(������������ϵ��)
	tint32 m_nCreatorProfession; // �����ߵ�ְҵ,,����,��������,��������У�������,,������ְҵ��������
	ZombieAIConfig m_AIProto;

	ChallMemberBase m_MemberBase;
	ChallMemberAttr m_MemberAttr;
	ChallMemberFellow m_MemberFellow;

	AIController m_AIController;
	bool m_bStopAI;

	bool m_bCanAutoRevive; // �Ƿ�����Զ�����
	tint32 m_nAutoReviveMillsecond; // �Զ������ʱ������
	tint32 m_nCorpseTime; // ����ʬ�����ʱ��

public:
	tint32 GetLifeTime() const { return m_nLifeTime; }
	void SetLifeTime(tint32 val) { m_nLifeTime = val; }
	bool IsSummoned() const { return m_AIProto.eAIAction == ATAT_SUMMONED; }
	void SetOwnerObjID(tint32 nObjId) { m_nOwnerId = nObjId; }
	tint32 GetOwnerObjID() const { return m_nOwnerId; }
	Obj_CharacterPtr GetOwnerCharacter();
	Obj_UserPtr GetOwnerUser();

private:
	tint32 m_nLifeTime;	// ����ʱ�� ���� -1��ʾ����
	tfloat32 m_fAttackFactor;  // ����������ϵ��
	tfloat32 m_fDefendFactor;  // ����������ϵ��
	tint32 m_nCurSkillIndex;   // ��ǰѡ��ļ�������
	tint32 m_nOwnerId;			// �����ߵ�ID
};

POOLDEF_DECL(Obj_ZombieUser);

typedef boost::shared_ptr<Obj_ZombieUser> Obj_ZombieUserPtr;

#endif // __OBJ_ZOMBIE_USER_H__
