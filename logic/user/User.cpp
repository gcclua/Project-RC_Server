#include "User.h"
#include "Config.h"
#include "player/Player.h"
#include "city/CityManager.h"
#include "hero/HeroManager.h"
#include "march/MarchManager.h"
#include "Message/LoginMsg.h"
#include "Message/SceneMsg.h"
#include "Message/DBMsg.h"
#include "Message/CityMsg.h"
#include "service/MessageOp.h"
#include "packet/Packet/CG_REQ_NEAR_LIST_PAK.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "packet/Packet/GC_NOTICE_PAK.h"
#include "Message/ChatMsg.h"
#include "packet/Packet/GC_CHAT_PAK.h"
#include "packet/Packet/GC_NEAR_MARCHLIST_PAK.h"
#include "packet/Packet/GC_STOP_PAK.h"
#include "packet/Packet/GC_MOVE_PAK.h"
#include "packet/Packet/GC_TELEMOVE_PAK.h"
#include "packet/Packet/GC_RET_USE_SKILL_PAK.h"
#include "packet/Packet/GC_UPDATE_ANIMATION_STATE_PAK.h"
#include "packet/Packet/GC_FORCE_SETPOS_PAK.h"
#include "packet/Packet/GC_DELETE_OBJ_PAK.h"
#include "packet/Packet/GC_ATTACKFLY_PAK.h"
#include "packet/Packet/GC_PLAY_EFFECT_PAK.h"
#include "packet/Packet/GC_UPDATE_NEEDIMPACTINFO_PAK.h"
#include "packet/Packet/GC_REMOVEEFFECT_PAK.h"
#include "packet/Packet/GC_NOTICE_PAK.h"
#include "packet/Packet/GC_ROBOT_OPEN_PAK.h"
#include "packet/Packet/GC_ASSIGN_HERO_PAK.h"
#include "packet/Packet/CG_ASSIGN_HERO_PAK.h"
#include "packet/Packet/CG_BATTLEPREPARE_PAK.h"
#include "packet/Packet/CG_MARCH_MOVE_PAK.h"
#include "packet/Packet/GC_SEND_MARCH_PAK.h"
#include "packet/Packet/GC_LOGIN_RET_PAK.h"
#include "packet/Packet/GC_BATTLEINFOR_PAK.h"
#include "packet/Packet/GC_OBJPOSLIST_PAK.h"
#include "packet/Packet/GC_OBJCOMMANDPURSUE_PAK.h"
#include "packet/Packet/GC_OBJPREPAREFORATTACK_PAK.h"
#include "packet/Packet/GC_OBJGETHURT_PAK.h"
#include "packet/Packet/GC_FIGHT_PAK.h"
#include "packet/Packet/GC_BUILDING_LEVELUP_PAK.h"
#include "packet/Packet/GC_TROOP_TRAIN_PAK.h"
#include "packet/Packet/GC_BATTLEPREPARE_PAK.h"
#include "packet/Packet/GC_BATTLEEND_PAK.h"
#include "packet/Packet/GC_BATTLESTART_PAK.h"
#include "packet/Packet/GC_TROOPTRAIN_OVER_PAK.h"
#include "GuidDefine.h"
#include "Table/Table_CityBuildingSlot.h"

User::User(Player* pPlayer)
	:m_pPlayer(pPlayer)
{
	
	InitManage();
	m_nSaveTimeInterval = 0;
}

User::User(ACCOUNTNAME name)
{
	m_Name = name;
	Init();
}

void User::SerializeToDB(DBFullUserData& rDest)
{
	__ENTER_FUNCTION
		rDest.m_User.m_Guid = m_guid;
	    //rDest.m_User.m_CharName = m_Name.GetCText();
		tsnprintfex(rDest.m_User.m_CharName, sizeof(rDest.m_User.m_CharName), "%s",m_Name.GetCText());
		rDest.m_User.m_Level = m_nLevel;
		rDest.m_User.m_Gender = m_Gender;
		//rDest.m_User.m_AccName = m_szAccount.GetCText();
		tsnprintfex(rDest.m_User.m_AccName, sizeof(rDest.m_User.m_AccName), "%s",m_szAccount.GetCText());
	for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
	{
		BaseManager* Ptr = it->second;
		AssertEx(Ptr,"");
		Ptr->SerializeToDB(rDest);
	}
	__LEAVE_FUNCTION
}
void User::SerializeFromDB(const DBFullUserData& rSour)
{
	__ENTER_FUNCTION
		m_guid = rSour.m_User.m_Guid;
		m_Name = rSour.m_User.m_CharName;
		m_nLevel = rSour.m_User.m_Level;
		m_Gender = rSour.m_User.m_Gender;
		m_szAccount = rSour.m_User.m_AccName;
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManager* Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSour);
		}
	__LEAVE_FUNCTION
}

void User::InitManage(void)
{
	BaseManager* cityPtr = new CityManager(*this);
	m_mapBaseManager[EMANAGERTYPE_CITY] = cityPtr;

	BaseManager* heroPtr = new HeroManager(*this);
	m_mapBaseManager[EMANAGERTYPE_HERO] = heroPtr;

	BaseManager* marchPtr = new MarchManager(*this);
	m_mapBaseManager[EMANAGERTYPE_MARCH] = marchPtr;
}

