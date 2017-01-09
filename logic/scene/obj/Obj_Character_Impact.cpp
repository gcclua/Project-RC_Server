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
				//让这个BUFF消散掉
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
				//找到了 让这个BUFF消散掉
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
			// 无效了 删除
			it = m_buffList.erase(it);
			continue;
		}
		++it;
	}
	__LEAVE_FUNCTION
}

//清除下需要在登录时清除的BUFF
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
		//有效 则激活心跳
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
			//发送DEBUFF 造成仇恨 将目标加入威胁度列表
			OnThreat(rTarget,1);//加一点仇恨 强制让攻击目标进入自己的仇恨列表 
			
			//发出攻击需要消散的BUFF (DEBUFF 算发出攻击)
			
			for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
			{
				ImpactBaseLogicPtr _ImpactLogicPtr =*it;
				//有效
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
		//GOD 模式下不吃任何减益BUFF
		if (pLine->GetBuffType()==BUFFTYPE::DEBUFF)
		{
			//受到DEBUFF 造成仇恨
			OnThreat(rSender,10);
			InAttacked(rSender);
			
			//受到DEBUFF BUFF处理
			for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
			{
				//有效
				ImpactBaseLogicPtr _ImpactLogicPtr =*it;
				if (_ImpactLogicPtr && _ImpactLogicPtr->IsActive() && _ImpactLogicPtr->IsEffect())
				{
					//无敌buff
					if (_ImpactLogicPtr->IsGODModel())
					{
						return;
					}
					//收到攻击消散的BUFF (DEBUFF 表示受到攻击)
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
			//受到DEBUFF 技能处理
			if (IsUsingSkill())
			{
				AssertEx(m_CurSkillLogicPtr, "");
				//技能无敌
				if (m_CurSkillLogicPtr->IsSkillGod())
				{
					return;
				}
				//技能受攻击处理
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
		tmpImpStruct.m_nSkillId =nSkillId;//技能ID
		tmpImpStruct.m_nSenderType =rSender.GetObjType();//发送者类别
		//发送者是玩家和 伙伴记录GUID
		if (rSender.IsHero())
		{
			Obj_Hero& rSendHero =dynamic_cast<Obj_Hero&>(rSender);
			tmpImpStruct.m_SenderGuid =rSendHero.GetUID();
		}
	
		tmpImpStruct.m_nSceneClassId =rScene.GetSceneClassID();//发送的场景ID
		tmpImpStruct.m_nSceneInstanceId =rScene.GetSceneInstID();//发送的场景实例ID
		tmpImpStruct.m_nSenderObjId =rSender.GetID();//发送者objId
		tmpImpStruct.m_nDelayTime =rLine.GetDelayTime();//延迟生效时间
		tmpImpStruct.m_pImpactDataInfo =pLine;//配表信息
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