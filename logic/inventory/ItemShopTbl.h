#ifndef _ITEMSHOPTBL_H_
#define _ITEMSHOPTBL_H_
#pragma once
#include <map>
#include <string>
#include "../common/const_def.h"

class ItemShopBase
{
public:
	ItemShopBase(){};
	~ItemShopBase(){};

	int		GetId() const { return m_nId; }
	void	SetId(int val) { m_nId = val; }

	string	GetItemname() const { return m_strItemname; }
	void	SetItemname(string val) { m_strItemname = val; }

	int		GetCosttype() const { return m_nCosttype; }
	void	SetCosttype(int val) { m_nCosttype = val; }

	int		GetCostcount() const { return m_nCostcount; }
	void	SetCostcount(int val) { m_nCostcount = val; }

	int		GetIfnew() const { return m_nIfnew; }
	void	SetIfnew(int val) { m_nIfnew = val; }

	int		GetIfhot() const { return m_nIfhot; }
	void	SetIfhot(int val) { m_nIfhot = val; }

	int		GetSale() const { return m_nSale; }
	void	SetSale(int val) { m_nSale = val; }

	int		GetSelltype() const { return m_nSelltype; }
	void	SetSelltype(int val) { m_nSelltype = val; }

	int		GetOntime() const { return m_nOntime; }
	void	SetOntime(int val) { m_nOntime = val; }

	int		GetOfftime() const { return m_nOfftime; }
	void	SetOfftime(int val) { m_nOfftime = val; }

	int		GetLevellimit() const { return m_nLevellimit; }
	void	SetLevellimit(int val) { m_nLevellimit = val; }

	int		GetRequestvip() const { return m_nRequestvip; }
	void	SetRequestvip(int val) { m_nRequestvip = val; }

	int		GetCountdaily() const { return m_nCountdaily; }
	void	SetCountdaily(int val) { m_nCountdaily = val; }

	int		GetCounttotal() const { return m_nCounttotal; }
	void	SetCounttotal(int val) { m_nCounttotal = val; }

	int		GetCountdailyp() const { return m_nCountdailyp; }
	void	SetCountdailyp(int val) { m_nCountdailyp = val; }

	int		GetCounttotalp() const { return m_nCounttotalp; }
	void	SetCounttotalp(int val) { m_nCounttotalp = val; }

	int		GetServerId() const { return m_nServerId; }
	void	SetServerId(int val) { m_nServerId = val; }

	int		GetCltShow() const { return m_nCltShow; }
	void	SetCltShow(int val) { m_nCltShow = val; }
protected:
	int		m_nId;
	string	m_strItemname;
	int		m_nCosttype;
	int		m_nCostcount;
	int		m_nIfnew;
	int		m_nIfhot;
	int		m_nSale;
	int		m_nSelltype;
	int		m_nOntime;
	int		m_nOfftime;
	int		m_nLevellimit;
	int		m_nRequestvip;
	int		m_nCountdaily;
	int		m_nCounttotal;
	int		m_nCountdailyp;
	int		m_nCounttotalp;
	int		m_nServerId;
	int		m_nCltShow;
};

class SseShopItems;
class Player;
class ItemShopTbl
{
public:
	ItemShopTbl();
	~ItemShopTbl();

	void			LoadTbl();
	void			ClearTbl();

	ItemShopBase*	GetItemShopBase(int nIndex);
	bool			CanOnTime(ItemShopBase* pItemShopBase);
	void			FillShopItems(Player *pPlayer, SseShopItems *data);
	static ItemShopTbl&	Instance(){return m_tblItemShop;}
protected:
	static const char*  szConfigFile;
	static ItemShopTbl	m_tblItemShop;
	map<int,ItemShopBase*>	m_mapItemShopBase;
};

#endif

