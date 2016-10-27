#include "ServerPlayer.h"
#include "Packet/Packet/PacketDefine.h"
#include "Service/MessageOp.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "packet/Packet/SG_CONNECTED_HEARTBEAT_PAK.h"
#include "packet/Packet/GS_CONNECTED_HEARTBEAT_PAK.h"

POOLDEF_IMPL(ServerPlayer);

ServerPlayer::ServerPlayer(void)
	: m_BaseInfo()
	, m_Socket()
	, m_SocketInputStream(&m_Socket, SERVERPLAYER_SOCKETINPUT_BUFSIZE, SERVERPLAYER_SOCKETINPUT_MAXBUFSIZE)
	, m_SocketOutputStream(&m_Socket, SERVERPLAYER_SOCKETOUTPUT_BUFSIZE, SERVERPLAYER_SOCKETOUTPUT_MAXBUFSIZE)
	, m_nHealthLevel(0)
{

}

ServerPlayer::~ServerPlayer(void)
{

}

bool ServerPlayer::ProcessInput(void)
{
	__ENTER_PROTECT_EX

	tuint32 ret = m_SocketInputStream.Fill();
	if(static_cast<tint32>(ret) <= SOCKET_ERROR)
	{
		//CacheLog(LOGDEF_INST(ParallelWorld),
			//"ServerPlayer(%d)::ProcessInput, m_SocketInputStream.Fill, %s, %d, %d, %s:%d:%d",
			//m_BaseInfo.m_nWorldID,
			//m_BaseInfo.m_szWorldName.GetCText(),
			//m_BaseInfo.m_nWorldType,
			//m_BaseInfo.m_nBattleWorldID,
			//m_BaseInfo.m_szServerIP.GetCText(),
			//static_cast<tint32>(m_BaseInfo.m_uServerPort),
			//static_cast<tint32>(m_BaseInfo.m_uServerPortFC));
		return false;
	}

	__CATCH_PROTECT_EX

	return false;

	__LEAVE_PROTECT_EX

	return true;
}

bool ServerPlayer::ProcessOutput(void)
{
	__ENTER_PROTECT_EX

	tuint32 size = m_SocketOutputStream.Length();
	if(size == 0)
	{
		return true;
	}

	tuint32 ret = m_SocketOutputStream.Flush();
	if(static_cast<tint32>(ret) <= SOCKET_ERROR)
	{
		//CacheLog(LOGDEF_INST(ParallelWorld),
			//"ServerPlayer(%d)::ProcessOutput, m_SocketOutputStream.Flush, %s, %d, %d, %s:%d:%d",
			//m_BaseInfo.m_nWorldID,
			//m_BaseInfo.m_szWorldName.GetCText(),
			//m_BaseInfo.m_nWorldType,
			//m_BaseInfo.m_nBattleWorldID,
			//m_BaseInfo.m_szServerIP.GetCText(),
			//static_cast<tint32>(m_BaseInfo.m_uServerPort),
			//static_cast<tint32>(m_BaseInfo.m_uServerPortFC));
		return false;
	}

	__CATCH_PROTECT_EX

	return false;

	__LEAVE_PROTECT_EX

	return true;
}

