#include "GameInterface_Scene.h"
#include "Message/SceneMsg.h"
#include "Service/MessageOp.h"
#include "Message/ChatMsg.h"
#include "Scene/Scene/Scene.h"
#include "Packet/Packet/GC_CHAT_PAK.h"
#include "Table/Table_NameFilter.h"


void SceneInterface::BroadCastChatMsg2Scene(::GC_CHAT &rPacket)
{
	__ENTER_FUNCTION
	BroadcastChatMsgPtr msgPtr = POOLDEF_NEW(BroadcastChatMsg);
	AssertEx(msgPtr, "");

	msgPtr->m_ChannelType = rPacket.chattype();
	msgPtr->m_strChatInfo = rPacket.chatinfo().c_str();
	
	SendMessage2Scene(msgPtr);
	__LEAVE_FUNCTION
}

void SceneInterface::SendNoticeToUser(const int64 &rGuid, const char *szNotice)
{
	__ENTER_FUNCTION

	if (rGuid != invalid_guid64 && szNotice != null_ptr)
	{
		NoticeMsgPtr MsgPtr = POOLDEF_NEW(NoticeMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_szNotice = szNotice;
		SendMessage2User(rGuid, MsgPtr);
	}

	__LEAVE_FUNCTION
}

void SceneInterface::BroadcastNotice(const char *szNotice)
{
	__ENTER_FUNCTION

	if (szNotice != null_ptr)
	{
		BroadcastNoticeMsgPtr msgPtr = POOLDEF_NEW(BroadcastNoticeMsg);
		AssertEx(msgPtr, "");
		msgPtr->m_strChatInfo = szNotice;
		SendMessage2Scene(msgPtr);
	}

	__LEAVE_FUNCTION
}

void SceneInterface::BroadcastNoticeToSceneClass(SceneClassID nClassID,const char *szNotice)
{
	__ENTER_FUNCTION

	if (szNotice != null_ptr)
	{
		BroadcastNoticeMsgPtr msgPtr = POOLDEF_NEW(BroadcastNoticeMsg);
		AssertEx(msgPtr, "");
		msgPtr->m_strChatInfo = szNotice;
		SendMessage2Scene(nClassID,msgPtr);
	}

	__LEAVE_FUNCTION
}

void SceneInterface::BroadcastNoticeToSceneInst(SceneID sceneid,const char *szNotice)
{
	__ENTER_FUNCTION

	if (szNotice != null_ptr)
	{
		BroadcastNoticeMsgPtr msgPtr = POOLDEF_NEW(BroadcastNoticeMsg);
		AssertEx(msgPtr, "");
		msgPtr->m_strChatInfo = szNotice;
		SendMessage2Scene(sceneid,msgPtr);
	}

	__LEAVE_FUNCTION
}


bool SceneInterface::IsNameScreening(const char* szName,bool bScreeningSpecialSign)
{
	__ENTER_FUNCTION
	if (szName == null_ptr)
	{
		return false;
	}
	if (bScreeningSpecialSign && IsNameContainSpecialSign(szName))
	{
		return true;
	}
	if (StrSafeCheck(szName, static_cast<uint32>(strlen(szName))) == false)
	{
		return true;
	}
	for (int i = 0; i < GetTable_NameFilterCount(); i++)
	{
		const Table_NameFilter* pNameFilter = GetTable_NameFilterByIndex(i);
		if (pNameFilter != null_ptr)
		{
			if (pNameFilter->GetName() != null_ptr)
			{
				const char* str = strstr(szName,pNameFilter->GetName());
				if (str != null_ptr)
				{
					return true;
				}
			}
		}
	}
	__LEAVE_FUNCTION
	return false;
}
bool SceneInterface::IsNameContainSpecialSign(const char* szName)
{
	__ENTER_FUNCTION

	if (szName == null_ptr)
	{
		return false;
	}

	int nLength = static_cast<int>(strlen(szName));
	if (nLength <= 0 )
	{
		return false;
	}

	for(int i = 0; i<nLength; i++)
	{
		switch(szName[i]) 
		{
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '(':
		case ')':
		case '_':
		case '+':
			{
				return true;
				break;
			}
		}
	}

	return false;
	__LEAVE_FUNCTION
	return false;
}
void SceneInterface::BroadCastSampleSystemChat2Scene(const char* strNotice)
{
	__ENTER_FUNCTION

	Packets::GC_CHAT_PAK pak;
	pak.m_PacketData.set_chattype(GC_CHAT::CHAT_TYPE_SYSTEM);
	pak.m_PacketData.set_chatinfo(strNotice);
	BroadCastChatMsg2Scene(pak.m_PacketData);

	__LEAVE_FUNCTION
}


void SceneInterface::KickPlayerByGuid(const int64 &rGuid, int nReason)
{
	__ENTER_FUNCTION

	if (rGuid != invalid_guid64)
	{
		KickPlayerByGuidMsgPtr MsgPtr = POOLDEF_NEW(KickPlayerByGuidMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_nReason = nReason;
		SendMessage2User(rGuid, MsgPtr);
	}

	__LEAVE_FUNCTION
}



