//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_CONNECTED_HEARTBEAT_PAK_H_
 #define _CG_CONNECTED_HEARTBEAT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_CONNECTED_HEARTBEAT_PAK:public Packet
 {
 public:
 CG_CONNECTED_HEARTBEAT_PAK():Packet(m_PacketData){}
 virtual ~CG_CONNECTED_HEARTBEAT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_CONNECTED_HEARTBEAT_PAK;}
 public:
 ::CG_CONNECTED_HEARTBEAT m_PacketData;
 };

 class CG_CONNECTED_HEARTBEAT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_CONNECTED_HEARTBEAT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_CONNECTED_HEARTBEAT_PAK ; }
 };

 class CG_CONNECTED_HEARTBEAT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_CONNECTED_HEARTBEAT_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::CG_CONNECTED_HEARTBEAT_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