void User::Init(void)
{
	__ENTER_FUNCTION
		InitManage();
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManager* Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->Init();
		}
		__LEAVE_FUNCTION
}

void User::InitAsCreateNewChar(int nTileId,int nX,int nZ)
{
	__ENTER_FUNCTION

		CacheLog(LOGDEF_INST(CreateChar),"InitAsCreateNewChar:: start  \1 userId=%d,\2 tileid=%d,\3 time=%d",m_guid,nTileId,gTimeManager.GetANSITime());
		DBReqCreateCityMsgPtr MsgPtr = POOLDEF_NEW(DBReqCreateCityMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_Data.m_UserId = m_guid;
		MsgPtr->m_Data.m_tileID = nTileId;
		MsgPtr->m_Data.m_fPosX  = (tfloat32)nX;
		MsgPtr->m_Data.m_fPosZ  = (tfloat32)nZ;
		int64 nCityId = GUIDDEF_GEN(City);
		MsgPtr->m_Data.m_nCityID = nCityId;
		MsgPtr->m_Data.m_nFood   = _GameConfig().m_nDefaultFood;
		MsgPtr->m_Data.m_nStone  = _GameConfig().m_nDefaultStone;
		MsgPtr->m_Data.m_nIron   = _GameConfig().m_nDefaultIron;
		MsgPtr->m_Data.m_nGold   = _GameConfig().m_nDefaultGold;
		MsgPtr->m_nPlayerID = m_pPlayer->GetID();

		tint32 nCount = GetTable_CityBuildingSlotCount();
		for (tint32 i = 0;i < nCount;i++)
		{
			const Table_CityBuildingSlot* pTable = GetTable_CityBuildingSlotByIndex(i);
			AssertEx(pTable,"");
			if (pTable->GetUnlockLevel() != 0)
			{
				continue;
			}
			DBBuilding rBuilding;
			int64 nBuildId = GUIDDEF_GEN(Building);
			rBuilding.m_ID = nBuildId;
			rBuilding.m_nLevel = 1;
			rBuilding.m_nSlot = pTable->GetId();
			rBuilding.m_nType = pTable->GetBuildingType();
			rBuilding.m_nCityID = nCityId;
			MsgPtr->m_Data.m_lstBuilding.push_back(rBuilding);
	
			if (pTable->GetBuildingType() == BUIDINGTYPE_BARRACKS)
			{
				DBMarch rMarch;
				rMarch.InitMarch(m_guid,nCityId,nBuildId);
				MsgPtr->m_Data.m_lstMarch.push_back(rMarch);
				DBTroopTrain rTroopTrain;
				rTroopTrain.InitTrain(nBuildId,nCityId);
				MsgPtr->m_Data.m_lstTrain.push_back(rTroopTrain);
			}
		}

		int HeroType = 1;
		if (m_Gender ==1)
		{
			HeroType = 2;
		}

		MsgPtr->m_Data.m_Hero.InitHero(HeroType,nCityId);

		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);

		CacheLog(LOGDEF_INST(CreateChar),"InitAsCreateNewChar:: end  \1 userId=%d,\2 tileid=%d,\3 time=%d",m_guid,nTileId,gTimeManager.GetANSITime());

	__LEAVE_FUNCTION
}

void User::OnLogin()
{
	__ENTER_FUNCTION
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManager* Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->OnLogin();
		}
		__LEAVE_FUNCTION
}

void User::SetName(const CHARNAME& NewName)
{
	__ENTER_FUNCTION
		m_Name =NewName;
	__LEAVE_FUNCTION
}

void User::SetName(const tchar* strName)
{
	__ENTER_FUNCTION

		if (strName != null_ptr)
		{
			m_Name = strName;
		}

		__LEAVE_FUNCTION
}

void User::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManager* Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->Tick(rTimeInfo);
		}

		Tick_Save(rTimeInfo);
	__LEAVE_FUNCTION
}

void  User::FillGCLogin(::GC_LOGIN_RET &rPacket)
{
	__ENTER_FUNCTION
		CityManager* pCityManager = (CityManager*)GetBaseManager(EMANAGERTYPE_CITY);
		AssertEx(pCityManager,"");
		pCityManager->FileData(rPacket.mutable_city());

		HeroManager* pHeroManage = (HeroManager*)GetBaseManager(EMANAGERTYPE_HERO);
		AssertEx(pHeroManage,"");
		pHeroManage->FileData(rPacket.mutable_herolist());

		MarchManager* pMarchManage = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
		AssertEx(pMarchManage,"");
		pMarchManage->FileData(rPacket.mutable_marchlist());

	__LEAVE_FUNCTION
}

BaseManager* User::GetBaseManager(int nType)
{
	__ENTER_FUNCTION
		AssertEx(nType>=EMANAGERTYPE_MIN && nType<EMANAGERTYPE_MAX,"");
	    return m_mapBaseManager[nType];
	__LEAVE_FUNCTION
		return null_ptr;
}

