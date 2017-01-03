//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_BATTLEINFOR_PAK_H_
 #define _GC_BATTLEINFOR_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_BATTLEINFOR_PAK:public Packet
 {
 public:
 GC_BATTLEINFOR_PAK():Packet(m_PacketData){}
 virtual ~GC_BATTLEINFOR_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_BATTLEINFOR_PAK;}
 public:
 ::GC_BATTLEINFOR m_PacketData;
 };

 class GC_BATTLEINFOR_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_BATTLEINFOR_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_BATTLEINFOR_PAK ; }
 };

 class GC_BATTLEINFOR_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_BATTLEINFOR_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
