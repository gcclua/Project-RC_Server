/********************************************************************************
 *	文件名：	GameStruct_Skill.h
 *	全路径：	\Server\Common\SkillStruct\GameStruct_Skill.h
 *	创建人：	zz
 *	创建时间：2013-1-8
 *
 *	功能说明：技能相关数据结构
 *	修改记录：
*********************************************************************************/
#ifndef GAMESTRUCT_SKILL_H
#define GAMESTRUCT_SKILL_H

#include "Base.h"
#include "GameDefine_Skill.h"

class Table_SkillBase;
class Table_SkillEx;

//==========================技能数据结构 Begin============================================================//
struct SkillInfo_T
{
	enum CONST_VALUE
	{
		PARAM_LIST_SIZE =8,
	};
	SkillInfo_T() {Cleanup();};
	~SkillInfo_T() {};
	void Cleanup(void)
	{
		m_pSkillBase = null_ptr;
		m_pSkillEx = null_ptr;
		m_nTargetId = invalid_id;
		m_nSkillId =invalid_id;
		m_nSkillDelayTime =0;
		m_nSkillRemainTime =0;
		for (int i=0; i<PARAM_LIST_SIZE; i++)
		{
			m_aParam[i] = -1;
		}	
	}
	inline bool IsValid(void) const {return (null_ptr==m_pSkillBase || null_ptr==m_pSkillEx)? false:true;}
	int GetParamByIndex(int nIndex) const
	{
		if(0<=nIndex && PARAM_LIST_SIZE>nIndex)
		{
			return m_aParam[nIndex];
		}
		return 0;
	}
	void SetParamByIndex(int nIndex, int nValue) 
	{
		if(0<=nIndex && PARAM_LIST_SIZE>nIndex)
		{
			m_aParam[nIndex] = nValue;
		}

	}
	void InitParam()
	{
		for (int i=0; i<PARAM_LIST_SIZE; i++)
		{
			m_aParam[i] = -1;
		}
	}
	Table_SkillBase const*		m_pSkillBase;
	Table_SkillEx const*		m_pSkillEx;
	int		m_nSkillId;
	int		m_nTargetId;
	int		m_nSkillDelayTime;
	int		m_nSkillRemainTime;//距离结束剩余时间
private:
	bsarray<int, PARAM_LIST_SIZE> m_aParam;


};
//==========================技能数据结构 End============================================================//




//==========================冷却时间相关 Begin============================================================//
struct  DBCoolDown_Info;
class TimeInfo;

struct CoolDown_Info
{
public:
	CoolDown_Info()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		m_nID =-1;
		m_nCDTime =-1;
		m_nCDTimeElapsed =0;
	}

	CoolDown_Info& operator=(CoolDown_Info const& rhs)
	{
		m_nID = rhs.m_nID;
		m_nCDTime = rhs.m_nCDTime;
		m_nCDTimeElapsed = rhs.m_nCDTimeElapsed;
		return *this;
	};
	void Init(int nId,int nCDTime,int nElapsed)
	{
		if (nId>=0 && nCDTime>0)
		{
			m_nID =nId;
			m_nCDTime =nCDTime;
			m_nCDTimeElapsed =nElapsed;
		}
		else
		{
			CleanUp();
		}
	}
	void Tick(TimeInfo const&rTimeInfo);
	int GetRemainTime(void) const
	{
		int nRemainTime =m_nCDTime -m_nCDTimeElapsed;
		return nRemainTime;
	}
	bool IsCoolDowned(void)const
	{
		if (m_nID<0)
		{
			return true;
		}
		return (m_nCDTime>m_nCDTimeElapsed);
	}
public:
	bool SerializeToDB(DBCoolDown_Info& rDest) const;//数据拷贝到存储结构中
	bool SerializeFromDB(const DBCoolDown_Info& rDest);
public:

	int16 m_nID;//冷却ID
	int m_nCDTime;//冷却时间 毫秒 !!!不存储
	int m_nCDTimeElapsed;//冷却流逝时间 毫秒
};


class CooldownList_T
{
public:
	enum
	{
		LIST_SIZE = 32,
	};
	CooldownList_T(void)
	{
		CleanUp();
	}
	void CleanUp()
	{
		for(int nId=0;LIST_SIZE>nId;++nId)
		{
			m_CooldownList[nId].CleanUp();
		}
	}
	void ClearCooldown(void)
	{
		for(int nId=0;LIST_SIZE>nId;++nId)
		{
			m_CooldownList[nId].m_nCDTimeElapsed =m_CooldownList[nId].m_nCDTime;
		}
	}
	CooldownList_T& operator=(CooldownList_T const& rhs)
	{
		for(int nId=0;LIST_SIZE>nId;++nId)
		{
			m_CooldownList[nId] = rhs.m_CooldownList[nId];
		}
		return *this;
	}
	int GetListSize(void) const
	{
		return LIST_SIZE;
	}
	