bool User::UpdateMarchState(int64 nMarchId,int nState)
{
	__ENTER_FUNCTION
		MarchManager* pMarchManage = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
		AssertEx(pMarchManage,"");
		return pMarchManage->UpdateMarchState(nMarchId,nState);
	__LEAVE_FUNCTION
		return false;
}

bool User::SendMarchIntoMap(int64 nMarchId)
{
	__ENTER_FUNCTION

	MarchManager* pMarchManage = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
	AssertEx(pMarchManage,"");
	if (!pMarchManage->CheckSendMarchIntoMap(nMarchId))
	{
		return false;
	}

	MarchPtr pMarch = pMarchManage->GetMarchInfo(nMarchId);
	if (pMarch== null_ptr)
	{
		return false;
	}

	CityManager* pCityManager = (CityManager*)GetBaseManager(EMANAGERTYPE_CITY);
	AssertEx(pCityManager,"");
	if (!pCityManager->CheckSendMarchIntoMap(pMarch->GetBuildId()))
	{
		return false;
	}

	 pMarchManage->UpdateMarchState(nMarchId,MARCHSTATUS_READY);

	 ReqMarchStartMsgPtr MsgPtr = POOLDEF_NEW(ReqMarchStartMsg);

	 MsgPtr->m_Pos = pCityManager->GetPos();
	 pMarch->SetPos(pCityManager->GetPos());
	 MsgPtr->m_March = *pMarch;
	 SendMessage2Srv(ServiceID::SCENE,MsgPtr);

	__LEAVE_FUNCTION
		return false;
}


bool User::AssignHeroToMarch(int64 nMarchId,int64 nHeroId)
{
	__ENTER_FUNCTION
		HeroManager* pHeroManager = (HeroManager*)GetBaseManager(EMANAGERTYPE_HERO);
	    AssertEx(pHeroManager,"");

		if (!pHeroManager->CheckAssignHero(nHeroId))
		{
			return false;
		}

		MarchManager* pMarchManager = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
		AssertEx(pMarchManager,"");

		if (!pMarchManager->CheckAssignHero(nMarchId))
		{
			return false;
		}

		int64 curHeroId = pMarchManager->GetHeroId(nMarchId);

		HeroPtr pHero = pHeroManager->GetHero(nHeroId);

		AssertEx(pHero,"");

		pMarchManager->AssignHeroToMarch(nMarchId,*pHero);
		pHeroManager->AssignHeroToMarch(nHeroId,nMarchId);

		if (curHeroId >0)
		{
			pHeroManager->UnAssignHero(curHeroId);
		}


		return true;
	__LEAVE_FUNCTION
	return false;
}

