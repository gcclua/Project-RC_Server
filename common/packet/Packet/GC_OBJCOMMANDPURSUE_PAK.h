//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _GC_OBJCOMMANDPURSUE_PAK_H_
 #define _GC_OBJCOMMANDPURSUE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class GC_OBJCOMMANDPURSUE_PAK:public Packet
 {
 public:
 GC_OBJCOMMANDPURSUE_PAK():Packet(m_PacketData){}
 virtual ~GC_OBJCOMMANDPURSUE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_GC_OBJCOMMANDPURSUE_PAK;}
 public:
 ::GC_OBJCOMMANDPURSUE m_PacketData;
 };

 class GC_OBJCOMMANDPURSUE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::GC_OBJCOMMANDPURSUE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_GC_OBJCOMMANDPURSUE_PAK ; }
 };

 class GC_OBJCOMMANDPURSUE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::GC_OBJCOMMANDPURSUE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
