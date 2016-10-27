#ifndef _BATTLEMANAGER_H_
#define _BATTLEMANAGER_H_

#pragma once

#include <map>
#include "base/BaseManager.h"
#include "player/Player.h"
using namespace std;

class DB_Player;
enum ESKILLTYPE
{
	ESKILLTYPE_MIN = 1,
	ESKILLTYPE_ATTACK = 1,
	ESKILLTYPE_ATTACKBUF,
	ESKILLTYPE_DEFENCEBUF,
	ESKILLTYPE_INTBUF,
	ESKILLTYPE_LIFBUF,
	ESKILLTYPE_MAX,
};

enum ESKILLRANGE
{
	ESKILLRANGE_MIN = 1,
	ESKILLRANGE_SINGLE = 1,
	ESKILLRANGE_ALL,
	ESKILLRANGE_LINE,
	ESKILLRANGE_RAND,
	ESKILLRANGE_MAX,
};

class BattleEnity
{
public:
	BattleEnity(){}
	~BattleEnity(){}

	int		GetRoleId() const { return m_nRoleId; }
	void	SetRoleId(int val) { m_nRoleId = val; }

	int		GetPosition() const { return m_nPosition; }
	void	SetPosition(int val) { m_nPosition = val; }

	int		GetLife() const { return m_nLife; }
	void	SetLife(int val) { m_nLife = val; }
	void	AddLife(int nLifeAdd);
	void	SubLife(int nLifeSub);

	int		GetAttack() const { return m_nAttack; }
	void	SetAttack(int val) { m_nAttack = val; }
	void	AddAttack(int nAttackAdd);
	void	SubAttack(int nAttackSub);

	int		GetDefence() const { return m_nDefence; }
	void	SetDefence(int val) { m_nDefence = val; }
	void	AddDefence(int nDefenceAdd);
	void	SubDefence(int nDefenceSub);

	int		GetInt() const { return m_nInt; }
	void	SetInt(int val) { m_nInt = val; }
	void	AddInt(int nIntAdd);
	void	SubInt(int nIntSub);

	void	AddSkill(int nSkill) {m_vecSkill.push_back(nSkill);}
	vector<int>& GetSkill(){return m_vecSkill;}

	void	AddSkillLvl(int nSkill) {m_vecSkillLvl.push_back(nSkill);}
	vector<int>& GetSkillLvl(){return m_vecSkillLvl;}

	int		GetSkillLevel(int nSkillId);

	int		GetRow() { return (m_nPosition-1)/3; };
	int		GetCol() { return (m_nPosition-1)%3; };

	int		ProcessBySkillType(int nSkillType, int nSkillValue);
protected:
	int		m_nRoleId;
	int		m_nPosition;
	int		m_nLife;
	int		m_nAttack;
	int		m_nDefence;
	int		m_nInt;
	vector<int>	m_vecSkill;
	vector<int> m_vecSkillLvl;
};

class SseBattleReport;
class BattleRound;
class BattleReport;
class Player;
class BloodNpc;
class BattleManager : public BaseManager
{
public:
	BattleManager(Player *player);
	virtual ~BattleManager(void);

	void		Init();
	void		LoadDB(DB_Player *pdbPlayer);
	void		SaveDB(DB_Player *pdbPlayer);
	

	int			GetLostEnity() const { return m_nLostEnity; }
	void		SetLostEnity(int val) { m_nLostEnity = val; }


	vector<BattleEnity*>	GetEnityByCol(bool bSelf, int nCol);

	BattleEnity*			GetBattleAttack(bool bSelf);
	vector<BattleEnity*>	GetBattleEnemy(bool bSelf, int nAttackPos, int nSkillRange);
	vector<BattleEnity*>	GetBattleEnemySingle(bool bSelf, int nAttackPos);
	vector<BattleEnity*>	GetBattleEnemyAll(bool bSelf, int nAttackPos);
	vector<BattleEnity*>	GetBattleEnemyLine(bool bSelf, int nAttackPos);
	vector<BattleEnity*>	GetBattleEnemyRand(bool bSelf, int nAttackPos);

	
	void		ClearBattleSelf();
	void		ClearBattleOther();

	int			GetBattleSelf();
	int			GetBattleOther();
	int			GetBattleFirstEmpty(bool bSelf);

	bool		CheckSelfRoundEnd();
	bool		CheckOtherRoundEnd();

	void		CreateSelfBattle();
	void		CreateNpcBattle(int nTaskId);
	void		CreatePlayerBattle(Player *pPlayerOther);
	void        CreateNPCFight(int NPCID);
	
	void		CreateSelfBloodBattle(BloodNpc *pBloodNpc);
	void		CreateNpcBloodBattle(BloodNpc *pBloodNpc);

	int			CalBattleHurt(int nSkillId, BattleEnity *pAttack, BattleEnity *pDefence, BattleEnity *pFirst);
	int			CalSkillSingleHurt(int nSkillId, BattleEnity *pAttack, BattleEnity *pDefence);
	int			CalSkillAllHurt(int nSkillId, BattleEnity *pAttack, BattleEnity *pDefence, BattleEnity *pFirst);

	bool		CalFirstAttack();

	void 		StartBattlePre(bool bSelf, vector<BattleEnity*> vecBattle, BattleReport *data);
	void 		StartBattlePreSelf(BattleReport *data);
	void 		StartBattlePreOther(BattleReport *data);

	int			CreateUseSkill(BattleEnity *pAttack);

	bool		BattleRoundOnce(BattleReport *data);
	bool		ProcessBattleLogic(bool bSelfFirst, BattleReport *data);
	void		CheckBattleEnity(bool bSelf);
	bool		ProcessFinialBattle();

	int			CalcBattleStart(bool bSelfWin);
	int			StartBattle(BattleReport *data);
	int			StartBattleWithNpc(int nTaskId, BattleReport *data);
	int         StartFightWithNPC(int NPCID,BattleReport *data);
	int  		StartBattleWithPlayer(Player *pPlayerOther, BattleReport *data);
	int			StartBloodBattle(BloodNpc *pBloodNpc , BattleReport *data);

protected:
	vector<BattleEnity *>	m_vecBattleSelf;
	vector<BattleEnity *>	m_vecBattleOther;

	size_t					m_nOrderSelf;
	size_t					m_nOrderOther;
	int						m_nRoundCount;
	int						m_nLostEnity;
};


#endif
