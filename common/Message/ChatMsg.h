#ifndef _CHATMSG_H_
#define _CHATMSG_H_
#include "service/BaseService.h"
#include "service/Invoker.h"
#include "Player/Player.h"
#include "Chat/GameDefine_Chat.h"
#include "scene/GameStruct_Scene.h"
#include "LoudSpeaker/GameStruct_LoudSpeaker.h"
#include "Chat/GameStruct_TextChat.h"
#include "service/Message.h"

MESSAGE_DEF_BEGIN(BroadcastChatMsg)
	int m_ChannelType;						// Ƶ��
	int64 m_SenderGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// ����������
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// ������Ϣ
	int m_SenderVIPLevel;								// ������VIP�ȼ�
	int m_SenderLevel;									// �����ߵȼ�
MESSAGE_DEF_END(BroadcastChatMsg)

MESSAGE_DEF_BEGIN(SendTellChatMsg)
	int64	m_SenderGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// ����������
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// ������Ϣ
	int m_SenderVIPLevel;								// ������VIP�ȼ�
	int m_SenderLevel;									// �����ߵȼ�
	int m_ReceiverLevel;									// �����ߵȼ�
MESSAGE_DEF_END(SendTellChatMsg)

MESSAGE_DEF_BEGIN(SendTellChatSelfMsg)
	int64	m_SenderGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// ����������
	int64	m_ReceiverGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_ReceiverName;		// ����������
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// ������Ϣ
	int m_SenderLevel;											// ���͵ȼ�
	int m_ReceiverLevel;											// �����ߵȼ�
MESSAGE_DEF_END(SendTellChatSelfMsg)

MESSAGE_DEF_BEGIN(SendFriendChatMsg)
	int64	m_SenderGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// ����������
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// ������Ϣ
	int m_SenderLevel;									// �����ߵȼ�
MESSAGE_DEF_END(SendFriendChatMsg)

MESSAGE_DEF_BEGIN(SendFriendChatSelfMsg)
	int64	m_SenderGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// ����������
	int64	m_ReceiverGuid;						// ������GUID
	FLString<MAX_NAME_SIZE> m_ReceiverName;		// ����������
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// ������Ϣ
	int m_SenderLevel;											// �����ߵȼ�
	int m_ReceiverLevel;											// �����ߵȼ�
MESSAGE_DEF_END(SendFriendChatSelfMsg)

//�㲥��Ϣ
MESSAGE_DEF_BEGIN(BroadcastNoticeMsg)
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// ��Ŀ��Ϣ
MESSAGE_DEF_END(BroadcastNoticeMsg)

//�㲥��Ϣ
MESSAGE_DEF_BEGIN(BroadcastRollNoticeMsg)
	FLString<CHAT_SIZE_MAX>	m_strRollNotice;		// ������Ϣ
	FLString<CHANNELID_LENGTH_MAX>	m_strChannelID;			// ������
MESSAGE_DEF_END(BroadcastRollNoticeMsg)

MESSAGE_DEF_BEGIN(BroadcastLoudSpeakerMsg)
	LoudSpeaker_T m_LoudSpeakerInfo;
MESSAGE_DEF_END(BroadcastLoudSpeakerMsg)

#endif	//_CHATMSG_H_
