//This code create by CodeEngine

#include "Packet/Packet/GS_CONNECTED_HEARTBEAT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GS_CONNECTED_HEARTBEAT_PAKHandler::Execute( Packets::GS_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GS_CONNECTED_HEARTBEAT_PAKHandler::Execute( Packets::GS_CONNECTED_HEARTBEAT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
