#include "Obj_Character.h"
#include "Scene/Impact/ImpactBaseLogic.h"
#include "Table/Table_Impact.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_SkillBase.h"
#include "../scene/Scene.h"
#include "Config.h"

void Obj_Character::OnReceiveDamage(DamagesInof_T & rDamage)
{
	__ENTER_FUNCTION
		if (false ==IsSceneValid())
		{
			return;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr SenderPtr =rScene.GetCharacterByID(rDamage.GetSenderID());
		if (!SenderPtr)
		{
			return;
		}
		

		//�˺���Ѫ����
		OnTypeDamage(rDamage);
		//�ܻ�״̬���� ��Ѫ�˲���Ч �Ѿ������� �Ͳ����ܻ�״̬������ ֱ��������
		if (IsDie() ==false && rDamage.IsHit() && rDamage.GetTotalDamage() >0)
		{
			{
				if ( rDamage.GetClientShowTimes() <= 1 )
				{
					BroadCastAnimState((int)ANIMATIONSTATE_T::STATE_HIT);
				}
				else
				{
					BroadCastAnimState((int)ANIMATIONSTATE_T::STATE_HIT,
						-1,
						-1,
						-1,
						-1,
						rDamage.GetClientShowTimes(),
						rDamage.GetClientShowInterval() );
				}
			}
		}
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				if (_ImpactLogicPtr->IsFadeoutWhenReceiveDamage() ||
					_ImpactLogicPtr->IsFadeoutWhenReceiveAttack())
				{
					_ImpactLogicPtr->OnFadeOut(*this);//���˺����߹������Խ����BUFF(��鷢������Ч) 
				}
				_ImpactLogicPtr->OnReceiveDamage(*this,rDamage);//�ܵ��˺�ʱ���Ĵ���
			}
		}
		//�����ܵ������Ĵ���
		if (IsUsingSkill())
		{
			if (m_CurSkillLogicPtr)
			{
				m_CurSkillLogicPtr->OnBeAttacked(*this);
			}
		}
		//��޴��� ���ӵĳ��ֵ=(�Թ�����˺�*ְҵ���ϵ��)+���ܹ��г��
		if (CanAcceptThreat())
		{
			//ְҵ���ϵ��
			float fProfessionThreatRefix =1.0f;
			//���ܳ������ֵ
			int nSkillThreatRefix =0;
			if (rDamage.GetSkillID() !=invalid_id)
			{
				Table_SkillEx const* pSkillEx =GetTable_SkillExByID(rDamage.GetSkillID());
				if (pSkillEx !=null_ptr)
				{
					nSkillThreatRefix =pSkillEx->GetRefixThreat();
				}
			}
			int nIncThreatNum =(int)(rDamage.GetNotypeDamage()*fProfessionThreatRefix+nSkillThreatRefix);
			OnThreat(*SenderPtr,nIncThreatNum);
		}
	__LEAVE_FUNCTION
}

//�����˺�����
void Obj_Character::OnTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		RefixTypeDamage(rDamage);//�˺�����
		IgnoreTypeDamage(rDamage);//�˺�����
		AbsorbAndReflexTypeDamage(rDamage);//�˺����պͷ���
		//ת�����������˺�
		rDamage.TotalDamageToNotypeDamage();
		//�������˺�����
		OnNoTypeDamage(rDamage);
	__LEAVE_FUNCTION
}
//�����������˺���  ���ܳ��������˺����� ���յĵ�Ѫ
void Obj_Character::OnNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		//�޸�Ѫ���ı�
		if (false == IsSceneValid())
		{
			return;
		}
		Scene& rScene = GetScene();
		Obj_CharacterPtr senderPtr = rScene.GetCharacterByID(rDamage.GetSenderID());
		if (!senderPtr)
		{
			return;
		}
		int nAddAnimState =-1;//���ӵ�״̬
		
		RefixNoTypeDamage(rDamage); //�˺�����
		IgnoreNoTypeDamage(rDamage);//�˺�����
		AbsorbAndReflexNoTypeDamage(rDamage);//�˺����պͷ���
		int  nIncHp=0-rDamage.GetNotypeDamage()-rDamage.GetDecHp();
		//����ߵ� ��Ѫ
		int nOldHp =GetCurHp();
		//IncreaseHp(nIncHp,*SenderPtr);
		//mwh-ע��IncreaseHp���ص��µ�Ѫ������Ϊ����BOSS�ģ�Ҫ�����⴦��
		int nNewHp = IncreaseHp(nIncHp,*senderPtr);//GetCurHp();
		
	__LEAVE_FUNCTION
}

