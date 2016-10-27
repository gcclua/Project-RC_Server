#include "ImpactLogic_001.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Obj/Obj_Character.h"
#include "Table/Table_Impact.h"

POOLDEF_IMPL(ImpactLogic_001);

void ImpactLogic_001::InitImpactDataInfo(ImpactStruct& rImpactStruct)
{
	__ENTER_FUNCTION
		//!!!先调用基类的 初始化
		ImpactBaseLogic::InitImpactDataInfo(rImpactStruct);
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rLine =*(m_ImpactStruct.m_pImpactDataInfo);
		m_ImpactStruct.m_fContinuTime =rLine.GetParamValuebyIndex(CONTINUETIME)/1000.0f;
	__LEAVE_FUNCTION
}
void ImpactLogic_001::OnNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)
{
	__ENTER_FUNCTION
		//如果有标记BUFF 则只对拥有标记BUFF的伤害发送者发送的伤害做修正
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		int nDamageType =rImpactData.GetParamValuebyIndex(DAMAGETYPETYPE);
		if (nDamageType !=NOTYPE)
		{
			return;
		}
		bool bIsDecByMuti =(rImpactData.GetParamValuebyIndex(ISDECBYMULTI)==1);//是否乘法减免
		if (bIsDecByMuti)
		{
			return;
		}
		int nFlagBuffId =rImpactData.GetParamValuebyIndex(FLAGBUFFID);
		if (nFlagBuffId !=invalid_id)
		{
			if (rSelf.IsSceneValid() ==false)
			{
				return;
			}
			Scene &rScene =rSelf.GetScene();
			Obj_CharacterPtr _DamageSenderPtr =rScene.GetCharacterByID(rSelfDamage.GetSenderID());
			if (_DamageSenderPtr)
			{
				if(_DamageSenderPtr->IsHaveImpact(nFlagBuffId) ==false)
				{
					return;
				}
			}
		}
		int nRefixValue =rImpactData.GetParamValuebyIndex(VALUE);
		float fRefixPer =rImpactData.GetParamValuebyIndex(PER)/10000.0f;
		int nNoTypeDamage =rRefixDamage.GetNotypeDamage();
		nNoTypeDamage =(int)(nNoTypeDamage+nRefixValue+rSelfDamage.GetNotypeDamage()*fRefixPer);
		rRefixDamage.SetNotypeDamage(nNoTypeDamage);
	__LEAVE_FUNCTION
}
void ImpactLogic_001::OnTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		int nDamageType =rImpactData.GetParamValuebyIndex(DAMAGETYPETYPE);
		if (nDamageType ==NOTYPE)
		{
			return;
		}
		bool bIsDecByMuti =(rImpactData.GetParamValuebyIndex(ISDECBYMULTI)==1);//是否乘法减免
		if (bIsDecByMuti)
		{
			return;
		}
		//如果有标记BUFF 则只对拥有标记BUFF的伤害发送者发送的伤害做修正
		int nFlagBuffId =rImpactData.GetParamValuebyIndex(FLAGBUFFID);
		if (nFlagBuffId !=invalid_id)
		{
			if (rSelf.IsSceneValid() ==false)
			{
				return;
			}
			Scene &rScene =rSelf.GetScene();
			Obj_CharacterPtr _DamageSenderPtr =rScene.GetCharacterByID(rSelfDamage.GetSenderID());
			if (_DamageSenderPtr)
			{
				if(_DamageSenderPtr->IsHaveImpact(nFlagBuffId) ==false)
				{
					return;
				}
			}
		}
		int nRefixValue =rImpactData.GetParamValuebyIndex(VALUE);
		float fRefixPer =rImpactData.GetParamValuebyIndex(PER)/10000.0f;
		//物理伤害修正
	
		int nPhyTypeDamage =rRefixDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS);
		nPhyTypeDamage =(int)(nPhyTypeDamage+nRefixValue+rSelfDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS)*fRefixPer);
		rRefixDamage.SetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS,nPhyTypeDamage);
		
	__LEAVE_FUNCTION
}

bool ImpactLogic_001::IsDecNoTypedDamagebyMulti(void)//是否是按累乘减免无类型伤害
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return false;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		int nDamageType =rImpactData.GetParamValuebyIndex(DAMAGETYPETYPE);
		if (nDamageType !=NOTYPE)
		{
			return false;
		}
		bool bIsDecByMuti =(rImpactData.GetParamValuebyIndex(ISDECBYMULTI)==1);//是否乘法减免
		if (bIsDecByMuti ==false)
		{
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
	
}
float ImpactLogic_001::GetDecNoTypedDamagebyMulti(void)//按累乘减免类型无伤害的百分比
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return 0.0f;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		if (IsDecNoTypedDamagebyMulti()==false)
		{
			return 0.0f;
		}
		return (0-(rImpactData.GetParamValuebyIndex(PER)/10000.0f));
	__LEAVE_FUNCTION
		return 0.0f;
}
