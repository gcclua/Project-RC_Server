
#ifndef _GAMEDEFINE_MARCH_H_
#define _GAMEDEFINE_MARCH_H_

#include "Base.h"

#define  MAX_MARCH_TROOPCOUNT 100

enum MARCHSTATUS
{
	MARCHSTATUS_PROCESS = 0, //�н�����ͣ��״̬
	MARCHSTATUS_STATION = 1, // פ��״̬
	MARCHSTATUS_DEFENCE,     // ����״̬
	MARCHSTATUS_FIGHT,       // ս��״̬
	MARCHSTATUS_OVER ,       // ����״̬
	MARCHSTATUS_COLLECT,      // �ɼ���Դ
};



#endif