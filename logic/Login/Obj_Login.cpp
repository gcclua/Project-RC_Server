#include "Obj_Login.h"
#include "Player/Player.h"
#include "Message/LoginMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "common/Config.h"
#include "Message/DBMsg.h"
#include "Packet/Packet/GC_NOTICE_PAK.h"
#include "Packet/Packet/GC_LOGIN_RET_PAK.h"
#include "Packet/Packet/GC_LOGIN_QUEUE_STATUS_PAK.h"
#include "Scene/GameInterface_Scene.h"
#include "Login/GameInterface_Login.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "packet/Packet/GC_CREATEROLE_RET_PAK.h"


Obj_Login::Obj_Login(Player &player)
	: m_rPlayer(player)
	, m_nValidateType(invalid_id)
	, m_bShouldCached(false)
	, m_bIsGM(false)
	, m_nGMAccessLevel(GM_ACCESS_INVALID)
	, m_nQueueIndex(invalid_id)
{
	//�˹��캯��������ʱPlayer��δ�������
	//��Ҫֱ�ӻ���ʹ��player��m_rPlayer
	
}

Obj_Login::~Obj_Login( void )
{
	//����������������ʱPlayer���������
	//��Ҫֱ�ӻ���ʹ��m_rPlayer
}

void Obj_Login::_CleanUp(void)
{
	Player &rPlayer = m_rPlayer;
	(*this).~Obj_Login();
	new(this) Obj_Login(rPlayer);
}

void Obj_Login::OnValidateAccountRet(
	tint32 nResult,
	tint32 nValidateType,
	const ACCOUNTNAME &rAccount,
	const FLString<128> &rDeviceID,
	const FLString<128> &rDeviceType,
	const FLString<128> &rDeviceVersion,
	const FLString<128> &rChannelID,
	const FLString<128> &rMediaID,
	const FLString<128> &rOID,
	const FLString<128> &rAccessToken,
	bool bShouldCached
	)
{
	__ENTER_FUNCTION

		//if (nResult == ValidateResult::OK)
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_VALIDATE_OK);

			m_nValidateType = nValidateType;
			m_szAccount = rAccount;
			m_DeviceID = rDeviceID;
			m_DeviceType = rDeviceType;
			m_DeviceVersion = rDeviceVersion;
			m_ChannelID = rChannelID;
			m_MediaID = rMediaID;
			m_OID = rOID;
			m_AccessToken = rAccessToken;
			m_bShouldCached = bShouldCached;
			m_bIsGM = gGMList.IsUserInGmTable(m_szAccount, m_nGMAccessLevel);
			if (!m_bIsGM)
			{
				m_nGMAccessLevel = GM_ACCESS_INVALID;
			}


			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnValidateAccountRet) ok, validatetype(%d), account(%s), deviceid(%s), devicetype(%s), deviceversion(%s), channelid(%s), mediaid(%s), oid(%s), accesstoken(%s), shouldcached(%s), isgm(%s), gmaccesslevel(%d)",
				m_rPlayer.GetID(),
				m_nValidateType,
				m_szAccount.GetCText(),
				m_DeviceID.GetCText(),
				m_DeviceType.GetCText(),
				m_DeviceVersion.GetCText(),
				m_ChannelID.GetCText(),
				m_MediaID.GetCText(),
				m_OID.GetCText(),
				m_AccessToken.GetCText(),
				m_bShouldCached ? "true" : "false",
				m_bIsGM ? "true" : "false",
				m_nGMAccessLevel);

			AccountStateCheckMsgPtr MsgPtr = POOLDEF_NEW(AccountStateCheckMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_nPlayerID = m_rPlayer.GetID();
			MsgPtr->m_szAccount = m_szAccount;
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

			m_rPlayer.SetStatus(PlayerStatus::LOGIN_ACCOUNTSTATECHECKING);

			// ��½��֤�ɹ���ȥ����һ�ΰ󶨵��ֻ�����
			//BillingInterface::RequestBindPhoneInfo(m_szAccount, m_rPlayer.GetID(), invalid_guid64, false);
		}
		/*else
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_VALIDATE_FAILED);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnValidateAccountRet) failed, result(%d), validatetype(%d)",
				m_rPlayer.GetID(),
				nResult,
				nValidateType);

			Packets::GC_LOGIN_RET_PAK pak;
			pak.m_PacketData.set_result(GC_LOGIN_RET::ACCOUNTVERIFYFAIL);
			pak.m_PacketData.set_validateresult(nResult);
			pak.m_PacketData.set_userid("");
			pak.m_PacketData.set_oid("");
			pak.m_PacketData.set_accesstoken("");
			pak.m_PacketData.set_rapidvalidatecode(RapidValidateCode::INVALID);
			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::CONNECTED);
		}*/

		__LEAVE_FUNCTION
}


