//This code create by CodeEngine

using System;
 using Module.Log;
 using Google.ProtocolBuffers;
 using System.Collections;
namespace SPacket.SocketInstance
 {
 public class GC_NEAR_MARCHLISTHandler : Ipacket
 {
 public uint Execute(PacketDistributed ipacket)
 {
 GC_NEAR_MARCHLIST packet = (GC_NEAR_MARCHLIST )ipacket;
 if (null == packet) return (uint)PACKET_EXE.PACKET_EXE_ERROR;
 //enter your logic
 return (uint)PACKET_EXE.PACKET_EXE_CONTINUE;
 }
 }
 }
