#include <time.h>
#include "ItemLogicManager.h"
#include "player/Player.h"
#include "InventoryManager.h"
#include "error_def.h"
#include "GameDataConfig.h"


ItemLogicManager::ItemLogicManager(Player *pPlayer)
: BaseManager(pPlayer)
{
}

ItemLogicManager::~ItemLogicManager(void)
{
}


void ItemLogicManager::Init()
{

}

void ItemLogicManager::LoadDB(DB_Player *pdbPlayer)
{

}
void ItemLogicManager::SaveDB(DB_Player *pdbPlayer)
{
}
/////////////////////


int ItemLogicManager::GetItemTypeByIndex(int nItemIndex)
{


	return 0;
}

bool ItemLogicManager::HasItemByIndex(int nItemIndex, int nParam)
{
	if (nItemIndex == ITEMTYPE_GOLD)
	{
		if (m_pPlayer->GetGold() > 0)
		{
			return true;
		}
	}
	else if (nItemIndex == ITEMTYPE_CASH)
	{
		if (m_pPlayer->GetCash() > 0)
		{
			return true;
		}
	}
	else if (nItemIndex == ITEMTYPE_POWER)
	{
		if (m_pPlayer->GetPower() > 0)
		{
			return true;
		}
	}
	else if (nItemIndex == ITEMTYPE_QI)
	{
		if (m_pPlayer->GetQi() > 0)
		{
			return true;
		}
	}
	else if (nItemIndex == ITEMTYPE_PLAYEREXP)
	{
		if (m_pPlayer->GetExp() > 0)
		{
			return true;
		}
	}
	
	return false;
}


int64 ItemLogicManager::GetItemCount(int nItemIndex, int nParam )
{
	if (nItemIndex == ITEMTYPE_GOLD)
	{
		return m_pPlayer->GetGold();
	}
	else if (nItemIndex == ITEMTYPE_CASH)
	{
		return m_pPlayer->GetCash();
	}
	else if (nItemIndex == ITEMTYPE_POWER)
	{
		return m_pPlayer->GetPower();
	}
	else if (nItemIndex == ITEMTYPE_QI)
	{
		return m_pPlayer->GetQi();
	}
	else if (nItemIndex == ITEMTYPE_PLAYEREXP)
	{
		return m_pPlayer->GetExp();
	}
	

	return 0;
}

void ItemLogicManager::AddItem(int nItemIndex, int nItemCount,CASH_TYPE_DEF cashtype, bool bUpdate, int nParam)
{
	if (nItemIndex == ITEMTYPE_GOLD)
	{
		m_pPlayer->AddGold(nItemCount);
	}
	else if (nItemIndex == ITEMTYPE_CASH)
	{
		m_pPlayer->AddCash(nItemCount,cashtype);
	}
	else if (nItemIndex == ITEMTYPE_POWER)
	{
		m_pPlayer->AddPowerNolimit(nItemCount);
	}
	else if (nItemIndex == ITEMTYPE_QI)
	{
		m_pPlayer->AddQiNolimit(nItemCount);
	}
	else if (nItemIndex == ITEMTYPE_PLAYEREXP)
	{
		m_pPlayer->AddExp(nItemCount);
	}
	
	
}

void ItemLogicManager::RemoveItem(int nItemIndex, int nItemCount, int nParam)
{
	if (nItemIndex == ITEMTYPE_GOLD)
	{
		m_pPlayer->SubGold(nItemCount);
	}
	else if (nItemIndex == ITEMTYPE_CASH)
	{
		m_pPlayer->SubCash(nItemCount,CASH_TYPE_COST_DEFAULT);
	}
	else if (nItemIndex == ITEMTYPE_POWER)
	{
		m_pPlayer->SubPower(nItemCount);
	}
	else if (nItemIndex == ITEMTYPE_QI)
	{
		m_pPlayer->SubQi(nItemCount);
	}
	else if (nItemIndex == ITEMTYPE_PLAYEREXP)
	{
		m_pPlayer->SubExp(nItemCount);
	}
	
}

void ItemLogicManager::DeleteItemByType( int nItemIndex )
{
	
}