void Obj_Login::OnAccountStateCheckRet(bool bRet, bool bQueueOK)
{
	__ENTER_FUNCTION

		if (bRet)
		{
			if (bQueueOK)
			{
				m_rPlayer.SetStatus(PlayerStatus::LOGIN_ACCOUNTSTATECHECK_OK);

				CacheLog(LOGDEF_INST(Login),
					"player(%d) onevent(OnAccountStateCheckRet) ok ok",
					m_rPlayer.GetID());

				BeginQueue();

				m_rPlayer.SetStatus(PlayerStatus::LOGIN_QUEUING);
			}
			else
			{
				m_rPlayer.SetStatus(PlayerStatus::LOGIN_ACCOUNTSTATECHECK_OK);

				CacheLog(LOGDEF_INST(Login),
					"player(%d) onevent(OnAccountStateCheckRet) ok failed",
					m_rPlayer.GetID());

				Packets::GC_LOGIN_RET_PAK pak;
				pak.m_PacketData.set_result(GC_LOGIN_RET::QUEUEFULL);
				pak.m_PacketData.set_validateresult(0);
				pak.m_PacketData.set_userid(0);
				pak.m_PacketData.set_oid("");
				pak.m_PacketData.set_accesstoken("");
				//pak.m_PacketData.set_rapidvalidatecode(RapidValidateCode::INVALID);
				SendPacket(pak);

				m_rPlayer.SetStatus(PlayerStatus::CONNECTED);
			}
		}
		else
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_ACCOUNTSTATECHECK_FAILED);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnAccountStateCheckRet) failed",
				m_rPlayer.GetID());

			Packets::GC_LOGIN_RET_PAK pak;
			pak.m_PacketData.set_result(GC_LOGIN_RET::ALREADYLOGIN);
			pak.m_PacketData.set_validateresult(0);
			pak.m_PacketData.set_userid(0);
			pak.m_PacketData.set_oid("");
			pak.m_PacketData.set_accesstoken("");
			//pak.m_PacketData.set_rapidvalidatecode(RapidValidateCode::INVALID);
			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::CONNECTED);

			//if (_GameConfig().m_bOpenRepeatLoginReplace)
			{
				LoginInterface::KickPlayerByAccount(m_szAccount, PlayerKickReason::REPEATLOGINREPLACE);
			}
		}

		__LEAVE_FUNCTION
}

