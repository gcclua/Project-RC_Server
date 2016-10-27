#ifndef _ITEMTBL_H_
#define _ITEMTBL_H_
#pragma once
#include <map>
#include <string>
#include "../common/const_def.h"
using namespace std;

class ItemBase
{
public:
	ItemBase(){};
	~ItemBase(){};

	int		GetIndex() const { return m_nIndex; }
	void	SetIndex(int val) { m_nIndex = val; }

	string	GetName() const { return m_strName; }
	void	SetName(string val) { m_strName = val; }

	int		GetItemType() const { return m_nItemType; }
	void	SetItemType(int val) { m_nItemType = val; }

	int		GetDescId() const { return m_nDescId; }
	void	SetDescId(int val) { m_nDescId = val; }

	int		GetValue() const { return m_nValue; }
	void	SetValue(int val) { m_nValue = val; }

	int		GetValidTime() const { return m_nValidTime; }
	void	SetValidTime(int val) { m_nValidTime = val; }

	int		GetDelete() const { return m_bDelete; }
	void	SetDelete(int val) { m_bDelete = val; }

	int		GetCanUse() const { return m_bCanUse; }
	void	SetCanUse(int val) { m_bCanUse = val; }

	int		GetOrder() const { return m_nOrder; }
	void	SetOrder(int val) { m_nOrder = val; }

	int		GetParam1() const { return m_nParam1; }
	void	SetParam1(int val) { m_nParam1 = val; }

	int		GetParam2() const { return m_nParam2; }
	void	SetParam2(int val) { m_nParam2 = val; }

	int		GetParam3() const { return m_nParam3; }
	void	SetParam3(int val) { m_nParam3 = val; }
protected:
	int		m_nIndex;
	string	m_strName;
	int		m_nItemType;
	int		m_nDescId;
	int		m_nValue;
	int		m_nValidTime;
	int		m_bDelete;
	int		m_bCanUse;
	int		m_nOrder;
	int		m_nParam1;
	int		m_nParam2;
	int		m_nParam3;

};

class ItemTbl
{
public:
	ItemTbl(void);
	~ItemTbl(void);

	void			LoadTbl();
	void			ClearTbl();

	ItemBase*		GetItemBase(int nIndex);

	static ItemTbl&	Instance(){return m_tblItemes;}
protected:
	static const char*  szConfigFile;
	static ItemTbl		m_tblItemes;
	map<int,ItemBase*>	m_mapItemBase;
};

#endif

