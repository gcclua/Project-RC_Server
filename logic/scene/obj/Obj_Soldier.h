#ifndef _OBJ_SOLIDER_H_
#define _OBJ_SOLIDER_H_

#include "Obj_Character.h"
#include "Table/Table_NpcSkillStrategy.h"
#include "Table/Table_NpcOptionalSkill.h"
#include "Obj_Npc.h"


class Obj_Solider : public Obj_Npc
{
public:
	Obj_Solider(void);
	virtual ~Obj_Solider(void);

public:
	virtual int GetObjType(void) const {return ObjType::SOLDIER;}

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

	virtual bool CanBeView(Obj_Character &rObj);

};

POOLDEF_DECL(Obj_Solider);

typedef GeneralObjRefCont<Obj_Solider, 256> SoliderRefCont;


#endif
