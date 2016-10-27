#include "Scene.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Table/Table_SceneClass.h"
#include "CombatStruct/GameStruct_CombatAttr.h"
#include "Table/Table_NpcSkillStrategy.h"
#include "Table/Table_NpcOptionalSkill.h"
#include "Table/Table_SnareObjInfo.h"
#include "Table/Table_SnareObjBuffInfo.h"
#include "Service/MessageOp.h"

void Scene::NpcInit(void)
{
	__ENTER_FUNCTION



	__LEAVE_FUNCTION
}


Obj_NpcPtr Scene::CreateNpc(int nDataID, const ScenePos &rPos, bool bReliveable, int nLevel)
{
	__ENTER_FUNCTION

	Obj_NpcPtr NpcPtr = POOLDEF_NEW(Obj_Npc);
	AssertEx(NpcPtr, "");

	Table_RoleBaseAttr const* pTable =GetTable_RoleBaseAttrByID(nDataID);
	if (pTable ==null_ptr)
	{
		return Obj_NpcPtr();
	}
	Table_RoleBaseAttr const& rTable =*pTable;
	
 	NpcPtr->SetDataID(nDataID);
 	NpcPtr->SetScenePos(rPos);
 	NpcPtr->SetName(rTable.GetName());
	NpcPtr->SetRelivePos(rPos);
 	//�ȼ�
	if (nLevel == invalid_id)
	{
		nLevel = rTable.GetLevel();
	}
 	NpcPtr->SetLevel(nLevel);
 	//����
 	NpcPtr->SetForceType(rTable.GetCamp());
 	//Ѳ�߷�Χ
 	NpcPtr->SetPathRadius(rTable.GetPathRadius());
 	//���䷶Χ
 	NpcPtr->SetAlertRadius(rTable.GetAlertRadius());
 	//�Ƿ�����ƶ�
 	NpcPtr->SetRandMove((rTable.GetIsRanbdMove() ==1? true:false ));
	//����ƶ���Χ
 	NpcPtr->SetRandMoveDis(rTable.GetRandMoveDis());
	//NPC����
	NpcPtr->SetNpcType(rTable.GetNpcType());
	//ʬ��ͣ��ʱ��
	NpcPtr->SetCorpseTime(rTable.GetCorpseTime());

	//����Ƶ��
	NpcPtr->SetAttackTime(rTable.GetAttackTime());
	//��ս����Զ��
	NpcPtr->SetAttackDisType(rTable.GetAttackDisType());
	//����ʹ�ò���ID
	NpcPtr->SetSkillStrategyId(rTable.GetSkillstrategyIndex());
	//��ʼ��ս������
	NpcPtr->MarkInitalAttrCalcDirty();

	//�л�������AI
	NpcPtr->SwitchAI(Obj_Npc::AI_IDLE);
	//����npcӵ�еļ���
	Table_NpcSkillStrategy const* pNpcSkillStrategy =GetTable_NpcSkillStrategyByIndex(rTable.GetSkillstrategyIndex());
	if (pNpcSkillStrategy !=null_ptr)
	{
		Table_NpcSkillStrategy const& rNpcSkillStrategy =*pNpcSkillStrategy;
		//������Ĭ�ϼ���
		NpcPtr->SetOwnSkill(rNpcSkillStrategy.GetDefaultSkillId(),0);
		//�ٲ鿴�Ƿ������õ���������
		if (rNpcSkillStrategy.GetIsHaveOptionalSkill() ==1)
		{
			int nSkillIndex =1;//0��������Ĭ�ϼ�����
			int nCount =rNpcSkillStrategy.getSkillIdCount();
			for (int nIndex=0;nIndex<nCount;nIndex++)
			{
				int nSkillId =rNpcSkillStrategy.GetSkillIdbyIndex(nIndex);
				if (nSkillId !=invalid_id)
				{
					NpcPtr->SetOwnSkill(nSkillId,nSkillIndex);
					nSkillIndex++;
				}
			}
		}
	}
	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_Npc>(NpcPtr);
	_AddNonUserObj(objPtr);
	return NpcPtr;

	__LEAVE_FUNCTION
	return Obj_NpcPtr();
}

