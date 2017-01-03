//This code create by CodeEngine mrd.cyou.com ,don't modify

using System;
 using scg = global::System.Collections.Generic;
 using pb = global::Google.ProtocolBuffers;
 using pbc = global::Google.ProtocolBuffers.Collections;
 #pragma warning disable



[Serializable]
public class CG_LOGIN : PacketDistributed
{
public enum VALIDATETYPE 
 { 
  TEST = 0,                 //测试登录模式 
  CYOU = 1,                 //聚合SDK登陆模式 
 }
public const int vtypeFieldNumber = 1;
 private bool hasVtype;
 private Int32 vtype_ = 0;
 public bool HasVtype {
 get { return hasVtype; }
 }
 public Int32 Vtype {
 get { return vtype_; }
 set { SetVtype(value); }
 }
 public void SetVtype(Int32 value) { 
 hasVtype = true;
 vtype_ = value;
 }

public const int gameversionFieldNumber = 2;
 private bool hasGameversion;
 private Int32 gameversion_ = 0;
 public bool HasGameversion {
 get { return hasGameversion; }
 }
 public Int32 Gameversion {
 get { return gameversion_; }
 set { SetGameversion(value); }
 }
 public void SetGameversion(Int32 value) { 
 hasGameversion = true;
 gameversion_ = value;
 }

public const int programversionFieldNumber = 3;
 private bool hasProgramversion;
 private Int32 programversion_ = 0;
 public bool HasProgramversion {
 get { return hasProgramversion; }
 }
 public Int32 Programversion {
 get { return programversion_; }
 set { SetProgramversion(value); }
 }
 public void SetProgramversion(Int32 value) { 
 hasProgramversion = true;
 programversion_ = value;
 }

public const int publicresourceversionFieldNumber = 4;
 private bool hasPublicresourceversion;
 private Int32 publicresourceversion_ = 0;
 public bool HasPublicresourceversion {
 get { return hasPublicresourceversion; }
 }
 public Int32 Publicresourceversion {
 get { return publicresourceversion_; }
 set { SetPublicresourceversion(value); }
 }
 public void SetPublicresourceversion(Int32 value) { 
 hasPublicresourceversion = true;
 publicresourceversion_ = value;
 }

public const int maxpacketidFieldNumber = 5;
 private bool hasMaxpacketid;
 private Int32 maxpacketid_ = 0;
 public bool HasMaxpacketid {
 get { return hasMaxpacketid; }
 }
 public Int32 Maxpacketid {
 get { return maxpacketid_; }
 set { SetMaxpacketid(value); }
 }
 public void SetMaxpacketid(Int32 value) { 
 hasMaxpacketid = true;
 maxpacketid_ = value;
 }

public const int forceenterFieldNumber = 6;
 private bool hasForceenter;
 private Int32 forceenter_ = 0;
 public bool HasForceenter {
 get { return hasForceenter; }
 }
 public Int32 Forceenter {
 get { return forceenter_; }
 set { SetForceenter(value); }
 }
 public void SetForceenter(Int32 value) { 
 hasForceenter = true;
 forceenter_ = value;
 }

public const int deviceidFieldNumber = 7;
 private bool hasDeviceid;
 private string deviceid_ = "";
 public bool HasDeviceid {
 get { return hasDeviceid; }
 }
 public string Deviceid {
 get { return deviceid_; }
 set { SetDeviceid(value); }
 }
 public void SetDeviceid(string value) { 
 hasDeviceid = true;
 deviceid_ = value;
 }

public const int devicetypeFieldNumber = 8;
 private bool hasDevicetype;
 private string devicetype_ = "";
 public bool HasDevicetype {
 get { return hasDevicetype; }
 }
 public string Devicetype {
 get { return devicetype_; }
 set { SetDevicetype(value); }
 }
 public void SetDevicetype(string value) { 
 hasDevicetype = true;
 devicetype_ = value;
 }

public const int deviceversionFieldNumber = 9;
 private bool hasDeviceversion;
 private string deviceversion_ = "";
 public bool HasDeviceversion {
 get { return hasDeviceversion; }
 }
 public string Deviceversion {
 get { return deviceversion_; }
 set { SetDeviceversion(value); }
 }
 public void SetDeviceversion(string value) { 
 hasDeviceversion = true;
 deviceversion_ = value;
 }

public const int accountFieldNumber = 10;
 private bool hasAccount;
 private string account_ = "";
 public bool HasAccount {
 get { return hasAccount; }
 }
 public string Account {
 get { return account_; }
 set { SetAccount(value); }
 }
 public void SetAccount(string value) { 
 hasAccount = true;
 account_ = value;
 }

public const int validateinfoFieldNumber = 11;
 private bool hasValidateinfo;
 private string validateinfo_ = "";
 public bool HasValidateinfo {
 get { return hasValidateinfo; }
 }
 public string Validateinfo {
 get { return validateinfo_; }
 set { SetValidateinfo(value); }
 }
 public void SetValidateinfo(string value) { 
 hasValidateinfo = true;
 validateinfo_ = value;
 }

public const int channelidFieldNumber = 12;
 private bool hasChannelid;
 private string channelid_ = "";
 public bool HasChannelid {
 get { return hasChannelid; }
 }
 public string Channelid {
 get { return channelid_; }
 set { SetChannelid(value); }
 }
 public void SetChannelid(string value) { 
 hasChannelid = true;
 channelid_ = value;
 }

public const int mediachannelFieldNumber = 13;
 private bool hasMediachannel;
 private string mediachannel_ = "";
 public bool HasMediachannel {
 get { return hasMediachannel; }
 }
 public string Mediachannel {
 get { return mediachannel_; }
 set { SetMediachannel(value); }
 }
 public void SetMediachannel(string value) { 
 hasMediachannel = true;
 mediachannel_ = value;
 }

public const int rapidvalidatecodeFieldNumber = 14;
 private bool hasRapidvalidatecode;
 private Int32 rapidvalidatecode_ = 0;
 public bool HasRapidvalidatecode {
 get { return hasRapidvalidatecode; }
 }
 public Int32 Rapidvalidatecode {
 get { return rapidvalidatecode_; }
 set { SetRapidvalidatecode(value); }
 }
 public void SetRapidvalidatecode(Int32 value) { 
 hasRapidvalidatecode = true;
 rapidvalidatecode_ = value;
 }

public const int reservedint1FieldNumber = 15;
 private bool hasReservedint1;
 private Int32 reservedint1_ = 0;
 public bool HasReservedint1 {
 get { return hasReservedint1; }
 }
 public Int32 Reservedint1 {
 get { return reservedint1_; }
 set { SetReservedint1(value); }
 }
 public void SetReservedint1(Int32 value) { 
 hasReservedint1 = true;
 reservedint1_ = value;
 }

public const int reservedint2FieldNumber = 16;
 private bool hasReservedint2;
 private Int32 reservedint2_ = 0;
 public bool HasReservedint2 {
 get { return hasReservedint2; }
 }
 public Int32 Reservedint2 {
 get { return reservedint2_; }
 set { SetReservedint2(value); }
 }
 public void SetReservedint2(Int32 value) { 
 hasReservedint2 = true;
 reservedint2_ = value;
 }

public const int reservedint3FieldNumber = 17;
 private bool hasReservedint3;
 private Int32 reservedint3_ = 0;
 public bool HasReservedint3 {
 get { return hasReservedint3; }
 }
 public Int32 Reservedint3 {
 get { return reservedint3_; }
 set { SetReservedint3(value); }
 }
 public void SetReservedint3(Int32 value) { 
 hasReservedint3 = true;
 reservedint3_ = value;
 }

public const int reservedint4FieldNumber = 18;
 private bool hasReservedint4;
 private Int32 reservedint4_ = 0;
 public bool HasReservedint4 {
 get { return hasReservedint4; }
 }
 public Int32 Reservedint4 {
 get { return reservedint4_; }
 set { SetReservedint4(value); }
 }
 public void SetReservedint4(Int32 value) { 
 hasReservedint4 = true;
 reservedint4_ = value;
 }

public const int reservedstring1FieldNumber = 19;
 private bool hasReservedstring1;
 private string reservedstring1_ = "";
 public bool HasReservedstring1 {
 get { return hasReservedstring1; }
 }
 public string Reservedstring1 {
 get { return reservedstring1_; }
 set { SetReservedstring1(value); }
 }
 public void SetReservedstring1(string value) { 
 hasReservedstring1 = true;
 reservedstring1_ = value;
 }

public const int reservedstring2FieldNumber = 20;
 private bool hasReservedstring2;
 private string reservedstring2_ = "";
 public bool HasReservedstring2 {
 get { return hasReservedstring2; }
 }
 public string Reservedstring2 {
 get { return reservedstring2_; }
 set { SetReservedstring2(value); }
 }
 public void SetReservedstring2(string value) { 
 hasReservedstring2 = true;
 reservedstring2_ = value;
 }

public const int reservedstring3FieldNumber = 21;
 private bool hasReservedstring3;
 private string reservedstring3_ = "";
 public bool HasReservedstring3 {
 get { return hasReservedstring3; }
 }
 public string Reservedstring3 {
 get { return reservedstring3_; }
 set { SetReservedstring3(value); }
 }
 public void SetReservedstring3(string value) { 
 hasReservedstring3 = true;
 reservedstring3_ = value;
 }

public const int reservedstring4FieldNumber = 22;
 private bool hasReservedstring4;
 private string reservedstring4_ = "";
 public bool HasReservedstring4 {
 get { return hasReservedstring4; }
 }
 public string Reservedstring4 {
 get { return reservedstring4_; }
 set { SetReservedstring4(value); }
 }
 public void SetReservedstring4(string value) { 
 hasReservedstring4 = true;
 reservedstring4_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasVtype) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Vtype);
}
 if (HasGameversion) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Gameversion);
}
 if (HasProgramversion) {
size += pb::CodedOutputStream.ComputeInt32Size(3, Programversion);
}
 if (HasPublicresourceversion) {
size += pb::CodedOutputStream.ComputeInt32Size(4, Publicresourceversion);
}
 if (HasMaxpacketid) {
size += pb::CodedOutputStream.ComputeInt32Size(5, Maxpacketid);
}
 if (HasForceenter) {
size += pb::CodedOutputStream.ComputeInt32Size(6, Forceenter);
}
 if (HasDeviceid) {
size += pb::CodedOutputStream.ComputeStringSize(7, Deviceid);
}
 if (HasDevicetype) {
size += pb::CodedOutputStream.ComputeStringSize(8, Devicetype);
}
 if (HasDeviceversion) {
size += pb::CodedOutputStream.ComputeStringSize(9, Deviceversion);
}
 if (HasAccount) {
size += pb::CodedOutputStream.ComputeStringSize(10, Account);
}
 if (HasValidateinfo) {
size += pb::CodedOutputStream.ComputeStringSize(11, Validateinfo);
}
 if (HasChannelid) {
size += pb::CodedOutputStream.ComputeStringSize(12, Channelid);
}
 if (HasMediachannel) {
size += pb::CodedOutputStream.ComputeStringSize(13, Mediachannel);
}
 if (HasRapidvalidatecode) {
size += pb::CodedOutputStream.ComputeInt32Size(14, Rapidvalidatecode);
}
 if (HasReservedint1) {
size += pb::CodedOutputStream.ComputeInt32Size(15, Reservedint1);
}
 if (HasReservedint2) {
size += pb::CodedOutputStream.ComputeInt32Size(16, Reservedint2);
}
 if (HasReservedint3) {
size += pb::CodedOutputStream.ComputeInt32Size(17, Reservedint3);
}
 if (HasReservedint4) {
size += pb::CodedOutputStream.ComputeInt32Size(18, Reservedint4);
}
 if (HasReservedstring1) {
size += pb::CodedOutputStream.ComputeStringSize(19, Reservedstring1);
}
 if (HasReservedstring2) {
size += pb::CodedOutputStream.ComputeStringSize(20, Reservedstring2);
}
 if (HasReservedstring3) {
size += pb::CodedOutputStream.ComputeStringSize(21, Reservedstring3);
}
 if (HasReservedstring4) {
size += pb::CodedOutputStream.ComputeStringSize(22, Reservedstring4);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasVtype) {
output.WriteInt32(1, Vtype);
}
 
