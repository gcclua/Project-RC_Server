//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef _CG_CREATEROLE_PAK_H_
 #define _CG_CREATEROLE_PAK_H_

 #include "Base.h"
 #include "PBMessage.pb.h"
 #include "PacketDefine.h"
 #include "LibNetwork.h"
namespace Packets
 {
class CG_CREATEROLE_PAK:public Packet
 {
 public:
 CG_CREATEROLE_PAK():Packet(m_PacketData){}
 virtual ~CG_CREATEROLE_PAK(){}
 virtual tuint32 Execute( Player* pPlayer );
 virtual PacketID_t GetPacketID( ) const {return PACKET_CG_CREATEROLE_PAK;}
 public:
 ::CG_CREATEROLE m_PacketData;
 };

 class CG_CREATEROLE_PAKFactory : public PacketFactory
 {
 public:
 Packet* CreatePacket() { return new Packets::CG_CREATEROLE_PAK(); }
 PacketID_t GetPacketID()const { return PACKET_CG_CREATEROLE_PAK ; }
 };

 class CG_CREATEROLE_PAKHandler 
 {
 public:
 static tuint32 Execute( Packets::CG_CREATEROLE_PAK* pPacket, Player* pPlayer ) ;
 };

}
 #endif
