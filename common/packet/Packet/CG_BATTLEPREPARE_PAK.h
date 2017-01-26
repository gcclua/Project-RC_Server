//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_BATTLEPREPARE_PAK_H_
 #define _CG_BATTLEPREPARE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_BATTLEPREPARE_PAK:public Packet
 {
 public:
 CG_BATTLEPREPARE_PAK():Packet(m_PacketData){}
 virtual ~CG_BATTLEPREPARE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_BATTLEPREPARE_PAK;}
 public:
 ::CG_BATTLEPREPARE m_PacketData;
 };

 class CG_BATTLEPREPARE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_BATTLEPREPARE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_BATTLEPREPARE_PAK ; }
 };

 class CG_BATTLEPREPARE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_BATTLEPREPARE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
