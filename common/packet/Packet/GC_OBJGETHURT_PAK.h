//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_OBJGETHURT_PAK_H_
 #define _GC_OBJGETHURT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_OBJGETHURT_PAK:public Packet
 {
 public:
 GC_OBJGETHURT_PAK():Packet(m_PacketData){}
 virtual ~GC_OBJGETHURT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_OBJGETHURT_PAK;}
 public:
 ::GC_OBJGETHURT m_PacketData;
 };

 class GC_OBJGETHURT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_OBJGETHURT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_OBJGETHURT_PAK ; }
 };

 class GC_OBJGETHURT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_OBJGETHURT_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
