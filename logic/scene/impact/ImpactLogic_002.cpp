#include "ImpactLogic_002.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"
#include "skill/GameStruct_Skill.h"

POOLDEF_IMPL(ImpactLogic_002);
void ImpactLogic_002::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		//!!!!先调用基类的 StartEffect
		ImpactBaseLogic::StartEffect(rSelf);

		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		ScenePos selfPos =rSelf.GetScenePos();
		
		Obj_CharacterPtr SendPtr =GetImpactSender(rSelf);//统一使用此接口来获取BUFF发送者的信息
		if (!SendPtr)
		{
			return;
		}
		int nImpactId =rImpactData.GetParamValuebyIndex(IMPACT_ID);
		//任何效果逻辑自己不能把自己当成子效果派发出去
		if (nImpactId ==invalid_id || CheckSubImpactIsMyself(nImpactId))
		{
			return;
		}
		
		//目标类型检测
		int nTargetType =rImpactData.GetParamValuebyIndex(TARGETTYPE);
		int nScanType =rImpactData.GetParamValuebyIndex(SCANTYPE);
		int nMaxTarNum =rImpactData.GetParamValuebyIndex(MAXTARGETNUM);
		CharacterRefCont objCharList;
		switch (nScanType)
		{
		case SCAN_CIRCLE:
			{
				float fScanRadius=(float)rImpactData.GetParamValuebyIndex(SCANPARAME_01);
				rScene.Scan_Character_Circle(objCharList,selfPos,fScanRadius);
			}
			break;
		case SCAN_SECTOR:
			{
				float fScanRadius =(float)rImpactData.GetParamValuebyIndex(SCANPARAME_01);
				float fDirection =rSelf.GetFaceDir();
				int nAngle =rImpactData.GetParamValuebyIndex(SCANPARAME_02);
				float fRadian =nAngle*_PI/180;
				rScene.Scan_Character_Sector(objCharList,selfPos,fScanRadius,fDirection,fRadian);
			}
			break;
		case SCAN_RAY:
			{
				float fDirection =rSelf.GetFaceDir();
				float fLength =(float)rImpactData.GetParamValuebyIndex(SCANPARAME_01);
				float fScope=(float)rImpactData.GetParamValuebyIndex(SCANPARAME_02)/2.0f;
				rScene.Scan_Character_Ray(objCharList,selfPos,fDirection,fLength,fScope);
			}
			break;
		case SCAN_RING:
			{
				float fMinRadius =(float)rImpactData.GetParamValuebyIndex(SCANPARAME_01);
				float fMaxRadius=(float)rImpactData.GetParamValuebyIndex(SCANPARAME_02);
				rScene.Scan_Character_Ring(objCharList,selfPos,fMinRadius,fMaxRadius);
			}
			break;
		case SCAN_TARGETOBJ:
			{
				int nObjId = rSelf.GetCurSelectObjId(); // 角色目前选中的id
				Obj_CharacterPtr _Ptr = rScene.GetCharacterByID(nObjId); // 得到这个obj
				if ( _Ptr )
				{ // 如果这个obj存在,则加入
					objCharList.Append(_Ptr.get());
				}
			}
			break;
		default:
			break;
		}
		
		int nSelNum=0;
		//注：该2号逻辑BUFF的发送者 向该BUFF的拥有者周围发送子BUFF
		for (int i = 0; i < objCharList.Size(); i++)
		{
			if (nSelNum >=nMaxTarNum)
			{
				break;
			}
			if (false ==IsWantedUnit(rImpactData,*SendPtr,objCharList[i],nTargetType))//不是需要的目标
			{
				continue;
			}
			SendPtr->SendImpactToUnit(objCharList[i],nImpactId,m_ImpactStruct.m_nSkillId);
			nSelNum++;
		}
	__LEAVE_FUNCTION
}

bool ImpactLogic_002::IsWantedUnit(Table_Impact const& rImpactData,Obj_Character& rSelf,Obj_Character& rUnit,int nTargetType)
{
	__ENTER_FUNCTION
		bool bRet =rSelf.IsWantedTypeUnit(nTargetType,rUnit);
		return bRet;
	__LEAVE_FUNCTION
		return false;
}