	void  Tick(TimeInfo const&rTimeInfo)
	{
		for(int nId=0;LIST_SIZE>nId;++nId)
		{
			m_CooldownList[nId].Tick(rTimeInfo);
		}
	}
	bool IsSlotCooldowned(int16 nID) const
	{
		if(0 <= nID)
		{
			for(int nId=0;LIST_SIZE>nId;++nId)
			{
				if(m_CooldownList[nId].m_nID==nID)
				{
					return m_CooldownList[nId].IsCoolDowned();
				}
			}
		}
		return false;
	}
	bool IsCooldownIdVaild(int16 nID)const
	{
		if(0 <= nID)
		{
			for(int nId=0;LIST_SIZE>nId;++nId)
			{
				if(m_CooldownList[nId].m_nID ==nID)
				{
					return true;
				}
			}
		}
		return false;
	}
	CoolDown_Info const& GetCooldownById(int16 nID) const
	{
		if(0 <= nID)
		{
			for(int nId=0;LIST_SIZE>nId;++nId)
			{
				if(m_CooldownList[nId].m_nID ==nID)
				{
					return m_CooldownList[nId];
				}
			}
		}
		AssertEx(false,"");
		return m_CooldownList[0];;
	}

	bool UpdateCooldown(int16 nID, int nTotalTime,int nElapsed)//更新CDTime列表
	{
		if(0<=nID)
		{
			int nCurrentUsedSlot = -1;
			int nFirstEmptySlot = -1;
			for(int nId=0;LIST_SIZE>nId;++nId)
			{
				//先看看 是否已经存在冷却列表里面 找到直接跳出
				if(m_CooldownList[nId].m_nID==nID)
				{
					nCurrentUsedSlot = nId;
					break;
				}
				//看下有没有备用的空位 找到了 先记下 继续看 列表中是否已经存在了
				if(m_CooldownList[nId].m_nID<0 || false==m_CooldownList[nId].IsCoolDowned())
				{
					if(0>nFirstEmptySlot)
					{
						nFirstEmptySlot = nId;
					}
				}
			}
			if(0>nCurrentUsedSlot)
			{
				if(0<=nFirstEmptySlot)
				{
					nCurrentUsedSlot = nFirstEmptySlot;
				}
			}
			if(0<=nCurrentUsedSlot)
			{
				m_CooldownList[nCurrentUsedSlot].Init(nID, nTotalTime,nElapsed);
			}
			else
			{
				return false;
			}
			return true;
		}
		return false;
	}
	bool IsCooldownIndexVaild(int nIndex) const 
	{
		if(0<=nIndex && LIST_SIZE>nIndex)
		{
			return true;
		}
		return false;
	}
	CoolDown_Info const& GetCooldownByIndex(int nIndex) const
	{
		if(0<=nIndex && LIST_SIZE>nIndex)
		{
			return m_CooldownList[nIndex];
		}
		AssertEx(false,"");
		return m_CooldownList[0];
	}
	void RemoveCoolDownById(int nID)
	{
		if(0 <= nID)
		{
			for(int nId=0;LIST_SIZE>nId;++nId)
			{
				if(m_CooldownList[nId].m_nID ==nID)
				{
					m_CooldownList[nId].CleanUp();
				}
			}
		}
	}

protected:
private:
	bsarray<CoolDown_Info, LIST_SIZE> m_CooldownList;
};
//==========================冷却时间相关 End=============================================================//



//==========================伤害信息相关 Begin=============================================================//
//分类型的伤害结构
class DamagesInof_T
{
public:
	enum
	{
		DAMAGE_PHYSICS=0,
		DAMAGE_LIST_SIZE,
	};
public:
	int GetSenderID(void) const {return m_SenderID;}
	void SetSenderID(int objID){m_SenderID = objID;}
	int GetSkillID(void) const {return m_nSkillID;}
	void SetSkillID(int nID){m_nSkillID = nID;}
	int GetImpactID(void) const {return m_nImpactID;}
	void SetImpactID(int nID){m_nImpactID = nID;}
	bool IsHit(void) const {return m_bHit;}
	void SetHitFlag(bool bFlag) {m_bHit = bFlag;}
	int GetDecHp() const { return m_nDecHp; }
	void SetDecHp(int val) { m_nDecHp = val; }
	int GetNotypeDamage(void) const {return m_nNoTypeDamage;}
	void SetNotypeDamage(int nDamage) {m_nNoTypeDamage = nDamage;}
	void SetFromNPCFlag(bool bNpc) { m_bIsFromeNPC = bNpc; }
	bool IsFromNPC() { return m_bIsFromeNPC; }
	bool IsReflex() const { return m_bIsReflex; }
	void SetIsReflex(bool val) { m_bIsReflex = val; }
	int GetClientShowInterval() const { return m_nClientShowInterval; }
	void SetClientShowInterval(int val) { m_nClientShowInterval = val; }
	int GetClientShowTimes() const { return m_nClientShowTimes; }
	void SetClientShowTimes(int val) { m_nClientShowTimes = val; }
	int GetTypeDamageByType(int nType) const
	{
		if(0<=nType && DAMAGE_LIST_SIZE>nType)
		{
			return m_nTypeDamage[nType];
		}
		return 0;
	}
	void SetTypeDamageByType(int nType, int nDamage)
	{
		if(0<=nType && DAMAGE_LIST_SIZE>nType)
		{
			m_nTypeDamage[nType] = nDamage;
		}
	}
	
