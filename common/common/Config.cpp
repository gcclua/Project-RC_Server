
#include "Config.h"
#include "IniFile.h"
#include "Table/Table_ServerConfigList.h"

///////////////////////////////////////////////////////////////////////
/////GameConfig
//////////////////////////////////////////////////////////////////////
#define FILE_GAME_CONFIG	"./Config/GameConfig.ini"

GameConfig gGameConfig;

void	GameConfig::CleanUp()
{
	__ENTER_FUNCTION

	m_nUserDataSaveDBInterval = 0;


	m_nPlayerSaveInterval = 120000;
	m_nPlayerCachedDataTimeout = 600;
	m_nAcceptPlayerPerTick = 20;					//Login每次Tick接受新连接最大数量

	m_nCompatibleVersion = 0;

	m_nProcessConnectionHealthLimit = 20;

	
	m_fPlayerViewRadius = 10.0f;
	m_fPlayerViewEdgeInc = 4.0f;

	m_EscapeCountdown              = 15000;
	m_nDBThreadCount = 16;

	m_nDefaultSceneId = invalid_id;	
	m_nDefaultFood  = 0;
	m_nDefaultStone = 0;
	m_nDefaultIron  = 0;
	m_nDefaultGold  = 0;


	__LEAVE_FUNCTION
}
void	GameConfig::Load()
{
	__ENTER_FUNCTION

	IniFile ini;

	AssertEx(ini.Open(FILE_GAME_CONFIG),"There is no GameConfig.ini");

	tint32	 nValue=0;
	tfloat32 fValue = 0.0f;
	tuint32  uValue=0;
	tchar	 szValue[MAX_TEXTCONFIG_LENGTH]={0};
	
	AssertEx(ini.ReadUInt("DataBase", "UserDataSaveDBInterval", uValue),"");
	m_nUserDataSaveDBInterval = (uValue > 0) ? uValue : DB_USER_SAVE_DB_INTERVAL;

	AssertEx(ini.ReadInt("DataBase", "DBThreadCount", nValue), "");
	m_nDBThreadCount = nValue;

	AssertEx(ini.ReadInt("Login", "PlayerSaveInterval", nValue), "");
	m_nPlayerSaveInterval = nValue;

	AssertEx(ini.ReadInt("Login", "PlayerSaveInterval", nValue), "");
	m_nPlayerSaveInterval = nValue;
	AssertEx(ini.ReadInt("Login", "PlayerCachedDataTimeout", nValue), "");
	m_nPlayerCachedDataTimeout = nValue;

	AssertEx(ini.ReadInt("Login", "AcceptPlayerPerTick", nValue), "");
	m_nAcceptPlayerPerTick = nValue;

	AssertEx(ini.ReadInt("Login", "PortForClient", nValue), "");
	m_uPortForClient = nValue;

	AssertEx(ini.ReadFloat("PlayerView", "PlayerViewRadius", fValue), "");
	m_fPlayerViewRadius = fValue;
	AssertEx(ini.ReadFloat("PlayerView", "PlayerViewEdgeInc", fValue), "");
	m_fPlayerViewEdgeInc = fValue;

	AssertEx(ini.ReadInt("Escape", "EscapeCountdown", nValue), "");
	m_EscapeCountdown = nValue;

	AssertEx(ini.ReadInt("DefaultCharPosition", "DefaultSceneId", nValue), "");
	m_nDefaultSceneId = nValue;

	AssertEx(ini.ReadInt("DefaultResource", "Food", nValue), "");
	m_nDefaultFood = nValue;

	AssertEx(ini.ReadInt("DefaultResource", "Stone", nValue), "");
	m_nDefaultStone = nValue;

	AssertEx(ini.ReadInt("DefaultResource", "Iron", nValue), "");
	m_nDefaultIron = nValue;

	AssertEx(ini.ReadInt("DefaultResource", "Gold", nValue), "");
	m_nDefaultGold = nValue;

	__LEAVE_FUNCTION
}
//todo gaona 上线前整理需要ReLoad加载的配置项 
void	GameConfig::ReLoad()
{
	__ENTER_FUNCTION

	IniFile ini;

	AssertEx(ini.Open(FILE_GAME_CONFIG),"There is no GameConfig.ini");

	tuint32  uValue=0;
	tint32	nValue=0;
	tfloat32 fValue = 0.0f;
	
	//放于此函数内可以Relaod的配置项，需要是可以进行原子访问的类型，例如 int，bool，float，byte等基本类型。

	AssertEx(ini.ReadUInt("DataBase", "UserDataSaveDBInterval", uValue),"");
	m_nUserDataSaveDBInterval = (uValue > 0) ? uValue : DB_USER_SAVE_DB_INTERVAL;

	AssertEx(ini.ReadInt("DataBase", "DBThreadCount", nValue), "");
	m_nDBThreadCount = nValue;

	AssertEx(ini.ReadFloat("PlayerView", "PlayerViewRadius", fValue), "");
	m_fPlayerViewRadius = fValue;
	AssertEx(ini.ReadFloat("PlayerView", "PlayerViewEdgeInc", fValue), "");
	m_fPlayerViewEdgeInc = fValue;

	AssertEx(ini.ReadInt("Login", "PlayerSaveInterval", nValue), "");
	m_nPlayerSaveInterval = nValue;
	AssertEx(ini.ReadInt("Login", "PlayerCachedDataTimeout", nValue), "");
	m_nPlayerCachedDataTimeout = nValue;
	AssertEx(ini.ReadInt("Login", "AcceptPlayerPerTick", nValue), "");
	m_nAcceptPlayerPerTick = nValue;

	AssertEx(ini.ReadInt("Login", "PortForClient", nValue), "");
	m_uPortForClient = nValue;

	AssertEx(ini.ReadInt("Login", "CompatibleVersion", nValue), "");
	m_nCompatibleVersion = nValue;

	AssertEx(ini.ReadInt("Login", "ProcessConnectionHealthLimit", nValue), "");
	m_nProcessConnectionHealthLimit = nValue;

	AssertEx(ini.ReadInt("Escape", "EscapeCountdown", nValue), "");
	m_EscapeCountdown = nValue;

	__LEAVE_FUNCTION
} 
bool GameConfig::IsDisablePacket(tint32 nPacketID) const
{
	
	return false;
}

