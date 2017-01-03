//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_FORCE_SETPOS_PAK_H_
 #define _GC_FORCE_SETPOS_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_FORCE_SETPOS_PAK:public Packet
 {
 public:
 GC_FORCE_SETPOS_PAK():Packet(m_PacketData){}
 virtual ~GC_FORCE_SETPOS_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_FORCE_SETPOS_PAK;}
 public:
 ::GC_FORCE_SETPOS m_PacketData;
 };

 class GC_FORCE_SETPOS_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_FORCE_SETPOS_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_FORCE_SETPOS_PAK ; }
 };

 class GC_FORCE_SETPOS_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_FORCE_SETPOS_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
