#ifndef _SERVERPLAYERDEFINE_H_
#define _SERVERPLAYERDEFINE_H_

#include "Base.h"

class ServerPlayerBaseInfo
{
public:
	ServerPlayerBaseInfo(void)
	{
		CleanUp();
	}
public:
	void CleanUp(void)
	{
		m_nWorldID = invalid_id;
		m_szWorldName.CleanUp();
		m_nWorldType = 0;
		m_nBattleWorldID = invalid_id;
		m_szServerIP.CleanUp();
		m_uServerPort = 0;
		m_uServerPortFC = 0;
	}
public:
	tint32			m_nWorldID;
	FLString<32>	m_szWorldName;
	tint32			m_nWorldType;
	tint32			m_nBattleWorldID;
	FLString<32>	m_szServerIP;
	tuint16			m_uServerPort;
	tuint16			m_uServerPortFC;
};

class ServerPlayerBaseInfoTraits
{
public:
	static void CleanUpElems(ServerPlayerBaseInfo *lpElems, tint32 nSize)
	{
		if (lpElems != null_ptr)
		{
			for (tint32 i = 0; i < nSize; i++)
			{
				lpElems[i].CleanUp();
			}
		}
	}

	static void CleanUpElem(ServerPlayerBaseInfo &rElem)
	{
		rElem.CleanUp();
	}

	static bool ShouldSeal(void)
	{
		return false;
	}
};

typedef FLSeque<ServerPlayerBaseInfo, ServerPlayerBaseInfoTraits, 256> ServerPlayerBaseInfoSeque;

#define HANDLEPACKET_SERVERPLAYER_EMPTY(PACKETCLASS) \
tuint32 HandlePacket(PACKETCLASS &rPacket) \
{ \
	return PACKET_EXE_CONTINUE; \
}

#define SERVERPLAYER_SOCKETINPUT_BUFSIZE		512*1024
#define SERVERPLAYER_SOCKETINPUT_MAXBUFSIZE		2048*1024

#define SERVERPLAYER_SOCKETOUTPUT_BUFSIZE		512*1024
#define SERVERPLAYER_SOCKETOUTPUT_MAXBUFSIZE	2048*1024

#endif
