//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_OBJINFOR_PAK_H_
 #define _GC_OBJINFOR_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_OBJINFOR_PAK:public Packet
 {
 public:
 GC_OBJINFOR_PAK():Packet(m_PacketData){}
 virtual ~GC_OBJINFOR_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_OBJINFOR_PAK;}
 public:
 ::GC_OBJINFOR m_PacketData;
 };

 class GC_OBJINFOR_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_OBJINFOR_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_OBJINFOR_PAK ; }
 };

 class GC_OBJINFOR_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_OBJINFOR_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
