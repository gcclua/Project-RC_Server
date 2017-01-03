//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_FIGHT_PAK_H_
 #define _CG_FIGHT_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_FIGHT_PAK:public Packet
 {
 public:
 CG_FIGHT_PAK():Packet(m_PacketData){}
 virtual ~CG_FIGHT_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_FIGHT_PAK;}
 public:
 ::CG_FIGHT m_PacketData;
 };

 class CG_FIGHT_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_FIGHT_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_FIGHT_PAK ; }
 };

 class CG_FIGHT_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_FIGHT_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
