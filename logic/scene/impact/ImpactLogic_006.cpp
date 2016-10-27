#include "ImpactLogic_006.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"

POOLDEF_IMPL(ImpactLogic_006);

void ImpactLogic_006::InitImpactDataInfo(ImpactStruct& rImpactStruct)
{
	__ENTER_FUNCTION
		//!!!先调用基类的 初始化
		ImpactBaseLogic::InitImpactDataInfo(rImpactStruct);

		
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rLine =*(m_ImpactStruct.m_pImpactDataInfo);
		m_ImpactStruct.m_fContinuTime =rLine.GetParamValuebyIndex(CONTINUTIME)/1000.0f;
		m_ImpactStruct.m_nIntervalTime =rLine.GetParamValuebyIndex(INTERTIME);
	__LEAVE_FUNCTION
}
void ImpactLogic_006::OnIntervalOver(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Obj_CharacterPtr SendPtr =GetImpactSender(rSelf);//统一使用此接口来获取BUFF发送者的信息
		if (!SendPtr)
		{
			return;
		}
		//注:该6号逻辑BUFF的发送者针对该BUFF拥有者发送子buff
		for (int i=0;i<MAXBUFFNUM;i++)
		{
			int nImpactId =rImpactData.GetParamValuebyIndex(BUFFID_01+i);
			//任何效果逻辑自己不能把自己当成子效果派发出去
			if (nImpactId !=invalid_id && CheckSubImpactIsMyself(nImpactId)==false)
			{
				SendPtr->SendImpactToUnit(rSelf,nImpactId,m_ImpactStruct.m_nSkillId);
			}
		}
	__LEAVE_FUNCTION
}