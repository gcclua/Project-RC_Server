#include "TimeInfo.h"

TimeInfo::TimeInfo(void)
{
	m_uLastSysRunTime = gTimeManager.SysRunTime();
	m_nAnsiTime       = _ansitime();

	tm ltm;
	_localtime(m_nAnsiTime,ltm);
	m_nLastYear      = ltm.tm_year + 1970;
	m_nLastMonth     = ltm.tm_mon;
	m_nLastDay       = ltm.tm_yday;
	m_nLastSecond    = ltm.tm_sec;
	m_nLastHour      = ltm.tm_hour;
	m_nLastMinute    = ltm.tm_min;
	Update();
}

TimeInfo::~TimeInfo(void)
{

}

void TimeInfo::Update()
{
	__ENTER_FUNCTION
		tuint32 uSysRunTime = gTimeManager.SysRunTime();
		m_nAnsiTime     = _ansitime();
		tm ltm;
		_localtime(m_nAnsiTime,ltm);
		int nYear      = ltm.tm_year + 1970;
		int nMonth     = ltm.tm_mon;
		int nDay       = ltm.tm_yday;
		int nSecond    = ltm.tm_sec;
		int nHour      = ltm.tm_hour;
		int nMinute    = ltm.tm_min;
		m_uTimeElapse = static_cast<int>(uSysRunTime-m_uLastSysRunTime);

		m_bDiffYear    = (m_nLastYear != nYear);
		m_bDiffMonth   = (m_nLastMonth != nMonth);
		m_bDiffDay     = (m_nLastDay != nDay);
		m_bDiffSecond  =  (m_nLastSecond != nSecond);
		m_bDiffHour    = (m_nLastHour != nHour);
		m_bDiffMinute  = (m_nLastMinute != nMinute);
		m_uLastSysRunTime = uSysRunTime;
		m_nLastYear       = nYear;
		m_nLastMonth      = nMonth;
		m_nLastDay        = nDay;
		m_nLastHour       = nHour;
		m_nLastMinute     = nMinute;
		m_nLastSecond     = nSecond;
	__LEAVE_FUNCTION
}