//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_REMOVEEFFECT_PAK_H_
 #define _GC_REMOVEEFFECT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_REMOVEEFFECT_PAK:public Packet
 {
 public:
 GC_REMOVEEFFECT_PAK():Packet(m_PacketData){}
 virtual ~GC_REMOVEEFFECT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_REMOVEEFFECT_PAK;}
 public:
 ::GC_REMOVEEFFECT m_PacketData;
 };

 class GC_REMOVEEFFECT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_REMOVEEFFECT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_REMOVEEFFECT_PAK ; }
 };

 class GC_REMOVEEFFECT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_REMOVEEFFECT_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