if (HasGameversion) {
output.WriteInt32(2, Gameversion);
}
 
if (HasProgramversion) {
output.WriteInt32(3, Programversion);
}
 
if (HasPublicresourceversion) {
output.WriteInt32(4, Publicresourceversion);
}
 
if (HasMaxpacketid) {
output.WriteInt32(5, Maxpacketid);
}
 
if (HasForceenter) {
output.WriteInt32(6, Forceenter);
}
 
if (HasDeviceid) {
output.WriteString(7, Deviceid);
}
 
if (HasDevicetype) {
output.WriteString(8, Devicetype);
}
 
if (HasDeviceversion) {
output.WriteString(9, Deviceversion);
}
 
if (HasAccount) {
output.WriteString(10, Account);
}
 
if (HasValidateinfo) {
output.WriteString(11, Validateinfo);
}
 
if (HasChannelid) {
output.WriteString(12, Channelid);
}
 
if (HasMediachannel) {
output.WriteString(13, Mediachannel);
}
 
if (HasRapidvalidatecode) {
output.WriteInt32(14, Rapidvalidatecode);
}
 
if (HasReservedint1) {
output.WriteInt32(15, Reservedint1);
}
 
if (HasReservedint2) {
output.WriteInt32(16, Reservedint2);
}
 
if (HasReservedint3) {
output.WriteInt32(17, Reservedint3);
}
 
if (HasReservedint4) {
output.WriteInt32(18, Reservedint4);
}
 
if (HasReservedstring1) {
output.WriteString(19, Reservedstring1);
}
 
if (HasReservedstring2) {
output.WriteString(20, Reservedstring2);
}
 
if (HasReservedstring3) {
output.WriteString(21, Reservedstring3);
}
 
if (HasReservedstring4) {
output.WriteString(22, Reservedstring4);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_LOGIN _inst = (CG_LOGIN) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Vtype = input.ReadInt32();
break;
}
   case  16: {
 _inst.Gameversion = input.ReadInt32();
break;
}
   case  24: {
 _inst.Programversion = input.ReadInt32();
break;
}
   case  32: {
 _inst.Publicresourceversion = input.ReadInt32();
break;
}
   case  40: {
 _inst.Maxpacketid = input.ReadInt32();
break;
}
   case  48: {
 _inst.Forceenter = input.ReadInt32();
break;
}
   case  58: {
 _inst.Deviceid = input.ReadString();
break;
}
   case  66: {
 _inst.Devicetype = input.ReadString();
break;
}
   case  74: {
 _inst.Deviceversion = input.ReadString();
break;
}
   case  82: {
 _inst.Account = input.ReadString();
break;
}
   case  90: {
 _inst.Validateinfo = input.ReadString();
break;
}
   case  98: {
 _inst.Channelid = input.ReadString();
break;
}
   case  106: {
 _inst.Mediachannel = input.ReadString();
break;
}
   case  112: {
 _inst.Rapidvalidatecode = input.ReadInt32();
break;
}
   case  120: {
 _inst.Reservedint1 = input.ReadInt32();
break;
}
   case  128: {
 _inst.Reservedint2 = input.ReadInt32();
break;
}
   case  136: {
 _inst.Reservedint3 = input.ReadInt32();
break;
}
   case  144: {
 _inst.Reservedint4 = input.ReadInt32();
break;
}
   case  154: {
 _inst.Reservedstring1 = input.ReadString();
break;
}
   case  162: {
 _inst.Reservedstring2 = input.ReadString();
break;
}
   case  170: {
 _inst.Reservedstring3 = input.ReadString();
break;
}
   case  178: {
 _inst.Reservedstring4 = input.ReadString();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasVtype) return false;
 if (!hasGameversion) return false;
 if (!hasProgramversion) return false;
 if (!hasPublicresourceversion) return false;
 if (!hasMaxpacketid) return false;
 if (!hasForceenter) return false;
 if (!hasDeviceid) return false;
 if (!hasDevicetype) return false;
 if (!hasDeviceversion) return false;
 if (!hasAccount) return false;
 if (!hasValidateinfo) return false;
 if (!hasChannelid) return false;
 if (!hasMediachannel) return false;
 if (!hasRapidvalidatecode) return false;
 if (!hasReservedint1) return false;
 if (!hasReservedint2) return false;
 if (!hasReservedint3) return false;
 if (!hasReservedint4) return false;
 if (!hasReservedstring1) return false;
 if (!hasReservedstring2) return false;
 if (!hasReservedstring3) return false;
 if (!hasReservedstring4) return false;
 return true;
 }

}


[Serializable]
public class GC_LOGIN_RET : PacketDistributed
{
public enum LOGINRESULT 
 { 
  SUCCESS      = 1, 
  ACCOUNTVERIFYFAIL = 2, 
  READROLELISTFAIL = 3, 
  ALREADYLOGIN  = 4, 
  QUEUEFULL  = 5, 
  NEEDFORCEENTER = 6, 
  PACKETNOTMATCH = 7, 
  VERSIONNOTMATCH = 8, 
 }public enum VALIDATERESULT 
 { 
  OK           = 0, 
  FAIL_VALIDATETYPEERROR = 1, 
  FAIL_PERFORM      = 2, 
  FAIL_OPCODE       = 3, 
  FAIL_TAG        = 4, 
  FAIL_STATE       = 5, 
  FAIL_DATA_STATUS    = 6, 
  FAIL_CHANNELID     = 7, 
  FAIL_BLOCKED     = 8, 
 }
public const int resultFieldNumber = 1;
 private bool hasResult;
 private Int32 result_ = 0;
 public bool HasResult {
 get { return hasResult; }
 }
 public Int32 Result {
 get { return result_; }
 set { SetResult(value); }
 }
 public void SetResult(Int32 value) { 
 hasResult = true;
 result_ = value;
 }

public const int validateresultFieldNumber = 2;
 private bool hasValidateresult;
 private Int32 validateresult_ = 0;
 public bool HasValidateresult {
 get { return hasValidateresult; }
 }
 public Int32 Validateresult {
 get { return validateresult_; }
 set { SetValidateresult(value); }
 }
 public void SetValidateresult(Int32 value) { 
 hasValidateresult = true;
 validateresult_ = value;
 }

public const int useridFieldNumber = 3;
 private bool hasUserid;
 private string userid_ = "";
 public bool HasUserid {
 get { return hasUserid; }
 }
 public string Userid {
 get { return userid_; }
 set { SetUserid(value); }
 }
 public void SetUserid(string value) { 
 hasUserid = true;
 userid_ = value;
 }

public const int oidFieldNumber = 4;
 private bool hasOid;
 private string oid_ = "";
 public bool HasOid {
 get { return hasOid; }
 }
 public string Oid {
 get { return oid_; }
 set { SetOid(value); }
 }
 public void SetOid(string value) { 
 hasOid = true;
 oid_ = value;
 }

public const int accesstokenFieldNumber = 5;
 private bool hasAccesstoken;
 private string accesstoken_ = "";
 public bool HasAccesstoken {
 get { return hasAccesstoken; }
 }
 public string Accesstoken {
 get { return accesstoken_; }
 set { SetAccesstoken(value); }
 }
 public void SetAccesstoken(string value) { 
 hasAccesstoken = true;
 accesstoken_ = value;
 }

public const int rapidvalidatecodeFieldNumber = 6;
 private bool hasRapidvalidatecode;
 private Int32 rapidvalidatecode_ = 0;
 public bool HasRapidvalidatecode {
 get { return hasRapidvalidatecode; }
 }
 public Int32 Rapidvalidatecode {
 get { return rapidvalidatecode_; }
 set { SetRapidvalidatecode(value); }
 }
 public void SetRapidvalidatecode(Int32 value) { 
 hasRapidvalidatecode = true;
 rapidvalidatecode_ = value;
 }

public const int roleGUIDListFieldNumber = 7;
 private pbc::PopsicleList<UInt64> roleGUIDList_ = new pbc::PopsicleList<UInt64>();
 public scg::IList<UInt64> roleGUIDListList {
 get { return pbc::Lists.AsReadOnly(roleGUIDList_); }
 }
 
 public int roleGUIDListCount {
 get { return roleGUIDList_.Count; }
 }
 
public UInt64 GetRoleGUIDList(int index) {
 return roleGUIDList_[index];
 }
 public void AddRoleGUIDList(UInt64 value) {
 roleGUIDList_.Add(value);
 }

public const int roleTypeListFieldNumber = 8;
 private pbc::PopsicleList<Int32> roleTypeList_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> roleTypeListList {
 get { return pbc::Lists.AsReadOnly(roleTypeList_); }
 }
 
 public int roleTypeListCount {
 get { return roleTypeList_.Count; }
 }
 
public Int32 GetRoleTypeList(int index) {
 return roleTypeList_[index];
 }
 public void AddRoleTypeList(Int32 value) {
 roleTypeList_.Add(value);
 }

public const int playerNameListFieldNumber = 9;
 private pbc::PopsicleList<string> playerNameList_ = new pbc::PopsicleList<string>();
 public scg::IList<string> playerNameListList {
 get { return pbc::Lists.AsReadOnly(playerNameList_); }
 }
 
 public int playerNameListCount {
 get { return playerNameList_.Count; }
 }
 
public string GetPlayerNameList(int index) {
 return playerNameList_[index];
 }
 public void AddPlayerNameList(string value) {
 playerNameList_.Add(value);
 }

public const int roleLevelListFieldNumber = 10;
 private pbc::PopsicleList<Int32> roleLevelList_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> roleLevelListList {
 get { return pbc::Lists.AsReadOnly(roleLevelList_); }
 }
 
 public int roleLevelListCount {
 get { return roleLevelList_.Count; }
 }
 
public Int32 GetRoleLevelList(int index) {
 return roleLevelList_[index];
 }
 public void AddRoleLevelList(Int32 value) {
 roleLevelList_.Add(value);
 }

public const int ModelVisualIDFieldNumber = 11;
 private pbc::PopsicleList<Int32> ModelVisualID_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> ModelVisualIDList {
 get { return pbc::Lists.AsReadOnly(ModelVisualID_); }
 }
 
 public int ModelVisualIDCount {
 get { return ModelVisualID_.Count; }
 }
 
public Int32 GetModelVisualID(int index) {
 return ModelVisualID_[index];
 }
 public void AddModelVisualID(Int32 value) {
 ModelVisualID_.Add(value);
 }

public const int WeaponIDFieldNumber = 12;
 private pbc::PopsicleList<Int32> WeaponID_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> WeaponIDList {
 get { return pbc::Lists.AsReadOnly(WeaponID_); }
 }
 
 public int WeaponIDCount {
 get { return WeaponID_.Count; }
 }
 
public Int32 GetWeaponID(int index) {
 return WeaponID_[index];
 }
 public void AddWeaponID(Int32 value) {
 WeaponID_.Add(value);
 }

public const int WeaponEffectGemFieldNumber = 13;
 private pbc::PopsicleList<Int32> WeaponEffectGem_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> WeaponEffectGemList {
 get { return pbc::Lists.AsReadOnly(WeaponEffectGem_); }
 }
 
