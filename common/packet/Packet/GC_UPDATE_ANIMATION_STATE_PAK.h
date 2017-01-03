//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_UPDATE_ANIMATION_STATE_PAK_H_
 #define _GC_UPDATE_ANIMATION_STATE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_UPDATE_ANIMATION_STATE_PAK:public Packet
 {
 public:
 GC_UPDATE_ANIMATION_STATE_PAK():Packet(m_PacketData){}
 virtual ~GC_UPDATE_ANIMATION_STATE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_UPDATE_ANIMATION_STATE_PAK;}
 public:
 ::GC_UPDATE_ANIMATION_STATE m_PacketData;
 };

 class GC_UPDATE_ANIMATION_STATE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_UPDATE_ANIMATION_STATE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_UPDATE_ANIMATION_STATE_PAK ; }
 };

 class GC_UPDATE_ANIMATION_STATE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_UPDATE_ANIMATION_STATE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
