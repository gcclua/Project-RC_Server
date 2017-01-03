/********************************************************************************
 *	文件名：	GameStruct_CombatAttr.h
 *	全路径：	\Server\Common\CombatStruct\GameStruct_CombatAttr.h
 *	创建人：	罗勇
 *	创建时间：2014-1-7
 *
 *	功能说明：战斗属性结构
 *	CombatAttr 是指是战斗的数值 包括初始值(无各种加成的 )和最终值(计算各种加成后的)
 *	CombatAttr_Refix 是指战斗的数值加成 包括加成的数值和百分比
 *	修改记录：
*********************************************************************************/
#ifndef COMBATATTRSTRUCT_H
#define COMBATATTRSTRUCT_H
#include "Base.h"
#include "GameDefine_CombatAttr.h"


// 战斗属性加成
struct CombatAttr_Refix
{
public:

	CombatAttr_Refix()
	{
		CleanUp();
	}
	void CleanUp()
	{
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			m_RefixValue[i]=0;
			m_RefixPer[i]=0.0f;
		}
		m_CalculationDirtyFlag.ClearAllBits();
		m_SynDirtyFlag.ClearAllBits();
		m_BroadcastDirtyFlag.ClearAllBits();

	}
	tint32 GetRefixValueByIndex(tint32 index) const
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return 0;
		}
		return m_RefixValue[index];
	}

	//设置加成的具体数值
	void SetRefixValueByIndex(tint32 index,int nValue)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return ;
		}
		m_RefixValue[index] =nValue;
		
		//有修改 将脏标记置上
		SetCalculationDirtyFlag(index,true);
		SetSynDirtyFlag(index,true);
		SetBroadcastDirtyFlag(index,true);
	}

	tfloat32 GetRefixPerByIndex(tint32 index)const
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return 0;
		}
		return m_RefixPer[index];
	}

	//设置加成的百分比
	void SetRefixPerByIndex(tint32 index,float fPer)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return ;
		}
		if (fPer+1 <0)//不能小于-1
		{
			fPer =-1;
		}
		m_RefixPer[index] =fPer;
		//有修改 将脏标记置上
		SetCalculationDirtyFlag(index,true);
		SetSynDirtyFlag(index,true);
		SetBroadcastDirtyFlag(index,true);
	}

	//重载加法操作符 计算两种(比如buff 和装备)加成之和
	CombatAttr_Refix operator+(CombatAttr_Refix const& AddObj)
	{
		CombatAttr_Refix TotalRefix;
		
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			//计算加成数值之和
			tint32 nAddValue =AddObj.GetRefixValueByIndex(i);
			tint32 nValue =GetRefixValueByIndex(i);
			tint32 TotalValue =nAddValue+nValue;
			TotalRefix.SetRefixValueByIndex(i,TotalValue);
		
			
			//计算加成百分比之和
			tfloat32 fAddPer =AddObj.GetRefixPerByIndex(i);
			tfloat32 fPer =GetRefixPerByIndex(i);
			tfloat32 fTotalPer =fAddPer+fPer;
			TotalRefix.SetRefixPerByIndex(i,fTotalPer);
		}
		return TotalRefix;
	}
	//重载+= 计算两种(比如buff 和装备)加成之和
	void operator+=(CombatAttr_Refix const& AddObj)
	{
		
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			//计算加成数值之和
			tint32 nAddValue =AddObj.GetRefixValueByIndex(i);
			tint32 nValue =GetRefixValueByIndex(i);
			tint32 TotalValue =nAddValue+nValue;
			SetRefixValueByIndex(i,TotalValue);
		
			
			//计算加成百分比之和
			tfloat32 fAddPer =AddObj.GetRefixPerByIndex(i);
			tfloat32 fPer =GetRefixPerByIndex(i);
			tfloat32 fTotalPer =fAddPer+fPer;
			SetRefixPerByIndex(i,fTotalPer);
		}
	}
	//重新计算 只要有一项有修改 全部重新计算
	bool IsCalculationFlagDirty()const
	{
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			if (m_CalculationDirtyFlag.GetBit(i))
			{
				return true;
			}
		}
		return false;
	}
	bool IsCalculationFlagDirty(tint32 nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_CalculationDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetCalculationDirtyFlag(tint32 nIndex,bool bDirty)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			m_CalculationDirtyFlag.SetBit(nIndex,bDirty);
		}
	}
	void CleanAllCalculationDirtyFlag()
	{
		m_CalculationDirtyFlag.ClearAllBits();
	}
	void MarkAllCalculationDirtyFlag()
	{
		m_CalculationDirtyFlag.MarkAllBits();
	}


	bool IsSynFlagDirty(tint32 nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_SynDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetSynDirtyFlag(tint32 nIndex,bool bDirty)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			m_SynDirtyFlag.SetBit(nIndex,bDirty);
		}
	}
	void CleanAllSynDirtyFlag()
	{
		m_SynDirtyFlag.ClearAllBits();
	}
	void MarkAllSynDirtyFlag()
	{
		m_SynDirtyFlag.MarkAllBits();
	}

	bool IsBroadcastFlagDirty(tint32 nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_BroadcastDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetBroadcastDirtyFlag(tint32 nIndex,bool bDirty)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			m_BroadcastDirtyFlag.SetBit(nIndex,bDirty);
		}
	}
	void CleanAllBroadcastDirtyFlag()
	{
		m_BroadcastDirtyFlag.ClearAllBits();
	}
	void MarkAllBroadcastDirtyFlag()
	{
		m_BroadcastDirtyFlag.MarkAllBits();
	}
