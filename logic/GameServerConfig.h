#ifndef _GAMESERVERCONFIG_H_
#define _GAMESERVERCONFIG_H_
#pragma once
#include <vector>
#include <string>
#include "Base.h"

#ifdef _WIN32
#pragma warning(disable: 4290)
#include <libconfig.hpp>
#else
#include <libconfig.h++>
#endif

using namespace std;
using namespace libconfig;

class GameServerConfig
{
public:
	GameServerConfig();
	~GameServerConfig(void);

	bool	loadFromFile();

	int		SaveInterval() const { return m_nSaveInterval; }
	void	SaveInterval(int val) { m_nSaveInterval = val; }

	// ÿ���������ܵ������
	int     AcceptPlayerPerTick() const {return m_nAcceptPlayerPerTick;}
	void    AcceptPlayerPerTick(int val) {m_nAcceptPlayerPerTick=val;}

	int     PlayerSaveInterval() const {return m_nPlayerSaveInterval;}

	int     PlayerCacheDataTimeOut() const {return m_nPlayerCachedDataTimeout;}

	int		ErrorSaveEnable() const { return m_nErrorSaveEnable; }
	void	ErrorSaveEnable(int val) { m_nErrorSaveEnable = val; }

	int		CacheEnable() const { return m_bCacheEnable; }
	void	CacheEnable(int val) { m_bCacheEnable = val; }
	int		CacheFreeCnt() const { return m_nCacheFreeCnt; }
	void	CacheFreeCnt(int val) { m_nCacheFreeCnt = val; }
	int		CacheSaveInterval() const { return m_nCacheSaveInterval; }
	void	CacheSaveInterval(int val) { m_nCacheSaveInterval = val; }
	int		CacheSaveUpdateTime() const { return m_nCacheSaveUpdateTime; }
	void	CacheSaveUpdateTime(int val) { m_nCacheSaveUpdateTime = val; }
	int		CacheRemoveUpdateTime() const { return m_nCacheRemoveUpdateTime; }
	void	CacheRemoveUpdateTime(int val) { m_nCacheRemoveUpdateTime = val; }
	int		CacheRemoveTime() const { return m_nCacheRemoveTime; }
	void	CacheRemoveTime(int val) { m_nCacheRemoveTime = val; }

	int     DBThreadCount() const {return m_nDBThreadCount;}


	static GameServerConfig&	Instance(){return m_cfgGameServer;}
protected:
	static const char*		szConfigFile;
	static GameServerConfig	m_cfgGameServer;

	int		m_nSaveInterval;
	int		m_nErrorSaveEnable;

	int		m_bCacheEnable;
	int		m_nCacheFreeCnt;
	int		m_nCacheSaveInterval;
	int		m_nCacheSaveUpdateTime;
	int		m_nCacheRemoveUpdateTime;
	int		m_nCacheRemoveTime;

	// DB���߳�
	int     m_nDBThreadCount;
	// Loginÿ���������ܵ������
	int     m_nAcceptPlayerPerTick;

	// ��Ҷ�ʱ�洢���������
	int     m_nPlayerSaveInterval;

	// ��һ������ݳ�ʱʱ�䣬��
	int	m_nPlayerCachedDataTimeout;				

    
	Config	m_configSrv;
};

#endif


