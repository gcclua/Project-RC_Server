
#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_

#include "player.h"
#include "service/TimeInfo.h"

#define  PROCESSCONNECTIONTIME 6000

class PlayerManager
{
public:
	PlayerManager(void);
	virtual ~PlayerManager(void);


public:
	virtual void Init(void);
	virtual void Tick(const TimeInfo &rTimeInfo);

protected:
	void QuerySockets(void);
	void ProcessInputs(void);
	void ProcessOutputs(void);
	void ProcessExceptions(void);
	void ProcessCommand(void);
	virtual void ProcessTicks(const TimeInfo &rTimeInfo) = 0;
	void ProcessConnection(const TimeInfo &rTimeInfo);

protected:
	int m_nProcessCoonectTime;

public:
	enum 
	{
		ADD_FOR_NEWPLAYER, // 添加Player,玩家建立连接
		ADD_FOR_ENTREWORLD, //添加Player,玩家首次进入场景
	};

	enum 
	{
		DEL_FOR_INPUTEXP1=1,    // 删除Player,收包异常
		DEL_FOR_INPUTEXP2,
		DEL_FOR_INPUTEXP3,

		DEL_FOR_OUTPUTEXP1=10,  // 删除Player,发包异常
		DEL_FOR_OUTPUTEXP2,
		DEL_FOR_OUTPUTEXP3,

		DEL_FOR_EXP = 20,      // 删除Player,连接异常

		DEL_FOR_COMMANDEXP1=30,    // 处理包异常
		DEL_FOR_COMMANDEXP2,
		DEL_FOR_COMMANDEXP3,

		Del_FOR_CONNECTEXP1 =40,
		Del_FOR_CONNECTEXP2,
		Del_FOR_CONNECTEXP3,

		DEL_FOR_DEALL,

		DEL_FOR_LOGINTICK1,
		DEL_FOR_LOGINTICK2,

		DEL_FOR_ENTERWORLD,
	};

public:

	// 添加指定的Player
	void Add(PlayerPtr Ptr,int nResult);

	// 删除指定的Player，删除成功后返回下一个元素的迭代器，否则返回End
	PlayerPtrList::iterator Del(PlayerPtr Ptr,int nResult);
public:
	void DelAll(void);

protected:
	virtual void OnAddPlayer(PlayerPtr Ptr,int nResult) = 0;
	virtual void OnDelPlayer(PlayerPtr Ptr,int nResult) = 0;
protected:
	PlayerPtrList m_PlayerList;

#if defined(__USE_SELECT__)
protected:
	fd_set m_ReadSet;
	fd_set m_WriteSet;
	fd_set m_ExceptSet;
#endif

#if defined(__USE_POOL)
protected:
	typedef bsvector<pollfd> PollFDVector;
	PollFDVector m_PollFDVector;
#endif

};



#endif