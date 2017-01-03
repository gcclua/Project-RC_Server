#include "TimeManager.h"
#include "Misc.h"
#if defined(_WIN32)
#include <Windows.h>
#endif


TimeManager gTimeManager;

TimeManager::TimeManager(void)
{
	Init();
}

TimeManager::~TimeManager(void)
{

}

void TimeManager::Init(void)
{
#if defined(_WIN32)
	{
		m_StartTime = GetTickCount();
		m_CurrentTime = GetTickCount();
	}
#else
	{
		m_StartTime = 0;
		m_CurrentTime = 0;
		gettimeofday(&_tstart,&_tz);
	}
#endif
	SetTime();
}

tuint32 TimeManager::SysRunTime(void)
{
#if defined(_WIN32)
	{
		m_CurrentTime = GetTickCount();
	}
#else
	{
		struct timeval _tend;
		gettimeofday(&_tend,&_tz);
		double t1,t2;
		t1 = (double)_tstart.tv_sec*1000 + (double)_tstart.tv_usec/1000;
		t2 = (double)_tend.tv_sec*1000 + (double)_tend.tv_usec/1000;
		m_CurrentTime = (tuint32)(t2-t1);
		
	}
#endif
	return m_CurrentTime;
}

tuint32 TimeManager::RunTime(void)
{
	SysRunTime();
	if (m_CurrentTime < m_StartTime)
	{
		return ((tuint32)0XFFFFFFFF-m_StartTime) + m_CurrentTime;
	}
	else
	{
		return m_CurrentTime - m_StartTime;
	}
}

tuint32 TimeManager::CurrentDate(void)
{
	tuint32 Date;
	ConvertTU(&m_TM,Date);
	return Date;
}

void TimeManager::SetTime(void)
{
	time_t TempAnsiTime = _ansitime();
	tm TempLocalTime;
	_localtime(TempAnsiTime,TempLocalTime);

	m_SetTime = TempAnsiTime;
	memcpy(&m_TM,&TempLocalTime,sizeof(tm));
}

time_t TimeManager::GetANSITime(void)
{
	return _ansitime();
}

tuint32 TimeManager::Time2DWORD(void)
{
	tuint32 uRet = 0;
	uRet += GetYear();
	uRet -= 2000;
	uRet = uRet*100;

	uRet += GetMonth()+1;
	uRet = uRet*100;

	uRet += GetDay();
	uRet = uRet*100;

	uRet += GetHour();
	uRet = uRet*100;

	uRet += GetMinute();
	return uRet;
}

tuint32 TimeManager::Time2DWORD(tint32 year, tint32 month, tint32 day, tint32 hour, tint32 minute)
{
	if (!(year>=2000 && year<=2500)) return 0;
	if (!(month >= 1 && month<12)) return 0;
	if (!(day>=1 && month<=31)) return 0;
	if (!(hour>=0 && hour<=23)) return 0;
	if (!(minute>=0 && minute<60)) return 0;

	tuint32 uRet = 0;
	uRet += year;
	uRet -= 2000;
	uRet = uRet*100;

	uRet += month;
	uRet = uRet*100;

	uRet += day;
	uRet = uRet*100;

	uRet += hour;
	uRet = uRet*100;

	uRet += minute;
	return uRet;
}

void TimeManager::DWORD2Time(tuint32 Date, tm &TM)
{
	memset(&TM,0,sizeof(tm));

	TM.tm_year = (Date / 100000000) + 2000 -1900;
	TM.tm_mon  = (Date % 100000000) / 1000000 - 1;
	TM.tm_mday = (Date % 1000000) /10000;
	TM.tm_hour = (Date % 10000) / 100;
	TM.tm_min  = Date % 100;
	TM.tm_wday = ConvertWDay(TM.tm_year + 1900,TM.tm_mon +1 ,TM.tm_mday);
}

tuint32 TimeManager::DiffDWORDTime(tuint32 Date1, tuint32 Date2)
{
	tm S_D1,S_D2;
	DWORD2Time(Date1,S_D1);
	DWORD2Time(Date2,S_D2);

	time_t t1,t2;

	t1 = mktime(&S_D1);
	t2 = mktime(&S_D2);

	tuint32 dif = (tuint32)( abs( (tint32) (difftime(t2,t1)/60)));
	return dif;
}

bool TimeManager::IsDiffDay00(time_t uPrevANSITime, time_t uNextANSITime)
{
	tm tPrevTm;
	_localtime(uPrevANSITime,tPrevTm);

	tm tCurTm;
	_localtime(uNextANSITime,tCurTm);

	return tCurTm.tm_year != tPrevTm.tm_year || tCurTm.tm_yday != tPrevTm.tm_yday;
}
/*
输入：标准时间
输出：是否是同一天（以4点为分界）
*/
bool TimeManager::IsDiffDay04(time_t uPrevANSITime, time_t uNextANSITime)
{
	time_t nTime1 = uPrevANSITime - 14400;
	time_t nTime2 = uNextANSITime - 14400;

	nTime1 = _MAX(nTime1,0);
	nTime2 = _MAX(nTime2,0);
	return IsDiffDay00(nTime1,nTime2);
}