void InitGameConfig(void)
{
	__ENTER_FUNCTION

	gGameConfig.Load();

	__LEAVE_FUNCTION
}
void ReloadGameConfig(void)
{
	__ENTER_FUNCTION

	gGameConfig.ReLoad();

	__LEAVE_FUNCTION
}
const GameConfig & _GameConfig(void)
{
	return gGameConfig;
}

#define FILE_GMLIST	"./Config/GMList.ini"
GM_List gGMList;

void InitGMListConfig()
{
	__ENTER_FUNCTION

	LoadGMList();

	__LEAVE_FUNCTION
}

void ReLoadGMListConfig()
{
	__ENTER_FUNCTION

	LoadGMList();

	__LEAVE_FUNCTION
}

void LoadGMList()
{
	__ENTER_FUNCTION

	IniFile ini;
	AssertEx(ini.Open(FILE_GMLIST),"There is no GMList.ini");
	gGMList.CleanUp();

	tint32 nIsOpen=0;
	AssertEx(ini.ReadInt("GM", "IsOpen", nIsOpen), "This is no IsOpen");
	gGMList.SetIsOpen(nIsOpen>0?true:false);

	tint32 nMaxCount = 0;
	AssertEx(ini.ReadInt("GM", "MaxCount", nMaxCount), "This is no MaxCount");

	tchar szFullCount[MAX_ACCOUNT_SIZE];
	tint32 nAccess = GM_ACCESS_INVALID;
	tchar szAccount[MAX_ACCOUNT_SIZE];
	tchar szAccess[MAX_ACCOUNT_SIZE];
	for( tint32 i=0; i<nMaxCount && i<4096; ++i )
	{
		nAccess = GM_ACCESS_INVALID;
		memset(szFullCount,0,sizeof(szFullCount));
		memset(szAccount,0,sizeof(szAccount));
		memset(szAccess,0,sizeof(szAccess));

		tsnprintf( szAccount, sizeof(szAccount),"Account%d", i ) ;
		tsnprintf( szAccess, sizeof(szAccess),"Access%d", i ) ;

		if(false == ini.ReadText("GM", szAccount, szFullCount, MAX_ACCOUNT_SIZE))
		{
			//DiskLog(LOGDEF_INST(ServerStatus),"LoadGMList() Loading Account%d ... Error", i); 
		}
		if (false == ini.ReadInt("GM", szAccess, nAccess))
		{
			//DiskLog(LOGDEF_INST(ServerStatus),"LoadGMList() Loading Access%d ... Error", i); 
		}
		
		ACCOUNTNAME AccountName(szFullCount);
		gGMList.AddGMChar(AccountName, nAccess);
	}

	__LEAVE_FUNCTION
}

