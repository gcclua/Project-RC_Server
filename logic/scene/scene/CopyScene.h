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
		STATUS_READY = 1, // 交战双方进入,
		STATUS_LINE, // 布阵
		STATUS_SELECTTARGET,//选择目标
		STATUS_MARCH, // 行军
		STATUS_COMBAT, // 冲锋
		STATUS_CLOSED,
	};
protected:
	int m_nStatus;

protected:
	bool GetOpened(void) const {return (m_nStatus == STATUS_OPENED);}

public:
	//virtual bool IsAllowPK(void){return false;}; //场景是否可以PK

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
	bsarray<tint32, MAX_ARRANGE_COUNT> m_lstAttack; // 攻击方的成员列表
	bsarray<tint32, MAX_ARRANGE_COUNT> m_lstDefence; // 攻击方的成员列表
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
	int m_nDifficulty;		//难度 1,2,3
	int m_nStartTime;		//副本开始时间
	int m_nStar;				//星级
	int m_DieCount;			//记录死亡总次数
	int m_nResult;			//结果，0失败1胜利2平局
	int m_nTier;				//层次，用于计算副本npc属性
	int m_nLevel;			//副本自适应等级
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
	// 战斗相关的消息包
	virtual void HandleMessage(const ReqSetRobotOpenMsg& rMsg);

public:
	int GetCopySceneLevel( );
};

POOLDEF_DECL(CopyScene);
BSARRAY_ASSIGN_DECL(tint32, MAX_ARRANGE_COUNT);
typedef GeneralInvoker<CopyScene, 125, 30000> GeneralCopySceneInvoker;

#endif
