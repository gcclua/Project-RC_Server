
#ifndef _INVOKER_H_
#define _INVOKER_H_

#include "Base.h"
#include "TimeInfo.h"

class Invoker
{
public:
	enum 
	{
		// ����״̬�����ڴ�״̬ʱ���Խ��е���
		STATE_READY = 0,
		// ����״̬ ����ʱ���ܽ���ִ��״̬
		STATE_SCHEDULING,
		// ִ��״̬��ִ����ɺ�תΪ����״̬
		STATE_RUNNING,
	};

public:
	Invoker(const tchar *szName,int nNormalInitDoingInterval,int nSlowlyInitDoingInterval);
	virtual ~Invoker(void);

private:
	FLString<64> m_szName;

public:
	// �ײ�ʹ�ã��߼������
	void Invoke(void);
public:
	virtual int GetRunState(void ) = 0;

protected:
	// �ɽ��˺��������Ƕ�ʱ���õ���������
	virtual void Doing(void) = 0;

public:
	void UpdateDoingInterval(int nElapse){m_nDoingInterval += nElapse;}
	bool IsOverNormalDoingInterval(void) const {return (m_nDoingInterval >= m_nNormalInitDoingInterval);}
	bool IsOverSlowlyDoingInterval(void) const {return (m_nDoingInterval >= m_nSlowlyInitDoingInterval);}

private:
	int m_nNormalInitDoingInterval;
	int m_nSlowlyInitDoingInterval;
	int m_nDoingInterval;

public:
	int  GetState(void) const;
	void SetState(int nState);

public:
	void CheckScheduleState(int nElapse);
	void CheckRunState(int nElapse);

private:
	int  m_nState;
	int  m_nScheduleTime;
	int  m_nRunTime;

public:
	void UpdateTimeInfo(void){m_TimeInfo.Update();}
	const TimeInfo& GetTimeInfo(void) const {return m_TimeInfo;}

private:
	TimeInfo m_TimeInfo;

};

typedef boost::shared_ptr<Invoker> InvokerPtr;
typedef std::list<InvokerPtr>     InvokerPtrList;
typedef tslist<InvokerPtr>        InvokerTSList;
typedef std::set<InvokerPtr>       InvokerPtrSet;

template<typename _ServiceT,int _NormalInterval,int _SlowlyInterval>
class GeneralInvoker : public Invoker
{
public:
	explicit GeneralInvoker< _ServiceT, _NormalInterval,_SlowlyInterval>(_ServiceT &rService, const tchar* szName)
		:Invoker(szName,_NormalInterval,_SlowlyInterval)
		,m_rService(rService)
	{

	}
	virtual ~GeneralInvoker< _ServiceT, _NormalInterval,_SlowlyInterval>(void)
	{

	}

public:
	virtual int GetRunState(void)
	{
		return m_rService.GetRunState();
	}

protected:
	virtual void Doing(void)
	{
		UpdateTimeInfo();
		m_rService.Tick(GetTimeInfo());
	}

private:
	_ServiceT &m_rService;
};


#endif