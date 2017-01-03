//This code create by CodeEngine

using System.IO;
 using System;
 #if UNITY_WP8 
 using UnityPortSocket; 
 #else 
 using System.Net.Sockets; 
 #endif 
 using Google.ProtocolBuffers;
public abstract class PacketDistributed
 {
 public static PacketDistributed CreatePacket(MessageID packetID)
 {
 PacketDistributed packet = null;
 switch (packetID)
 {
 case MessageID.PACKET_CG_CHAT: { packet = new CG_CHAT(); } break;
case MessageID.PACKET_CG_CONNECTED_HEARTBEAT: { packet = new CG_CONNECTED_HEARTBEAT(); } break;
case MessageID.PACKET_CG_FIGHT: { packet = new CG_FIGHT(); } break;
case MessageID.PACKET_CG_LEAVE_COPYSCENE: { packet = new CG_LEAVE_COPYSCENE(); } break;
case MessageID.PACKET_CG_LOGIN: { packet = new CG_LOGIN(); } break;
case MessageID.PACKET_CG_MOVE: { packet = new CG_MOVE(); } break;
case MessageID.PACKET_CG_REQ_NEAR_LIST: { packet = new CG_REQ_NEAR_LIST(); } break;
case MessageID.PACKET_GC_ATTACKFLY: { packet = new GC_ATTACKFLY(); } break;
case MessageID.PACKET_GC_CHAT: { packet = new GC_CHAT(); } break;
case MessageID.PACKET_GC_CONNECTED_HEARTBEAT: { packet = new GC_CONNECTED_HEARTBEAT(); } break;
case MessageID.PACKET_GC_DELETE_OBJ: { packet = new GC_DELETE_OBJ(); } break;
case MessageID.PACKET_GC_FORCE_SETPOS: { packet = new GC_FORCE_SETPOS(); } break;
case MessageID.PACKET_GC_LOGIN_RET: { packet = new GC_LOGIN_RET(); } break;
case MessageID.PACKET_GC_MOVE: { packet = new GC_MOVE(); } break;
case MessageID.PACKET_GC_NEAR_MARCHLIST: { packet = new GC_NEAR_MARCHLIST(); } break;
case MessageID.PACKET_GC_NOTICE: { packet = new GC_NOTICE(); } break;
case MessageID.PACKET_GC_PLAY_EFFECT: { packet = new GC_PLAY_EFFECT(); } break;
case MessageID.PACKET_GC_REMOVEEFFECT: { packet = new GC_REMOVEEFFECT(); } break;
case MessageID.PACKET_GC_RET_USE_SKILL: { packet = new GC_RET_USE_SKILL(); } break;
case MessageID.PACKET_GC_STOP: { packet = new GC_STOP(); } break;
case MessageID.PACKET_GC_TELEMOVE: { packet = new GC_TELEMOVE(); } break;
case MessageID.PACKET_GC_UPDATE_ANIMATION_STATE: { packet = new GC_UPDATE_ANIMATION_STATE(); } break;
case MessageID.PACKET_GC_UPDATE_NEEDIMPACTINFO: { packet = new GC_UPDATE_NEEDIMPACTINFO(); } break;
case MessageID.PACKET_GC_UPDATE_SCENE_INSTACTIVATION: { packet = new GC_UPDATE_SCENE_INSTACTIVATION(); } break;
 
 }
 if (null != packet)
 {
 packet.packetID = packetID;
 }
 return packet;
 }
 public void SendPacket()
 {
 NetWorkLogic.GetMe().SendPacket(this); 
 }
 
 public PacketDistributed ParseFrom(byte[] data, int nLen)
 {
 CodedInputStream input = CodedInputStream.CreateInstance(data,0,nLen);
 PacketDistributed inst = MergeFrom(input,this);
 input.CheckLastTagWas(0);
 return inst;
 }
 
 public abstract int SerializedSize();
 public abstract void WriteTo(CodedOutputStream data);
 public abstract PacketDistributed MergeFrom(CodedInputStream input,PacketDistributed _Inst);
 public abstract bool IsInitialized();
 
 public MessageID GetPacketID() { return packetID; }
 protected MessageID packetID;
 }
