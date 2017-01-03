#ifndef __CONFIG_H__
#define	__CONFIG_H__

#include "Base.h"
#include "DBStruct/DBStruct.h"
#include "Scene/GameDefine_Scene.h"

class Table_ServerConfigList;

///////////////////////////////////////////////////////////////////////
/////GameConfig
//////////////////////////////////////////////////////////////////////
#define MAX_DISABLE_PACKETID (8)	//GameConfig.ini中最多可以配置的禁制的消息ID
#define MAX_TEXTCONFIG_LENGTH (256) //GameConfig.ini字符串配置项最大长度

class GameConfig
{
public:
	GameConfig()
	{
		CleanUp();
	}
public:
	void	CleanUp();
	void	Load();
	void	ReLoad();
public:
	bool	IsDisablePacket(tint32 nPacketID) const;
	void	LoadSpecificTimeRankConfig();
public:
	tuint32 m_nUserDataSaveDBInterval;


	tint32	m_nPlayerSaveInterval;					// 玩家定时存储间隔，毫秒
	tint32	m_nPlayerCachedDataTimeout;				// 玩家缓存数据超时时间，秒
	tint32	m_nAcceptPlayerPerTick;					// Login每次Tick接受新连接最大数量
	tint32  m_uPortForClient;                       // login对客户端的端口

	tint32  m_nCompatibleVersion;					// 服务器兼容最低版本

	tint32	m_nProcessConnectionHealthLimit;		// 心跳踢人设置

	tfloat32 m_fPlayerViewRadius;					// 玩家视野范围
	tfloat32 m_fPlayerViewEdgeInc;					// 玩家视野边缘增量

	tint32   m_EscapeCountdown;							// 逃亡状态倒计时

	tint32   m_nDBThreadCount;                     // 数据库连接线程

	tint32	 m_nDefaultSceneId;						// 默认场景，大地图

	int64    m_nDefaultFood;                       // 缺省的资源-食物
	int64    m_nDefaultStone;                      // 缺省的资源-石头
	int64    m_nDefaultIron;                       // 缺省的资源-铁
	int64    m_nDefaultGold;                       // 缺省的资源-金币

};

void InitGameConfig(void);
void ReloadGameConfig(void);
const GameConfig& _GameConfig(void);


///////////////////////////////////////////////////////////////////////
/////GMList
//////////////////////////////////////////////////////////////////////
enum GM_ACCESS
{
	GM_ACCESS_INVALID = -1,	
	GM_ACCESS_DEVELOPER = 0 , //研发用或者外网超级GM，拥有全部权限
	GM_ACCESS_LEVEL1 = 1 ,	 //只有部分权限，比如传送、隐身等
	GM_ACCESS_LEVEL2 = 2 ,	
	GM_ACCESS_LEVEL3 = 3 ,
	GM_ACCESS_LEVEL4 = 4 ,

	GM_ACCESS_COUNT ,
};

class GM_List
{
public:
	GM_List( )
	{
		CleanUp( ) ;
	};

	void CleanUp( )
	{
		bstMutexScopedLock LockGuard(m_Mutex);
		m_GMCharList.clear();
		m_IsOpen = false;
	}

public:
	void AddGMChar(const ACCOUNTNAME& rAccount,  tint32 nAccess)
	{
		bstMutexScopedLock LockGuard(m_Mutex);
		if (m_GMCharList.find(rAccount) == m_GMCharList.end())
		{
			m_GMCharList.insert(std::make_pair(rAccount, nAccess) );
		}
	}

	bool IsUserInGmTable(const ACCOUNTNAME& rAccount,  tint32 &nAccess)
	{
		bstMutexScopedLock LockGuard(m_Mutex);

		if (m_GMCharList.find(rAccount) != m_GMCharList.end())	//存在
		{
			nAccess = m_GMCharList[rAccount];
			return true;
		}

		return false;
	}

	bool IsOpenGM() const { return m_IsOpen; }
	void SetIsOpen(bool bValue) { m_IsOpen = bValue; }

private:
	typedef std::map<ACCOUNTNAME, tint32>	GMCharList;
	GMCharList			m_GMCharList;	//【stl】
	mutable bstMutex	m_Mutex; //需要锁
	bool				m_IsOpen;
};
void InitGMListConfig();
void ReLoadGMListConfig();
void LoadGMList();

extern GM_List gGMList;



#endif
