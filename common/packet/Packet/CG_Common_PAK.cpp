//This code create by CodeEngine Author:Wendy ,don't modify
#include "CG_LOGIN_PAK.h"
tuint32 Packets::CG_LOGIN_PAK::Execute( Player* pPlayer )
 {
 __ENTER_FUNCTION
 return CG_LOGIN_PAKHandler::Execute(this,pPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
 tuint32 Packets::CG_LOGIN_PAK::Execute( ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 return CG_LOGIN_PAKHandler::Execute(this,pServerPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
//This code create by CodeEngine Author:Wendy ,don't modify
#include "CG_CONNECTED_HEARTBEAT_PAK.h"
tuint32 Packets::CG_CONNECTED_HEARTBEAT_PAK::Execute( Player* pPlayer )
 {
 __ENTER_FUNCTION
 return CG_CONNECTED_HEARTBEAT_PAKHandler::Execute(this,pPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
 tuint32 Packets::CG_CONNECTED_HEARTBEAT_PAK::Execute( ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 return CG_CONNECTED_HEARTBEAT_PAKHandler::Execute(this,pServerPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
//This code create by CodeEngine Author:Wendy ,don't modify
#include "CG_REQ_NEAR_LIST_PAK.h"
tuint32 Packets::CG_REQ_NEAR_LIST_PAK::Execute( Player* pPlayer )
 {
 __ENTER_FUNCTION
 return CG_REQ_NEAR_LIST_PAKHandler::Execute(this,pPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
 tuint32 Packets::CG_REQ_NEAR_LIST_PAK::Execute( ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 return CG_REQ_NEAR_LIST_PAKHandler::Execute(this,pServerPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
//This code create by CodeEngine Author:Wendy ,don't modify
#include "CG_CHAT_PAK.h"
tuint32 Packets::CG_CHAT_PAK::Execute( Player* pPlayer )
 {
 __ENTER_FUNCTION
 return CG_CHAT_PAKHandler::Execute(this,pPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
 tuint32 Packets::CG_CHAT_PAK::Execute( ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 return CG_CHAT_PAKHandler::Execute(this,pServerPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
//This code create by CodeEngine Author:Wendy ,don't modify
#include "CG_MOVE_PAK.h"
tuint32 Packets::CG_MOVE_PAK::Execute( Player* pPlayer )
 {
 __ENTER_FUNCTION
 return CG_MOVE_PAKHandler::Execute(this,pPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
 tuint32 Packets::CG_MOVE_PAK::Execute( ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 return CG_MOVE_PAKHandler::Execute(this,pServerPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