void Obj_Login::OnQueueFinish(void)
{
	__ENTER_FUNCTION

		m_rPlayer.SetStatus(PlayerStatus::LOGIN_QUEUE_FINISH);

	CacheLog(LOGDEF_INST(Login),
		"player(%d) onevent(OnQueueFinish)",
		m_rPlayer.GetID());

	EndQueue();

	DBAskCharListMsgPtr MsgPtr = POOLDEF_NEW(DBAskCharListMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_nPlayerID = m_rPlayer.GetID();
	MsgPtr->m_AccName = m_szAccount;
	SendMessage2Srv(ServiceID::DBAGENT, MsgPtr);

	m_rPlayer.SetStatus(PlayerStatus::LOGIN_QUERYING_CHARLIST);

	__LEAVE_FUNCTION
}

void Obj_Login::OnCharListRet(tint32 nResult, const DBCharDataList &rList)
{
	__ENTER_FUNCTION

		if (nResult == DBMsgResult::RESULT_SUCCESS)
		{
			

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnCharListRet) ok",
				m_rPlayer.GetID());

			if (rList.m_CharNum>0)
			{
				m_rPlayer.SetStatus(PlayerStatus::LOGIN_QUERY_CHARLIST_OK);
				m_CharList.CopyFrom(rList);

				DBLoadUserMsgPtr MsgPtr = POOLDEF_NEW(DBLoadUserMsg);
				AssertEx(MsgPtr, "");
				MsgPtr->m_UserGuid	  = m_CharList.m_CharDataList[0].m_Guid;
				MsgPtr->m_AccName = m_szAccount;
				MsgPtr->m_nPlayerID = m_rPlayer.GetID();
				SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
			}
			else
			{
				m_rPlayer.SetStatus(PlayerStatus::LOGIN_READYTONEXT);
				
				Packets::GC_LOGIN_RET_PAK pak;
				pak.m_PacketData.set_result(GC_LOGIN_RET::VERSIONNOTMATCH);
				pak.m_PacketData.set_validateresult(0);
				pak.m_PacketData.set_userid(0);
				pak.m_PacketData.set_oid("");
				pak.m_PacketData.set_accesstoken("");
				SendPacket(pak);
				return;
			}
			

			

			//����CMBI��־
			//���	�ֶ�����	Ӣ������	�ֶ�����	�Ƿ����	��ע
			//	1	ʱ��	yyyy-mm-dd HH:mi:ss	�ַ���	��	��
			//	2	��Ϸ��ʶ	appkey	�ַ���	��	��
			//	3	��Ϸ�汾	version	�ַ���	��	��
			//	4	��־ģ����	login	�ַ���	��	Ĭ��ֵ��login��
			//	5	��������־�淶�汾��	normversion	�ַ���	��	
			//	6	�����	stepnumid	�ַ���	��	Ĭ��ֵ��2050��
			//	7	��Ϸ������id	serverid	�ַ���	��	�����ɺ����������id�Ķ��ձ�
			//	8	�ƹ�����id	gamechannel	�ַ���	��	��
			//	9	�˺�id	userid	�ַ���	��	billing���ɵ�userid
			//	10	�˻���	accname	�ַ���	��	������������ע���˺Ż������ƽ̨���ص�id
			//	11	��ɫid	roleid	�ַ���	��	�״ε�½��Ϊ�գ�Ĭ��ֵ��null��
			//	12	��ɫ��	rolename	�ַ���	��	�״ε�½��Ϊ�գ�Ĭ��ֵ��null��
			//	13	��ɫ�ȼ�	rolelevel	������	��	�״ε�½Ĭ��Ϊ��͵ȼ�
			//	14	�豸Ψһ��ʶ	deviceid	�ַ���	��	��
			//	15	��¼ip	ip	�ַ���	��	��
			//	16	��ֵ���������	valueamount	������	��	��ֵ��������磺��ʯ��Ԫ����
			CacheLog(LOGDEF_INST(login), "1login\1%d\1%s\1%s\1%s\1null\1null\1%d\1%s\1%s\1%d",
				2050,
				m_MediaID.GetCText(),
				m_szAccount.GetCText(),		//billing���ɵ�userid
				m_szAccount.GetCText(),		//������������ע���˺Ż������ƽ̨���ص�id
				0,
				m_DeviceID.GetCText(),
				m_rPlayer.GetSocket().m_Host,
				0);

			m_rPlayer.SetStatus(PlayerStatus::LOGIN_LOADING_CHAR);
		}
		else
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_QUERY_CHARLIST_FAILED);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnCharListRet) failed",
				m_rPlayer.GetID());

			AccountOfflineMsgPtr MsgPtr = POOLDEF_NEW(AccountOfflineMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_nPlayerID = m_rPlayer.GetID();
			MsgPtr->m_szAccount = m_szAccount;
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

			Packets::GC_LOGIN_RET_PAK pak;
			pak.m_PacketData.set_result(GC_LOGIN_RET::READROLELISTFAIL);
			pak.m_PacketData.set_validateresult(0);
			pak.m_PacketData.set_userid(0);
			pak.m_PacketData.set_oid("");
			pak.m_PacketData.set_accesstoken("");
			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::CONNECTED);
		}

		__LEAVE_FUNCTION
}

