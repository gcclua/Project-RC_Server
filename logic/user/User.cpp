#include "User.h"
#include "player/Player.h"
#include "city/CityManager.h"
#include "GameServerConfig.h"
#include "Message/LoginMsg.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"
#include "Clock.h"
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

User::User(Player* pPlayer)
	:m_pPlayer(pPlayer)
{
	BaseManagerPtr cityPtr = BaseManagerPtr(new CityManager(*this));
	m_mapBaseManager[EMANAGERTYPE_CITY] = cityPtr;

	m_nSaveTimeInterval = 0;
}

void User::SerializeToDB(DBFullUserData& rDest)
{
	__ENTER_FUNCTION
	for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
	{
		BaseManagerPtr Ptr = it->second;
		AssertEx(Ptr,"");
		Ptr->SerializeToDB(rDest);
	}
	__LEAVE_FUNCTION
}
void User::SerializeFromDB(const DBFullUserData& rSour)
{
	__ENTER_FUNCTION
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManagerPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSour);
		}
	__LEAVE_FUNCTION
}

void User::Init(void)
{
	__ENTER_FUNCTION
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManagerPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->Init();
		}
		__LEAVE_FUNCTION
}

void User::OnLogin()
{
	__ENTER_FUNCTION
		for (BaseManagerPtrMap::iterator it = m_mapBaseManager.begin();it != m_mapBaseManager.end();it++)
		{
			BaseManagerPtr Ptr = it->second;
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
			BaseManagerPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->Tick(rTimeInfo);
		}

		Tick_Save(rTimeInfo);
	__LEAVE_FUNCTION
}

BaseManagerPtr User::GetBaseManager(int nType)
{
	__ENTER_FUNCTION
		AssertEx(nType>=EMANAGERTYPE_MIN && nType<EMANAGERTYPE_MAX,"");
	    return m_mapBaseManager[nType];
	__LEAVE_FUNCTION
		return null_ptr;
}