private:
	typedef BitSet<COMBATATTR_T::COMBATATTR_MAXNUM> DirtyFlag;
	bsarray<tint32, COMBATATTR_T::COMBATATTR_MAXNUM> m_RefixValue;
	bsarray<tfloat32, COMBATATTR_T::COMBATATTR_MAXNUM> m_RefixPer;
	DirtyFlag m_CalculationDirtyFlag;//重新计算的脏标记
	DirtyFlag m_SynDirtyFlag;//同步自身属性的脏标记
	DirtyFlag m_BroadcastDirtyFlag;//广播自身属性的脏标记
};

// 战斗属性数值
struct CombatAttr
{
public:
	
	CombatAttr()
	{
		CleanUp();
	}
	void CleanUp()
	{
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			m_CombatAttr[i] =0;
		}
		m_CalculationDirtyFlag.ClearAllBits();
		m_SynDirtyFlag.ClearAllBits();
		m_BroadcastDirtyFlag.ClearAllBits();
	}
	
	//重载乘法运算符 战斗数值=战斗数值*战斗加成值
	//主要用来计算最终的战斗数值： 最终战斗数值 =战斗初始值(无加成)*最终加成值(buff 装备等各种加成之和)
	//CombatAttr initial
	//CombatAttr_Refix FinalyAddition
	//CombatAttr Finaly =initial*FinalyAddition;
	CombatAttr operator *(CombatAttr_Refix const& Addion)
	{
		CombatAttr ConstantAttr;
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			tint32 nAddValue =Addion.GetRefixValueByIndex(i);
			tfloat32 fAddPer =Addion.GetRefixPerByIndex(i);
			tint32 nCombatAttr =(int)((m_CombatAttr[i]+nAddValue)*(1+fAddPer));
			//统一使用set接口赋值
			ConstantAttr.SetCombatAttrByIndex(i,nCombatAttr);
		}
		return ConstantAttr;
	}
	//重载*=运算符
	void operator *=(CombatAttr_Refix const& Addion)
	{
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			tint32 nAddValue =Addion.GetRefixValueByIndex(i);
			tfloat32 fAddPer =Addion.GetRefixPerByIndex(i);
			tint32 nCombatAttr =(int)((m_CombatAttr[i]+nAddValue)*(1+fAddPer));
			//统一使用set接口赋值
			SetCombatAttrByIndex(i,nCombatAttr);
		}
	}
	tint32 GetCombatAttrByIndex(tint32 index)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return 0;
		}
		return m_CombatAttr[index];
	}
	void SetCombatAttrByIndex(tint32 index,int nValue)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return;
		}
		m_CombatAttr[index] =nValue;
		//有修改 将脏标记置上
		SetCalculationDirtyFlag(index,true);
		SetSynDirtyFlag(index,true);
		SetBroadcastDirtyFlag(index,true);
	}

	//重新计算时 只要有一项脏了 全部重新计算
	bool IsCalculationFlagDirty()const
	{
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			if (m_CalculationDirtyFlag.GetBit(i))
			{
				return true;
			}
		}
		return false;
	}
	bool IsCalculationFlagDirty(tint32 nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_CalculationDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetCalculationDirtyFlag(tint32 nIndex,bool bDirty)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			m_CalculationDirtyFlag.SetBit(nIndex,bDirty);
		}
	}
	void CleanAllCalculationDirtyFlag()
	{
		m_CalculationDirtyFlag.ClearAllBits();
	}
	void MarkAllCalculationDirtyFlag()
	{
		m_CalculationDirtyFlag.MarkAllBits();
	}


	bool IsSynFlagDirty(tint32 nIndex) const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_SynDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetSynDirtyFlag(tint32 nIndex,bool bDirty)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			m_SynDirtyFlag.SetBit(nIndex,bDirty);
		}
	}
	void CleanAllSynDirtyFlag()
	{
		m_SynDirtyFlag.ClearAllBits();
	}
	void MarkAllSynDirtyFlag()
	{
		m_SynDirtyFlag.MarkAllBits();
	}

	bool IsBroadcastFlagDirty(tint32 nIndex)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_BroadcastDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetBroadcastDirtyFlag(tint32 nIndex,bool bDirty)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			m_BroadcastDirtyFlag.SetBit(nIndex,bDirty);
		}
	}
	void CleanAllBroadcastDirtyFlag()
	{
		m_BroadcastDirtyFlag.ClearAllBits();
	}
	void MarkAllBroadcastDirtyFlag()
	{
		m_BroadcastDirtyFlag.MarkAllBits();
	}
private:
	bsarray<tint32, COMBATATTR_T::COMBATATTR_MAXNUM> m_CombatAttr;

	typedef BitSet<COMBATATTR_T::COMBATATTR_MAXNUM> DirtyFlag;
	
	DirtyFlag m_CalculationDirtyFlag;//重新计算的脏标记
	DirtyFlag m_SynDirtyFlag;//同步自身属性的脏标记
	DirtyFlag m_BroadcastDirtyFlag;//广播自身属性的脏标记
};

// 归属信息
struct BelongInfo
{
	tint32 m_nTeamID;	//队伍ID		
	tint32 m_nObjID;	//objID	
	tint32 m_nHP;		//伤害
	tint32 m_nScore;	//积分
	BelongInfo(void) {
		Clear();
	}		
	BelongInfo(tint32 nTeamID,tint32 nObjID,tint32 nHP) {
		m_nHP = nHP;
		m_nTeamID = nTeamID;
		m_nObjID = nObjID;
		m_nScore = 0;
	}		
	void Clear()
	{
		m_nTeamID = invalid_id;
		m_nObjID = invalid_id;
		m_nHP = 0;
		m_nScore = 0;
	}
};


#endif // !COMBATATTRSTRUCT_H
