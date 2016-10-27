#include "SysLog.h"
#include "distribution.h"
#include <time.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

//#include <log4cxx/logger.h>
#endif

const char  SZLOG_SYS[]				= "LogSys";	

CSysLog::CSysLog(void)
{
	m_nSrvID		= 0;
	m_pLogSys		= NULL;	
	m_lastCheck		= 0;
	m_bShowLog		= false;
	m_nSendLogLv	= 0;
	m_nModul		= 0;
	m_nModulVal		= 0;
	m_bInUse		= false;
	m_nPos			= 0;
#ifdef _WIN32
	InitializeCriticalSection(&m_Section); 
#else
	pthread_mutex_init(&m_mutex,0);	
#endif
}

CSysLog::~CSysLog(void)
{
#ifdef WIN32
	::DeleteCriticalSection(&m_Section);
#else
	pthread_mutex_destroy(&m_mutex);
#endif
	if(m_pLogSys)
	{
		m_pLogSys->close();
		delete m_pLogSys;	
	}
}
CSysLog* CSysLog::GetInstance()
{
	static CSysLog log;
	return &log;
}

void CSysLog::Quit()
{
	m_SysLogNet.Quit();
}
void CSysLog::SetLogInfo(bool bGameLog,int nSrvID,
						 string strLogDir,string strLogName,
						 string strAddr,string strPort,
						 bool bShowLog,int nSendLogLv,
						 int nModul,int nModulVal)
{
	m_bGameLog	= bGameLog;
	m_bShowLog	= bShowLog;
	m_nSendLogLv = nSendLogLv;
	m_nModul	= nModul;
	m_nModulVal	= nModulVal;

	m_nSrvID	= nSrvID;
	m_strLogDir = strLogDir;
	m_strLogName= strLogName;
	if(m_bShowLog||m_nSendLogLv>0)
		m_bInUse = true;
	if(m_nSendLogLv>0)
	{
		m_SysLogNet.StartThread(strAddr,strPort);
	}
}
bool CSysLog::CreateDir(const char* szDir)
{
	if(!TURNON_LOG)
		return true;
	if(!m_bShowLog)
		return true;
	char szCurDir[512];
	memset(szCurDir,0,512);

#ifdef _WIN32
	GetCurrentDirectory(512,szCurDir);
	if(!SetCurrentDirectory(szDir))
	{
		if(!CreateDirectory(szDir,NULL))
		{
			cout << "Can't Create Directory: " << szDir << endl;
			SetCurrentDirectory(szCurDir);
			return 0;
		}
	}
	SetCurrentDirectory(szCurDir);
#else
	getcwd(szCurDir,512);
	if(chdir(szDir)!=0)
	{
		char szCmd[512];
		memset(szCmd,0,512);
		sprintf(szCmd,"mkdir %s -p \r\n",szDir);
		system(szCmd);
		//if(open(szDir,O_RDWR|O_CREAT|O_DIRECTORY)!=0)
		//{
		//	cout << "Create Dir:"<<szCurDir<<"Failed!"<<endl;
			//LOG4CXX_FATAL(logger_, "Create Dir:"+szCurDir+"Failed!");
		//	return 0;
		//}
	}
	chdir(szCurDir);
#endif


	return true;
}
bool CSysLog::CreateLog()
{
	if(!TURNON_LOG)
		return true;
	if(!m_bShowLog)
		return true;
	time_t lt = time(NULL);
	if(lt-m_lastCheck<300)
		return true;
	m_lastCheck = lt;
	struct tm *newtime = NULL;
	char szTime[128];
	newtime = localtime(&lt);
	strftime(szTime, 128-1, "%Y-%m-%d", newtime);

	m_strLogDay = szTime;
	char szFile[512];


#ifdef _WIN32
	char szDir[512];
	memset(szDir,0,512);
	GetCurrentDirectory(512,szDir);
	if(!CreateDir(SZLOG_SYS))
		return false;
	SetCurrentDirectory(szDir);
	sprintf(szFile,"%s\\%s\\%s%d_%s.log",szDir,SZLOG_SYS,m_strLogName.c_str(),m_nSrvID,m_strLogDay.c_str());

#else
	if(!CreateDir(m_strLogDir.c_str()))
		return false;
	//strcpy(szDir,"/data/fish/lin/Test1/Test1/LogSys");
	sprintf(szFile,"%s/%s%d_%s.log",m_strLogDir.c_str(),m_strLogName.c_str(),m_nSrvID,m_strLogDay.c_str());
#endif

	m_pLogSys		= new ofstream(szFile, ios::out | ios::app);
	if(m_pLogSys==NULL)
	{
		//LOG4CXX_FATAL(logger_, "Create File:"+szFile+"Failed!");
		cout << "Create File:"<<szFile<<"Failed!"<<endl;
		return false;
	}

#ifdef _WIN32
	SetCurrentDirectory(szDir);
#else

#endif	
	return true;
}
void CSysLog::WriteCurTime()
{
	struct tm *newtime = NULL;
	char szTime[128];

	time_t lt = time(NULL);
	newtime = localtime(&lt);
	strftime(szTime, 128-1, "%Y-%m-%d %H:%M:%S", newtime);
	*this << szTime;
}