 public int WeaponEffectGemCount {
 get { return WeaponEffectGem_.Count; }
 }
 
public Int32 GetWeaponEffectGem(int index) {
 return WeaponEffectGem_[index];
 }
 public void AddWeaponEffectGem(Int32 value) {
 WeaponEffectGem_.Add(value);
 }

public const int HuanHuaWeaponModelFieldNumber = 14;
 private pbc::PopsicleList<Int32> HuanHuaWeaponModel_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> HuanHuaWeaponModelList {
 get { return pbc::Lists.AsReadOnly(HuanHuaWeaponModel_); }
 }
 
 public int HuanHuaWeaponModelCount {
 get { return HuanHuaWeaponModel_.Count; }
 }
 
public Int32 GetHuanHuaWeaponModel(int index) {
 return HuanHuaWeaponModel_[index];
 }
 public void AddHuanHuaWeaponModel(Int32 value) {
 HuanHuaWeaponModel_.Add(value);
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasResult) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Result);
}
 if (HasValidateresult) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Validateresult);
}
 if (HasUserid) {
size += pb::CodedOutputStream.ComputeStringSize(3, Userid);
}
 if (HasOid) {
size += pb::CodedOutputStream.ComputeStringSize(4, Oid);
}
 if (HasAccesstoken) {
size += pb::CodedOutputStream.ComputeStringSize(5, Accesstoken);
}
 if (HasRapidvalidatecode) {
size += pb::CodedOutputStream.ComputeInt32Size(6, Rapidvalidatecode);
}
{
int dataSize = 0;
for(int i=0; i<roleGUIDListList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeUInt64SizeNoTag(roleGUIDListList[i]);
}
size += dataSize;
size += 1 * roleGUIDList_.Count;
}
{
int dataSize = 0;
for(int i=0; i<roleTypeListList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(roleTypeListList[i]);
}
size += dataSize;
size += 1 * roleTypeList_.Count;
}
{
int dataSize = 0;
for(int i=0; i<playerNameListList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeStringSizeNoTag(playerNameListList[i]);
}
size += dataSize;
size += 1 * playerNameList_.Count;
}
{
int dataSize = 0;
for(int i=0; i<roleLevelListList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(roleLevelListList[i]);
}
size += dataSize;
size += 1 * roleLevelList_.Count;
}
{
int dataSize = 0;
for(int i=0; i<ModelVisualIDList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(ModelVisualIDList[i]);
}
size += dataSize;
size += 1 * ModelVisualID_.Count;
}
{
int dataSize = 0;
for(int i=0; i<WeaponIDList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(WeaponIDList[i]);
}
size += dataSize;
size += 1 * WeaponID_.Count;
}
{
int dataSize = 0;
for(int i=0; i<WeaponEffectGemList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(WeaponEffectGemList[i]);
}
size += dataSize;
size += 1 * WeaponEffectGem_.Count;
}
{
int dataSize = 0;
for(int i=0; i<HuanHuaWeaponModelList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(HuanHuaWeaponModelList[i]);
}
size += dataSize;
size += 1 * HuanHuaWeaponModel_.Count;
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasResult) {
output.WriteInt32(1, Result);
}
 
if (HasValidateresult) {
output.WriteInt32(2, Validateresult);
}
 
if (HasUserid) {
output.WriteString(3, Userid);
}
 
if (HasOid) {
output.WriteString(4, Oid);
}
 
if (HasAccesstoken) {
output.WriteString(5, Accesstoken);
}
 
if (HasRapidvalidatecode) {
output.WriteInt32(6, Rapidvalidatecode);
}
{
if (roleGUIDList_.Count > 0) {
for(int i=0; i<roleGUIDList_.Count; ++i){
output.WriteUInt64(7,roleGUIDList_[i]);
}
}

}
{
if (roleTypeList_.Count > 0) {
for(int i=0; i<roleTypeList_.Count; ++i){
output.WriteInt32(8,roleTypeList_[i]);
}
}

}
{
if (playerNameList_.Count > 0) {
for(int i=0; i<playerNameList_.Count; ++i){
output.WriteString(9,playerNameList_[i]);
}
}

}
{
if (roleLevelList_.Count > 0) {
for(int i=0; i<roleLevelList_.Count; ++i){
output.WriteInt32(10,roleLevelList_[i]);
}
}

}
{
if (ModelVisualID_.Count > 0) {
for(int i=0; i<ModelVisualID_.Count; ++i){
output.WriteInt32(11,ModelVisualID_[i]);
}
}

}
{
if (WeaponID_.Count > 0) {
for(int i=0; i<WeaponID_.Count; ++i){
output.WriteInt32(12,WeaponID_[i]);
}
}

}
{
if (WeaponEffectGem_.Count > 0) {
for(int i=0; i<WeaponEffectGem_.Count; ++i){
output.WriteInt32(13,WeaponEffectGem_[i]);
}
}

}
{
if (HuanHuaWeaponModel_.Count > 0) {
for(int i=0; i<HuanHuaWeaponModel_.Count; ++i){
output.WriteInt32(14,HuanHuaWeaponModel_[i]);
}
}

}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_LOGIN_RET _inst = (GC_LOGIN_RET) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Result = input.ReadInt32();
break;
}
   case  16: {
 _inst.Validateresult = input.ReadInt32();
break;
}
   case  26: {
 _inst.Userid = input.ReadString();
break;
}
   case  34: {
 _inst.Oid = input.ReadString();
break;
}
   case  42: {
 _inst.Accesstoken = input.ReadString();
break;
}
   case  48: {
 _inst.Rapidvalidatecode = input.ReadInt32();
break;
}
   case  56: {
 _inst.AddRoleGUIDList(input.ReadUInt64());
break;
}
   case  64: {
 _inst.AddRoleTypeList(input.ReadInt32());
break;
}
   case  74: {
 _inst.AddPlayerNameList(input.ReadString());
break;
}
   case  80: {
 _inst.AddRoleLevelList(input.ReadInt32());
break;
}
   case  88: {
 _inst.AddModelVisualID(input.ReadInt32());
break;
}
   case  96: {
 _inst.AddWeaponID(input.ReadInt32());
break;
}
   case  104: {
 _inst.AddWeaponEffectGem(input.ReadInt32());
break;
}
   case  112: {
 _inst.AddHuanHuaWeaponModel(input.ReadInt32());
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasResult) return false;
 if (!hasValidateresult) return false;
 if (!hasUserid) return false;
 if (!hasOid) return false;
 if (!hasAccesstoken) return false;
 if (!hasRapidvalidatecode) return false;
 return true;
 }

}


[Serializable]
public class CG_CONNECTED_HEARTBEAT : PacketDistributed
{

public const int isresponseFieldNumber = 1;
 private bool hasIsresponse;
 private Int32 isresponse_ = 0;
 public bool HasIsresponse {
 get { return hasIsresponse; }
 }
 public Int32 Isresponse {
 get { return isresponse_; }
 set { SetIsresponse(value); }
 }
 public void SetIsresponse(Int32 value) { 
 hasIsresponse = true;
 isresponse_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasIsresponse) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Isresponse);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasIsresponse) {
output.WriteInt32(1, Isresponse);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_CONNECTED_HEARTBEAT _inst = (CG_CONNECTED_HEARTBEAT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Isresponse = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasIsresponse) return false;
 return true;
 }

}


[Serializable]
public class GC_CONNECTED_HEARTBEAT : PacketDistributed
{

public const int serveransitimeFieldNumber = 1;
 private bool hasServeransitime;
 private Int32 serveransitime_ = 0;
 public bool HasServeransitime {
 get { return hasServeransitime; }
 }
 public Int32 Serveransitime {
 get { return serveransitime_; }
 set { SetServeransitime(value); }
 }
 public void SetServeransitime(Int32 value) { 
 hasServeransitime = true;
 serveransitime_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasServeransitime) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Serveransitime);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasServeransitime) {
output.WriteInt32(1, Serveransitime);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_CONNECTED_HEARTBEAT _inst = (GC_CONNECTED_HEARTBEAT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Serveransitime = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasServeransitime) return false;
 return true;
 }

}


[Serializable]
public class CG_REQ_NEAR_LIST : PacketDistributed
{

public const int marchIdFieldNumber = 1;
 private bool hasMarchId;
 private Int64 marchId_ = 0;
 public bool HasMarchId {
 get { return hasMarchId; }
 }
 public Int64 MarchId {
 get { return marchId_; }
 set { SetMarchId(value); }
 }
 public void SetMarchId(Int64 value) { 
 hasMarchId = true;
 marchId_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasMarchId) {
size += pb::CodedOutputStream.ComputeInt64Size(1, MarchId);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasMarchId) {
output.WriteInt64(1, MarchId);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_REQ_NEAR_LIST _inst = (CG_REQ_NEAR_LIST) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.MarchId = input.ReadInt64();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasMarchId) return false;
 return true;
 }

}


[Serializable]
public class GC_NEAR_MARCHLIST : PacketDistributed
{

public const int GuidFieldNumber = 1;
 private pbc::PopsicleList<UInt64> Guid_ = new pbc::PopsicleList<UInt64>();
 public scg::IList<UInt64> GuidList {
 get { return pbc::Lists.AsReadOnly(Guid_); }
 }
 
 public int GuidCount {
 get { return Guid_.Count; }
 }
 
public UInt64 GetGuid(int index) {
 return Guid_[index];
 }
 public void AddGuid(UInt64 value) {
 Guid_.Add(value);
 }

public const int NameFieldNumber = 2;
 private pbc::PopsicleList<string> Name_ = new pbc::PopsicleList<string>();
 public scg::IList<string> NameList {
 get { return pbc::Lists.AsReadOnly(Name_); }
 }
 
 public int NameCount {
 get { return Name_.Count; }
 }
 
public string GetName(int index) {
 return Name_[index];
 }
 public void AddName(string value) {
 Name_.Add(value);
 }

public const int LevelFieldNumber = 3;
 private pbc::PopsicleList<Int32> Level_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> LevelList {
 get { return pbc::Lists.AsReadOnly(Level_); }
 }
 
 public int LevelCount {
 get { return Level_.Count; }
 }
 
public Int32 GetLevel(int index) {
 return Level_[index];
 }
 public void AddLevel(Int32 value) {
 Level_.Add(value);
 }

public const int CombatNumFieldNumber = 4;
 private pbc::PopsicleList<Int32> CombatNum_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> CombatNumList {
 get { return pbc::Lists.AsReadOnly(CombatNum_); }
 }
 
