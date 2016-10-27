#include "ItemTbl.h"
#include "../common/DBC.h"
#include "../common/string-util.h"
ItemTbl ItemTbl::m_tblItemes;
const char* ItemTbl::szConfigFile = "Config/ItemBase.txt";
ItemTbl::ItemTbl(void)
{
}

ItemTbl::~ItemTbl(void)
{
	ClearTbl();
}

enum EITEMTBL
{
	EITEMTBL_INDEX,
	EITEMTBL_NAME,
	EITEMTBL_ITEMTYPE,
	EITEMTBL_DESC,
	EITEMTBL_LOGICVALUE,
	EITEMTBL_VALIDTIME,
	EITEMTBL_DELETE,
	EITEMTBL_CANUSE,
	EITEMTBL_ORDER,
	EITEMTBL_PARAM1,
	EITEMTBL_PARAM2,
	EITEMTBL_PARAM3,
};

void ItemTbl::LoadTbl()
{
	ClearTbl();

	DBCFile fileDBC(0);
	fileDBC.OpenFromTXT(szConfigFile);
	int nRow = fileDBC.GetRecordsNum();
	for (int i = 0; i < nRow; i++)
	{
		ItemBase *pItemBase = new ItemBase;
		if (pItemBase == NULL)
		{
			continue;
		}

		pItemBase->SetIndex(fileDBC.Search_Posistion(i, EITEMTBL_INDEX)->iValue); 
		string temp = "";
		gb2312ToUtf8(fileDBC.Search_Posistion(i, 1)->pString,temp);
		pItemBase->SetName(temp);
		pItemBase->SetItemType(fileDBC.Search_Posistion(i, EITEMTBL_ITEMTYPE)->iValue);
		pItemBase->SetDescId(fileDBC.Search_Posistion(i, EITEMTBL_DESC)->iValue);
		pItemBase->SetValue(fileDBC.Search_Posistion(i, EITEMTBL_LOGICVALUE)->iValue);
		pItemBase->SetValidTime(fileDBC.Search_Posistion(i, EITEMTBL_VALIDTIME)->iValue);
		pItemBase->SetDelete(fileDBC.Search_Posistion(i, EITEMTBL_DELETE)->iValue);                    
		pItemBase->SetCanUse(fileDBC.Search_Posistion(i, EITEMTBL_CANUSE)->iValue);                  
		pItemBase->SetOrder(fileDBC.Search_Posistion(i, EITEMTBL_ORDER)->iValue);                                       
		pItemBase->SetParam1(fileDBC.Search_Posistion(i, EITEMTBL_PARAM1)->iValue);                    
		pItemBase->SetParam2(fileDBC.Search_Posistion(i, EITEMTBL_PARAM2)->iValue);                      
		pItemBase->SetParam3(fileDBC.Search_Posistion(i, EITEMTBL_PARAM3)->iValue);                          

		m_mapItemBase.insert(make_pair(pItemBase->GetIndex(),pItemBase));

	}
}

void ItemTbl::ClearTbl()
{	
	for (map<int,ItemBase*>::iterator iter = m_mapItemBase.begin(); iter != m_mapItemBase.end(); iter++)
	{
		ItemBase *pItemBase = (ItemBase*)iter->second;
		if (pItemBase != NULL)
		{
			delete pItemBase;
		}
	}
	m_mapItemBase.clear();
}

ItemBase* ItemTbl::GetItemBase(int nIndex)
{
	map<int,ItemBase*>::iterator iterFind = m_mapItemBase.find(nIndex);
	if (iterFind != m_mapItemBase.end())
	{
		return (ItemBase*)iterFind->second;
	}
	return NULL;
}
