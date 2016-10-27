#include "Obj_Hero.h"
#include "Table/Table_CoolDownTime.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Scene/Scene/Scene.h"
#include "DictionaryFormat/DictionaryFormat.h"

POOLDEF_IMPL(Obj_Hero);

Obj_Hero::Obj_Hero( void )
{
	

}

Obj_Hero::~Obj_Hero( void )
{

}

void Obj_Hero::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Npc::OnEnterScene();

	__LEAVE_FUNCTION
}

void Obj_Hero::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Npc::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Hero::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

	Obj_Npc::Tick(rTimeInfo);

	__LEAVE_PROTECT
}

