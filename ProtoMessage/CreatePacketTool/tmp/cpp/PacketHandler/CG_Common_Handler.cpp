//This code create by CodeEngine

#include "Packet/Packet/CG_LOGIN_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_LOGIN_PAKHandler::Execute( Packets::CG_LOGIN_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_LOGIN_PAKHandler::Execute( Packets::CG_LOGIN_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/CG_CONNECTED_HEARTBEAT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_CONNECTED_HEARTBEAT_PAKHandler::Execute( Packets::CG_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_CONNECTED_HEARTBEAT_PAKHandler::Execute( Packets::CG_CONNECTED_HEARTBEAT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/CG_REQ_NEAR_LIST_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_REQ_NEAR_LIST_PAKHandler::Execute( Packets::CG_REQ_NEAR_LIST_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_REQ_NEAR_LIST_PAKHandler::Execute( Packets::CG_REQ_NEAR_LIST_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/CG_CHAT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_CHAT_PAKHandler::Execute( Packets::CG_CHAT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_CHAT_PAKHandler::Execute( Packets::CG_CHAT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/CG_MOVE_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_MOVE_PAKHandler::Execute( Packets::CG_MOVE_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_MOVE_PAKHandler::Execute( Packets::CG_MOVE_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/CG_FIGHT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_FIGHT_PAKHandler::Execute( Packets::CG_FIGHT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_FIGHT_PAKHandler::Execute( Packets::CG_FIGHT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/CG_LEAVE_COPYSCENE_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::CG_LEAVE_COPYSCENE_PAKHandler::Execute( Packets::CG_LEAVE_COPYSCENE_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::CG_LEAVE_COPYSCENE_PAKHandler::Execute( Packets::CG_LEAVE_COPYSCENE_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
