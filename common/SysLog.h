#pragma once
#include <fstream>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <WinSock2.h>
#include "wtypes.h"
#include <Windows.h>
#endif

#include <pthread.h> 
#include "Base.h"
#include "SysLogNet.h"
const int	TURNON_LOG				= 1;			//是否写入日志	
const int	TURNON_DEBUG			= 1;			//是否写入debug日志
using namespace std;


enum LOG_TYPE
{
	LT_LogOn = 0,
	LT_LogOut,
	LT_Register,
	LT_BanLogin,

	LT_AddCrash,
	LT_CostCrash,

	//建筑相关

	LT_SendGift,
	LT_SendGiftPlatid,
	LT_GiftWinCount,
	LT_BannerGift,
	LT_Photo,

	//战斗相关
	LT_BtlNPCStart,
	LT_BattleStart,
	LT_BattleEnd,
	LT_CalHonor,

	//召回好友
	LT_CallBackFriend,
	LT_CallBackFriendPlatid,

	//功能相关
	LT_SCIENCELEVELUP,// 科技升级

	LT_ADMIN_ADDRES,
	LT_ADMIN_ADDARMY,
	LT_ADMIN_DELARMY,
	LT_ADMIN_ADDBLD,
	LT_ADMIN_DELBLD,
	LT_ADMIN_SETBLDLB,
	LT_ADMIN_SETALLBLDLV,
	LT_ADMIN_SETBLDLV,
	LT_ADMIN_SETARMYLV,
	LT_ADMIN_ADDNPC,
	LT_ADMIN_DELNPC,
};

const char LOG_MSG[][32] = 
{
	"1001","LogOn          ",
	"1002","LogOut         ",
	"1003","RegisterUser   ",
	"1004","BanLogin       ",
	"1005","Upgrade        ",
	"1006","StarStat       ",
	"1007","TransferUser   ",
	"1008","MDB_Error      ",
	"1009","LoadByMDB      ",
	"1010","Expiate        ",
	"1011","UserBanLogin   ",
	"1012","ClearData      ",
	"1013","WaiGua         ",
	"1014","WaiGuaBan      ",
	"1015","RemoveUser     ",
	"1016","FinishTutorial ",
	"1017","ErrorLog       ",
	"1018","BtlWaiGua      ",
	"1019","BtlWaiGuaKick  ",


	"1100","AddCredit      ",
	"1101","CostCredit     ",
	"1102","AddRes         ",
	"1103","CostRes        ",
	"1104","SetRes         ",
	"1105","CreditBuy      ",
	"1106","FinishTask     ",
	"1107","DelArmy        ",
	"1108","DelEmeny       ",
	"1109","AddHonor       ",
	"1110","CostHonor      ",

	
};

const int MAX_LOG_SMG_LENGTH = 1024*5;
class CSysLog
{
public:

private:
	CSysLog(void);
	~CSysLog(void);
public:
	static CSysLog* GetInstance();
	void Quit();
	void SetLogInfo(bool bGameLog,int nSrvID,string strLogDir,string strLogName,string strAddr,string strPort,bool bShowLog,int nSendLogLv,int nModul,int nModulVal);
	bool CreateLog();
	bool CreateDir(const char* szDir);
	void ChgLogFile();

	void WriteCurTime();

	ofstream* GetSysLogOF(){return m_pLogSys;}


	bool IsStatUser(int64 nUserID);
	int	 GetSrvID() {return m_nSrvID;}
	void BeginMsg();
	void EndMsg(int64 nUserID,LOG_TYPE emType,int nDmd);
	void EndMsg();
	void SendMsg();
	bool InUse();
	bool NeedSend(int64 nUserID,LOG_TYPE emType,int nDmd);
#ifdef _WIN32
	inline void LogLock() {
		EnterCriticalSection( &m_Section ); 
	}
	inline void LogUnLock() {
		LeaveCriticalSection(&m_Section);
	}
#else
	inline void LogLock() {
		pthread_mutex_lock(&m_mutex);
	}
	inline void LogUnLock() {
		pthread_mutex_unlock(&m_mutex);
	}
#endif

