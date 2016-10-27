#include <math.h>
#include "BattleManager.h"
#include "../common/string-util.h"
#include "player/Player.h"

#include "error_def.h"
#include "BattleTaskTbl.h"
#include "GameDataConfig.h"


//////////////////battle enity///////////////////
void BattleEnity::AddLife(int nLifeAdd)
{
	if (nLifeAdd <= 0)
	{
		return;
	}

	m_nLife += nLifeAdd;
}

void BattleEnity::SubLife(int nLifeSub)
{
	if (nLifeSub <= 0)
	{
		return;
	}

	m_nLife -= nLifeSub;
	if (m_nLife < 0)
	{
		m_nLife = 0;
	}
}

void BattleEnity::AddAttack(int nAttackAdd)
{
	if (nAttackAdd <= 0)
	{
		return;
	}

	m_nAttack += nAttackAdd;
}

void BattleEnity::SubAttack(int nAttackSub)
{
	if (nAttackSub <= 0)
	{
		return;
	}

	m_nAttack -= nAttackSub;
	if (m_nAttack < 0)
	{
		m_nAttack = 0;
	}
}

void BattleEnity::AddDefence(int nDefenceAdd)
{
	if (nDefenceAdd <= 0)
	{
		return;
	}

	m_nDefence += nDefenceAdd;
}

void BattleEnity::SubDefence(int nDefenceSub)
{
	if (nDefenceSub <= 0)
	{
		return;
	}
	m_nDefence -= nDefenceSub;
	if (m_nDefence < 0)
	{
		m_nDefence = 0;
	}
}

void BattleEnity::AddInt(int nIntAdd)
{
	if (nIntAdd <= 0)
	{
		return;
	}

	m_nInt += nIntAdd;
}

void BattleEnity::SubInt(int nIntSub)
{
	if (nIntSub <= 0)
	{
		return;
	}

	m_nInt -= nIntSub;
	if (m_nInt < 0)
	{
		m_nInt = 0;
	}
}
int BattleEnity::GetSkillLevel(int nSkillId)
{
	for (size_t i = 0; i < m_vecSkill.size(); i++)
	{
		if (m_vecSkill[i] == nSkillId)
		{
			return m_vecSkillLvl[i];
		}
	}

	return -1;
}

int	BattleEnity::ProcessBySkillType(int nSkillType, int nSkillValue)
{
	if (nSkillType == ESKILLTYPE_ATTACK)
	{
		SubLife(nSkillValue);
		return -nSkillValue;
	}
	else if (nSkillType == ESKILLTYPE_ATTACKBUF)
	{
		AddAttack(nSkillValue);
		return nSkillValue;
	}
	else if (nSkillType == ESKILLTYPE_DEFENCEBUF)
	{
		AddDefence(nSkillValue);
		return nSkillValue;
	}
	else if (nSkillType == ESKILLTYPE_INTBUF)
	{
		AddInt(nSkillValue);
		return nSkillValue;
	}
	else if (nSkillType == ESKILLTYPE_LIFBUF)
	{
		AddLife(nSkillValue);
		return nSkillValue;
	}

	return 0;
}

///////////////////////battlemanager///////////////////////////////////

BattleManager::BattleManager(Player *player)
: BaseManager(player)
, m_nOrderSelf(0)
, m_nOrderOther(0)
, m_nRoundCount(0)
, m_nLostEnity(0)
{

}
BattleManager::~BattleManager(void)
{
	ClearBattleSelf();
	ClearBattleOther();
}

void BattleManager::Init()
{

}

void BattleManager::LoadDB(DB_Player *pdbPlayer)
{

}
void BattleManager::SaveDB(DB_Player *pdbPlayer)
{
}

#define BATTLE_COL_COUNT 3
#define BATTLE_ARRANGE_COUNT 9
int ARRANGEPOS[BATTLE_ARRANGE_COUNT] = {1,4,7,2,5,8,3,6,9};
vector<BattleEnity*> BattleManager::GetEnityByCol(bool bSelf, int nCol)
{
	vector<BattleEnity*> vecBattleEnity;
	if (bSelf)
	{
		for (int i = 0; i < BATTLE_COL_COUNT; i++)
		{
			int nPos = ARRANGEPOS[nCol * BATTLE_COL_COUNT + i] - 1;
			if (nPos >= (int)m_vecBattleSelf.size())
			{
				continue;
			}
			if (m_vecBattleSelf[nPos] != NULL)
			{
				vecBattleEnity.push_back(m_vecBattleSelf[nPos]);
			}
		}
	}
	else
	{
		for (int i = 0; i < BATTLE_COL_COUNT; i++)
		{
			int nPos = ARRANGEPOS[nCol * BATTLE_COL_COUNT + i] - 1;
			if (nPos >= (int)m_vecBattleOther.size())
			{
				continue;
			}
			if (m_vecBattleOther[nPos] != NULL)
			{
				vecBattleEnity.push_back(m_vecBattleOther[nPos]);
			}
		}
	}
	return vecBattleEnity;
}

