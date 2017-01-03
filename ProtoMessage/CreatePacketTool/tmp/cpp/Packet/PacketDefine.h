//This code create by CodeEngine Author:Wendy ,don't modify

#ifndef __PACKET_DEFINE_H__
 #define __PACKET_DEFINE_H__
 
 #include "BaseType.h"
 #define MAX_PACKET_NAME_SIZE (128) 
 
 namespace Packets
 {
 //消息类型值描述格式：PACKET_XX_YYYYYY
 //XX可以描述为：GC、CG 
 //G游戏服务器端、C客户端 
 //YYYYYY表示消息内容
 //例如：PACKET_CG_ATTACK 表示客户端发给游戏服务器端关于攻击的消息
 enum PACKET_DEFINE
 {
 PACKET_NONE = 0 , // 0，空
 PACKET_CG_LOGIN_PAK = 1, //client ask login 
 PACKET_GC_LOGIN_RET_PAK =2, //client login result 
 PACKET_CG_CONNECTED_HEARTBEAT_PAK,	//client connected heartbeat
PACKET_GC_CONNECTED_HEARTBEAT_PAK,	//server connected heartbeat
PACKET_CG_REQ_NEAR_LIST_PAK,	//client ask nearlist
PACKET_GC_NEAR_MARCHLIST_PAK,	//server send nearby player list to client
PACKET_CG_CHAT_PAK,	//Client send chat info
PACKET_GC_CHAT_PAK,	//Server send chat info
PACKET_GC_NOTICE_PAK,	//notice from server
PACKET_GC_UPDATE_SCENE_INSTACTIVATION_PAK,	//Update Scene InstActivation
PACKET_GS_CONNECTED_HEARTBEAT_PAK,	//gameserver to server heartbeat
PACKET_SG_CONNECTED_HEARTBEAT_PAK,	//server to gameserver heartbeat
PACKET_CG_MOVE_PAK,	//Player Move
PACKET_GC_MOVE_PAK,	//Notify Character Move
PACKET_GC_STOP_PAK,	//Notify Character Stop
PACKET_GC_TELEMOVE_PAK,	//TeleMove
PACKET_GC_RET_USE_SKILL_PAK,	//Use Skill ret
PACKET_GC_UPDATE_ANIMATION_STATE_PAK,	//Update Animation state
PACKET_GC_DELETE_OBJ_PAK,	//Delete Player
PACKET_GC_ATTACKFLY_PAK,	//Attak fly
PACKET_GC_FORCE_SETPOS_PAK,	//Server Force Set Player Pos
PACKET_GC_UPDATE_NEEDIMPACTINFO_PAK,	//syn need Impact Info
PACKET_GC_PLAY_EFFECT_PAK,	//Server Send Player Use Tool
PACKET_GC_REMOVEEFFECT_PAK,	//remove Effect
PACKET_CG_FIGHT_PAK,	//Send Open Fight Req to Server
PACKET_CG_LEAVE_COPYSCENE_PAK,	// Client Leave Copyscene

 PACKET_MAX //消息类型的最大值
 };

 
 void InitPacketNameVector();
 const tchar* GetPacketNameByID(tint32 nPacketID);
 }
 #endif
