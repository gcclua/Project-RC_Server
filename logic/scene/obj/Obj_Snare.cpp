#include "Obj_Snare.h"
#include "Scene/Scene/Scene.h"
POOLDEF_IMPL(Obj_Snare);

Obj_Snare::Obj_Snare(void)
{
	m_snareId =invalid_id;
	m_OwnerId =invalid_id;
	m_OwnerGuid =invalid_guid64;
	m_bIsOwnerCanSee =false; //是否主人可见
	m_bIsActivateCanSee =false;//是否生效后可见
	m_bDelOwnerLevelScene =false;//主人不在场景时是否删除
	m_nLifeTime =0;//存活时间
	m_nValidDelayTime =0;//延迟生效时间
	m_ActivateRadius =0;//陷阱触发半径
	m_nNeedTargetType =0;//扫描目标类型(针对主人来说)
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
		if (nLifeTime -m_nValidDelayTime <=0)//未激活
		{
			m_nCurState =Obj_Snare::STATE_NOACTIVATE;
			return ;
		}
		if (nLifeTime-m_nLifeTime >=0) //生存期结束 删除
		{
			DelFromScene();
			return;
		}
		Obj_CharacterPtr OwnerPtr;//！！！注意使用之前记得判空 
		if (m_OwnerId !=invalid_id)//有主人的情况下
		{

			OwnerPtr =rScene.GetCharacterByID(m_OwnerId);
		}
		if (m_nCurState ==Obj_Snare::STATE_NOACTIVATE) //待激活状态
		{
			if (m_nActivateModel ==Obj_Snare::ACTIVATE_SCAN) //需要扫描到目标
			{
				//扫描周围的Obj
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
			else if (m_nActivateModel ==Obj_Snare::ACTIVATE_TIME)//时间到了就激活
			{
				m_nCurState =Obj_Snare::STATE_ACTIVATE;
			}
			//记下生效的时间
			if (m_nCurState ==Obj_Snare::STATE_ACTIVATE)
			{
				m_nActiveTime = static_cast<tuint32>(Clock::getCurrentSystemTime());
			}
		}
		if (m_nCurState ==Obj_Snare::STATE_ACTIVATE) //激活状态
		{
			if (m_OwnerId !=invalid_id)//有主人的情况下
			{
				//有主人且主人不在的时候需要删除 则检测主人是否还在
				if (m_bDelOwnerLevelScene)
				{
					if (OwnerPtr ==null_ptr)
					{
						DelFromScene();
						return;
					}
				}
				//定时扫描向周围派发BUFF
				BroadcastBuff(OwnerPtr);
			}
			else //无主人的情况
			{
				//定时扫描向周围派发BUFF
				BroadcastBuff(OwnerPtr);
			}
		}
	__LEAVE_PROTECT
}
bool  Obj_Snare::IsWantedTarget(Obj_Character& rTarget,Obj_CharacterPtr OwnerPtr)
{
	__ENTER_FUNCTION
		//无目标要求
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
		//还未到BUFF 生效的时间
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
					m_ImpactInfo[nBuffIndex].m_nMaxValidNum!=-1) //达到目标上限了 -1表示无目标上限
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
					else //无主的就自己给自己加
					{
						objCharCont[i].ReceiveImpact(m_ImpactInfo[nBuffIndex].m_nImpactId,-1,objCharCont[i]);
					}
				}
			}
			if (isEffect || m_ImpactInfo[nBuffIndex].m_bIsEffectByHit ==false)
			{
				m_ImpactInfo[nBuffIndex].m_nLastScanTime = static_cast<tuint32>(Clock::getCurrentSystemTime());;
				m_ImpactInfo[nBuffIndex].m_nEffectTimes++;
				//该BUFF 是否已经不需要了
				if (m_ImpactInfo[nBuffIndex].m_nScanIntervalTime ==-1) //扫描间隔为-1 表示生效一次就不需要了
				{
					m_ImpactInfo[nBuffIndex].CleanUp();
				}
				//生效次数已经达上限了
				else if (m_ImpactInfo[nBuffIndex].m_nMaxEffectTimes !=-1 && //-1表示无上限限制
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