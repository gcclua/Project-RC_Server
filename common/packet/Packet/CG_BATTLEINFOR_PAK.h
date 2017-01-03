//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_BATTLEINFOR_PAK_H_
 #define _CG_BATTLEINFOR_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_BATTLEINFOR_PAK:public Packet
 {
 public:
 CG_BATTLEINFOR_PAK():Packet(m_PacketData){}
 virtual ~CG_BATTLEINFOR_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_BATTLEINFOR_PAK;}
 public:
 ::CG_BATTLEINFOR m_PacketData;
 };

 class CG_BATTLEINFOR_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_BATTLEINFOR_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_BATTLEINFOR_PAK ; }
 };

 class CG_BATTLEINFOR_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_BATTLEINFOR_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
