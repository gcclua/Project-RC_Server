////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：9:18 2014-03-03
//             说明：冷却列表数据存储
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBSTRUCTCOOLDOWN_H__
#define __DBSTRUCTCOOLDOWN_H__

#include "Base.h"
struct DBCoolDown_Info
{
public:
	DBCoolDown_Info(){CleanUp();}
	void				CleanUp();
	void				CopyFrom(const DBCoolDown_Info& rSour);
public:
	int16 m_nID;//冷却ID
	int m_nCDTimeElapsed;//冷却流逝时间 毫秒
};
#endif