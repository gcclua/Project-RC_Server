
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

	int  m_uTimeElapse ;    // �ϴ��������������������˶��ٺ���
	bool m_bDiffYear;       // �ϴ������������������Ƿ����
	bool m_bDiffMonth;      // �ϴ������������������Ƿ����
	bool m_bDiffDay;        // �ϴ������������������Ƿ����
	bool m_bDiffSecond;     // �ϴ������������������Ƿ����
	bool m_bDiffHour;       // �ϴ������������������Ƿ��Сʱ
	bool m_bDiffMinute;     // �ϴ������������������Ƿ�����

public:
	time_t m_nAnsiTime;     // 1970.1.1��ʱ�����ھ����˶�����

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