void Obj_Login::OnCreateCharRet(tint32 nResult, const DBFullUserData &rDBUser)
{
	__ENTER_FUNCTION
		if (nResult == DBMsgResult::RESULT_SUCCESS)
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_CREATE_CHAR_OK);

			m_rPlayer.GetObjUser().SerializeFromDB(rDBUser);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnCreateCharRet) ok guid(%lld) name(%s) ip(%s) accname(%s) deviceid(%s)",
				m_rPlayer.GetID(),
				m_rPlayer.GetObjUser().GetGuid(),
				m_rPlayer.GetObjUser().GetName().GetCText(),
				m_rPlayer.GetSocket().m_Host,
				m_szAccount.GetCText(),
				m_DeviceID.GetCText());

				ReqIdleTileMsgPtr MsgPtr = POOLDEF_NEW(ReqIdleTileMsg);
				MsgPtr->m_userId = rDBUser.m_User.m_Guid;
				MsgPtr->m_nPlayerID = m_rPlayer.GetID();
				SendMessage2Srv(ServiceID::WORLDMAP,MsgPtr);

			//Packets::GC_CREATEROLE_RET_PAK pak;
			//pak.m_PacketData.set_result(GC_CREATEROLE_RET::CREATEROLE_SUCCESS);
			//pak.m_PacketData.set_playerguid(m_rPlayer.GetObjUser().GetGuid());
			//pak.m_PacketData.set_playername(m_rPlayer.GetObjUser().GetName().GetCText());
			//SendPacket(pak);

			//���	�ֶ�����	Ӣ������	�ֶ�����	�Ƿ����	��ע
			//	1	ʱ��	yyyy-mm-dd HH:mi:ss	�ַ���	��	��
			//	2	��Ϸ��ʶ	appkey	�ַ���	��	��
			//	3	��Ϸ�汾	version	�ַ���	��	��
			//	4	��־ģ����	rolebuild	�ַ���	��	Ĭ��ֵ��rolebuild��
			//	5	��������־�淶�汾��	normversion	�ַ���	��	
			//	6	�����	stepnumid	�ַ���	��	Ĭ��ֵ��3025��
			//	7	��Ϸ������id	serverid	�ַ���	��	��
			//	8	�ƹ�����id	gamechannel	�ַ���	��	��
			//	9	�˺�id	userid	�ַ���	��	��
			//	10	��ɫid	roleid	�ַ���	��	��
			//	11	��ɫ����	rolename	�ַ���	��	��
			//	12	��ɫְҵid	roletypeid	�ַ���	��	�����ɺ󷵻ؽ�ɫְҵid�Ķ��ձ�
			CacheLog(LOGDEF_INST(rolebuild), "rolebuild\1%d\1%s\1%s\1%lld\1%s\1%d",
				3025,
				m_MediaID.GetCText(),
				m_szAccount.GetCText(),
				m_rPlayer.GetObjUser().GetGuid(),
				m_rPlayer.GetObjUser().GetName().GetCText());

			AuditLog(LOGDEF_INST(Audit_Role), "CreateRole", rDBUser.m_User.m_Guid,
				m_nWorldId,"");

			//m_rPlayer.SetStatus(PlayerStatus::LOGIN_READYENTERWORLD);

		}
		else if (nResult == DBMsgResult::RESULT_SAME_NAME)
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_CREATE_CHAR_FAILED);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnCreateCharRet) failed(samename)",
				m_rPlayer.GetID());

			Packets::GC_CREATEROLE_RET_PAK pak;
			pak.m_PacketData.set_result(GC_CREATEROLE_RET::CREATEROLE_FAIL_NAMEEXIST);
			pak.m_PacketData.set_playerguid(invalid_guid64);
			pak.m_PacketData.set_playername("");
			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::LOGIN_READYTONEXT);
		}
		else
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_CREATE_CHAR_FAILED);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnCreateCharRet) failed(error)",
				m_rPlayer.GetID());

			AccountOfflineMsgPtr MsgPtr = POOLDEF_NEW(AccountOfflineMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_nPlayerID = m_rPlayer.GetID();
			MsgPtr->m_szAccount = m_szAccount;
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

			Packets::GC_CREATEROLE_RET_PAK pak;
			pak.m_PacketData.set_result(GC_CREATEROLE_RET::CREATEROLE_FAIL);
			pak.m_PacketData.set_playerguid(invalid_guid64);
			pak.m_PacketData.set_playername("");
			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::CONNECTED);
		}

		__LEAVE_FUNCTION
}