void User::Tick_Save(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		m_nSaveTimeInterval += rTimeInfo.m_uTimeElapse;
	if (m_nSaveTimeInterval >= GameServerConfig::Instance().PlayerSaveInterval())
	{
		m_nSaveTimeInterval = 0;

		SavePlayerDataMsgPtr MsgPtr = POOLDEF_NEW(SavePlayerDataMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_Guid = GetGuid();
		SerializeToDB(MsgPtr->m_UserData);
		MsgPtr->m_bImmediateSave = false;
		MsgPtr->m_UserData.m_baseUser.m_LastLogoutTime = (int)Clock::getCurrentSystemTime();
		SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
	}
	__LEAVE_FUNCTION
}

tuint32 User::HandlePacket(::CG_REQ_NEAR_LIST& rPacket)
{
	__ENTER_FUNCTION
		MarchReqNearListMsgPtr MsgPtr = POOLDEF_NEW(MarchReqNearListMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_marchId = rPacket.marchid();
		SendMessage2March(MsgPtr->m_marchId,MsgPtr);
		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 User::HandlePacket(::CG_MOVE &rPacket)
{
	__ENTER_FUNCTION
		MarchMoveMsgPtr MsgPtr = POOLDEF_NEW(MarchMoveMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_marchId = rPacket.marchid();
		tint32 nSize = rPacket.poscount();
		MsgPtr->m_nPosCount = nSize;
		bool isClientMoving =(rPacket.ismoving() ==1 ? true:false);
		MsgPtr->m_ismoving = isClientMoving;
		if (nSize == rPacket.posx_size() && nSize == rPacket.posz_size())
		{
			for (tint32 i = 0; i < nSize; i++)
			{
				MsgPtr->m_nPosX.push_back(rPacket.posx(i));
				MsgPtr->m_nPoxZ.push_back(rPacket.posz(i));
			}
		}
		SendMessage2March(MsgPtr->m_marchId,MsgPtr);
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

void User::HandleMessage(const NoticeMsg& rMsg)
{
	Packets::GC_NOTICE_PAK pak;
	pak.m_PacketData.set_notice(rMsg.m_szNotice.GetCText());

	pak.m_PacketData.set_filterrepeat(rMsg.m_nIsFilterRepeat);

	SendPacket(pak);
}

void User::HandleMessage(const Remove_EffectMsg& rMsg)
{
	Packets::GC_REMOVEEFFECT_PAK effectPak;
	effectPak.m_PacketData.set_objid(rMsg.m_nObjId);
	effectPak.m_PacketData.set_effectid(rMsg.m_nEffectId);
	SendPacket(effectPak);
}

void User::HandleMessage(const Update_NeedImpactInfoMsg& rMsg)
{	
	Packets::GC_UPDATE_NEEDIMPACTINFO_PAK InfoPak;
	InfoPak.m_PacketData.set_objid(rMsg.m_nObjId);
	InfoPak.m_PacketData.add_impactid(rMsg.m_nImpactId[0]);
	InfoPak.m_PacketData.add_impactlogicid(rMsg.m_iImpactLogicId[0]);
	InfoPak.m_PacketData.add_isforever(rMsg.m_nIsForever[0]);

	InfoPak.m_PacketData.add_remaintime(rMsg.m_nRemainTime[0]);
	InfoPak.m_PacketData.add_isadd(rMsg.m_nIsAdd[0]);
	SendPacket(InfoPak);
}

void User::HandleMessage(const Player_EffectMsg &rMsg)
{
	Packets::GC_PLAY_EFFECT_PAK effectPak;
	effectPak.m_PacketData.set_objid(rMsg.m_nObjId);
	effectPak.m_PacketData.set_effectid(rMsg.m_nEffectId);
	SendPacket(effectPak);
}

void User::HandleMessage(const AttackFlyMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_ATTACKFLY_PAK flypak;
	flypak.m_PacketData.set_objid(rMsg.m_nObjId);
	flypak.m_PacketData.set_dis(rMsg.m_nDis);
	flypak.m_PacketData.set_hight(rMsg.m_nHight);
	flypak.m_PacketData.set_flytime(rMsg.m_nFlyTime);

	SendPacket(flypak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Force_SetPosMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_FORCE_SETPOS_PAK pak;
	pak.m_PacketData.set_serverid(rMsg.m_nObjId);
	pak.m_PacketData.set_posx(rMsg.m_nPosX);
	pak.m_PacketData.set_posz(rMsg.m_nPoxZ);
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Del_MarchMsg& rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_DELETE_OBJ_PAK pak;
	pak.m_PacketData.set_serverid(rMsg.m_nObjId);
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const Update_Animation_State &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_UPDATE_ANIMATION_STATE_PAK Animstatepak;
	Animstatepak.m_PacketData.set_objid(rMsg.m_nObjId);
	Animstatepak.m_PacketData.set_animationstate(rMsg.m_nAnimationState);
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

void User::HandleMessage(const RetUserSkillMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_RET_USE_SKILL_PAK retPak;
	retPak.m_PacketData.set_skillid(rMsg.m_nSkillId);
	retPak.m_PacketData.set_senderid(rMsg.m_nSenderId);
	retPak.m_PacketData.set_targetid(rMsg.m_nTargetId);
	SendPacket(retPak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetMarchMoveMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_MOVE_PAK pak;
	pak.m_PacketData.set_serverid(rMsg.m_serverId);
	pak.m_PacketData.set_poscount(rMsg.m_nPosCount);

	int nSize = rMsg.m_nPosCount;
	for (int i = 0; i < nSize; i++)
	{

		pak.m_PacketData.add_posserial(rMsg.m_nSerial[i]);
		pak.m_PacketData.add_posx(rMsg.m_nPosX[i]);
		pak.m_PacketData.add_posz(rMsg.m_nPoxZ[i]);;
	}
	SendPacket(pak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const RetMarchTeleMoveMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_TELEMOVE_PAK teleMovepak;
	teleMovepak.m_PacketData.set_objid(rMsg.m_nObjId);
	teleMovepak.m_PacketData.set_targetposx(rMsg.m_nPosX);
	teleMovepak.m_PacketData.set_targetposz(rMsg.m_nPoxZ);
	
	SendPacket(teleMovepak);
	__LEAVE_FUNCTION
}

void User::HandleMessage(const MarchStopMsg &rMsg)
{
	__ENTER_FUNCTION
	Packets::GC_STOP_PAK pak;
	pak.m_PacketData.set_serverid(rMsg.m_serverId);
	pak.m_PacketData.set_posserial(rMsg.m_nSerial);
	pak.m_PacketData.set_posx(static_cast<int>(rMsg.m_fX * 100.0f));
	pak.m_PacketData.set_posz(static_cast<int>(rMsg.m_fZ * 100.0f));

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
		if (rMarch.m_Guid != invalid_id)
		{
			continue;
		}

		pak.m_PacketData.add_guid(rMarch.m_Guid);
		pak.m_PacketData.add_name(rMarch.m_szName.GetCText());
		pak.m_PacketData.add_level(rMarch.m_nLevel);
		pak.m_PacketData.add_combatnum(rMarch.m_nCombatNum);
		nRealCount ++;
	}
	if (nRealCount > 0)
	{
		SendPacket(pak);
	}

	__LEAVE_FUNCTION

}