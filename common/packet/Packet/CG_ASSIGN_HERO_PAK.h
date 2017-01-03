//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_ASSIGN_HERO_PAK_H_
 #define _CG_ASSIGN_HERO_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_ASSIGN_HERO_PAK:public Packet
 {
 public:
 CG_ASSIGN_HERO_PAK():Packet(m_PacketData){}
 virtual ~CG_ASSIGN_HERO_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_ASSIGN_HERO_PAK;}
 public:
 ::CG_ASSIGN_HERO m_PacketData;
 };

 class CG_ASSIGN_HERO_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_ASSIGN_HERO_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_ASSIGN_HERO_PAK ; }
 };

 class CG_ASSIGN_HERO_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_ASSIGN_HERO_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
