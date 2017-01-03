//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_ROBOT_OPEN_PAK_H_
 #define _GC_ROBOT_OPEN_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_ROBOT_OPEN_PAK:public Packet
 {
 public:
 GC_ROBOT_OPEN_PAK():Packet(m_PacketData){}
 virtual ~GC_ROBOT_OPEN_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_ROBOT_OPEN_PAK;}
 public:
 ::GC_ROBOT_OPEN m_PacketData;
 };

 class GC_ROBOT_OPEN_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_ROBOT_OPEN_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_ROBOT_OPEN_PAK ; }
 };

 class GC_ROBOT_OPEN_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_ROBOT_OPEN_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
