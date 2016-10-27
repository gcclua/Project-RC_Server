#include "Obj_Character.h"
#include "Scene/Scene/Scene.h"
bool Obj_Character::IsHit(Obj_Character& rDefenser)
{
	__ENTER_FUNCTION
		//buff�������ʵ�����
		float fBuffRefix =0.0f;
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				float fRefix =0.0f;
				//�ҵ��� �����BUFF��ɢ��
				if (ImpactLogicPtr->IsActive()
					&& ImpactLogicPtr->IsEffect() 
					&& ImpactLogicPtr->IsRefixHitPer(*this,fRefix))
				{
					fBuffRefix+=fRefix;	
				}
			}
		}

		float fMinHitRate =0.3f;
		float fMaxHitRate =1.0f;
		int nAttackerHit =GetCombatAttrByID(COMBATATTR_T::HIT);
		
		float fHitRate =nAttackerHit+fBuffRefix;
		//�����������޴���
		fHitRate =_MIN(_MAX(fHitRate,fMinHitRate),fMaxHitRate);
		if(fHitRate <=0)
		{
			return false;
		}
		if (fHitRate >=1)
		{
			return true;
		}
		float fRandom =Random::Gen();
		if (fRandom -fHitRate <0)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}

bool Obj_Character::IsCritical(Obj_Character& rDefenser)
{
	__ENTER_FUNCTION
		return false;
	__LEAVE_FUNCTION
		return false;
}

void Obj_Character::CalculateAttackDamage(Obj_Character& rDefenser,bool& bIsHit ,float fDamageRefix,int nAttackAdd,DamagesInof_T& AttackDamage)
{
	__ENTER_FUNCTION
	
		//	�����˺�=rand(g,f)*max(������������-(1-min((��������͸-������������)/10000,1))*���������������,c*������������)						
		//	cΪ�˺�����ϵ��		c=10%
		//	f�˺��������ޣ�g�˺���������		f=102%	g=98%

		// end

	
		const float fPDamageRatio = 0.1f;            //�������˺�����ϵ��
		const float fDamageRangeMin = 0.90f;         //�˺���������
		const float fDamageRangeMax = 1.05f;         //�˺���������
		const float fDefenseRefixRateParam = 0.5f;	//����ϵ��

		//����������
		int nPAttack =GetCombatAttrByID(COMBATATTR_T::ATTACK);//������
		int nMinPDamage =(int)(nPAttack*fPDamageRatio);//���������˺�

		//������������
		int nPDefense =rDefenser.GetCombatAttrByID(COMBATATTR_T::DEFENCE);//�������
		int nDefenseDuctical =0;

		nPAttack = (int)(nPAttack * fDamageRefix) + nAttackAdd; 


		int nPDamage =0;
		int nMDamage =0;


		bIsHit =false;
		if (false ==IsHit(rDefenser))
		{
			return;
		}
		bIsHit =true;
		int nMaxPDamage =(int)(nPAttack-nPDefense);//�����˺�����

		nMaxPDamage = (int)(nMaxPDamage); 

		int nDamageRangeMin =(int)(fDamageRangeMin*100);//�˺����޷Ŵ�100�� ת��int
		int nDamageRangeMax =(int)(fDamageRangeMax*100);//�˺����޷Ŵ�100�� ת��int
		float fDamageRangeRate =Random::Gen(nDamageRangeMin,nDamageRangeMax+1)/100.0f; //�˺���������ϵ��
		nPDamage =(int)(fDamageRangeRate*_MAX(nMaxPDamage,nMinPDamage));
		nPDamage =_MAX(nPDamage, 1);
		
		nPDamage =_MAX(nPDamage,0);
		AttackDamage.SetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS,nPDamage);
	__LEAVE_FUNCTION
}

