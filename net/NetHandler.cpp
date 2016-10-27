#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#endif

#include "NetHandler.h"
#include "../net/NetCache.h"
#include "../common/Clock.h"
#include "../net/ProtocolHandler.h"


NetHandler::NetHandler()
{
    fdCache.clear();
    pthread_mutex_init(&send_mutex, NULL);
	pthread_mutex_init(&map_mutex, NULL);
	m_bRunning = true;
}

NetHandler::~NetHandler()
{
	for (map<int,NetCache*>::iterator iter = fdCache.begin(); iter != fdCache.end(); iter++)
	{
		NetCache *pNetCache = (NetCache*)iter->second;
		if (pNetCache != NULL)
		{
			delete pNetCache;
		}
	}
	fdCache.clear();
	pthread_mutex_destroy(&map_mutex);
    pthread_mutex_destroy(&send_mutex);
}

NetCache *NetHandler::addConnection(int fd, struct sockaddr_in addr, size_t rsize)
{
    NetCache *cache = new NetCache(fd, addr, rsize);
	lockMap();
    fdCache.insert(pair<int, NetCache*>(fd, cache));
	unlockMap();
#ifdef _WIN32
    if (fd > fdmax)
    {
        fdmax = fd;
    }
#endif
    return cache;
}

void NetHandler::removeConnection(int fd)
{
    NetCache *cache = getCacheFromFd(fd);
    if (cache != NULL)
    {
        //int64 id = cache->uid;
		lockMap();
        fdCache.erase(fd);
		unlockMap();
        delete cache;
    }
}

NetCache *NetHandler::getCacheFromFd(int fd)
{
	NetCache* cache = NULL;
	lockMap();
    map<int, NetCache*>::const_iterator it = fdCache.find(fd);
    if (it != fdCache.end())
    {
        cache = it->second;
    }
	unlockMap();
	return cache;
}

bool NetHandler::sendSizedFdString(int fd, const string& str)
{
    // send to web
    unsigned int len = str.length();
    char buf[10];
    sprintf(buf, "%05X", len);
    lockSend(); // we use this to lock the send procedure
    sendFdString(fd, buf, strlen(buf));
    bool succ = sendFdString(fd, str.c_str(), str.length());
    unlockSend();
    return succ;
}

bool NetHandler::sendIntSizedFdString(int fd, const string& str)
{
    // send to world
    //unsigned short len = htons(str.length());
    unsigned int ulen = (unsigned int) str.length();
    lockSend(); // we use this to lock the send procedure
    sendFdString(fd, (const char*) (&ulen), sizeof (ulen));
    bool succ = sendFdString(fd, str.c_str(), str.length());
    unlockSend();
    return succ;
}

bool NetHandler::sendSizedTypeFdString(int fd, int type, const string& str)
{
	NetCache *cache = getCacheFromFd(fd);
	if (cache == NULL)
	{
		return false;
	}

	int index = cache->getNextIndex();
	index = htonl(index);
	unsigned short utype = (unsigned short) type;
	utype = htons(type);
	unsigned short ulen = (unsigned short) str.length() + sizeof (unsigned short)
			+ sizeof (unsigned int) ;
	ulen = htons(ulen);
	lockSend(); // we use this to lock the send procedure
	sendFdString(fd, (const char*) (&ulen), sizeof (unsigned short) );
	sendFdString(fd, (const char*) (&utype), sizeof (unsigned short) );
	sendFdString(fd, (const char*) (&index), sizeof (unsigned int) );
	bool succ = sendFdString(fd, str.c_str(), str.length());
	unlockSend();
	return succ;
}

void NetHandler::closeConnection(int fd)
{
    NetCache *cache = getCacheFromFd(fd);
    if (cache != NULL)
    {
        cache->remove = true;
    }
}

char *NetHandler::getRemoteAddress(int fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof (addr);
    if (getpeername(fd, (struct sockaddr*) &addr, &len) == 0)
    {
        return inet_ntoa(addr.sin_addr);
    }
    else
    {
        return NULL;
    }
}

bool NetHandler::preNetEvent(time_t now)
{
    return true;
}

void NetHandler::quit()
{
	m_bRunning = false;
}

#ifdef _WIN32 // for Windows

// Windows specific

bool NetHandler::sendFdString(int fd, const char* str, size_t size)
{
    // for windows, we send string directly
    return send(fd, str, size, 0) == size;
}

// Windows specific

void NetHandler::doCloseConnection(int fd)
{
    if (fd > 0)
    {
        FD_CLR(fd, &master);
        shutdown(fd, SD_BOTH);
        removeConnection(fd);
    }
}

// Windows specific

