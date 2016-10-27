#include "InventoryManager.h"
#include "player/Player.h"
#include "error_def.h"
#include "../gamed/event/MessageDef.h"
#include "GameDataConfig.h"

InventoryManager::InventoryManager(Player *player)
:BaseManager(player)
, m_nAllocId(0)
, m_timeInventory(0)
{

}

InventoryManager::~InventoryManager(void)
{
	ClearInventory();
}

void InventoryManager::Init()
{
	m_timeInventory = 0;
	vector<int>& vecItem = GameDataConfig::Instance().GetItem();
	for (size_t i = 0; i < vecItem.size(); i++)
	{
		AddInventory(vecItem[i],1);
	}
	
}

void InventoryManager::LoadDB(DB_Player *pdbPlayer)
{
	DB_InventoryManager *pdbInventoryManager = pdbPlayer->mutable_inventorymanager();
	if (pdbInventoryManager == NULL)
	{
		return;
	}
	
	for (int i = 0; i < pdbInventoryManager->inventorys_size(); i++)
	{
		DB_Inventory *pdbInventory = pdbInventoryManager->mutable_inventorys(i);
		Inventory *pInventory = new Inventory();
		pInventory->SetInventoryId(pdbInventory->id());
		pInventory->SetIndex(pdbInventory->index());
		pInventory->SetCount(pdbInventory->count());
		m_mapInventory[pInventory->GetInventoryId()] = pInventory;
	}

	m_nAllocId = pdbInventoryManager->allocid();

	for (int i = 0; i< pdbInventoryManager->buyrecords_size(); i++)
	{
		DB_BuyRecord *pdbBuyRecord = pdbInventoryManager->mutable_buyrecords(i);
		BuyRecord *pBuyRecord = new BuyRecord();
		pBuyRecord->SetIndex(pdbBuyRecord->index());
		pBuyRecord->SetCount(pdbBuyRecord->count());
		AddBuyRecordTotal(pBuyRecord);
	}

	for (int i = 0; i< pdbInventoryManager->buyrecordsday_size(); i++)
	{
		DB_BuyRecord *pdbBuyRecord = pdbInventoryManager->mutable_buyrecordsday(i);
		BuyRecord *pBuyRecord = new BuyRecord();
		pBuyRecord->SetIndex(pdbBuyRecord->index());
		pBuyRecord->SetCount(pdbBuyRecord->count());
		AddBuyRecordDay(pBuyRecord);
	}

	m_timeInventory = pdbInventoryManager->timeinventory();
}

void InventoryManager::SaveDB(DB_Player *pdbPlayer)
{
	DB_InventoryManager *pdbInventoryManager = pdbPlayer->mutable_inventorymanager();
	if (pdbInventoryManager == NULL)
	{
		return;
	}

	for (map<int,Inventory*>::iterator iter = m_mapInventory.begin(); iter != m_mapInventory.end(); iter ++)
	{
		Inventory *pInventory = (Inventory*)iter->second;
		DB_Inventory *pdbInventory = pdbInventoryManager->add_inventorys();

		pdbInventory->set_id(pInventory->GetInventoryId());
		pdbInventory->set_index(pInventory->GetIndex());
		pdbInventory->set_count(pInventory->GetCount());
	}

	pdbInventoryManager->set_allocid(m_nAllocId);

	for (map<int, BuyRecord*>::iterator iter = m_mapBuyRecordTotal.begin(); iter != m_mapBuyRecordTotal.end(); iter++)
	{
		BuyRecord *pBuyRecord = (BuyRecord*)iter->second;
		DB_BuyRecord *pdbBuyRecord = pdbInventoryManager->add_buyrecords();

		pdbBuyRecord->set_index(pBuyRecord->GetIndex());
		pdbBuyRecord->set_count(pBuyRecord->GetCount());
	}

	for (map<int, BuyRecord*>::iterator iter = m_mapBuyRecordDay.begin(); iter != m_mapBuyRecordDay.end(); iter++)
	{
		BuyRecord *pBuyRecord = (BuyRecord*)iter->second;
		DB_BuyRecord *pdbBuyRecord = pdbInventoryManager->add_buyrecordsday();

		pdbBuyRecord->set_index(pBuyRecord->GetIndex());
		pdbBuyRecord->set_count(pBuyRecord->GetCount());
	}

	pdbInventoryManager->set_timeinventory(m_timeInventory);
}

