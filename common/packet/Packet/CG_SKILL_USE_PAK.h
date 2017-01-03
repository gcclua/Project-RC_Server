//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_SKILL_USE_PAK_H_
 #define _CG_SKILL_USE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_SKILL_USE_PAK:public Packet
 {
 public:
 CG_SKILL_USE_PAK():Packet(m_PacketData){}
 virtual ~CG_SKILL_USE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_SKILL_USE_PAK;}
 public:
 ::CG_SKILL_USE m_PacketData;
 };

 class CG_SKILL_USE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_SKILL_USE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_SKILL_USE_PAK ; }
 };

 class CG_SKILL_USE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_SKILL_USE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
