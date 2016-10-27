//This code create by CodeEngine

#include "Packet/Packet/GC_LOGIN_RET_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_LOGIN_RET_PAKHandler::Execute( Packets::GC_LOGIN_RET_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_LOGIN_RET_PAKHandler::Execute( Packets::GC_LOGIN_RET_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_CONNECTED_HEARTBEAT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_CONNECTED_HEARTBEAT_PAKHandler::Execute( Packets::GC_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_CONNECTED_HEARTBEAT_PAKHandler::Execute( Packets::GC_CONNECTED_HEARTBEAT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_NEAR_MARCHLIST_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_NEAR_MARCHLIST_PAKHandler::Execute( Packets::GC_NEAR_MARCHLIST_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_NEAR_MARCHLIST_PAKHandler::Execute( Packets::GC_NEAR_MARCHLIST_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_CHAT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_CHAT_PAKHandler::Execute( Packets::GC_CHAT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_CHAT_PAKHandler::Execute( Packets::GC_CHAT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_NOTICE_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_NOTICE_PAKHandler::Execute( Packets::GC_NOTICE_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_NOTICE_PAKHandler::Execute( Packets::GC_NOTICE_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_UPDATE_SCENE_INSTACTIVATION_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAKHandler::Execute( Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAKHandler::Execute( Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_MOVE_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_MOVE_PAKHandler::Execute( Packets::GC_MOVE_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_MOVE_PAKHandler::Execute( Packets::GC_MOVE_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_STOP_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_STOP_PAKHandler::Execute( Packets::GC_STOP_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_STOP_PAKHandler::Execute( Packets::GC_STOP_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_TELEMOVE_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_TELEMOVE_PAKHandler::Execute( Packets::GC_TELEMOVE_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_TELEMOVE_PAKHandler::Execute( Packets::GC_TELEMOVE_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_RET_USE_SKILL_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_RET_USE_SKILL_PAKHandler::Execute( Packets::GC_RET_USE_SKILL_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_RET_USE_SKILL_PAKHandler::Execute( Packets::GC_RET_USE_SKILL_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_UPDATE_ANIMATION_STATE_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_UPDATE_ANIMATION_STATE_PAKHandler::Execute( Packets::GC_UPDATE_ANIMATION_STATE_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_UPDATE_ANIMATION_STATE_PAKHandler::Execute( Packets::GC_UPDATE_ANIMATION_STATE_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_DELETE_OBJ_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_DELETE_OBJ_PAKHandler::Execute( Packets::GC_DELETE_OBJ_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_DELETE_OBJ_PAKHandler::Execute( Packets::GC_DELETE_OBJ_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_ATTACKFLY_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_ATTACKFLY_PAKHandler::Execute( Packets::GC_ATTACKFLY_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_ATTACKFLY_PAKHandler::Execute( Packets::GC_ATTACKFLY_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_FORCE_SETPOS_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_FORCE_SETPOS_PAKHandler::Execute( Packets::GC_FORCE_SETPOS_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_FORCE_SETPOS_PAKHandler::Execute( Packets::GC_FORCE_SETPOS_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_UPDATE_NEEDIMPACTINFO_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_UPDATE_NEEDIMPACTINFO_PAKHandler::Execute( Packets::GC_UPDATE_NEEDIMPACTINFO_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_UPDATE_NEEDIMPACTINFO_PAKHandler::Execute( Packets::GC_UPDATE_NEEDIMPACTINFO_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_PLAY_EFFECT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_PLAY_EFFECT_PAKHandler::Execute( Packets::GC_PLAY_EFFECT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_PLAY_EFFECT_PAKHandler::Execute( Packets::GC_PLAY_EFFECT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
//This code create by CodeEngine

#include "Packet/Packet/GC_REMOVEEFFECT_PAK.h"
 #include "Player/Player.h"
 #include "ServerPlayer/ServerPlayer.h"
tuint32 Packets::GC_REMOVEEFFECT_PAKHandler::Execute( Packets::GC_REMOVEEFFECT_PAK* pPacket, Player* pPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pPlayer, "");
 return pPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
 tuint32 Packets::GC_REMOVEEFFECT_PAKHandler::Execute( Packets::GC_REMOVEEFFECT_PAK* pPacket, ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 AssertEx(pPacket, "");
 AssertEx(pServerPlayer, "");
 return pServerPlayer->HandlePacket(pPacket->m_PacketData);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR ; 
 }
