/********************************************************************************
 *	�ļ�����	GameStruct_TextChat.cpp
 *	ȫ·����	\Common\Team\GameStruct_TextChat.cpp
 *	�����ˣ�	zz
 *	����ʱ�䣺2016-12-10
 *
 *	����˵����������Ϣ����ͷ�ļ� ԭ��������Ϣ ����Ƶ�� ���� ���ӵ�
 *	�޸ļ�¼��
*********************************************************************************/

#include "GameStruct_TextChat.h"
#include "Packet/Packet/CG_CHAT_PAK.h"

TextChat::TextChat()
{
	CleanUp();
}

TextChat::~TextChat()
{
}

void TextChat::CopyFrom(const TextChat& rhs)
{
	__ENTER_FUNCTION

	m_Channel = rhs.m_Channel;
	m_ChatInfo = rhs.m_ChatInfo;
	m_ReceiverGuid = rhs.m_ReceiverGuid;
	m_ReceiverName = rhs.m_ReceiverName;

	__LEAVE_FUNCTION
}

void TextChat::CleanUp()
{
	__ENTER_FUNCTION

	m_Channel = invalid_id;
	m_ChatInfo = "";
	m_ReceiverGuid = invalid_guid64;
	m_ReceiverName = "";
	

	__LEAVE_FUNCTION
}

bool TextChat::WriteFromCGCHAT(CG_CHAT &rPacket)
{
	__ENTER_FUNCTION

	if (rPacket.chatinfo().size() > CHAT_SIZE_MAX)
	{
		return false;
	}

	m_Channel = rPacket.chattype();
	m_ChatInfo = rPacket.chatinfo().c_str();

	if (rPacket.has_receiverguid())
	{
		m_ReceiverGuid = rPacket.receiverguid();
	}
	if (rPacket.has_receivername())
	{
		m_ReceiverName = rPacket.receivername().c_str();
	}

	return true;

	__LEAVE_FUNCTION
	return false;
}