void CSysLog::ChgLogFile()
{
	if(!TURNON_LOG)
		return ;
	if(!m_bShowLog)
		return;
	struct tm *newtime = NULL;
	char szTime[128];

	time_t lt = time(NULL);
	newtime = localtime(&lt);
	strftime(szTime, 128-1, "%Y-%m-%d", newtime);
	if(m_strLogDay.compare(szTime)==0)
		return;
	//m_strLogDay = szTime;
	LogLock();
	if(m_pLogSys)
	{
		m_pLogSys->close();
		delete m_pLogSys;
		m_pLogSys		= NULL;	
	}
	CreateLog();
	LogUnLock();
}

void CSysLog::BeginMsg()
{
	memset(m_szBuf,0,MAX_LOG_SMG_LENGTH);
	m_nPos=0;
}

void CSysLog::EndMsg()
{
	m_szBuf[m_nPos] = 0;
	if(m_pLogSys&&m_bShowLog)
		*m_pLogSys << m_szBuf << std::endl;
}

void CSysLog::EndMsg(int64 nUserID,LOG_TYPE emType,int nDmd)
{
	m_szBuf[m_nPos] = 0;
	if(m_pLogSys&&m_bShowLog)
		*m_pLogSys << m_szBuf << std::endl;
	//if(NeedSend(nUserID,emType,nDmd))
	//{
	//	m_SysLogNet.PushSendStr(m_szBuf);
	//}
}

void CSysLog::SendMsg()
{
	m_SysLogNet.PushSendStr(m_szBuf);
}

bool CSysLog::IsStatUser(int64 nUserID)
{
	if(!m_bGameLog)
		return false;
	if(m_nModul==0)
		return true;
	return (getUidHash(nUserID)%m_nModul)==m_nModulVal;
}

bool CSysLog::NeedSend(int64 nUserID,LOG_TYPE emType,int nDmd)
{
	bool bSend = false;
	if(nDmd!=0)
		return true;
	switch(emType)
	{
	case LT_LogOn:
	case LT_LogOut:
	case LT_Register:
		bSend = true;
		break;
	default:
		{
			bSend = IsStatUser(nUserID);
		}
		break;

	}
	return bSend;
}

bool CSysLog::InUse()
{
	return m_bInUse;
}


//template <class T1,class T2,class T3,class T4>
//void SYS_STAT(int64 uid,string strType,int nLV,int nGender,
//			  bool bYellowDmd,int nYellowDmdLV,bool bYearYellowDmd,
//			  int64 nTotalRecharge,int nRegDays,int64 nCredits,
//			  bool bSendSome,T1 subTp1,T2 subTp2,T3 subTp3,
//			  T4 val1,int nVal2,int nVal3,int nVal4,int nVal5)
//{
//	CSysLog* pLog = CSysLog::GetInstance();
//	if(!pLog->InUse())
//		return;
//
//	if(bSendSome&&!pLog->IsStatUser(uid))
//	{
//		return;
//	}
//	pLog->LogLock();
//	pLog->BeginMsg();
//	//time,serverid,uid,type,level,gender,yellowdmd,yellowdmdlv,yearyellowdmd,TotalRecharge,RegDays,obligate1,obligate2,obligate3,
//	//subtype1,subtype2,subtype3,value1,value2,value3,value4,value5
//	pLog->WriteCurTime();
//	*pLog	<< pLog->GetSrvID()<<uid<<strType<<nLV<<nGender<<bYellowDmd<<nYellowDmdLV<<bYearYellowDmd<<nTotalRecharge<<nRegDays<<nCredits<<0<<0<<0
//		<< subTp1 << subTp2 << subTp3 << val1 << nVal2 << nVal3 << nVal4 << nVal5;
//
//	pLog->SendMsg();
//	pLog->LogUnLock();
//}
//
//void SYS_STAT(	int64 uid,string strType,int nLV,int nGender,
//				bool bYellowDmd,int nYellowDmdLV,bool bYearYellowDmd,
//				int nTotalRecharge,int nRegDays,int nCredits,bool bSendSome,
//				string strSubTp1,string strSubTp2,string strSubTp3,
//				int nVal1,int nVal2,int nVal3,int nVal4,int nVal5)
//{
//
//
//
//}
//void SYS_STAT(	int64 uid,string strType,int nLV,int nGender,
//				bool bYellowDmd,int nYellowDmdLV,bool bYearYellowDmd,
//				int nTotalRecharge,int nRegDays,int nCredits,bool bSendSome,
//				int nSubTp1,string nSubTp2,string nSubTp3,int nVal1,int nVal2,int nVal3,int nVal4,int nVal5)
//{
//	CSysLog* pLog = CSysLog::GetInstance();
//	if(!pLog->InUse())
//		return;
//
//	if(bSendSome&&!pLog->IsStatUser(uid))
//	{
//		return;
//	}
//	pLog->LogLock();
//	pLog->BeginMsg();
//	//time,serverid,uid,type,level,gender,yellowdmd,yellowdmdlv,yearyellowdmd,TotalRecharge,RegDays,obligate1,obligate2,obligate3,
//	//subtype1,subtype2,subtype3,value1,value2,value3,value4,value5
//	pLog->WriteCurTime();
//	*pLog	<< pLog->GetSrvID()<<uid<<strType<<nLV<<nGender<<bYellowDmd<<nYellowDmdLV<<bYearYellowDmd<<nTotalRecharge<<nRegDays<<0<<0<<0
//		<< nSubTp1 << nSubTp2 << nSubTp3 << nVal1 << nVal2 << nVal3 << nVal4 << nVal5;
//
//	pLog->SendMsg();
//	pLog->LogUnLock();
//
//}