 public int CombatNumCount {
 get { return CombatNum_.Count; }
 }
 
public Int32 GetCombatNum(int index) {
 return CombatNum_[index];
 }
 public void AddCombatNum(Int32 value) {
 CombatNum_.Add(value);
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
 {
int dataSize = 0;
for(int i=0; i<GuidList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeUInt64SizeNoTag(GuidList[i]);
}
size += dataSize;
size += 1 * Guid_.Count;
}
{
int dataSize = 0;
for(int i=0; i<NameList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeStringSizeNoTag(NameList[i]);
}
size += dataSize;
size += 1 * Name_.Count;
}
{
int dataSize = 0;
for(int i=0; i<LevelList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(LevelList[i]);
}
size += dataSize;
size += 1 * Level_.Count;
}
{
int dataSize = 0;
for(int i=0; i<CombatNumList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(CombatNumList[i]);
}
size += dataSize;
size += 1 * CombatNum_.Count;
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
 {
if (Guid_.Count > 0) {
for(int i=0; i<Guid_.Count; ++i){
output.WriteUInt64(1,Guid_[i]);
}
}

}
{
if (Name_.Count > 0) {
for(int i=0; i<Name_.Count; ++i){
output.WriteString(2,Name_[i]);
}
}

}
{
if (Level_.Count > 0) {
for(int i=0; i<Level_.Count; ++i){
output.WriteInt32(3,Level_[i]);
}
}

}
{
if (CombatNum_.Count > 0) {
for(int i=0; i<CombatNum_.Count; ++i){
output.WriteInt32(4,CombatNum_[i]);
}
}

}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_NEAR_MARCHLIST _inst = (GC_NEAR_MARCHLIST) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.AddGuid(input.ReadUInt64());
break;
}
   case  18: {
 _inst.AddName(input.ReadString());
break;
}
   case  24: {
 _inst.AddLevel(input.ReadInt32());
break;
}
   case  32: {
 _inst.AddCombatNum(input.ReadInt32());
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  return true;
 }

}


[Serializable]
public class CG_CHAT : PacketDistributed
{
public enum CHATTYPE 
 { 
  CHAT_TYPE_INVALID    = 0, 
  CHAT_TYPE_NORMAL     = 1,  // 附近频道 
  CHAT_TYPE_WORLD     = 2,  // 世界频道 
  CHAT_TYPE_SYSTEM    = 3,  // 系统频道 
  CHAT_TYPE_LOUDSPEAKER  = 4,  // 小喇叭 
  CHAT_TYPE_FRIEND    = 5,  // 好友频道 
 }
public const int chattypeFieldNumber = 1;
 private bool hasChattype;
 private Int32 chattype_ = 0;
 public bool HasChattype {
 get { return hasChattype; }
 }
 public Int32 Chattype {
 get { return chattype_; }
 set { SetChattype(value); }
 }
 public void SetChattype(Int32 value) { 
 hasChattype = true;
 chattype_ = value;
 }

public const int chatinfoFieldNumber = 2;
 private bool hasChatinfo;
 private string chatinfo_ = "";
 public bool HasChatinfo {
 get { return hasChatinfo; }
 }
 public string Chatinfo {
 get { return chatinfo_; }
 set { SetChatinfo(value); }
 }
 public void SetChatinfo(string value) { 
 hasChatinfo = true;
 chatinfo_ = value;
 }

public const int receiverguidFieldNumber = 3;
 private bool hasReceiverguid;
 private UInt64 receiverguid_ = 0;
 public bool HasReceiverguid {
 get { return hasReceiverguid; }
 }
 public UInt64 Receiverguid {
 get { return receiverguid_; }
 set { SetReceiverguid(value); }
 }
 public void SetReceiverguid(UInt64 value) { 
 hasReceiverguid = true;
 receiverguid_ = value;
 }

public const int receivernameFieldNumber = 4;
 private bool hasReceivername;
 private string receivername_ = "";
 public bool HasReceivername {
 get { return hasReceivername; }
 }
 public string Receivername {
 get { return receivername_; }
 set { SetReceivername(value); }
 }
 public void SetReceivername(string value) { 
 hasReceivername = true;
 receivername_ = value;
 }

public const int receiverlevelFieldNumber = 5;
 private bool hasReceiverlevel;
 private Int32 receiverlevel_ = 0;
 public bool HasReceiverlevel {
 get { return hasReceiverlevel; }
 }
 public Int32 Receiverlevel {
 get { return receiverlevel_; }
 set { SetReceiverlevel(value); }
 }
 public void SetReceiverlevel(Int32 value) { 
 hasReceiverlevel = true;
 receiverlevel_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasChattype) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Chattype);
}
 if (HasChatinfo) {
size += pb::CodedOutputStream.ComputeStringSize(2, Chatinfo);
}
 if (HasReceiverguid) {
size += pb::CodedOutputStream.ComputeUInt64Size(3, Receiverguid);
}
 if (HasReceivername) {
size += pb::CodedOutputStream.ComputeStringSize(4, Receivername);
}
 if (HasReceiverlevel) {
size += pb::CodedOutputStream.ComputeInt32Size(5, Receiverlevel);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasChattype) {
output.WriteInt32(1, Chattype);
}
 
if (HasChatinfo) {
output.WriteString(2, Chatinfo);
}
 
if (HasReceiverguid) {
output.WriteUInt64(3, Receiverguid);
}
 
if (HasReceivername) {
output.WriteString(4, Receivername);
}
 
if (HasReceiverlevel) {
output.WriteInt32(5, Receiverlevel);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_CHAT _inst = (CG_CHAT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Chattype = input.ReadInt32();
break;
}
   case  18: {
 _inst.Chatinfo = input.ReadString();
break;
}
   case  24: {
 _inst.Receiverguid = input.ReadUInt64();
break;
}
   case  34: {
 _inst.Receivername = input.ReadString();
break;
}
   case  40: {
 _inst.Receiverlevel = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasChattype) return false;
 if (!hasChatinfo) return false;
 return true;
 }

}


[Serializable]
public class GC_CHAT : PacketDistributed
{
public enum CHATTYPE 
 { 
  CHAT_TYPE_INVALID    = 0, 
  CHAT_TYPE_NORMAL     = 1,  // 附近频道 
  CHAT_TYPE_WORLD     = 2,  // 世界频道 
  CHAT_TYPE_SYSTEM    = 3,  // 系统频道 
  CHAT_TYPE_LOUDSPEAKER  = 4,  // 小喇叭 
  CHAT_TYPE_FRIEND    = 5,  // 好友频道 
 }
public const int chattypeFieldNumber = 1;
 private bool hasChattype;
 private Int32 chattype_ = 0;
 public bool HasChattype {
 get { return hasChattype; }
 }
 public Int32 Chattype {
 get { return chattype_; }
 set { SetChattype(value); }
 }
 public void SetChattype(Int32 value) { 
 hasChattype = true;
 chattype_ = value;
 }

public const int chatinfoFieldNumber = 2;
 private bool hasChatinfo;
 private string chatinfo_ = "";
 public bool HasChatinfo {
 get { return hasChatinfo; }
 }
 public string Chatinfo {
 get { return chatinfo_; }
 set { SetChatinfo(value); }
 }
 public void SetChatinfo(string value) { 
 hasChatinfo = true;
 chatinfo_ = value;
 }

public const int senderguidFieldNumber = 3;
 private bool hasSenderguid;
 private UInt64 senderguid_ = 0;
 public bool HasSenderguid {
 get { return hasSenderguid; }
 }
 public UInt64 Senderguid {
 get { return senderguid_; }
 set { SetSenderguid(value); }
 }
 public void SetSenderguid(UInt64 value) { 
 hasSenderguid = true;
 senderguid_ = value;
 }

public const int sendernameFieldNumber = 4;
 private bool hasSendername;
 private string sendername_ = "";
 public bool HasSendername {
 get { return hasSendername; }
 }
 public string Sendername {
 get { return sendername_; }
 set { SetSendername(value); }
 }
 public void SetSendername(string value) { 
 hasSendername = true;
 sendername_ = value;
 }

public const int senderlevelFieldNumber = 5;
 private bool hasSenderlevel;
 private Int32 senderlevel_ = 0;
 public bool HasSenderlevel {
 get { return hasSenderlevel; }
 }
 public Int32 Senderlevel {
 get { return senderlevel_; }
 set { SetSenderlevel(value); }
 }
 public void SetSenderlevel(Int32 value) { 
 hasSenderlevel = true;
 senderlevel_ = value;
 }

public const int receiverguidFieldNumber = 6;
 private bool hasReceiverguid;
 private UInt64 receiverguid_ = 0;
 public bool HasReceiverguid {
 get { return hasReceiverguid; }
 }
 public UInt64 Receiverguid {
 get { return receiverguid_; }
 set { SetReceiverguid(value); }
 }
 public void SetReceiverguid(UInt64 value) { 
 hasReceiverguid = true;
 receiverguid_ = value;
 }

public const int receivernameFieldNumber = 7;
 private bool hasReceivername;
 private string receivername_ = "";
 public bool HasReceivername {
 get { return hasReceivername; }
 }
 public string Receivername {
 get { return receivername_; }
 set { SetReceivername(value); }
 }
 public void SetReceivername(string value) { 
 hasReceivername = true;
 receivername_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasChattype) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Chattype);
}
 if (HasChatinfo) {
size += pb::CodedOutputStream.ComputeStringSize(2, Chatinfo);
}
 if (HasSenderguid) {
size += pb::CodedOutputStream.ComputeUInt64Size(3, Senderguid);
}
 if (HasSendername) {
size += pb::CodedOutputStream.ComputeStringSize(4, Sendername);
}
 if (HasSenderlevel) {
size += pb::CodedOutputStream.ComputeInt32Size(5, Senderlevel);
}
 if (HasReceiverguid) {
size += pb::CodedOutputStream.ComputeUInt64Size(6, Receiverguid);
}
 if (HasReceivername) {
size += pb::CodedOutputStream.ComputeStringSize(7, Receivername);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasChattype) {
output.WriteInt32(1, Chattype);
}
 
if (HasChatinfo) {
output.WriteString(2, Chatinfo);
}
 
if (HasSenderguid) {
output.WriteUInt64(3, Senderguid);
}
 
if (HasSendername) {
output.WriteString(4, Sendername);
}
 
if (HasSenderlevel) {
output.WriteInt32(5, Senderlevel);
}
 
if (HasReceiverguid) {
output.WriteUInt64(6, Receiverguid);
}
 
if (HasReceivername) {
output.WriteString(7, Receivername);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_CHAT _inst = (GC_CHAT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Chattype = input.ReadInt32();
break;
}
   case  18: {
 _inst.Chatinfo = input.ReadString();
break;
}
   case  24: {
 _inst.Senderguid = input.ReadUInt64();
break;
}
   case  34: {
 _inst.Sendername = input.ReadString();
break;
}
   case  40: {
 _inst.Senderlevel = input.ReadInt32();
break;
}
   case  48: {
 _inst.Receiverguid = input.ReadUInt64();
break;
}
   case  58: {
 _inst.Receivername = input.ReadString();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasChattype) return false;
 if (!hasChatinfo) return false;
 return true;
 }

}


[Serializable]
public class GC_NOTICE : PacketDistributed
{

public const int noticeFieldNumber = 1;
 private bool hasNotice;
 private string notice_ = "";
 public bool HasNotice {
 get { return hasNotice; }
 }
 public string Notice {
 get { return notice_; }
 set { SetNotice(value); }
 }
 public void SetNotice(string value) { 
 hasNotice = true;
 notice_ = value;
 }

public const int filterRepeatFieldNumber = 2;
 private bool hasFilterRepeat;
 private Int32 filterRepeat_ = 0;
 public bool HasFilterRepeat {
 get { return hasFilterRepeat; }
 }
 public Int32 FilterRepeat {
 get { return filterRepeat_; }
 set { SetFilterRepeat(value); }
 }
 public void SetFilterRepeat(Int32 value) { 
 hasFilterRepeat = true;
 filterRepeat_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasNotice) {
size += pb::CodedOutputStream.ComputeStringSize(1, Notice);
}
 if (HasFilterRepeat) {
size += pb::CodedOutputStream.ComputeInt32Size(2, FilterRepeat);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasNotice) {
output.WriteString(1, Notice);
}
 
if (HasFilterRepeat) {
output.WriteInt32(2, FilterRepeat);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_NOTICE _inst = (GC_NOTICE) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  10: {
 _inst.Notice = input.ReadString();
break;
}
   case  16: {
 _inst.FilterRepeat = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasNotice) return false;
 return true;
 }

}


