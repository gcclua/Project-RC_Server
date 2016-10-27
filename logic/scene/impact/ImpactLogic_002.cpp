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
		//!!!!�ȵ��û���� StartEffect
		ImpactBaseLogic::StartEffect(rSelf);

		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		ScenePos selfPos =rSelf.GetScenePos();
		
		Obj_CharacterPtr SendPtr =GetImpactSender(rSelf);//ͳһʹ�ô˽ӿ�����ȡBUFF�����ߵ���Ϣ
		if (!SendPtr)
		{
			return;
		}
		int nImpactId =rImpactData.GetParamValuebyIndex(IMPACT_ID);
		//�κ�Ч���߼��Լ����ܰ��Լ�������Ч���ɷ���ȥ
		if (nImpactId ==invalid_id || CheckSubImpactIsMyself(nImpactId))
		{
			return;
		}
		
		//Ŀ�����ͼ��
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
				int nObjId = rSelf.GetCurSelectObjId(); // ��ɫĿǰѡ�е�id
				Obj_CharacterPtr _Ptr = rScene.GetCharacterByID(nObjId); // �õ����obj
				if ( _Ptr )
				{ // ������obj����,�����
					objCharList.Append(_Ptr.get());
				}
			}
			break;
		default:
			break;
		}
		
		int nSelNum=0;
		//ע����2���߼�BUFF�ķ����� ���BUFF��ӵ������Χ������BUFF
		for (int i = 0; i < objCharList.Size(); i++)
		{
			if (nSelNum >=nMaxTarNum)
			{
				break;
			}
			if (false ==IsWantedUnit(rImpactData,*SendPtr,objCharList[i],nTargetType))//������Ҫ��Ŀ��
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