//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_STOP_PAK_H_
 #define _GC_STOP_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_STOP_PAK:public Packet
 {
 public:
 GC_STOP_PAK():Packet(m_PacketData){}
 virtual ~GC_STOP_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_STOP_PAK;}
 public:
 ::GC_STOP m_PacketData;
 };

 class GC_STOP_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_STOP_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_STOP_PAK ; }
 };

 class GC_STOP_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_STOP_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::GC_STOP_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
