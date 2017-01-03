//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_LOGIN_PAK_H_
 #define _CG_LOGIN_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_LOGIN_PAK:public Packet
 {
 public:
 CG_LOGIN_PAK():Packet(m_PacketData){}
 virtual ~CG_LOGIN_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_LOGIN_PAK;}
 public:
 ::CG_LOGIN m_PacketData;
 };

 class CG_LOGIN_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_LOGIN_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_LOGIN_PAK ; }
 };

 class CG_LOGIN_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_LOGIN_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::CG_LOGIN_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
