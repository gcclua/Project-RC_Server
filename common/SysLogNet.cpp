#include "SysLogNet.h"
#include <time.h>
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
#include <signal.h>
#include <fcntl.h>
#endif

#include "../net/NetCache.h"
#include "../common/Clock.h"

CSysLogNet::CSysLogNet(void)
{
//	memset(&m_LogStat,0,sizeof(SLogStatItem));
	m_LogStat.iFd = 0;
	m_LogStat.m_tmLastSend = 0;
	m_LogStat.Status = SLSTAT_DOWN;
	m_LogStat.tLastTry = 0;
#ifdef _WIN32
	InitializeCriticalSection(&m_Section); 
#else
	pthread_mutex_init(&m_mutexNet,0);	
#endif
	m_bRunnig	= false;
}
CSysLogNet::~CSysLogNet(void)
{
	m_lstStr2Send.clear();

#ifdef WIN32
	::DeleteCriticalSection(&m_Section);
#else
	pthread_mutex_destroy(&m_mutexNet);
#endif
}

bool CSysLogNet::StartThread(string strAddr,string strPort)
{
	m_LogStat.strAddr	= strAddr;
	m_LogStat.strPort	= strPort;
	int ret = pthread_create(&m_thSysLogNet, NULL, CSysLogNet::ThreadProc, (void *)this);

	if(ret != 0)
	{
		return false;
	}
	m_bRunnig = true;
	return true;
}

void* CSysLogNet::ThreadProc(void* lParam)
{
	CSysLogNet* pNet = static_cast<CSysLogNet*>(lParam);
	pNet->Run();
	return NULL;
}

void CSysLogNet::Run()
{
	// first let's increase the limit of open files
#ifndef _WIN32

	//struct rlimit srl;
	//srl.rlim_cur = MAX_CONNECTIONS+10;
	//srl.rlim_max = MAX_CONNECTIONS+10;
	//if (setrlimit(RLIMIT_NOFILE, &srl)<0)
	//{
	//	LOG4CXX_FATAL(logger_, "Cannot set RLimit!");
	//	//exit(1);
	//	return;
	//}
	epfd = epoll_create(10);
	if (epfd<0)
	{
		//exit(1);
		return;
	}

	// Now let's ignore broken pipes
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGPIPE, &sa, NULL)<0)
	{
		
	}

	if (initSockets()<0) {
		//exit(1);
		return;
	}

	struct epoll_event ev, evs[MAX_EVENTS];
	for (;;)
	{
		int count = epoll_wait(epfd, evs, MAX_EVENTS, 1000);
		if (count<0)
		{
			
		}
		time_t now = Clock::getCurrentSystemTime();
		if (!preNetEvent(now)) {
			
			break;
		}
		for (int i=0; i<count; i++)
		{
			if (!m_bRunnig)
			{
				break;
			}
			int fd = evs[i].data.fd;
			//if (isListenSocket(fd)) 
			//{
			//	struct sockaddr_in sa;
			//	socklen_t slen = sizeof(sa);
			//	int nfd = 0;
			//	nfd = accept(fd, (struct sockaddr*)&sa, &slen);
			//	if (nfd>0)
			//	{
			//		ev.events = EPOLLIN | EPOLLHUP; //| EPOLLRDHUP;
			//		ev.data.fd = nfd;
			//		if (epoll_ctl(epfd, EPOLL_CTL_ADD, nfd, &ev) < 0)
			//		{
			//			LOG4CXX_ERROR(logger_, "epoll_ctl error, cannot add client!");
			//		}
			//		else
			//		{
			//			size_t rsize = readCacheSize(fd);
			//			//size_t rsize = (fd==wsfd ? NetCache::WEBSERVER_READ_SIZE : NetCache::DEFAULT_READ_SIZE);
			//			NetCache *cache = addConnection(nfd, sa, rsize);
			//			createProtocolHandler(cache, fd);
			//		}
			//	}
			//}
			//else // data
			{
				NetCache *cache = getCacheFromFd(fd);
				if (cache!=NULL)
				{
					__uint32_t events = evs[i].events;
					bool readError = false;
					if ((events&EPOLLIN)>0)
					{
						int64 uid = cache->uid;
						readError = !cache->read();
						if (!readError)
						{
							string req;
							while (cache->assemble(req) && !cache->remove)
							{
								//if (cache->ph!=NULL)
								//{
								//	cache->ph->handle(uid, req);
								//}
								//else
								//{
								//	LOG4CXX_WARN(logger_, "Protocol handler is NULL for fd:"<<fd);
								//}
							}
						}
					}
					if ((events&EPOLLOUT)>0)
					{
						if( isConnecting( fd ))
						{
							connectSuccess( fd ); 
						}
						else if(cache->write())
						{
							ev.events = EPOLLIN | EPOLLHUP;// | EPOLLRDHUP;
							ev.data.fd = fd;
							epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
						}
						
					}
					if ((cache->remove&&!cache->waitToWrite()) || readError || 
						(events&EPOLLHUP)>0 || //(events&EPOLLRDHUP)>0 || 
						(events&EPOLLERR)>0)
					{
						//int64 uid = cache->uid;
						//if (uid>=0 && cache->ph!=NULL)
						//{
						//	cache->ph->leave(uid);
						//}
						LOG4CXX_DEBUG(logger_, "Client disconnected of fd:" << fd << ", remove: " << cache->remove << ", read error: " << readError << ", hup: " << (events&EPOLLHUP) << //", rdhup: " << (events&EPOLLRDHUP) << 
							", epoll error: " << (events&EPOLLERR));
						doCloseConnection(fd);
						if (isConnectSocket(fd)) {
							connectFailed(fd);
						}
					}
				}
				else
				{
					LOG4CXX_WARN(logger_, "Cannot find cache for fd:"<<fd);
				}
			}
		}
		if(m_LogStat.Status == SLSTAT_ACTIVE)
		{
			NetCache *cache = getCacheFromFd(m_LogStat.iFd);
			if (cache!=NULL&&!cache->waitToWrite())
			{
				string str;
				if(PopSendStr(str))
					sendIntSizedFdString(m_LogStat.iFd,str);
			}
		}
		if (!m_bRunnig)
		{
			break;
		}
	}
