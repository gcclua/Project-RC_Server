/********************************************************************************
 *	文件名：	GameStruct_CombatAttr.h
 *	全路径：	\Server\Common\CombatStruct\GameStruct_CombatAttr.h
 *	创建人：	zz
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
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			m_RefixValue[i]=0;
			m_RefixPer[i]=0.0f;
		}
		m_CalculationDirtyFlag.ClearAllBits();
		m_SynDirtyFlag.ClearAllBits();
		m_BroadcastDirtyFlag.ClearAllBits();

	}
	int GetRefixValueByIndex(int index) const
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return 0;
		}
		return m_RefixValue[index];
	}

	//设置加成的具体数值
	void SetRefixValueByIndex(int index,int nValue)
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

	float GetRefixPerByIndex(int index)const
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return 0;
		}
		return m_RefixPer[index];
	}

	//设置加成的百分比
	void SetRefixPerByIndex(int index,float fPer)
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
		
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			//计算加成数值之和
			int nAddValue =AddObj.GetRefixValueByIndex(i);
			int nValue =GetRefixValueByIndex(i);
			int TotalValue =nAddValue+nValue;
			TotalRefix.SetRefixValueByIndex(i,TotalValue);
		
			
			//计算加成百分比之和
			float fAddPer =AddObj.GetRefixPerByIndex(i);
			float fPer =GetRefixPerByIndex(i);
			float fTotalPer =fAddPer+fPer;
			TotalRefix.SetRefixPerByIndex(i,fTotalPer);
		}
		return TotalRefix;
	}
	//重载+= 计算两种(比如buff 和装备)加成之和
	void operator+=(CombatAttr_Refix const& AddObj)
	{
		
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			//计算加成数值之和
			int nAddValue =AddObj.GetRefixValueByIndex(i);
			int nValue =GetRefixValueByIndex(i);
			int TotalValue =nAddValue+nValue;
			SetRefixValueByIndex(i,TotalValue);
		
			
			//计算加成百分比之和
			float fAddPer =AddObj.GetRefixPerByIndex(i);
			float fPer =GetRefixPerByIndex(i);
			float fTotalPer =fAddPer+fPer;
			SetRefixPerByIndex(i,fTotalPer);
		}
	}
	//重新计算 只要有一项有修改 全部重新计算
	bool IsCalculationFlagDirty()const
	{
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			if (m_CalculationDirtyFlag.GetBit(i))
			{
				return true;
			}
		}
		return false;
	}
	bool IsCalculationFlagDirty(int nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_CalculationDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetCalculationDirtyFlag(int nIndex,bool bDirty)
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


	bool IsSynFlagDirty(int nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_SynDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetSynDirtyFlag(int nIndex,bool bDirty)
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

	bool IsBroadcastFlagDirty(int nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_BroadcastDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetBroadcastDirtyFlag(int nIndex,bool bDirty)
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
	bsarray<int, COMBATATTR_T::COMBATATTR_MAXNUM> m_RefixValue;
	bsarray<float, COMBATATTR_T::COMBATATTR_MAXNUM> m_RefixPer;
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
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			int nAddValue =Addion.GetRefixValueByIndex(i);
			float fAddPer =Addion.GetRefixPerByIndex(i);
			int nCombatAttr =(int)((m_CombatAttr[i]+nAddValue)*(1+fAddPer));
			//统一使用set接口赋值
			ConstantAttr.SetCombatAttrByIndex(i,nCombatAttr);
		}
		return ConstantAttr;
	}
	//重载*=运算符
	void operator *=(CombatAttr_Refix const& Addion)
	{
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			int nAddValue =Addion.GetRefixValueByIndex(i);
			float fAddPer =Addion.GetRefixPerByIndex(i);
			int nCombatAttr =(int)((m_CombatAttr[i]+nAddValue)*(1+fAddPer));
			//统一使用set接口赋值
			SetCombatAttrByIndex(i,nCombatAttr);
		}
	}
	int GetCombatAttrByIndex(int index)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return 0;
		}
		return m_CombatAttr[index];
	}
	void SetCombatAttrByIndex(int index,int nValue)
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
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			if (m_CalculationDirtyFlag.GetBit(i))
			{
				return true;
			}
		}
		return false;
	}
	bool IsCalculationFlagDirty(int nIndex)const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_CalculationDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetCalculationDirtyFlag(int nIndex,bool bDirty)
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


	bool IsSynFlagDirty(int nIndex) const
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_SynDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetSynDirtyFlag(int nIndex,bool bDirty)
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

	bool IsBroadcastFlagDirty(int nIndex)
	{
		if (nIndex >=0 && nIndex<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			bool bDirty =m_BroadcastDirtyFlag.GetBit(nIndex);
			return bDirty;
		}
		return false;
	}
	void SetBroadcastDirtyFlag(int nIndex,bool bDirty)
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
	bsarray<int, COMBATATTR_T::COMBATATTR_MAXNUM> m_CombatAttr;

	typedef BitSet<COMBATATTR_T::COMBATATTR_MAXNUM> DirtyFlag;
	
	DirtyFlag m_CalculationDirtyFlag;//重新计算的脏标记
	DirtyFlag m_SynDirtyFlag;//同步自身属性的脏标记
	DirtyFlag m_BroadcastDirtyFlag;//广播自身属性的脏标记
};



#endif // !COMBATATTRSTRUCT_H
