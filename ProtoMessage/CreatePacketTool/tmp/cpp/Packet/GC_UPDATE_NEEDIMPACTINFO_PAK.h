//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_UPDATE_NEEDIMPACTINFO_PAK_H_
 #define _GC_UPDATE_NEEDIMPACTINFO_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_UPDATE_NEEDIMPACTINFO_PAK:public Packet
 {
 public:
 GC_UPDATE_NEEDIMPACTINFO_PAK():Packet(m_PacketData){}
 virtual ~GC_UPDATE_NEEDIMPACTINFO_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_UPDATE_NEEDIMPACTINFO_PAK;}
 public:
 ::GC_UPDATE_NEEDIMPACTINFO m_PacketData;
 };

 class GC_UPDATE_NEEDIMPACTINFO_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_UPDATE_NEEDIMPACTINFO_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_UPDATE_NEEDIMPACTINFO_PAK ; }
 };

 class GC_UPDATE_NEEDIMPACTINFO_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_UPDATE_NEEDIMPACTINFO_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::GC_UPDATE_NEEDIMPACTINFO_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
