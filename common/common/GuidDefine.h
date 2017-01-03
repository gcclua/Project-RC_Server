#ifndef _GUIDDEFINE_H_
#define _GUIDDEFINE_H_

#include "Base.h"
#include "GuidGenerator.h"

class GuidType
{
public:
	enum CONSTANT_VALUE
	{
		CHAR		= 0,	// ��ɫ
		CITY        = 1,    // ����
		BUILDING	= 2,	// ����
		HERO        = 3,    // Ӣ��
		MARCH       = 4,    // March
		TROOP       = 5,    // ����

		MAX				//����
	};
};


GUIDDEF_DECL(Char);
GUIDDEF_DECL(City);
GUIDDEF_DECL(Building);
GUIDDEF_DECL(Hero);
GUIDDEF_DECL(March);
GUIDDEF_DECL(Troop);
void InitGuidModule();

#endif