#include "Service.h"

Service::Service(void)
{

}

Service::~Service(void)
{

}

int Service::GetRunState(void)
{
	return GetRunState_General();
}

int Service::GetRunState_General(void)
{
	switch (m_nStatus)
	{
	case ServiceStatus::EMPTY:
			{
				AssertEx(false,"");
				return BaseService::RUNSTATE_PAUSE;
			}
		break;
	case ServiceStatus::OPENUP:
	case ServiceStatus::OPENUP_PROCESS:
	case ServiceStatus::RUNNING:
	case ServiceStatus::SHUTDOWN:
	case ServiceStatus::SHUTDOWN_PROCESS:
	case ServiceStatus::FINALSAVE:
	case ServiceStatus::FINALSAVE_PROCESS:
			{
				return BaseService::RUNSTATE_NORMAL;
			}
			break;
	case ServiceStatus::OPENUP_OK:
	case ServiceStatus::SHUTDOWN_OK:
	case ServiceStatus::FINALSAVE_OK:
		{
			return BaseService::RUNSTATE_PAUSE;
		}
		break;
	default:
		{
			AssertEx(false,"");
			return BaseService::RUNSTATE_PAUSE;
		}
	}
}

int Service::GetRunState_Base(void)
{
	switch (m_nStatus)
	{
	case ServiceStatus::EMPTY:
		{
			AssertEx(false,"");
			return BaseService::RUNSTATE_PAUSE;
		}
	break;
	case ServiceStatus::OPENUP:
	case ServiceStatus::OPENUP_PROCESS:
	case ServiceStatus::RUNNING:
	case ServiceStatus::SHUTDOWN:
	case ServiceStatus::SHUTDOWN_PROCESS:
	case ServiceStatus::FINALSAVE:
	case ServiceStatus::FINALSAVE_PROCESS:
	case ServiceStatus::OPENUP_OK:
	case ServiceStatus::SHUTDOWN_OK:
	case ServiceStatus::FINALSAVE_OK:
		{
			return BaseService::RUNSTATE_NORMAL;
		}
		break;
	default:
		{
			AssertEx(false,"");
			return BaseService::RUNSTATE_PAUSE;
		}
		break;
	}
}

void Service::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		BaseService::Tick(rTimeInfo);
	    Tick_Status(rTimeInfo);
	__LEAVE_FUNCTION
}

void Service::Openup(void)
{
	__ENTER_FUNCTION

		OpenupOk();

	__LEAVE_FUNCTION

}

void Service::Shutdown(void)
{
	__ENTER_FUNCTION

		ShutdownOk();

	__LEAVE_FUNCTION

}

void Service::Finalsave(void)
{
	__ENTER_FUNCTION

		FinalsaveOk();

	__LEAVE_FUNCTION

}

void Service::OpenupOk(void)
{
	__ENTER_FUNCTION

		m_nStatus = ServiceStatus::OPENUP_OK;
		

	__LEAVE_FUNCTION
}

void Service::ShutdownOk()
{
	__ENTER_FUNCTION

		m_nStatus = ServiceStatus::SHUTDOWN_OK;


	__LEAVE_FUNCTION
}

void Service::FinalsaveOk()
{
	__ENTER_FUNCTION

		m_nStatus = ServiceStatus::FINALSAVE_OK;


	__LEAVE_FUNCTION
}

void Service::Tick_Status(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (m_nStatus == ServiceStatus::OPENUP)
		{
			m_nStatus = ServiceStatus::OPENUP_PROCESS;
			Openup();
		}
		else if (m_nStatus == ServiceStatus::RUNNING)
		{
			if (m_bCanCallOnStartRuning)
			{
				m_bCanCallOnStartRuning = false;
				OnStartRunning();
			}
		}
		else if (m_nStatus == ServiceStatus::SHUTDOWN)
		{
			m_nStatus = ServiceStatus::SHUTDOWN_PROCESS;
			Shutdown();
		}
		else if (m_nStatus == ServiceStatus::FINALSAVE)
		{
			m_nStatus = ServiceStatus::FINALSAVE_PROCESS;
			Finalsave();
		}
	__LEAVE_FUNCTION
}

InvokerPtr Service::FetchInvoker(void)
{
	__ENTER_FUNCTION
	InvokerPtr Ptr;
	if (!m_InvokerPtrTSList.empty())
	{
		Ptr = m_InvokerPtrTSList.pop_front();
	}
	return Ptr;
	__LEAVE_FUNCTION
	InvokerPtr RetPtr;
	return RetPtr;
}

void Service::AddInvoker( const InvokerPtr Ptr )
{
	__ENTER_FUNCTION

		m_InvokerPtrTSList.push_back(Ptr);

	__LEAVE_FUNCTION
}