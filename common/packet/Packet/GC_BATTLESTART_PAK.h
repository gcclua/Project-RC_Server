//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_BATTLESTART_PAK_H_
 #define _GC_BATTLESTART_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_BATTLESTART_PAK:public Packet
 {
 public:
 GC_BATTLESTART_PAK():Packet(m_PacketData){}
 virtual ~GC_BATTLESTART_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_BATTLESTART_PAK;}
 public:
 ::GC_BattleStart m_PacketData;
 };

 class GC_BATTLESTART_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_BATTLESTART_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_BATTLESTART_PAK ; }
 };

 class GC_BATTLESTART_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_BATTLESTART_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
