#ifndef _OBJ_ACTION_H_
#define _OBJ_ACTION_H_

#include "Obj_Dynamic.h"

class Obj_Action : public Obj_Dynamic
{
public:
	Obj_Action(void);
	virtual ~Obj_Action(void);

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);
};

#endif