/*
输入：标准时间
输出：是否是同一天（以12点为分界）
*/
bool TimeManager::IsDiffDay12(time_t uPrevANSITime, time_t uNextANSITime)
{
	time_t nTime1 = uPrevANSITime - 43200;
	time_t nTime2 = uNextANSITime - 43200;

	nTime1 = _MAX(nTime1,0);
	nTime2 = _MAX(nTime2,0);
	return IsDiffDay00(nTime1,nTime2);
}
/*
输入：标准时间
输出：是否是同一天（以18点为分界）
*/
bool TimeManager::IsDiffDay18(time_t uPrevANSITime, time_t uNextANSITime)
{
	time_t nTime1 = uPrevANSITime - 64800;
	time_t nTime2 = uNextANSITime - 64800;

	nTime1 = _MAX(nTime1,0);
	nTime2 = _MAX(nTime2,0);
	return IsDiffDay00(nTime1,nTime2);
}
/*
输入：标准时间
输出：是否是同一天（以20点为分界）
*/
bool TimeManager::IsDiffDay20(time_t uPrevANSITime, time_t uNextANSITime)
{
	time_t nTime1 = uPrevANSITime - 72000;
	time_t nTime2 = uNextANSITime - 72000;

	nTime1 = _MAX(nTime1,0);
	nTime2 = _MAX(nTime2,0);
	return IsDiffDay00(nTime1,nTime2);
}

tint32 TimeManager::GetHour(time_t uANSITime)
{
	tm tTm;


	_localtime(uANSITime,tTm);
	return tTm.tm_hour;
}

tint32 TimeManager::DiffDayCount(time_t uPrevANSITime, time_t uNextANSITime)
{
	tint32 dif = (tuint32)(difftime(uNextANSITime,uPrevANSITime)/(24*60*60));
	return dif;
}

tuint32 TimeManager::Time2Day(void)
{
	tuint32 uRet = 0;
	uRet += GetYear();
	
	uRet += uRet*100;
	uRet += GetMonth() +1;

	uRet += uRet*100;
	uRet += GetDay();

	return uRet;
}

tuint32 TimeManager::DiffTime(tuint32 Date1, tuint32 Date2)
{
	tm S_D1, S_D2;

	ConvertUT(Date1, &S_D1);
	ConvertUT(Date2, &S_D2);

	time_t t1,t2;


	t1 = mktime(&S_D1);
	t2 = mktime(&S_D2);

	tuint32 dif = (tuint32)( abs( (tint32) (difftime(t2,t1)))*1000);
	return dif;
}

tuint32 TimeManager::DiffTime_InSecond(tuint32 Date1,tuint32 Date2)
{
	tm S_D1, S_D2;

	ConvertUT(Date1, &S_D1);
	ConvertUT(Date2, &S_D2);

	time_t t1,t2;


	t1 = mktime(&S_D1);
	t2 = mktime(&S_D2);

	tuint32 dif = (tuint32)abs( (tint32) difftime(t2,t1));
	return dif;
}

void TimeManager::ConvertUT(tuint32 Date,tm* TM)
{
	if (TM != null_ptr)
	{
		memset(TM,0,sizeof(tm));

		TM->tm_year = ((Date>>26)&0x3f) + 100;
		TM->tm_mon  = (Date>>22)&0xf;
		TM->tm_mday = (Date>>17)&0x1f;
		TM->tm_hour = (Date>>12)&0x1f;
		TM->tm_min  = (Date>>6)&0x3f;
		TM->tm_sec  = (Date)   &0x3f;
	}
}

void TimeManager::ConvertTU(tm *TM, tuint32 &Date)
{
	if (TM != null_ptr)
	{
		Date = 0;
		Date += (TM->tm_year%100) & 0x3f;
		Date  =(Date<<4);
		Date += TM->tm_mon & 0xf;
		Date = (Date<<5);
		Date += TM->tm_mday & 0x1f;
		Date = (Date<<5);
		Date += TM->tm_hour & 0x1f;
		
		Date = (Date<<6);
		Date += TM->tm_min & 0x3f;
		Date = (Date<<6);
		Date += TM->tm_sec & 0x3f;
	}
}

tuint32 TimeManager::GetDayTime()
{
	tm ltm;
	_localtime(m_SetTime,ltm);
	
	tuint32 uRet = 0;
	uRet = (ltm.tm_year-100)*1000;
	uRet += ltm.tm_yday;

	return uRet;
}

tuint32 TimeManager::GetHourTime(void)
{
#define  ANSI_TIME_2007_0101_000000 ( 1167580800)
#define  SECONDS_PER_DAY (86400)

	tm ltm;
	_localtime(m_SetTime,ltm);

	tuint32 uRet = 0;
	uRet = ((tint32)m_SetTime - ANSI_TIME_2007_0101_000000) / SECONDS_PER_DAY;

	uRet *= 100;
	uRet += ltm.tm_hour*4;
	uRet += (tuint32)(ltm.tm_min/15);

	return uRet;
}

tuint32 TimeManager::GetQuarterTime(void)
{
	tm ltm;
	_localtime(m_SetTime,ltm);

	tuint32 uRet = 0;
	uRet = ltm.tm_year - 100;
	uRet *= 1000;
	uRet += ltm.tm_yday;
	uRet *= 100;

	uRet += ltm.tm_hour*4;
	uRet += (tuint32)(ltm.tm_min/15);
	return uRet;
}

tuint32 TimeManager::GetWeekTime()
{
	tm ltm;
	_localtime(m_SetTime,ltm);

	tuint32 uRet = 0;
	uRet = (ltm.tm_year - 100)*1000;

	if (ltm.tm_yday <= ltm.tm_wday)
	{
		return uRet;
	}

	tint32 it = ltm.tm_yday-ltm.tm_wday;
	uRet += static_cast<tuint32>(ceil((double)it/7));
	return uRet;
}

tint32 TimeManager::ConvertWDay(tint32 year, tint32 month, tint32 day)
{
	if (month == 1 || month == 2)
	{
		month += 12;
		year  -= 1;
	}

	tint32 wday = (day + 2 * month + 3*(month+1)/5 + year + year/4 -year/100 + year/400+1)%7;
	return wday;
}