//This code create by CodeEngine ,don't modify

using System;
 public enum MessageID :ushort
 {
 PACKET_NONE = 0 , // 0£¬¿Õ
 PACKET_CG_LOGIN = 1, //client ask login 
 PACKET_GC_LOGIN_RET =2, //client login result 
 PACKET_CG_CONNECTED_HEARTBEAT,	//client connected heartbeat
PACKET_GC_CONNECTED_HEARTBEAT,	//server connected heartbeat
PACKET_CG_REQ_NEAR_LIST,	//client ask nearlist
PACKET_GC_NEAR_MARCHLIST,	//server send nearby player list to client
PACKET_CG_CHAT,	//Client send chat info
PACKET_GC_CHAT,	//Server send chat info
PACKET_GC_NOTICE,	//notice from server
PACKET_GC_UPDATE_SCENE_INSTACTIVATION,	//Update Scene InstActivation
PACKET_GS_CONNECTED_HEARTBEAT,	//gameserver to server heartbeat
PACKET_SG_CONNECTED_HEARTBEAT,	//server to gameserver heartbeat
PACKET_CG_MOVE,	//Player Move
PACKET_GC_MOVE,	//Notify Character Move
PACKET_GC_STOP,	//Notify Character Stop
PACKET_GC_TELEMOVE,	//TeleMove
PACKET_GC_RET_USE_SKILL,	//Use Skill ret
PACKET_GC_UPDATE_ANIMATION_STATE,	//Update Animation state
PACKET_GC_DELETE_OBJ,	//Delete Player
PACKET_GC_ATTACKFLY,	//Attak fly
PACKET_GC_FORCE_SETPOS,	//Server Force Set Player Pos
PACKET_GC_UPDATE_NEEDIMPACTINFO,	//syn need Impact Info
PACKET_GC_PLAY_EFFECT,	//Server Send Player Use Tool
PACKET_GC_REMOVEEFFECT,	//remove Effect
PACKET_CG_FIGHT,	//Send Open Fight Req to Server
PACKET_CG_LEAVE_COPYSCENE,	// Client Leave Copyscene

 PACKET_SIZE
 }
