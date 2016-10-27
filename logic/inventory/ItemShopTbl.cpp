#include <time.h>
#include "ItemShopTbl.h"
#include "../common/DBC.h"
#include "../event/SseShopItems.pb.h"
#include "../common/string-util.h"
#include "Player.h"
#include "InventoryManager.h"
#include "VipManager.h"
ItemShopTbl ItemShopTbl::m_tblItemShop;
const char* ItemShopTbl::szConfigFile = "Config/ItemShop.txt";
ItemShopTbl::ItemShopTbl(void)
{
}

ItemShopTbl::~ItemShopTbl(void)
{
	ClearTbl();
}

void ItemShopTbl::LoadTbl()
{
	ClearTbl();

	DBCFile fileDBC(0);
	fileDBC.OpenFromTXT(szConfigFile);
	int nRow = fileDBC.GetRecordsNum();
	for (int i = 0; i < nRow; i++)
	{
		ItemShopBase *pItemShopBase= new ItemShopBase;
		if (pItemShopBase == NULL)
		{
			continue;
		}

		pItemShopBase->SetId(fileDBC.Search_Posistion(i, 0)->iValue);
		string strSrc = fileDBC.Search_Posistion(i, 1)->pString;
		string strDst;
		gb2312ToUtf8(strSrc, strDst);
		pItemShopBase->SetItemname(strDst);
		pItemShopBase->SetCosttype(fileDBC.Search_Posistion(i, 2)->iValue);
		pItemShopBase->SetCostcount(fileDBC.Search_Posistion(i, 3)->iValue);
		pItemShopBase->SetIfnew(fileDBC.Search_Posistion(i, 4)->iValue);
		pItemShopBase->SetIfhot(fileDBC.Search_Posistion(i, 5)->iValue);
		pItemShopBase->SetSale(fileDBC.Search_Posistion(i, 6)->iValue);
		pItemShopBase->SetSelltype(fileDBC.Search_Posistion(i, 7)->iValue);
		string strOnTime = fileDBC.Search_Posistion(i, 8)->pString;
		string delims("/");
		vector<int> vecTime;
		tokenize_as_int(strOnTime, vecTime, delims);
		if (vecTime.size() >= 3)
		{
			tm tmOnTime;
			memset(&tmOnTime, 0, sizeof(tmOnTime));
			tmOnTime.tm_year = vecTime[0] - 1900;;
			tmOnTime.tm_mon = vecTime[1] - 1;
			tmOnTime.tm_mday = vecTime[2];
			time_t timeOnTimes = mktime(&tmOnTime);
			pItemShopBase->SetOntime((int)timeOnTimes);
		}
		else
		{
			pItemShopBase->SetOntime(0);
		}
		
		string strOffTime = fileDBC.Search_Posistion(i, 9)->pString;
		vecTime.clear();
		tokenize_as_int(strOffTime, vecTime, delims);
		if (vecTime.size() >= 3)
		{
			tm tmOffTime;
			memset(&tmOffTime, 0, sizeof(tm));
			tmOffTime.tm_year = vecTime[0] - 1900;
			tmOffTime.tm_mon = vecTime[1] - 1;
			tmOffTime.tm_mday = vecTime[2];
			time_t timeOffTimes = mktime(&tmOffTime);
			pItemShopBase->SetOfftime((int)timeOffTimes);
		}
		else
		{
			pItemShopBase->SetOfftime(0);
		}
		
		pItemShopBase->SetLevellimit(fileDBC.Search_Posistion(i, 10)->iValue);
		pItemShopBase->SetRequestvip(fileDBC.Search_Posistion(i, 11)->iValue);
		pItemShopBase->SetCountdaily(fileDBC.Search_Posistion(i, 12)->iValue);
		pItemShopBase->SetCounttotal(fileDBC.Search_Posistion(i, 13)->iValue);
		pItemShopBase->SetCountdailyp(fileDBC.Search_Posistion(i, 14)->iValue);
		pItemShopBase->SetCounttotalp(fileDBC.Search_Posistion(i, 15)->iValue);

		pItemShopBase->SetServerId(fileDBC.Search_Posistion(i, 16)->iValue);
		pItemShopBase->SetCltShow(fileDBC.Search_Posistion(i, 17)->iValue);

		m_mapItemShopBase.insert(make_pair(pItemShopBase->GetId(), pItemShopBase));

	}
}

