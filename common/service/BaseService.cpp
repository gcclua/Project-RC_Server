#include "BaseService.h"

BaseService::BaseService(void)
{

}

BaseService::~BaseService(void)
{

}

void BaseService::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		HandleAllMessage();

	__LEAVE_FUNCTION
}

void BaseService::ReceiveMessage(ConstMessagePtr ConstPtr)
{
	__ENTER_FUNCTION

		m_ConstMessagePtrTsList.push_back(ConstPtr);

	__LEAVE_FUNCTION
}

bool BaseService::IsHaveUnHandleMessage(void)
{
	__ENTER_FUNCTION

		return (!m_ConstMessagePtrTsList.empty());

	__LEAVE_FUNCTION
		return false;
}

void BaseService::HandleAllMessage(void)
{
	__ENTER_FUNCTION

		while (!m_ConstMessagePtrTsList.empty())
		{
			ConstMessagePtr csp = m_ConstMessagePtrTsList.pop_front();
			if (csp)
			{
				csp->ReflectHandle(*this);
			}
		}

	__LEAVE_FUNCTION
}