void InventoryManager::OnLogin()
{
	CheckBuyRecordDay();
}

void InventoryManager::CheckBuyRecordDay()
{
	if (m_timeInventory == 0)
	{
		ClearBuyRecordDay();
		m_timeInventory = time(NULL);
		return;
	}
	else
	{
		time_t	timeNow		= time(NULL);
		tm		tmNow		= *localtime(&timeNow);
		tm		tmInventory	= *localtime(&m_timeInventory);
		if (tmNow.tm_year != tmInventory.tm_year || tmNow.tm_yday != tmInventory.tm_yday)
		{
			ClearBuyRecordDay();
			m_timeInventory = timeNow;
			return;
		}
	}

}

Inventory*	InventoryManager::AddInventory(int nIndex, int nCount, bool bUpdate)
{
	Inventory *pInventory = GetInventoryByIndex(nIndex);
	if (pInventory != NULL)
	{
		pInventory->AddCount(nCount);
	}
	else
	{
		pInventory = new Inventory();
		pInventory->SetInventoryId(AllocId());
		pInventory->SetIndex(nIndex);
		pInventory->SetCount(nCount);
		m_mapInventory[pInventory->GetInventoryId()] = pInventory;
	}
	
	return pInventory;
}

void InventoryManager::AddInventory(Inventory *pInventory)
{
	if (pInventory == NULL)
	{
		return;
	}

	map<int, Inventory*>::iterator iterFind = m_mapInventory.find(pInventory->GetInventoryId());
	if (iterFind != m_mapInventory.end())
	{
		Inventory *pInventory = (Inventory*)iterFind->second;
		if (pInventory != NULL)
		{
			delete pInventory;
		}
	}
	m_mapInventory[pInventory->GetInventoryId()] = pInventory;
}

void InventoryManager::RemoveInventoryById(int nInventoryId, int nCount, bool bUpdate)
{
	map<int, Inventory*>::iterator iterFind = m_mapInventory.find(nInventoryId);
	if (iterFind != m_mapInventory.end())
	{
		Inventory *pInventory = (Inventory*)iterFind->second;
		int nCurrentCnt = pInventory->GetCount();
		if (nCurrentCnt <= nCount)
		{
			m_mapInventory.erase(iterFind);
			delete pInventory;
		}
		else
		{
			pInventory->SetCount(nCurrentCnt - nCount);
		}
	
	}
}

void InventoryManager::RemoveInventoryByIndex(int nIndex, int nCount, bool bUpdate)
{
	int nCountRemove = nCount;
	int nInventoryId = 0;
	for (map<int, Inventory*>::iterator iter = m_mapInventory.begin(); iter != m_mapInventory.end(); iter++)
	{
		Inventory *pInventory = (Inventory*)iter->second;
		nInventoryId = pInventory->GetInventoryId();
		if (pInventory != NULL && pInventory->GetIndex() == nIndex)
		{
			int nCurrentCnt = pInventory->GetCount();
			if (nCurrentCnt <= nCountRemove)
			{
				m_mapInventory.erase(iter);
				delete pInventory;
				nCountRemove -= nCurrentCnt;

				if (nCountRemove <= 0)
				{
					break;
				}
			}
			else
			{
				pInventory->SetCount(nCurrentCnt - nCountRemove);
				break;
			}

			
		}
	}
}

bool InventoryManager::HasInventoryById(int nInventoryId)
{
	map<int,Inventory*>::iterator iterFind = m_mapInventory.find(nInventoryId);
	if (iterFind == m_mapInventory.end())
		return false;
	else
		return true;
}

