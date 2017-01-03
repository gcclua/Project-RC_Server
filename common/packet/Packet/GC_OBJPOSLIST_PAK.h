//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_OBJPOSLIST_PAK_H_
 #define _GC_OBJPOSLIST_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_OBJPOSLIST_PAK:public Packet
 {
 public:
 GC_OBJPOSLIST_PAK():Packet(m_PacketData){}
 virtual ~GC_OBJPOSLIST_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_OBJPOSLIST_PAK;}
 public:
 ::GC_OBJPOSLIST m_PacketData;
 };

 class GC_OBJPOSLIST_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_OBJPOSLIST_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_OBJPOSLIST_PAK ; }
 };

 class GC_OBJPOSLIST_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_OBJPOSLIST_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
