//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_SEND_MARCH_PAK_H_
 #define _CG_SEND_MARCH_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_SEND_MARCH_PAK:public Packet
 {
 public:
 CG_SEND_MARCH_PAK():Packet(m_PacketData){}
 virtual ~CG_SEND_MARCH_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_SEND_MARCH_PAK;}
 public:
 ::CG_SEND_MARCH m_PacketData;
 };

 class CG_SEND_MARCH_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_SEND_MARCH_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_SEND_MARCH_PAK ; }
 };

 class CG_SEND_MARCH_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_SEND_MARCH_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