	void Cleanup(void)
	{
		m_SenderID = -1;
		m_bIsFromeNPC = false;
		m_nSkillID = -1;
		m_nImpactID = -1;
		m_nNoTypeDamage = 0;
		m_bHit =false;
		m_nDecHp =0;
		m_bIsReflex =false;
		m_nClientShowTimes =-1; //客户端冒血的次数 -1表示不需要多次冒血
		m_nClientShowInterval =-1;//客户端多次冒血的间隔时间 
		for(int nIndex=0; DAMAGE_LIST_SIZE>nIndex; ++nIndex)
		{
			m_nTypeDamage[nIndex] = 0;
		}
	}
	DamagesInof_T(void) {Cleanup();}
	DamagesInof_T(DamagesInof_T const& rhs) :
		m_SenderID(rhs.m_SenderID), 
		m_bIsFromeNPC(rhs.m_bIsFromeNPC),
		m_nSkillID(rhs.m_nSkillID), 
		m_nImpactID(rhs.m_nImpactID), 
		m_bHit(rhs.m_bHit),
		m_nNoTypeDamage(rhs.m_nNoTypeDamage),
		m_nDecHp(rhs.m_nDecHp),
		m_bIsReflex(rhs.m_bIsReflex),
		m_nClientShowTimes(rhs.m_nClientShowTimes),
		m_nClientShowInterval(rhs.m_nClientShowInterval)

	{
		for(int nIndex=0; DAMAGE_LIST_SIZE>nIndex; ++nIndex)
		{
			m_nTypeDamage[nIndex] = rhs.m_nTypeDamage[nIndex];
		}
	}
	DamagesInof_T& operator=(DamagesInof_T const& rhs)
	{
		m_SenderID = rhs.m_SenderID;
		m_bIsFromeNPC = rhs.m_bIsFromeNPC;
		m_nSkillID = rhs.m_nSkillID;
		m_nImpactID = rhs.m_nImpactID;
		m_bHit =rhs.m_bHit;
		m_nDecHp =rhs.m_nDecHp;
		m_nNoTypeDamage = rhs.m_nNoTypeDamage;
		m_bIsReflex =rhs.m_bIsReflex;
		m_nClientShowTimes =rhs.m_nClientShowTimes;
		m_nClientShowInterval =rhs.m_nClientShowInterval;
		for(int nIndex=0; DAMAGE_LIST_SIZE>nIndex; ++nIndex)
		{
			m_nTypeDamage[nIndex] = rhs.m_nTypeDamage[nIndex];
		}
		return *this;
	}
	bool IsValid(void)
	{
		bool bRet = false;
		if(0>=m_nNoTypeDamage)
		{
			for(int nIndex=0; DAMAGE_LIST_SIZE>nIndex; ++nIndex)
			{
				if(0<m_nTypeDamage[nIndex])
				{
					bRet = true;
					break;
				}
			}
		}
		else
		{
			bRet = true;
		}
		return bRet;
	}
	//注意此函数会将分类型的伤害合计到无类型伤害中,并清除所有分类型伤害
	void TotalDamageToNotypeDamage(void)
	{
		int nDamage = m_nNoTypeDamage;
		for(int nIndex=0; DAMAGE_LIST_SIZE>nIndex; ++nIndex)
		{
			nDamage +=	m_nTypeDamage[nIndex];
			m_nTypeDamage[nIndex] = 0;
		}
		m_nNoTypeDamage = nDamage;
	}
	int GetTotalDamage(void) const
	{
		int nDamage = m_nNoTypeDamage;
		for(int nIndex=0; DAMAGE_LIST_SIZE>nIndex; ++nIndex)
		{
			nDamage +=	m_nTypeDamage[nIndex];
		}
		return nDamage;
	}
protected:
private:
	int m_SenderID; // 伤害发出者objID
	bool m_bIsFromeNPC; //伤害是否是由NPC发起的
	int m_nSkillID; //技能ID
	int m_nImpactID; //buff ID
	bool m_bHit;//是否击中
	int m_nNoTypeDamage;
	bsarray<int, DAMAGE_LIST_SIZE> m_nTypeDamage;
	int m_nDecHp;//附加的掉血值
	bool m_bIsReflex;//是否是反射回来的伤害
	int m_nClientShowTimes; //客户端冒血的次数 -1表示不需要多次冒血
	int m_nClientShowInterval;//客户端多次冒血的间隔时间 
};
//==========================伤害信息相关 End=============================================================//


#endif // !GAMESTRUCT_SKILL_H
