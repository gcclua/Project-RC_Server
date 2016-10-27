/********************************************************************************
 *	�ļ�����	GameStruct_PK.h
 *	ȫ·����	\Server\Server\Common\CombatStruct\GameStruct_PK.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-2-10
 *
 *	����˵����PK������ݽṹ
 *	�޸ļ�¼��
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
		MAX_REMAIN_TIME =300,//�����б��ʣ��ʱ�� 5���� ��λ�� 
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
	bool SerializeToDB(DBPKAttackerInfo& rDest);//���ݿ������洢�ṹ��
	bool SerializeFromDB(const DBPKAttackerInfo& rSour);//�洢�ṹ�����ݿ���
public:
	int64 m_AttackerGUID;
	time_t m_nAttackTime;//�����б��ʣ��ʱ�� ��λ����
};

struct PKAttackerList
{
public:
	enum 
	{
		MAX_LIST_SIZE =16,//�б�������(�޸Ĵ�ֵ����ͬ���޸����ݿ�洢)
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
		
		//�Ƿ��Ѿ����б���
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
		//�п�λ ֱ�Ӽӽ�ȥ
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
		//�б����� �ҵ����Ƚ��б�� �滻�� �����б�ʱ����õ�
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
	//!!!ע�����֮ǰ �ȵ���IsPKAttackerInfoIndexVaild �ж���Ч��
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
	bool SerializeToDB(DBPKAttackerList& rDest);//���ݿ������洢�ṹ��
	bool SerializeFromDB(const DBPKAttackerList& rSour);//�洢�ṹ�����ݿ���
public:
	bsarray<PKAttackerInfo, MAX_LIST_SIZE> m_AttackerList;

};



#endif