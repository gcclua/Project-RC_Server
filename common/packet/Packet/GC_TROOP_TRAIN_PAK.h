//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_TROOP_TRAIN_PAK_H_
 #define _GC_TROOP_TRAIN_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_TROOP_TRAIN_PAK:public Packet
 {
 public:
 GC_TROOP_TRAIN_PAK():Packet(m_PacketData){}
 virtual ~GC_TROOP_TRAIN_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_TROOP_TRAIN_PAK;}
 public:
 ::GC_Troop_Train m_PacketData;
 };

 class GC_TROOP_TRAIN_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_TROOP_TRAIN_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_TROOP_TRAIN_PAK ; }
 };

 class GC_TROOP_TRAIN_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_TROOP_TRAIN_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
