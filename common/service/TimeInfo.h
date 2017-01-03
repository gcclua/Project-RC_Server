
#ifndef _TIMEINFO_H_
#define _TIMEINFO_H_

#include "Base.h"

class TimeInfo
{
public:
	TimeInfo();
	~TimeInfo();

public:
	void Update();

public:

	int  m_uTimeElapse ;    // 上次心跳到本次心跳，隔了多少毫秒
	bool m_bDiffYear;       // 上次心跳到本次心跳，是否跨年
	bool m_bDiffMonth;      // 上次心跳到本次心跳，是否跨月
	bool m_bDiffDay;        // 上次心跳到本次心跳，是否跨天
	bool m_bDiffSecond;     // 上次心跳到本次心跳，是否垮秒
	bool m_bDiffHour;       // 上次心跳到本次心跳，是否跨小时
	bool m_bDiffMinute;     // 上次心跳到本次心跳，是否跨分钟

public:
	time_t m_nAnsiTime;     // 1970.1.1零时到现在经历了多少秒

private:
	tuint32   m_uLastSysRunTime;
	int   m_nLastYear;
	int   m_nLastMonth;
	int   m_nLastDay;
	int   m_nLastHour;
	int   m_nLastMinute;
	int   m_nLastSecond;

};


#endif