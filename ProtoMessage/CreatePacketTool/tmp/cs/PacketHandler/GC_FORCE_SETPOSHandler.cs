//This code create by CodeEngine

using System;
 using Module.Log;
 using Google.ProtocolBuffers;
 using System.Collections;
namespace SPacket.SocketInstance
 {
 public class GC_FORCE_SETPOSHandler : Ipacket
 {
 public uint Execute(PacketDistributed ipacket)
 {
 GC_FORCE_SETPOS packet = (GC_FORCE_SETPOS )ipacket;
 if (null == packet) return (uint)PACKET_EXE.PACKET_EXE_ERROR;
 //enter your logic
 return (uint)PACKET_EXE.PACKET_EXE_CONTINUE;
 }
 }
 }
