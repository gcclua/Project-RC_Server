//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _SG_CONNECTED_HEARTBEAT_PAK_H_
 #define _SG_CONNECTED_HEARTBEAT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class SG_CONNECTED_HEARTBEAT_PAK:public Packet
 {
 public:
 SG_CONNECTED_HEARTBEAT_PAK():Packet(m_PacketData){}
 virtual ~SG_CONNECTED_HEARTBEAT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_SG_CONNECTED_HEARTBEAT_PAK;}
 public:
 ::SG_CONNECTED_HEARTBEAT m_PacketData;
 };

 class SG_CONNECTED_HEARTBEAT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::SG_CONNECTED_HEARTBEAT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_SG_CONNECTED_HEARTBEAT_PAK ; }
 };

 class SG_CONNECTED_HEARTBEAT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::SG_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::SG_CONNECTED_HEARTBEAT_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
