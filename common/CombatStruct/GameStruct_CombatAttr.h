/********************************************************************************
 *	�ļ�����	GameStruct_CombatAttr.h
 *	ȫ·����	\Server\Common\CombatStruct\GameStruct_CombatAttr.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2014-1-7
 *
 *	����˵����ս�����Խṹ
 *	CombatAttr ��ָ��ս������ֵ ������ʼֵ(�޸��ּӳɵ� )������ֵ(������ּӳɺ��)
 *	CombatAttr_Refix ��ָս������ֵ�ӳ� �����ӳɵ���ֵ�Ͱٷֱ�
 *	�޸ļ�¼��
*********************************************************************************/
#ifndef COMBATATTRSTRUCT_H
#define COMBATATTRSTRUCT_H
#include "Base.h"
#include "GameDefine_CombatAttr.h"


// ս�����Լӳ�
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

	//���üӳɵľ�����ֵ
	void SetRefixValueByIndex(int index,int nValue)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return ;
		}
		m_RefixValue[index] =nValue;
		
		//���޸� ����������
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

	//���üӳɵİٷֱ�
	void SetRefixPerByIndex(int index,float fPer)
	{
		if (index<0 || index>=COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			return ;
		}
		if (fPer+1 <0)//����С��-1
		{
			fPer =-1;
		}
		m_RefixPer[index] =fPer;
		//���޸� ����������
		SetCalculationDirtyFlag(index,true);
		SetSynDirtyFlag(index,true);
		SetBroadcastDirtyFlag(index,true);
	}

	//���ؼӷ������� ��������(����buff ��װ��)�ӳ�֮��
	CombatAttr_Refix operator+(CombatAttr_Refix const& AddObj)
	{
		CombatAttr_Refix TotalRefix;
		
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			//����ӳ���ֵ֮��
			int nAddValue =AddObj.GetRefixValueByIndex(i);
			int nValue =GetRefixValueByIndex(i);
			int TotalValue =nAddValue+nValue;
			TotalRefix.SetRefixValueByIndex(i,TotalValue);
		
			
			//����ӳɰٷֱ�֮��
			float fAddPer =AddObj.GetRefixPerByIndex(i);
			float fPer =GetRefixPerByIndex(i);
			float fTotalPer =fAddPer+fPer;
			TotalRefix.SetRefixPerByIndex(i,fTotalPer);
		}
		return TotalRefix;
	}
	//����+= ��������(����buff ��װ��)�ӳ�֮��
	void operator+=(CombatAttr_Refix const& AddObj)
	{
		
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			//����ӳ���ֵ֮��
			int nAddValue =AddObj.GetRefixValueByIndex(i);
			int nValue =GetRefixValueByIndex(i);
			int TotalValue =nAddValue+nValue;
			SetRefixValueByIndex(i,TotalValue);
		
			
			//����ӳɰٷֱ�֮��
			float fAddPer =AddObj.GetRefixPerByIndex(i);
			float fPer =GetRefixPerByIndex(i);
			float fTotalPer =fAddPer+fPer;
			SetRefixPerByIndex(i,fTotalPer);
		}
	}
	//���¼��� ֻҪ��һ�����޸� ȫ�����¼���
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
	DirtyFlag m_CalculationDirtyFlag;//���¼��������
	DirtyFlag m_SynDirtyFlag;//ͬ���������Ե�����
	DirtyFlag m_BroadcastDirtyFlag;//�㲥�������Ե�����
};

// ս��������ֵ
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
	
	//���س˷������ ս����ֵ=ս����ֵ*ս���ӳ�ֵ
	//��Ҫ�����������յ�ս����ֵ�� ����ս����ֵ =ս����ʼֵ(�޼ӳ�)*���ռӳ�ֵ(buff װ���ȸ��ּӳ�֮��)
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
			//ͳһʹ��set�ӿڸ�ֵ
			ConstantAttr.SetCombatAttrByIndex(i,nCombatAttr);
		}
		return ConstantAttr;
	}
	//����*=�����
	void operator *=(CombatAttr_Refix const& Addion)
	{
		for (int i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			int nAddValue =Addion.GetRefixValueByIndex(i);
			float fAddPer =Addion.GetRefixPerByIndex(i);
			int nCombatAttr =(int)((m_CombatAttr[i]+nAddValue)*(1+fAddPer));
			//ͳһʹ��set�ӿڸ�ֵ
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
		//���޸� ����������
		SetCalculationDirtyFlag(index,true);
		SetSynDirtyFlag(index,true);
		SetBroadcastDirtyFlag(index,true);
	}

	//���¼���ʱ ֻҪ��һ������ ȫ�����¼���
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
	
	DirtyFlag m_CalculationDirtyFlag;//���¼��������
	DirtyFlag m_SynDirtyFlag;//ͬ���������Ե�����
	DirtyFlag m_BroadcastDirtyFlag;//�㲥�������Ե�����
};



#endif // !COMBATATTRSTRUCT_H
