#include "ImpactLogic_003.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"

POOLDEF_IMPL(ImpactLogic_003);

void ImpactLogic_003::InitImpactDataInfo(ImpactStruct& rImpactStruct)
{
	__ENTER_FUNCTION
		//!!!先调用基类的 初始化
		ImpactBaseLogic::InitImpactDataInfo(rImpactStruct);
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rLine =*(m_ImpactStruct.m_pImpactDataInfo);
		m_ImpactStruct.m_fContinuTime =rLine.GetParamValuebyIndex(CONTIUNTIME)/1000.0f;
		m_ImpactStruct.m_nIntervalTime =rLine.GetParamValuebyIndex(INTERVALTIME);
	__LEAVE_FUNCTION
}
void ImpactLogic_003::OnIntervalOver(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		Obj_CharacterPtr SendPtr =GetImpactSender(rSelf);//统一使用此接口来获取BUFF发送者的信息
		if (!SendPtr)
		{
			return;
		}
		ScenePos selfPos =rSelf.GetScenePos();
		int nImpactId =rImpactData.GetParamValuebyIndex(IMPACT_ID);
		int	 nMaxNum=rImpactData.GetParamValuebyIndex(MAXTARGETNUM);
		int nScanType =rImpactData.GetParamValuebyIndex(SCANTYPE);
		//任何效果逻辑自己不能把自己当成子效果派发出去
		if (nImpactId ==invalid_id || CheckSubImpactIsMyself(nImpactId))
		{
			return;
		}
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
		default:
			break;
		}
		int nSelNum =0;
		//该3号逻辑的BUFF发送者定时向该BUFF的拥有者周围发送子BUFF
		for (int i = 0; i < objCharList.Size(); i++)
		{
			if (nSelNum >=nMaxNum)
			{
				break;
			}
			if (false ==IsWantedUnit(rImpactData,*SendPtr,objCharList[i]))//不是需要的目标
			{
				continue;
			}
			SendPtr->SendImpactToUnit(objCharList[i],nImpactId,m_ImpactStruct.m_nSkillId);
			nSelNum++;
		}
	__LEAVE_FUNCTION
}
bool ImpactLogic_003::IsWantedUnit(Table_Impact const& rImpactData,Obj_Character& rSelf,Obj_Character& rUnit) 
{
	__ENTER_FUNCTION
		//目标类型检测
		int nTargetType =rImpactData.GetParamValuebyIndex(TARGETTYPE);
		bool bRet =rSelf.IsWantedTypeUnit(nTargetType,rUnit);
		return bRet;
	__LEAVE_FUNCTION
		return false;
}