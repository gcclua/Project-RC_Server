
#ifndef _GAMEDEFINE_TROOP_H_
#define _GAMEDEFINE_TROOP_H_

#include "Base.h"

enum TROOPTYPE
{
	TROOPTYPE_INVILID = 0,
	TROOPTYPE_INFANTRY = 1,    // ����
	TROOPTYPE_HEAVYSHIELD,     // �ضܲ���
	TROOPTYPE_CAVALRY,         // ���
	TROOPTYPE_ARCHER,          // ������
	TROOPTYPE_ARTILLERY,       // ����

	TROOPTYPE_MAX,             // ��������
};

// ��������λ��
#define  TROOP_ARRANGE_MAX_POSITION 9 

// ���Ķ�����
#define  TROOP_QUEUE_MAX_COUNT 5

// ÿ�ӱ����������
#define  TROOP_QUEUE_MAX_SIGCOUNT 18

#define TROOP_OWNSKILL 6

typedef IDContainer_T<TROOP_OWNSKILL> TroopOwnSkillList;

typedef std::map<int64,int64> BarrackMarchMap;

#endif