//�����˺�����
void Obj_Character::RefixTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF�˺�����
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->OnTypeDamage(*this,RefixDamageInfo,rDamage);
			}
		}
		int nNewPhyDamage =_MAX(rDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS)+RefixDamageInfo.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS),0);
		rDamage.SetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS,nNewPhyDamage);
	__LEAVE_FUNCTION
}
//�������˺�����
void Obj_Character::RefixNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		float fMultiNoTypeDecPer =1.0f;//buff�۳��˺�����İٷֱ�
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF�˺�����
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->OnNoTypeDamage(*this,RefixDamageInfo,rDamage);
				if (_ImpactLogicPtr->IsDecNoTypedDamagebyMulti())
				{
					float fTmpPer =_ImpactLogicPtr->GetDecNoTypedDamagebyMulti();
					if (fTmpPer>0)
					{
						fMultiNoTypeDecPer=fMultiNoTypeDecPer*(1-fTmpPer);
					}
				}
			}
		}

		fMultiNoTypeDecPer =_MIN(fMultiNoTypeDecPer,1);
		int nRefixNoTypeDamge =rDamage.GetNotypeDamage()+RefixDamageInfo.GetNotypeDamage()-(int)(rDamage.GetNotypeDamage()*(1-fMultiNoTypeDecPer));
		int nNewNoTypeDamage =_MAX(nRefixNoTypeDamge,0);
		rDamage.SetNotypeDamage(nNewNoTypeDamage);
	__LEAVE_FUNCTION
}
// ���������˺���ȫ���˺�
void Obj_Character::RefixSendAllDamage(Obj_Character& rTarget, DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION;
	DamagesInof_T RefixDamageInfo;
	ImpactPtrList::iterator it;
	// ����
	for ( it = m_buffList.begin(); it != m_buffList.end(); it++ )
	{
		ImpactBaseLogicPtr _ImpactLogicPtr =*it;
		// ��Ч
		if ( _ImpactLogicPtr && _ImpactLogicPtr->IsActive() && _ImpactLogicPtr->IsEffect() )
		{
			_ImpactLogicPtr->RefixSendAllDamage( *this, rTarget, RefixDamageInfo, rDamage );
		}
	}
	int nNewPhyDamage = _MAX( rDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS) + RefixDamageInfo.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS), 0 );
	int nNoTypeDamage = _MAX( rDamage.GetNotypeDamage() + RefixDamageInfo.GetNotypeDamage(), 0 );
	rDamage.SetTypeDamageByType( DamagesInof_T::DAMAGE_PHYSICS, nNewPhyDamage );
	rDamage.SetNotypeDamage( nNoTypeDamage );
	__LEAVE_FUNCTION;
}
//�����˺�����
void Obj_Character::IgnoreTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		ImpactPtrList::iterator it;
		//BUFF�˺�����
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->IgnoreTypedDamage(*this,rDamage);
			}
		}
	__LEAVE_FUNCTION
}
//�������˺�����
void Obj_Character::IgnoreNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		ImpactPtrList::iterator it;
		//BUFF�˺�����
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				
				_ImpactLogicPtr->IgnoreNoTypeDamage(*this,rDamage);
			}
		}
	__LEAVE_FUNCTION
}
//�����˺����պͷ���
void Obj_Character::AbsorbAndReflexTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF�˺����պͷ���
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				
				_ImpactLogicPtr->AbsorbAndReflexTypedDamage(*this,RefixDamageInfo,rDamage);
			}
		}
		int nNewPhyDamage =_MAX(rDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS)-RefixDamageInfo.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS),0);
		rDamage.SetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS,nNewPhyDamage);
	__LEAVE_FUNCTION
}
//�������˺����պͷ���
void Obj_Character::AbsorbAndReflexNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF�˺����պͷ���
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->AbsorbAndReflexNoTypeDamage(*this,RefixDamageInfo,rDamage);
			}
		}
		int nNewNoTypeDamage =_MAX(rDamage.GetNotypeDamage()-RefixDamageInfo.GetNotypeDamage(),0);
		rDamage.SetNotypeDamage(nNewNoTypeDamage);
	__LEAVE_FUNCTION
}

