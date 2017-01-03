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
		//!!!�ȵ��û���� ��ʼ��
		ImpactBaseLogic::InitImpactDataInfo(rImpactStruct);
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rLine =*(m_ImpactStruct.m_pImpactDataInfo);
		m_ImpactStruct.m_fContinuTime =rLine.GetParamValuebyIndex(CONTINUETIME)/1000.0f;
	__LEAVE_FUNCTION
}

//buff��ʼ��Ч
void ImpactLogic_007::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		if (rSelf.IsNpc() ==false) //ֻ��NPC��Ч
		{
			return;
		}
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		int nSkillId =m_ImpactStruct.m_nSkillId;
		//XP���ܷ�����Ⱥ��Ч�� ֻ�Է�BOSS���NPC��Ч
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
		//�����������ȵ��û���� StartEffect
		ImpactBaseLogic::StartEffect(rSelf);
		int nSendId =m_ImpactStruct.m_nSenderObjId;
		Obj_CharacterPtr SendPtr =GetImpactSender(rSelf);//ͳһʹ�ô˽ӿ�����ȡBUFF�����ߵ���Ϣ
		if (!SendPtr)
		{
			return;
		}
		//����Ŀ���ʳ���buff�ķ�����
		rSelf.ChangeCurSelectObjId(nSendId);
		//�յ����
		rSelf.OnThreat(*SendPtr,10);
		
	__LEAVE_FUNCTION
}
