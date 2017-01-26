//This code create by CodeEngine Author:Wendy ,don't modify

#include "LibNetwork.h"
 #include"CG_LOGIN_PAK.h"
#include"CG_CONNECTED_HEARTBEAT_PAK.h"
#include"CG_REQ_NEAR_LIST_PAK.h"
#include"CG_CHAT_PAK.h"
#include"CG_MOVE_PAK.h"
#include"CG_MARCH_MOVE_PAK.h"
#include"CG_SKILL_USE_PAK.h"
#include"CG_FIGHT_PAK.h"
#include"CG_LEAVE_COPYSCENE_PAK.h"
#include"CG_ROBOT_OPEN_PAK.h"
#include"CG_ASSIGN_HERO_PAK.h"
#include"CG_SEND_MARCH_PAK.h"
#include"CG_CREATEROLE_PAK.h"
#include"CG_BATTLEINFOR_PAK.h"
#include"CG_OBJPOSLIST_PAK.h"
#include"CG_BUILDING_LEVELUP_PAK.h"
#include"CG_TROOP_TRAIN_PAK.h"
#include"CG_BATTLEPREPARE_PAK.h"
#include"GC_LOGIN_RET_PAK.h"
#include"GC_CONNECTED_HEARTBEAT_PAK.h"
#include"GC_NEAR_MARCHLIST_PAK.h"
#include"GC_CHAT_PAK.h"
#include"GC_NOTICE_PAK.h"
#include"GC_UPDATE_SCENE_INSTACTIVATION_PAK.h"
#include"GC_MOVE_PAK.h"
#include"GC_MARCH_MOVE_PAK.h"
#include"GC_STOP_PAK.h"
#include"GC_TELEMOVE_PAK.h"
#include"GC_RET_USE_SKILL_PAK.h"
#include"GC_UPDATE_ANIMATION_STATE_PAK.h"
#include"GC_DELETE_OBJ_PAK.h"
#include"GC_ATTACKFLY_PAK.h"
#include"GC_FORCE_SETPOS_PAK.h"
#include"GC_UPDATE_NEEDIMPACTINFO_PAK.h"
#include"GC_PLAY_EFFECT_PAK.h"
#include"GC_REMOVEEFFECT_PAK.h"
#include"GC_FIGHT_PAK.h"
#include"GC_ROBOT_OPEN_PAK.h"
#include"GC_ASSIGN_HERO_PAK.h"
#include"GC_SEND_MARCH_PAK.h"
#include"GC_CREATEROLE_RET_PAK.h"
#include"GC_LOGIN_QUEUE_STATUS_PAK.h"
#include"GC_BATTLEINFOR_PAK.h"
#include"GC_OBJPOSLIST_PAK.h"
#include"GC_OBJCOMMANDPURSUE_PAK.h"
#include"GC_OBJPREPAREFORATTACK_PAK.h"
#include"GC_OBJGETHURT_PAK.h"
#include"GC_BUILDING_LEVELUP_PAK.h"
#include"GC_UPDATE_MARCH_PAK.h"
#include"GC_TROOP_TRAIN_PAK.h"
#include"GC_TROOPTRAIN_OVER_PAK.h"
#include"GC_BATTLEPREPARE_PAK.h"
#include"GC_BATTLEEND_PAK.h"
#include"GC_BATTLESTART_PAK.h"
PacketFactoryManager gPacketFactoryManager;
 PacketFactoryManager::PacketFactoryManager( )
 {
 __ENTER_FUNCTION
 m_Factories = null_ptr ;
 m_Size = Packets::PACKET_MAX ;
 AssertEx( m_Size>0, "" ) ;
 m_Factories = new PacketFactory*[ m_Size ];
 AssertEx( m_Factories, "" ) ;
 m_pPacketAllocCount = new tuint32[m_Size] ;
 AssertEx( m_pPacketAllocCount, "" ) ;
 for( tint32 i=0; i<m_Size; i++ )
 {
 m_Factories[i] = null_ptr ;
 m_pPacketAllocCount[i] = 0 ;
 }
 __LEAVE_FUNCTION
 }
 
 PacketFactoryManager::~PacketFactoryManager( ) 
 {
 __ENTER_FUNCTION

 AssertEx( m_Factories!=null_ptr,"" ) ;
 for( tint32 i=0; i<m_Size; i++ ) 
 {
 SAFE_DELETE(m_Factories[i]) ;
 }
 SAFE_DELETE_ARRAY(m_Factories) ;
 SAFE_DELETE_ARRAY(m_pPacketAllocCount) ;
 __LEAVE_FUNCTION
 }
 
 void PacketFactoryManager::AddFactory( PacketFactory* pFactory ) 
 {
 __ENTER_FUNCTION
 
 if( m_Factories[pFactory->GetPacketID()]!=null_ptr )
 {
 AssertEx( false, "") ;
 return ;
 }
 
 m_Factories[pFactory->GetPacketID()] = pFactory ;
 
 __LEAVE_FUNCTION
 }
 Packet* PacketFactoryManager::CreatePacket( PacketID_t packetID ) 
 {
 __ENTER_FUNCTION
 if( packetID>=m_Size || m_Factories[packetID]==null_ptr ) 
 {
 AssertEx(false, "") ;
 return null_ptr ;
 }
 Packet* pPacket = null_ptr ;
 Lock() ;
 try
 {
 pPacket = m_Factories[packetID]->CreatePacket();
 m_pPacketAllocCount[packetID]++ ;
 }
 catch(...)
 {
 pPacket = null_ptr ;
 }
 Unlock() ;
 return pPacket ;
 __LEAVE_FUNCTION
 return null_ptr ;
 }

 void PacketFactoryManager::RemovePacket( Packet* pPacket )
 {
 __ENTER_FUNCTION
 if( pPacket==null_ptr )
 {
 AssertEx(false, "") ;
 return ;
 }
 PacketID_t packetID = pPacket->GetPacketID() ;
 if( packetID>=m_Size ) 

 {
 AssertEx(false, "") ;
 return ;
 }
 
 Lock() ;
 try
 {
 SAFE_DELETE( pPacket ) ;
 m_pPacketAllocCount[packetID] -- ;
 }
 catch(...)
 {
 }
 Unlock() ;
 return ;
 __LEAVE_FUNCTION
 return ;
 }
