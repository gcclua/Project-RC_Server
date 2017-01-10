//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_UPDATE_MARCH_PAK_H_
 #define _GC_UPDATE_MARCH_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_UPDATE_MARCH_PAK:public Packet
 {
 public:
 GC_UPDATE_MARCH_PAK():Packet(m_PacketData){}
 virtual ~GC_UPDATE_MARCH_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_UPDATE_MARCH_PAK;}
 public:
 ::GC_Update_March m_PacketData;
 };

 class GC_UPDATE_MARCH_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_UPDATE_MARCH_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_UPDATE_MARCH_PAK ; }
 };

 class GC_UPDATE_MARCH_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_UPDATE_MARCH_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
