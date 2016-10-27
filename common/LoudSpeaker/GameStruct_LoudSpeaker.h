/********************************************************************************
 *	�ļ�����	GameStruct_LoudSpeaker.h
 *	ȫ·����	\Common\Team\GameStruct_LoudSpeaker.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2014-04-10
 *
 *	����˵����С������ؽṹ�嶨��ͷ�ļ�
 *	�޸ļ�¼��
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
	int64	m_SenderGuid;									// ������GUID
	FLString<MAX_NAME_SIZE> m_SenderName;					// ����������
	FLString<CHAT_SIZE_MAX>	m_strChatInfo;					// ������Ϣ

	int m_SenderLevel;									// �����ߵȼ�
};

#endif