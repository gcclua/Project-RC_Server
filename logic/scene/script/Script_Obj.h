#ifndef _SCRIPT_OBJ_H_
#define _SCRIPT_OBJ_H_

#include "Base.h"

struct lua_State;

int C_GetScenePos(lua_State *L);
int C_ForceSetScenePos(lua_State *L);
int C_ForceSetFellowScenePos(lua_State *L);
int C_AuditLog_KillVillainBoss(lua_State *L);
int C_KillBossRewardItem(lua_State *L);

#endif
