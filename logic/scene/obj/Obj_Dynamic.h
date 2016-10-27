#ifndef _OBJ_DYNAMIC_H_
#define _OBJ_DYNAMIC_H_

#include "Obj.h"

class Obj_Dynamic : public Obj
{
public:
	Obj_Dynamic(void);
	virtual ~Obj_Dynamic(void);

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);
};

#endif
