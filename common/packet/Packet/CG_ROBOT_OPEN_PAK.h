//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_ROBOT_OPEN_PAK_H_
 #define _CG_ROBOT_OPEN_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_ROBOT_OPEN_PAK:public Packet
 {
 public:
 CG_ROBOT_OPEN_PAK():Packet(m_PacketData){}
 virtual ~CG_ROBOT_OPEN_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_ROBOT_OPEN_PAK;}
 public:
 ::CG_ROBOT_OPEN m_PacketData;
 };

 class CG_ROBOT_OPEN_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_ROBOT_OPEN_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_ROBOT_OPEN_PAK ; }
 };

 class CG_ROBOT_OPEN_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_ROBOT_OPEN_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
