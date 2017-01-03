#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

#include "BaseType.h"
#include "BaseLib.h"

/*
关于时间和日期，着重说明一下
首先区分时间、日期两个概念，时间是一个区间，日期是一个点
例如：日期-日期=时间，日期+时间=日期
因此GetANSITime返回的其实是一个时间，即1970.1.1零时以来的秒数
而Time2DWORD返回的则是日期
GetANSITime返回的虽然是一个时间，但加上1970.1.1零时这个日期，也可以表示一个日期
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
	输入：void
	输出：系统到现在为止运行了多少毫秒
	*/
	tuint32 SysRunTime(void);
	/*
	输入：void
	输出：程序运行了多少毫秒
	*/
	tuint32	RunTime(void);
	/*
	输入：void
	输出：程序启动时系统运行了多少毫秒
	*/
	tuint32 StartTime(void) const
	{
		return m_StartTime;
	}
	/*
	输入：void
	输出：void
	更新对当前系统日期的记录值
	*/
	void	SetTime(void);
	/*
	输入：void
	输出：返回1970.1.1零时到现在经历了多少秒
	*/
	time_t	GetANSITime(void);
	/*
	输入：void
	输出：获取当前日期的分量
	*/
	tint32	GetYear(void) const		{return m_TM.tm_year+1900;}	//[1900,????]
	tint32	GetMonth(void) const	{return m_TM.tm_mon;}		//[0,11]
	tint32	GetDay(void) const		{return m_TM.tm_mday;}		//[1,31]
	tint32	GetHour(void) const		{return m_TM.tm_hour;}		//[0,23]
	tint32	GetMinute(void) const	{return m_TM.tm_min;}		//[0,59]
	tint32	GetSecond(void) const	{return m_TM.tm_sec;}		//[0,59]
	tint32	GetYDay(void) const		{return m_TM.tm_yday;}		//[0,365]
	tint32	GetWeek(void) const		{return m_TM.tm_wday;}		//取得当前是星期几；0表示：星期天，1～6表示：星期一～星期六
	/*
	输入：void
	输出：返回当前日期，格式为tuint32表示的年、月、日、时、分，例如：0,507,211,233 表示 "2005.07.21 12:33"
	*/
	tuint32	Time2DWORD(void);
	/*
	输入：日期分量
	输出：返回指定日期，格式同上
	*/
	tuint32 Time2DWORD(tint32 year, tint32 month, tint32 day, tint32 hour, tint32 minute);
	/*
	输入：Time2DWORD函数返回的日期
	输出：标准日期
	*/
	void	DWORD2Time(tuint32 Date, tm &TM);
	/*
	输入：Time2DWORD函数返回的日期
	输出：相差的分钟
	*/
	tuint32 DiffDWORDTime(tuint32 Date1, tuint32 Date2);
	/*
	输入：标准时间
	输出：相差天数
	*/
	tint32	DiffDayCount(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	输入：标准时间
	输出：是否是同一天（以0点为分界）
	*/
	bool	IsDiffDay00(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	输入：标准时间
	输出：是否是同一天（以4点为分界）
	*/
	bool	IsDiffDay04(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	输入：标准时间
	输出：是否是同一天（以12点为分界）
	*/
	bool	IsDiffDay12(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	输入：标准时间
	输出：是否是同一天（以18点为分界）
	*/
	bool	IsDiffDay18(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	输入：标准时间
	输出：是否是同一天（以20点为分界）
	*/
	bool	IsDiffDay20(time_t uPrevANSITime, time_t uNextANSITime);
	/*
	输入：标准时间
	输出：输出小时
	*/
	tint32	GetHour(time_t uANSITime);
	/*
	输入：void
	输出：返回当前日期，格式为tuint32表示的年、月、日，例如：20070403表示2007年4月3日
	*/
	tuint32	Time2Day(void);
	/*
	输入：void
	输出：返回当前日期，格式为tuint32表示的年、月、日、时、分、秒，[6bit 0-99][4bit 0-11][5bit 0-30][5bit 0-23][6bit 0-59][6bit 0-59]
	*/
	tuint32	CurrentDate(void);
	/*
	输入：CurrentDate或ConvertTU得到的日期
	输出：两个日期的差值，毫秒，超过42天会溢出
	*/
	tuint32	DiffTime(tuint32 Date1, tuint32 Date2);
	/*
	输入：CurrentDate或ConvertTU得到的日期
	输出：两个日期的差值，秒
	*/
	tuint32	DiffTime_InSecond(tuint32 Date1, tuint32 Date2);
	/*
	输入：和CurrentDate返回值同格式的日期
	输出：标准日期
	*/
	void	ConvertUT(tuint32 Date, tm *TM);
	/*
	输入：标准日期
	输出：和CurrentDate返回值同格式的日期
	*/
	void	ConvertTU(tm *TM, tuint32 &Date);
	/*
	输入：void
	输出：返回当前日期，精确到天，千位数代表年份，后三位代表天数
	*/
	tuint32	GetDayTime(void);
	/*
	输入：void
	输出：返回当前日期，精确到小时，例如12723表示本年度第127天的5(23/4)点的第3(23%4)刻钟
	*/
	tuint32	GetHourTime(void);
	/*
	输入：void
	输出：返回当前日期，精确到时刻，[0-99当前年份-2000][0-365当前是今年的第几天][0-96当前是今天的第几个时刻(15mins)]，例:903461表示2009年第34天的第61个时刻
	*/
	tuint32	GetQuarterTime(void);
	/*
	输入：void
	输出：返回当前日期，精确到周，千位数代表年份，其他三位代表周数
	*/
	tuint32	GetWeekTime(void);
	/*
	输入：日期分量(年份为真实年份)
	输出：星期几；0表示：星期天，1～6表示：星期一～星期六
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