void Obj_Character::SetDie(bool bDie)
{	
// 	if (bDie == true)
// 	{
// 		SetCurHp(0);
// 	}	
	m_bDie = bDie;	
	m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::DIEFLAG,true);	//���±��

}
bool Obj_Character::IsAlive(void) const
{
	if (m_bDie)
	{
		return false;
	}
	return true;
}
bool Obj_Character::IsDie()
{
// 	if (m_bDie && GetCurHp() > 0)
// 	{
// 		SetCurHp(0);
// 	}
	return m_bDie;
}

void Obj_Character::OnDie(Obj_Character& rKiller)
{
	__ENTER_FUNCTION
	//�ر�Ŀǰһ�в���
	if (IsUsingSkill()) 
	{
		AssertEx(m_CurSkillLogicPtr, "");
		m_CurSkillLogicPtr->BreakSkill(*this);
	}
	StopMove(true,true);
	
	//����obj����״̬
	SetDie(true);
	//������ BUFF һ�δ������
	ImpactPtrList::iterator it;
	for (it=m_buffList.begin();it!=m_buffList.end();it++)
	{
		//��Ч
		ImpactBaseLogicPtr _ImpactLogicPtr =*it;
		if (_ImpactLogicPtr && _ImpactLogicPtr->IsActive() && _ImpactLogicPtr->IsEffect())
		{
			_ImpactLogicPtr->OnDie(*this);
		}
	}
	__LEAVE_FUNCTION
}
bool Obj_Character::OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		//�����˺� ���������������в���б�
		OnThreat(rTarget,1);//��һ���� ǿ���ù���Ŀ������Լ��ĳ���б� 
		// �������˺�Ҫ�������Ч����һЩ����
		RefixSendAllDamage( rTarget, rDamage );

		rTarget.OnReceiveDamage(rDamage);
		//�����˺����Խ����BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				if (_ImpactLogicPtr->IsFadeoutWhenSendDamage() ||
					_ImpactLogicPtr->IsFadeoutWhenSendAttack())
				{
					_ImpactLogicPtr->OnFadeOut(*this);
				}
				else
				{
					_ImpactLogicPtr->OnSendDamgeFinish( *this, rTarget, rDamage );
				}
			}
		}
		ResetEscape();
		return true;
	__LEAVE_FUNCTION
		return false;

}

void Obj_Character::Tick_Damage(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (IsInCombat())
	{
		if (m_EscapeCountDown > 0)
		{
			m_EscapeCountDown -= rTimeInfo.m_uTimeElapse;
		}
	}
	__LEAVE_FUNCTION
}

bool Obj_Character::IsInEscape()
{
	__ENTER_FUNCTION
	if (IsInCombat())
	{
		return m_EscapeCountDown<=0;
	}
	return false;
	__LEAVE_FUNCTION
	return false;
}

void Obj_Character::ResetEscape()
{
	__ENTER_FUNCTION
	m_EscapeCountDown = _GameConfig().m_EscapeCountdown;
	__LEAVE_FUNCTION
}