	template <class T> CSysLog& operator << (const T &value)
	{
		sprintf(m_szBuf+m_nPos,"%d,",value);
		m_nPos = strlen(m_szBuf);

		//if(m_pLogSys&&m_bShowLog)
		//	*m_pLogSys << value <<",";
		//if(m_bSendLog)
		//{
		//	sprintf(m_szBuf+m_nPos,"%d,",value);
		//	m_nPos = strlen(m_szBuf);
		//}
		return *this;
	}
	CSysLog& operator << (int64 value);
	CSysLog& operator << (char value);
	CSysLog& operator << (double value);
	CSysLog& operator << (float value);
	CSysLog& operator << (char* szBuf);
	CSysLog& operator << (const char* szBuf);
	CSysLog& operator << (string& str);
	CSysLog& operator << (const string& str);
private:
	
private:
	CSysLogNet	m_SysLogNet;
	bool		m_bShowLog;
	int			m_nSendLogLv;
	int			m_nModul;
	int			m_nModulVal;
	bool		m_bInUse;
	int			m_nSrvID;
	string		m_strLogDir;
	string		m_strLogName;
	bool		m_bGameLog;		//true:gamelog false:halllog

	string		m_strLogDay;
	ofstream*	m_pLogSys;	
	time_t		m_lastCheck;
	int			m_nPos;
	char		m_szBuf[MAX_LOG_SMG_LENGTH];
#ifdef _WIN32
	CRITICAL_SECTION m_Section; 
#else
	pthread_mutex_t m_mutex;
#endif

};

template <class T1,class T2,class T3,class T4>
void SYS_STAT(int64 uid,string strType,int nLV,int nGender,int64 nTotalRecharge,int nRegDays,int64 nCredits,
			  bool bSendSome,T1 subTp1,T2 subTp2,T3 subTp3,T4 val1,int nVal2=0,int nVal3=0,int nVal4=0,int nVal5=0)
{
	CSysLog* pLog = CSysLog::GetInstance();
	if(!pLog->InUse())
		return;

	if(bSendSome&&!pLog->IsStatUser(uid))
	{
		return;
	}
	pLog->LogLock();
	pLog->BeginMsg();
	pLog->WriteCurTime();
	*pLog	<< pLog->GetSrvID()<<uid<<strType<<nLV<<nGender<<nTotalRecharge<<nRegDays<<nCredits<<0<<0<<0
		<< subTp1 << subTp2 << subTp3 << val1 << nVal2 << nVal3 << nVal4 << nVal5;

	pLog->SendMsg();
	pLog->LogUnLock();
}


#define CHG_LOG_FILE()	{ CSysLog::GetInstance()->ChgLogFile();}
#define SYS_LOG(uid,logType,succ,msg) \
{\
	{\
	CSysLog* pLog = CSysLog::GetInstance();\
	if(pLog->InUse())\
	{\
		pLog->LogLock();\
		pLog->BeginMsg();\
		pLog->WriteCurTime();\
		*pLog << pLog->GetSrvID()<<uid<<LOG_MSG[logType*2]<<LOG_MSG[logType*2+1]<<succ<<msg;\
		pLog->EndMsg(uid,logType,0);\
		pLog->LogUnLock();\
	}\
	}\
}

#define CACHE_LOG(logType,msg) \
{\
{\
	CSysLog* pLog = CSysLog::GetInstance();\
	if(pLog->InUse())\
{\
	pLog->LogLock();\
	pLog->BeginMsg();\
	pLog->WriteCurTime();\
	*pLog << pLog->GetSrvID()<<logType<<msg;\
	pLog->EndMsg();\
	pLog->LogUnLock();\
}\
}\
}

//old,need "," at code
//#define SYS_LOG(uid,logType,succ,msg) \
//{\
//	CSysLog* pLog = CSysLog::GetInstance();\
//	ofstream* pOF = pLog->GetSysLogOF();\
//	if(pOF)\
//	{\
//		pLog->LogLock();\
//		pLog->WriteCurTime(pOF);\
//		*pOF << pLog->GetSrvID()<<","<<uid<<","<<LOG_MSG[logType*2]<<","<<LOG_MSG[logType*2+1]<<","<<succ<<",";\
//		*pOF << msg <<std::endl;\
//		pLog->LogUnLock();\
//	}\
//}