bool ServerPlayer::ProcessCommand(void)
{
	__ENTER_PROTECT_EX

	//每帧可以执行的消息数量上限
	for(tint32 i = 0; i < 12; i++)
	{
		tchar header[PACKET_HEADER_SIZE] = {0};
		if(!m_SocketInputStream.Peek(&header[0], PACKET_HEADER_SIZE))
		{
			//数据不能填充消息头
			break;
		}

		tuint32 packetSize;
		memcpy(&packetSize, &header[0], sizeof(tuint32));
		packetSize = ntohl(packetSize);

		PacketID_t packetID;
		memcpy(&packetID, &header[sizeof(tuint32)], sizeof(PacketID_t));
		packetID = ntohs(packetID);

		if (!((packetID > Packets::PACKET_NONE) && (packetID < Packets::PACKET_MAX)))
		{
			//CacheLog(LOGDEF_INST(ParallelWorld),
				//"serverplayer(%d), process packet, packetid(%d) error",
				//m_BaseInfo.m_nWorldID,
				//static_cast<tint32>(packetID));
			return false;
		}

		__ENTER_PROTECT_EX

			if(m_SocketInputStream.Length() < packetSize)
			{
				break;
			}

			Packet *pPacket = gPacketFactoryManager.CreatePacket(packetID);
			if(pPacket == null_ptr)
			{
				//CacheLog(LOGDEF_INST(ParallelWorld),
					//"serverplayer(%d), process packet, create packet(%d) error",
					//m_BaseInfo.m_nWorldID,
					//static_cast<tint32>(packetID));
				return false;
			}
			Packet &rPacket = *pPacket;

			bool bRetReadPacket = m_SocketInputStream.ReadPacket(rPacket, packetSize - PACKET_HEADER_SIZE, false);
			if(bRetReadPacket == false)
			{
				//CacheLog(LOGDEF_INST(ParallelWorld),
					//"serverplayer(%d), process packet, read packet(%d) error",
					//m_BaseInfo.m_nWorldID,
					//static_cast<tint32>(packetID));
				gPacketFactoryManager.RemovePacket(&rPacket);
				return false;
			}

			bool bException = false;

			__ENTER_PROTECT_EX

				tuint32 uret;
				__ENTER_PROTECT_EX
				uret = rPacket.Execute(this);
				__CATCH_PROTECT_EX
				uret = PACKET_EXE_ERROR;
				__LEAVE_PROTECT_EX
				if (uret != PACKET_EXE_CONTINUE)
				{
					//CacheLog(LOGDEF_INST(ParallelWorld),
						//"serverplayer(%d), process packet, execute packet(%d) error(%u)",
						//m_BaseInfo.m_nWorldID,
						//static_cast<tint32>(packetID),
						//uret);
					gPacketFactoryManager.RemovePacket(&rPacket);
					return false;
				}

			__CATCH_PROTECT_EX

			bException = true;

			__LEAVE_PROTECT_EX

			gPacketFactoryManager.RemovePacket(&rPacket);

			if(bException)
			{
				return false;
			}

		__CATCH_PROTECT_EX

		return false;

		__LEAVE_PROTECT_EX
	}

	__CATCH_PROTECT_EX

	return false;

	__LEAVE_PROTECT_EX

	return true;
}

bool ServerPlayer::ProcessConnection(time_t nAnsiTime)
{
	__ENTER_FUNCTION

	Packets::SG_CONNECTED_HEARTBEAT_PAK pak;
	//pak.m_PacketData.set_senderworldid(WorldID());
	pak.m_PacketData.set_receiverworldid(m_BaseInfo.m_nWorldID);
	SendPacket(pak);

	m_nHealthLevel--;

#if defined(__WINDOWS__)
	return (abs(m_nHealthLevel) <= 300);
#elif defined(__LINUX__)
	return (abs(m_nHealthLevel) <= 30);
#endif

	__LEAVE_FUNCTION
	return false;
}

void ServerPlayer::SendPacket(const Packet &rPacket)
{
	__ENTER_FUNCTION

	bool ret = m_SocketOutputStream.WritePacket(rPacket, false);
	if (!ret)
	{
		FLString<128> szPacketID(rPacket.GetPacketID());
		VerifyEx(false, szPacketID.GetCText());
	}

	__LEAVE_FUNCTION
}

tuint32 ServerPlayer::HandlePacket(::GS_CONNECTED_HEARTBEAT &rPacket)
{
	__ENTER_FUNCTION



	m_nHealthLevel++;

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 ServerPlayer::HandlePacket(::SG_CONNECTED_HEARTBEAT &rPacket)
{
	__ENTER_FUNCTION



	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}



