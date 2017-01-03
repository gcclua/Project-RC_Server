//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_OBJPREPAREFORATTACK_PAK_H_
 #define _GC_OBJPREPAREFORATTACK_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_OBJPREPAREFORATTACK_PAK:public Packet
 {
 public:
 GC_OBJPREPAREFORATTACK_PAK():Packet(m_PacketData){}
 virtual ~GC_OBJPREPAREFORATTACK_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_OBJPREPAREFORATTACK_PAK;}
 public:
 ::GC_OBJPREPAREFORATTACK m_PacketData;
 };

 class GC_OBJPREPAREFORATTACK_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_OBJPREPAREFORATTACK_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_OBJPREPAREFORATTACK_PAK ; }
 };

 class GC_OBJPREPAREFORATTACK_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_OBJPREPAREFORATTACK_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