BattleEnity* BattleManager::GetBattleAttack(bool bSelf)
{
	if (bSelf)
	{
		for (size_t i = m_nOrderSelf; i < m_vecBattleSelf.size(); i++ )
		{
			m_nOrderSelf++;
			if (m_vecBattleSelf[i] != NULL)
			{
				return m_vecBattleSelf[i];
			}
		}
	}
	else
	{
		for (size_t i = m_nOrderOther; i < m_vecBattleOther.size(); i++ )
		{
			m_nOrderOther++;
			if (m_vecBattleOther[i] != NULL)
			{
				return m_vecBattleOther[i];
			}
		}
	}
	
	return NULL;
}

vector<BattleEnity*> BattleManager::GetBattleEnemySingle(bool bSelf, int nAttackPos)
{
	int nAttackCol = (nAttackPos- 1 ) % BATTLE_COL_COUNT;
	if (nAttackCol < 0)
	{
		nAttackCol = 0;
	}
	if (nAttackCol > BATTLE_COL_COUNT)
	{
		nAttackCol = BATTLE_COL_COUNT - 1;
	}

	int nStart = nAttackCol * BATTLE_COL_COUNT;
	vector<BattleEnity*> vecBattleDefence;
	if (bSelf)
	{
		for (int i = 0; i < BATTLE_ARRANGE_COUNT; i++ )
		{
			int nPos = ARRANGEPOS[nStart] - 1 ;
			if (nPos < 0 || nPos >= (int)m_vecBattleSelf.size())
			{
				continue;
			}
			if (m_vecBattleSelf[nPos] != NULL )
			{
				vecBattleDefence.push_back(m_vecBattleSelf[nPos]);
				break;
			}
			nStart++;
			nStart %= BATTLE_ARRANGE_COUNT;
		}
	}
	else
	{
		for (int i = 0; i < BATTLE_ARRANGE_COUNT; i++ )
		{
			int nPos = ARRANGEPOS[nStart] - 1 ;
			if (nPos < 0 || nPos >= (int)m_vecBattleOther.size())
			{
				continue;
			}
			if (m_vecBattleOther[nPos] != NULL )
			{
				vecBattleDefence.push_back(m_vecBattleOther[nPos]);
				break;
			}
			nStart++;
			nStart %= BATTLE_ARRANGE_COUNT;
		}
	}

	return vecBattleDefence;
}

vector<BattleEnity*> BattleManager::GetBattleEnemyAll(bool bSelf, int nAttackPos)
{
	vector<BattleEnity*> vecBattleDefence;
	int nPosition = nAttackPos - 1;
	if (nPosition < 0 || nPosition >= (int)m_vecBattleSelf.size())
	{
		return vecBattleDefence;
	}
	if (bSelf)
	{
		for (size_t i = 0; i < m_vecBattleSelf.size(); i++)
		{
			BattleEnity *pBattleEnity = m_vecBattleSelf[nPosition];
			if (pBattleEnity != NULL)
			{
				vecBattleDefence.push_back(pBattleEnity);
			}
			nPosition ++;
			nPosition %= m_vecBattleSelf.size();
		}
		return vecBattleDefence;
	}
	else
	{
		for (size_t i = 0; i < m_vecBattleOther.size(); i++)
		{
			BattleEnity *pBattleEnity = m_vecBattleOther[nPosition];
			if (pBattleEnity != NULL)
			{
				vecBattleDefence.push_back(pBattleEnity);
			}
			nPosition ++;
			nPosition %= m_vecBattleSelf.size();
		}
		return vecBattleDefence;
	}
	return vecBattleDefence;
}

