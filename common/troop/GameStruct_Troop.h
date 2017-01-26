
#ifndef _GAMESTRUCT_TROOP_H_
#define _GAMESTRUCT_TROOP_H_

#include "Base.h"
#include "GameDefine_Troop.h"
#include "DBStruct/DBStruct_Troop.h"
#include "skill/GameStruct_Skill.h"


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

	int64 GetId() const {return m_Id;}
	void  SetId(int64 val) {m_Id= val;}

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}

	int  GetLevel() const {return m_nLevel;}
	void SetLevel(int nVal) {m_nLevel = nVal;}

	int  GetCount() const {return m_nCount;}
	void SetCount(int nVal) {m_nCount=nVal;}

	int64 GetMarchId() const {return m_nMarchId;}
	void  SetMarchId(int64 nVal) {m_nMarchId = nVal;}

	int   GetHp() const {return m_nHp;}
	void  SetHp(int nVal) {m_nHp = nVal;}

	int   GetArrangeIndex() const {return m_nArrangeIndex;}
	void  SetArrangeIndex(int nVal) {m_nArrangeIndex = nVal;}

	int   GetQueueIndex() const {return m_nQueueIndex;}
	void  SetQueueIndex(int nVal) {m_nQueueIndex = nVal;}

	CooldownList_T&		GetCooldownList(void){return m_CoolDownList;}
	CooldownList_T const& GetCooldownList(void)const{return m_CoolDownList;}
	tint32				GetOwnSkill(tint32 index) const;
	void				SetOwnSkill(tint32 skillId, tint32 index);
	void				AddOwnSkill(tint32 skillId);


private:
	int64   m_Id;
	int     m_nType; //兵类型
	int     m_nLevel;//等级
	int     m_nCount; // 数量
	int64   m_nMarchId;// 所属March
	int     m_nHp;       // 当前总血量
	int     m_nArrangeIndex; // 队形的位置
	int     m_nQueueIndex;   // 队列的位子(在兵营用到）

	CooldownList_T		m_CoolDownList;					//冷却列表
	TroopOwnSkillList	m_OwnSkillList;					//技能列表
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
		return m_TroopList.ElemSize();
	}

	bool IsTroopIdVaild(int  nType)const
	{
		if(0 < nType)
		{
			for(tint32 nId=0;m_TroopList.ElemSize()>nId;++nId)
			{
				if(m_TroopList[nId].GetType() ==nType)
				{
					return true;
				}
			}
		}
		return false;
	}

	// 检测是否可以增加军队
	bool CheckAddTroop(int nQueueIndex,int nTroopType)
	{
		if(0<nTroopType && nQueueIndex>=0)
		{
			if (m_TroopList[nQueueIndex].GetType() == 0)
			{
				return true;
			}
			if (m_TroopList[nQueueIndex].GetType() != nTroopType)
			{
				return false;
			}
			// 跳过检测最大值
			return true;
		}
		return false;
	}

	bool UpdateTroop(int nType, tint32 hp,int nQueueIndex)//更新CDTime列表
	{
		if(0<nType && nQueueIndex>=0)
		{
			if (m_TroopList[nQueueIndex].GetType() != 0 && m_TroopList[nQueueIndex].GetType() != nType)
			{
				return false;
			}
			m_TroopList[nQueueIndex].SetType(nType);
			//AssertEx(m_TroopList[nQueueIndex].GetHp()+hp<TROOP_QUEUE_MAX_SIGCOUNT,"");
			m_TroopList[nQueueIndex].SetHp(m_TroopList[nQueueIndex].GetHp()+hp);
			return true;
		}
		return false;
	}

	void SetTroopHp(int nArrangeIndex,int nHp)
	{
		for(tint32 nId=0;m_TroopList.ElemSize()>nId;++nId)
		{
			if(m_TroopList[nId].GetArrangeIndex() ==nArrangeIndex)
			{
				m_TroopList[nId].SetHp(nHp);
			}
		}
	}

	Troop const& GetTroopById(int64  nTroopId) const
	{
		if(0 <= nTroopId)
		{
			for(tint32 nId=0;m_TroopList.ElemSize()>nId;++nId)
			{
				if(m_TroopList[nId].GetId() ==nTroopId)
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
		if(0<=nIndex && m_TroopList.ElemSize()>nIndex)
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

	bool SwapQueueForArrange(int nArrange1,int nArrange2)
	{
		int nSize = m_TroopList.ElemSize();
		for (int i=0;i<nSize;i++)
		{
			if (m_TroopList[i].GetArrangeIndex() == nArrange1)
			{
				m_TroopList[i].SetArrangeIndex(nArrange2);
			}

			if (m_TroopList[i].GetArrangeIndex() == nArrange2)
			{
				m_TroopList[i].SetArrangeIndex(nArrange1);
			}
		}
		return true;
	}

private:
	bsarray<Troop, LIST_SIZE> m_TroopList;
};

BSARRAY_ASSIGN_DECL(Troop,TROOP_QUEUE_MAX_COUNT);

typedef std::map<int64,TroopList_T> MarchTroopMap;
typedef std::map<int64,int64> TroopMarchMap;
#endif