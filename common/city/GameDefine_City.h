
#ifndef _GAMEDEFINE_CITY_H_
#define _GAMEDEFINE_CITY_H_

#include "Base.h"
#include "building/GameDefine_Building.h"
#include "troop/GameDefine_Troop.h"
// �����о�������
#define MAX_CITY_RESEARCH_COUNT 2
// ���Ľ��������
#define MAX_CITY_CONSTRUCT_COUNT 2

// ���ı��Ķ�����
#define MAX_TROOP_QUEUE          ((BUILDING_BARRACK_MAX+BUILDING_WALL_MAX)*TROOP_QUEUE_MAX_COUNT)     

// ���еػ�����
enum CITY_SLOT
{
	CITY_SLOT_INNERBIG = 1,     //���ڴ�
	CITY_SLOT_INNERMIDDLE,  //������
	CITY_SLOT_INNERSMALL,   //����С

	CITY_SLOT_OUTERBIG,     //�����
	CITY_SLOT_OUTERMIDDLE,  //������
	CITY_SLOT_OUTERSMALL,   //����С
};

enum SOURCETYPE
{
	SOURCETYPE_FOOD = 1,       // ʳ��
	SOURCETYPE_STONE,          // ʯ��
	SOURCETYPE_IRON,           // ����
	SOURCETYPE_GOLD,           // ���
};

enum TECHNOLOGYTYPE
{
	TECHNOLOGYTYPE_MIN = 0,
	TECHNOLOGYTYPE_FOOD = TECHNOLOGYTYPE_MIN,  // ������ʳ���ٶ�
	TECHNOLOGYTYPE_STONE, // ����ʯ�ϵ��ٶ�
	TECHNOLOGYTYPE_IRON,  // ����������ٶ�
	TECHNOLOGYTYPE_TRAIN, // ѵ�����ٶ�

	TECHNOLOGYTYPE_MAX,   // ���ĿƼ���
};


#endif