Obj_SnarePtr Scene::CreateSnareObj(tint32 nSnareID,tint32 OwnerId, const ScenePos &rPos)
{
	__ENTER_FUNCTION
		Obj_SnarePtr SnarePtr = POOLDEF_NEW(Obj_Snare);
	AssertEx(SnarePtr, "");
	Table_SnareObjInfo const* pLine =GetTable_SnareObjInfoByID(nSnareID);
	if (pLine ==null_ptr)
	{
		return Obj_SnarePtr();
	}
	Table_SnareObjInfo const& rLine =*pLine;

	SnarePtr->SetSnareId(nSnareID);//����ID
	SnarePtr->SetOwnerId(OwnerId);//����ID
	if (OwnerId !=invalid_id)//�����Ƿ����
	{
		Obj_CharacterPtr OwnerPtr =GetCharacterByID(OwnerId);
		AssertEx(OwnerPtr, "");
		if (OwnerPtr->IsHero())
		{
			Obj_HeroPtr _OwnUser =boost::static_pointer_cast<Obj_Hero,Obj_Character>(OwnerPtr);
			AssertEx(_OwnUser, "");
			SnarePtr->SetOwnerGuid(_OwnUser->GetUID());;
		}
	}
	SnarePtr->SetScenePos(rPos);
	SnarePtr->SetStealthLev(rLine.GetStealthLev());//������
	SnarePtr->SetIsOwnerCanSee((rLine.GetIsOwnerCanSee() ==1 ? true:false));//�Ƿ����˿ɼ�
	SnarePtr->SetIsActivateCanSee((rLine.GetIsActivateCanSee() ==1 ? true:false));//�Ƿ񼤻�ɼ�
	SnarePtr->SetIsDelOwnerLevelScene((rLine.GetIsDelOwnerLeave() ==1 ? true:false));//�Ƿ������뿪���� ɾ��
	SnarePtr->SetLifeTime(rLine.GetLifeTime());//���ʱ��
	SnarePtr->SetValidDelayTime(rLine.GetDelayTime());//�ӳ���Чʱ�� 
	SnarePtr->SetActivateRadius(rLine.GetActivateRadius());//�����뾶
	SnarePtr->SetNeedTargetType(rLine.GetTargetType());//��Ե�Ŀ������
	SnarePtr->SetCurState(Obj_Snare::STATE_NOACTIVATE);//���õ�ǰ״̬Ϊδ����
	SnarePtr->SetActivateModel(rLine.GetActivateModel());//���弤�ʽ
	//����BUFF��Ϣ
	for (tint32 nBuffIndex =0;nBuffIndex<Obj_Snare::MAXBUFFNUM;nBuffIndex++)
	{
		Obj_Snare::SnareSendImpactInfo impactInfo;
		Table_SnareObjBuffInfo const* pBuffInfo =GetTable_SnareObjBuffInfoByID(rLine.GetBUffIndexbyIndex(nBuffIndex));
		if (pBuffInfo!=null_ptr)
		{
			impactInfo.m_nImpactId =pBuffInfo->GetImpactId();
			impactInfo.m_DelayTime =pBuffInfo->GetDelayTime();
			impactInfo.m_nScanIntervalTime =pBuffInfo->GetScanIntervalTime();
			impactInfo.m_nMaxEffectTimes =pBuffInfo->GetMaxEffectTime();
			impactInfo.m_bIsEffectByHit =(pBuffInfo->GetIsEffectByHit() ==1);
			impactInfo.m_nValidRadius =pBuffInfo->GetValidRadius();
			impactInfo.m_nMaxValidNum =pBuffInfo->GetMaxValidNum();
			SnarePtr->SetImpactInfoByIndex(impactInfo,nBuffIndex);
		}
	}
	SnarePtr->SetCreateTime(static_cast<tuint32>(Clock::getCurrentSystemTime()));
	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_Snare>(SnarePtr);
	_AddNonUserObj(objPtr);
	return SnarePtr;
	__LEAVE_FUNCTION
		return Obj_SnarePtr();
}

