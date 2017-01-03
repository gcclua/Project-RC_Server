//This code create by CodeEngine

using System;
 using Module.Log;
 using Google.ProtocolBuffers;
 using System.Collections;
namespace SPacket.SocketInstance
 {
 public class GC_UPDATE_ANIMATION_STATEHandler : Ipacket
 {
 public uint Execute(PacketDistributed ipacket)
 {
 GC_UPDATE_ANIMATION_STATE packet = (GC_UPDATE_ANIMATION_STATE )ipacket;
 if (null == packet) return (uint)PACKET_EXE.PACKET_EXE_ERROR;
 //enter your logic
 return (uint)PACKET_EXE.PACKET_EXE_CONTINUE;
 }
 }
 }
