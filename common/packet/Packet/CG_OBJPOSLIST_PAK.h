//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_OBJPOSLIST_PAK_H_
 #define _CG_OBJPOSLIST_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_OBJPOSLIST_PAK:public Packet
 {
 public:
 CG_OBJPOSLIST_PAK():Packet(m_PacketData){}
 virtual ~CG_OBJPOSLIST_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_OBJPOSLIST_PAK;}
 public:
 ::CG_OBJPOSLIST m_PacketData;
 };

 class CG_OBJPOSLIST_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_OBJPOSLIST_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_OBJPOSLIST_PAK ; }
 };

 class CG_OBJPOSLIST_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_OBJPOSLIST_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