bool InventoryManager::HasInventoryByIndex(int nIndex)
{
	for (map<int, Inventory*>::iterator iter = m_mapInventory.begin(); iter != m_mapInventory.end(); iter++)
	{
		Inventory *pInventory = (Inventory*)iter->second;
		if (pInventory != NULL && pInventory->GetIndex() == nIndex)
		{
			return true;
		}
	}
	return false;
}

Inventory* InventoryManager::GetInventoryById(int nInventoryId)
{
	map<int,Inventory*>::iterator iterFind = m_mapInventory.find(nInventoryId);
	if (iterFind == m_mapInventory.end())
		return NULL;
	else
		return iterFind->second;
}

Inventory* InventoryManager::GetInventoryByIndex(int nIndex)
{
	for (map<int, Inventory*>::iterator iter = m_mapInventory.begin(); iter != m_mapInventory.end(); iter++)
	{
		Inventory *pInventory = (Inventory*)iter->second;
		if (pInventory != NULL && pInventory->GetIndex() == nIndex)
		{
			return pInventory;
		}
	}
	return NULL;
}

int InventoryManager::GetCountByIndex(int nIndex)
{
	int nCount = 0;
	for (map<int, Inventory*>::iterator iter = m_mapInventory.begin(); iter != m_mapInventory.end(); iter++)
	{
		Inventory *pInventory = (Inventory*)iter->second;
		if (pInventory == NULL)
		{
			continue;
		}
		if (pInventory->GetIndex() == nIndex)
		{
			nCount += pInventory->GetCount();
		}
	}
	return nCount;
}

void InventoryManager::ClearInventory()
{
	for (map<int,Inventory*>::iterator iter = m_mapInventory.begin(); iter != m_mapInventory.end(); iter++)
	{
		Inventory *pInventory = (Inventory*)iter->second;
		if (pInventory != NULL)
		{
			delete pInventory;
		}
	}
	m_mapInventory.clear();
}

BuyRecord* InventoryManager::AddBuyRecordTotal(int nIndex, int nCount)
{
	BuyRecord *pBuyRecored = GetBuyRecordTotal(nIndex);
	if (pBuyRecored != NULL)
	{
		pBuyRecored->AddCount(nCount);
		return pBuyRecored;
	}
	else
	{
		pBuyRecored = new BuyRecord();
		pBuyRecored->SetIndex(nIndex);
		pBuyRecored->SetCount(nCount);
		m_mapBuyRecordTotal[pBuyRecored->GetIndex()] = pBuyRecored;
		return pBuyRecored;
	}
}

void InventoryManager::AddBuyRecordTotal(BuyRecord *pBuyRecord)
{
	if (pBuyRecord == NULL)
	{
		return;
	}

	map<int, BuyRecord*>::iterator iterFind = m_mapBuyRecordTotal.find(pBuyRecord->GetIndex());
	if (iterFind != m_mapBuyRecordTotal.end())
	{
		BuyRecord *pBuyRecordTemp = (BuyRecord*)iterFind->second;
		if (pBuyRecordTemp != NULL)
		{
			delete pBuyRecordTemp;
		}
	}
	m_mapBuyRecordTotal[pBuyRecord->GetIndex()] = pBuyRecord;
}

BuyRecord* InventoryManager::GetBuyRecordTotal(int nIndex)
{
	map<int,BuyRecord*>::iterator iterFind = m_mapBuyRecordTotal.find(nIndex);
	if (iterFind == m_mapBuyRecordTotal.end())
		return NULL;
	else
		return iterFind->second;
}

int InventoryManager::GetBuyRecordCountTotal(int nIndex)
{
	BuyRecord *pBuyRecord = GetBuyRecordTotal(nIndex);
	if (pBuyRecord == NULL)
	{
		return 0;
	}
	return pBuyRecord->GetCount();
}

void InventoryManager::RemoveBuyRecordTotal(int nIndex, int nCount)
{
	map<int, BuyRecord*>::iterator iterFind = m_mapBuyRecordTotal.find(nIndex);
	if (iterFind != m_mapBuyRecordTotal.end())
	{
		BuyRecord *pBuyRecord = (BuyRecord*)iterFind->second;
		int nCurrentCnt = pBuyRecord->GetCount();
		if (nCurrentCnt <= nCount)
		{
			m_mapBuyRecordTotal.erase(iterFind);
			delete pBuyRecord;
		}
		else
		{
			pBuyRecord->SetCount(nCurrentCnt - nCount);
		}
	}
}

