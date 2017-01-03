#include "Daemon.h"
#include <string.h>
#include "../common/string-util.h"
#include "../common/coredump.h"
#include "Exception.h"
#include "service/ServiceManager.h"
#include "LibNetwork.h"
#include "../DBManage/DBService.h"
#include "Log/LogService.h"
#include "Login/LoginService.h"
#include "scene/SceneService.h"
#include "worldmap/WorldMapService.h"
#include "user\WorldUserService.h"
#include "Config.h"
#include "Table/TableManager.h"
#include "packet/Packet/PacketDefine.h"
#include "ServerConfig.h"

ServerConfig serverConfig("D:/project/RealmConquerors/src/Server/server/DebugPath/server.cfg");


#include <string>
using namespace std;



Daemon::Daemon(int nid)
{
	InitRuntimeFolder(nid);
}

void Daemon::InitRuntimeFolder(int nGameId)
{
	__ENTER_FUNCTION
		FLString<256> szFloder;
		szFloder = "./RuntimeData";
		AssertEx(InitFolder(szFloder.GetCText()), "");

		szFloder += "/";
		szFloder += FLString<256>(nGameId);
		AssertEx(InitFolder(szFloder.GetCText()), "");

		FLString<256> szFloderLog;
		szFloderLog = szFloder;
		szFloderLog += "/Log";
		AssertEx(InitFolder(szFloderLog.GetCText()), "");

	__LEAVE_FUNCTION
}

void Daemon::RunServiceManager(void)
{
	__ENTER_FUNCTION
	gServiceManager.Create(ServiceID::MAX,_GameConfig().m_nDBThreadCount);
	gServiceManager.Register(new DBService());
	gServiceManager.Register(new LoginService(_GameConfig().m_uPortForClient));
	gServiceManager.Register(new LogService());
	//gServiceManager.Register(new DBTestService());
	gServiceManager.Register(new SceneService());
	gServiceManager.Register(new WorldUserService());
	gServiceManager.Register(new WorldMapService());
	
	gServiceManager.InitAllService();
	gServiceManager.Run();
	__LEAVE_FUNCTION
}

void Daemon::InitStaticManager()
{
	gPacketFactoryManager.Init();
}


Daemon::~Daemon()
{

}

void Daemon::start()
{
	//InitTable();
	InitGameConfig();

	Packets::InitPacketNameVector();
	InitStaticManager();
	RunServiceManager();
}

void Daemon::quit()
{
	
}

int main(int argn, char *argv[]) // here is the entrance of daemon
{
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    // dump process id
#ifndef _WIN32
    pid_t pid = getpid();
    char filebuff[256];
    sprintf(filebuff, "%s%s.pid", argv[0], argv[1]);
    FILE * fp = fopen(filebuff, "w");
    fprintf(fp, "%d\n", pid);
    fclose(fp);

    signal(SIGSEGV, saveBackTrace);
    signal(SIGILL, saveBackTrace);
    signal(SIGFPE, saveBackTrace);
    signal(SIGABRT, saveBackTrace);
    signal(SIGTERM, saveBackTrace);
    signal(SIGKILL, saveBackTrace);
    signal(SIGXFSZ, saveBackTrace);

    // block SIGINT to all child process:
    sigset_t bset, oset;
    sigemptyset(&bset);
    sigaddset(&bset, SIGINT);
    // equivalent to sigprocmask
    if (pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0)
    {
        printf("set thread signal mask error!");
        return 0;
    }
#endif
    if (argn != 2)
    {
        printf("usage: gamed node_id\n");
        return 1;
    }
	srand((unsigned int)time(NULL));
    int nid;
    safe_atoi(argv[1], nid);
    Daemon daemon(nid);
    daemon.start();
	printf("daemon quit ");
    return 0;
}
