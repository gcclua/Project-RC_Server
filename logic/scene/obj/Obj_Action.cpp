#include "Obj_Action.h"

Obj_Action::Obj_Action( void )
{

}

Obj_Action::~Obj_Action( void )
{

}

void Obj_Action::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Dynamic::OnEnterScene();

	__LEAVE_FUNCTION
}

void Obj_Action::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Dynamic::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Action::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Obj_Dynamic::Tick(rTimeInfo);

	__LEAVE_FUNCTION
}