void InventoryManager::ClearBuyRecordTotal(int nIndex)
{
	for (map<int,BuyRecord*>::iterator iter = m_mapBuyRecordTotal.begin(); iter != m_mapBuyRecordTotal.end(); iter++)
	{
		BuyRecord *pBuyRecord = (BuyRecord*)iter->second;
		if (pBuyRecord != NULL)
		{
			delete pBuyRecord;
		}
	}
	m_mapBuyRecordTotal.clear();
}

////////////////buyrecord begin/////////////////////////////////
BuyRecord* InventoryManager::AddBuyRecordDay(int nIndex, int nCount)
{
	BuyRecord *pBuyRecored = GetBuyRecordDay(nIndex);
	if (pBuyRecored != NULL)
	{
		pBuyRecored->AddCount(nCount);
		return pBuyRecored;
	}
	else
	{
		pBuyRecored = new BuyRecord();
		pBuyRecored->SetIndex(nIndex);
		pBuyRecored->SetCount(nCount);
		m_mapBuyRecordDay[pBuyRecored->GetIndex()] = pBuyRecored;
		return pBuyRecored;
	}
}

void InventoryManager::AddBuyRecordDay(BuyRecord *pBuyRecord)
{
	if (pBuyRecord == NULL)
	{
		return;
	}

	map<int, BuyRecord*>::iterator iterFind = m_mapBuyRecordDay.find(pBuyRecord->GetIndex());
	if (iterFind != m_mapBuyRecordDay.end())
	{
		BuyRecord *pBuyRecordTemp = (BuyRecord*)iterFind->second;
		if (pBuyRecordTemp != NULL)
		{
			delete pBuyRecordTemp;
		}
	}
	m_mapBuyRecordDay[pBuyRecord->GetIndex()] = pBuyRecord;
}

BuyRecord* InventoryManager::GetBuyRecordDay(int nIndex)
{
	map<int,BuyRecord*>::iterator iterFind = m_mapBuyRecordDay.find(nIndex);
	if (iterFind == m_mapBuyRecordDay.end())
		return NULL;
	else
		return iterFind->second;
}

int InventoryManager::GetBuyRecordCountDay(int nIndex)
{
	BuyRecord *pBuyRecord = GetBuyRecordDay(nIndex);
	if (pBuyRecord == NULL)
	{
		return 0;
	}
	return pBuyRecord->GetCount();
}

void InventoryManager::RemoveBuyRecordDay(int nIndex, int nCount)
{
	map<int, BuyRecord*>::iterator iterFind = m_mapBuyRecordDay.find(nIndex);
	if (iterFind != m_mapBuyRecordDay.end())
	{
		BuyRecord *pBuyRecord = (BuyRecord*)iterFind->second;
		int nCurrentCnt = pBuyRecord->GetCount();
		if (nCurrentCnt <= nCount)
		{
			m_mapBuyRecordDay.erase(iterFind);
			delete pBuyRecord;
		}
		else
		{
			pBuyRecord->SetCount(nCurrentCnt - nCount);
		}
	}
}

void InventoryManager::ClearBuyRecordDay()
{
	for (map<int,BuyRecord*>::iterator iter = m_mapBuyRecordDay.begin(); iter != m_mapBuyRecordDay.end(); iter++)
	{
		BuyRecord *pBuyRecord = (BuyRecord*)iter->second;
		if (pBuyRecord != NULL)
		{
			delete pBuyRecord;
		}
	}
	m_mapBuyRecordDay.clear();
}

///////////////////buy record end//////////////////////

void  InventoryManager::OnBox(int itemid)
{
	int itemlist[] = {210018,210012,210015,210010};
	bool bFlag = false;
	for (int i=0;i<4;i++)
	{
		if (itemid ==itemlist[i])
		{
			bFlag = true;
			break;
		}
	}
}


