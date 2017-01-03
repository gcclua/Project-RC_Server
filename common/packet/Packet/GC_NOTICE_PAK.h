//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_NOTICE_PAK_H_
 #define _GC_NOTICE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_NOTICE_PAK:public Packet
 {
 public:
 GC_NOTICE_PAK():Packet(m_PacketData){}
 virtual ~GC_NOTICE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_NOTICE_PAK;}
 public:
 ::GC_NOTICE m_PacketData;
 };

 class GC_NOTICE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_NOTICE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_NOTICE_PAK ; }
 };

 class GC_NOTICE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_NOTICE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