void User::Tick_Save(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		m_nSaveTimeInterval += rTimeInfo.m_uTimeElapse;
	if (m_nSaveTimeInterval >= _GameConfig().m_nPlayerSaveInterval)
	{
		m_nSaveTimeInterval = 0;

		SavePlayerDataMsgPtr MsgPtr = POOLDEF_NEW(SavePlayerDataMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_Guid = GetGuid();
		SerializeToDB(MsgPtr->m_UserData);
		MsgPtr->m_bImmediateSave = false;
		MsgPtr->m_UserData.m_User.m_LastLogoutTime = gTimeManager.GetANSITime();
		SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
	}
	__LEAVE_FUNCTION
}

tuint32 User::HandlePacket(::CG_Troop_Train &rPacket)
{
	__ENTER_FUNCTION

	MarchManager* pMarchManager = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
	AssertEx(pMarchManager,"");
	Packets::GC_TROOP_TRAIN_PAK pak;
	if (!pMarchManager->CheckTrainTroop(rPacket.buildid(),rPacket.trooptype(),rPacket.queueindex()))
	{
		pak.m_PacketData.set_ret(2);
		SendPacket(pak);
		return false;
	}


		CityManager* pCityManager = (CityManager*)GetBaseManager(EMANAGERTYPE_CITY);
	AssertEx(pCityManager,"");
	
	pCityManager->BeginTrainTroop(rPacket.buildid(),rPacket.queueindex(),rPacket.trooptype(),rPacket.count(),(GC_Troop_Train*)(&pak.m_PacketData));
	SendPacket(pak);

	return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_OBJPOSLIST &rPacket)
{
	__ENTER_FUNCTION
		ReqObjListMsgPtr MsgPtr = POOLDEF_NEW(ReqObjListMsg);
	MsgPtr->m_nSceneId = rPacket.sceneid();
	MsgPtr->m_ReceiverGuid = GetGuid();
	SceneID rScene(1,rPacket.sceneid());
	SendMessage2Scene(rScene,MsgPtr);
	return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_MARCH_MOVE &rPacket)
{
	__ENTER_FUNCTION
		ReqMarchSetPosMsgPtr MsgPtr = POOLDEF_NEW(ReqMarchSetPosMsg);
		MsgPtr->m_fPosX = (tfloat32)rPacket.posx();
		MsgPtr->m_fPosZ = (tfloat32)rPacket.posz();
		MsgPtr->m_ReceiverGuid = rPacket.marchid();
		SceneID rScene(0,0);
		SendMessage2Scene(rScene,MsgPtr);
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_BATTLEPREPARE &rPacket)
{
	__ENTER_FUNCTION
		ReqArrangChangeMsgPtr MsgPtr = POOLDEF_NEW(ReqArrangChangeMsg);
		MsgPtr->m_nSceneId = rPacket.sceneid();
	MsgPtr->m_ReceiverGuid = GetGuid();
	int nSize = rPacket.objlist_size();
	for (int i=0;i<nSize;i++)
	{
		CG_OBJARRANGEINDEX* pIndex = rPacket.mutable_objlist(i);
		MsgPtr->m_lstArrange.push_back(pIndex->arrangeindex());
		MsgPtr->m_lstObj.push_back(pIndex->objid());
	}
	SceneID rScene(1,rPacket.sceneid());
	SendMessage2Scene(rScene,MsgPtr);
	return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_Building_LevelUp &rPacket)
{
	__ENTER_FUNCTION
		AssertEx(rPacket.buildingid()>0,"");
		CityManager* pCityManager = (CityManager*)GetBaseManager(EMANAGERTYPE_CITY);
		AssertEx(pCityManager,"");
		Packets::GC_BUILDING_LEVELUP_PAK pak;
		pCityManager->BuildLevelUp(rPacket.buildingid(),(GC_Building_LevelUp*)(&pak.m_rPacketData));
		SendPacket(pak);
	
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
	return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_BATTLEINFOR &rPacket)
{
	__ENTER_FUNCTION
		ReqBattleInfoMsgPtr MsgPtr = POOLDEF_NEW(ReqBattleInfoMsg);
		MsgPtr->m_nSceneId = rPacket.sceneid();
		SceneID rScene(1,rPacket.sceneid());
		MsgPtr->m_ReceiverGuid = GetGuid();
		SendMessage2Scene(rScene,MsgPtr);
		return PACKET_EXE_CONTINUE;
		__LEAVE_FUNCTION
			return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_ROBOT_OPEN &rPacket)
{
	__ENTER_FUNCTION
		ReqSetRobotOpenMsgPtr MsgPtr = POOLDEF_NEW(ReqSetRobotOpenMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_ReceiverGuid = GetGuid();
	if (rPacket.open()>0)
	{
		MsgPtr->m_bOpen        = 1;
	}
	else
	{
		MsgPtr->m_bOpen        = 0;
	}
	SceneID rScene(1,rPacket.sceneid());
	SendMessage2Scene(rScene,MsgPtr);
	return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_SKILL_USE &rPacket)
{
	__ENTER_FUNCTION
		tint32 nSkillId =-1;
		tint32 nTargetId =-1;
		if (rPacket.has_skillid())
		{
			nSkillId =rPacket.skillid();
		}
		if (rPacket.targetid() != -1)
		{
			nTargetId =rPacket.targetid();
		}
		
		UserSkillMsgPtr MsgPtr = POOLDEF_NEW(UserSkillMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_nSenderId = rPacket.senderid();
		MsgPtr->m_nSkillId  = nSkillId;
		MsgPtr->m_nTargetId = nTargetId;
		SendMessage2Scene(rPacket.sceneid(),MsgPtr);


	return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_SEND_MARCH &rPacket)
{
	__ENTER_FUNCTION
		int64 nMarchId = rPacket.marchid();
		if (nMarchId<=0)
			return PACKET_EXE_CONTINUE;

		if (SendMarchIntoMap(nMarchId))
		{

		}
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

uint32 User::HandlePacket(::CG_LEAVE_COPYSCENE & rPacket)
{
	__ENTER_FUNCTION
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32  User::HandlePacket(::CG_FIGHT & rPacket)
{
	__ENTER_FUNCTION
		MarchReqFightMsgPtr MsgPtr = POOLDEF_NEW(MarchReqFightMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_nSceneId      = rPacket.sceneid();
		MsgPtr->m_nType         = rPacket.type();
		MsgPtr->m_nAtttackId    = rPacket.attackid();
		MsgPtr->m_nDefenceId    = rPacket.defenceid();
		MsgPtr->m_ReceiverGuid  = GetGuid();
		if (rPacket.has_defenceid())
		{
			MsgPtr->m_nDefenceId  = rPacket.defenceid();
		}
		else
		{
			MsgPtr->m_nDefenceId  = 0;
		}
		
		SendMessage2Srv(ServiceID::SCENE,MsgPtr);
		//SendMessage2March(MsgPtr->m_nAtttackId,MsgPtr);
		return PACKET_EXE_CONTINUE;
		__LEAVE_FUNCTION
			return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_REQ_NEAR_LIST& rPacket)
{
	__ENTER_FUNCTION
		MarchReqNearListMsgPtr MsgPtr = POOLDEF_NEW(MarchReqNearListMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_nReceiveObjId = rPacket.blockid();
		MsgPtr->m_ReceiverGuid = GetGuid();
		SceneID rScene(0,0);
		SendMessage2Scene(rScene,MsgPtr);
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_MOVE &rPacket)
{
	__ENTER_FUNCTION
		MarchMoveMsgPtr MsgPtr = POOLDEF_NEW(MarchMoveMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_nReceiveObjId = rPacket.objid();
		tint32 nSize = rPacket.poscount();
		MsgPtr->m_nPosCount = nSize;
		MsgPtr->m_ReceiverGuid = GetGuid();
		bool isClientMoving =(rPacket.ismoving() ==1 ? true:false);
		MsgPtr->m_ismoving = isClientMoving;
		if (nSize == rPacket.posx_size() && nSize == rPacket.posz_size())
		{
			for (tint32 i = 0; i < nSize; i++)
			{
				MsgPtr->m_fPosX.push_back((tfloat32)rPacket.posx(i));
				MsgPtr->m_fPoxZ.push_back((tfloat32)rPacket.posz(i));
			}
		}
		SceneID rScene(invalid_id,rPacket.sceneid());
		SendMessage2Scene(rScene,MsgPtr);
	return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
	return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_CHAT &rPacket)
{
	__ENTER_FUNCTION
		// 应先做检查 禁言 发言CD等等
		time_t nUnForbidTime = m_UnForbidTalkTime;
	time_t nAnsiTime = _ansitime();
	if (nUnForbidTime > nAnsiTime)
	{
		tint32 nDiffTime = static_cast<tint32>(nUnForbidTime - nAnsiTime);

		tint32 nDaySeconds = 60 * 60 * 24;
		tint32 nHourSeconds = 60 * 60;
		tint32 nMinuteSeconds = 60;

		tint32 nDay = nDiffTime / nDaySeconds;
		tint32 nHour = (nDiffTime % nDaySeconds) / nHourSeconds;
		tint32 nMinute = (nDiffTime % nHourSeconds) / nMinuteSeconds;

		tchar szNotice[256] = {0};
		tchar* str = DictionaryFormat::FormatDictionary(szNotice, sizeof(szNotice), "#{3233}", nDay, nHour, nMinute);
		SendNotice(str);

		//CacheLog(LOGDEF_INST(Chat), "Forbid Chat! user(%08X, %08X)  unforbidtime(%d), ansitime(%d), difftime(%d), day(%d), hour(%d), minute(%d)",
			//GetGuid().GetHigh32Value(), GetGuid().GetLow32Value(),
			//static_cast<tint32>(nUnForbidTime), static_cast<tint32>(nAnsiTime), nDiffTime,
			//nDay, nHour, nMinute);

		return PACKET_EXE_CONTINUE;
	}

		

		//if (_GameConfig().m_bOpenCheckChatUnsualEmotion && CheckContent_Utf8mb4(rPacket.chatinfo().c_str()))
		//{
			//SendNotice("#{1278}");
			//return PACKET_EXE_CONTINUE;
		//}

		if (false == IsNoneInvalidText(rPacket))
		{
			SendNotice("#{1278}");
			return PACKET_EXE_CONTINUE;
		}


		TextChat textchat;
		textchat.WriteFromCGCHAT(rPacket);

		HandleChatInfo(textchat);

		__LEAVE_FUNCTION
			return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_ASSIGN_HERO &rPacket)
{
	__ENTER_FUNCTION
		int64 nMarchId = rPacket.marchid();
		int64 nHeroId  = rPacket.heroid();
		AssertEx(nMarchId>0,"");
		AssertEx(nHeroId>0,"");
		Packets::GC_ASSIGN_HERO_PAK pak;
		pak.m_PacketData.set_marchid(nMarchId);
		pak.m_PacketData.set_heroid(nHeroId);
		if (AssignHeroToMarch(nMarchId,nHeroId))
		{
			pak.m_PacketData.set_ret(0);
		}
		else
		{
			pak.m_PacketData.set_ret(1);
		}

		SendPacket(pak);
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

void User::SendPacket( const Packet &rPacket )
{
	__ENTER_FUNCTION

		m_pPlayer->SendPacket(rPacket);

	__LEAVE_FUNCTION
}

void User::SendNotice( const tchar* szNotice ,bool IsFilterRepeat)
{
	__ENTER_FUNCTION

		if (szNotice != null_ptr && szNotice[0])
		{
			Packets::GC_NOTICE_PAK pak;
			pak.m_PacketData.set_notice(szNotice);
			if (IsFilterRepeat == true)
			{
				pak.m_PacketData.set_filterrepeat(1);
			}
			SendPacket(pak);
		}

		__LEAVE_FUNCTION
}

bool User::IsNoneInvalidText(CG_CHAT &rPacket)
{
	__ENTER_FUNCTION

		std::string strChatInfo(rPacket.chatinfo());

	if (std::string::npos != strChatInfo.find("\n"))
	{
		return false;
	}

	return true;

	__LEAVE_FUNCTION
		return false;
}

void User::HandleChatInfo(const TextChat& textchat, tint32 nVoiceIndex /* = invalid_id */)
{
	__ENTER_FUNCTION

		CG_CHAT::CHATTYPE eChatType = static_cast<CG_CHAT::CHATTYPE>(textchat.GetChannel());
	switch (eChatType)
	{
	case CG_CHAT::CHAT_TYPE_NORMAL:
		{
	
				Packets::GC_CHAT_PAK pak;
				pak.m_PacketData.set_chattype(eChatType);
				pak.m_PacketData.set_chatinfo(textchat.GetChatInfo().GetCText());
				pak.m_PacketData.set_senderguid(m_guid);
				pak.m_PacketData.set_sendername(m_Name.GetCText());
				pak.m_PacketData.set_senderlevel(m_nLevel);
				

				//Scene& rScene = GetScene();
				//rScene.BroadCast(pak);


				//AuditLog(LOGDEF_INST(Audit_Chat), "ChatInfo", GetGuid(), "Channel=NORMAL \1 Info=%s", textchat.GetChatInfo().GetCText());
		}
		break;
	
	case CG_CHAT::CHAT_TYPE_WORLD:
		{
		

			// 副本链接会发送到世界频道 不算CD
			
			BroadcastChatMsgPtr msgPtr = POOLDEF_NEW(BroadcastChatMsg);
			AssertEx(msgPtr, "");
			if (msgPtr)
			{
				msgPtr->m_ChannelType = textchat.GetChannel();
				msgPtr->m_SenderGuid = m_guid;
				msgPtr->m_SenderName = m_Name;
				msgPtr->m_strChatInfo = textchat.GetChatInfo();
				msgPtr->m_SenderLevel = m_nLevel;
				SendMessage2Scene(msgPtr);

				//m_LastWorldChatTime = gTimeManager.GetANSITime();

				//AuditLog(LOGDEF_INST(Audit_Chat), "ChatInfo", GetGuid(), "Channel=WORLD \1 Info=%s", textchat.GetChatInfo().GetCText());
			}			
		}
		break;
	
	
	case CG_CHAT::CHAT_TYPE_FRIEND:
		{
			if (textchat.IsHaveReceiverGuid())
			{
				int64 receiverGuid = textchat.GetReceiverGuid();
				if (receiverGuid>0)
				{
					SendFriendChatMsgPtr msgPtr = POOLDEF_NEW(SendFriendChatMsg);
					AssertEx(msgPtr, "");
					if (msgPtr)
					{
						msgPtr->m_SenderGuid = m_guid;
						msgPtr->m_SenderName = m_Name;
						msgPtr->m_strChatInfo = textchat.GetChatInfo();
						msgPtr->m_SenderLevel = m_nLevel;
						// 发给私聊对象
						SendMessage2Srv(ServiceID::WORLDUSER, msgPtr);
					}

					//AuditLog(LOGDEF_INST(Audit_Chat), "ChatInfo", GetGuid(), "Channel=FRIEND \1 Info=%s", textchat.GetChatInfo().GetCText());

				}
			}			
		}
		break;
	
	default:
		break;
	}

	__LEAVE_FUNCTION
}

void User::HandleMessage(const KickPlayerByGuidMsg &rMsg)
{
	__ENTER_FUNCTION
		m_pPlayer->KickMe(rMsg.m_nReason);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetMarchStartMsg& rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_SEND_MARCH_PAK pak;
		
		pak.m_PacketData.set_ret(rMsg.m_ret);
		if (rMsg.m_ret)
		{
			UpdateMarchState(rMsg.m_marchId,MARCHSTATUS_PROCESS);
			
			pak.m_PacketData.set_marchid(rMsg.m_marchId);
		}
		SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetBattleStartMsg& rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_BATTLESTART_PAK pak;

	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetBattleEndMsg& rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_BATTLEEND_PAK pak;

		pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
		pak.m_PacketData.set_camp(rMsg.m_camp);
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const MarchRetFightMsg &rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_FIGHT_PAK pak;
		pak.m_PacketData.set_marchid(rMsg.m_nMarchId);
		pak.m_PacketData.set_ret(rMsg.m_nResult);
		pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
		pak.m_PacketData.set_sceneclass(rMsg.m_nSceneClass);
		SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const UpdateMarchMsg &rMsg)
{
	__ENTER_FUNCTION
	MarchManager* pMarchManager = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
	AssertEx(pMarchManager,"");

	pMarchManager->UpdateMarchData(rMsg.m_rMarch);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetObjListMsg &rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_OBJPOSLIST_PAK pak;
		pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	int nSize = (int)rMsg.m_objList.size();
	for (int i=0;i<nSize;i++)
	{
		GC_OBJPOS * pObj = pak.m_PacketData.add_objposlist();
		pObj->set_objid(rMsg.m_objList[i].m_objId);
		pObj->set_hp(rMsg.m_objList[i].m_hp);;
		pObj->set_posx((int)(rMsg.m_objList[i].m_fPosX*100));
		pObj->set_posz((int)(rMsg.m_objList[i].m_fPosZ*100));
		pObj->set_objstate(rMsg.m_objList[i].m_nState);
		pObj->set_targetid(rMsg.m_objList[i].m_nTargetId);
	}

	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetBattleInfoMsg& rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_BATTLEINFOR_PAK pak;
		pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
		pak.m_PacketData.set_camp(rMsg.m_nCamp);
		pak.m_PacketData.set_currentstate(rMsg.m_nState);
		int nSize = (int)rMsg.m_objList.size();
		for (int i=0;i<nSize;i++)
		{
			GC_OBJINFOR * pObjInfo = pak.m_PacketData.add_objlist();
			pObjInfo->set_id(rMsg.m_objList[i].m_objId);
			pObjInfo->set_unitdataid(rMsg.m_objList[i].m_dataId);
			int SkillCount = (int)rMsg.m_objList[i].m_skillLst.size();
			//pObjInfo->set_skilldataid(rMsg.m_objList[i].m_skillLst[0]);
			for (int j=0;j<SkillCount;j++)
			{
				pObjInfo->add_skilldataid(rMsg.m_objList[i].m_skillLst[j]);
			}
			pObjInfo->set_arrangeindex(rMsg.m_objList[i].m_arrangeIndex);
			pObjInfo->set_attack(rMsg.m_objList[i].m_attack);
			pObjInfo->set_camp(rMsg.m_objList[i].m_camp);
			pObjInfo->set_hp(rMsg.m_objList[i].m_hp);
			pObjInfo->set_level(rMsg.m_objList[i].m_level);
			pObjInfo->set_defence(rMsg.m_objList[i].m_defence);
			pObjInfo->set_maxhp(rMsg.m_objList[i].m_maxHp);
			pObjInfo->set_posx((int)(rMsg.m_objList[i].m_fPosX*100));
			pObjInfo->set_posz((int)(rMsg.m_objList[i].m_fPosZ*100));
			pObjInfo->set_sp(rMsg.m_objList[i].m_xp);
			pObjInfo->set_unitcount(rMsg.m_objList[i].m_unitCount);

		}
		
		SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetSetRobotOpenMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_ROBOT_OPEN_PAK pak;
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	pak.m_PacketData.set_ret(rMsg.m_nRet);
	SendPacket(pak);
	__LEAVE_FUNCTION

}

void User::HandleMessage(const NoticeMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_NOTICE_PAK pak;
	pak.m_PacketData.set_notice(rMsg.m_szNotice.GetCText());

	pak.m_PacketData.set_filterrepeat(rMsg.m_nIsFilterRepeat);

	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Remove_EffectMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_REMOVEEFFECT_PAK effectPak;
	effectPak.m_PacketData.set_objid(rMsg.m_nObjId);
	effectPak.m_PacketData.set_effectid(rMsg.m_nEffectId);
	effectPak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(effectPak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Update_NeedImpactInfoMsg& rMsg)
{	
	__ENTER_FUNCTION
	Packets::GC_UPDATE_NEEDIMPACTINFO_PAK InfoPak;
	InfoPak.m_PacketData.set_objid(rMsg.m_nObjId);
	InfoPak.m_PacketData.add_impactid(rMsg.m_nImpactId[0]);
	InfoPak.m_PacketData.add_impactlogicid(rMsg.m_iImpactLogicId[0]);
	InfoPak.m_PacketData.add_isforever(rMsg.m_nIsForever[0]);
	InfoPak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	InfoPak.m_PacketData.add_remaintime(rMsg.m_nRemainTime[0]);
	InfoPak.m_PacketData.add_isadd(rMsg.m_nIsAdd[0]);
	SendPacket(InfoPak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Player_EffectMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_PLAY_EFFECT_PAK effectPak;
	effectPak.m_PacketData.set_objid(rMsg.m_nObjId);
	effectPak.m_PacketData.set_effectid(rMsg.m_nEffectId);
	effectPak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(effectPak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const AttackFlyMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_ATTACKFLY_PAK flypak;
	flypak.m_PacketData.set_objid(rMsg.m_nObjId);
	flypak.m_PacketData.set_dis(rMsg.m_nDis);
	flypak.m_PacketData.set_hight(rMsg.m_nHight);
	flypak.m_PacketData.set_flytime(rMsg.m_nFlyTime);
	flypak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(flypak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Force_SetPosMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_FORCE_SETPOS_PAK pak;
	pak.m_PacketData.set_objid(rMsg.m_nObjId);
	pak.m_PacketData.set_posx((int)(rMsg.m_fPosX*100));
	pak.m_PacketData.set_posz((int)(rMsg.m_fPosZ*100));
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Del_MarchMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_DELETE_OBJ_PAK pak;
	pak.m_PacketData.set_objid(rMsg.m_nObjId);
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	pak.m_PacketData.set_marchid(rMsg.m_nMarchObjId);

	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const ObjTrackTargetMsg &rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_OBJCOMMANDPURSUE_PAK pak;
		pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
		pak.m_PacketData.set_aimobjid(rMsg.m_nTargetId);
		pak.m_PacketData.set_objid(rMsg.m_nObjId);

		SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const ObjHurtMsg &rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_OBJGETHURT_PAK pak;
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	pak.m_PacketData.set_attackobjid(rMsg.m_nAttackId);
	pak.m_PacketData.set_objid(rMsg.m_nObjId);
	pak.m_PacketData.set_damage(rMsg.m_damage);
	pak.m_PacketData.set_deathnumber(rMsg.m_DeadCount);
	pak.m_PacketData.set_objdead(rMsg.m_IsDie);
	pak.m_PacketData.set_objid(rMsg.m_nObjId);

	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const ObjAttackTargetMsg &rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_OBJPREPAREFORATTACK_PAK pak;
		pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
		pak.m_PacketData.set_aimobjid(rMsg.m_nTargetId);
		pak.m_PacketData.set_objid(rMsg.m_nObjId);
		SendPacket(pak);

	__LEAVE_FUNCTION
}

void User::HandleMessage(const Update_Animation_State &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_UPDATE_ANIMATION_STATE_PAK Animstatepak;
	Animstatepak.m_PacketData.set_objid(rMsg.m_nObjId);
	Animstatepak.m_PacketData.set_animationstate(rMsg.m_nAnimationState);
	Animstatepak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	if (rMsg.m_nVerticalOffDis>0)
	{
		Animstatepak.m_PacketData.set_verticaloffdis(rMsg.m_nVerticalOffDis);
	}
	if (rMsg.m_nHorizontalOffDis>0)
	{
		Animstatepak.m_PacketData.set_horizontaloffdis(rMsg.m_nHorizontalOffDis);
	}
	if (rMsg.m_nStateLastTime>0)
	{
		Animstatepak.m_PacketData.set_statelasttime(rMsg.m_nStateLastTime);
	}
	if ( rMsg.m_nStateResortTime > 0 )
	{
		Animstatepak.m_PacketData.set_stateresorttime(rMsg.m_nStateResortTime);
	}
	if ( rMsg.m_nHitTimes > 1 )
	{ // 多次受击
		Animstatepak.m_PacketData.set_hittimes(rMsg.m_nHitTimes);
		if ( rMsg.m_nHitInterval > 0 )
		{ // 多次受击的间隔
			Animstatepak.m_PacketData.set_hitinterval(rMsg.m_nHitInterval);
		}
	}

	SendPacket(Animstatepak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetArrangChangeMsg &rMsg)
{
	__ENTER_FUNCTION
		Packets::GC_BATTLEPREPARE_PAK pak;
	    pak.m_PacketData.set_ret(rMsg.m_ret);
		SendPacket(pak);
		
		
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetUserSkillMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_RET_USE_SKILL_PAK retPak;
	retPak.m_PacketData.set_skillid(rMsg.m_nSkillId);
	retPak.m_PacketData.set_senderid(rMsg.m_nSenderId);
	retPak.m_PacketData.set_targetid(rMsg.m_nTargetId);
	retPak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(retPak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetMarchMoveMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_MOVE_PAK pak;
	pak.m_PacketData.set_objid(rMsg.m_nObjId);
	pak.m_PacketData.set_poscount(rMsg.m_nPosCount);
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	int nSize = rMsg.m_nPosCount;
	for (int i = 0; i < nSize; i++)
	{

		pak.m_PacketData.add_posserial(rMsg.m_nSerial[i]);
		pak.m_PacketData.add_posx((int)(rMsg.m_fPosX[i]*100));
		pak.m_PacketData.add_posz((int)(rMsg.m_fPoxZ[i]*100));;
	}
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetMarchTeleMoveMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_TELEMOVE_PAK teleMovepak;
	teleMovepak.m_PacketData.set_objid(rMsg.m_nObjId);
	teleMovepak.m_PacketData.set_targetposx((int)(rMsg.m_fPosX*100));
	teleMovepak.m_PacketData.set_targetposz((int)(rMsg.m_fPoxZ*100));
	teleMovepak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	
	SendPacket(teleMovepak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const MarchStopMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_STOP_PAK pak;
	pak.m_PacketData.set_objid(rMsg.m_nObjId);
	pak.m_PacketData.set_posserial(rMsg.m_nSerial);
	pak.m_PacketData.set_posx((int)(rMsg.m_fX*100));
	pak.m_PacketData.set_posz((int)(rMsg.m_fZ*100));
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const MarchRetNearListMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_NEAR_MARCHLIST_PAK pak;
	tint32 nRealCount = (int)rMsg.m_BaseMarchVec.size();
	for (tint32 i = 0; i < nRealCount; i++)
	{
		MarchBaseInfo rMarch = rMsg.m_BaseMarchVec[i];
		if (rMarch.m_Guid == invalid_id)
		{
			continue;
		}

		pak.m_PacketData.add_guid(rMarch.m_Guid);
		pak.m_PacketData.add_name(rMarch.m_szName.GetCText());
		pak.m_PacketData.add_level(rMarch.m_nLevel);
		pak.m_PacketData.add_posx((int)rMarch.m_fPosX*100);
		pak.m_PacketData.add_posz((int)rMarch.m_fPosZ*100);
	}
	pak.m_PacketData.set_sceneid(rMsg.m_nSceneId);

	SendPacket(pak);

	__LEAVE_FUNCTION

}

void User::HandleMessage(const TrainTroopOverMsg& rMsg)
{
	__ENTER_FUNCTION
		MarchManager* pMarchManger = (MarchManager*)GetBaseManager(EMANAGERTYPE_MARCH);
		AssertEx(pMarchManger,"");

		pMarchManger->AddTroopByBuildId(rMsg.m_nBuildId,rMsg.m_nType,rMsg.m_nHp,rMsg.m_nQueueIndex);

		Packets::GC_TROOPTRAIN_OVER_PAK pak;
		pak.m_PacketData.set_ret(0);
		pak.m_PacketData.set_buildid(rMsg.m_nBuildId);
		pak.m_PacketData.set_queueid(rMsg.m_ID);
		pak.m_PacketData.set_trooptype(rMsg.m_nType);
		pak.m_PacketData.set_hp(rMsg.m_nHp);
		SendPacket(pak);

	__LEAVE_FUNCTION
}