[Serializable]
public class GC_UPDATE_SCENE_INSTACTIVATION : PacketDistributed
{

public const int sceneclassidFieldNumber = 1;
 private bool hasSceneclassid;
 private Int32 sceneclassid_ = 0;
 public bool HasSceneclassid {
 get { return hasSceneclassid; }
 }
 public Int32 Sceneclassid {
 get { return sceneclassid_; }
 set { SetSceneclassid(value); }
 }
 public void SetSceneclassid(Int32 value) { 
 hasSceneclassid = true;
 sceneclassid_ = value;
 }

public const int sceneinstcountFieldNumber = 2;
 private bool hasSceneinstcount;
 private Int32 sceneinstcount_ = 0;
 public bool HasSceneinstcount {
 get { return hasSceneinstcount; }
 }
 public Int32 Sceneinstcount {
 get { return sceneinstcount_; }
 set { SetSceneinstcount(value); }
 }
 public void SetSceneinstcount(Int32 value) { 
 hasSceneinstcount = true;
 sceneinstcount_ = value;
 }

public const int sceneactivationFieldNumber = 3;
 private pbc::PopsicleList<Int32> sceneactivation_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> sceneactivationList {
 get { return pbc::Lists.AsReadOnly(sceneactivation_); }
 }
 
 public int sceneactivationCount {
 get { return sceneactivation_.Count; }
 }
 
public Int32 GetSceneactivation(int index) {
 return sceneactivation_[index];
 }
 public void AddSceneactivation(Int32 value) {
 sceneactivation_.Add(value);
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasSceneclassid) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Sceneclassid);
}
 if (HasSceneinstcount) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Sceneinstcount);
}
{
int dataSize = 0;
for(int i=0; i<sceneactivationList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(sceneactivationList[i]);
}
size += dataSize;
size += 1 * sceneactivation_.Count;
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasSceneclassid) {
output.WriteInt32(1, Sceneclassid);
}
 
if (HasSceneinstcount) {
output.WriteInt32(2, Sceneinstcount);
}
{
if (sceneactivation_.Count > 0) {
for(int i=0; i<sceneactivation_.Count; ++i){
output.WriteInt32(3,sceneactivation_[i]);
}
}

}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_UPDATE_SCENE_INSTACTIVATION _inst = (GC_UPDATE_SCENE_INSTACTIVATION) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Sceneclassid = input.ReadInt32();
break;
}
   case  16: {
 _inst.Sceneinstcount = input.ReadInt32();
break;
}
   case  24: {
 _inst.AddSceneactivation(input.ReadInt32());
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasSceneclassid) return false;
 if (!hasSceneinstcount) return false;
 return true;
 }

}


[Serializable]
public class GS_CONNECTED_HEARTBEAT : PacketDistributed
{

public const int senderworldidFieldNumber = 1;
 private bool hasSenderworldid;
 private Int32 senderworldid_ = 0;
 public bool HasSenderworldid {
 get { return hasSenderworldid; }
 }
 public Int32 Senderworldid {
 get { return senderworldid_; }
 set { SetSenderworldid(value); }
 }
 public void SetSenderworldid(Int32 value) { 
 hasSenderworldid = true;
 senderworldid_ = value;
 }

public const int receiverworldidFieldNumber = 2;
 private bool hasReceiverworldid;
 private Int32 receiverworldid_ = 0;
 public bool HasReceiverworldid {
 get { return hasReceiverworldid; }
 }
 public Int32 Receiverworldid {
 get { return receiverworldid_; }
 set { SetReceiverworldid(value); }
 }
 public void SetReceiverworldid(Int32 value) { 
 hasReceiverworldid = true;
 receiverworldid_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasSenderworldid) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Senderworldid);
}
 if (HasReceiverworldid) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Receiverworldid);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasSenderworldid) {
output.WriteInt32(1, Senderworldid);
}
 
if (HasReceiverworldid) {
output.WriteInt32(2, Receiverworldid);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GS_CONNECTED_HEARTBEAT _inst = (GS_CONNECTED_HEARTBEAT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Senderworldid = input.ReadInt32();
break;
}
   case  16: {
 _inst.Receiverworldid = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasSenderworldid) return false;
 if (!hasReceiverworldid) return false;
 return true;
 }

}


[Serializable]
public class SG_CONNECTED_HEARTBEAT : PacketDistributed
{

public const int senderworldidFieldNumber = 1;
 private bool hasSenderworldid;
 private Int32 senderworldid_ = 0;
 public bool HasSenderworldid {
 get { return hasSenderworldid; }
 }
 public Int32 Senderworldid {
 get { return senderworldid_; }
 set { SetSenderworldid(value); }
 }
 public void SetSenderworldid(Int32 value) { 
 hasSenderworldid = true;
 senderworldid_ = value;
 }

public const int receiverworldidFieldNumber = 2;
 private bool hasReceiverworldid;
 private Int32 receiverworldid_ = 0;
 public bool HasReceiverworldid {
 get { return hasReceiverworldid; }
 }
 public Int32 Receiverworldid {
 get { return receiverworldid_; }
 set { SetReceiverworldid(value); }
 }
 public void SetReceiverworldid(Int32 value) { 
 hasReceiverworldid = true;
 receiverworldid_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasSenderworldid) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Senderworldid);
}
 if (HasReceiverworldid) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Receiverworldid);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasSenderworldid) {
output.WriteInt32(1, Senderworldid);
}
 
if (HasReceiverworldid) {
output.WriteInt32(2, Receiverworldid);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 SG_CONNECTED_HEARTBEAT _inst = (SG_CONNECTED_HEARTBEAT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Senderworldid = input.ReadInt32();
break;
}
   case  16: {
 _inst.Receiverworldid = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasSenderworldid) return false;
 if (!hasReceiverworldid) return false;
 return true;
 }

}


[Serializable]
public class CG_MOVE : PacketDistributed
{

public const int poscountFieldNumber = 1;
 private bool hasPoscount;
 private Int32 poscount_ = 0;
 public bool HasPoscount {
 get { return hasPoscount; }
 }
 public Int32 Poscount {
 get { return poscount_; }
 set { SetPoscount(value); }
 }
 public void SetPoscount(Int32 value) { 
 hasPoscount = true;
 poscount_ = value;
 }

public const int posxFieldNumber = 2;
 private pbc::PopsicleList<Int32> posx_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> posxList {
 get { return pbc::Lists.AsReadOnly(posx_); }
 }
 
 public int posxCount {
 get { return posx_.Count; }
 }
 
public Int32 GetPosx(int index) {
 return posx_[index];
 }
 public void AddPosx(Int32 value) {
 posx_.Add(value);
 }

public const int poszFieldNumber = 3;
 private pbc::PopsicleList<Int32> posz_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> poszList {
 get { return pbc::Lists.AsReadOnly(posz_); }
 }
 
 public int poszCount {
 get { return posz_.Count; }
 }
 
public Int32 GetPosz(int index) {
 return posz_[index];
 }
 public void AddPosz(Int32 value) {
 posz_.Add(value);
 }

public const int ismovingFieldNumber = 4;
 private bool hasIsmoving;
 private Int32 ismoving_ = 0;
 public bool HasIsmoving {
 get { return hasIsmoving; }
 }
 public Int32 Ismoving {
 get { return ismoving_; }
 set { SetIsmoving(value); }
 }
 public void SetIsmoving(Int32 value) { 
 hasIsmoving = true;
 ismoving_ = value;
 }

public const int marchidFieldNumber = 5;
 private bool hasMarchid;
 private Int64 marchid_ = 0;
 public bool HasMarchid {
 get { return hasMarchid; }
 }
 public Int64 Marchid {
 get { return marchid_; }
 set { SetMarchid(value); }
 }
 public void SetMarchid(Int64 value) { 
 hasMarchid = true;
 marchid_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasPoscount) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Poscount);
}
{
int dataSize = 0;
for(int i=0; i<posxList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(posxList[i]);
}
size += dataSize;
size += 1 * posx_.Count;
}
{
int dataSize = 0;
for(int i=0; i<poszList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(poszList[i]);
}
size += dataSize;
size += 1 * posz_.Count;
}
 if (HasIsmoving) {
size += pb::CodedOutputStream.ComputeInt32Size(4, Ismoving);
}
 if (HasMarchid) {
size += pb::CodedOutputStream.ComputeInt64Size(5, Marchid);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasPoscount) {
output.WriteInt32(1, Poscount);
}
{
if (posx_.Count > 0) {
for(int i=0; i<posx_.Count; ++i){
output.WriteInt32(2,posx_[i]);
}
}

}
{
if (posz_.Count > 0) {
for(int i=0; i<posz_.Count; ++i){
output.WriteInt32(3,posz_[i]);
}
}

}
 
if (HasIsmoving) {
output.WriteInt32(4, Ismoving);
}
 
if (HasMarchid) {
output.WriteInt64(5, Marchid);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_MOVE _inst = (CG_MOVE) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Poscount = input.ReadInt32();
break;
}
   case  16: {
 _inst.AddPosx(input.ReadInt32());
break;
}
   case  24: {
 _inst.AddPosz(input.ReadInt32());
break;
}
   case  32: {
 _inst.Ismoving = input.ReadInt32();
break;
}
   case  40: {
 _inst.Marchid = input.ReadInt64();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasPoscount) return false;
 if (!hasIsmoving) return false;
 if (!hasMarchid) return false;
 return true;
 }

}


[Serializable]
public class GC_MOVE : PacketDistributed
{

public const int serveridFieldNumber = 1;
 private bool hasServerid;
 private Int32 serverid_ = 0;
 public bool HasServerid {
 get { return hasServerid; }
 }
 public Int32 Serverid {
 get { return serverid_; }
 set { SetServerid(value); }
 }
 public void SetServerid(Int32 value) { 
 hasServerid = true;
 serverid_ = value;
 }

public const int poscountFieldNumber = 2;
 private bool hasPoscount;
 private Int32 poscount_ = 0;
 public bool HasPoscount {
 get { return hasPoscount; }
 }
 public Int32 Poscount {
 get { return poscount_; }
 set { SetPoscount(value); }
 }
 public void SetPoscount(Int32 value) { 
 hasPoscount = true;
 poscount_ = value;
 }

public const int posserialFieldNumber = 3;
 private pbc::PopsicleList<Int32> posserial_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> posserialList {
 get { return pbc::Lists.AsReadOnly(posserial_); }
 }
 
 public int posserialCount {
 get { return posserial_.Count; }
 }
 
public Int32 GetPosserial(int index) {
 return posserial_[index];
 }
 public void AddPosserial(Int32 value) {
 posserial_.Add(value);
 }

public const int posxFieldNumber = 4;
 private pbc::PopsicleList<Int32> posx_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> posxList {
 get { return pbc::Lists.AsReadOnly(posx_); }
 }
 
 public int posxCount {
 get { return posx_.Count; }
 }
 
public Int32 GetPosx(int index) {
 return posx_[index];
 }
 public void AddPosx(Int32 value) {
 posx_.Add(value);
 }

public const int poszFieldNumber = 5;
 private pbc::PopsicleList<Int32> posz_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> poszList {
 get { return pbc::Lists.AsReadOnly(posz_); }
 }
 
 public int poszCount {
 get { return posz_.Count; }
 }
 
public Int32 GetPosz(int index) {
 return posz_[index];
 }
 public void AddPosz(Int32 value) {
 posz_.Add(value);
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasServerid) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Serverid);
}
 if (HasPoscount) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Poscount);
}
{
int dataSize = 0;
for(int i=0; i<posserialList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(posserialList[i]);
}
size += dataSize;
size += 1 * posserial_.Count;
}
{
int dataSize = 0;
for(int i=0; i<posxList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(posxList[i]);
}
size += dataSize;
size += 1 * posx_.Count;
}
{
int dataSize = 0;
for(int i=0; i<poszList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(poszList[i]);
}
size += dataSize;
size += 1 * posz_.Count;
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasServerid) {
output.WriteInt32(1, Serverid);
}
 
