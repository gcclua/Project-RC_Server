#ifndef __CONFIG_H__
#define	__CONFIG_H__

#include "Base.h"
#include "DBStruct/DBStruct.h"
#include "Scene/GameDefine_Scene.h"

class Table_ServerConfigList;

///////////////////////////////////////////////////////////////////////
/////GameConfig
//////////////////////////////////////////////////////////////////////
#define MAX_DISABLE_PACKETID (8)	//GameConfig.ini�����������õĽ��Ƶ���ϢID
#define MAX_TEXTCONFIG_LENGTH (256) //GameConfig.ini�ַ�����������󳤶�

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


	tint32	m_nPlayerSaveInterval;					// ��Ҷ�ʱ�洢���������
	tint32	m_nPlayerCachedDataTimeout;				// ��һ������ݳ�ʱʱ�䣬��
	tint32	m_nAcceptPlayerPerTick;					// Loginÿ��Tick�����������������
	tint32  m_uPortForClient;                       // login�Կͻ��˵Ķ˿�

	tint32  m_nCompatibleVersion;					// ������������Ͱ汾

	tint32	m_nProcessConnectionHealthLimit;		// ������������

	tfloat32 m_fPlayerViewRadius;					// �����Ұ��Χ
	tfloat32 m_fPlayerViewEdgeInc;					// �����Ұ��Ե����

	tint32   m_EscapeCountdown;							// ����״̬����ʱ

	tint32   m_nDBThreadCount;                     // ���ݿ������߳�

	tint32	 m_nDefaultSceneId;						// Ĭ�ϳ��������ͼ

	int64    m_nDefaultFood;                       // ȱʡ����Դ-ʳ��
	int64    m_nDefaultStone;                      // ȱʡ����Դ-ʯͷ
	int64    m_nDefaultIron;                       // ȱʡ����Դ-��
	int64    m_nDefaultGold;                       // ȱʡ����Դ-���

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
	GM_ACCESS_DEVELOPER = 0 , //�з��û�����������GM��ӵ��ȫ��Ȩ��
	GM_ACCESS_LEVEL1 = 1 ,	 //ֻ�в���Ȩ�ޣ����紫�͡������
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

		if (m_GMCharList.find(rAccount) != m_GMCharList.end())	//����
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
	GMCharList			m_GMCharList;	//��stl��
	mutable bstMutex	m_Mutex; //��Ҫ��
	bool				m_IsOpen;
};
void InitGMListConfig();
void ReLoadGMListConfig();
void LoadGMList();

extern GM_List gGMList;



#endif
