//This code create by CodeEngine Author:Wendy ,don't modify
#include "SG_CONNECTED_HEARTBEAT_PAK.h"
tuint32 Packets::SG_CONNECTED_HEARTBEAT_PAK::Execute( Player* pPlayer )
 {
 __ENTER_FUNCTION
 return SG_CONNECTED_HEARTBEAT_PAKHandler::Execute(this,pPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
 tuint32 Packets::SG_CONNECTED_HEARTBEAT_PAK::Execute( ServerPlayer* pServerPlayer )
 {
 __ENTER_FUNCTION
 return SG_CONNECTED_HEARTBEAT_PAKHandler::Execute(this,pServerPlayer);
 __LEAVE_FUNCTION
 return PACKET_EXE_ERROR;
 }
