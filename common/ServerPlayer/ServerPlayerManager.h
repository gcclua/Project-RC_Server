#ifndef _SERVERPLAYERMANAGER_H_
#define _SERVERPLAYERMANAGER_H_

#include "ServerPlayer.h"
#include "Service/TimeInfo.h"

class ServerPlayerManager
{
public:
	ServerPlayerManager(void);
	~ServerPlayerManager(void);

public:
	void Tick(const TimeInfo &rTimeInfo);

protected:
	void QuerySockets(void);
	void ProcessInputs(void);
	void ProcessOutputs(void);
	void ProcessExceptions(void);
	void ProcessCommands(void);

public:
	void Add(ServerPlayerPtr Ptr);
	ServerPlayerPtrList::iterator Del(ServerPlayerPtr Ptr);
public:
	void DelAll(void);

protected:
	ServerPlayerPtrList m_ServerPlayerList;	//¡¾stl¡¿

#if defined(__USE_SELECT__)
protected:
	fd_set m_ReadSet;
	fd_set m_WriteSet;
	fd_set m_ExceptSet;
#endif

#if defined(__USE_POLL__)
protected:
	typedef bsvector<pollfd> PollFDVector;
	PollFDVector m_PollFDVector;	//¡¾stl¡¿
#endif
};

#endif
