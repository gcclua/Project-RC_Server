#include "Player.h"
#include "Exception.h"
#include "LibNetwork.h"
#include "packet/Packet/GC_CONNECTED_HEARTBEAT_PAK.h"


POOLDEF_IMPL(Player);
using namespace std; 

tint32 Player::m_nIDGenerator = 0;

Player::Player()
	:m_Socket()
	,m_SocketInputStream(&m_Socket)
	,m_SocketOutputStream(&m_Socket)
	,m_UserObj(this)
	,m_LoginObj(*this)
	,m_bKickMe(false)
	,m_nHealthLevel(0)
{
	m_nID=m_nIDGenerator++;
}

Player::~Player(void)
{
	

}


bool Player::ProcessInput( )
{
	__ENTER_PROTECT_EX

		tuint32 ret = m_SocketInputStream.Fill( ) ;
	if( (tint32)ret <= SOCKET_ERROR )
	{
		CacheLog(LOGDEF_INST(Error), "Player(%lld)::ProcessInput, m_SocketInputStream.Fill, %d, %s", 
			GetObjUser().GetGuid(),(tint32)ret, SocketAPI::getsocketerror_ex());
		return false ;
	}

	__CATCH_PROTECT_EX

		return false ;

	__LEAVE_PROTECT_EX

		return true;
}

bool Player::ProcessCommand(void)
{
	__ENTER_PROTECT_EX

		//每帧可以执行的消息数量上限
		for( tint32 i=0;i<12; i++ )
		{
			tchar header[PACKET_HEADER_SIZE]={0};
			if( !m_SocketInputStream.Peek(&header[0], PACKET_HEADER_SIZE) )
			{//数据不能填充消息头
				break ;
			}

			tuint32 packetSize;
			memcpy( &packetSize, &header[0], sizeof(tuint32) ) ;	
			packetSize = ntohl(packetSize);

			PacketID_t packetID;
			memcpy( &packetID, &header[sizeof(tuint32)], sizeof(PacketID_t) );
			packetID = ntohs(packetID);

			if (!((packetID > Packets::PACKET_NONE) && (packetID < Packets::PACKET_MAX)))
			{
				CacheLog(LOGDEF_INST(Player), "player(%d), process packet, packetid(%d) error",
					GetID(), static_cast<tint32>(packetID));
				PrintLastPacketLog("packetid error");
				return false;
			}

			__ENTER_PROTECT_EX

				if( m_SocketInputStream.Length()<packetSize) //加上跳过的preheader
				{//消息没有接收全
					break;
				}

				Packet* pPacket = gPacketFactoryManager.CreatePacket( packetID ) ;
				if( pPacket == null_ptr )
				{
					CacheLog(LOGDEF_INST(Player), "player(%d), process packet, create packet(%d) error",
						GetID(), static_cast<tint32>(packetID));
					PrintLastPacketLog("create packet error");
					return false ;
				}
				Packet &rPacket = *pPacket;

				tuint32 nSizeBefore = m_SocketInputStream.Length();
				bool bRetReadPacket = m_SocketInputStream.ReadPacket( rPacket, packetSize - PACKET_HEADER_SIZE, Player::isCryptoPacket(rPacket.GetPacketID()) ) ;
				if( bRetReadPacket==false )
				{//读取消息内容错误
					CacheLog(LOGDEF_INST(Player), "player(%d), process packet, read packet(%d) error",
						GetID(), static_cast<tint32>(packetID));
					gPacketFactoryManager.RemovePacket( &rPacket ) ;
					PrintLastPacketLog("read packet error");
					return false ;
				}
				tuint32 nSizeAfter = m_SocketInputStream.Length();
				OnReceivePacket(static_cast<tint32>(rPacket.GetPacketID()), static_cast<tint64>(nSizeBefore - nSizeAfter));

				bool bException = false ;

				__ENTER_PROTECT_EX

					tuint32 uret ;
				__ENTER_PROTECT_EX
			
						uret = rPacket.Execute(this);

					__CATCH_PROTECT_EX
						uret = PACKET_EXE_ERROR ;
					__LEAVE_PROTECT_EX

						if (uret != PACKET_EXE_CONTINUE)
						{
							CacheLog(LOGDEF_INST(Player), "player(%d), process packet, execute packet(%d) error(%u)",
								GetID(), static_cast<tint32>(packetID), uret);
							gPacketFactoryManager.RemovePacket( &rPacket ) ;
							PrintLastPacketLog("execute packet error");
							return false ;
						}

						__CATCH_PROTECT_EX

							bException = true;

						__LEAVE_PROTECT_EX

							gPacketFactoryManager.RemovePacket( &rPacket ) ;

						if( bException )
						{
							PrintLastPacketLog("exception");
							return false ;
						}
						__CATCH_PROTECT_EX

							PrintLastPacketLog("exception");
						return false;

						__LEAVE_PROTECT_EX
		}

		__CATCH_PROTECT_EX

			PrintLastPacketLog("exception");
		return false;

		__LEAVE_PROTECT_EX

			return true ;
}

bool Player::ProcessOutput(void)
{
	__ENTER_PROTECT_EX


		tuint32 size = m_SocketOutputStream.Length() ;
	if( size==0 )
	{
		return true ;
	}

	tuint32 ret = m_SocketOutputStream.Flush( ) ;
	if( (tint32)ret <= SOCKET_ERROR )
	{
		CacheLog(LOGDEF_INST(Error), "Player(%lld)::ProcessOutput, m_SocketOutputStream.Flush, %d, %s",
			GetObjUser().GetGuid(),(tint32)ret, SocketAPI::getsocketerror_ex());
		return false ;
	}

	__CATCH_PROTECT_EX

		return false;

	__LEAVE_PROTECT_EX

		return true;
}