void Obj_Login::OnLoadCharRet(tint32 nResult, const DBFullUserData &rDBUser, bool bInBR, time_t nBRtime)
{
	__ENTER_FUNCTION

		if (nResult == DBMsgResult::RESULT_SUCCESS)
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_LOAD_CHAR_OK);

			time_t nAnsiTime = _ansitime();
			m_rPlayer.GetObjUser().SerializeFromDB(rDBUser);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnLoadCharRet) ok guid(%lld) name(%s) ip(%s) accname(%s) deviceid(%s)",
				m_rPlayer.GetID(),
				m_rPlayer.GetObjUser().GetGuid(),
				m_rPlayer.GetObjUser().GetName().GetCText(),
				m_rPlayer.GetSocket().m_Host,
				m_szAccount.GetCText(),
				m_DeviceID.GetCText());

			

			Packets::GC_LOGIN_RET_PAK pak;
			pak.m_PacketData.set_result(GC_LOGIN_RET::SUCCESS);
			pak.m_PacketData.set_validateresult(0);
			pak.m_PacketData.set_oid(m_OID.GetCText());
			pak.m_PacketData.set_accesstoken(m_AccessToken.GetCText());
			pak.m_PacketData.set_userid(m_CharList.m_CharDataList[0].m_Guid);
			pak.m_PacketData.set_playername(m_CharList.m_CharDataList[0].m_CharName);
			pak.m_PacketData.set_level(0);
			m_rPlayer.GetObjUser().FillGCLogin(pak.m_PacketData);
			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::LOGIN_READYENTERWORLD);
			//m_rPlayer.SetStatus(PlayerStatus::GAME_PLAYERING);
		}
		else
		{
			m_rPlayer.SetStatus(PlayerStatus::LOGIN_LOAD_CHAR_FAILED);

			CacheLog(LOGDEF_INST(Login),
				"player(%d) onevent(OnLoadCharRet) failed",
				m_rPlayer.GetID());

			AccountOfflineMsgPtr MsgPtr = POOLDEF_NEW(AccountOfflineMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_nPlayerID = m_rPlayer.GetID();
			MsgPtr->m_szAccount = m_szAccount;
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);


			Packets::GC_LOGIN_RET_PAK pak;
			pak.m_PacketData.set_result(GC_LOGIN_RET::READROLELISTFAIL);
			pak.m_PacketData.set_validateresult(0);
			pak.m_PacketData.set_oid(m_OID.GetCText());
			pak.m_PacketData.set_accesstoken(m_AccessToken.GetCText());
			pak.m_PacketData.set_userid(m_CharList.m_CharDataList[0].m_Guid);
			pak.m_PacketData.set_playername(m_CharList.m_CharDataList[0].m_CharName);
			pak.m_PacketData.set_level(0);

			SendPacket(pak);

			m_rPlayer.SetStatus(PlayerStatus::CONNECTED);
		}

		__LEAVE_FUNCTION
}

