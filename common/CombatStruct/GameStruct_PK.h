/********************************************************************************
 *	文件名：	GameStruct_PK.h
 *	全路径：	\Server\Server\Common\CombatStruct\GameStruct_PK.h
 *	创建人：	zz
 *	创建时间：2013-2-10
 *
 *	功能说明：PK相关数据结构
 *	修改记录：
*********************************************************************************/
#ifndef GAMESTRUCT_PK_H
#define GAMESTRUCT_PK_H

#include "Base.h"
#include "GameDefine_PK.h"

struct DBPKAttackerInfo;
struct DBPKAttackerList;

struct PKAttackerInfo
{
public:
	enum 
	{
		MAX_REMAIN_TIME =300,//留在列表的剩余时间 5分钟 单位秒 
	};
	
	PKAttackerInfo()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		m_AttackerGUID =invalid_guid64;
		m_nAttackTime =0;
	}
public:
	bool SerializeToDB(DBPKAttackerInfo& rDest);//数据拷贝到存储结构中
	bool SerializeFromDB(const DBPKAttackerInfo& rSour);//存储结构中数据拷贝
public:
	int64 m_AttackerGUID;
	time_t m_nAttackTime;//留在列表的剩余时间 单位毫秒
};

struct PKAttackerList
{
public:
	enum 
	{
		MAX_LIST_SIZE =16,//列表保留人数(修改此值，请同步修改数据库存储)
	};
	PKAttackerList()
	{
	  CleanUp();
	}
	void CleanUp(void)
	{
		for (int i=0;i<MAX_LIST_SIZE;i++)
		{
			m_AttackerList[i].CleanUp();
		}
	}
	
	bool AddAttacker(int64 TargetGuid)
	{
		
		//是否已经在列表中
		int nOldIndex =-1;
		if (IsAttacker(TargetGuid,nOldIndex))
		{
			if (nOldIndex>=0 && nOldIndex<MAX_LIST_SIZE)
			{
				m_AttackerList[nOldIndex].m_nAttackTime = Clock::getCurrentSystemTime();
			}
			return true;
		}
		bool bHaveEmpty =false;
		//有空位 直接加进去
		for (int i=0;i<MAX_LIST_SIZE;i++)
		{
			if (m_AttackerList[i].m_AttackerGUID ==invalid_guid64)
			{
				m_AttackerList[i].m_AttackerGUID =TargetGuid;
				m_AttackerList[i].m_nAttackTime = Clock::getCurrentSystemTime();
				bHaveEmpty =true;
				break;
			}
		}
		//列表满了 找到最先进列表的 替换掉 进入列表时间最久的
		if (bHaveEmpty ==false)
		{
			int nMaxElapseTime =0;
			int nSelIndex =-1;
			for (int i=0;i<MAX_LIST_SIZE;i++)
			{
				int nElapseTime =(int)(Clock::getCurrentSystemTime() -m_AttackerList[i].m_nAttackTime);
				if (nElapseTime>nMaxElapseTime)
				{
					nMaxElapseTime =nElapseTime;
					nSelIndex =i;
				}
			}
			if (nSelIndex >=0 && nSelIndex<MAX_LIST_SIZE)
			{
				m_AttackerList[nSelIndex].m_AttackerGUID =TargetGuid;
				m_AttackerList[nSelIndex].m_nAttackTime =static_cast<int>(Clock::getCurrentSystemTime());
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	bool RemoveAttacker(int64 TargetGuid)
	{
		for (int i=0;i<MAX_LIST_SIZE;i++)
		{
			if (m_AttackerList[i].m_AttackerGUID ==TargetGuid)
			{
				m_AttackerList[i].CleanUp();
				return true;
			}
		}
		return false;
	}
	bool RemoveAttackerByIndex(int index)
	{
		if (index >=0 && index<MAX_LIST_SIZE)
		{
			m_AttackerList[index].CleanUp();
			return true;
		}
		return false;
	}
	bool IsAttacker(int64 TargetGuid)
	{
		for (int i=0;i<MAX_LIST_SIZE;i++)
		{
			if (m_AttackerList[i].m_AttackerGUID ==TargetGuid)
			{
				return true;
			}
		}
		return false;
	}
	bool IsAttacker(int64 TargetGuid,int &nIndex)
	{
		for (int i=0;i<MAX_LIST_SIZE;i++)
		{
			if (m_AttackerList[i].m_AttackerGUID ==TargetGuid)
			{
				nIndex =i;
				return true;
			}
		}
		nIndex =-1;
		return false;
	}
	bool IsPKAttackerInfoIndexVaild(int nIndex) const 
	{
		if(0<=nIndex && MAX_LIST_SIZE>nIndex)
		{
			return true;
		}
		return false;
	}
	//!!!注意调用之前 先调用IsPKAttackerInfoIndexVaild 判断有效性
	PKAttackerInfo& GetPKAttackerInfoByIndex(int nIndex)
	{
		if(0<=nIndex && MAX_LIST_SIZE>nIndex)
		{
			return m_AttackerList[nIndex];
		}
		AssertEx(false,"");
		return m_AttackerList[0];
	}
	bool isEmpty()
	{
		for (int i=0;i<MAX_LIST_SIZE;i++)
		{
			if (m_AttackerList[i].m_AttackerGUID !=invalid_guid64)
			{
				return false;
			}
		}
		return true;
	}
public:
	bool SerializeToDB(DBPKAttackerList& rDest);//数据拷贝到存储结构中
	bool SerializeFromDB(const DBPKAttackerList& rSour);//存储结构中数据拷贝
public:
	bsarray<PKAttackerInfo, MAX_LIST_SIZE> m_AttackerList;

};



#endif