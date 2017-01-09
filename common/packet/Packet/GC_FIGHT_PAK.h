//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_FIGHT_PAK_H_
 #define _GC_FIGHT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_FIGHT_PAK:public Packet
 {
 public:
 GC_FIGHT_PAK():Packet(m_PacketData){}
 virtual ~GC_FIGHT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_FIGHT_PAK;}
 public:
 ::GC_FIGHT m_PacketData;
 };

 class GC_FIGHT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_FIGHT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_FIGHT_PAK ; }
 };

 class GC_FIGHT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_FIGHT_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
