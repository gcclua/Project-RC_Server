#define _CRT_SECURE_NO_WARNINGS
#include "GameNetHandler.h"

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../net/NetCache.h"
#include "../common/Clock.h"
#include "AdminHandler.h"
#include "PolicyHandler.h"
#include "../common/SysLog.h"
#include "string-util.h"

extern ServerConfig serverConfig;

GameNetHandler::GameNetHandler(EventQueue *eventQueue, int nid)
: eq(eventQueue), nid_(nid)
{
	pthread_mutex_init(&kick_mutex, NULL);
	pthread_mutex_init(&join_mutex, NULL);
}

void GameNetHandler::addUser(int fd, int64 uid)
{
	lockjoin();
	map<int, int64>::iterator itor = mapJoinFd.find(fd);
	if(itor == mapJoinFd.end())
	{
		mapJoinFd.insert(make_pair(fd, uid));
	}
	else
	{
		mapJoinFd[fd] = uid;
	}
	unlockjoin();
}

void GameNetHandler::kickUser(int fd, int64 uid)
{
	lockkick();
	map<int, int64>::iterator itor = mapKickFd.find(fd);
	if(itor == mapKickFd.end())
	{
		mapKickFd.insert(make_pair(fd, uid));
	}
	else
	{
		mapKickFd[fd] = uid;
	}
	unlockkick();
}

bool GameNetHandler::sendToWorld(int fd, const string& str) 
{
	if(fd <= 0)
	{
		int currWorld = nid_ / (serverConfig.gamedNum() / serverConfig.worlddNum());
        if(currWorld >= serverConfig.worlddNum())
        {
            currWorld = serverConfig.worlddNum() - 1;
        }
		for(size_t i = 0; i < WorldServer.size(); i++ )
		{
			if(WorldServer[currWorld].Status == NET_ACTIVE)
			{
				break;
			}
			currWorld ++; 
			if(currWorld >= serverConfig.worlddNum())
			{
				currWorld = 0;
			}
		}
		if(WorldServer[currWorld].Status != NET_ACTIVE)
		{
			return false; 
		}
		fd = WorldServer[currWorld].iFd;
	}
	return sendIntSizedFdString(fd, str);
}

bool GameNetHandler::sendDataToClient(int fd, int type, const string& str)
{
	if(fd > 0)
	{
		return sendSizedTypeFdString(fd, type, str);
	}
	return false;
}

bool GameNetHandler::isListenSocket(int fd)
{
	return fd==clientfd || fd==adminfd || fd==policyfd;
}

