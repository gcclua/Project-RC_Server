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

	int GetNpcForceType() const;		// ��ȡNPC����

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
		AI_MARCH,//�о�
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
		METHOD_NORMAL=0,// ��ս���Ŀ��ѡ�� ģʽ
		METHOD_NEAREST=1, //�������Ŀ��
	};

	virtual bool CanAcceptThreat(void) const {return true;};
	virtual bool OnThreat(Obj_Character& rAttacker,int nIncThreatNum);
	virtual void  Tick_EnemyList(const TimeInfo& rTimeInfo);
	
	//��Ŀ�귢���˺�
	virtual bool OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage);
	//�����˺�
	virtual void OnReceiveDamage(DamagesInof_T& rDamage);
public:
	bool InCombat(){return m_curAIType == AI_COMBAT;}
	void EnterMarch();
	void EnterTrace();
	bool SwitchAI(int AIType);
	void ProessTrace(Obj_Character& rUnit,float fAttackDis);//׷��
	// ��ս��״̬��ѡ��һ������
	void SelectSkillAndTarget(int& nSelSkillId,int& nSelObjectId);
	// ��׷��״̬���ͷŵļ���
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
	//����
	virtual void OnDie(Obj_Character& rKiller);
	virtual void ChangeCurSelectObjId(int nId);

	// �����ƶ�·��
	void MoveAppend(const ScenePos &rPos);

	// ��ʼ�о�·������
	virtual void   SelectTargetForMarch(bool bAttack);
	virtual void   InitPassiveSkill();
	
protected:   

	//NPC ���ܵ�ʹ�÷�ʽ
	enum 
	{
		SKILLUSE_CD =0,//��ȴ���˾��ͷ�
		SKILLUSE_WEIGHT,//Ȩ�ؿ���
	};
	void Tick_AI(TimeInfo const& rTimeInfo);
	void Tick_AI_Idle(TimeInfo const& rTimeInfo);
	void Tick_AI_March(TimeInfo const& rTimeInfo);
	void Tick_AI_Combat(TimeInfo const& rTimeInfo);
	void Tick_AI_Trace(TimeInfo const& rTimeInfo);

	bool SelectCanAttackObj();
	virtual void EnterCombat(void);
	virtual void LeaveCombat(void);

	//npc ѡ��Ŀ�귽ʽ
	int SelectNewTarget(int SelMethod);
	int SelectMethod_Sencond();
	int SelectMethod_Rand();
	int SelectMethod_March();
	// ���ݼ��ܵ�Ŀ���ѡ���߼����Լ�����ѡ��
	int SelectNewSkillTarget(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx);
	

	int m_curAIType;
	tfloat32 m_fAlertRadius;//���䷶Χ
	int m_nLastAttackTime;//�ϴι�����ʱ��
	int m_nAttackTime;//������Ƶ��
	ScenePos m_lastTracePos;//��һ��׷�ٵ�λ��
	float m_fTraceStopDis;//׷��ֹͣ����
	int m_nLastTraceTime;//�ϴ�׷��ʱ��
	int m_nTraceTime;//׷�ٵ�ʱ��
	int16 m_nAttackDisType;//������������ ��ս����Զ��
	int m_nSkillStrategyId;//����ʹ�ò���Id
	int    m_nXpSpeed; // ս��ظ��ٶ�
	bool   m_bRobot;    // �Ƿ��йܣ��Զ��ͷż���
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
	int     m_nArrangeIndex; // ���ε�λ��

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
