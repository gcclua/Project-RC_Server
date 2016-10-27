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
		//死亡需要消散的BUFF
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::ONDIE)!=0)
		{
			if (false ==rSelf.IsAlive() || false ==rSelf.GetActive())
 			{
 				//!!!消散 处理
				OnFadeOut(rSelf);
				return true;
 			}
		}
		//发送者离开需要消散的BUFF
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::SENDLEAVE)!=0)
		{
				//!!!消散 处理
			OnFadeOut(rSelf);
			return true;
		}
		//离开场景 需要消散的BUFF
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::LEAVESCENE)!=0)
		{
			if (rSelf.IsSceneValid())
			{
				if (rSelf.GetScene().GetSceneClassID() !=m_ImpactStruct.m_nSceneClassId ||
					rSelf.GetScene().GetSceneInstID() !=m_ImpactStruct.m_nSceneInstanceId )
				{
					//!!!消散 处理
					OnFadeOut(rSelf);
					return true;
				}
			}
		}
		if (m_ImpactStruct.m_nDelayTime >0)//延迟生效
		{
			m_ImpactStruct.m_nDelayTime -=rTimeInfo.m_uTimeElapse;
			return true;
		}
		if (IsContinue() && IsEffect())
		{
			//定时触发
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
						if (i >10) //设置一个循环上限
						{
							m_ImpactStruct.m_nIntervalElapsed =0;
							break;
						}
						if (m_ImpactStruct.m_nIntervalElapsed <m_ImpactStruct.m_nIntervalTime)
						{
							break;
						}
						//间隔触发
						m_ImpactStruct.m_nIntervalElapsed=m_ImpactStruct.m_nIntervalElapsed-m_ImpactStruct.m_nIntervalTime;
						OnIntervalOver(rSelf);
					}
				}
			}
			//时间控制
			if (m_nLifeType == TIMETYPE)
			{
				//永久性BUFF 就不走下面逻辑了 
				if (rImpactData.GetIsForever() !=1)
				{
					//BUFF流逝的时间
					m_nContinueElapsedTime +=rTimeInfo.m_uTimeElapse;
					int nElapseTime =(int)(Clock::getCurrentSystemTime()-m_ImpactStruct.m_nEffectTime);
					if (m_nContinueElapsedTime >=(int)(m_ImpactStruct.m_fContinuTime*1000) || //毫秒级检测(只支持在线情况)
						nElapseTime >=(m_ImpactStruct.m_fContinuTime+1)|| //校验是否超过持续时间了(包含离线时间 做1s的容错 没下线的情况下以在线时间为准 GetANSITime 貌似是向上取整 )
						nElapseTime<0  //超上限了
						)
					{
						//!!!消散 处理
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
				//先置为生效 状态
				m_bIsEffect =true;
				m_ImpactStruct.m_nEffectTime = Clock::getCurrentSystemTime();//记录下生效的时间
				StartEffect(rSelf);
				//定时触发 生效的时候 做一次触发
				if (IsContinue() && IsEffect() && IsIntervaled()) 
				{
					//间隔触发
					m_ImpactStruct.m_nIntervalElapsed =0;
					OnIntervalOver(rSelf);
				}
			}
			else
			{
				//生效失败 
				m_bIsActive =false; 
				m_bIsEffect =false;
				return false;
			}
		}
		//不是持续效果 生效完后消散 保证BUFF 生效完后 会消散
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

//离开场景前的处理
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
		//离开场景需要 消散
		if (rImpactData.GetFadeOutRule()!=-1 &&
			(rImpactData.GetFadeOutRule() & BUFFFADEOUTRULE::LEAVESCENE)!=0)
		{
			//!!!消散 处理
			OnFadeOut(rSelf);
		}
	__LEAVE_FUNCTION
}
//对命中率的修正
bool ImpactBaseLogic::IsRefixHitPer(Obj_Character& rSelf,float& fRefixHitPer)
{
	fRefixHitPer =0.0f;
	return false;
}
//对暴击率的修正
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
		//如果有需要在BUFF激活时播放特效 播放特效
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
//buff开始生效 前的处理
bool ImpactBaseLogic::BeforeStartEffec(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		// returb false 表示不生效
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return false;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		
		ImpactPtrList& _buffList =rSelf.GetBuffList();
		ImpactPtrList::iterator it;
		//互斥 叠加处理
		for (it=_buffList.begin();it!=_buffList.end();it++)
		{
			//有效
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsEffect())
			{
				//如果身上有这个BUFF 且BUFF可叠加则不加新的做叠加处理
				if (_ImpactLogicPtr->GetImpatInfo().m_nImpactId ==rImpactData.GetImpactID()
					&& rImpactData.GetMaxOverlayCount() !=-1)
				{
					//叠加次数+1
					_ImpactLogicPtr->OnOverlay(rSelf);
					return false; //该BUFF 不生效
				}
				//互斥处理
				if (_ImpactLogicPtr->GetImpatInfo().m_pImpactDataInfo !=null_ptr)
				{
					Table_Impact const& rTmpImpactData =*(_ImpactLogicPtr->GetImpatInfo().m_pImpactDataInfo);
					//同一互斥集合
					if (rTmpImpactData.GetMutexcollectionId()!=-1)
					{
						if (rTmpImpactData.GetMutexcollectionId() ==rImpactData.GetMutexcollectionId())
						{
							//互斥优先级高于 已有的 则消散掉已有的
							if (rImpactData.GetMutexpriority() >=rTmpImpactData.GetMutexpriority())
							{
								_ImpactLogicPtr->OnFadeOut(rSelf);
								return true;
							}
							//已经有了 更高级别的 则加不上
							else
							{
								return false; //该BUFF 不生效
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
		//如果有需要在BUFF生效时播放特效 播放特效
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
		//如果是客户端关心的 则通知下客户端更新(禁止移动和隐身的BUFF 必须同步给客户端)
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
		//已经达到最大叠加层数 不再叠加
		if (rImpactData.GetMaxOverlayCount()<=m_ImpactStruct.m_nImpactWrapCnt)
		{
			return;
		}
		m_ImpactStruct.m_nImpactWrapCnt++;//叠加层数+1
	__LEAVE_FUNCTION
}
//任何效果逻辑自己不能把自己当成子效果派发出去
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
			m_ImpactStruct.m_nImpactWrapCnt--; //叠加层数-1
		}
		ImpactStruct tmpImpactStruct =m_ImpactStruct;//保存一份数据
		//如果是客户端关心的 则通知下客户端更新(禁止移动和隐身的BUFF 必须同步给客户端)
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
		//清除信息
		m_bIsActive =false;
		m_bIsEffect =false;
		m_ImpactStruct.CleanUp();
		//如果有特效 且特效需要在 BUFF消散时移除则 移除特效
		if (rImpactData.GetEffectId() !=invalid_id && rImpactData.GetIsRemoveEffectFadeOut() ==1)
		{
			Remove_EffectMsgPtr MsgPtr = POOLDEF_NEW(Remove_EffectMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_nObjId = rSelf.GetID();
			MsgPtr->m_nEffectId = rImpactData.GetEffectId();
			rScene.BroadCast_InSight_Include(MsgPtr,rSelf.GetID());
			
		}
		//!!!!放在最后处理
		//还剩余叠加层数 在消散后 重新激活生效一次
		if (tmpImpactStruct.m_nImpactWrapCnt>0)
		{
			tmpImpactStruct.m_nEffectTime = Clock::getCurrentSystemTime();//记录下生效的时间
			tmpImpactStruct.m_nIntervalElapsed =0;
			//重置数据
			InitImpactDataInfo(tmpImpactStruct);
			//重新激活生效一次
			OnActive(rSelf);
			m_bIsEffect =true;
			m_nContinueElapsedTime =0;
			StartEffect(rSelf);
			return;
		}
	__LEAVE_FUNCTION
}
//统一使用该接口获取BUFF发送者
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
		
		//不是同一个场景 发送者无效
		if (rScene.GetSceneClassID() ==m_ImpactStruct.m_nSceneClassId &&
			rScene.GetSceneInstID() ==m_ImpactStruct.m_nSceneInstanceId )
		{
			//根据objID获取
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
	//检测是否已经生效了 生效了 就直接置为生效
	if (m_ImpactStruct.m_nEffectTime>0)
	{
		m_bIsEffect =true;
	}
	m_nLifeType = pLine->GetLifeType();
	
	return true;
	__LEAVE_FUNCTION
		return false;
}
