//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_CONNECTED_HEARTBEAT_PAK_H_
 #define _GC_CONNECTED_HEARTBEAT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_CONNECTED_HEARTBEAT_PAK:public Packet
 {
 public:
 GC_CONNECTED_HEARTBEAT_PAK():Packet(m_PacketData){}
 virtual ~GC_CONNECTED_HEARTBEAT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_CONNECTED_HEARTBEAT_PAK;}
 public:
 ::GC_CONNECTED_HEARTBEAT m_PacketData;
 };

 class GC_CONNECTED_HEARTBEAT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_CONNECTED_HEARTBEAT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_CONNECTED_HEARTBEAT_PAK ; }
 };

 class GC_CONNECTED_HEARTBEAT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
