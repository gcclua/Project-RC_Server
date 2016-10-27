/********************************************************************************
 *	文件名：	GameStruct_Threat.h
 *	全路径：	\Server\Server\Common\CombatStruct\GameStruct_Threat.h
 *	创建人：	zz
 *	创建时间：2013-1-20
 *
 *	功能说明：仇恨相关数据结构
 *	修改记录：
*********************************************************************************/
#ifndef GAMESTRUCT_THREAT
#define GAMESTRUCT_THREAT
#include "Base.h"
#include "GameDefine_Threat.h"
struct EnemyUnit_T
{
public:
	EnemyUnit_T(void)
	{
		CleanUp();
	}
	~EnemyUnit_T(void){};
	void CleanUp(void)
	{
		m_nObjId =invalid_id;
		m_nThreat =0;
		m_nLastThreatTime =0;
	}
	void RestThreat()
	{
		m_nThreat =0;
	}
	bool isValid(void) const
	{
		if (m_nObjId >=0)
		{
			return true;
		}
		return false;
	}
	int GetObjID(void) const{return m_nObjId;}
	void SetObjId(int nId){m_nObjId =nId;}
	int GetThreat(void) const{return m_nThreat;}
	void SetThreat(int nThreat)
	{
		if (nThreat <1)
		{
			nThreat =1;
		}
		if (nThreat >10000000)
		{
			nThreat =10000000;
		}
		m_nThreat =nThreat;
		if (nThreat >0)
		{
			m_nLastThreatTime = static_cast<uint32>(Clock::getCurrentSystemTime());//更新最近一次造成仇恨的时间
		}
	}
	uint32 GetLastThreatTime() const { return m_nLastThreatTime; }
	void SetLastThreatTime(uint32 val) { m_nLastThreatTime = val; }
private:
	int m_nObjId;
	int m_nThreat;
	uint32 m_nLastThreatTime;
};

BSARRAY_ASSIGN_DECL(EnemyUnit_T, 32);
struct EnemyUnitList_T
{
public:
	enum 
	{
		LIST_SIZE =32,
		MAXTIME =15000,//超过15s无增加仇恨行为 则移除
	};
	EnemyUnitList_T(void){CleanUp();};
	~EnemyUnitList_T(void){};
	void CleanUp(void)
	{
		for (int i=0;i<LIST_SIZE;i++)
		{
			m_enemyList[i].CleanUp();
		}
	}
	int GetSize(void) const {return LIST_SIZE;}
	int CalculationEnemyCount(void) const
	{
		int nCount =0;
		for (int i=0;i<LIST_SIZE;i++)
		{
			if (true ==m_enemyList[i].isValid())
			{
				nCount++;
			}
		}
		return nCount;
	}
	void RemoveEnemyByIndex(int nIndex)
	{
		if (nIndex >=0 && nIndex<LIST_SIZE)
		{
			m_enemyList[nIndex].CleanUp();
		}
	}
	bool AddEnemyToList(int nIndex,int nObjId, int nThreat)
	{
		if (nIndex >=0 && nIndex<LIST_SIZE)
		{
			if (false ==m_enemyList[nIndex].isValid())
			{
				m_enemyList[nIndex].SetObjId(nObjId);
				m_enemyList[nIndex].SetThreat(nThreat);
				return true;
			}
		}
		return false;
	}
	bool IsUnitVaild(int nIndex) const
	{
		if (nIndex >=0 && nIndex<LIST_SIZE)
		{
			return true;
		}
		return false;
	}
	//get前 记得判断是否有效
	EnemyUnit_T const& GetUnitByIndex(int nIndex) const
	{
		AssertEx(nIndex >=0 && nIndex<LIST_SIZE,"");
		return m_enemyList[nIndex];
	}
	//get前 记得判断是否有效
	EnemyUnit_T& GetUnitByIndex(int nIndex) 
	{
		AssertEx(nIndex >=0&&nIndex<LIST_SIZE,"");
		return m_enemyList[nIndex];
	}
	int GetSlotInEnemyList(int objId)
	{
		for (int nIndex=0;nIndex<LIST_SIZE;nIndex++)
		{
			if (m_enemyList[nIndex].isValid() && m_enemyList[nIndex].GetObjID() ==objId)
			{
				return nIndex;
			}
		}
		return -1;
	}
private:
	bsarray<EnemyUnit_T, LIST_SIZE> m_enemyList;
};
struct EnemyDataInfo_T
{
public:
	EnemyDataInfo_T(void) {CleanUp();};
	~EnemyDataInfo_T(void) {};
	
	void CleanUp(void)
	{
		m_oList.CleanUp();
	}
	int GetCount(void) const {return m_oList.CalculationEnemyCount();};
	EnemyUnitList_T const& GetEnemyList(void) const {return m_oList;};
	EnemyUnitList_T& GetEnemyList(void) {return m_oList;};
private:
	EnemyUnitList_T m_oList;
};
#endif // !GAMESTRUCT_THREAT
