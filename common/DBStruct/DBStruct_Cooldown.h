////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺9:18 2014-03-03
//             ˵������ȴ�б����ݴ洢
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
	int16 m_nID;//��ȴID
	int m_nCDTimeElapsed;//��ȴ����ʱ�� ����
};
#endif