if (HasPoscount) {
output.WriteInt32(2, Poscount);
}
{
if (posserial_.Count > 0) {
for(int i=0; i<posserial_.Count; ++i){
output.WriteInt32(3,posserial_[i]);
}
}

}
{
if (posx_.Count > 0) {
for(int i=0; i<posx_.Count; ++i){
output.WriteInt32(4,posx_[i]);
}
}

}
{
if (posz_.Count > 0) {
for(int i=0; i<posz_.Count; ++i){
output.WriteInt32(5,posz_[i]);
}
}

}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_MOVE _inst = (GC_MOVE) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Serverid = input.ReadInt32();
break;
}
   case  16: {
 _inst.Poscount = input.ReadInt32();
break;
}
   case  24: {
 _inst.AddPosserial(input.ReadInt32());
break;
}
   case  32: {
 _inst.AddPosx(input.ReadInt32());
break;
}
   case  40: {
 _inst.AddPosz(input.ReadInt32());
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasServerid) return false;
 if (!hasPoscount) return false;
 return true;
 }

}


[Serializable]
public class GC_STOP : PacketDistributed
{

public const int serveridFieldNumber = 1;
 private bool hasServerid;
 private Int32 serverid_ = 0;
 public bool HasServerid {
 get { return hasServerid; }
 }
 public Int32 Serverid {
 get { return serverid_; }
 set { SetServerid(value); }
 }
 public void SetServerid(Int32 value) { 
 hasServerid = true;
 serverid_ = value;
 }

public const int posserialFieldNumber = 2;
 private bool hasPosserial;
 private Int32 posserial_ = 0;
 public bool HasPosserial {
 get { return hasPosserial; }
 }
 public Int32 Posserial {
 get { return posserial_; }
 set { SetPosserial(value); }
 }
 public void SetPosserial(Int32 value) { 
 hasPosserial = true;
 posserial_ = value;
 }

public const int posxFieldNumber = 3;
 private bool hasPosx;
 private Int32 posx_ = 0;
 public bool HasPosx {
 get { return hasPosx; }
 }
 public Int32 Posx {
 get { return posx_; }
 set { SetPosx(value); }
 }
 public void SetPosx(Int32 value) { 
 hasPosx = true;
 posx_ = value;
 }

public const int poszFieldNumber = 4;
 private bool hasPosz;
 private Int32 posz_ = 0;
 public bool HasPosz {
 get { return hasPosz; }
 }
 public Int32 Posz {
 get { return posz_; }
 set { SetPosz(value); }
 }
 public void SetPosz(Int32 value) { 
 hasPosz = true;
 posz_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasServerid) {
size += pb::CodedOutputStream.ComputeInt32Size(1, Serverid);
}
 if (HasPosserial) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Posserial);
}
 if (HasPosx) {
size += pb::CodedOutputStream.ComputeInt32Size(3, Posx);
}
 if (HasPosz) {
size += pb::CodedOutputStream.ComputeInt32Size(4, Posz);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasServerid) {
output.WriteInt32(1, Serverid);
}
 
if (HasPosserial) {
output.WriteInt32(2, Posserial);
}
 
if (HasPosx) {
output.WriteInt32(3, Posx);
}
 
if (HasPosz) {
output.WriteInt32(4, Posz);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_STOP _inst = (GC_STOP) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.Serverid = input.ReadInt32();
break;
}
   case  16: {
 _inst.Posserial = input.ReadInt32();
break;
}
   case  24: {
 _inst.Posx = input.ReadInt32();
break;
}
   case  32: {
 _inst.Posz = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasServerid) return false;
 if (!hasPosserial) return false;
 if (!hasPosx) return false;
 if (!hasPosz) return false;
 return true;
 }

}


[Serializable]
public class GC_TELEMOVE : PacketDistributed
{

public const int objIdFieldNumber = 1;
 private bool hasObjId;
 private Int32 objId_ = 0;
 public bool HasObjId {
 get { return hasObjId; }
 }
 public Int32 ObjId {
 get { return objId_; }
 set { SetObjId(value); }
 }
 public void SetObjId(Int32 value) { 
 hasObjId = true;
 objId_ = value;
 }

public const int targetPosXFieldNumber = 2;
 private bool hasTargetPosX;
 private Int32 targetPosX_ = 0;
 public bool HasTargetPosX {
 get { return hasTargetPosX; }
 }
 public Int32 TargetPosX {
 get { return targetPosX_; }
 set { SetTargetPosX(value); }
 }
 public void SetTargetPosX(Int32 value) { 
 hasTargetPosX = true;
 targetPosX_ = value;
 }

public const int targetPosZFieldNumber = 3;
 private bool hasTargetPosZ;
 private Int32 targetPosZ_ = 0;
 public bool HasTargetPosZ {
 get { return hasTargetPosZ; }
 }
 public Int32 TargetPosZ {
 get { return targetPosZ_; }
 set { SetTargetPosZ(value); }
 }
 public void SetTargetPosZ(Int32 value) { 
 hasTargetPosZ = true;
 targetPosZ_ = value;
 }

public const int needChangeFacetoFieldNumber = 4;
 private bool hasNeedChangeFaceto;
 private Int32 needChangeFaceto_ = 0;
 public bool HasNeedChangeFaceto {
 get { return hasNeedChangeFaceto; }
 }
 public Int32 NeedChangeFaceto {
 get { return needChangeFaceto_; }
 set { SetNeedChangeFaceto(value); }
 }
 public void SetNeedChangeFaceto(Int32 value) { 
 hasNeedChangeFaceto = true;
 needChangeFaceto_ = value;
 }

public const int animaIdFieldNumber = 5;
 private bool hasAnimaId;
 private Int32 animaId_ = 0;
 public bool HasAnimaId {
 get { return hasAnimaId; }
 }
 public Int32 AnimaId {
 get { return animaId_; }
 set { SetAnimaId(value); }
 }
 public void SetAnimaId(Int32 value) { 
 hasAnimaId = true;
 animaId_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasObjId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ObjId);
}
 if (HasTargetPosX) {
size += pb::CodedOutputStream.ComputeInt32Size(2, TargetPosX);
}
 if (HasTargetPosZ) {
size += pb::CodedOutputStream.ComputeInt32Size(3, TargetPosZ);
}
 if (HasNeedChangeFaceto) {
size += pb::CodedOutputStream.ComputeInt32Size(4, NeedChangeFaceto);
}
 if (HasAnimaId) {
size += pb::CodedOutputStream.ComputeInt32Size(5, AnimaId);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasObjId) {
output.WriteInt32(1, ObjId);
}
 
if (HasTargetPosX) {
output.WriteInt32(2, TargetPosX);
}
 
if (HasTargetPosZ) {
output.WriteInt32(3, TargetPosZ);
}
 
if (HasNeedChangeFaceto) {
output.WriteInt32(4, NeedChangeFaceto);
}
 
if (HasAnimaId) {
output.WriteInt32(5, AnimaId);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_TELEMOVE _inst = (GC_TELEMOVE) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ObjId = input.ReadInt32();
break;
}
   case  16: {
 _inst.TargetPosX = input.ReadInt32();
break;
}
   case  24: {
 _inst.TargetPosZ = input.ReadInt32();
break;
}
   case  32: {
 _inst.NeedChangeFaceto = input.ReadInt32();
break;
}
   case  40: {
 _inst.AnimaId = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasObjId) return false;
 if (!hasTargetPosX) return false;
 if (!hasTargetPosZ) return false;
 if (!hasNeedChangeFaceto) return false;
 return true;
 }

}


[Serializable]
public class GC_RET_USE_SKILL : PacketDistributed
{

public const int skillIdFieldNumber = 1;
 private bool hasSkillId;
 private Int32 skillId_ = 0;
 public bool HasSkillId {
 get { return hasSkillId; }
 }
 public Int32 SkillId {
 get { return skillId_; }
 set { SetSkillId(value); }
 }
 public void SetSkillId(Int32 value) { 
 hasSkillId = true;
 skillId_ = value;
 }

public const int senderIdFieldNumber = 2;
 private bool hasSenderId;
 private Int32 senderId_ = 0;
 public bool HasSenderId {
 get { return hasSenderId; }
 }
 public Int32 SenderId {
 get { return senderId_; }
 set { SetSenderId(value); }
 }
 public void SetSenderId(Int32 value) { 
 hasSenderId = true;
 senderId_ = value;
 }

public const int TargetIdFieldNumber = 3;
 private bool hasTargetId;
 private Int32 TargetId_ = 0;
 public bool HasTargetId {
 get { return hasTargetId; }
 }
 public Int32 TargetId {
 get { return TargetId_; }
 set { SetTargetId(value); }
 }
 public void SetTargetId(Int32 value) { 
 hasTargetId = true;
 TargetId_ = value;
 }

public const int skillfailTypeFieldNumber = 4;
 private bool hasSkillfailType;
 private Int32 skillfailType_ = 0;
 public bool HasSkillfailType {
 get { return hasSkillfailType; }
 }
 public Int32 SkillfailType {
 get { return skillfailType_; }
 set { SetSkillfailType(value); }
 }
 public void SetSkillfailType(Int32 value) { 
 hasSkillfailType = true;
 skillfailType_ = value;
 }

public const int skillnameFieldNumber = 5;
 private bool hasSkillname;
 private string skillname_ = "";
 public bool HasSkillname {
 get { return hasSkillname; }
 }
 public string Skillname {
 get { return skillname_; }
 set { SetSkillname(value); }
 }
 public void SetSkillname(string value) { 
 hasSkillname = true;
 skillname_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasSkillId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, SkillId);
}
 if (HasSenderId) {
size += pb::CodedOutputStream.ComputeInt32Size(2, SenderId);
}
 if (HasTargetId) {
size += pb::CodedOutputStream.ComputeInt32Size(3, TargetId);
}
 if (HasSkillfailType) {
size += pb::CodedOutputStream.ComputeInt32Size(4, SkillfailType);
}
 if (HasSkillname) {
size += pb::CodedOutputStream.ComputeStringSize(5, Skillname);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasSkillId) {
output.WriteInt32(1, SkillId);
}
 
if (HasSenderId) {
output.WriteInt32(2, SenderId);
}
 
if (HasTargetId) {
output.WriteInt32(3, TargetId);
}
 
if (HasSkillfailType) {
output.WriteInt32(4, SkillfailType);
}
 
if (HasSkillname) {
output.WriteString(5, Skillname);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_RET_USE_SKILL _inst = (GC_RET_USE_SKILL) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.SkillId = input.ReadInt32();
break;
}
   case  16: {
 _inst.SenderId = input.ReadInt32();
break;
}
   case  24: {
 _inst.TargetId = input.ReadInt32();
break;
}
   case  32: {
 _inst.SkillfailType = input.ReadInt32();
break;
}
   case  42: {
 _inst.Skillname = input.ReadString();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasSkillId) return false;
 if (!hasSenderId) return false;
 if (!hasTargetId) return false;
 return true;
 }

}


