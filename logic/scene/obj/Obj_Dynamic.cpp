#include "Obj_Dynamic.h"

Obj_Dynamic::Obj_Dynamic( void )
{

}

Obj_Dynamic::~Obj_Dynamic( void )
{

}

void Obj_Dynamic::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj::OnEnterScene();

	__LEAVE_FUNCTION
}

void Obj_Dynamic::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Dynamic::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Obj::Tick(rTimeInfo);

	__LEAVE_FUNCTION
}
