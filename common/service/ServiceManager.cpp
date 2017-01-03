#include "ServiceManager.h"

ServiceManager gServiceManager;
extern bool gIsShouldShutdownBySignal;
extern bool gIsShouldShutdownByGM;

ServiceManager::ServiceManager(void)
	:m_nStatus(ServiceManagerStatus::EMPTY)
	,m_nLogCpuMemStat_Time(0)
	,m_nInvokeMonitor_JoinCount(0)
	,m_nInvokeMonitor_Time(0)
	,m_nInvokeMonitor_ScheduleCount(0)
{

}

ServiceManager::~ServiceManager(void)
{

}

void ServiceManager::Create(int nServiceCount,tint32 nThreadCount)
{
	__ENTER_FUNCTION

	AssertEx(m_ServicePtrVec.empty(),"");
	m_ServicePtrVec.resize(nServiceCount);

	AssertEx(!m_CPUPoolPtr,"");
	m_CPUPoolPtr = CPUPoolPtr(new CPUPool(nThreadCount));

	__LEAVE_FUNCTION
}

void ServiceManager::Register(Service*  pInst)
{
	__ENTER_FUNCTION

	AssertEx(pInst != null_ptr,"");
	ServicePtr ptr(pInst);

	AssertEx(ptr,"");
	const int nID = ptr->GetServiceID();
	AssertEx(nID >= 0 && nID< (int)m_ServicePtrVec.size(),"");

	AssertEx(!m_ServicePtrVec[nID],"");
	m_ServicePtrVec[nID] = ptr;

	__LEAVE_FUNCTION
}

void ServiceManager::Run(void)
{
	__ENTER_FUNCTION

	RunOpenup();

	RunMainLogic();

	RunShutdown();

	RunFinalSave();

	__LEAVE_FUNCTION

}

void ServiceManager::RunOpenup(void)
{
	__ENTER_FUNCTION

		m_nStatus = ServiceManagerStatus::OPENUP;
		SetAllServiceStatus(ServiceStatus::OPENUP);

		uint32 uLastTickTime = gTimeManager.SysRunTime();
		while(true)
		{
			uint32 uCurrentTime = gTimeManager.SysRunTime();
			int nElapse = static_cast<int>(uCurrentTime-uLastTickTime);
			uLastTickTime = uCurrentTime;

			Tick(nElapse);
			if (IsAllServiceStatusEqual(ServiceStatus::OPENUP_OK))
			{
				break;
			}
			_Sleep(10);
		}

		Wait(600);


	__LEAVE_FUNCTION
}

void ServiceManager::RunMainLogic(void)
{
	__ENTER_FUNCTION
		m_nStatus = ServiceManagerStatus::RUNNING;
		SetAllServiceStatus(ServiceStatus::RUNNING);
		
		uint32 uLastTickTime = gTimeManager.SysRunTime();
		int    nShutdownCheckTime = 10000;
		while (true)
		{
			uint32 uCurrentTime = gTimeManager.SysRunTime();
			int  nElapse      = static_cast<int>(uCurrentTime-uLastTickTime);
			uLastTickTime = uCurrentTime;
			Tick(nElapse);

			nShutdownCheckTime -= nElapse;
			if (nShutdownCheckTime <=0)
			{
				nShutdownCheckTime = 10000;
				if (IsShoudShutdown())
				{
					break;
				}
			}
			_Sleep(10);
		}

		Wait(600);

	__LEAVE_FUNCTION
}

void ServiceManager::RunShutdown( void )
{
	__ENTER_FUNCTION
		m_nStatus = ServiceManagerStatus::SHUTDOWN;
	    SetAllServiceStatus(ServiceStatus::SHUTDOWN);
		uint32 uLastTickTime = gTimeManager.SysRunTime();
		while(true)
		{
			uint32 uCurrentTime = gTimeManager.SysRunTime();
			int nElapse = static_cast<int>(uCurrentTime-uLastTickTime);
			uLastTickTime = uCurrentTime;

			Tick(nElapse);
			if (IsAllServiceStatusEqual(ServiceStatus::SHUTDOWN_OK))
			{
				break;
			}
			_Sleep(10);
		}

		Wait(600);
		
	__LEAVE_FUNCTION
}

void ServiceManager::RunFinalSave( void )
{
	__ENTER_FUNCTION
		m_nStatus = ServiceManagerStatus::FINALSAVE;
	SetAllServiceStatus(ServiceStatus::FINALSAVE);
	uint32 uLastTickTime = gTimeManager.SysRunTime();
	while(true)
	{
		uint32 uCurrentTime = gTimeManager.SysRunTime();
		int nElapse = static_cast<int>(uCurrentTime-uLastTickTime);
		uLastTickTime = uCurrentTime;

		Tick(nElapse);
		if (IsAllServiceStatusEqual(ServiceStatus::FINALSAVE_OK))
		{
			break;
		}
		_Sleep(10);
	}

	Wait(600);

	__LEAVE_FUNCTION
}

void ServiceManager::Wait(int nSecondTimeOut)
{
	__ENTER_FUNCTION
		AssertEx(m_CPUPoolPtr,"");

		boost::xtime xt;
		xtime_get(&xt,boost::TIME_UTC_);
		xt.sec += nSecondTimeOut;

		VerifyEx(m_CPUPoolPtr->wait(xt),"");
	__LEAVE_FUNCTION
}

