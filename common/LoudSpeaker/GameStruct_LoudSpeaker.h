/********************************************************************************
 *	文件名：	GameStruct_LoudSpeaker.h
 *	全路径：	\Common\Team\GameStruct_LoudSpeaker.h
 *	创建人：	zz
 *	创建时间：2014-04-10
 *
 *	功能说明：小喇叭相关结构体定义头文件
 *	修改记录：
*********************************************************************************/

#ifndef _GAMESTRUCT_LOUDSPEAKER_H_
#define _GAMESTRUCT_LOUDSPEAKER_H_

#include "Base.h"
#include "Chat/GameDefine_Chat.h"
#include "Scene/GameDefine_Scene.h"


class LoudSpeaker_T
{
public:
	LoudSpeaker_T();
	~LoudSpeaker_T();

public:
	int64 GetSenderGUID() {return m_SenderGuid;}
	void SetSenderGUID(int64 senderGUID) {m_SenderGuid = senderGUID;}

	FLString<MAX_NAME_SIZE> GetSenderName() {return m_SenderName;}
	void SetSenderName(FLString<MAX_NAME_SIZE> senderName) {m_SenderName = senderName;}

	FLString<CHAT_SIZE_MAX> GetStrChatInfo() {return m_strChatInfo;}
	void SetStrChatInfo(const char* strChatInfo) {m_strChatInfo = strChatInfo;}

	int GetLinkType(int nIndex);
	void SetLinkType(int nIndex, int nLinkType);

	

	int GetSenderLevel() {return m_SenderLevel;}
	void SetSenderLevel(int nSenderLevel) {m_SenderLevel = nSenderLevel;}

private:
	int64	m_SenderGuid;									// 发送者GUID
	FLString<MAX_NAME_SIZE> m_SenderName;					// 发送者名字
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;					// 聊天信息

	int m_SenderLevel;									// 发送者等级
};

#endif