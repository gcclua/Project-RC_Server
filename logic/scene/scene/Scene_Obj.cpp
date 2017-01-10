#include "Scene.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Table/Table_SceneClass.h"
#include "CombatStruct/GameStruct_CombatAttr.h"
#include "Table/Table_NpcSkillStrategy.h"
#include "Table/Table_NpcOptionalSkill.h"
#include "Table/Table_SnareObjInfo.h"
#include "Table/Table_SnareObjBuffInfo.h"
#include "Service/MessageOp.h"
#include "Table/Table_Troop.h"
#include "Table/Table_Hero.h"

void Scene::NpcInit(void)
{
	__ENTER_FUNCTION



	__LEAVE_FUNCTION
}


Obj_NpcPtr Scene::CreateNpc(int nDataID, const ScenePos &rPos, bool bReliveable,int nForce, int nLevel,Obj_NpcPtr NpcPtr)
{
	__ENTER_FUNCTION
	if (NpcPtr == null_ptr)
	{
		NpcPtr = POOLDEF_NEW(Obj_Npc);
	}
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
 	//等级
	if (nLevel == invalid_id)
	{
		nLevel = rTable.GetLevel();
	}
 	NpcPtr->SetLevel(nLevel);
 	//势力
 	NpcPtr->SetForceType(nForce);
	//尸体停留时间
	NpcPtr->SetCorpseTime(rTable.GetCorpseTime());

	//攻击频率
	NpcPtr->SetAttackTime(rTable.GetAttackTime());
	//近战还是远程
	NpcPtr->SetAttackDisType(rTable.GetAttackDisType());
	//技能使用策略ID
	NpcPtr->SetSkillStrategyId(rTable.GetSkillstrategyIndex());
	//警戒范围
	NpcPtr->SetAlertRadius(rTable.GetSelectRadius());
	// 战意恢复速度
	NpcPtr->SetXpSpeed(rTable.GetXpSpeed());
	//初始化战斗属性
	NpcPtr->MarkInitalAttrCalcDirty();

	//切换到待机AI
	NpcPtr->SwitchAI(Obj_Npc::AI_IDLE);
	//设置npc拥有的技能
	Table_NpcSkillStrategy const* pNpcSkillStrategy =GetTable_NpcSkillStrategyByIndex(rTable.GetSkillstrategyIndex());
	if (pNpcSkillStrategy !=null_ptr)
	{
		Table_NpcSkillStrategy const& rNpcSkillStrategy =*pNpcSkillStrategy;
		//先设置默认技能
		NpcPtr->SetOwnSkill(rNpcSkillStrategy.GetDefaultSkillId(),0);

		int nSkillIndex =1;//0号索引给默认技能了
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
	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_Npc>(NpcPtr);
	_AddNonMarchObj(objPtr);
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

	SnarePtr->SetSnareId(nSnareID);//陷阱ID
	SnarePtr->SetOwnerId(OwnerId);//主人ID
	if (OwnerId !=invalid_id)//主人是否玩家
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
	SnarePtr->SetStealthLev(rLine.GetStealthLev());//隐身级别
	SnarePtr->SetIsOwnerCanSee((rLine.GetIsOwnerCanSee() ==1 ? true:false));//是否主人可见
	SnarePtr->SetIsActivateCanSee((rLine.GetIsActivateCanSee() ==1 ? true:false));//是否激活可见
	SnarePtr->SetIsDelOwnerLevelScene((rLine.GetIsDelOwnerLeave() ==1 ? true:false));//是否主人离开场景 删除
	SnarePtr->SetLifeTime(rLine.GetLifeTime());//存活时间
	SnarePtr->SetValidDelayTime(rLine.GetDelayTime());//延迟生效时间 
	SnarePtr->SetActivateRadius(rLine.GetActivateRadius());//触发半径
	SnarePtr->SetNeedTargetType(rLine.GetTargetType());//针对的目标类型
	SnarePtr->SetCurState(Obj_Snare::STATE_NOACTIVATE);//设置当前状态为未激活
	SnarePtr->SetActivateModel(rLine.GetActivateModel());//陷阱激活方式
	//设置BUFF信息
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
	SnarePtr->SetCreateTime(gTimeManager.RunTime());
	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_Snare>(SnarePtr);
	_AddNonMarchObj(objPtr);
	return SnarePtr;
	__LEAVE_FUNCTION
		return Obj_SnarePtr();
}

Obj_TroopPtr  Scene::CreateTroopObj(const Troop& rTroop,const ScenePos &rPos,int nForce)
{
	__ENTER_FUNCTION
		Obj_TroopPtr objTroopPtr = POOLDEF_NEW(Obj_Troop);
	AssertEx(objTroopPtr,"");

	Table_Troop const* pTroop = GetTable_TroopByID(rTroop.GetType());
	if (pTroop == null_ptr)
	{
		return Obj_TroopPtr();
	}

	objTroopPtr->SetType(rTroop.GetType());
	objTroopPtr->SetLevel(rTroop.GetLevel());
	objTroopPtr->SetArrangeIndex(rTroop.GetArrangeIndex());
	objTroopPtr->SetScenePos(rPos);
	objTroopPtr->GetCooldownList() = rTroop.GetCooldownList();
	objTroopPtr->SetCurHp(rTroop.GetHp());
	CreateNpc(pTroop->GetDataIDbyIndex(rTroop.GetLevel()-1),rPos,false,nForce,rTroop.GetLevel(),objTroopPtr);

	//初始化战斗属性
	objTroopPtr->MarkInitalAttrCalcDirty();
	
	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_Troop>(objTroopPtr);
	_AddNonMarchObj(objPtr);
	return objTroopPtr;
	__LEAVE_FUNCTION
		return Obj_TroopPtr();
}

Obj_HeroPtr  Scene::CreateHeroObj(const Hero& rHero,const ScenePos &rPos,int nForce)
{
	__ENTER_FUNCTION
		Obj_HeroPtr objHeroPtr = POOLDEF_NEW(Obj_Hero);
		AssertEx(objHeroPtr,"");

		Table_Hero const* pHero = GetTable_HeroByID(rHero.GetType());
		if (pHero == null_ptr)
		{
			return Obj_HeroPtr();
		}

		objHeroPtr->SetUID(rHero.GetUID());
		objHeroPtr->SetType(rHero.GetType());
		objHeroPtr->SetLevel(rHero.GetLevel());
		objHeroPtr->SetQuality(rHero.GetQuality());
		objHeroPtr->SetName(rHero.GetName());
		objHeroPtr->SetArrangeIndex(rHero.GetArrangeIndex());
		objHeroPtr->SetScenePos(rPos);
		objHeroPtr->SetCurHp(rHero.GetHp());

		objHeroPtr->GetCooldownList() = rHero.GetCooldownList();
		CreateNpc(pHero->GetDataIDbyIndex(rHero.GetLevel()-1),rPos,false,nForce,rHero.GetLevel(),objHeroPtr);
		//初始化战斗属性
		objHeroPtr->MarkInitalAttrCalcDirty();
		
		ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_Hero>(objHeroPtr);
		_AddNonMarchObj(objPtr);
		return objHeroPtr;
	__LEAVE_FUNCTION
		return Obj_HeroPtr();
}

Obj_MarchPtr Scene::CreateMarch(const March& rMarchData,const ScenePos& rPos)
{
	__ENTER_FUNCTION

	Obj_MarchPtr MarchPtr = POOLDEF_NEW(Obj_March);
	AssertEx(MarchPtr, "");

	if (rMarchData.GetMarchId() == 0)
	{
		return Obj_MarchPtr();
	}

	MarchPtr->SetScenePos(rPos);

	//坐标
	MarchPtr->SetMarch(rMarchData);

	MarchPtr->SetGuid(rMarchData.GetMarchId());
	

	ObjPtr objPtr = boost::static_pointer_cast<Obj, Obj_March>(MarchPtr);
	_AddNonMarchObj(objPtr);
	return MarchPtr;

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

void Scene::_AddNonMarchObj(ObjPtr Ptr)
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

void Scene::_DelMarchImmediate(int nObjID)
{
	__ENTER_FUNCTION

	ObjPtrMap::iterator itRemove = m_ObjPtrMap.find(nObjID);
	AssertEx(itRemove != m_ObjPtrMap.end(), "");
	ObjPtr objPtr = itRemove->second;
	AssertEx(objPtr, "");
	AssertEx(objPtr->IsMarch(), "");

	Obj_MarchPtr marchPtr = boost::static_pointer_cast<Obj_March, Obj>(objPtr);
	AssertEx(marchPtr, "");

	marchPtr->OnLeaveScene();
	OnObjLeave(marchPtr->GetID());
	marchPtr->SetScene(null_ptr);
	marchPtr->SetID(invalid_id);

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
