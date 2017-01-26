//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_TROOP_TRAIN_PAK_H_
 #define _CG_TROOP_TRAIN_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_TROOP_TRAIN_PAK:public Packet
 {
 public:
 CG_TROOP_TRAIN_PAK():Packet(m_PacketData){}
 virtual ~CG_TROOP_TRAIN_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_TROOP_TRAIN_PAK;}
 public:
 ::CG_Troop_Train m_PacketData;
 };

 class CG_TROOP_TRAIN_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_TROOP_TRAIN_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_TROOP_TRAIN_PAK ; }
 };

 class CG_TROOP_TRAIN_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_TROOP_TRAIN_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