CSysLog& CSysLog::operator << (char value)
{
	sprintf(m_szBuf+m_nPos,"%c,",value);
	m_nPos = strlen(m_szBuf);

	//if(m_pLogSys&&m_bShowLog)
	//	*m_pLogSys << value <<",";
	//if(m_bSendLog)
	//{
	//	sprintf(m_szBuf+m_nPos,"%c,",value);
	//	m_nPos = strlen(m_szBuf);
	//}
	return *this;
}

CSysLog& CSysLog::operator << (float value)
{
	sprintf(m_szBuf+m_nPos,"%f,",value);
	m_nPos = strlen(m_szBuf);

	//if(m_pLogSys&&m_bShowLog)
	//	*m_pLogSys << value <<",";
	//if(m_bSendLog)
	//{
	//	sprintf(m_szBuf+m_nPos,"%f,",value);
	//	m_nPos = strlen(m_szBuf);
	//}
	return *this;	
}

CSysLog& CSysLog::operator << (double value)
{
	sprintf(m_szBuf+m_nPos,"%lf,",value);
	m_nPos = strlen(m_szBuf);

	//if(m_pLogSys&&m_bShowLog)
	//	*m_pLogSys << value <<",";
	//if(m_bSendLog)
	//{
	//	sprintf(m_szBuf+m_nPos,"%lf,",value);
	//	m_nPos = strlen(m_szBuf);
	//}
	return *this;	
}

CSysLog& CSysLog::operator << (int64 value)
{
	sprintf(m_szBuf+m_nPos,"%lld,",value);
	m_nPos = strlen(m_szBuf);

	//if(m_pLogSys&&m_bShowLog)
	//	*m_pLogSys << value <<",";
	//if(m_bSendLog)
	//{
	//	sprintf(m_szBuf+m_nPos,"%lld,",value);
	//	m_nPos = strlen(m_szBuf);
	//}
	return *this;
}
CSysLog& CSysLog::operator << (char* szBuf)
{
	return *this << (const char*)szBuf;
}
CSysLog& CSysLog::operator << (const char* szBuf)
{
	sprintf(m_szBuf+m_nPos,"%s,",szBuf);
	m_nPos = strlen(m_szBuf);

	//if(m_pLogSys&&m_bShowLog)
	//	*m_pLogSys << szBuf <<",";
	//if(m_bSendLog)
	//{
	//	sprintf(m_szBuf+m_nPos,"%s,",szBuf);
	//	m_nPos = strlen(m_szBuf);

	//}
	return *this;
}
CSysLog& CSysLog::operator << (string& str)
{		
	sprintf(m_szBuf+m_nPos,"%s,",str.c_str());
	m_nPos = strlen(m_szBuf);
	//if(m_pLogSys&&m_bShowLog)
	//	*m_pLogSys << str.c_str() <<",";
	//if(m_bSendLog)
	//{
	//	sprintf(m_szBuf+m_nPos,"%s,",str.c_str());
	//	m_nPos = strlen(m_szBuf);

	//}
	return *this;
}
CSysLog& CSysLog::operator << (const string& str)
{
	sprintf(m_szBuf+m_nPos,"%s,",str.c_str());
	m_nPos = strlen(m_szBuf);

	return *this;
}
