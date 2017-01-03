#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

#include "BaseType.h"
#include "BaseLib.h"

/*
����ʱ������ڣ�����˵��һ��
��������ʱ�䡢�����������ʱ����һ�����䣬������һ����
���磺����-����=ʱ�䣬����+ʱ��=����
���GetANSITime���ص���ʵ��һ��ʱ�䣬��1970.1.1��ʱ����������
��Time2DWORD���ص���������
GetANSITime���ص���Ȼ��һ��ʱ�䣬������1970.1.1��ʱ������ڣ�Ҳ���Ա�ʾһ������
*/

class TimeManager
{
public:
	TimeManager(void);
	~TimeManager(void);
private:
	void	Init(void);

public:
	/*
	���룺void
	�����ϵͳ������Ϊֹ�����˶��ٺ���
	*/
	tuint32 SysRunTime(void);
	/*
	���룺void
	��������������˶��ٺ���
	*/
	tuint32	RunTime(void);
	/*
	���룺void
	�������������ʱϵͳ�����˶��ٺ���
	*/
	tuint32 StartTime(void) const
	{
		return m_StartTime;
	}
	/*
	���룺void
	�����void
	���¶Ե�ǰϵͳ���ڵļ�¼ֵ
	*/
	void	SetTime(void);
	/*
	���룺void
	���������1970.1.1��ʱ�����ھ����˶�����
	*/
	time_t	GetANSITime(void);
	/*
	���룺void
	�������ȡ��ǰ���ڵķ���
	*/
	tint32	GetYear(void) const		{return m_TM.tm_year+1900;}	//[1900,????]
	tint32	GetMonth(void) const	{return m_TM.tm_mon;}		//[0,11]
	tint32	GetDay(void) const		{return m_TM.tm_mday;}		//[1,31]
	tint32	GetHour(void) const		{return m_TM.tm_hour;}		//[0,23]
	tint32	GetMinute(void) const	{return m_TM.tm_min;}		//[0,59]
	tint32	GetSecond(void) const	{return m_TM.tm_sec;}		//[0,59]
	tint32	GetYDay(void) const		{return m_TM.tm_yday;}		//[0,365]
	tint32	GetWeek(void) const		{return m_TM.tm_wday;}		//ȡ�õ�ǰ�����ڼ���0��ʾ�������죬1��6��ʾ������һ��������
	/*
	���룺void
	��������ص�ǰ���ڣ���ʽΪtuint32��ʾ���ꡢ�¡��ա�ʱ���֣����磺0,507,211,233 ��ʾ "2005.07.21 12:33"
	*/
	tuint32	Time2DWORD(void);
	/*
	���룺���ڷ���
	���������ָ�����ڣ���ʽͬ��
	*/
	tuint32 Time2DWORD(tint32 year, tint32 month, tint32 day, tint32 hour, tint32 minute);
	/*
	���룺Time2DWORD�������ص�����
	�������׼����
	*/
	void	DWORD2Time(tuint32 Date, tm &TM);
	/*
	���룺Time2DWORD�������ص�����
	��������ķ���
	*/
	tuint32 DiffDWORDTime(tuint32 Date1, tuint32 Date2);
	/*
	���룺��׼ʱ��
	������������
	*/
	tint32	DiffDayCount(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	���룺��׼ʱ��
	������Ƿ���ͬһ�죨��0��Ϊ�ֽ磩
	*/
	bool	IsDiffDay00(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	���룺��׼ʱ��
	������Ƿ���ͬһ�죨��4��Ϊ�ֽ磩
	*/
	bool	IsDiffDay04(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	���룺��׼ʱ��
	������Ƿ���ͬһ�죨��12��Ϊ�ֽ磩
	*/
	bool	IsDiffDay12(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	���룺��׼ʱ��
	������Ƿ���ͬһ�죨��18��Ϊ�ֽ磩
	*/
	bool	IsDiffDay18(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	���룺��׼ʱ��
	������Ƿ���ͬһ�죨��20��Ϊ�ֽ磩
	*/
	bool	IsDiffDay20(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	���룺��׼ʱ��
	��������Сʱ
	*/
	tint32	GetHour(time_t uANSITime);
	/*
	���룺void
	��������ص�ǰ���ڣ���ʽΪtuint32��ʾ���ꡢ�¡��գ����磺20070403��ʾ2007��4��3��
	*/
	tuint32	Time2Day(void);
	/*
	���룺void
	��������ص�ǰ���ڣ���ʽΪtuint32��ʾ���ꡢ�¡��ա�ʱ���֡��룬[6bit 0-99][4bit 0-11][5bit 0-30][5bit 0-23][6bit 0-59][6bit 0-59]
	*/
	tuint32	CurrentDate(void);
	/*
	���룺CurrentDate��ConvertTU�õ�������
	������������ڵĲ�ֵ�����룬����42������
	*/
	tuint32	DiffTime(tuint32 Date1, tuint32 Date2);
	/*
	���룺CurrentDate��ConvertTU�õ�������
	������������ڵĲ�ֵ����
	*/
	tuint32	DiffTime_InSecond(tuint32 Date1, tuint32 Date2);
	/*
	���룺��CurrentDate����ֵͬ��ʽ������
	�������׼����
	*/
	void	ConvertUT(tuint32 Date, tm *TM);
	/*
	���룺��׼����
	�������CurrentDate����ֵͬ��ʽ������
	*/
	void	ConvertTU(tm *TM, tuint32 &Date);
	/*
	���룺void
	��������ص�ǰ���ڣ���ȷ���죬ǧλ��������ݣ�����λ��������
	*/
	tuint32	GetDayTime(void);
	/*
	���룺void
	��������ص�ǰ���ڣ���ȷ��Сʱ������12723��ʾ����ȵ�127���5(23/4)��ĵ�3(23%4)����
	*/
	tuint32	GetHourTime(void);
	/*
	���룺void
	��������ص�ǰ���ڣ���ȷ��ʱ�̣�[0-99��ǰ���-2000][0-365��ǰ�ǽ���ĵڼ���][0-96��ǰ�ǽ���ĵڼ���ʱ��(15mins)]����:903461��ʾ2009���34��ĵ�61��ʱ��
	*/
	tuint32	GetQuarterTime(void);
	/*
	���룺void
	��������ص�ǰ���ڣ���ȷ���ܣ�ǧλ��������ݣ�������λ��������
	*/
	tuint32	GetWeekTime(void);
	/*
	���룺���ڷ���(���Ϊ��ʵ���)
	��������ڼ���0��ʾ�������죬1��6��ʾ������һ��������
	*/
	tint32 ConvertWDay(tint32 year, tint32 month, tint32 day);

private:
	tuint32		m_StartTime;
	tuint32		m_CurrentTime;
	time_t		m_SetTime;
	tm			m_TM;

private:
#ifdef __LINUX__
	struct timeval _tstart;
	struct timezone _tz;
#endif
};

extern TimeManager gTimeManager;

#endif
