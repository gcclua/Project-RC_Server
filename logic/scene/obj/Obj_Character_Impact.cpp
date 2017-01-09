#include "Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Scene/GameInterface_Scene.h"
#include "ImpactStruct/GameStruct_Impact.h"
#include "Table/Table_Impact.h"

#include "Scene/Impact/ImpactLogic_000.h"
#include "Scene/Impact/ImpactLogic_001.h"
#include "Scene/Impact/ImpactLogic_002.h"
#include "Scene/Impact/ImpactLogic_003.h"
#include "Scene/Impact/ImpactLogic_004.h"
#include "Scene/Impact/ImpactLogic_005.h"
#include "Scene/Impact/ImpactLogic_006.h"
#include "Scene/Impact/ImpactLogic_007.h"


void Obj_Character::Tick_Impact(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		Tick_ImpactClean();
		Tick_ImpactAdd();
		Tick_ImapctRun(rTimeInfo);
	__LEAVE_FUNCTION

}

bool Obj_Character::IsHaveImpact(int nImpactId) const
{
	__ENTER_FUNCTION
		if (nImpactId < 0)
		{
			return false;
		}
		for (ImpactPtrList::const_iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
		{
			ImpactBaseLogicPtr impLogicPtr =*it;
			if (impLogicPtr)
			{
				if (impLogicPtr->IsActive()  && impLogicPtr->GetImpatInfo().m_nImpactId == nImpactId)
				{
					return true;
				}
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}

void Obj_Character::CleanAllImpact(void)
{
	__ENTER_FUNCTION
		
		for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				//�����BUFF��ɢ��
				if (ImpactLogicPtr->IsActive())
				{
					ImpactLogicPtr->OnFadeOut(*this);
				}
			}
		}
	__LEAVE_FUNCTION
}
bool Obj_Character::RemoveImpactById(int nImpactId)
{
	__ENTER_FUNCTION
		
		for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				//�ҵ��� �����BUFF��ɢ��
				if (ImpactLogicPtr->IsActive() && ImpactLogicPtr->GetImpatInfo().m_nImpactId ==nImpactId)
				{
					
					ImpactLogicPtr->OnFadeOut(*this);
					return true;
				}
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}

void Obj_Character::AddImpact(ImpactBaseLogicPtr InstancePtr)
{
	__ENTER_FUNCTION
	m_CachebuffList.push_back(InstancePtr);
	__LEAVE_FUNCTION
	
}

void Obj_Character::_AddImpactImmediate(ImpactBaseLogicPtr InstancePtr)
{
	__ENTER_FUNCTION
	int nBuffListSize =static_cast<int>(m_buffList.size());
	if (nBuffListSize >=MAX_BUFF_SIZE)
	{
		return;
	}
	m_buffList.push_back(InstancePtr);
	__LEAVE_FUNCTION
}

ImpactPtrList::iterator Obj_Character:: _DelImpactImmediate(ImpactPtrList::iterator itRemove)
{
	ImpactPtrList::iterator it =m_buffList.erase(itRemove);
	return it;
}

void  Obj_Character::Tick_ImpactAdd(void)
{
	__ENTER_FUNCTION
	
	for (ImpactPtrList::iterator it = m_CachebuffList.begin(); it != m_CachebuffList.end(); ++it)
	{
		if (m_buffList.size() >= MAX_BUFF_SIZE)
		{
			break;
		}
		m_buffList.push_back(*it);
	}
	m_CachebuffList.clear();
	__LEAVE_FUNCTION
}

void  Obj_Character::Tick_ImpactClean(void)
{
	__ENTER_FUNCTION
	
	for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end();)
	{
		if (*it && !(*it)->IsActive())
		{
			// ��Ч�� ɾ��
			it = m_buffList.erase(it);
			continue;
		}
		++it;
	}
	__LEAVE_FUNCTION
}

