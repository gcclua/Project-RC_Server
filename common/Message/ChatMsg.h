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
	int m_ChannelType;						// 频道
	int64 m_SenderGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// 发送者姓名
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// 聊天信息
	int m_SenderVIPLevel;								// 发送者VIP等级
	int m_SenderLevel;									// 发送者等级
MESSAGE_DEF_END(BroadcastChatMsg)

MESSAGE_DEF_BEGIN(SendTellChatMsg)
	int64	m_SenderGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// 发送者姓名
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// 聊天信息
	int m_SenderVIPLevel;								// 发送者VIP等级
	int m_SenderLevel;									// 发送者等级
	int m_ReceiverLevel;									// 接收者等级
MESSAGE_DEF_END(SendTellChatMsg)

MESSAGE_DEF_BEGIN(SendTellChatSelfMsg)
	int64	m_SenderGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// 发送者姓名
	int64	m_ReceiverGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_ReceiverName;		// 发送者姓名
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// 聊天信息
	int m_SenderLevel;											// 发送等级
	int m_ReceiverLevel;											// 接收者等级
MESSAGE_DEF_END(SendTellChatSelfMsg)

MESSAGE_DEF_BEGIN(SendFriendChatMsg)
	int64	m_SenderGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// 发送者姓名
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// 聊天信息
	int m_SenderLevel;									// 发送者等级
MESSAGE_DEF_END(SendFriendChatMsg)

MESSAGE_DEF_BEGIN(SendFriendChatSelfMsg)
	int64	m_SenderGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_SenderName;		// 发送者姓名
	int64	m_ReceiverGuid;						// 发送者GUID
	FLString<MAX_NAME_SIZE> m_ReceiverName;		// 发送者姓名
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// 聊天信息
	int m_SenderLevel;											// 发送者等级
	int m_ReceiverLevel;											// 接收者等级
MESSAGE_DEF_END(SendFriendChatSelfMsg)

//广播消息
MESSAGE_DEF_BEGIN(BroadcastNoticeMsg)
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;		// 醒目信息
MESSAGE_DEF_END(BroadcastNoticeMsg)

//广播消息
MESSAGE_DEF_BEGIN(BroadcastRollNoticeMsg)
	FLString<CHAT_SIZE_MAX>	m_strRollNotice;		// 滚动信息
	FLString<CHANNELID_LENGTH_MAX>	m_strChannelID;			// 渠道号
MESSAGE_DEF_END(BroadcastRollNoticeMsg)

MESSAGE_DEF_BEGIN(BroadcastLoudSpeakerMsg)
	LoudSpeaker_T m_LoudSpeakerInfo;
MESSAGE_DEF_END(BroadcastLoudSpeakerMsg)

#endif	//_CHATMSG_H_
