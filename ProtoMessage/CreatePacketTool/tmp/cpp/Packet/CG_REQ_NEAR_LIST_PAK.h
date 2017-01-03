//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_REQ_NEAR_LIST_PAK_H_
 #define _CG_REQ_NEAR_LIST_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_REQ_NEAR_LIST_PAK:public Packet
 {
 public:
 CG_REQ_NEAR_LIST_PAK():Packet(m_PacketData){}
 virtual ~CG_REQ_NEAR_LIST_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_REQ_NEAR_LIST_PAK;}
 public:
 ::CG_REQ_NEAR_LIST m_PacketData;
 };

 class CG_REQ_NEAR_LIST_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_REQ_NEAR_LIST_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_REQ_NEAR_LIST_PAK ; }
 };

 class CG_REQ_NEAR_LIST_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_REQ_NEAR_LIST_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::CG_REQ_NEAR_LIST_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