//�������Ҫ�ڵ�¼ʱ�����BUFF
void Obj_Character::CleanUpImpactOnLogin(void)
{
	__ENTER_FUNCTION
		
		for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
		{
			ImpactBaseLogicPtr impactLogicPtr =*it;
			if (impactLogicPtr)
			{
				ImpactStruct const& rImpactInfo =impactLogicPtr->GetImpatInfo();
				if (rImpactInfo.IsVaild() && impactLogicPtr->IsActive())
				{
					if (rImpactInfo.m_pImpactDataInfo != null_ptr)
					{
						const int nFadeOutRule = rImpactInfo.m_pImpactDataInfo->GetFadeOutRule();
						if (nFadeOutRule != -1 &&
							(nFadeOutRule & BUFFFADEOUTRULE::ONLOGIN) != 0)
						{
							impactLogicPtr->OnFadeOut(*this);
						}
					}
				}
			}
		}
	__LEAVE_FUNCTION
}

void Obj_Character::Tick_ImapctRun(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
	
	for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
	{
		//��Ч �򼤻�����
		ImpactBaseLogicPtr _ImpactLogicPtr =*it;
		if (_ImpactLogicPtr)
		{
			ImpactStruct const& ImpactInfo =_ImpactLogicPtr->GetImpatInfo();
			if (ImpactInfo.IsVaild())
			{
				if (_ImpactLogicPtr->IsActive() ==false)
				{
					_ImpactLogicPtr->OnActive(*this);
				}
				_ImpactLogicPtr->Tick(rTimeInfo,*this);
			}
		}
	}
	__LEAVE_FUNCTION
}

void Obj_Character::SendImpactToUnit(Obj_Character& rTarget,int nImpactId,int nSkillId)
{
	__ENTER_FUNCTION
		if (nImpactId ==invalid_id)
		{
			return;
		}
		const Table_Impact*  pLine =GetTable_ImpactByID(nImpactId);
		if (pLine ==null_ptr)
		{
			return;
		}
		const Table_Impact&  rLine =*pLine;
		
		if (rLine.GetBuffType()==BUFFTYPE::DEBUFF)
		{
			//����DEBUFF ��ɳ�� ��Ŀ�������в���б�
			OnThreat(rTarget,1);//��һ���� ǿ���ù���Ŀ������Լ��ĳ���б� 
			
			//����������Ҫ��ɢ��BUFF (DEBUFF �㷢������)
			
			for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
			{
				ImpactBaseLogicPtr _ImpactLogicPtr =*it;
				//��Ч
				if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
				{
					if (_ImpactLogicPtr->IsFadeoutWhenSendAttack())
					{
						_ImpactLogicPtr->OnFadeOut(*this);
					}
				}
			}
		}
		rTarget.ReceiveImpact(nImpactId,nSkillId,*this);
	__LEAVE_FUNCTION
}

ImpactBaseLogicPtr Obj_Character::CreateImpactInstanceById(int nLogicId)
{
	__ENTER_FUNCTION
		ImpactBaseLogicPtr InstancePtr ;
		switch (nLogicId)
		{
		case ImpactBaseLogic::IMPACT_000:
			{
				ImpactLogic_000Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_000);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_000>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_001:
			{
				ImpactLogic_001Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_001);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_001>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_002:
			{
				ImpactLogic_002Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_002);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_002>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_003:
			{
				ImpactLogic_003Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_003);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_003>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_004:
			{
				ImpactLogic_004Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_004);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_004>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_005:
			{
				ImpactLogic_005Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_005);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_005>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_006:
			{
				ImpactLogic_006Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_006);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_006>(LogicPtr); 
			}
			break;
		case ImpactBaseLogic::IMPACT_007:
			{
				ImpactLogic_007Ptr LogicPtr =POOLDEF_NEW(ImpactLogic_007);
				AssertEx(LogicPtr, "");
				InstancePtr=boost::static_pointer_cast<ImpactBaseLogic,ImpactLogic_007>(LogicPtr); 
			}
			break;
		default:
			break;
		}
		return InstancePtr;
	__LEAVE_FUNCTION
		ImpactBaseLogicPtr InvaildPtr ;
		return InvaildPtr;
}

