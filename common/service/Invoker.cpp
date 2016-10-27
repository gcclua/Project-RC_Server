#include "Invoker.h"
#include "SysLog.h"

Invoker::Invoker(string szName,int nNormalInitDoingInterval,int nSlowlyInitDoingInterval)
{
	m_szName = szName;
	m_nNormalInitDoingInterval = nNormalInitDoingInterval;
	m_nSlowlyInitDoingInterval = nSlowlyInitDoingInterval;
	m_nDoingInterval = 0;
	SetState(STATE_READY);
	m_nScheduleTime = 0;
	m_nRunTime      = 0;
}

Invoker::~Invoker(void)
{

}

void Invoker::Invoke(void)
{
	SetState(STATE_RUNNING);

	__ENTER_PROTECT
		Doing();
	__LEAVE_PROTECT

	m_nDoingInterval = 0;
	SetState(STATE_READY);
}

int Invoker::GetState(void) const
{
	return m_nState;
}

void Invoker::SetState(int nState)
{
	m_nState = nState;
	if (m_nState == STATE_SCHEDULING)
	{
		m_nScheduleTime = 0;
	}
	
	if (m_nState == STATE_RUNNING)
	{
		m_nRunTime = 0;
	}
}

void Invoker::CheckScheduleState(int nElapse)
{
	int nLastScheduleTime = m_nScheduleTime;
	m_nScheduleTime += nElapse;

	if (m_nScheduleTime >1000)
	{
		if (static_cast<int>(nLastScheduleTime /1000) != static_cast<int>(m_nScheduleTime / 1000))
		{
			CACHE_LOG("Efficiency","Schedule Slowly, Invoker(%s),Time(%d)"<<m_szName<<m_nScheduleTime);
		}
	}
}

void Invoker::CheckRunState(int nElapse)
{
	int uLastRunTime = m_nRunTime;
	m_nRunTime += nElapse;
	if (m_nRunTime > 1000)
	{
		if (static_cast<int>(uLastRunTime /1000) != static_cast<int>(m_nRunTime / 1000))
		{
			CACHE_LOG("Efficiency","Run Slowly, Invoker("<<m_szName<<"),Time("<<m_nRunTime<<")");
		}
	}
}