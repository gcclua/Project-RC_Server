#ifndef _DAEMON_H_
#define _DAEMON_H_
#pragma once


class Daemon
{
public:
	Daemon(int nid);
	virtual ~Daemon();
	void		start();
	void		quit();
public: 
	void InitRuntimeFolder(int nGameId);
	void RunServiceManager( void);
	void InitStaticManager(void);
};

bool gIsShouldShutdownBySignal = false;
bool gIsShouldShutdownByGM = false;

#endif
