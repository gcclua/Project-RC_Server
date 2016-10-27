#ifndef _SCRIPT_CHARACTER_H_
#define _SCRIPT_CHARACTER_H_

#include "Base.h"

struct lua_State;

int C_GetCurHp(lua_State *L);
int C_GetMaxHp(lua_State *L);
int C_IncreaseHp(lua_State *L);
int C_ForceKill(lua_State *L);
int C_ForceDecHp(lua_State *L);
int C_GetRandomNearUserObjID(lua_State *L);
int C_IsHaveImpact(lua_State *L);
int C_SendImpactToUnit(lua_State *L);
int C_RemoveImpactByID(lua_State *L);
int C_IsActive(lua_State *L);
int C_MoveTo(lua_State *L);
int C_FullHpAndMp(lua_State *L);
int C_GetSceneClassId(lua_State *L);
int C_GetCharCombatAttrValue(lua_State *L);
int C_GetCharMP(lua_State *L);
int C_IncCharMP(lua_State *L);

int C_SwithAIToFollow(lua_State *L);
int C_ChangeCurSelectObjId(lua_State *L);
int C_SetNpcForce(lua_State *L);
int C_SetNpcLifeTime(lua_State *L);

#endif
