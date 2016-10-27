#ifndef _INVENTORYMANAGER_H_
#define _INVENTORYMANAGER_H_

#pragma once

#include <map>
#include "base/BaseManager.h"
using namespace std;

class Player;
class DB_Player;


class Inventory
{
public:
	Inventory(){};
	~Inventory(){};

	int		GetInventoryId() const { return m_nInventoryId; }
	void	SetInventoryId(int val) { m_nInventoryId = val; }

	int		GetIndex() const { return m_nIndex; }
	void	SetIndex(int val) { m_nIndex = val; }

	int		GetCount() const { return m_nCount; }
	void	SetCount(int val) { m_nCount = val; }

	void	AddCount(int nAddCount)
	{
		m_nCount += nAddCount;
		if (m_nCount < 0)
		{
			m_nCount = 0;
		}
		
	}
protected:
	int		m_nInventoryId;
	int		m_nIndex;
	int		m_nCount;
};

class BuyRecord
{
public:
	BuyRecord(): m_nIndex(0), m_nCount(0){};
	~BuyRecord(){};

	int		GetIndex() const { return m_nIndex; }
	void	SetIndex(int val) { m_nIndex = val; }

	int		GetCount() const { return m_nCount; }
	void	SetCount(int val) { m_nCount = val; }
	void	AddCount(int nAddCount)
	{
		m_nCount += nAddCount;
		if (m_nCount < 0)
		{
			m_nCount = 0;
		}

	}
protected:
	int		m_nIndex;
	int		m_nCount;	
};

class InventoryData;

class InventoryManager : public BaseManager
{
public:
	InventoryManager(Player *player);
	virtual ~InventoryManager(void);

	void		Init();
	void		LoadDB(DB_Player *pdbPlayer);
	void		SaveDB(DB_Player *pdbPlayer);

	int			AllocId();
	void		OnLogin();
	void		CheckBuyRecordDay();
	///////////////bag sys manager///////////////////////////
	Inventory*	AddInventory(int nIndex, int nCount, bool bUpdate = false);
	void		AddInventory(Inventory *pInventory);
	void		RemoveInventoryById(int nInventoryId, int nCount, bool bUpdate = false);
	void		RemoveInventoryByIndex(int nIndex, int nCount, bool bUpdate = false);
	bool		HasInventoryById(int nInventoryId);
	bool		HasInventoryByIndex(int nIndex);
	Inventory*	GetInventoryById(int nInventoryId);
	Inventory*	GetInventoryByIndex(int nIndex);
	int			GetCountByIndex(int nIndex);
	void		ClearInventory();

	BuyRecord*	AddBuyRecordTotal(int nIndex, int nCount);
	void		AddBuyRecordTotal(BuyRecord *pBuyRecord);
	BuyRecord*	GetBuyRecordTotal(int nIndex);
	int			GetBuyRecordCountTotal(int nIndex);
	void		RemoveBuyRecordTotal(int nIndex, int nCount);
	void		ClearBuyRecordTotal(int nIndex);

	BuyRecord*	AddBuyRecordDay(int nIndex, int nCount);
	void		AddBuyRecordDay(BuyRecord *pBuyRecord);
	BuyRecord*	GetBuyRecordDay(int nIndex);
	int			GetBuyRecordCountDay(int nIndex);
	void		RemoveBuyRecordDay(int nIndex, int nCount);
	void		ClearBuyRecordDay();

	void        OnBox(int itemid);

protected:
	int						m_nAllocId;
	map<int,Inventory*>		m_mapInventory;
	map<int,BuyRecord*>		m_mapBuyRecordTotal;
	map<int,BuyRecord*>		m_mapBuyRecordDay;
	time_t					m_timeInventory;
};

inline 	int InventoryManager::AllocId()
{
	return ++m_nAllocId;
}

#endif

