#include "GameServerConfig.h"

GameServerConfig GameServerConfig::m_cfgGameServer;
const char* GameServerConfig::szConfigFile = "ServerCfg/gameserver.cfg";
GameServerConfig::GameServerConfig()
{
	m_nPlayerSaveInterval = 120000;
	m_nPlayerCachedDataTimeout = 600;
}

GameServerConfig::~GameServerConfig(void)
{

}

bool GameServerConfig::loadFromFile()
{
	try
	{
		m_configSrv.readFile(szConfigFile);

		m_nSaveInterval			= m_configSrv.lookup("save_interval");
		m_nErrorSaveEnable		= m_configSrv.lookup("EnableErrorSave");

		m_bCacheEnable			= m_configSrv.lookup("MemCache.EnableFlag");
		m_nCacheFreeCnt			= m_configSrv.lookup("MemCache.FreeCnt");
		m_nCacheSaveInterval	= m_configSrv.lookup("MemCache.SaveInterval");
		m_nCacheSaveUpdateTime	= m_configSrv.lookup("MemCache.SaveUpdateTime");
		m_nCacheRemoveUpdateTime= m_configSrv.lookup("MemCache.RemoveUpdateTime");
		m_nCacheRemoveTime		= m_configSrv.lookup("MemCache.RemoveTime");

		m_nDBThreadCount        = m_configSrv.lookup("DBThread_count");
		m_nAcceptPlayerPerTick  = m_configSrv.lookup("AcceptPlayerPerTick");

	}
	catch (ParseException ex)
	{
		printf("Parsing config file %s failed.\n", szConfigFile);
		return false;
	}
	catch (FileIOException ex) {
		printf("Read config file %s failed. IOExcetpion.\n", szConfigFile);
		return false;
	}
	catch (SettingNotFoundException ex) {
		printf("Read config file %s failed. Setting \"%s\" not found.\n", szConfigFile, ex.getPath());
		return false;
	}
	return true;
}