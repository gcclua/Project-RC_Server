#ifndef _BATTLETASKTBL_H_
#define _BATTLETASKTBL_H_
#pragma once
#include <map>
#include <string>

#include "Base.h"

class BattleTaskBase
{
public:
	BattleTaskBase(){};
	~BattleTaskBase(){};

	int		GetId() const { return m_nId; }
	void	SetId(int val) { m_nId = val; }

	string	GetName() const { return m_strName; }
	void	SetName(string val) { m_strName = val; }

	int		GetDecId() const { return m_nDecId; }
	void	SetDecId(int val) { m_nDecId = val; }

	int		GetOpenId() const { return m_nOpenId; }
	void	SetOpenId(int val) { m_nOpenId = val; }

	int		GetChainName() const { return m_nChainName; }
	void	SetChainName(int val) { m_nChainName = val; }

	int		GetGuankaNum() const { return m_nGuankaNum; }
	void	SetGuankaNum(int val) { m_nGuankaNum = val; }

	int		GetDifficulty() const { return m_nDifficulty; }
	void	SetDifficulty(int val) { m_nDifficulty = val; }

	int		GetNpcId() const { return m_nNpcId; }
	void	SetNpcId(int val) { m_nNpcId = val; }

	int		GetExp() const { return m_nExp; }
	void	SetExp(int val) { m_nExp = val; }

	int		GetGold() const { return m_nGold; }
	void	SetGold(int val) { m_nGold = val; }

	int		GetHeroExp() const { return m_nHeroExp; }
	void	SetHeroExp(int val) { m_nHeroExp = val; }

	int		GetDropId1() const { return m_nDropId1; }
	void	SetDropId1(int val) { m_nDropId1 = val; }

	int		GetDropId2() const { return m_nDropId2; }
	void	SetDropId2(int val) { m_nDropId2 = val; }

	int		GetDropId3() const { return m_nDropId3; }
	void	SetDropId3(int val) { m_nDropId3 = val; }

	int		GetDropId4() const { return m_nDropId4; }
	void	SetDropId4(int val) { m_nDropId4 = val; }

	int		GetDropId5() const { return m_nDropId5; }
	void	SetDropId5(int val) { m_nDropId5 = val; }

	int		GetDropId6() const { return m_nDropId6; }
	void	SetDropId6(int val) { m_nDropId6 = val; }

	int		GetDropId7() const { return m_nDropId7; }
	void	SetDropId7(int val) { m_nDropId7 = val; }

	int		GetDropId8() const { return m_nDropId8; }
	void	SetDropId8(int val) { m_nDropId8 = val; }

	int		GetDropId9() const { return m_nDropId9; }
	void	SetDropId9(int val) { m_nDropId9 = val; }

	int		GetDropId10() const { return m_nDropId10; }
	void	SetDropId10(int val) { m_nDropId10 = val; }

	int		GetSpecialDrop() const { return m_nSpecialDrop; }
	void	SetSpecialDrop(int val) { m_nSpecialDrop = val; }

	int		GetSpecailType() const { return m_nSpecailType; }
	void	SetSpecailType(int val) { m_nSpecailType = val; }

	int		GetSpecailCount() const { return m_nSpecailCount; }
	void	SetSpecailCount(int val) { m_nSpecailCount = val; }

	int		GetLostExp() const { return m_nLostExp; }
	void	SetLostExp(int val) { m_nLostExp = val; }

	int		GetDifficultyC() const { return m_nDifficultyC; }
	void	SetDifficultyC(int val) { m_nDifficultyC = val; }

	int		GetHeroID() const { return m_nHeroID; }
	void	SetHeroID(int val) { m_nHeroID = val; }

	int		GetNeedVipLevel() const { return m_nNeedVipLevel; }
	void	SetNeedVipLevel(int val) { m_nNeedVipLevel = val; }

	int		GetClenPrice() const { return m_nClenPrice; }
	void	SetClenPrice(int val) { m_nClenPrice = val; }

	vector<int>&	GetDropId(){return m_vecDropId;}
protected:
	int		m_nId;
	string	m_strName;
	int		m_nDecId;
	int		m_nOpenId;
	int		m_nChainName;
	int		m_nGuankaNum;
	int		m_nDifficulty;
	int		m_nNpcId;
	int		m_nExp;
	int		m_nGold;
	int		m_nHeroExp;
	int		m_nDropId1;
	int		m_nDropId2;
	int		m_nDropId3;
	int		m_nDropId4;
	int		m_nDropId5;
	int		m_nDropId6;
	int		m_nDropId7;
	int		m_nDropId8;
	int		m_nDropId9;
	int		m_nDropId10;
	int		m_nSpecialDrop;
	int		m_nSpecailType;
	int		m_nSpecailCount;
	int		m_nLostExp;	
	int		m_nDifficultyC;
	int		m_nHeroID;
	int		m_nNeedVipLevel;
	int		m_nClenPrice;

	vector<int>	m_vecDropId;
};

class BattleTaskTbl
{
public:
	BattleTaskTbl();
	~BattleTaskTbl();

	void			LoadTbl();
	void			ClearTbl();

	BattleTaskBase*	GetBattleTaskBase(int nIndex);

	static BattleTaskTbl&	Instance(){return m_tblBattleTask;}
protected:
	static const char*  szConfigFile;
	static BattleTaskTbl	m_tblBattleTask;
	map<int,BattleTaskBase*>	m_mapBattleTaskBase;
	map<int,vector<int> > m_mapTaskChain;
};

#endif