[Serializable]
public class GC_UPDATE_ANIMATION_STATE : PacketDistributed
{

public const int objIdFieldNumber = 1;
 private bool hasObjId;
 private Int32 objId_ = 0;
 public bool HasObjId {
 get { return hasObjId; }
 }
 public Int32 ObjId {
 get { return objId_; }
 set { SetObjId(value); }
 }
 public void SetObjId(Int32 value) { 
 hasObjId = true;
 objId_ = value;
 }

public const int AnimationStateFieldNumber = 2;
 private bool hasAnimationState;
 private Int32 AnimationState_ = 0;
 public bool HasAnimationState {
 get { return hasAnimationState; }
 }
 public Int32 AnimationState {
 get { return AnimationState_; }
 set { SetAnimationState(value); }
 }
 public void SetAnimationState(Int32 value) { 
 hasAnimationState = true;
 AnimationState_ = value;
 }

public const int verticalOffDisFieldNumber = 3;
 private bool hasVerticalOffDis;
 private Int32 verticalOffDis_ = 0;
 public bool HasVerticalOffDis {
 get { return hasVerticalOffDis; }
 }
 public Int32 VerticalOffDis {
 get { return verticalOffDis_; }
 set { SetVerticalOffDis(value); }
 }
 public void SetVerticalOffDis(Int32 value) { 
 hasVerticalOffDis = true;
 verticalOffDis_ = value;
 }

public const int horizontalOffDisFieldNumber = 4;
 private bool hasHorizontalOffDis;
 private Int32 horizontalOffDis_ = 0;
 public bool HasHorizontalOffDis {
 get { return hasHorizontalOffDis; }
 }
 public Int32 HorizontalOffDis {
 get { return horizontalOffDis_; }
 set { SetHorizontalOffDis(value); }
 }
 public void SetHorizontalOffDis(Int32 value) { 
 hasHorizontalOffDis = true;
 horizontalOffDis_ = value;
 }

public const int stateLastTimeFieldNumber = 5;
 private bool hasStateLastTime;
 private Int32 stateLastTime_ = 0;
 public bool HasStateLastTime {
 get { return hasStateLastTime; }
 }
 public Int32 StateLastTime {
 get { return stateLastTime_; }
 set { SetStateLastTime(value); }
 }
 public void SetStateLastTime(Int32 value) { 
 hasStateLastTime = true;
 stateLastTime_ = value;
 }

public const int stateResortTimeFieldNumber = 6;
 private bool hasStateResortTime;
 private Int32 stateResortTime_ = 0;
 public bool HasStateResortTime {
 get { return hasStateResortTime; }
 }
 public Int32 StateResortTime {
 get { return stateResortTime_; }
 set { SetStateResortTime(value); }
 }
 public void SetStateResortTime(Int32 value) { 
 hasStateResortTime = true;
 stateResortTime_ = value;
 }

public const int hitTimesFieldNumber = 7;
 private bool hasHitTimes;
 private Int32 hitTimes_ = 0;
 public bool HasHitTimes {
 get { return hasHitTimes; }
 }
 public Int32 HitTimes {
 get { return hitTimes_; }
 set { SetHitTimes(value); }
 }
 public void SetHitTimes(Int32 value) { 
 hasHitTimes = true;
 hitTimes_ = value;
 }

public const int hitIntervalFieldNumber = 8;
 private bool hasHitInterval;
 private Int32 hitInterval_ = 0;
 public bool HasHitInterval {
 get { return hasHitInterval; }
 }
 public Int32 HitInterval {
 get { return hitInterval_; }
 set { SetHitInterval(value); }
 }
 public void SetHitInterval(Int32 value) { 
 hasHitInterval = true;
 hitInterval_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasObjId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ObjId);
}
 if (HasAnimationState) {
size += pb::CodedOutputStream.ComputeInt32Size(2, AnimationState);
}
 if (HasVerticalOffDis) {
size += pb::CodedOutputStream.ComputeInt32Size(3, VerticalOffDis);
}
 if (HasHorizontalOffDis) {
size += pb::CodedOutputStream.ComputeInt32Size(4, HorizontalOffDis);
}
 if (HasStateLastTime) {
size += pb::CodedOutputStream.ComputeInt32Size(5, StateLastTime);
}
 if (HasStateResortTime) {
size += pb::CodedOutputStream.ComputeInt32Size(6, StateResortTime);
}
 if (HasHitTimes) {
size += pb::CodedOutputStream.ComputeInt32Size(7, HitTimes);
}
 if (HasHitInterval) {
size += pb::CodedOutputStream.ComputeInt32Size(8, HitInterval);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasObjId) {
output.WriteInt32(1, ObjId);
}
 
if (HasAnimationState) {
output.WriteInt32(2, AnimationState);
}
 
if (HasVerticalOffDis) {
output.WriteInt32(3, VerticalOffDis);
}
 
if (HasHorizontalOffDis) {
output.WriteInt32(4, HorizontalOffDis);
}
 
if (HasStateLastTime) {
output.WriteInt32(5, StateLastTime);
}
 
if (HasStateResortTime) {
output.WriteInt32(6, StateResortTime);
}
 
if (HasHitTimes) {
output.WriteInt32(7, HitTimes);
}
 
if (HasHitInterval) {
output.WriteInt32(8, HitInterval);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_UPDATE_ANIMATION_STATE _inst = (GC_UPDATE_ANIMATION_STATE) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ObjId = input.ReadInt32();
break;
}
   case  16: {
 _inst.AnimationState = input.ReadInt32();
break;
}
   case  24: {
 _inst.VerticalOffDis = input.ReadInt32();
break;
}
   case  32: {
 _inst.HorizontalOffDis = input.ReadInt32();
break;
}
   case  40: {
 _inst.StateLastTime = input.ReadInt32();
break;
}
   case  48: {
 _inst.StateResortTime = input.ReadInt32();
break;
}
   case  56: {
 _inst.HitTimes = input.ReadInt32();
break;
}
   case  64: {
 _inst.HitInterval = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasObjId) return false;
 if (!hasAnimationState) return false;
 return true;
 }

}


[Serializable]
public class GC_DELETE_OBJ : PacketDistributed
{

public const int serverIdFieldNumber = 1;
 private bool hasServerId;
 private Int32 serverId_ = 0;
 public bool HasServerId {
 get { return hasServerId; }
 }
 public Int32 ServerId {
 get { return serverId_; }
 set { SetServerId(value); }
 }
 public void SetServerId(Int32 value) { 
 hasServerId = true;
 serverId_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasServerId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ServerId);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasServerId) {
output.WriteInt32(1, ServerId);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_DELETE_OBJ _inst = (GC_DELETE_OBJ) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ServerId = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasServerId) return false;
 return true;
 }

}


[Serializable]
public class GC_ATTACKFLY : PacketDistributed
{

public const int objIdFieldNumber = 1;
 private bool hasObjId;
 private Int32 objId_ = 0;
 public bool HasObjId {
 get { return hasObjId; }
 }
 public Int32 ObjId {
 get { return objId_; }
 set { SetObjId(value); }
 }
 public void SetObjId(Int32 value) { 
 hasObjId = true;
 objId_ = value;
 }

public const int DisFieldNumber = 2;
 private bool hasDis;
 private Int32 Dis_ = 0;
 public bool HasDis {
 get { return hasDis; }
 }
 public Int32 Dis {
 get { return Dis_; }
 set { SetDis(value); }
 }
 public void SetDis(Int32 value) { 
 hasDis = true;
 Dis_ = value;
 }

public const int HightFieldNumber = 3;
 private bool hasHight;
 private Int32 Hight_ = 0;
 public bool HasHight {
 get { return hasHight; }
 }
 public Int32 Hight {
 get { return Hight_; }
 set { SetHight(value); }
 }
 public void SetHight(Int32 value) { 
 hasHight = true;
 Hight_ = value;
 }

public const int FlyTimeFieldNumber = 4;
 private bool hasFlyTime;
 private Int32 FlyTime_ = 0;
 public bool HasFlyTime {
 get { return hasFlyTime; }
 }
 public Int32 FlyTime {
 get { return FlyTime_; }
 set { SetFlyTime(value); }
 }
 public void SetFlyTime(Int32 value) { 
 hasFlyTime = true;
 FlyTime_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasObjId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ObjId);
}
 if (HasDis) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Dis);
}
 if (HasHight) {
size += pb::CodedOutputStream.ComputeInt32Size(3, Hight);
}
 if (HasFlyTime) {
size += pb::CodedOutputStream.ComputeInt32Size(4, FlyTime);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasObjId) {
output.WriteInt32(1, ObjId);
}
 
if (HasDis) {
output.WriteInt32(2, Dis);
}
 
if (HasHight) {
output.WriteInt32(3, Hight);
}
 
if (HasFlyTime) {
output.WriteInt32(4, FlyTime);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_ATTACKFLY _inst = (GC_ATTACKFLY) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ObjId = input.ReadInt32();
break;
}
   case  16: {
 _inst.Dis = input.ReadInt32();
break;
}
   case  24: {
 _inst.Hight = input.ReadInt32();
break;
}
   case  32: {
 _inst.FlyTime = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasObjId) return false;
 if (!hasDis) return false;
 if (!hasHight) return false;
 if (!hasFlyTime) return false;
 return true;
 }

}


[Serializable]
public class GC_FORCE_SETPOS : PacketDistributed
{

public const int ServerIDFieldNumber = 1;
 private bool hasServerID;
 private Int32 ServerID_ = 0;
 public bool HasServerID {
 get { return hasServerID; }
 }
 public Int32 ServerID {
 get { return ServerID_; }
 set { SetServerID(value); }
 }
 public void SetServerID(Int32 value) { 
 hasServerID = true;
 ServerID_ = value;
 }

public const int PosXFieldNumber = 2;
 private bool hasPosX;
 private Int32 PosX_ = 0;
 public bool HasPosX {
 get { return hasPosX; }
 }
 public Int32 PosX {
 get { return PosX_; }
 set { SetPosX(value); }
 }
 public void SetPosX(Int32 value) { 
 hasPosX = true;
 PosX_ = value;
 }

public const int PosZFieldNumber = 3;
 private bool hasPosZ;
 private Int32 PosZ_ = 0;
 public bool HasPosZ {
 get { return hasPosZ; }
 }
 public Int32 PosZ {
 get { return PosZ_; }
 set { SetPosZ(value); }
 }
 public void SetPosZ(Int32 value) { 
 hasPosZ = true;
 PosZ_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasServerID) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ServerID);
}
 if (HasPosX) {
size += pb::CodedOutputStream.ComputeInt32Size(2, PosX);
}
 if (HasPosZ) {
size += pb::CodedOutputStream.ComputeInt32Size(3, PosZ);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasServerID) {
output.WriteInt32(1, ServerID);
}
 
if (HasPosX) {
output.WriteInt32(2, PosX);
}
 
if (HasPosZ) {
output.WriteInt32(3, PosZ);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_FORCE_SETPOS _inst = (GC_FORCE_SETPOS) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ServerID = input.ReadInt32();
break;
}
   case  16: {
 _inst.PosX = input.ReadInt32();
break;
}
   case  24: {
 _inst.PosZ = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasServerID) return false;
 if (!hasPosX) return false;
 if (!hasPosZ) return false;
 return true;
 }

}


[Serializable]
public class GC_UPDATE_NEEDIMPACTINFO : PacketDistributed
{

public const int objIdFieldNumber = 1;
 private bool hasObjId;
 private Int32 objId_ = 0;
 public bool HasObjId {
 get { return hasObjId; }
 }
 public Int32 ObjId {
 get { return objId_; }
 set { SetObjId(value); }
 }
 public void SetObjId(Int32 value) { 
 hasObjId = true;
 objId_ = value;
 }

public const int impactIdFieldNumber = 2;
 private pbc::PopsicleList<Int32> impactId_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> impactIdList {
 get { return pbc::Lists.AsReadOnly(impactId_); }
 }
 