Obj_MarchPtr Scene::CreateMarch(const March& rMarchData, const ScenePos &rPos)
{
	__ENTER_FUNCTION

	Obj_MarchPtr MarchPtr = POOLDEF_NEW(Obj_March);
	AssertEx(MarchPtr, "");

	if (rMarchData.GetMarchId() == 0)
	{
		return Obj_MarchPtr();
	}

	//����
	MarchPtr->SetScenePos(rPos);
	//���� ���������� ����ı�
	MarchPtr->SetForceType(5);
	
	MarchPtr->SetCityId(rMarchData.GetCityId());

	MarchPtr->SetPlayerId(rMarchData.GetPlayerId());
	//���� ��������
	MarchPtr->SetName(rMarchData.GetName());

	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_March>(MarchPtr);
	_AddNonUserObj(objPtr);
	return MarchPtr;

	__LEAVE_FUNCTION
	return Obj_MarchPtr();
}


Obj_MarchPtr Scene::GetMarchByID(int nObjID)
{
	__ENTER_FUNCTION

	Obj_MarchPtr PtrRet;
	ObjPtr Ptr = GetObjByID(nObjID);
	if (Ptr)
	{
		if (Ptr->IsMarch())
		{
			PtrRet = boost::static_pointer_cast<Obj_March, Obj>(Ptr);
		}
	}
	return PtrRet;

	__LEAVE_FUNCTION
	return Obj_MarchPtr();
}

Obj_NpcPtr Scene::GetNpcByID(int nObjID)
{
	__ENTER_FUNCTION

	Obj_NpcPtr PtrRet;
	ObjPtr Ptr = GetObjByID(nObjID);
	if (Ptr)
	{
		if (Ptr->IsNpc())
		{
			PtrRet = boost::static_pointer_cast<Obj_Npc, Obj>(Ptr);
		}
	}
	return PtrRet;

	__LEAVE_FUNCTION
	return Obj_NpcPtr();
}

Obj_CharacterPtr Scene::GetCharacterByID(int nObjID)
{
	__ENTER_FUNCTION

	Obj_CharacterPtr PtrRet;
	ObjPtr Ptr = GetObjByID(nObjID);
	if (Ptr)
	{
		if (Ptr->IsCharacter())
		{
			PtrRet = boost::static_pointer_cast<Obj_Character, Obj>(Ptr);
		}
	}
	return PtrRet;

	__LEAVE_FUNCTION
	return Obj_CharacterPtr();
}
ObjPtr Scene::GetObjByID(int nObjID)
{
	__ENTER_FUNCTION

	ObjPtr PtrRet;
	ObjPtrMap::iterator it = m_ObjPtrMap.find(nObjID);
	if (it != m_ObjPtrMap.end())
	{
		AssertEx((*it).second, "");
		if ((*it).second->GetActive())
		{
			PtrRet = (*it).second;
		}
	}
	if (!PtrRet)
	{
		int nCount = static_cast<int>(m_AddingCacheObjPtrVec.size());
		for (int i = 0; i < nCount; i++)
		{
			AssertEx(m_AddingCacheObjPtrVec[i], "");
			if (nObjID == m_AddingCacheObjPtrVec[i]->GetID())
			{
				if (m_AddingCacheObjPtrVec[i]->GetActive())
				{
					PtrRet = m_AddingCacheObjPtrVec[i];
				}
			}
		}
	}
	return PtrRet;

	__LEAVE_FUNCTION
	return ObjPtr();
}

Obj_SnarePtr Scene::GetSnareObjByID(tint32 nObjID)
{
	__ENTER_FUNCTION
		Obj_SnarePtr PtrRet;
	ObjPtr Ptr = GetObjByID(nObjID);
	if (Ptr)
	{
		if (Ptr->IsSnareObj())
		{
			PtrRet = boost::static_pointer_cast<Obj_Snare, Obj>(Ptr);
		}
	}
	return PtrRet;
	__LEAVE_FUNCTION
		return Obj_SnarePtr();
}

