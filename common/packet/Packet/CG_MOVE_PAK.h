//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_MOVE_PAK_H_
 #define _CG_MOVE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_MOVE_PAK:public Packet
 {
 public:
 CG_MOVE_PAK():Packet(m_PacketData){}
 virtual ~CG_MOVE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_MOVE_PAK;}
 public:
 ::CG_MOVE m_PacketData;
 };

 class CG_MOVE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_MOVE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_MOVE_PAK ; }
 };

 class CG_MOVE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_MOVE_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::CG_MOVE_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
