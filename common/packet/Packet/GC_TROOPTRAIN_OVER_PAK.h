//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_TROOPTRAIN_OVER_PAK_H_
 #define _GC_TROOPTRAIN_OVER_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_TROOPTRAIN_OVER_PAK:public Packet
 {
 public:
 GC_TROOPTRAIN_OVER_PAK():Packet(m_PacketData){}
 virtual ~GC_TROOPTRAIN_OVER_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_TROOPTRAIN_OVER_PAK;}
 public:
 ::GC_TroopTrain_Over m_PacketData;
 };

 class GC_TROOPTRAIN_OVER_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_TROOPTRAIN_OVER_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_TROOPTRAIN_OVER_PAK ; }
 };

 class GC_TROOPTRAIN_OVER_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_TROOPTRAIN_OVER_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
