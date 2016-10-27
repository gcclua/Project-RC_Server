#include "Obj_Snare.h"
#include "Scene/Scene/Scene.h"
POOLDEF_IMPL(Obj_Snare);

Obj_Snare::Obj_Snare(void)
{
	m_snareId =invalid_id;
	m_OwnerId =invalid_id;
	m_OwnerGuid =invalid_guid64;
	m_bIsOwnerCanSee =false; //�Ƿ����˿ɼ�
	m_bIsActivateCanSee =false;//�Ƿ���Ч��ɼ�
	m_bDelOwnerLevelScene =false;//���˲��ڳ���ʱ�Ƿ�ɾ��
	m_nLifeTime =0;//���ʱ��
	m_nValidDelayTime =0;//�ӳ���Чʱ��
	m_ActivateRadius =0;//���崥���뾶
	m_nNeedTargetType =0;//ɨ��Ŀ������(���������˵)
	m_nCurState =Obj_Snare::STATE_INVALID;
	m_nCreateTime =0;
	m_nActiveTime =0;
	m_nActivateModel =-1;
	for (tint32 nBuffIndex =0;nBuffIndex<Obj_Snare::MAXBUFFNUM;nBuffIndex++)
	{
		m_ImpactInfo[nBuffIndex].CleanUp();
	}
}
void Obj_Snare::SetImpactInfoByIndex(SnareSendImpactInfo const& rImpactInfo,tint32 nIndex)
{
	__ENTER_FUNCTION
		if(nIndex>=0 && nIndex<Obj_Snare::MAXBUFFNUM)
		{
			m_ImpactInfo[nIndex] =rImpactInfo;
		}
	__LEAVE_FUNCTION
}
void Obj_Snare::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT
		Obj::Tick(rTimeInfo);
		if (IsSceneValid() ==false)
		{
			return;
		}
		Scene& rScene=GetScene();
		tint32 nLifeTime =(tint32)(Clock::getCurrentSystemTime()-m_nCreateTime);
		if (nLifeTime -m_nValidDelayTime <=0)//δ����
		{
			m_nCurState =Obj_Snare::STATE_NOACTIVATE;
			return ;
		}
		if (nLifeTime-m_nLifeTime >=0) //�����ڽ��� ɾ��
		{
			DelFromScene();
			return;
		}
		Obj_CharacterPtr OwnerPtr;//������ע��ʹ��֮ǰ�ǵ��п� 
		if (m_OwnerId !=invalid_id)//�����˵������
		{

			OwnerPtr =rScene.GetCharacterByID(m_OwnerId);
		}
		if (m_nCurState ==Obj_Snare::STATE_NOACTIVATE) //������״̬
		{
			if (m_nActivateModel ==Obj_Snare::ACTIVATE_SCAN) //��Ҫɨ�赽Ŀ��
			{
				//ɨ����Χ��Obj
				CharacterRefCont objCharCont;
				rScene.Scan_Character_Circle(objCharCont, GetScenePos(), (tfloat32)m_ActivateRadius);
				for (tint32 i = 0; i < objCharCont.Size(); i++)
				{
					if (IsWantedTarget(objCharCont[i],OwnerPtr))
					{
						m_nCurState =Obj_Snare::STATE_ACTIVATE;
						break;
					}
				}
			}
			else if (m_nActivateModel ==Obj_Snare::ACTIVATE_TIME)//ʱ�䵽�˾ͼ���
			{
				m_nCurState =Obj_Snare::STATE_ACTIVATE;
			}
			//������Ч��ʱ��
			if (m_nCurState ==Obj_Snare::STATE_ACTIVATE)
			{
				m_nActiveTime = static_cast<tuint32>(Clock::getCurrentSystemTime());
			}
		}
		if (m_nCurState ==Obj_Snare::STATE_ACTIVATE) //����״̬
		{
			if (m_OwnerId !=invalid_id)//�����˵������
			{
				//�����������˲��ڵ�ʱ����Ҫɾ�� ���������Ƿ���
				if (m_bDelOwnerLevelScene)
				{
					if (OwnerPtr ==null_ptr)
					{
						DelFromScene();
						return;
					}
				}
				//��ʱɨ������Χ�ɷ�BUFF
				BroadcastBuff(OwnerPtr);
			}
			else //�����˵����
			{
				//��ʱɨ������Χ�ɷ�BUFF
				BroadcastBuff(OwnerPtr);
			}
		}
	__LEAVE_PROTECT
}
bool  Obj_Snare::IsWantedTarget(Obj_Character& rTarget,Obj_CharacterPtr OwnerPtr)
{
	__ENTER_FUNCTION
		//��Ŀ��Ҫ��
		if (m_nNeedTargetType ==-1)
		{
			return true;
		}
		if (IsSceneValid() ==false)
		{
			return false;
		}
		if (OwnerPtr !=null_ptr && OwnerPtr->IsWantedTypeUnit(m_nNeedTargetType,rTarget))
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
void Obj_Snare::BroadcastBuff(Obj_CharacterPtr OwnerPtr)
{
	if (IsSceneValid() ==false)
	{
		return ;
	}
	Scene& rScene=GetScene();
	tint32 nActiveTime=(tint32)(Clock::getCurrentSystemTime()-m_nActiveTime);
	for (tint32 nBuffIndex=0;nBuffIndex<Obj_Snare::MAXBUFFNUM;nBuffIndex++)
	{
		if (m_ImpactInfo[nBuffIndex].m_nImpactId ==invalid_id)
		{
			continue;
		}
		//��δ��BUFF ��Ч��ʱ��
		if (m_ImpactInfo[nBuffIndex].m_DelayTime >nActiveTime)
		{
			continue;
		}
		bool isEffect =false;
		tint32 nDiffInterTime = (tint32)(Clock::getCurrentSystemTime()-m_ImpactInfo[nBuffIndex].m_nLastScanTime);
		if (nDiffInterTime>=m_ImpactInfo[nBuffIndex].m_nScanIntervalTime)
		{
			CharacterRefCont objCharCont;
			rScene.Scan_Character_Circle(objCharCont, GetScenePos(), (tfloat32)m_ImpactInfo[nBuffIndex].m_nValidRadius);
			tint32 nVaildNum =0;
			for (tint32 i = 0; i < objCharCont.Size(); i++)
			{
				if (nVaildNum >=m_ImpactInfo[nBuffIndex].m_nMaxValidNum && 
					m_ImpactInfo[nBuffIndex].m_nMaxValidNum!=-1) //�ﵽĿ�������� -1��ʾ��Ŀ������
				{
					break;
				}
				if (IsWantedTarget(objCharCont[i],OwnerPtr))
				{
					isEffect =true;
					nVaildNum++;
					if (OwnerPtr !=null_ptr)
					{
						objCharCont[i].ReceiveImpact(m_ImpactInfo[nBuffIndex].m_nImpactId,-1,*OwnerPtr);
					}
					else //�����ľ��Լ����Լ���
					{
						objCharCont[i].ReceiveImpact(m_ImpactInfo[nBuffIndex].m_nImpactId,-1,objCharCont[i]);
					}
				}
			}
			if (isEffect || m_ImpactInfo[nBuffIndex].m_bIsEffectByHit ==false)
			{
				m_ImpactInfo[nBuffIndex].m_nLastScanTime = static_cast<tuint32>(Clock::getCurrentSystemTime());;
				m_ImpactInfo[nBuffIndex].m_nEffectTimes++;
				//��BUFF �Ƿ��Ѿ�����Ҫ��
				if (m_ImpactInfo[nBuffIndex].m_nScanIntervalTime ==-1) //ɨ����Ϊ-1 ��ʾ��Чһ�ξͲ���Ҫ��
				{
					m_ImpactInfo[nBuffIndex].CleanUp();
				}
				//��Ч�����Ѿ���������
				else if (m_ImpactInfo[nBuffIndex].m_nMaxEffectTimes !=-1 && //-1��ʾ����������
					m_ImpactInfo[nBuffIndex].m_nEffectTimes >=m_ImpactInfo[nBuffIndex].m_nMaxEffectTimes)
				{
					m_ImpactInfo[nBuffIndex].CleanUp();
				}
			}
		}
	}
}

bool Obj_Snare::CanBeView(Obj_March &rObj)
{
	__ENTER_FUNCTION
		if (m_bIsActivateCanSee)
		{
			if (m_nCurState == Obj_Snare::STATE_ACTIVATE)
			{
				return true;
			}
		}
		if (m_bIsOwnerCanSee)
		{
			if (rObj.GetID() == m_OwnerId)
			{
				return true;
			}
		}
		return (Obj::CanBeView(rObj));
	__LEAVE_FUNCTION
		return false;
}