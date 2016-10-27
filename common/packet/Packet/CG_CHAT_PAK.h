//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_CHAT_PAK_H_
 #define _CG_CHAT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_CHAT_PAK:public Packet
 {
 public:
 CG_CHAT_PAK():Packet(m_PacketData){}
 virtual ~CG_CHAT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_CHAT_PAK;}
 public:
 ::CG_CHAT m_PacketData;
 };

 class CG_CHAT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_CHAT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_CHAT_PAK ; }
 };

 class CG_CHAT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_CHAT_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::CG_CHAT_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