#endif
}

void CSysLogNet::Quit()
{
	LogLock();
	m_bRunnig = false;
	LogUnLock();
	pthread_join(m_thSysLogNet, NULL);
	m_lstStr2Send.clear();
}

int CSysLogNet::initSockets()
{
	last_keepalive_check = 0;
	connectToStatSrv();
	return 0;
}

bool CSysLogNet::connectToStatSrv()
{

	//for( int i = 0; i<WorldServer.size(); i++)
	{
		time_t  tNow = time( NULL ); 
		if( (m_LogStat.Status == SLSTAT_DOWN ||
			m_LogStat.Status == SLSTAT_CONNECTING )
			&& tNow - m_LogStat.tLastTry > 5 )
		{
			m_LogStat.tLastTry = tNow; 
			struct addrinfo sa;
			m_LogStat.iFd = createConnectSocket("lsfd",m_LogStat.strAddr,m_LogStat.strPort,sa);
			if (m_LogStat.iFd<0) 
			{
				return true;
			//	continue;
			}
			//NetCache *cache = addConnection(m_LogStat.iFd,*(sockaddr_in*)sa.ai_addr,NetCache::WEBSERVER_READ_SIZE);
			addConnection(m_LogStat.iFd,*(sockaddr_in*)sa.ai_addr,DEFAULT_SERVER_SIZE);
			m_LogStat.Status = SLSTAT_CONNECTING;
		}
	}

	return true;
}

bool CSysLogNet::preNetEvent(time_t now)
{
	keepAlive(now);
	return true;
}

void CSysLogNet::keepAlive(time_t now)
{
	if ((now-last_keepalive_check)>30000) 
	{
		connectToStatSrv(); // reconnect

		last_keepalive_check = now;
		if(m_LogStat.Status == SLSTAT_ACTIVE)
		{
			sendIntSizedFdString( m_LogStat.iFd, "ka");
		}
	}
}

int CSysLogNet::readCacheSize(int listenFd)
{
	return DEFAULT_SERVER_SIZE;
}

void CSysLogNet::createProtocolHandler(NetCache *cache, int listenFd)
{
	//don't listen
	return;
}

int CSysLogNet::connectFailed(int connectFd)
{
	if (isConnectSocket( connectFd)) 
	{
		m_LogStat.iFd = 0;
		m_LogStat.Status = SLSTAT_DOWN;
		connectToStatSrv();
	}
	return 0;
}

bool CSysLogNet::isConnecting( int fd )
{
	return ((m_LogStat.iFd == fd) && (m_LogStat.Status == SLSTAT_CONNECTING));
}

bool CSysLogNet::connectSuccess( int fd )
{
	m_LogStat.Status = SLSTAT_ACTIVE;
	return true;
}

void CSysLogNet::PushSendStr(const char* szBuf)
{
	LogLock();
	if(m_LogStat.Status == SLSTAT_ACTIVE)
	{
		m_lstStr2Send.push_back(string(szBuf));
	}
	else
	{
		//if(m_lstStr2Send.size()<2000)
		//{
		//	m_lstStr2Send.push_back(string(szBuf));
		//}
	}
	LogUnLock();
}
bool CSysLogNet::PopSendStr(string& str)
{
	bool bHasInfo = false;
	LogLock();
	if(m_lstStr2Send.size()>0)
	{
		str = m_lstStr2Send.front();
		m_lstStr2Send.pop_front();
		bHasInfo = true;
	}
	LogUnLock();
	return bHasInfo;
}