void NetHandler::start()
{
	m_bRunning = true;
    fd_set readset;
    FD_ZERO(&master);
    int listenFd = initSockets();
    if (listenFd < 0)
    {
        exit(1);
    }
    if (listenFd > fdmax)
    {
        fdmax = listenFd;
    }


    struct timeval timeout;

    for (; ; )
    {
		if (!m_bRunning)
		{
			break;
		}
        readset = master;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        int count = select(fdmax + 1, &readset, NULL, NULL, &timeout);
        if (count < 0)
        {
            exit(1);
        }
        time_t now = Clock::getCurrentSystemTime();
        if (!preNetEvent(now))
        {
            break;
        }
        if (count > 0)
        {
            for (int i = 0; i <= fdmax; i++)
            {
                if (FD_ISSET(i, &readset))
                {
                    if (isListenSocket(i))
                    {
                        struct sockaddr_in sa;
                        socklen_t slen = sizeof (sa);
                        int nfd = accept(i, (struct sockaddr*) &sa, &slen);
                        if (nfd < 0)
                        {
                            
                        }
                        else
                        {
                            FD_SET(nfd, &master);
                            if (nfd > fdmax)
                            {
                                fdmax = nfd;
                            }
                            size_t rsize = readCacheSize(i);
                            NetCache *cache = addConnection(nfd, sa, rsize);
                            createProtocolHandler(cache, i);
                        }
                    }
                    else
                    {
                        NetCache *cache = getCacheFromFd(i);
                        if (cache != NULL)
                        {
                            int64 uid = cache->uid;
                            bool readSucc = cache->read();
                            if (readSucc)
                            {
                                string req;
                                while (cache->assemble(req) && !cache->remove)
                                {
                                    //LOG4CXX_DEBUG(logger_, "Command Received \"" << req.substr(0, 2) << "\" from uid:" << uid << " fd:" << i);

                                    if (cache->ph != NULL)
                                    {
                                        cache->ph->handle(uid, req);
                                    }
                                    else
                                    {
                                        
                                    }
                                }
                            }
                            if (!readSucc || (cache->remove && !cache->waitToWrite()))
                            {
                                if (uid >= 0 && cache->ph != NULL)
                                {
                                    cache->ph->leave(uid);
                                }
                                doCloseConnection(i);
                              
                                if (isConnectSocket(i))
                                {
                                    int newFd = connectFailed(i);
                                    fdmax = max(fdmax, newFd);
                                }
                            }
                        }
                        else
                        {
                          
                        }
                    }
                }
            }
        }
    }
}

// Windows specific

int NetHandler::createListenSocket(string socket_name, string port, string address)
{
    int ret = socket(PF_INET, SOCK_STREAM, 0);
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo(address.c_str(), port.c_str(), &hints, &res);
    if (::bind(ret, res->ai_addr, res->ai_addrlen) < 0)
    {
        return -1;
    }
    if (listen(ret, MAX_QUEUE_LENGTH) < 0)
    {
        return -1;
    }

    if (ret > 0)
    {
        FD_SET(ret, &master);
    }
    return ret;
}

// Windows specific

int NetHandler::createConnectSocket(string socket_name, string address, string port, struct addrinfo &sa)
{
    int ret = socket(PF_INET, SOCK_STREAM, 0);
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Connecting to World Server
    getaddrinfo(address.c_str(), port.c_str(), &hints, &res);
    if (connect(ret, res->ai_addr, res->ai_addrlen) < 0)
    {

        return -1;
    };
    sa = *res;

    if (ret > 0)
    {
        FD_SET(ret, &master);
    }

    return ret;
}

#else // for Linux

// Linux specific

bool NetHandler::sendFdString(int fd, const char* str, size_t size)
{
    NetCache *cache = getCacheFromFd(fd);
    if (cache == NULL)
    {
        return false;
    }
    if (!cache->prepareWrite(str, size))
    {
        return false;
    }
    else
    {
        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLOUT | EPOLLHUP; // | EPOLLRDHUP;
        ev.data.fd = fd;
        epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
        return true;
    }
}


// Linux specific

void NetHandler::doCloseConnection(int fd)
{
    if (fd > 0)
    {
        struct epoll_event ev;
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
        shutdown(fd, SHUT_RDWR);
        close(fd);
        removeConnection(fd);
    }
}

// Linux specific

