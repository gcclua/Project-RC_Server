//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_BATTLEEND_PAK_H_
 #define _GC_BATTLEEND_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_BATTLEEND_PAK:public Packet
 {
 public:
 GC_BATTLEEND_PAK():Packet(m_PacketData){}
 virtual ~GC_BATTLEEND_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_BATTLEEND_PAK;}
 public:
 ::GC_BATTLEEND m_PacketData;
 };

 class GC_BATTLEEND_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_BATTLEEND_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_BATTLEEND_PAK ; }
 };

 class GC_BATTLEEND_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_BATTLEEND_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
