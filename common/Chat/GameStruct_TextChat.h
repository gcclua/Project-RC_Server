/********************************************************************************
 *	文件名：	GameStruct_TextChat.h
 *	全路径：	\Common\Team\GameStruct_TextChat.h
 *	创建人：	zz
 *	创建时间：2014-12-11
 *
 *	功能说明：聊天信息定义头文件 原生聊天信息 包含频道 文字 链接等
 *	修改记录：
*********************************************************************************/

#ifndef _GAMESTRUCT_TEXTCHAT_H_
#define _GAMESTRUCT_TEXTCHAT_H_

#include "Base.h"
#include "Chat/GameDefine_Chat.h"
#include "Scene/GameDefine_Scene.h"

class CG_CHAT;

class TextChat
{
public:
	TextChat();
	~TextChat();

public:
	void CopyFrom(const TextChat& rhs);
	void CleanUp();
	bool WriteFromCGCHAT(CG_CHAT &rPacket);

public:
	int GetChannel() const { return m_Channel; }
	void SetChannel(int val) { m_Channel = val; }

	FLString<CHAT_SIZE_MAX> GetChatInfo() const { return m_ChatInfo; }
	void SetChatInfo(FLString<CHAT_SIZE_MAX> val) { m_ChatInfo = val; }

	int64 GetReceiverGuid() const { return m_ReceiverGuid; }
	void SetReceiverGuid(int64 val) { m_ReceiverGuid = val; }
	bool IsHaveReceiverGuid() const { return m_ReceiverGuid != invalid_guid64; }

	CHARNAME GetReceiverName() const { return m_ReceiverName; }
	void SetReceiverName(CHARNAME val) { m_ReceiverName = val; }
	bool IsHaveReceiverName() const { return m_ReceiverName != ""; }

	int GetLoudSpeakerNum() const { return m_LoudSpeakerNum; }
	void SetLoudSpeakerNum(int val) { m_LoudSpeakerNum = val; }
	bool IsHaveLoudSpeakerNum() const { return m_LoudSpeakerNum != invalid_id; }


private:
	int m_Channel;
	FLString<CHAT_SIZE_MAX> m_ChatInfo;
	int64 m_ReceiverGuid;
	CHARNAME m_ReceiverName;
	int m_LoudSpeakerNum;
};

#endif