bool Obj_Character::OnThreat(Obj_Character& rAttacker,int nIncThreatNum)
{
	__ENTER_FUNCTION
		//�Լ����ܽ����Լ��ĳ���б�
		if (rAttacker.GetID() == GetID())
		{
			return false;
		}
		if (CanAcceptThreat() == false)
		{
			return false;
		}
		if (false == rAttacker.GetActive() || false == rAttacker.IsAlive())
		{
			return false;
		}
		else
		{
			IncreaseUnitThreat(rAttacker, nIncThreatNum);
		}
		//�������ս��״̬ �л���ս��״̬
		if (false == m_bIsInCombat)
		{
			EnterCombat();
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

int Obj_Character::IncreaseUnitThreat(Obj_Character& rUnit, int nThreat)
{
	__ENTER_FUNCTION
		if (false ==rUnit.IsAlive() || false ==rUnit.GetActive())
		{
			return -1;
		}
		int nSlot =-1;
		EnemyUnitList_T& rEnemyList = m_enemyInfo.GetEnemyList();
		int nEnemyCount = m_enemyInfo.GetCount();
		//�Ƿ��Ѿ��ڳ���б���
		if (nEnemyCount > 0)
		{
			nSlot = rEnemyList.GetSlotInEnemyList(rUnit.GetID());
		}
		//���ٳ���б��� �Ҹ���λ
		if (nSlot ==-1)
		{
			for (int nIndex =0;nIndex<rEnemyList.GetSize();nIndex++)
			{
				if (false ==rEnemyList.IsUnitVaild(nIndex))
				{
					continue;
				}
				EnemyUnit_T& rEnemy =rEnemyList.GetUnitByIndex(nIndex);
				if (rEnemy.isValid() ==false)
				{
					nSlot =nIndex;
					break;
				}
			}
		}
		if (nSlot >=0)
		{
			if (rEnemyList.IsUnitVaild(nSlot))
			{
				EnemyUnit_T& rSelUnit =rEnemyList.GetUnitByIndex(nSlot);
				if (nThreat > 0)
				{
					if (rSelUnit.isValid())
					{
						nThreat += rSelUnit.GetThreat();
						rSelUnit.SetThreat(nThreat);
					}
					else//���ڳ���б��� �ӽ�ȥ
					{
						rEnemyList.AddEnemyToList(nSlot, rUnit.GetID(), nThreat);
					}
				}
				else
				{
					if (rSelUnit.isValid())
					{
						nThreat += rSelUnit.GetThreat();
						if (nThreat <= 0)
						{
							rSelUnit.CleanUp();
						}
						else
						{
							rSelUnit.SetThreat(nThreat);
						}
					}
				}
			}
		}
		return nSlot;
	__LEAVE_FUNCTION
			return -1;
}
int Obj_Character::GetUnitThreat(Obj_Character& rUnit)
{
	__ENTER_FUNCTION
		int nThreat =0;
		int nEnemyCount =m_enemyInfo.GetCount();
		EnemyUnitList_T& rEnemyList =m_enemyInfo.GetEnemyList();
		int nCount =0;
		for (int i=0;i<rEnemyList.GetSize();i++)
		{
			if (false ==rEnemyList.IsUnitVaild(i))
			{
				continue;
			}
			EnemyUnit_T& rEnemy=rEnemyList.GetUnitByIndex(i);
			if (rEnemy.isValid())
			{
				if (rEnemy.GetObjID() ==rUnit.GetID())
				{
					nThreat =rEnemy.GetThreat();
					break;
				}
				nCount++;
			}
			if (nCount >=nEnemyCount)
			{
				break;
			}
		}
		return nThreat;
	__LEAVE_FUNCTION
		return 0;
}
bool Obj_Character::IsInEnemyList(Obj_Character& rUnit)
{
	__ENTER_FUNCTION
	
	EnemyUnitList_T& rEnemyList =m_enemyInfo.GetEnemyList();
	for (int i=0; i<rEnemyList.GetSize(); i++)
	{
		if (false ==rEnemyList.IsUnitVaild(i))
		{
			continue;
		}
		EnemyUnit_T& rEnemy=rEnemyList.GetUnitByIndex(i);
		if (rEnemy.isValid())
		{
			if (rEnemy.GetObjID() == rUnit.GetID())
			{
				return true;
			}
		}
	}
	return false;

	__LEAVE_FUNCTION
	return false;
}
int  Obj_Character::ClearUnitThreat(Obj_Character & rUnit)
{
	__ENTER_FUNCTION
		int nThreat =0;
		int nSlot =-1;
		int nEnemyCount =m_enemyInfo.GetCount();
		EnemyUnitList_T& rEnemyList =m_enemyInfo.GetEnemyList();
		int nCount =0;
		for (int i=0;i<rEnemyList.GetSize();i++)
		{
			if (false ==rEnemyList.IsUnitVaild(i))
			{
				continue;
			}
			EnemyUnit_T& rEnemy=rEnemyList.GetUnitByIndex(i);
			if (rEnemy.isValid())
			{
				if (rEnemy.GetObjID() ==rUnit.GetID())
				{
					rEnemy.CleanUp();
					nSlot =i;
					break;
				}
				nCount++;
			}
			if (nCount >=nEnemyCount)
			{
				break;
			}
		}
		return nSlot;
	__LEAVE_FUNCTION
		return -1;
}

int  Obj_Character::ClearFullThreat(void)
{
	__ENTER_FUNCTION
		EnemyUnitList_T& rEnemyList = m_enemyInfo.GetEnemyList();
		int nEnemyCount = GetEnemyCount();
		int nCount = 0;
		for(int nIdx=0;nIdx <rEnemyList.GetSize();++nIdx)
		{
			if (false ==rEnemyList.IsUnitVaild(nIdx))
			{
				continue;
			}
			EnemyUnit_T& rUnit = rEnemyList.GetUnitByIndex(nIdx);


			if(rUnit.isValid())
			{
				rUnit.RestThreat();
				++nCount;
				if(nEnemyCount<=nCount)
				{
					break;
				}
			}
		}
		return nCount;
	__LEAVE_FUNCTION
		return 0;
}
bool Obj_Character::IsTrackPointUsed(int nPointIndex)
{
	if (nPointIndex>=0 && nPointIndex<MAXTRACEPOINTNUM)
	{
		return m_IsTrackPointUsed[nPointIndex];
	}
	return false;
}
void Obj_Character::SetTrackPointFlag(int nPointIndex,bool bFlag)
{
	if (nPointIndex>=0 && nPointIndex<MAXTRACEPOINTNUM)
	{
		m_IsTrackPointUsed[nPointIndex] =bFlag;
	}
}
void Obj_Character::CleanUpAllTrackPointFlag(void)
{
	for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
	{
		m_IsTrackPointUsed[nPointIndex] =false;
	}
}

int	 Obj_Character::GetEnemyCount(void) const
{
	__ENTER_FUNCTION
		int  nCount=m_enemyInfo.GetCount();	
		return nCount;
	__LEAVE_FUNCTION
		return 0;
}

void Obj_Character::EnterCombat(void)
{
	__ENTER_FUNCTION

		m_bIsInCombat =true;
	__LEAVE_FUNCTION
}

void Obj_Character::LeaveCombat(void)
{
	__ENTER_FUNCTION
		//��ճ���б�
		m_enemyInfo.CleanUp();
		m_bIsInCombat =false;
	__LEAVE_FUNCTION
}

void Obj_Character::OnEnterCombat(void)
{
	if (IsSceneValid())
	{
		GetScene().OnObjEnterCombat(GetID());
	}
	ResetEscape();
}

void Obj_Character::OnLeaveCombat(void)
{
	if (IsSceneValid())
	{
		GetScene().OnObjLeaveCombat(GetID());
	}
}



