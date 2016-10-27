#include "BattleTaskTbl.h"
#include "../common/DBC.h"
BattleTaskTbl BattleTaskTbl::m_tblBattleTask;
const char* BattleTaskTbl::szConfigFile = "Config/BattleTask.txt";
BattleTaskTbl::BattleTaskTbl(void)
{
}

BattleTaskTbl::~BattleTaskTbl(void)
{
	ClearTbl();
}

void BattleTaskTbl::LoadTbl()
{
	ClearTbl();

	DBCFile fileDBC(0);
	fileDBC.OpenFromTXT(szConfigFile);
	int nRow = fileDBC.GetRecordsNum();
	for (int i = 0; i < nRow; i++)
	{
		BattleTaskBase *pBattleTaskBase= new BattleTaskBase;
		if (pBattleTaskBase == NULL)
		{
			continue;
		}

		pBattleTaskBase->SetId(fileDBC.Search_Posistion(i, 0)->iValue);
		pBattleTaskBase->SetName(fileDBC.Search_Posistion(i, 1)->pString);
		pBattleTaskBase->SetDecId(fileDBC.Search_Posistion(i, 2)->iValue);
		pBattleTaskBase->SetOpenId(fileDBC.Search_Posistion(i, 3)->iValue);
		pBattleTaskBase->SetChainName(fileDBC.Search_Posistion(i, 4)->iValue);
		pBattleTaskBase->SetGuankaNum(fileDBC.Search_Posistion(i, 5)->iValue);
		pBattleTaskBase->SetDifficulty(fileDBC.Search_Posistion(i, 6)->iValue);
		pBattleTaskBase->SetNpcId(fileDBC.Search_Posistion(i, 7)->iValue);
		pBattleTaskBase->SetExp(fileDBC.Search_Posistion(i, 8)->iValue);
		pBattleTaskBase->SetGold(fileDBC.Search_Posistion(i, 9)->iValue);
		pBattleTaskBase->SetHeroExp(fileDBC.Search_Posistion(i, 10)->iValue);
		pBattleTaskBase->SetDropId1(fileDBC.Search_Posistion(i, 11)->iValue);
		pBattleTaskBase->SetDropId2(fileDBC.Search_Posistion(i, 12)->iValue);
		pBattleTaskBase->SetDropId3(fileDBC.Search_Posistion(i, 13)->iValue);
		pBattleTaskBase->SetDropId4(fileDBC.Search_Posistion(i, 14)->iValue);
		pBattleTaskBase->SetDropId5(fileDBC.Search_Posistion(i, 15)->iValue);
		pBattleTaskBase->SetDropId6(fileDBC.Search_Posistion(i, 16)->iValue);
		pBattleTaskBase->SetDropId7(fileDBC.Search_Posistion(i, 17)->iValue);
		pBattleTaskBase->SetDropId8(fileDBC.Search_Posistion(i, 18)->iValue);
		pBattleTaskBase->SetDropId9(fileDBC.Search_Posistion(i, 19)->iValue);
		pBattleTaskBase->SetDropId10(fileDBC.Search_Posistion(i, 20)->iValue);
		pBattleTaskBase->SetSpecialDrop(fileDBC.Search_Posistion(i, 21)->iValue);
		pBattleTaskBase->SetSpecailType(fileDBC.Search_Posistion(i, 22)->iValue);
		pBattleTaskBase->SetSpecailCount(fileDBC.Search_Posistion(i, 23)->iValue);
		pBattleTaskBase->SetLostExp(fileDBC.Search_Posistion(i, 24)->iValue);
		pBattleTaskBase->SetDifficultyC(fileDBC.Search_Posistion(i, 25)->iValue);
		pBattleTaskBase->SetHeroID(fileDBC.Search_Posistion(i, 26)->iValue);
		pBattleTaskBase->SetNeedVipLevel(fileDBC.Search_Posistion(i, 27)->iValue);
		pBattleTaskBase->SetClenPrice(fileDBC.Search_Posistion(i, 28)->iValue);

		m_mapTaskChain[pBattleTaskBase->GetChainName()].push_back(pBattleTaskBase->GetId());

		m_mapBattleTaskBase.insert(make_pair(pBattleTaskBase->GetId(), pBattleTaskBase));

		
	}
}

void BattleTaskTbl::ClearTbl()
{
	for (map<int,BattleTaskBase*>::iterator iter = m_mapBattleTaskBase.begin(); iter != m_mapBattleTaskBase.end(); iter++)
	{
		BattleTaskBase *pBattleTaskBase = (BattleTaskBase*)iter->second;
		if (pBattleTaskBase != NULL)
		{
			delete pBattleTaskBase;
		}
	}
	m_mapBattleTaskBase.clear();

	map<int,vector<int> >::iterator iter;
	for (iter = m_mapTaskChain.begin();iter != m_mapTaskChain.end();iter++)
	{
		iter->second.clear();
	}
	m_mapTaskChain.clear();
}

BattleTaskBase* BattleTaskTbl::GetBattleTaskBase(int nIndex)
{
	map<int,BattleTaskBase*>::iterator iterFind = m_mapBattleTaskBase.find(nIndex);
	if (iterFind != m_mapBattleTaskBase.end())
	{
		return (BattleTaskBase*)iterFind->second;
	}
	return NULL;
}


