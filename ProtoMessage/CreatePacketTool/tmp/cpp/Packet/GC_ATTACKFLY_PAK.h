//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_ATTACKFLY_PAK_H_
 #define _GC_ATTACKFLY_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_ATTACKFLY_PAK:public Packet
 {
 public:
 GC_ATTACKFLY_PAK():Packet(m_PacketData){}
 virtual ~GC_ATTACKFLY_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_ATTACKFLY_PAK;}
 public:
 ::GC_ATTACKFLY m_PacketData;
 };

 class GC_ATTACKFLY_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_ATTACKFLY_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_ATTACKFLY_PAK ; }
 };

 class GC_ATTACKFLY_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_ATTACKFLY_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::GC_ATTACKFLY_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
