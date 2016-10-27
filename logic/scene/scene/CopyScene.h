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
public:
	virtual InvokerPtr InitMyself(void);

protected:
	void Initialize(void);

protected:
	enum
	{
		STATUS_READY = 0,
		STATUS_OPENED,
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
	virtual void OnScriptSkillStart(int nID,int nSkillId);
	virtual void OnScriptSkillBreak(int nID,int nSkillId);
	virtual void OnScriptSkillFininsh(int nID,int nSkillId);
	virtual bool OnScriptCheckUseSkill(int nID,int nSkillId);
	virtual void OnObjDie(int nID,int nKillerId);
	virtual bool OnObjBeforeHPChange(int nID, int nHP, int& nSpecialHP);
	virtual bool OnObjBeforeMPChange(int nID, int nMP, int& nSpecialMP);
	virtual void OnClientObjEnterOK(int nID);
	virtual bool IsCopyScene(void) const {return true;}
	virtual bool IsCanEnterByGuid(const int64 &rGuid);
	virtual int GetCopyScenePlayType(void) const { return GetPlayType(); }
	virtual int GetCopySceneDifficulty(void) const { return GetDifficulty(); }
	virtual int GetCopySceneTier(void) const { return m_nTier; }
	virtual void SetCopySceneTier(int val) { m_nTier = val; }
	virtual void OnObjTeleportChangeScene(int nID);

private:
	void CleanUpPlayersGuid(void);
private:
	bsarray<int64, COPYSCENEMAXPLAYERCOUNT> m_PlayersGuid;

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
	int GetPlayType(void) const { return m_nPlayType; }
	void SetPlayType(int val) { m_nPlayType = val; }
	int GetDifficulty(void) const { return m_nDifficulty; }
	void SetDifficulty(int val) { m_nDifficulty = val; }
	int GetScore(void) const { return m_nScore; }
	void SetScore(int val) { m_nScore = val; }
	int GetCarom(void) const { return m_nCarom; }
	void SetCarom(int val) { m_nCarom = val; }
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
	int GetSweepLevel(void) const { return m_nSweepLevel; }
	void SetSweepLevel(int val) { m_nSweepLevel = val; }
private:
	int m_nDifficulty;		//难度 1,2,3
	int m_nPlayType;			//单人或多人
	int m_nScore;			//评分
	int m_nCarom;			//最高连击
	int m_nStartTime;		//副本开始时间
	int m_nStar;				//星级
	int m_DieCount;			//记录死亡总次数
	int m_nResult;			//结果，0失败1胜利2平局
	int m_nTier;				//层次，用于计算副本npc属性
	int m_nLevel;			//副本自适应等级
	int m_nSweepLevel;			//副本可扫荡等级 0（不可扫荡） 1（可扫荡普通） 2（可扫荡普通+困难） 3（普通+困难+挑战全部可以扫荡）
	int m_nExistTime;


protected:
	int m_nDemandMin;
	int m_nDemandMax;
	int m_nWaitCloseTime;
	int m_nHeartbeatTime;

public:
	virtual void HandleMessage(const MarchEnterSceneMsg &rMsg);
public:
	int GetCopySceneLevel( );
};

POOLDEF_DECL(CopyScene);

typedef GeneralInvoker<CopyScene, 125, 30000> GeneralCopySceneInvoker;

#endif