bool GameNetHandler::isConnectSocket(int fd)
{
    for (size_t i = 0; i < WorldServer.size(); i++)
    {
        if ( WorldServer[i].iFd == fd )
        {
            return true;
        }
    }
	
	return false;
}
bool GameNetHandler::isConnecting(int fd)
{
    for (size_t i = 0; i < WorldServer.size(); i++)
    {
        if ( WorldServer[i].iFd == fd )
        {
            if ( WorldServer[i].Status == NET_CONNECTING )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

bool GameNetHandler::connectSuccess(int fd)
{
	for(size_t i = 0; i<WorldServer.size(); i++)
	{
		if(WorldServer[i].iFd == fd)
		{
			// register to world server
			char buf[16];
			sprintf(buf, "a,%d", nid_);
			if(!sendIntSizedFdString(fd, string(buf)))
			{
				
			}
			WorldServer[i].Status = NET_ACTIVE;
			return true;
		}
	}

	
    return true;
}

int GameNetHandler::readCacheSize(int listenFd)
{
	return isConnectSocket(listenFd) ? DEFAULT_SERVER_SIZE
		: DEFAULT_CLIENT_SIZE;
}

void GameNetHandler::createProtocolHandler(NetCache *cache, int listenFd)
{
	int nfd = cache->fd;
	if (listenFd==adminfd)
	{
		cache->ph = new AdminHandler(this, nfd, nid_);
		//LOG4CXX_DEBUG(logger_, "Admin connected from "<<cache->addrstr()<<" into fd:"<<nfd);
	}
	else if (listenFd==policyfd)
	{
		cache->ph = new PolicyHandler(this, nfd);
		//LOG4CXX_DEBUG(logger_, "Policy client connected from "<<cache->addrstr()<<" into fd:"<<nfd);
	}
}

int GameNetHandler::connectFailed(int connectFd)
{
	if (isConnectSocket(connectFd)) 
	{
		bool bFind=false;
        for (size_t i = 0; i < WorldServer.size(); i++ )
        {
            if ( WorldServer[i].iFd == connectFd )
            {
                WorldServer[i].iFd = 0;
                WorldServer[i].Status = NET_DOWN ;
				bFind = true;
            }
        }
		if(bFind)
		{
			//connectToWorld();
			return 0;
		}


    }
    return 0;
}

bool GameNetHandler::preNetEvent(time_t now)
{
	kickIdleClients(now);
	keepAliveWithWordAndPKSrv(now);

	lockjoin();
	if(mapJoinFd.size() > 0)
	{
		map<int, int64>::iterator iter = mapJoinFd.begin();
		while(iter != mapJoinFd.end())
		{
			NetCache* cache = getCacheFromFd(iter->first);
			if(cache != NULL)
			{
				cache->uid = iter->second;
			}
			++iter;
		}
		mapJoinFd.clear();
	}
	unlockjoin();

	lockkick();
	if (mapKickFd.size() > 0)
	{
		map<int, int64>::iterator iter = mapKickFd.begin();
		while(iter != mapKickFd.end())
		{
			NetCache* cache = getCacheFromFd(iter->first);
			if(cache != NULL && cache->uid == iter->second)
			{
				doCloseConnection(iter->first);
			}
			++iter;
		}
		mapKickFd.clear();
	}
	unlockkick();
	return true;
}

void GameNetHandler::kickIdleClients(time_t now)
{
	if ((now-last_timeout_check)>(1000*30))
	{
		last_timeout_check = now;
		map<int,NetCache*>::const_iterator it = fdCache.begin();
		vector<int> idleList;
		idleList.clear();
		for (it=fdCache.begin(); it!=fdCache.end(); it++)
		{
			NetCache *cache = it->second;
			if (cache!=NULL && cache->ph!=NULL
				&& cache->ph->handlerType()==ProtocolHandler::CLIENT)
			{
				if (cache->idle)
				{
					idleList.push_back(cache->fd);
					int64 uid = cache->uid;
					if (uid>0)
					{
						cache->ph->leave(uid);
					}
				}
				else
				{
					cache->idle = true;
				}
			}
		}
		if (idleList.size()>0)
		{
			for (size_t i=0; i<idleList.size(); i++)
			{
				doCloseConnection(idleList[i]);
			}
		}
	}
}

/*bool GameNetHandler::connectToWorld( ) {
	if( WorldServer.size() == 0 )
	{
		for(int i = 0; i<serverConfig.worlddNum(); i++)
		{
			NetSockState worldd; 
			memset(&worldd,0, sizeof(worldd)); 
			worldd.Status = NET_DOWN; 
			WorldServer.push_back( worldd ); 
		}
	}

	for(int i = 0; i<serverConfig.worlddNum(); i++)
	{
		time_t  tNow = time(NULL); 
		if((WorldServer[i].Status == NET_DOWN ||
			WorldServer[i].Status == NET_CONNECTING)
			 && tNow - WorldServer[i].tLastTry > 5 )
		{
			WorldServer[i].tLastTry = tNow;
			int id = serverConfig.worlddId(i); 
			WorldServer[i].id = id; 
			struct addrinfo sa;
			LOG4CXX_DEBUG(logger_, "Connecting to world server, ID="<<id);
			int fd = createConnectSocket("wsfd",serverConfig.worlddIp(id),
				toString(serverConfig.worlddGamedPort(id)), sa);
			if (fd<0) 
			{
				LOG4CXX_ERROR(logger_, "Connect to world server failed! ID="<<id);
				continue;
			}

			NetCache *cache = addConnection(fd,*(sockaddr_in*)sa.ai_addr,
				DEFAULT_SERVER_SIZE);
			cache->ph = new WorldHandler(eq, fd, this);
			WorldServer[i].iFd = fd;
			WorldServer[i].Status = NET_CONNECTING;

#ifdef _WIN32
			connectSuccess(fd);
#endif
		}
	}
	
	return true;
}*/

void GameNetHandler::keepAliveWithWordAndPKSrv(time_t now)
{	
	if ((now-last_keepalive_check)>10000)
	{
		//connectToWorld(); // reconnect

		last_keepalive_check = now;
        for (size_t i = 0; i < WorldServer.size(); i++)
        {
            if ( WorldServer[i].Status != NET_DOWN && WorldServer[i].Status != NET_CONNECTING )
            {
                sendIntSizedFdString( WorldServer[i].iFd, "ka");
            }
        }
    }
}

int GameNetHandler::initSockets()
{
	//while (!connectToWorld())
	{
		//usleep(3000);
	}
	clientfd = createListenSocket("clientfd", toString(serverConfig.gamedServerPort(nid_)),
		serverConfig.gamedBindIp(nid_));
	if (clientfd<0)
	{
		return -1;
	}
	adminfd = createListenSocket("adminfd", toString(serverConfig.gamedAdminPort(nid_)),
		serverConfig.gamedBindIp(nid_));
	if (adminfd<0)
	{
		return -1;
	}
	policyfd = createListenSocket("policyfd", toString(serverConfig.gamedPolicyPort(nid_)),
		serverConfig.gamedBindIp(nid_));
	if (policyfd<0)
	{
		return -1;
	}

	last_timeout_check = 0;
	last_keepalive_check = 0;

#ifdef _WIN32
	return max(clientfd, max(adminfd, policyfd));
#else
	return 0;
#endif
}
