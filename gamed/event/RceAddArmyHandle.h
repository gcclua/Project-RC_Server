#ifndef _RCEADDARMYHANDLE_H_
#define _RCEADDARMYHANDLE_H_
#pragma once
//���ļ���.cpp�ļ�Ϊʹ�ù��ߴ����������ļ����޸ģ�����������ָ��ļ������������´�����
#include "BaseEvent.h"
class RceAddArmyHandle : public CBaseEvent
{
public:
	RceAddArmyHandle();
	~RceAddArmyHandle();
	RegistEvent(RceAddArmyHandle,C2S_RceAddArmy)

private:
	void handle(Event* e);
};
#endif

