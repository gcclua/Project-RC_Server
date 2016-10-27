#include "ServiceCell.h"

ServiceCell::ServiceCell(void)
{

}

ServiceCell::~ServiceCell(void)
{

}

void ServiceCell::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		BaseService::Tick(rTimeInfo);

	__LEAVE_FUNCTION
}

InvokerPtr ServiceCell::Init(void)
{
	__ENTER_FUNCTION

		AssertEx(false, "");

	__LEAVE_FUNCTION
		return InvokerPtr();
}
