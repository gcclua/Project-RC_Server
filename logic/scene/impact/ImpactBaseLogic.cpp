#include "ImpactBaseLogic.h"
#include "Scene/Obj/Obj_Character.h"
#include "Table/Table_Impact.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"

POOLDEF_IMPL(ImpactBaseLogic);

ImpactBaseLogic::ImpactBaseLogic()
{
	m_bIsActive =false;
	m_bIsEffect =false;
	m_ImpactStruct.CleanUp();
	m_nContinueElapsedTime =0;
	m_nLifeType = TIMETYPE;
}

bool ImpactBaseLogic::Tick(TimeInfo const&rTimeInfo,Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (false ==IsActive())
		{
			return false;
		}
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return false;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		//������Ҫ��ɢ��BUFF
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::ONDIE)!=0)
		{
			if (false ==rSelf.IsAlive() || false ==rSelf.GetActive())
 			{
 				//!!!��ɢ ����
				OnFadeOut(rSelf);
				return true;
 			}
		}
		//�������뿪��Ҫ��ɢ��BUFF
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::SENDLEAVE)!=0)
		{
				//!!!��ɢ ����
			OnFadeOut(rSelf);
			return true;
		}
		//�뿪���� ��Ҫ��ɢ��BUFF
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::LEAVESCENE)!=0)
		{
			if (rSelf.IsSceneValid())
			{
				if (rSelf.GetScene().GetSceneClassID() !=m_ImpactStruct.m_nSceneClassId ||
					rSelf.GetScene().GetSceneInstID() !=m_ImpactStruct.m_nSceneInstanceId )
				{
					//!!!��ɢ ����
					OnFadeOut(rSelf);
					return true;
				}
			}
		}
		if (m_ImpactStruct.m_nDelayTime >0)//�ӳ���Ч
		{
			m_ImpactStruct.m_nDelayTime -=rTimeInfo.m_uTimeElapse;
			return true;
		}
		if (IsContinue() && IsEffect())
		{
			//��ʱ����
			if (IsIntervaled()) 
			{
				m_ImpactStruct.m_nIntervalElapsed +=rTimeInfo.m_uTimeElapse;
				if (m_ImpactStruct.m_nIntervalElapsed >=m_ImpactStruct.m_nIntervalTime)
				{
					int nNeedOnIntervalTimes =0;
					if (m_ImpactStruct.m_nIntervalTime>0)
					{
						nNeedOnIntervalTimes=m_ImpactStruct.m_nIntervalElapsed/m_ImpactStruct.m_nIntervalTime ;
						if (rImpactData.GetIsForever() !=1)
						{
							int nElapseTime =(int)(Clock::getCurrentSystemTime()-m_ImpactStruct.m_nEffectTime);
							float fRemainTime =_MAX(m_ImpactStruct.m_fContinuTime-nElapseTime,0);
							int nMaxNeedOnIntervalTimes =(int)((fRemainTime+1)*1000)/m_ImpactStruct.m_nIntervalTime;
							nNeedOnIntervalTimes =_MIN(nNeedOnIntervalTimes,nMaxNeedOnIntervalTimes);
						}
					}
					for (int i=0;i<nNeedOnIntervalTimes;i++)
					{
						if (i >10) //����һ��ѭ������
						{
							m_ImpactStruct.m_nIntervalElapsed =0;
							break;
						}
						if (m_ImpactStruct.m_nIntervalElapsed <m_ImpactStruct.m_nIntervalTime)
						{
							break;
						}
						//�������
						m_ImpactStruct.m_nIntervalElapsed=m_ImpactStruct.m_nIntervalElapsed-m_ImpactStruct.m_nIntervalTime;
						OnIntervalOver(rSelf);
					}
				}
			}
			//ʱ�����
			if (m_nLifeType == TIMETYPE)
			{
				//������BUFF �Ͳ��������߼��� 
				if (rImpactData.GetIsForever() !=1)
				{
					//BUFF���ŵ�ʱ��
					m_nContinueElapsedTime +=rTimeInfo.m_uTimeElapse;
					int nElapseTime =(int)(Clock::getCurrentSystemTime()-m_ImpactStruct.m_nEffectTime);
					if (m_nContinueElapsedTime >=(int)(m_ImpactStruct.m_fContinuTime*1000) || //���뼶���(ֻ֧���������)
						nElapseTime >=(m_ImpactStruct.m_fContinuTime+1)|| //У���Ƿ񳬹�����ʱ����(��������ʱ�� ��1s���ݴ� û���ߵ������������ʱ��Ϊ׼ GetANSITime ò��������ȡ�� )
						nElapseTime<0  //��������
						)
					{
						//!!!��ɢ ����
						OnFadeOut(rSelf);
						return true;
					}
				}
			}
		}
		if (IsEffect() ==false)
		{
			if (BeforeStartEffec(rSelf))
			{
				//����Ϊ��Ч ״̬
				m_bIsEffect =true;
				m_ImpactStruct.m_nEffectTime = Clock::getCurrentSystemTime();//��¼����Ч��ʱ��
				StartEffect(rSelf);
				//��ʱ���� ��Ч��ʱ�� ��һ�δ���
				if (IsContinue() && IsEffect() && IsIntervaled()) 
				{
					//�������
					m_ImpactStruct.m_nIntervalElapsed =0;
					OnIntervalOver(rSelf);
				}
			}
			else
			{
				//��Чʧ�� 
				m_bIsActive =false; 
				m_bIsEffect =false;
				return false;
			}
		}
		//���ǳ���Ч�� ��Ч�����ɢ ��֤BUFF ��Ч��� ����ɢ
		if (false ==IsContinue() && IsEffect())
		{
			OnFadeOut(rSelf);
			return true;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

void ImpactBaseLogic::InitImpactDataInfo(ImpactStruct& rImpactStruct)
{
	m_ImpactStruct =rImpactStruct;
	Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
	m_nLifeType = rImpactData.GetLifeType();
}

//�뿪����ǰ�Ĵ���
void ImpactBaseLogic::BeforeLeaveScene(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (IsActive() ==false)
		{
			return;
		}
		if (m_ImpactStruct.m_pImpactDataInfo==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData=*(m_ImpactStruct.m_pImpactDataInfo);
		//�뿪������Ҫ ��ɢ
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::LEAVESCENE)!=0)
		{
			//!!!��ɢ ����
			OnFadeOut(rSelf);
		}
	__LEAVE_FUNCTION
}
//�������ʵ�����
bool ImpactBaseLogic::IsRefixHitPer(Obj_Character& rSelf,float& fRefixHitPer)
{
	fRefixHitPer =0.0f;
	return false;
}
//�Ա����ʵ�����
bool ImpactBaseLogic::IsRefixCriPer(Obj_Character& rSelf,float& fRefixCriPer)
{
	fRefixCriPer =0.0f;
	return false;
}
bool ImpactBaseLogic::OnActive(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return false;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		if (false ==m_bIsActive)
		{
			m_bIsActive =true;
			m_bIsEffect =false;
		}
		//�������Ҫ��BUFF����ʱ������Ч ������Ч
		if (rSelf.IsSceneValid() ==false)
		{
			return false;
		}
		Scene& rScene =rSelf.GetScene();
		if (rImpactData.GetPlayTime() ==PLAYACTIVE)
		{
			if (rImpactData.GetEffectId() !=invalid_id)
			{
	
				Player_EffectMsgPtr MsgPtr = POOLDEF_NEW(Player_EffectMsg);
				MsgPtr->m_nObjId = rSelf.GetID();
				MsgPtr->m_nEffectId = rImpactData.GetEffectId();
				rScene.BroadCast_InSight_Include(MsgPtr,rSelf.GetID());
			}
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}
//buff��ʼ��Ч ǰ�Ĵ���
bool ImpactBaseLogic::BeforeStartEffec(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		// returb false ��ʾ����Ч
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return false;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		
		ImpactPtrList& _buffList =rSelf.GetBuffList();
		ImpactPtrList::iterator it;
		//���� ���Ӵ���
		for (it=_buffList.begin();it!=_buffList.end();it++)
		{
			//��Ч
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsEffect())
			{
				//������������BUFF ��BUFF�ɵ����򲻼��µ������Ӵ���
				if (_ImpactLogicPtr->GetImpatInfo().m_nImpactId ==rImpactData.GetImpactID()
					&& rImpactData.GetMaxOverlayCount() !=-1)
				{
					//���Ӵ���+1
					_ImpactLogicPtr->OnOverlay(rSelf);
					return false; //��BUFF ����Ч
				}
				//���⴦��
				if (_ImpactLogicPtr->GetImpatInfo().m_pImpactDataInfo !=null_ptr)
				{
					Table_Impact const& rTmpImpactData =*(_ImpactLogicPtr->GetImpatInfo().m_pImpactDataInfo);
					//ͬһ���⼯��
					if (rTmpImpactData.GetMutexcollectionId()!=-1)
					{
						if (rTmpImpactData.GetMutexcollectionId() ==rImpactData.GetMutexcollectionId())
						{
							//�������ȼ����� ���е� ����ɢ�����е�
							if (rImpactData.GetMutexpriority() >=rTmpImpactData.GetMutexpriority())
							{
								_ImpactLogicPtr->OnFadeOut(rSelf);
								return true;
							}
							//�Ѿ����� ���߼���� ��Ӳ���
							else
							{
								return false; //��BUFF ����Ч
							}
						}
					}
				}
			}
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}
void ImpactBaseLogic::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		//�������Ҫ��BUFF��Чʱ������Ч ������Ч
		if (rSelf.IsSceneValid() ==false)
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		
		if (rImpactData.GetPlayTime() ==PLAYEFFCT)
		{
			if (rImpactData.GetEffectId() !=invalid_id)
			{
				Player_EffectMsgPtr MsgPtr = POOLDEF_NEW(Player_EffectMsg);
				MsgPtr->m_nObjId = rSelf.GetID();
				MsgPtr->m_nEffectId = rImpactData.GetEffectId();
				rScene.BroadCast_InSight_Include(MsgPtr,rSelf.GetID());
			}
		}
		//����ǿͻ��˹��ĵ� ��֪ͨ�¿ͻ��˸���(��ֹ�ƶ��������BUFF ����ͬ�����ͻ���)
		if ((rImpactData.GetIsNeedNoticeClient() ==1 || IsMoveDisabled() || IsStealth()))
		{
			Update_NeedImpactInfoMsgPtr MsgPtr = POOLDEF_NEW(Update_NeedImpactInfoMsg);
			MsgPtr->m_nObjId = rSelf.GetID();
			MsgPtr->m_nImpactId.push_back(m_ImpactStruct.m_nImpactId);
			MsgPtr->m_iImpactLogicId.push_back(rImpactData.GetLogicID());
			MsgPtr->m_nIsForever.push_back(rImpactData.GetIsForever());
			int nElaspeTime =(int)(Clock::getCurrentSystemTime()-m_ImpactStruct.m_nEffectTime);
			int nRemainTime =(int)(m_ImpactStruct.m_fContinuTime -nElaspeTime);
			MsgPtr->m_nRemainTime.push_back(nRemainTime);
			MsgPtr->m_nIsAdd.push_back(1);
			
			SendMessage2User(rSelf.GetPlayerId(),MsgPtr);
			
		}
	__LEAVE_FUNCTION
}
void ImpactBaseLogic::OnOverlay(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		//�Ѿ��ﵽ�����Ӳ��� ���ٵ���
		if (rImpactData.GetMaxOverlayCount()<=m_ImpactStruct.m_nImpactWrapCnt)
		{
			return;
		}
		m_ImpactStruct.m_nImpactWrapCnt++;//���Ӳ���+1
	__LEAVE_FUNCTION
}
//�κ�Ч���߼��Լ����ܰ��Լ�������Ч���ɷ���ȥ
bool ImpactBaseLogic::CheckSubImpactIsMyself(int nSubImpact)const
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_nImpactId ==nSubImpact)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
}
void ImpactBaseLogic::OnFadeOut(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		if (rSelf.IsSceneValid() ==false)
		{
			return ;
		}
		Scene& rScene =rSelf.GetScene();

		if (m_ImpactStruct.m_nImpactWrapCnt>0)
		{
			m_ImpactStruct.m_nImpactWrapCnt--; //���Ӳ���-1
		}
		ImpactStruct tmpImpactStruct =m_ImpactStruct;//����һ������
		//����ǿͻ��˹��ĵ� ��֪ͨ�¿ͻ��˸���(��ֹ�ƶ��������BUFF ����ͬ�����ͻ���)
		if ((rImpactData.GetIsNeedNoticeClient() ==1 || IsMoveDisabled() || IsStealth()))
		{
			Update_NeedImpactInfoMsgPtr MsgPtr = POOLDEF_NEW(Update_NeedImpactInfoMsg);
			MsgPtr->m_nObjId = rSelf.GetID();
			MsgPtr->m_nImpactId.push_back(m_ImpactStruct.m_nImpactId);
			MsgPtr->m_iImpactLogicId.push_back(rImpactData.GetLogicID());
			MsgPtr->m_nIsForever.push_back(rImpactData.GetIsForever());
			int nElaspeTime =(int)(Clock::getCurrentSystemTime()-m_ImpactStruct.m_nEffectTime);
			int nRemainTime =(int)(m_ImpactStruct.m_fContinuTime -nElaspeTime);
			MsgPtr->m_nRemainTime.push_back(nRemainTime);
			MsgPtr->m_nIsAdd.push_back(0);

			SendMessage2User(rSelf.GetPlayerId(),MsgPtr);

		}
		//�����Ϣ
		m_bIsActive =false;
		m_bIsEffect =false;
		m_ImpactStruct.CleanUp();
		//�������Ч ����Ч��Ҫ�� BUFF��ɢʱ�Ƴ��� �Ƴ���Ч
		if (rImpactData.GetEffectId() !=invalid_id && rImpactData.GetIsRemoveEffectFadeOut() ==1)
		{
			Remove_EffectMsgPtr MsgPtr = POOLDEF_NEW(Remove_EffectMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_nObjId = rSelf.GetID();
			MsgPtr->m_nEffectId = rImpactData.GetEffectId();
			rScene.BroadCast_InSight_Include(MsgPtr,rSelf.GetID());
			
		}
		//!!!!���������
		//��ʣ����Ӳ��� ����ɢ�� ���¼�����Чһ��
		if (tmpImpactStruct.m_nImpactWrapCnt>0)
		{
			tmpImpactStruct.m_nEffectTime = Clock::getCurrentSystemTime();//��¼����Ч��ʱ��
			tmpImpactStruct.m_nIntervalElapsed =0;
			//��������
			InitImpactDataInfo(tmpImpactStruct);
			//���¼�����Чһ��
			OnActive(rSelf);
			m_bIsEffect =true;
			m_nContinueElapsedTime =0;
			StartEffect(rSelf);
			return;
		}
	__LEAVE_FUNCTION
}
//ͳһʹ�øýӿڻ�ȡBUFF������
Obj_CharacterPtr ImpactBaseLogic::GetImpactSender(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		
		Obj_CharacterPtr BuffSenderPtr;
		if (rSelf.IsSceneValid() ==false)
		{
			return BuffSenderPtr;
		}
		Scene& rScene =rSelf.GetScene();
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return BuffSenderPtr;
		}
		
		//����ͬһ������ ��������Ч
		if (rScene.GetSceneClassID() ==m_ImpactStruct.m_nSceneClassId &&
			rScene.GetSceneInstID() ==m_ImpactStruct.m_nSceneInstanceId )
		{
			//����objID��ȡ
			Obj_CharacterPtr TmpSenderPtr =rScene.GetCharacterByID(m_ImpactStruct.m_nSenderObjId);
			if (TmpSenderPtr)
			{
				if (TmpSenderPtr->IsNpc())
				{
					BuffSenderPtr =TmpSenderPtr;
				}
			}
		}
		
		return BuffSenderPtr;
	__LEAVE_FUNCTION
		return Obj_CharacterPtr();
}
bool ImpactBaseLogic::SerializeToDB(DBImpactStruct& rDest)
{
	__ENTER_FUNCTION
		m_ImpactStruct.SerializeToDB(rDest);
		return true;
	__LEAVE_FUNCTION
		return false;
}

bool ImpactBaseLogic::SerializeFromDB(const DBImpactStruct& rSour)
{
	__ENTER_FUNCTION
	m_ImpactStruct.SerializeFromDB(rSour);
	const Table_Impact*  pLine =GetTable_ImpactByID(m_ImpactStruct.m_nImpactId);
	if (pLine ==null_ptr)
	{
		return false;
	}
	m_ImpactStruct.m_pImpactDataInfo =pLine;
	m_bIsActive =true;
	//����Ƿ��Ѿ���Ч�� ��Ч�� ��ֱ����Ϊ��Ч
	if (m_ImpactStruct.m_nEffectTime>0)
	{
		m_bIsEffect =true;
	}
	m_nLifeType = pLine->GetLifeType();
	
	return true;
	__LEAVE_FUNCTION
		return false;
}
