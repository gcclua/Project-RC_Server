//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_LEAVE_COPYSCENE_PAK_H_
 #define _CG_LEAVE_COPYSCENE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_LEAVE_COPYSCENE_PAK:public Packet
 {
 public:
 CG_LEAVE_COPYSCENE_PAK():Packet(m_PacketData){}
 virtual ~CG_LEAVE_COPYSCENE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual tuint32 Execute( ServerPlayer* pServerPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_LEAVE_COPYSCENE_PAK;}
 public:
 ::CG_LEAVE_COPYSCENE m_PacketData;
 };

 class CG_LEAVE_COPYSCENE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_LEAVE_COPYSCENE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_LEAVE_COPYSCENE_PAK ; }
 };

 class CG_LEAVE_COPYSCENE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_LEAVE_COPYSCENE_PAK* pPacket, Player* pPlayer ) ;
 static tuint32 Execute( Packets::CG_LEAVE_COPYSCENE_PAK* pPacket, ServerPlayer* pServerPlayer ) ;
 };

}
 #endif