void ServiceManager::InitAllService()
{
	__ENTER_FUNCTION
		for (int i=0; i<static_cast<int>(m_ServicePtrVec.size()); i++)
		{
			AssertEx(m_ServicePtrVec[i],"");
			m_ServicePtrVec[i]->Init();
		}
	__LEAVE_FUNCTION
}

bool ServiceManager::IsAllServiceStatusEqual(int nStatus)
{
	__ENTER_FUNCTION
		for (int i=0; i<static_cast<int>(m_ServicePtrVec.size()); i++)
		{
			AssertEx(m_ServicePtrVec[i],"");
			if (m_ServicePtrVec[i]->GetStatus() != nStatus)
			{
				//int n = m_ServicePtrVec[i]->GetStatus();
				return false;
			}
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

void ServiceManager::SetAllServiceStatus(int nStatus)
{
	__ENTER_FUNCTION
		for (int i=0; i<static_cast<int>(m_ServicePtrVec.size()); i++)
		{
			AssertEx(m_ServicePtrVec[i],"");
			m_ServicePtrVec[i]->SetStatus(nStatus);
		}
		__LEAVE_FUNCTION
}

bool ServiceManager::IsShoudShutdown(void)
{
	__ENTER_FUNCTION
		if (gIsShouldShutdownBySignal)
		{
			return true;
		}
		if (gIsShouldShutdownByGM)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}

void ServiceManager::ReceiveMessage(int nServiceID,ConstMessagePtr ConstPtr)
{
	__ENTER_FUNCTION
		if (nServiceID>=0 && nServiceID <(int)m_ServicePtrVec.size())
		{
			AssertEx(m_ServicePtrVec[nServiceID],"");
			m_ServicePtrVec[nServiceID]->ReceiveMessage(ConstPtr);
		}
	__LEAVE_FUNCTION
}

void ServiceManager::Tick(int nElapse)
{
	__ENTER_FUNCTION
		gTimeManager.SetTime();
		UpdateAllService(nElapse);
	    UpdateAllInvoker(nElapse);
		UpdateInvokeMonitor(nElapse);

	__LEAVE_FUNCTION
}

void ServiceManager::UpdateAllService(int nElapse)
{
	__ENTER_FUNCTION
		for (int i=0;i<(int)m_ServicePtrVec.size();i++)
		{
			AssertEx(m_ServicePtrVec[i],"");
			for (int j=0;j < 128; j++)
			{
				InvokerPtr InvPtr = m_ServicePtrVec[i]->FetchInvoker();
				if (InvPtr)
				{
					if (m_InvokerPtrSet.insert(InvPtr).second)
					{
						m_nInvokeMonitor_JoinCount++;
					}
					else
					{
						VerifyEx(false,"");
					}
				}
				else
				{
					break;
				}
			}
		}
	__LEAVE_FUNCTION
}

void ServiceManager::UpdateAllInvoker(int nElapse)
{
	__ENTER_FUNCTION
		AssertEx(m_CPUPoolPtr,"");
	    for (InvokerPtrSet::iterator it =m_InvokerPtrSet.begin();it != m_InvokerPtrSet.end();)
	    {
			const int nState = (*it)->GetState();
			switch (nState)
			{
			case Invoker::STATE_READY:
				{
					const int nRunState = (*it)->GetRunState();
					switch (nRunState)
					{
					case BaseService::RUNSTATE_NORMAL:
					case BaseService::RUNSTATE_SLOWLY:
						{
							(*it)->UpdateDoingInterval(nElapse);
							bool bOverTime = ((nRunState== BaseService::RUNSTATE_NORMAL) ?
								((*it)->IsOverNormalDoingInterval()):(*it)->IsOverSlowlyDoingInterval());
							if (bOverTime)
							{
								(*it)->SetState(Invoker::STATE_SCHEDULING);
								m_CPUPoolPtr->schedule(boost::bind(&Invoker::Invoke,*it));
								m_nInvokeMonitor_ScheduleCount++;
							}
						}
						break;
					case BaseService::RUNSTATE_PAUSE:
						{

						}
						break;
					default:
						{
							VerifyEx(false,"");
						}
						break;
					}
					it++;
				}
				break;
			case Invoker::STATE_SCHEDULING:
				{
					(*it)->CheckScheduleState(nElapse);
					it++;
				}
				break;
			case Invoker::STATE_RUNNING:
				{
					(*it)->CheckRunState(nElapse);
				}
				break;
			default:
				{
					VerifyEx(false,"");
				}
				break;
			}
	    }

	__LEAVE_FUNCTION
}

void ServiceManager::UpdateInvokeMonitor(int nElapse)
{
	__ENTER_FUNCTION
		m_nInvokeMonitor_Time += nElapse;
	    if (m_nInvokeMonitor_Time >= 1000)
		{
			m_nInvokeMonitor_Time = 0;
			m_nInvokeMonitor_JoinCount = 0;
			m_nInvokeMonitor_ScheduleCount = 0;
		}
	__LEAVE_FUNCTION
}