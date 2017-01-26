//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_BATTLEPREPARE_PAK_H_
 #define _GC_BATTLEPREPARE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_BATTLEPREPARE_PAK:public Packet
 {
 public:
 GC_BATTLEPREPARE_PAK():Packet(m_PacketData){}
 virtual ~GC_BATTLEPREPARE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_BATTLEPREPARE_PAK;}
 public:
 ::GC_BATTLEPREPARE m_PacketData;
 };

 class GC_BATTLEPREPARE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_BATTLEPREPARE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_BATTLEPREPARE_PAK ; }
 };

 class GC_BATTLEPREPARE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_BATTLEPREPARE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
