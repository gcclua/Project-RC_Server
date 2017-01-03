//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_DELETE_OBJ_PAK_H_
 #define _GC_DELETE_OBJ_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_DELETE_OBJ_PAK:public Packet
 {
 public:
 GC_DELETE_OBJ_PAK():Packet(m_PacketData){}
 virtual ~GC_DELETE_OBJ_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_DELETE_OBJ_PAK;}
 public:
 ::GC_DELETE_OBJ m_PacketData;
 };

 class GC_DELETE_OBJ_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_DELETE_OBJ_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_DELETE_OBJ_PAK ; }
 };

 class GC_DELETE_OBJ_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_DELETE_OBJ_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::GC_DELETE_OBJ_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
