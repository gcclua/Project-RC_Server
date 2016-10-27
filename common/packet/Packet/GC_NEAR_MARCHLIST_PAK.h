//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_NEAR_MARCHLIST_PAK_H_
 #define _GC_NEAR_MARCHLIST_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_NEAR_MARCHLIST_PAK:public Packet
 {
 public:
 GC_NEAR_MARCHLIST_PAK():Packet(m_PacketData){}
 virtual ~GC_NEAR_MARCHLIST_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_NEAR_MARCHLIST_PAK;}
 public:
 ::GC_NEAR_MARCHLIST m_PacketData;
 };

 class GC_NEAR_MARCHLIST_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_NEAR_MARCHLIST_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_NEAR_MARCHLIST_PAK ; }
 };

 class GC_NEAR_MARCHLIST_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_NEAR_MARCHLIST_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::GC_NEAR_MARCHLIST_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
