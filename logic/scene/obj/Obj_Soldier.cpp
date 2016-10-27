#include "Obj_Soldier.h"
#include "Table/Table_CoolDownTime.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Scene/Scene/Scene.h"
#include "DictionaryFormat/DictionaryFormat.h"

POOLDEF_IMPL(Obj_Solider);

Obj_Solider::Obj_Solider( void )
{
	
}

Obj_Solider::~Obj_Solider( void )
{

}

void Obj_Solider::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Npc::OnEnterScene();

	__LEAVE_FUNCTION
}

void Obj_Solider::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Npc::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Solider::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

	Obj_Npc::Tick(rTimeInfo);
	//AIÐÄÌø


	__LEAVE_PROTECT
}

bool Obj_Solider::CanBeView(Obj_Character &rObj)
{
	return true;
}