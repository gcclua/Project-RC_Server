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
	int m_nCorpseTime;//ʬ��ͣ��ʱ��
	//////////////////////////////////////////////////////////////////////////
// ���� End
//////////////////////////////////////////////////////////////////////////

public:
	const ScenePos & GetRelivePos(void) const { return m_RelivePos; }
	void SetRelivePos(const ScenePos &val) { m_RelivePos = val; }

private:
	ScenePos m_RelivePos;
	
//////////////////////////////////////////////////////////////////////////
// ���� Begin
//////////////////////////////////////////////////////////////////////////
public:
	virtual void CalculateInitalAttr(void);
	virtual void CalculateFinalyAttr(void);
	//��ȡ����ս��������ֵ
	virtual int GetCombatAttrByID(int AttrId);
	int GetNpcType() const { return m_nNpcType; }
	void SetNpcType(int val) { m_nNpcType = val; }

	int GetNpcForceType(Obj_Character &rObj) const;		// ��ȡNPC����
protected:
	int m_nNpcType;
	//////////////////////////////////////////////////////////////////////////
// ���� end
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// AI���Begin
//////////////////////////////////////////////////////////////////////////
public:
	//NPC��AI��Ϊ �����
	enum 
	{
		AI_IDLE =0,//����
		AI_COMBAT,//ս��
		AI_PATROL,//Ѳ��
		AI_FOLLOW,//����
		AI_TRACE,//׷��
	};
	enum 
	{
		RANDMOVEINTERVALTIME =5000,//����ƶ����ʱ�� 5s
		RANDMOVERATE =5,//����ƶ��ĸ���
	};

	//���
	enum 
	{
		METHOD_NORMAL=0,//�������Ŀ��ѡ�� ģʽ
		METHOD_SECOND,//�ڶ����Ŀ��ѡ�� ģʽ
		METHOD_RAND,//������Ŀ��ѡ�� ģʽ
		METHOD_FURTHEST,//��Զ���Ŀ��ѡ�� ģʽ
		METHOD_CLEAR,//������ ģʽ
		METHOD_IMPACT,//���ض�BUFF��Ŀ��
	};
	enum 
	{
		SWITCHTARGETTIME =5000,//�л�Ŀ��ļ��ʱ�� ��λ ����
	};
	
	void ResetSwitchTargetCooldown(void){m_nSwitchTargetCooldown =Obj_Npc::SWITCHTARGETTIME;}
	virtual bool CanAcceptThreat(void) const {return true;};
	virtual bool OnThreat(Obj_Character& rAttacker,int nIncThreatNum);
	virtual void  Tick_EnemyList(const TimeInfo& rTimeInfo);
	
	//��Ŀ�귢���˺�
	virtual bool OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage);
	//�����˺�
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
public:
	bool SwitchAI(int AIType);
	void ProessRandMove(void);//����ƶ�
	void ProessTrace(Obj_Character& rUnit,float fAttackDis);//׷��
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
	//����
	virtual void OnDie(Obj_Character& rKiller);
	virtual bool IsCloseCombat(); //�Ƿ��ǽ�ս
	virtual bool IsLongCombat();//�Ƿ���Զ��
	virtual bool IsPysicalAttack();//�﹥ 
	virtual bool IsMagicalAttack();//ħ��
	virtual void ChangeCurSelectObjId(int nId);
	