void Obj_Login::BeginQueue(void)
{
	__ENTER_FUNCTION

		m_nQueueIndex = 9998;

	Packets::GC_LOGIN_QUEUE_STATUS_PAK pak;
	pak.m_PacketData.set_status(GC_LOGIN_QUEUE_STATUS::BEGINQUEUE);
	pak.m_PacketData.set_index(m_nQueueIndex);
	SendPacket(pak);

	__LEAVE_FUNCTION
}

void Obj_Login::UpdateQueue(tint32 nQueueIndex)
{
	__ENTER_FUNCTION

		if (m_nQueueIndex != nQueueIndex)
		{
			m_nQueueIndex = nQueueIndex;

			Packets::GC_LOGIN_QUEUE_STATUS_PAK pak;
			pak.m_PacketData.set_status(GC_LOGIN_QUEUE_STATUS::QUEUING);
			pak.m_PacketData.set_index(m_nQueueIndex);
			SendPacket(pak);
		}

		__LEAVE_FUNCTION
}

void Obj_Login::EndQueue(void)
{
	__ENTER_FUNCTION

		m_nQueueIndex = invalid_id;

	Packets::GC_LOGIN_QUEUE_STATUS_PAK pak;
	pak.m_PacketData.set_status(GC_LOGIN_QUEUE_STATUS::ENDQUEUE);
	pak.m_PacketData.set_index(m_nQueueIndex);
	SendPacket(pak);

	__LEAVE_FUNCTION
}

tint32 Obj_Login::GetQueuingLevel(void) const
{
	if (m_bIsGM)
	{
		return PlayerQueuingData::QUEUINGLEVEL_GM;
	}

	//if ((!m_bShouldCached) &&
		//RapidValidateCode::IsValidate(m_nRapidValidateCode))
	//{
		//return PlayerQueuingData::QUEUINGLEVEL_RECONNECTION;
	//}

	return PlayerQueuingData::QUEUINGLEVEL_NORMAL;
}

void Obj_Login::SendPacket( const Packet &rPacket )
{
	__ENTER_FUNCTION

		m_rPlayer.SendPacket(rPacket);

	__LEAVE_FUNCTION
}

void Obj_Login::SendNotice( const tchar* szNotice )
{
	__ENTER_FUNCTION

		if (szNotice != null_ptr)
		{
			Packets::GC_NOTICE_PAK pak;
			pak.m_PacketData.set_notice(szNotice);
			SendPacket(pak);
		}

		__LEAVE_FUNCTION
}

