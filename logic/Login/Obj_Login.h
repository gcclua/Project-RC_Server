
#ifndef _OBJ_LOGIN_H_
#define _OBJ_LOGIN_H_

#include "Base.h"
#include "Service/TimeInfo.h"
#include "DBStruct/DBStruct_User.h"
#include "scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_CharList.h"

class Player;
class Packet;

class CG_LOGIN;
class CG_CREATEROLE;


class Obj_Login
{
public:
	explicit Obj_Login(Player &player);
	virtual ~Obj_Login(void);
private:
	Player &m_rPlayer;

public:
	void _CleanUp(void);

public:
	tint32 GetValidateType(void) const {return m_nValidateType;}
	const ACCOUNTNAME &GetAccount(void) const {return m_szAccount;}
	const FLString<128> &GetDeviceID(void) const {return m_DeviceID;}
	const FLString<128> &GetDeviceType(void) const {return m_DeviceType;}
	const FLString<128> &GetDeviceVersion(void) const {return m_DeviceVersion;}
	const FLString<128> &GetChannelID(void) const {return m_ChannelID;}
	const FLString<128> &GetMediaID(void) const {return m_MediaID;}
	const FLString<128> &GetOID(void) const {return m_OID;}
	const FLString<128> &GetAccessToken(void) const {return m_AccessToken;}
	bool GetShouldCached(void) const {return m_bShouldCached;}
	bool GetIsGM(void) const {return m_bIsGM;}
	tint32 GetGMAccessLevel(void) const {return m_nGMAccessLevel;}
private:
	tint32 m_nValidateType;
	ACCOUNTNAME m_szAccount;
	FLString<128> m_DeviceID;
	FLString<128> m_DeviceType;
	FLString<128> m_DeviceVersion;
	FLString<128> m_ChannelID;
	FLString<128> m_MediaID;
	FLString<128> m_OID;
	FLString<128> m_AccessToken;
	bool m_bShouldCached;
	bool m_bIsGM;
	tint32 m_nGMAccessLevel;
private:
	DBCharDataList m_CharList;
	int            m_nWorldId;

public:
	void OnValidateAccountRet(
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
		bool bShouldCached);
	void OnAccountStateCheckRet(bool bRet, bool bQueueOK);
	void OnQueueFinish(void);
	void OnCharListRet(tint32 nResult, const DBCharDataList &rList);
	void OnCreateCharRet(tint32 nResult, const DBFullUserData &rDBUser);
	void OnLoadCharRet(tint32 nResult, const DBFullUserData &rDBUser, bool bInBR, time_t nBRtime);

public:
	void BeginQueue(void);
	void UpdateQueue(tint32 nQueueIndex);
	void EndQueue(void);
public:
	tint32 GetQueuingLevel(void) const;
private:
	tint32 m_nQueueIndex;

public:
	void SendPacket(const Packet &rPacket);
	void SendNotice(const tchar* szNotice);

public:
	tuint32 HandlePacket(::CG_LOGIN &rPacket);
	tuint32 HandlePacket(::CG_CREATEROLE &rPacket);
};



#endif