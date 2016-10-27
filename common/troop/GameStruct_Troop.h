
#ifndef _GAMESTRUCT_TROOP_H_
#define _GAMESTRUCT_TROOP_H_

#include "Base.h"
#include "GameDefine_Troop.h"
#include "DBStruct/DBStruct_Troop.h"

class Troop
{

public:
	Troop();
	virtual ~Troop(void);

public:
	void SerializeToDB(DBTroop& rDest) const;
	void SerializeFromDB(const DBTroop& rSource);

	void CleanUp();

	Troop& operator=(Troop const& rhs);

public:

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}

	int  GetLevel() const {return m_nLevel;}
	void SetLevel(int nVal) {m_nLevel = nVal;}

	int  GetCount() const {return m_nCount;}
	void SetCount(int nVal) {m_nCount=nVal;}

	int64 GetBuildId() const {return m_nBuildID;}
	void  SetBuildId(int64 nVal) {m_nBuildID = nVal;}

	int   GetHp() const {return m_nHp;}
	void  SetHp(int nVal) {m_nHp = nVal;}

	int   GetArrangeIndex() const {return m_nArrangeIndex;}
	void  SetArrangeIndex(int nVal) {m_nArrangeIndex = nVal;}

	int   GetQueueIndex() const {return m_nQueueIndex;}
	void  SetQueueIndex(int nVal) {m_nQueueIndex = nVal;}

private:
	int     m_nType; //兵类型
	int     m_nLevel;//等级
	int     m_nCount; // 数量
	int64   m_nBuildID;// 所属兵营
	int     m_nHp;       // 当前总血量
	int     m_nArrangeIndex; // 队形的位置
	int     m_nQueueIndex;   // 队列的位子
};

typedef boost::shared_ptr<Troop> TroopPtr;

class TroopList_T
{
public:
	enum
	{
		LIST_SIZE = TROOP_QUEUE_MAX_COUNT,
	};
	TroopList_T(void)
	{
		CleanUp();
	}
	void CleanUp()
	{
		for(tint32 nId=0;LIST_SIZE>nId;++nId)
		{
			m_TroopList[nId].CleanUp();
		}
	}

	TroopList_T& operator=(TroopList_T const& rhs)
	{
		for(tint32 nId=0;LIST_SIZE>nId;++nId)
		{
			m_TroopList[nId] = rhs.m_TroopList[nId];
		}
		return *this;
	}
	tint32 GetListSize(void) const
	{
		return LIST_SIZE;
	}

	bool IsTroopIdVaild(int  nType)const
	{
		if(0 <= nType)
		{
			for(tint32 nId=0;LIST_SIZE>nId;++nId)
			{
				if(m_TroopList[nId].GetType() ==nType)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool UpdateTroop(int nType, tint32 nCount,int nQueueIndex)//更新CDTime列表
	{
		if(0<=nType && nQueueIndex>=0)
		{
			if (m_TroopList[nQueueIndex].GetType() != 0 && m_TroopList[nQueueIndex].GetType() != nType)
			{
				return false;
			}
			m_TroopList[nQueueIndex].SetType(nType);
			AssertEx(m_TroopList[nQueueIndex].GetCount()+nCount<TROOP_QUEUE_MAX_SIGCOUNT,"");
			m_TroopList[nQueueIndex].SetCount(m_TroopList[nQueueIndex].GetCount()+nCount);
		}
		return false;
	}

	Troop const& GetTroopById(int  nType) const
	{
		if(0 <= nType)
		{
			for(tint32 nId=0;LIST_SIZE>nId;++nId)
			{
				if(m_TroopList[nId].GetType() ==nType)
				{
					return m_TroopList[nId];
				}
			}
		}
		AssertEx(false,"");
		return m_TroopList[0];;
	}

	Troop const & GetTroopByIndex(tint32 nIndex) const
	{
		if(0<=nIndex && LIST_SIZE>nIndex)
		{
			return m_TroopList[nIndex];
		}
		AssertEx(false,"");
		return m_TroopList[0];
	}

	void SetTroop(int nIndex,const Troop& rTroop)
	{
		if (0<=nIndex && LIST_SIZE>nIndex)
		{
			m_TroopList[nIndex] = rTroop;
		}
	}

protected:
private:
	bsarray<Troop, LIST_SIZE> m_TroopList;
};


typedef map<int64,TroopList_T> BarrackTroopMap;
typedef map<int64,bsarray<int,TROOP_ARRANGE_MAX_POSITION>> BarrackArrangeMap;
#endif