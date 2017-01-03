#include "ImpactLogic_000.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_SkillBase.h"
#include "Message/SceneMsg.h"

POOLDEF_IMPL(ImpactLogic_000);

//buff��ʼ��Ч
void ImpactLogic_000::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		//�����������ȵ��û���� StartEffect
		ImpactBaseLogic::StartEffect(rSelf);

		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		//XP��ֻ�Է�BOSS��NPC��Ч
		if (m_ImpactStruct.m_nSkillId !=invalid_id) //XP�� ������+3
		{
			Table_SkillEx const* pSkillEx =GetTable_SkillExByID(m_ImpactStruct.m_nSkillId);
			if (pSkillEx !=null_ptr)
			{
				Table_SkillBase const* pSkillBase =GetTable_SkillBaseByID(pSkillEx->GetBaseId());
				if (pSkillBase !=null_ptr)
				{
					if (rSelf.IsNpc()==false)
					{
						return;
					}
				}
			}
		}
		Obj_CharacterPtr SenderPtr =GetImpactSender(rSelf);//ͳһʹ�ô˽ӿ�����ȡBUFF�����ߵ���Ϣ
		if (!SenderPtr)
		{
			return;
		}
		bool bIsHit =false;
		DamagesInof_T _DamageInfo;
		float fDamageRefix =rImpactData.GetParamValuebyIndex(DAMAGEREFIX)/10000.0f;
		int nDamageAdd =rImpactData.GetParamValuebyIndex(DAMAGEADD);
		int nAttackAdd =rImpactData.GetParamValuebyIndex(ATTACKADD);
		float fHpPerRefix =rImpactData.GetParamValuebyIndex(HPPERREFIX)/100.0f;
		int nHpValueRefix =rImpactData.GetParamValuebyIndex(HPVALUEREFIX);
		int nMaxHP =rSelf.GetCombatAttrByID((int)(COMBATATTR_T::MAXHP));
		int nHpDecValue =nHpValueRefix+(int)(nMaxHP*fHpPerRefix);
		int nClientShowTimes =rImpactData.GetParamValuebyIndex(CLIENTSHOWTIMES);
		int nClientShowInter =rImpactData.GetParamValuebyIndex(CLIENTSHOWINTER);
		if (rImpactData.GetParamValuebyIndex(DAMAGEREFIX)==0 &&
			nAttackAdd ==0 ) //����ȫΪ0 ���ʾֻ�ߵ�Ѫ �����˺��������� 100%����
		{
			bIsHit =true;
		}
		else
		{
			//������ɵ��˺�
			SenderPtr->CalculateAttackDamage(rSelf,bIsHit,fDamageRefix,nAttackAdd,_DamageInfo);
		}
		_DamageInfo.SetSkillID(m_ImpactStruct.m_nSkillId);
		_DamageInfo.SetImpactID(rImpactData.GetImpactID());
		_DamageInfo.SetSenderID(SenderPtr->GetID());
		_DamageInfo.SetFromNPCFlag(SenderPtr->IsNpc());

		_DamageInfo.SetHitFlag(bIsHit);
		if (nDamageAdd >0)
		{
			_DamageInfo.SetNotypeDamage(nDamageAdd); //���ӵ��������˺�
		}
		if (bIsHit)
		{
			_DamageInfo.SetDecHp(nHpDecValue);//���ӵ�Ѫ
		}
		_DamageInfo.SetIsReflex(false);
		_DamageInfo.SetClientShowTimes(nClientShowTimes);
		_DamageInfo.SetClientShowInterval(nClientShowInter);
		SenderPtr->OnSendDamageToUnit(rSelf,_DamageInfo);
		
		
		//Ŀǰֻ��Npc ���л��� ���� ����
		if (rSelf.IsNpc())
		{
			Obj_Npc& _objNpc =dynamic_cast<Obj_Npc&>(rSelf);
			int nAttcakDownRate =rImpactData.GetParamValuebyIndex(ATTACKDOWNRATE);
			int nRandNum =Random::Gen(0,100);
			int nMoveSpeedAttr =_objNpc.GetCombatAttrByID(COMBATATTR_T::MOVESPEED);
			//����
			if (nRandNum<nAttcakDownRate 
				&& _DamageInfo.GetTotalDamage()>0) //�ܵ��˺��ų�����
			{
				rSelf.BroadCastAnimState((int)ANIMATIONSTATE_T::STATE_ATTACKDOWN);
			}
			//��������л��� (�����ƶ��Ĺ��� �Ͳ������ɴ�����)
			if (rSelf.IsDie() &&  nMoveSpeedAttr>0)
			{
				
				int nAttackFlyRate =rImpactData.GetParamValuebyIndex(ATTACKFLYRATE);
				int nMaxDis =rImpactData.GetParamValuebyIndex(ATTACKFLYMAXDIS);
				int nMinDis =rImpactData.GetParamValuebyIndex(ATTACKFLYMINDIS);

				int nMaxHight =rImpactData.GetParamValuebyIndex(ATTACKFLYMAXHIGHT);
				int nMinHight =rImpactData.GetParamValuebyIndex(ATTACKFLYMINHIGHT);

				int nDis =Random::Gen(nMinDis,nMaxDis+1);
				int nHight =Random::Gen(nMinHight,nMaxHight+1);
				int nFlyTime =rImpactData.GetParamValuebyIndex(ATTACKFLYTIME);
				//���빥���ߵľ��� 
				int nDiffDis =(int)(rSelf.GetScenePos().Distance(SenderPtr->GetScenePos()));
				nRandNum =Random::Gen(0,100);
				if (nRandNum <nAttackFlyRate)
				{
					int nFlyDis =_MAX(2,nDis-nDiffDis);
					AttackFlyMsgPtr MsgPtr = POOLDEF_NEW(AttackFlyMsg);
					AssertEx(MsgPtr,"");
					MsgPtr->m_nObjId = rSelf.GetID();
					MsgPtr->m_nDis   = nFlyDis;
					MsgPtr->m_nHight = nHight;
					MsgPtr->m_nFlyTime = nFlyTime;
					MsgPtr->m_nSceneId = rSelf.GetSceneInstID();
					rScene.BroadCast_InSight_Include(MsgPtr,rSelf.GetID());

					
					
				}
				else 
				{
					Table_RoleBaseAttr const* pRoleInfo =GetTable_RoleBaseAttrByID(rSelf.GetDataID());
					//�����ر�����
					if (pRoleInfo!=null_ptr && pRoleInfo->GetIsAttackFly()==1)
					{
						AttackFlyMsgPtr MsgPtr = POOLDEF_NEW(AttackFlyMsg);
						AssertEx(MsgPtr,"");
						MsgPtr->m_nObjId = rSelf.GetID();
						MsgPtr->m_nDis   = 2;
						MsgPtr->m_nHight = 4;
						MsgPtr->m_nFlyTime = 300;
						MsgPtr->m_nSceneId = rSelf.GetSceneInstID();
						rScene.BroadCast_InSight_Include(MsgPtr,rSelf.GetID());
					}
				}
			}
		}
	__LEAVE_FUNCTION
}