void NetHandler::start()
{
	m_bRunning = true;
    // first let's increase the limit of open files
	int maxconn = 100000;
	struct rlimit srl;
	srl.rlim_cur = maxconn + 10;
	srl.rlim_max = maxconn + 10;
	if (setrlimit(RLIMIT_NOFILE, &srl) < 0)
	{
		exit(1);
	}
	epfd = epoll_create(maxconn);

    if (epfd < 0)
    {
        exit(1);
    }

    // Now let's ignore broken pipes
    struct sigaction sa;
    memset(&sa, 0, sizeof (sa));
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL) < 0)
    {
       
    }

    if (initSockets() < 0)
    {
        exit(1);
    }

    struct epoll_event ev, evs[MAX_EVENTS];
    for (; ; )
    {
		if (!m_bRunning)
		{
			break;
		}
        int count = epoll_wait(epfd, evs, MAX_EVENTS, 1000);
        if (count < 0)
        {
            
        }
        time_t now = Clock::getCurrentSystemTime();
        if (!preNetEvent(now))
        {
            
            break;
        }
        for (int i = 0; i < count; i++)
        {
            int fd = evs[i].data.fd;
            if (isListenSocket(fd))
            {
                struct sockaddr_in sa;
                socklen_t slen = sizeof (sa);
                int nfd = 0;
                nfd = accept(fd, (struct sockaddr*) &sa, &slen);
                if (nfd > 0)
                {
                    ev.events = EPOLLIN | EPOLLHUP; //| EPOLLRDHUP;
                    ev.data.fd = nfd;
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, nfd, &ev) < 0)
                    {
                        
                    }
                    else
                    {
                        size_t rsize = readCacheSize(fd);
                        //size_t rsize = (fd==wsfd ? NetCache::WEBSERVER_READ_SIZE : NetCache::DEFAULT_READ_SIZE);
                        NetCache *cache = addConnection(nfd, sa, rsize);
                        createProtocolHandler(cache, fd);
                    }
                }
            }
            else // data
            {
                NetCache *cache = getCacheFromFd(fd);
                if (cache != NULL)
                {
                    __uint32_t events = evs[i].events;
                    bool readError = false;
                    if ((events & EPOLLIN) > 0)
                    {
                        int64 uid = cache->uid;
                        readError = !cache->read();
                        if (!readError)
                        {
                            string req;
                            while (cache->assemble(req) && !cache->remove)
                            {

                                if (cache->ph != NULL)
                                {
                                    cache->ph->handle(uid, req);
                                }
                                else
                                {
                                    
                                }
                            }
                        }
                    }
                    if ((events & EPOLLOUT) > 0)
                    {
                        if ( isConnecting( fd ))
                        {
                            connectSuccess( fd );
                        }
                        else if (cache->write())
                        {
                            ev.events = EPOLLIN | EPOLLHUP; // | EPOLLRDHUP;
                            ev.data.fd = fd;
                            epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
                        }
                    }
                    if ((cache->remove && !cache->waitToWrite()) || readError ||
                            (events & EPOLLHUP) > 0 || //(events&EPOLLRDHUP)>0 ||
                            (events & EPOLLERR) > 0)
                    {
                        int64 uid = cache->uid;
                        if (uid >= 0 && cache->ph != NULL)
                        {
                            cache->ph->leave(uid);
                        }
                       
                        doCloseConnection(fd);
                        if (isConnectSocket(fd))
                        {
                            connectFailed(fd);
                        }
                    }
                }
                else
                {
                    
                }
            }
        }
    }

}

void setnonblocking(int fd)
{
    int opts;
    opts = fcntl(fd, F_GETFL);
    if (opts < 0)
    {
        fprintf(stderr, "fcntl failed\n");
        return;
    }
    opts = opts | O_NONBLOCK;
    if ( fcntl(fd, F_SETFL, opts) < 0)
    {
        fprintf(stderr, "fcntl failed\n");
        return;
    }
    return;
}

// Linux specific

int NetHandler::createListenSocket(string socket_name, string port, string address)
{
    int ret = socket(PF_INET, SOCK_STREAM, 0);
    if (ret < 0)
    {
        exit(1);
    }
    int yes = 1;
    if (setsockopt(ret, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int) ) < 0)
    {
       
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(address.c_str(), port.c_str(), &hints, &res);

    if (bind(ret, res->ai_addr, res->ai_addrlen) < 0)
    {
        exit(1);
    }

    freeaddrinfo(res);

    if (listen(ret, MAX_QUEUE_LENGTH) < 0)
    {
        exit(1);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = ret;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, ret, &ev) < 0)
    {
        exit(1);
    }

    return ret;
}

// Linux specific

int NetHandler::createConnectSocket(string socket_name, string address, string port, struct addrinfo &sa)
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        return -1;
    }

    setnonblocking(fd);
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(address.c_str(), port.c_str(), &hints, &res);
    connect(fd, res->ai_addr, res->ai_addrlen);
    sa = *res;
    freeaddrinfo(res);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLHUP | EPOLLOUT; //| EPOLLRDHUP | EPOLLHUP;
    ev.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0)
    {
        close(fd);
        return -1;
    }

    return fd;
}

#endif
