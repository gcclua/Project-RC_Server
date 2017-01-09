//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_BUILDING_LEVELUP_PAK_H_
 #define _GC_BUILDING_LEVELUP_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_BUILDING_LEVELUP_PAK:public Packet
 {
 public:
 GC_BUILDING_LEVELUP_PAK():Packet(m_PacketData){}
 virtual ~GC_BUILDING_LEVELUP_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_BUILDING_LEVELUP_PAK;}
 public:
 ::GC_Building_LevelUp m_PacketData;
 };

 class GC_BUILDING_LEVELUP_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_BUILDING_LEVELUP_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_BUILDING_LEVELUP_PAK ; }
 };

 class GC_BUILDING_LEVELUP_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_BUILDING_LEVELUP_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