protected:   
	struct CanUseSkillSkillInfo //NPC���ͷŵ� ��ѡ���ܵ����ݽṹ
	{
	public:
		CanUseSkillSkillInfo(){CleanUp();}
		int m_nSkillId;//����ID
		int m_SeleTargetLogic;//ѡ��Ŀ���߼�
		int m_SelectParam1;//�߼�����1
		int m_nSelectParam2;//�߼�����2
		int m_nUseType;//����ʹ�÷�ʽ
		int m_nWeight;//����Ȩ��
		int m_nActivateLogic;//���ܼ����߼�
		int m_nActivateParam1;//�߼�����1
		int m_nActivateParam2;//�߼�����2
		int m_nSeleObjId;//����ѡ���Ŀ��
		int m_nPriority;//����ѡ�����ȼ�
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
	//NPC ���ܼ����߼�
	enum 
	{
		SKILL_ATTACKTIME =0,//����Ƶ������
		SKILL_HPLESSTHEN, //Ѫ������ĳ���ٷֱ�
		SKILL_TARGETHPLESSTHEN, //Ŀ��Ѫ������ĳ���ٷֱ�
		SKILL_HAVEIMPACT, //��ĳ���ض���BUFF
		SKILL_TARGETHAVEIMPACT,//Ŀ����ĳ���ض���BUFF
		SKILL_COMBATTIME,//ս��ʱ�� ��λ����
		SKILL_SCRIPTCHECK,//�������
		SKILL_NOCHECK , //����������
	};
	//NPC ���ܵ�ʹ�÷�ʽ
	enum 
	{
		SKILLUSE_CD =0,//��ȴ���˾��ͷ�
		SKILLUSE_WEIGHT,//Ȩ�ؿ���
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
	//npc ѡ��Ŀ�귽ʽ
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
	int m_nLastRandMoveTime;//�ϴ�����ƶ���ʱ�� ��λ������
	int m_nSwitchTargetCooldown;
	float m_fPathRadius;//��ս��Χ
	float m_fAlertRadius;//���䷶Χ
	bool	 m_bIsRandMove;//�Ƿ�����ε�
	float m_fRandMoveDis;//����ε���Χ
	int m_FollowTargetObjId;//����Ŀ��ObjId
	int m_nLastAttackTime;//�ϴι�����ʱ��
	int m_nAttackTime;//������Ƶ��
	ScenePos m_lastTracePos;//��һ��׷�ٵ�λ��
	float m_fTraceStopDis;//׷��ֹͣ����
	int m_nLastTraceTime;//�ϴ�׷��ʱ��
	int m_nTraceTime;//׷�ٵ�ʱ��
	int16 m_nAttackDisType;//������������ ��ս����Զ��
	int m_nSkillStrategyId;//����ʹ�ò���Id
	uint32 m_nEnterCombatTime;//����ս����ʱ��
	bool	m_bIsJustEnterCombat;//�Ƿ�ոս���ս��
	//////////////////////////////////////////////////////////////////////////
//AI���End
//////////////////////////////////////////////////////////////////////////

	//ģ������ģ��NPC
public:
	void		SetModelVisualID(int nModeId){m_nModelVisualID = nModeId;}
	int		GetModelVisualID()const{return m_nModelVisualID;}
	void		SetWeaponDataID(int nWeaponDataID){m_nWeaponDataID = nWeaponDataID;}
	int		GetWeaponDataID()const{return m_nWeaponDataID;}
	void		SetKylinValue(int nKylinValue){m_nKylinValue = nKylinValue;}
	int		GetKylinValue()const{return m_nKylinValue;}
private:
	int m_nModelVisualID;		// ģ��ID
	int m_nWeaponDataID;			// ����ID
	int m_nKylinValue;			// ս��ֵ���ٵģ�
//////////////////////////////////////////////////////////////////////////
//Ѳ�����
public:
	enum 
	{
		PATROL_OVER			= 0,//ֱ�ӽ���
		PATROL_OVER_DELETE	= -1,//��������ɱ
	};
	enum 
	{
		PATROL_EVENT_SLEEP	= 1,//ͣ��
		PATROL_EVENT_BUFF	= 2,//���Լ���buff
	};
	enum  //¥�Ϲ����õ��Ĳ���λ����Χ[0,2]
	{
		PATROL_PARAM_SLEEPTIME	= 0,
		PATROL_PARAM_BUFFID		= 0,
	};
private:
	//Ѳ��·������
	int m_nCurPatrolStep;
	//Ѳ���ü�ʱ
	int m_nPatrolCountDown;
private:
	bool	IsNeedPatrol();
public:
	void	StartPatrol(Obj_Character& rChar, int nStartID);
//Ѳ�߽���
//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// �Զ��ظ�Start
public:
	void Tick_AutoCure(TimeInfo const& rTimeInfo);
private:
	int m_nCureTime;
	int m_nIncHp;
	int m_nIncMp;
	// �Զ��ظ�End
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
