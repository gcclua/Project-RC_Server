#ifndef __PROCESSWORLDEVENT_H__
#define __PROCESSWORLDEVENT_H__
#include "../GameEventHandler.h"
#include "../../event/EventDefine.h"


class ProcessWorldEvent
{
public:
	ProcessWorldEvent()
	{
		logger_ = log4cxx::Logger::getLogger("EventHelper");
	}
	~ProcessWorldEvent() {}

	static void createInstance(GameEventHandler* eh_)
	{
		getInstance()->eh_ = eh_;
		eh_->getEventHandler()->registHandler(EVENT_USER_BRAODCAST, ((ProcessRoutine)ProcessWorldEvent::handle_));
		eh_->getEventHandler()->registHandler(EVENT_WEB_BROADCAST, ((ProcessRoutine)ProcessWorldEvent::handle_));
	}

	static ProcessWorldEvent* getInstance()
	{
		static ProcessWorldEvent instance_;
		return &instance_;
	}

	static void handle_(Event* e)
	{
		ProcessWorldEvent::getInstance()->handle(e);
	}


private:
	void handle(Event* e);
	GameEventHandler* eh_;
	log4cxx::LoggerPtr logger_;
protected:
	void processBroadcastMsg(Event* e);
	void processWebBroadMsg(Event* e);
};




#endif
