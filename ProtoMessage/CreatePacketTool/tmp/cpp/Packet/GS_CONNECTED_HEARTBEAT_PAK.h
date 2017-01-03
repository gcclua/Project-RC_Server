//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GS_CONNECTED_HEARTBEAT_PAK_H_
 #define _GS_CONNECTED_HEARTBEAT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GS_CONNECTED_HEARTBEAT_PAK:public Packet
 {
 public:
 GS_CONNECTED_HEARTBEAT_PAK():Packet(m_PacketData){}
 virtual ~GS_CONNECTED_HEARTBEAT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GS_CONNECTED_HEARTBEAT_PAK;}
 public:
 ::GS_CONNECTED_HEARTBEAT m_PacketData;
 };

 class GS_CONNECTED_HEARTBEAT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GS_CONNECTED_HEARTBEAT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GS_CONNECTED_HEARTBEAT_PAK ; }
 };

 class GS_CONNECTED_HEARTBEAT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GS_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::GS_CONNECTED_HEARTBEAT_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