tuint32 Obj_Login::HandlePacket( ::CG_LOGIN &rPacket )
{
	__ENTER_FUNCTION

		tint32 vtype = rPacket.vtype();
	tint32 gameversion = rPacket.gameversion();
	tint32 programversion = rPacket.programversion();
	tint32 publicresourceversion = rPacket.publicresourceversion();
	tint32 maxpacketid = rPacket.maxpacketid();
	bool forceenter = (rPacket.forceenter() != 0);
	FLString<128> deviceid(rPacket.deviceid().c_str());
	FLString<128> devicetype(rPacket.devicetype().c_str());
	FLString<128> deviceversion(rPacket.deviceversion().c_str());

	ACCOUNTNAME account(rPacket.account().c_str());

	FLString<128> channelid(rPacket.channelid().c_str());
	FLString<128> mediachannel(rPacket.mediachannel().c_str());

	tint32 rapidvalidatecode = rPacket.rapidvalidatecode();

	
	//��֤�ͻ�����Ϣ�����ID
	/*if ((maxpacketid != (tint32)Packets::PACKET_MAX))
	{
		if ( !(forceenter && maxpacketid < (tint32)Packets::PACKET_MAX) )
		{
			//��Ϣ����һ�²������½
			CacheLog(LOGDEF_INST(Error), "maxpacketid Not Match! ClientMaxId:%d ServerMaxId:%d",
				maxpacketid,
				(tint32)Packets::PACKET_MAX);

			Packets::GC_LOGIN_RET_PAK pak;
			pak.m_PacketData.set_result(GC_LOGIN_RET::PACKETNOTMATCH);
			pak.m_PacketData.set_validateresult(0);
			pak.m_PacketData.set_userid(0);
			pak.m_PacketData.set_oid("");
			pak.m_PacketData.set_accesstoken("");
			//pak.m_PacketData.set_rapidvalidatecode(RapidValidateCode::INVALID);
			SendPacket(pak);

			return PACKET_EXE_CONTINUE;
		}
	}*/



	CacheLog(LOGDEF_INST(Login),
		"player(%d) onpacket(CG_LOGIN)",
		m_rPlayer.GetID());

	m_rPlayer.SetStatus(PlayerStatus::LOGIN_VALIDATING);
	m_szAccount = account;
	AccountStateCheckMsgPtr MsgPtr = POOLDEF_NEW(AccountStateCheckMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_nPlayerID = m_rPlayer.GetID();
	MsgPtr->m_szAccount = m_szAccount;
	SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

	m_rPlayer.SetStatus(PlayerStatus::LOGIN_ACCOUNTSTATECHECKING);

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}

tuint32 Obj_Login::HandlePacket(::CG_CREATEROLE &rPacket)
{
	__ENTER_FUNCTION


		FLString<128> szName(rPacket.name().c_str());
		if (SceneInterface::IsNameScreening(szName.GetCText(),true))
		{
			CacheLog(LOGDEF_INST(Login),
				"player(%d) onpacket(CG_CREATEROLE) failed(namescreening)",
				m_rPlayer.GetID());

			Packets::GC_CREATEROLE_RET_PAK pak;
			pak.m_PacketData.set_result(GC_CREATEROLE_RET::CREATEROLE_FAIL_NAMESCREENING);
			pak.m_PacketData.set_playerguid(invalid_guid64);
			pak.m_PacketData.set_playername("");
			SendPacket(pak);

			return PACKET_EXE_CONTINUE;
		}
		//����1*3
		if ( szName.GetLength() > CREATE_MAX_NAME_SIZE )
		{
			CacheLog(LOGDEF_INST(Login),
				"player(%d) onpacket(CG_CREATEROLE) failed(longname)",
				m_rPlayer.GetID());

			Packets::GC_CREATEROLE_RET_PAK pak;
			pak.m_PacketData.set_result(GC_CREATEROLE_RET::CREATEROLE_FAIL_LONGNAME);
			pak.m_PacketData.set_playerguid(invalid_guid64);
			pak.m_PacketData.set_playername("");
			SendPacket(pak);

			return PACKET_EXE_CONTINUE;
		}

		int gender = rPacket.gender();


		DBCreateCharMsgPtr MsgPtr = POOLDEF_NEW(DBCreateCharMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_AccName   = m_szAccount;
		MsgPtr->m_nPlayerID = m_rPlayer.GetID();
		MsgPtr->m_UserData.InitAsCreateNewChar(szName.GetCText(), m_szAccount.GetCText(),gender);
		SendMessage2Srv(ServiceID::DBAGENT, MsgPtr);

		CacheLog(LOGDEF_INST(Login),
			"player(%d) onpacket(CG_CREATEROLE)",
			m_rPlayer.GetID());

		m_rPlayer.SetStatus(PlayerStatus::LOGIN_CREATING_CHAR);

		return PACKET_EXE_CONTINUE;

		__LEAVE_FUNCTION
			return PACKET_EXE_CONTINUE;
}