void Obj_Character::ReceiveImpact(int nImpactId,int nSkillId,Obj_Character& rSender)
{
	__ENTER_FUNCTION
		const Table_Impact*  pLine =GetTable_ImpactByID(nImpactId);
		if (pLine ==null_ptr)
		{
			return;
		}
		if (IsSceneValid() ==false)
		{
			return;
		}
		Scene& rScene =GetScene();
		//GOD ģʽ�²����κμ���BUFF
		if (pLine->GetBuffType()==BUFFTYPE::DEBUFF)
		{
			//�ܵ�DEBUFF ��ɳ��
			OnThreat(rSender,10);
			InAttacked(rSender);
			
			//�ܵ�DEBUFF BUFF����
			for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
			{
				//��Ч
				ImpactBaseLogicPtr _ImpactLogicPtr =*it;
				if (_ImpactLogicPtr && _ImpactLogicPtr->IsActive() && _ImpactLogicPtr->IsEffect())
				{
					//�޵�buff
					if (_ImpactLogicPtr->IsGODModel())
					{
						return;
					}
					//�յ�������ɢ��BUFF (DEBUFF ��ʾ�ܵ�����)
					if (_ImpactLogicPtr->IsFadeoutWhenReceiveAttack()) 
					{
						_ImpactLogicPtr->OnFadeOut(*this);
					}
					else
					{
						_ImpactLogicPtr->OnAttack(*this,rSender);
					}
				}
			}
			//�ܵ�DEBUFF ���ܴ���
			if (IsUsingSkill())
			{
				AssertEx(m_CurSkillLogicPtr, "");
				//�����޵�
				if (m_CurSkillLogicPtr->IsSkillGod())
				{
					return;
				}
				//�����ܹ�������
				m_CurSkillLogicPtr->OnBeAttacked(*this);
			}
		}
		const Table_Impact& rLine =*pLine;
		
		ImpactBaseLogicPtr impactPtr =CreateImpactInstanceById(rLine.GetLogicID());
		if (!impactPtr)
		{
			return;
		}
		ImpactStruct tmpImpStruct;
		tmpImpStruct.CleanUp();
		tmpImpStruct.m_nImpactId =rLine.GetImpactID();//BuffId
		tmpImpStruct.m_nSkillId =nSkillId;//����ID
		tmpImpStruct.m_nSenderType =rSender.GetObjType();//���������
		//����������Һ� ����¼GUID
		if (rSender.IsHero())
		{
			Obj_Hero& rSendHero =dynamic_cast<Obj_Hero&>(rSender);
			tmpImpStruct.m_SenderGuid =rSendHero.GetUID();
		}
	
		tmpImpStruct.m_nSceneClassId =rScene.GetSceneClassID();//���͵ĳ���ID
		tmpImpStruct.m_nSceneInstanceId =rScene.GetSceneInstID();//���͵ĳ���ʵ��ID
		tmpImpStruct.m_nSenderObjId =rSender.GetID();//������objId
		tmpImpStruct.m_nDelayTime =rLine.GetDelayTime();//�ӳ���Чʱ��
		tmpImpStruct.m_pImpactDataInfo =pLine;//�����Ϣ
		impactPtr->InitImpactDataInfo(tmpImpStruct);
		AddImpact(impactPtr);
	__LEAVE_FUNCTION
}

bool Obj_Character::IsHaveImpactFadeoutReceiveDamage()
{
	__ENTER_FUNCTION
		for (ImpactPtrList::iterator it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				if (ImpactLogicPtr->IsActive() && ImpactLogicPtr->IsEffect())
				{
					if (ImpactLogicPtr->IsFadeoutWhenReceiveDamage())
					{
						return true;
					}
				}
			}
		}
	return false;
	__LEAVE_FUNCTION
	return false;
}