 public int impactIdCount {
 get { return impactId_.Count; }
 }
 
public Int32 GetImpactId(int index) {
 return impactId_[index];
 }
 public void AddImpactId(Int32 value) {
 impactId_.Add(value);
 }

public const int impactLogicIdFieldNumber = 3;
 private pbc::PopsicleList<Int32> impactLogicId_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> impactLogicIdList {
 get { return pbc::Lists.AsReadOnly(impactLogicId_); }
 }
 
 public int impactLogicIdCount {
 get { return impactLogicId_.Count; }
 }
 
public Int32 GetImpactLogicId(int index) {
 return impactLogicId_[index];
 }
 public void AddImpactLogicId(Int32 value) {
 impactLogicId_.Add(value);
 }

public const int isForeverFieldNumber = 4;
 private pbc::PopsicleList<Int32> isForever_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> isForeverList {
 get { return pbc::Lists.AsReadOnly(isForever_); }
 }
 
 public int isForeverCount {
 get { return isForever_.Count; }
 }
 
public Int32 GetIsForever(int index) {
 return isForever_[index];
 }
 public void AddIsForever(Int32 value) {
 isForever_.Add(value);
 }

public const int remainTimeFieldNumber = 5;
 private pbc::PopsicleList<Int32> remainTime_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> remainTimeList {
 get { return pbc::Lists.AsReadOnly(remainTime_); }
 }
 
 public int remainTimeCount {
 get { return remainTime_.Count; }
 }
 
public Int32 GetRemainTime(int index) {
 return remainTime_[index];
 }
 public void AddRemainTime(Int32 value) {
 remainTime_.Add(value);
 }

public const int isAddFieldNumber = 6;
 private pbc::PopsicleList<Int32> isAdd_ = new pbc::PopsicleList<Int32>();
 public scg::IList<Int32> isAddList {
 get { return pbc::Lists.AsReadOnly(isAdd_); }
 }
 
 public int isAddCount {
 get { return isAdd_.Count; }
 }
 
public Int32 GetIsAdd(int index) {
 return isAdd_[index];
 }
 public void AddIsAdd(Int32 value) {
 isAdd_.Add(value);
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasObjId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ObjId);
}
{
int dataSize = 0;
for(int i=0; i<impactIdList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(impactIdList[i]);
}
size += dataSize;
size += 1 * impactId_.Count;
}
{
int dataSize = 0;
for(int i=0; i<impactLogicIdList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(impactLogicIdList[i]);
}
size += dataSize;
size += 1 * impactLogicId_.Count;
}
{
int dataSize = 0;
for(int i=0; i<isForeverList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(isForeverList[i]);
}
size += dataSize;
size += 1 * isForever_.Count;
}
{
int dataSize = 0;
for(int i=0; i<remainTimeList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(remainTimeList[i]);
}
size += dataSize;
size += 1 * remainTime_.Count;
}
{
int dataSize = 0;
for(int i=0; i<isAddList.Count; ++i){
dataSize += pb::CodedOutputStream.ComputeInt32SizeNoTag(isAddList[i]);
}
size += dataSize;
size += 1 * isAdd_.Count;
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasObjId) {
output.WriteInt32(1, ObjId);
}
{
if (impactId_.Count > 0) {
for(int i=0; i<impactId_.Count; ++i){
output.WriteInt32(2,impactId_[i]);
}
}

}
{
if (impactLogicId_.Count > 0) {
for(int i=0; i<impactLogicId_.Count; ++i){
output.WriteInt32(3,impactLogicId_[i]);
}
}

}
{
if (isForever_.Count > 0) {
for(int i=0; i<isForever_.Count; ++i){
output.WriteInt32(4,isForever_[i]);
}
}

}
{
if (remainTime_.Count > 0) {
for(int i=0; i<remainTime_.Count; ++i){
output.WriteInt32(5,remainTime_[i]);
}
}

}
{
if (isAdd_.Count > 0) {
for(int i=0; i<isAdd_.Count; ++i){
output.WriteInt32(6,isAdd_[i]);
}
}

}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_UPDATE_NEEDIMPACTINFO _inst = (GC_UPDATE_NEEDIMPACTINFO) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ObjId = input.ReadInt32();
break;
}
   case  16: {
 _inst.AddImpactId(input.ReadInt32());
break;
}
   case  24: {
 _inst.AddImpactLogicId(input.ReadInt32());
break;
}
   case  32: {
 _inst.AddIsForever(input.ReadInt32());
break;
}
   case  40: {
 _inst.AddRemainTime(input.ReadInt32());
break;
}
   case  48: {
 _inst.AddIsAdd(input.ReadInt32());
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasObjId) return false;
 return true;
 }

}


[Serializable]
public class GC_PLAY_EFFECT : PacketDistributed
{

public const int ObjIDFieldNumber = 1;
 private bool hasObjID;
 private Int32 ObjID_ = 0;
 public bool HasObjID {
 get { return hasObjID; }
 }
 public Int32 ObjID {
 get { return ObjID_; }
 set { SetObjID(value); }
 }
 public void SetObjID(Int32 value) { 
 hasObjID = true;
 ObjID_ = value;
 }

public const int EffectIDFieldNumber = 2;
 private bool hasEffectID;
 private Int32 EffectID_ = 0;
 public bool HasEffectID {
 get { return hasEffectID; }
 }
 public Int32 EffectID {
 get { return EffectID_; }
 set { SetEffectID(value); }
 }
 public void SetEffectID(Int32 value) { 
 hasEffectID = true;
 EffectID_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasObjID) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ObjID);
}
 if (HasEffectID) {
size += pb::CodedOutputStream.ComputeInt32Size(2, EffectID);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasObjID) {
output.WriteInt32(1, ObjID);
}
 
if (HasEffectID) {
output.WriteInt32(2, EffectID);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_PLAY_EFFECT _inst = (GC_PLAY_EFFECT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ObjID = input.ReadInt32();
break;
}
   case  16: {
 _inst.EffectID = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasObjID) return false;
 if (!hasEffectID) return false;
 return true;
 }

}


[Serializable]
public class GC_REMOVEEFFECT : PacketDistributed
{

public const int objIdFieldNumber = 1;
 private bool hasObjId;
 private Int32 objId_ = 0;
 public bool HasObjId {
 get { return hasObjId; }
 }
 public Int32 ObjId {
 get { return objId_; }
 set { SetObjId(value); }
 }
 public void SetObjId(Int32 value) { 
 hasObjId = true;
 objId_ = value;
 }

public const int effectIdFieldNumber = 2;
 private bool hasEffectId;
 private Int32 effectId_ = 0;
 public bool HasEffectId {
 get { return hasEffectId; }
 }
 public Int32 EffectId {
 get { return effectId_; }
 set { SetEffectId(value); }
 }
 public void SetEffectId(Int32 value) { 
 hasEffectId = true;
 effectId_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasObjId) {
size += pb::CodedOutputStream.ComputeInt32Size(1, ObjId);
}
 if (HasEffectId) {
size += pb::CodedOutputStream.ComputeInt32Size(2, EffectId);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasObjId) {
output.WriteInt32(1, ObjId);
}
 
if (HasEffectId) {
output.WriteInt32(2, EffectId);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 GC_REMOVEEFFECT _inst = (GC_REMOVEEFFECT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.ObjId = input.ReadInt32();
break;
}
   case  16: {
 _inst.EffectId = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasObjId) return false;
 if (!hasEffectId) return false;
 return true;
 }

}


[Serializable]
public class CG_FIGHT : PacketDistributed
{

public const int SceneIDFieldNumber = 1;
 private bool hasSceneID;
 private Int32 SceneID_ = 0;
 public bool HasSceneID {
 get { return hasSceneID; }
 }
 public Int32 SceneID {
 get { return SceneID_; }
 set { SetSceneID(value); }
 }
 public void SetSceneID(Int32 value) { 
 hasSceneID = true;
 SceneID_ = value;
 }

public const int TypeFieldNumber = 2;
 private bool hasType;
 private Int32 Type_ = 0;
 public bool HasType {
 get { return hasType; }
 }
 public Int32 Type {
 get { return Type_; }
 set { SetType(value); }
 }
 public void SetType(Int32 value) { 
 hasType = true;
 Type_ = value;
 }

public const int AttackIdFieldNumber = 3;
 private bool hasAttackId;
 private Int64 AttackId_ = 0;
 public bool HasAttackId {
 get { return hasAttackId; }
 }
 public Int64 AttackId {
 get { return AttackId_; }
 set { SetAttackId(value); }
 }
 public void SetAttackId(Int64 value) { 
 hasAttackId = true;
 AttackId_ = value;
 }

public const int DefenceIdFieldNumber = 4;
 private bool hasDefenceId;
 private Int64 DefenceId_ = 0;
 public bool HasDefenceId {
 get { return hasDefenceId; }
 }
 public Int64 DefenceId {
 get { return DefenceId_; }
 set { SetDefenceId(value); }
 }
 public void SetDefenceId(Int64 value) { 
 hasDefenceId = true;
 DefenceId_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasSceneID) {
size += pb::CodedOutputStream.ComputeInt32Size(1, SceneID);
}
 if (HasType) {
size += pb::CodedOutputStream.ComputeInt32Size(2, Type);
}
 if (HasAttackId) {
size += pb::CodedOutputStream.ComputeInt64Size(3, AttackId);
}
 if (HasDefenceId) {
size += pb::CodedOutputStream.ComputeInt64Size(4, DefenceId);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasSceneID) {
output.WriteInt32(1, SceneID);
}
 
if (HasType) {
output.WriteInt32(2, Type);
}
 
if (HasAttackId) {
output.WriteInt64(3, AttackId);
}
 
if (HasDefenceId) {
output.WriteInt64(4, DefenceId);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_FIGHT _inst = (CG_FIGHT) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.SceneID = input.ReadInt32();
break;
}
   case  16: {
 _inst.Type = input.ReadInt32();
break;
}
   case  24: {
 _inst.AttackId = input.ReadInt64();
break;
}
   case  32: {
 _inst.DefenceId = input.ReadInt64();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasSceneID) return false;
 if (!hasType) return false;
 if (!hasAttackId) return false;
 return true;
 }

}


[Serializable]
public class CG_LEAVE_COPYSCENE : PacketDistributed
{

public const int noParamFieldNumber = 1;
 private bool hasNoParam;
 private Int32 noParam_ = 0;
 public bool HasNoParam {
 get { return hasNoParam; }
 }
 public Int32 NoParam {
 get { return noParam_; }
 set { SetNoParam(value); }
 }
 public void SetNoParam(Int32 value) { 
 hasNoParam = true;
 noParam_ = value;
 }

 private int memoizedSerializedSize = -1;
 public override int SerializedSize()
 {
 int size = memoizedSerializedSize;
 if (size != -1) return size;
 size = 0;
  if (HasNoParam) {
size += pb::CodedOutputStream.ComputeInt32Size(1, NoParam);
}
 memoizedSerializedSize = size;
 return size;
 }

public override void WriteTo(pb::CodedOutputStream output)
 {
 int size = SerializedSize();
  
if (HasNoParam) {
output.WriteInt32(1, NoParam);
}
 }
public override PacketDistributed MergeFrom(pb::CodedInputStream input,PacketDistributed _base) {
 CG_LEAVE_COPYSCENE _inst = (CG_LEAVE_COPYSCENE) _base;
 while (true) {
 uint tag = input.ReadTag();
 switch (tag) {
 case 0:
 {
 return _inst;
 }
    case  8: {
 _inst.NoParam = input.ReadInt32();
break;
}

 }
 }
 return _inst;
 }
//end merged
public override bool IsInitialized() {
  if (!hasNoParam) return false;
 return true;
 }

}

