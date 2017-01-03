//This code create by CodeEngine

using System;
 using Module.Log;
 using Google.ProtocolBuffers;
 using System.Collections;
namespace SPacket.SocketInstance
 {
 public class GC_CONNECTED_HEARTBEATHandler : Ipacket
 {
 public uint Execute(PacketDistributed ipacket)
 {
 GC_CONNECTED_HEARTBEAT packet = (GC_CONNECTED_HEARTBEAT )ipacket;
 if (null == packet) return (uint)PACKET_EXE.PACKET_EXE_ERROR;
 //enter your logic
 return (uint)PACKET_EXE.PACKET_EXE_CONTINUE;
 }
 }
 }