void ItemShopTbl::ClearTbl()
{
	for (map<int,ItemShopBase*>::iterator iter = m_mapItemShopBase.begin(); iter != m_mapItemShopBase.end(); iter++)
	{
		ItemShopBase *pItemShopBase = (ItemShopBase*)iter->second;
		if (pItemShopBase != NULL)
		{
			delete pItemShopBase;
		}
	}
	m_mapItemShopBase.clear();
}

ItemShopBase* ItemShopTbl::GetItemShopBase(int nIndex)
{
	map<int,ItemShopBase*>::iterator iterFind = m_mapItemShopBase.find(nIndex);
	if (iterFind != m_mapItemShopBase.end())
	{
		return (ItemShopBase*)iterFind->second;
	}
	return NULL;
}

bool ItemShopTbl::CanOnTime(ItemShopBase* pItemShopBase)
{
	if (pItemShopBase == NULL)
	{
		return false;
	}
	
	if (pItemShopBase->GetOntime() == 0 && pItemShopBase->GetOfftime() == 0)
	{
		return true;
	}

	if (pItemShopBase->GetOntime()< 0 && pItemShopBase->GetOfftime() < 0)
	{
		return false;
	}

	time_t timeNow = time(NULL);
	if (timeNow < pItemShopBase->GetOntime())
	{
		return false;
	}
	if (timeNow > pItemShopBase->GetOfftime())
	{
		return false;
	}

	return true;
}

void ItemShopTbl::FillShopItems(Player *pPlayer, SseShopItems *data)
{
	if (pPlayer == NULL)
	{
		return;
	}
	InventoryManager *pInventoryManager = pPlayer->GetInventoryManager();
	if (pInventoryManager == NULL)
	{
		return;
	}

	VipManager *pVipManager = pPlayer->GetVipManager();
	if (pVipManager == NULL)
	{
		return;
	}

	for (map<int,ItemShopBase*>::iterator iter = m_mapItemShopBase.begin(); iter != m_mapItemShopBase.end(); iter++)
	{
		ItemShopBase *pItemShopBase = (ItemShopBase*)iter->second;

		/*if (pItemShopBase->GetCltShow() <= 0)
		{
			continue;
		}*/

		if (!CanOnTime(pItemShopBase))
		{
			continue;
		}

		if (pItemShopBase->GetRequestvip() > 0 &&
			pVipManager->GetVipLevel() + 5 < pItemShopBase->GetRequestvip())
		{
			continue;
		}

		if (pItemShopBase->GetCounttotalp() > 0 &&
			pInventoryManager->GetBuyRecordCountTotal(pItemShopBase->GetId()) >= pItemShopBase->GetCounttotalp())
		{
			continue;
		}

		if (pItemShopBase->GetCountdailyp() > 0 &&
			pInventoryManager->GetBuyRecordCountDay(pItemShopBase->GetId()) >= pItemShopBase->GetCountdailyp())
		{
			continue;
		}

		ShopItemData *pShopItemData = data->add_shopitems();
		if (pItemShopBase == NULL || pShopItemData == NULL)
		{
			continue;
		}         

		pShopItemData->set_id(pItemShopBase->GetId());
		pShopItemData->set_itemname(pItemShopBase->GetItemname());
		pShopItemData->set_costtype(pItemShopBase->GetCosttype());
		pShopItemData->set_costcount(pItemShopBase->GetCostcount());
		pShopItemData->set_ifnew(pItemShopBase->GetIfnew());
		pShopItemData->set_ifhot(pItemShopBase->GetIfhot());
		pShopItemData->set_sale(pItemShopBase->GetSale());
		pShopItemData->set_selltype(pItemShopBase->GetSelltype());
		pShopItemData->set_ontime(pItemShopBase->GetOntime());
		pShopItemData->set_offtime(pItemShopBase->GetOfftime());
		pShopItemData->set_levellimit(pItemShopBase->GetLevellimit());
		pShopItemData->set_requestvip(pItemShopBase->GetRequestvip());
		pShopItemData->set_countdaily(pItemShopBase->GetCountdaily());
		pShopItemData->set_counttotal(pItemShopBase->GetCounttotal());
		pShopItemData->set_countdailyp(pItemShopBase->GetCountdailyp());
		pShopItemData->set_counttotalp(pItemShopBase->GetCounttotalp());
		pShopItemData->set_ctlshow(pItemShopBase->GetCltShow());
		
	}
}