bool Player::ProcessConnection(time_t nAnsiTime)
{
	Packets::GC_CONNECTED_HEARTBEAT_PAK pak;
	pak.m_PacketData.set_serveransitime(static_cast<tint32>(nAnsiTime));
	SendPacket(pak);
	return true;
}

void Player::KickMe(int nReason)
{
	__ENTER_FUNCTION
		m_bKickMe = true;
	   CacheLog(LOGDEF_INST(Player), "kick player reason(%d)", nReason);
	__LEAVE_FUNCTION
}

bool    Player::Tick_InGame(const TimeInfo &rTimeInfo)
{
	if (m_bKickMe)
	{
		return false;
	}

	return true;
}

bool Player::Tick_InLogin(const TimeInfo& rTimeInfo)
{
	if (m_bKickMe)
	{
		return false;
	}

	return true;
}

void  Player::SendPacket(const Packet &rPacket)
{
	__ENTER_FUNCTION
	uint32 nSizeBefore = m_SocketOutputStream.Length();
	bool ret = m_SocketOutputStream.WritePacket(rPacket,Player::isCryptoPacket(rPacket.GetPacketID()));
	if (!ret)
	{
		char szKey[128] = {0};
		tsnprintf(szKey,sizeof(szKey)-1,"%d",rPacket.GetPacketID());
		szKey[sizeof(szKey)-1] = '0';
		VerifyEx(false,szKey);
	}
	uint32 nSizeAfter = m_SocketOutputStream.Length();
	OnSendPacket(static_cast<int>(rPacket.GetPacketID()),static_cast<int64>(nSizeAfter - nSizeBefore));
	__LEAVE_FUNCTION

}

void Player::Disconnect(void)
{
	__ENTER_FUNCTION
		m_Socket.close();
	__LEAVE_FUNCTION
}

tuint32 Player::HandlePacket(::CG_CONNECTED_HEARTBEAT &rPacket)
{
	if (rPacket.isresponse() != 0)
	{
		m_nHealthLevel++;
	}
	return PACKET_EXE_CONTINUE;
}

bool Player::isCryptoPacket(PacketID_t nPacketID)
{
	return (nPacketID != Packets::PACKET_CG_LOGIN_PAK &&
		nPacketID != Packets::PACKET_GC_LOGIN_RET_PAK &&
		nPacketID != Packets::PACKET_CG_CONNECTED_HEARTBEAT_PAK &&
		nPacketID != Packets::PACKET_GC_CONNECTED_HEARTBEAT_PAK);
}

void Player::OnReceivePacket(int nPacketId,int64 nPacketSize)
{
	__ENTER_FUNCTION
		AssertEx(nPacketId>=0 && nPacketId< Packets::PACKET_MAX,"");
		m_PacketStat[nPacketId].m_nReceiveCount++;
		m_PacketStat[nPacketId].m_nReceiveSize += nPacketSize;
		PushRecPacketId(nPacketId);
	__LEAVE_FUNCTION
}
void Player::OnSendPacket(int nPacketId,int64 nPacketSize)
{
	__ENTER_FUNCTION
		AssertEx(nPacketId>=0 && nPacketId< Packets::PACKET_MAX,"");
	m_PacketStat[nPacketId].m_nSendCount++;
	m_PacketStat[nPacketId].m_nSendSize += nPacketSize;
	PushSendPacketId(nPacketId);
	__LEAVE_FUNCTION
}

void Player::PushRecPacketId(int nPacketId)
{
	__ENTER_FUNCTION
		for(int i=MAX_LASTPACKETSIZE-1;i>=1;i--)
		{
			m_lastRecPacketId[i] = m_lastRecPacketId[i-1];
		}
		m_lastRecPacketId[0] = nPacketId;
	__LEAVE_FUNCTION
}
void Player::PushSendPacketId(int nPacketId)
{
	__ENTER_FUNCTION
		for(int i=MAX_LASTPACKETSIZE-1;i>=1;i--)
		{
			m_lastSendPacketId[i] = m_lastSendPacketId[i-1];
		}
		m_lastSendPacketId[0] = nPacketId;
	__LEAVE_FUNCTION
}

void Player::PrintLastPacketLog(const tchar* szPrintType)
{
	__ENTER_FUNCTION

	FLString<512> szRecPacketInfo;
	FLString<512> szSndPacketInfo;
	tchar szPacket[128];
	for (tint32 i=0; i<MAX_LASTPACKETSIZE; i++)
	{
		tsnprintfex(szPacket, sizeof(szPacket), "[%d]recid=%d [%d]recname=%s ", 
			i, 
			m_lastRecPacketId[i], 
			i, 
			Packets::GetPacketNameByID(m_lastRecPacketId[i]));
		szRecPacketInfo += szPacket;

		tsnprintfex(szPacket, sizeof(szPacket), "[%d]sndid=%d [%d]sndname=%s ", 
			i, 
			m_lastSendPacketId[i], 
			i, 
			Packets::GetPacketNameByID(m_lastSendPacketId[i]));
		szSndPacketInfo += szPacket;
	}

	CacheLog(LOGDEF_INST(Player), "last packet type=%s acc=%s name=%s guid=%08X %s %s",
		szPrintType,
		GetObjLogin().GetAccount().GetCText(),
		GetObjUser().GetName().GetCText(),
		GetObjUser().GetGuid(),
		szRecPacketInfo.GetCText(),
		szSndPacketInfo.GetCText());

	__LEAVE_FUNCTION
}