void Scene::DelNpcByID(int nObjID)
{
__ENTER_FUNCTION
	Obj_NpcPtr	npcPtr = GetNpcByID(nObjID);
	if (npcPtr)
	{
		npcPtr->DelFromScene();
	}
__LEAVE_FUNCTION
}

void Scene::_AddNonUserObj(ObjPtr Ptr)
{
	__ENTER_FUNCTION

	int nObjID = _AllocObjID();
	m_AddingCacheObjPtrVec.push_back(Ptr);

	Ptr->SetID(nObjID);
	Ptr->SetScene(this);
	Ptr->OnEnterScene();
	OnObjEnter(Ptr->GetID());

	__LEAVE_FUNCTION
}

void Scene::_AddMarchImmediate(Obj_MarchPtr marchPtr, bool bFirstEnter)
{
	__ENTER_FUNCTION

	int nObjID = _AllocObjID();
	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_March>(marchPtr);
	m_ObjPtrMap.insert(std::make_pair(nObjID, objPtr));

	marchPtr->SetID(nObjID);
	marchPtr->SetScene(this);
	if (bFirstEnter)
	{
		marchPtr->OnLogin();
	}
	marchPtr->OnEnterScene();
	OnObjEnter(marchPtr->GetID());

	__LEAVE_FUNCTION
}

void Scene::_AddNonUserObjImmediate(ObjPtr objPtr)
{
	__ENTER_FUNCTION

	m_ObjPtrMap.insert(std::make_pair(objPtr->GetID(), objPtr));

	__LEAVE_FUNCTION
}

void Scene::_DelMarchImmediate(int nObjID, bool bLastLeave)
{
	__ENTER_FUNCTION

	ObjPtrMap::iterator itRemove = m_ObjPtrMap.find(nObjID);
	AssertEx(itRemove != m_ObjPtrMap.end(), "");
	ObjPtr objPtr = itRemove->second;
	AssertEx(objPtr, "");
	AssertEx(objPtr->IsMarch(), "");

	Obj_MarchPtr userPtr = boost::static_pointer_cast<Obj_March, Obj>(objPtr);
	AssertEx(userPtr, "");

	userPtr->OnLeaveScene();
	OnObjLeave(userPtr->GetID());
	if (bLastLeave)
	{
		userPtr->OnLogout();
	}
	userPtr->SetScene(null_ptr);
	userPtr->SetID(invalid_id);

	_erase(m_ObjPtrMap, itRemove);

	__LEAVE_FUNCTION
}

ObjPtrMap::iterator Scene::_DelNonUserObjImmediate(ObjPtrMap::iterator itRemove)
{
	__ENTER_FUNCTION

	AssertEx(itRemove != m_ObjPtrMap.end(), "");
	ObjPtr objPtr = itRemove->second;
	AssertEx(objPtr, "");
	AssertEx(!objPtr->IsMarch(), "");

	objPtr->OnLeaveScene();
	OnObjLeave(objPtr->GetID());
	objPtr->SetScene(null_ptr);
	objPtr->SetID(invalid_id);

	return _erase(m_ObjPtrMap, itRemove);

	__LEAVE_FUNCTION
	return m_ObjPtrMap.end();
}

int Scene::_AllocObjID(void)
{
	int nMaxQuery = (int)m_ObjPtrMap.size() + 1;
	for (int i = 0; i < nMaxQuery; i++)
	{
		ObjPtrMap::iterator it = m_ObjPtrMap.find(m_nObjIDAlloc);
		if (it == m_ObjPtrMap.end())
		{
			return _IncObjID();
		}
		else
		{
			_IncObjID();
		}
	}

	AssertEx(false, "");
	return invalid_id;
}

int Scene::_IncObjID(void)
{
	int nObjID = m_nObjIDAlloc++;
	if (m_nObjIDAlloc > SCENEOBJIDMAX)
	{
		m_nObjIDAlloc = SCENEOBJIDMIN;
	}
	return nObjID;
}


void Scene::DelAllNonUserObj(void)
{
	__ENTER_FUNCTION

	for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); it++)
	{
		ObjPtr Ptr = it->second;
		AssertEx(Ptr, "");
		Ptr->DelFromScene();
	}

	__LEAVE_FUNCTION
}
