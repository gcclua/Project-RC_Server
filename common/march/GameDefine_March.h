
#ifndef _GAMEDEFINE_MARCH_H_
#define _GAMEDEFINE_MARCH_H_

#include "Base.h"

#define  MAX_MARCH_TROOPCOUNT 100

//ӵ�л���������
#define MARCH_MAX_COUNT 4

enum MARCHSTATUS
{
	MARCHSTATUS_INVALID = invalid_id,//δ����״̬
	MARCHSTATUS_IDLE = 1,// ����״̬
	MARCHSTATUS_READY,   // ׼������
	MARCHSTATUS_PROCESS =10, //�н�����ͣ��״̬
	MARCHSTATUS_STATION , // פ��״̬
	MARCHSTATUS_DEFENCE,     // ����״̬
	MARCHSTATUS_FIGHT,       // ս��״̬
	MARCHSTATUS_OVER ,       // ����״̬
	MARCHSTATUS_COLLECT,      // �ɼ���Դ

	MARCHSTATUS_MAX,
};

enum MARCHFORCE  // ս�����������������Ƿ��ط�
{
	MARCHFORCE_ATTACK = 0,
	MARCHFORCE_DEFENCE,
};

#endif