bool PacketFactoryManager::Init( )
 {
 __ENTER_FUNCTION
 AddFactory(new Packets::CG_LOGIN_PAKFactory());
AddFactory(new Packets::CG_CONNECTED_HEARTBEAT_PAKFactory());
AddFactory(new Packets::CG_REQ_NEAR_LIST_PAKFactory());
AddFactory(new Packets::CG_CHAT_PAKFactory());
AddFactory(new Packets::CG_MOVE_PAKFactory());
AddFactory(new Packets::CG_MARCH_MOVE_PAKFactory());
AddFactory(new Packets::CG_SKILL_USE_PAKFactory());
AddFactory(new Packets::CG_FIGHT_PAKFactory());
AddFactory(new Packets::CG_LEAVE_COPYSCENE_PAKFactory());
AddFactory(new Packets::CG_ROBOT_OPEN_PAKFactory());
AddFactory(new Packets::CG_ASSIGN_HERO_PAKFactory());
AddFactory(new Packets::CG_SEND_MARCH_PAKFactory());
AddFactory(new Packets::CG_CREATEROLE_PAKFactory());
AddFactory(new Packets::CG_BATTLEINFOR_PAKFactory());
AddFactory(new Packets::CG_OBJPOSLIST_PAKFactory());
AddFactory(new Packets::CG_BUILDING_LEVELUP_PAKFactory());
AddFactory(new Packets::CG_TROOP_TRAIN_PAKFactory());
AddFactory(new Packets::CG_BATTLEPREPARE_PAKFactory());
 AddFactory(new Packets::GC_LOGIN_RET_PAKFactory());
AddFactory(new Packets::GC_CONNECTED_HEARTBEAT_PAKFactory());
AddFactory(new Packets::GC_NEAR_MARCHLIST_PAKFactory());
AddFactory(new Packets::GC_CHAT_PAKFactory());
AddFactory(new Packets::GC_NOTICE_PAKFactory());
AddFactory(new Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAKFactory());
AddFactory(new Packets::GC_MOVE_PAKFactory());
AddFactory(new Packets::GC_MARCH_MOVE_PAKFactory());
AddFactory(new Packets::GC_STOP_PAKFactory());
AddFactory(new Packets::GC_TELEMOVE_PAKFactory());
AddFactory(new Packets::GC_RET_USE_SKILL_PAKFactory());
AddFactory(new Packets::GC_UPDATE_ANIMATION_STATE_PAKFactory());
AddFactory(new Packets::GC_DELETE_OBJ_PAKFactory());
AddFactory(new Packets::GC_ATTACKFLY_PAKFactory());
AddFactory(new Packets::GC_FORCE_SETPOS_PAKFactory());
AddFactory(new Packets::GC_UPDATE_NEEDIMPACTINFO_PAKFactory());
AddFactory(new Packets::GC_PLAY_EFFECT_PAKFactory());
AddFactory(new Packets::GC_REMOVEEFFECT_PAKFactory());
AddFactory(new Packets::GC_FIGHT_PAKFactory());
AddFactory(new Packets::GC_ROBOT_OPEN_PAKFactory());
AddFactory(new Packets::GC_ASSIGN_HERO_PAKFactory());
AddFactory(new Packets::GC_SEND_MARCH_PAKFactory());
AddFactory(new Packets::GC_CREATEROLE_RET_PAKFactory());
AddFactory(new Packets::GC_LOGIN_QUEUE_STATUS_PAKFactory());
AddFactory(new Packets::GC_BATTLEINFOR_PAKFactory());
AddFactory(new Packets::GC_OBJPOSLIST_PAKFactory());
AddFactory(new Packets::GC_OBJCOMMANDPURSUE_PAKFactory());
AddFactory(new Packets::GC_OBJPREPAREFORATTACK_PAKFactory());
AddFactory(new Packets::GC_OBJGETHURT_PAKFactory());
AddFactory(new Packets::GC_BUILDING_LEVELUP_PAKFactory());
AddFactory(new Packets::GC_UPDATE_MARCH_PAKFactory());
AddFactory(new Packets::GC_TROOP_TRAIN_PAKFactory());
AddFactory(new Packets::GC_TROOPTRAIN_OVER_PAKFactory());
AddFactory(new Packets::GC_BATTLEPREPARE_PAKFactory());
AddFactory(new Packets::GC_BATTLEEND_PAKFactory());
AddFactory(new Packets::GC_BATTLESTART_PAKFactory());
       return true ;
 __LEAVE_FUNCTION
 return false ;
 }
