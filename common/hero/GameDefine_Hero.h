
#ifndef _GAMEDEFINE_HERO_H_
#define _GAMEDEFINE_HERO_H_

#include "Base.h"

#define HERO_NAME_SIZE 32
typedef FLString<HERO_NAME_SIZE> HERONAME;

#define HERO_OWNSKILL 6

typedef IDContainer_T<HERO_OWNSKILL> HeroOwnSkillList;

enum HEROTYPE
{
	HEROTYPE_MIN,
	HEROTYPE_1,
	HEROTYPE_2,


	HEROTYPE_MAX,
};

enum HEROSTATUS
{
	HEROSTATUS_IDLE,// ¿ÕÏÐ×´Ì¬
	HEROSTATUS_ASSIGN, // ÈÎÃü×´Ì¬
	HEROSTATUS_FIGHT, // ³öÕ½×´Ì¬
};

#endif