vector<BattleEnity*> BattleManager::GetBattleEnemyLine(bool bSelf, int nAttackPos)
{
	vector<int> vecDefenceCol;
	int nAttackCol = (nAttackPos -1) % BATTLE_COL_COUNT;
	vecDefenceCol.push_back(nAttackCol);
	for (int i = 0; i < BATTLE_COL_COUNT; i++)
	{
		if (i != nAttackCol)
		{
			vecDefenceCol.push_back(i);
		}
	}

	vector<BattleEnity*> vecBattleDefence;
	for (vector<int>::iterator iter = vecDefenceCol.begin(); iter != vecDefenceCol.end(); iter++)
	{
		vecBattleDefence = GetEnityByCol(bSelf, *iter);
		if (vecBattleDefence.size() > 0)
		{
			return vecBattleDefence;
		}
	}

	return vecBattleDefence;
}

vector<BattleEnity*> BattleManager::GetBattleEnemyRand(bool bSelf, int nAttackPos)
{
	vector<BattleEnity*> vecBattleDefence;

	if (bSelf)
	{
		for (vector<BattleEnity *>::iterator iter = m_vecBattleSelf.begin(); iter != m_vecBattleSelf.end(); iter++)
		{
			BattleEnity *pBattleEnity = (BattleEnity*)(*iter);
			if (pBattleEnity != NULL)
			{
				vecBattleDefence.push_back(pBattleEnity);
			}
		}
		
	}
	else
	{
		for (vector<BattleEnity *>::iterator iter = m_vecBattleOther.begin(); iter != m_vecBattleOther.end(); iter++)
		{
			BattleEnity *pBattleEnity = (BattleEnity*)(*iter);
			if (pBattleEnity != NULL)
			{
				vecBattleDefence.push_back(pBattleEnity);
			}
		}
	}

	if (vecBattleDefence.size() <= 0)
	{
		return vecBattleDefence;
	}

	int nRand = rand()%vecBattleDefence.size();
	BattleEnity *pTemp = vecBattleDefence.at(nRand);
	vecBattleDefence.clear();
	vecBattleDefence.push_back(pTemp);
	return vecBattleDefence;
}

vector<BattleEnity*> BattleManager::GetBattleEnemy(bool bSelf, int nAttackPos, int nSkillRange)
{
	
	if (nSkillRange == ESKILLRANGE_SINGLE)
	{
		return GetBattleEnemySingle(bSelf,nAttackPos);
	}
	else if (nSkillRange == ESKILLRANGE_ALL)
	{
		return GetBattleEnemyAll(bSelf, nAttackPos);
	}
	else if (nSkillRange == ESKILLRANGE_LINE)
	{
		return GetBattleEnemyLine(bSelf, nAttackPos);
	}
	else if (nSkillRange == ESKILLRANGE_RAND)
	{
		return GetBattleEnemyRand(bSelf, nAttackPos);
	}
	
	return vector<BattleEnity*>();
}

void BattleManager::ClearBattleSelf()
{
	for (vector<BattleEnity*>::iterator iter = m_vecBattleSelf.begin(); iter != m_vecBattleSelf.end(); iter++)
	{
		BattleEnity *pBattleEnity = (BattleEnity*)(*iter);
		if (pBattleEnity != NULL)
		{
			delete pBattleEnity;
		}
	}
	m_vecBattleSelf.clear();
	
}

void BattleManager::ClearBattleOther()
{
	for (vector<BattleEnity*>::iterator iter = m_vecBattleOther.begin(); iter != m_vecBattleOther.end(); iter++)
	{
		BattleEnity *pBattleEnity = (BattleEnity*)(*iter);
		if (pBattleEnity != NULL)
		{
			delete pBattleEnity;
		}
	}
	m_vecBattleOther.clear();
}

int BattleManager::GetBattleSelf()
{
	int nCount = 0;
	for (vector<BattleEnity*>::iterator iter = m_vecBattleSelf.begin(); iter != m_vecBattleSelf.end(); iter++)
	{
		BattleEnity *pBattleEnity = (BattleEnity*)(*iter);
		if (pBattleEnity != NULL)
		{
			nCount ++;
		}
	}
	return nCount;
}

int BattleManager::GetBattleOther()
{
	int nCount = 0;
	for (vector<BattleEnity*>::iterator iter = m_vecBattleOther.begin(); iter != m_vecBattleOther.end(); iter++)
	{
		BattleEnity *pBattleEnity = (BattleEnity*)(*iter);
		if (pBattleEnity != NULL)
		{
			nCount ++;
		}
	}
	return nCount;
}

