#include "ImpactLogic_007.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Obj/Obj_Npc.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(ImpactLogic_007);

void ImpactLogic_007::InitImpactDataInfo(ImpactStruct& rImpactStruct)
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

//buff开始生效
void ImpactLogic_007::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		if (rSelf.IsNpc() ==false) //只对NPC有效
		{
			return;
		}
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		int nSkillId =m_ImpactStruct.m_nSkillId;
		//XP技能发出的群嘲效果 只对非BOSS类的NPC有效
		if (nSkillId !=invalid_id)
		{
			Table_SkillEx const* pSkillEx =GetTable_SkillExByID(nSkillId);
			if (null_ptr ==pSkillEx)
			{
				return;
			}
			Table_SkillBase const* pSkillBase =GetTable_SkillBaseByID(pSkillEx->GetBaseId());
			if (pSkillBase ==null_ptr)
			{
				return;
			}
		
			if (false ==rSelf.IsNpc())
			{
				return;
			}

		}
		//！！！！！先调用基类的 StartEffect
		ImpactBaseLogic::StartEffect(rSelf);
		int nSendId =m_ImpactStruct.m_nSenderObjId;
		Obj_CharacterPtr SendPtr =GetImpactSender(rSelf);//统一使用此接口来获取BUFF发送者的信息
		if (!SendPtr)
		{
			return;
		}
		//更改目标问嘲讽buff的发送者
		rSelf.ChangeCurSelectObjId(nSendId);
		//收到仇恨
		rSelf.OnThreat(*SendPtr,10);
		
	__LEAVE_FUNCTION
}
