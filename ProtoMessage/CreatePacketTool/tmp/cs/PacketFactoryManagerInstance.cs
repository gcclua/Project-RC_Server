//This code create by CodeEngine Author:Wendy ,don't modify

namespace SPacket.SocketInstance
 {
 public class PacketFactoryManagerInstance : PacketFactoryManager
 {
 public override bool Init ()
 {
 AddFactory(new GC_LOGIN_RET_PF());
AddFactory(new GC_CONNECTED_HEARTBEAT_PF());
AddFactory(new GC_NEAR_MARCHLIST_PF());
AddFactory(new GC_CHAT_PF());
AddFactory(new GC_NOTICE_PF());
AddFactory(new GC_UPDATE_SCENE_INSTACTIVATION_PF());
AddFactory(new GC_MOVE_PF());
AddFactory(new GC_STOP_PF());
AddFactory(new GC_TELEMOVE_PF());
AddFactory(new GC_RET_USE_SKILL_PF());
AddFactory(new GC_UPDATE_ANIMATION_STATE_PF());
AddFactory(new GC_DELETE_OBJ_PF());
AddFactory(new GC_ATTACKFLY_PF());
AddFactory(new GC_FORCE_SETPOS_PF());
AddFactory(new GC_UPDATE_NEEDIMPACTINFO_PF());
AddFactory(new GC_PLAY_EFFECT_PF());
AddFactory(new GC_REMOVEEFFECT_PF());
AddFactory(new CG_LOGIN_PF());
AddFactory(new CG_CONNECTED_HEARTBEAT_PF());
AddFactory(new CG_REQ_NEAR_LIST_PF());
AddFactory(new CG_CHAT_PF());
AddFactory(new CG_MOVE_PF());
AddFactory(new CG_FIGHT_PF());
AddFactory(new CG_LEAVE_COPYSCENE_PF());
 AddPacketHander(MessageID.PACKET_GC_LOGIN_RET, new GC_LOGIN_RETHandler());
AddPacketHander(MessageID.PACKET_GC_CONNECTED_HEARTBEAT, new GC_CONNECTED_HEARTBEATHandler());
AddPacketHander(MessageID.PACKET_GC_NEAR_MARCHLIST, new GC_NEAR_MARCHLISTHandler());
AddPacketHander(MessageID.PACKET_GC_CHAT, new GC_CHATHandler());
AddPacketHander(MessageID.PACKET_GC_NOTICE, new GC_NOTICEHandler());
AddPacketHander(MessageID.PACKET_GC_UPDATE_SCENE_INSTACTIVATION, new GC_UPDATE_SCENE_INSTACTIVATIONHandler());
AddPacketHander(MessageID.PACKET_GC_MOVE, new GC_MOVEHandler());
AddPacketHander(MessageID.PACKET_GC_STOP, new GC_STOPHandler());
AddPacketHander(MessageID.PACKET_GC_TELEMOVE, new GC_TELEMOVEHandler());
AddPacketHander(MessageID.PACKET_GC_RET_USE_SKILL, new GC_RET_USE_SKILLHandler());
AddPacketHander(MessageID.PACKET_GC_UPDATE_ANIMATION_STATE, new GC_UPDATE_ANIMATION_STATEHandler());
AddPacketHander(MessageID.PACKET_GC_DELETE_OBJ, new GC_DELETE_OBJHandler());
AddPacketHander(MessageID.PACKET_GC_ATTACKFLY, new GC_ATTACKFLYHandler());
AddPacketHander(MessageID.PACKET_GC_FORCE_SETPOS, new GC_FORCE_SETPOSHandler());
AddPacketHander(MessageID.PACKET_GC_UPDATE_NEEDIMPACTINFO, new GC_UPDATE_NEEDIMPACTINFOHandler());
AddPacketHander(MessageID.PACKET_GC_PLAY_EFFECT, new GC_PLAY_EFFECTHandler());
AddPacketHander(MessageID.PACKET_GC_REMOVEEFFECT, new GC_REMOVEEFFECTHandler());
AddPacketHander(MessageID.PACKET_CG_LOGIN, new CG_LOGINHandler());
AddPacketHander(MessageID.PACKET_CG_CONNECTED_HEARTBEAT, new CG_CONNECTED_HEARTBEATHandler());
AddPacketHander(MessageID.PACKET_CG_REQ_NEAR_LIST, new CG_REQ_NEAR_LISTHandler());
AddPacketHander(MessageID.PACKET_CG_CHAT, new CG_CHATHandler());
AddPacketHander(MessageID.PACKET_CG_MOVE, new CG_MOVEHandler());
AddPacketHander(MessageID.PACKET_CG_FIGHT, new CG_FIGHTHandler());
AddPacketHander(MessageID.PACKET_CG_LEAVE_COPYSCENE, new CG_LEAVE_COPYSCENEHandler());
 return true;
 } 
 }
 

 

public class GC_ATTACKFLY_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_ATTACKFLY;
 }
 }
public class GC_CHAT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_CHAT;
 }
 }
public class GC_CONNECTED_HEARTBEAT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_CONNECTED_HEARTBEAT;
 }
 }
public class GC_DELETE_OBJ_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_DELETE_OBJ;
 }
 }
public class GC_FORCE_SETPOS_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_FORCE_SETPOS;
 }
 }
public class GC_LOGIN_RET_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_LOGIN_RET;
 }
 }
public class GC_MOVE_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_MOVE;
 }
 }
public class GC_NEAR_MARCHLIST_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_NEAR_MARCHLIST;
 }
 }
public class GC_NOTICE_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_NOTICE;
 }
 }
public class GC_PLAY_EFFECT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_PLAY_EFFECT;
 }
 }
public class GC_REMOVEEFFECT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_REMOVEEFFECT;
 }
 }
public class GC_RET_USE_SKILL_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_RET_USE_SKILL;
 }
 }
public class GC_STOP_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_STOP;
 }
 }
public class GC_TELEMOVE_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_TELEMOVE;
 }
 }
public class GC_UPDATE_ANIMATION_STATE_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_UPDATE_ANIMATION_STATE;
 }
 }
public class GC_UPDATE_NEEDIMPACTINFO_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_UPDATE_NEEDIMPACTINFO;
 }
 }
public class GC_UPDATE_SCENE_INSTACTIVATION_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_GC_UPDATE_SCENE_INSTACTIVATION;
 }
 }
public class CG_CHAT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_CHAT;
 }
 }
public class CG_CONNECTED_HEARTBEAT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_CONNECTED_HEARTBEAT;
 }
 }
public class CG_FIGHT_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_FIGHT;
 }
 }
public class CG_LEAVE_COPYSCENE_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_LEAVE_COPYSCENE;
 }
 }
public class CG_LOGIN_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_LOGIN;
 }
 }
public class CG_MOVE_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_MOVE;
 }
 }
public class CG_REQ_NEAR_LIST_PF : PacketFactory
 {
 public MessageID GetPacketID()
 {
 return MessageID.PACKET_CG_REQ_NEAR_LIST;
 }
 }
}