int BattleManager::GetBattleFirstEmpty(bool bSelf)
{
	if (bSelf)
	{
		for (size_t i = 0; i < m_vecBattleSelf.size(); i++)
		{
			BattleEnity *pBattleEnity = m_vecBattleSelf[i];
			if (pBattleEnity == NULL)
			{
				return i + 1;
			}
		}	
		return -1;
	}
	else 
	{
		for (size_t i = 0; i < m_vecBattleOther.size(); i++)
		{
			BattleEnity *pBattleEnity = m_vecBattleOther[i];
			if (pBattleEnity == NULL)
			{
				return i + 1;
			}
		}	
		return -1;
	}
}

bool BattleManager::CheckSelfRoundEnd()
{
	for (size_t i = m_nOrderSelf; i < m_vecBattleSelf.size(); i++ )
	{
		if (m_vecBattleSelf[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

bool BattleManager::CheckOtherRoundEnd()
{
	for (size_t i = m_nOrderOther; i < m_vecBattleOther.size(); i++ )
	{
		if (m_vecBattleOther[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

void BattleManager::CreateSelfBattle()
{
	ClearBattleSelf();
	
}

void BattleManager::CreateNPCFight(int NPCID)
{
	ClearBattleOther();
	

}

void BattleManager::CreateNpcBattle(int nTaskId)
{
	ClearBattleOther();
	
	
}

void BattleManager::CreatePlayerBattle(Player *pPlayerOther)
{
	ClearBattleOther();
}

void BattleManager::CreateSelfBloodBattle(BloodNpc *pBloodNpc)
{
	ClearBattleSelf();
	
}

void BattleManager::CreateNpcBloodBattle(BloodNpc *pBloodNpc)
{
}

int BattleManager::CalBattleHurt(int nSkillId, BattleEnity *pAttack, BattleEnity *pDefence, BattleEnity *pFirst)
{
	return 0;
	
}

int BattleManager::CalSkillSingleHurt(int nSkillId, BattleEnity *pAttack, BattleEnity *pDefence)
{
	
	return 0;
}

int BattleManager::CalSkillAllHurt(int nSkillId, BattleEnity *pAttack, BattleEnity *pDefence, BattleEnity *pFirst)
{
	return 0;
	
}

bool BattleManager::CalFirstAttack()
{
	
	return true;
}

void BattleManager::StartBattlePre(bool bSelf, vector<BattleEnity*> vecBattle, BattleReport *data)
{

	
}

void BattleManager::StartBattlePreSelf(BattleReport *data)
{
	StartBattlePre(true, m_vecBattleSelf, data);
}

void BattleManager::StartBattlePreOther(BattleReport *data)
{
	StartBattlePre(false, m_vecBattleOther, data);
}
int BattleManager::CreateUseSkill(BattleEnity *pAttack)
{
	
	return 0;
}

#define BATTLE_ROUND_MAX 10
bool BattleManager::BattleRoundOnce(BattleReport *data)
{
	return false;
}


bool BattleManager::ProcessBattleLogic(bool bSelfFirst, BattleReport *data)
{
	

	return true;

}

void BattleManager::CheckBattleEnity(bool bSelf)
{
	
}

bool BattleManager::ProcessFinialBattle()
{
	return 0;
}

int  BattleManager::StartFightWithNPC(int NPCID,BattleReport *data)
{
	CreateSelfBattle();
	CreateNPCFight(NPCID);

	StartBattlePreSelf(data);
	StartBattlePreOther(data);

	return StartBattle(data);
}

int BattleManager::StartBattle(BattleReport *data)
{
	

	return 1;
}

int BattleManager::StartBattleWithNpc(int nTaskId, BattleReport *data)
{
	CreateSelfBattle();
	CreateNpcBattle(nTaskId);

	StartBattlePreSelf(data);
	StartBattlePreOther(data);

	
	return StartBattle(data);
}

int BattleManager::StartBattleWithPlayer(Player *pPlayerOther, BattleReport *data)
{
	CreateSelfBattle();
	CreatePlayerBattle(pPlayerOther);

	//FillBattleArrange(data);

	StartBattlePreSelf(data);
	StartBattlePreOther(data);


	return StartBattle(data);
}


int BattleManager::StartBloodBattle(BloodNpc *pBloodNpc , BattleReport *data)
{
	CreateSelfBloodBattle(pBloodNpc);
	CreateNpcBloodBattle(pBloodNpc);

	StartBattlePreSelf(data);
	StartBattlePreOther(data);

	return StartBattle(data);
}



