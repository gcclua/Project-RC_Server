#ifndef _ITEMLOGICMANAGER_H_
#define _ITEMLOGICMANAGER_H_
#pragma once
#include <map>
#include "base/BaseManager.h"
#include "const_def.h"


const int ITEMTYPE_GOLD					= -11;	//金币
const int ITEMTYPE_CASH					= -12;	//游戏币
const int ITEMTYPE_POWER				= -13;	//体力值
const int ITEMTYPE_QI					= -14;	//元气值


const int ITEMTYPE_PLAYEREXP			= -100;	//玩家经验
const int ITEMTYPE_ROLEEXP				= -101;	//将经验

const int ITEMTYPE_ROLE					= -1000;//将
const int ITEMTYPE_ROLESOUL				= -1001;//将魂
const int ITEMTYPE_EQUIP				= -1002;//装备
const int ITEMTYPE_SKILL				= -1003;//技能
const int ITEMTYPE_FRAGMENT             = -1004;//残片
const int ITEMTYPE_INVENTORY			= -1005;//背包物品

class Player;
class SseInventoryUse;

class ItemLogicManager  : public BaseManager
{
public:
	ItemLogicManager(Player *pPlayer);
	~ItemLogicManager(void);

	void		Init();
	void		LoadDB(DB_Player *pdbPlayer);
	void		SaveDB(DB_Player *pdbPlayer);


	void		ItemUsePower(int nParam, SseInventoryUse *data);
	//item base operation/////////////////
	int			GetItemTypeByIndex(int nItemIndex);
	bool		HasItemByIndex(int nItemIndex, int param = 0);
	int64		GetItemCount(int nItemIndex, int param = 0);
	void		AddItem(int nItemIndex, int nItemCount,CASH_TYPE_DEF cashtype= CASH_TYPE_DEF_DEFAULT, bool bUpdate = false, int nParam = -1);
	void		RemoveItem(int nItemIndex, int nItemCount, int param = -1);
	void		DeleteItemByType( int nItemIndex );
	int			GetItemCountByPrefix(int prefix);

	void		SendItemUpdate(vector<int> vecItemIndex);
protected:
};

#endif
