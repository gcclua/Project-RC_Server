#ifndef _BASEEVENT_H_
#define _BASEEVENT_H_
#pragma once
#include "../../event/EventDefine.h"
#include "MessageDef.h"

#define RegistEvent(className,event_id) \
static void createInstance(GameEventHandler* eh) \
{ \
	className* instance_ = getInstance(); \
	instance_->eh_ = eh; \
	eh->getEventHandler()->registHandler(event_id,((ProcessRoutine)className::handle_));\
}\
static className* getInstance()\
{\
	static className ins;\
	return &ins;\
}\
static void handle_(Event* e)\
{\
	className::getInstance()->handle(e);\
}

class CBaseEvent {
public:
	CBaseEvent()
	{
		
	}

	virtual ~CBaseEvent() {}	

protected:
	virtual void handle(Event* e) = 0;
protected:
	static CBaseEvent* instance_;
};

#endif
