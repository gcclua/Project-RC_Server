#ifndef _COPYSCENE_H_
#define _COPYSCENE_H_

#include "Scene.h"
#include "service/Invoker.h"

class CopyScene : public Scene
{
public:
	CopyScene(void);
	virtual ~CopyScene(void);

public:
	virtual int GetRunState(void);
public:
	virtual void Tick(const TimeInfo &rTimeInfo);
private:
	virtual void Tick_Logic(const TimeInfo & rTimeInfo);
public:
	virtual InvokerPtr InitMyself(void);

protected:
	void Initialize(void);

protected:
	enum
	{
		STATUS_OPENED = 0,
		STATUS_READY = 1, // ��ս˫������,
		STATUS_LINE, // ����
		STATUS_SELECTTARGET,//ѡ��Ŀ��
		STATUS_MARCH, // �о�
		STATUS_COMBAT, // ���
		STATUS_CLOSED,
	};
protected:
	int m_nStatus;

protected:
	bool GetOpened(void) const {return (m_nStatus == STATUS_OPENED);}

public:
	//virtual bool IsAllowPK(void){return false;}; //�����Ƿ����PK

public:
	virtual bool GetActive(void) const;
	virtual void SetActive(void);
	virtual void OnObjEnter(int nID);
	virtual void OnObjLeave(int nID);
	virtual void OnObjEnterCombat(int nID);
	virtual void OnObjLeaveCombat(int nID);
	virtual void OnObjDie(int nID,int nKillerId);
	virtual bool IsCopyScene(void) const {return true;}
	virtual bool IsCanEnterByGuid(const int64 &rGuid);
	virtual int GetCopySceneDifficulty(void) const { return GetDifficulty(); }
	virtual int GetCopySceneTier(void) const { return m_nTier; }
	virtual void SetCopySceneTier(int val) { m_nTier = val; }

private:
	void CleanUpObjList(void);

private:
	bsarray<tint32, MAX_ARRANGE_COUNT> m_lstAttack; // �������ĳ�Ա�б�
	bsarray<tint32, MAX_ARRANGE_COUNT> m_lstDefence; // �������ĳ�Ա�б�
private:
	void InitMarchObj(const March& rMarch);
	void InitAttackObj(const March& rMarch);
	void InitDefenceObj(const March& rMarch);
	void SetAttackMarchLine();
	void SetDefenceMarchLine();
	void StartAttachMarch();
	void StartDefenceMarch();
	//void InitNpcObj();

public:
	tint32 GetSceneArrangeSelectTarget(tint32 nArrangeId,bool bAttack);

protected:
	void Tick_Close(const TimeInfo &rTimeInfo);
protected:
	int m_nTimeClose;


protected:
	void Open(int nPlayType, int nDifficulty, int nLevel);
	void Close(void);

protected:
	int CalcExistTime(void);

public:

	int GetDifficulty(void) const { return m_nDifficulty; }
	void SetDifficulty(int val) { m_nDifficulty = val; }
	int GetStartTime(void) const { return m_nStartTime; }
	void SetStartTime(int val) { m_nStartTime = val; }
	int GetStar(void) const { return m_nStar; }
	void SetStar(int val) { m_nStar = val; }
	int GetResult(void) const { return m_nResult; }
	void SetResult(int val) { m_nResult = val; }
	int GetDieCount(void) const { return m_DieCount; }
	void SetDieCount(int val) { m_DieCount = val; }
	virtual int GetLevel(void) const { return m_nLevel; }
	virtual void SetLevel(int val) { m_nLevel = val; }
private:
	int m_nDifficulty;		//�Ѷ� 1,2,3
	int m_nStartTime;		//������ʼʱ��
	int m_nStar;				//�Ǽ�
	int m_DieCount;			//��¼�����ܴ���
	int m_nResult;			//�����0ʧ��1ʤ��2ƽ��
	int m_nTier;				//��Σ����ڼ��㸱��npc����
	int m_nLevel;			//��������Ӧ�ȼ�
	int m_nExistTime;

	March m_AttackMarch;
	March m_DefenceMarch;

protected:
	int m_nWaitCloseTime;
	int m_nHeartbeatTime;

public:
	virtual void HandleMessage(const MarchEnterSceneMsg &rMsg);
	virtual void HandleMessage(const UserSkillMsg &rMsg);
	virtual void HandleMessage(const ReqBattleInfoMsg &rMsg);
	virtual void HandleMessage(const ReqObjListMsg &rMsg);
public:
	// ս����ص���Ϣ��
	virtual void HandleMessage(const ReqSetRobotOpenMsg& rMsg);

public:
	int GetCopySceneLevel( );
};

POOLDEF_DECL(CopyScene);
BSARRAY_ASSIGN_DECL(tint32, MAX_ARRANGE_COUNT);
typedef GeneralInvoker<CopyScene, 125, 30000> GeneralCopySceneInvoker;

#endif
