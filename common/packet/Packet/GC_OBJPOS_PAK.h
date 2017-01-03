//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_OBJPOS_PAK_H_
 #define _GC_OBJPOS_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_OBJPOS_PAK:public Packet
 {
 public:
 GC_OBJPOS_PAK():Packet(m_PacketData){}
 virtual ~GC_OBJPOS_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_OBJPOS_PAK;}
 public:
 ::GC_OBJPOS m_PacketData;
 };

 class GC_OBJPOS_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_OBJPOS_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_OBJPOS_PAK ; }
 };

 class GC_OBJPOS_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_OBJPOS_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
