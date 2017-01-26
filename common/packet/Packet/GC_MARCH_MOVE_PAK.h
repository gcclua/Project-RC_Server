//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_MARCH_MOVE_PAK_H_
 #define _GC_MARCH_MOVE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_MARCH_MOVE_PAK:public Packet
 {
 public:
 GC_MARCH_MOVE_PAK():Packet(m_PacketData){}
 virtual ~GC_MARCH_MOVE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_MARCH_MOVE_PAK;}
 public:
 ::GC_MARCH_MOVE m_PacketData;
 };

 class GC_MARCH_MOVE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_MARCH_MOVE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_MARCH_MOVE_PAK ; }
 };

 class GC_MARCH_MOVE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_MARCH_MOVE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
