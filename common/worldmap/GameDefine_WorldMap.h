
#ifndef _GAMEDEFINE_WORLDMAP_H_
#define _GAMEDEFINE_WORLDMAP_H_

#include "Base.h"

//���ĵؿ���
#define  MAX_TILE_NUM 10000

// �ؿ�����
enum TILE_TYPE
{
	TILE_TYPE_INVALID = 0,
	TILE_TYPE_CITY = 1, //���еؿ�
	TILE_TYPE_PLAIN, // ƽԭ
	TILE_TYPE_SOURCE, // ��Դ
	TILE_TYPE_WILD,    // Ұ��
};

#endif