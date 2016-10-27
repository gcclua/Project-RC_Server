#ifndef _SCRIPT_DEFINE_H_
#define _SCRIPT_DEFINE_H_

#include "Base.h"

/*----------------------------------------------------------------------
C接口编码注意事项：
	1.函数按int (*f)(lua_State *L)形式声明
	2.函数名与注册名一致
	3.使用__BEGIN_LUA和__END_LUA
	4.使用AssertEx(L, "")验证lua_State
	5.对每一个参数分别使用AssertLuaNumberParam或AssertLuaStringParam进行验证
	6.使用合适的BEGIN_X_DEFINE和END_X_DEFINE
	7.保持栈平衡，尤其是各个返回处，任何一个return x之前必须保证有x个返回值被压入栈中\
	8.认真为每个函数添加注释
*/

/*----------------------------------------------------------------------
Lua脚本编码注意事项：
	1.服务器脚本中的变量和函数，使用x+脚本号+_+名称的方式命名
	2.添、扣等操作一定要判断返回值，保证先删后给
	3.保持栈平衡，接受参数需要与函数的返回参数一致
	4.函数内部变量一定要加上local
*/

#define __BEGIN_LUA	__ENTER_PROTECT
#define __END_LUA	__LEAVE_PROTECT

#define AssertLuaNumberParam(luastate, index) \
{ \
	AssertEx(lua_gettop(luastate) >= index, ""); \
	AssertEx(lua_isnumber(luastate, index), ""); \
}

#define AssertLuaStringParam(luastate, index) \
{ \
	AssertEx(lua_gettop(luastate) >= index, ""); \
	AssertEx(lua_isstring(luastate, index), ""); \
}

/*----------------------------------------------------------------------
需求
	lua_State *L
产生
	Scene &rScene
*/
#define __BEGIN_SCENE_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene;
#define __END_SCENE_DEFINE \
}

/*----------------------------------------------------------------------
需求
	lua_State *L
	int _nObjID
产生
	Scene &rScene
	Obj &rObj
*/
#define __BEGIN_OBJ_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene; \
	ObjPtr _Ptr = rScene.GetObjByID(_nObjID); \
	if (_Ptr) \
	{ \
		Obj &rObj = *_Ptr;
#define __END_OBJ_DEFINE \
	} \
}

/*----------------------------------------------------------------------
需求
	lua_State *L
	int _nCharacterID
产生
	Scene &rScene
	Obj_Character &rCharacter
*/
#define __BEGIN_CHARACTER_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene; \
	Obj_CharacterPtr _Ptr = rScene.GetCharacterByID(_nCharacterID); \
	if (_Ptr) \
	{ \
		Obj_Character &rCharacter = *_Ptr;
#define __END_CHARACTER_DEFINE \
	} \
}

/*----------------------------------------------------------------------
需求
	lua_State *L
	int _nUserID
产生
	Scene &rScene
	Obj_User &rUser
*/
#define __BEGIN_USER_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene; \
	Obj_UserPtr _Ptr = rScene.GetUserByID(_nUserID); \
	if (_Ptr) \
	{ \
		Obj_User &rUser = *_Ptr;
#define __END_USER_DEFINE \
	} \
}

/*----------------------------------------------------------------------
需求
	lua_State *L
	int _nNpcID
产生
	Scene &rScene
	Obj_Npc &rNpc
*/
#define __BEGIN_NPC_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene; \
	Obj_NpcPtr _Ptr = rScene.GetNpcByID(_nNpcID); \
	if (_Ptr) \
	{ \
		Obj_Npc &rNpc = *_Ptr;
#define __END_NPC_DEFINE \
	} \
}

/*----------------------------------------------------------------------
需求
	lua_State *L
	int _nZombieUserID
产生
	Scene &rScene
	Obj_ZombieUser &rZombieUser
*/
#define __BEGIN_ZOMBIEUSER_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene; \
	Obj_ZombieUserPtr _Ptr = rScene.GetZombieUserByID(_nZombieUserID); \
	if (_Ptr) \
	{ \
		Obj_ZombieUser &rZombieUser = *_Ptr;
#define __END_ZOMBIEUSER_DEFINE \
	} \
}
/*----------------------------------------------------------------------
需求
	lua_State *L
	int _nFellowID
产生
	Scene &rScene
	Obj_Fellow &rFellow
*/
#define __BEGIN_FELLOW_DEFINE \
{ \
	void *_p = lua_gethostenv(L); \
	Scene *_pScene = static_cast<Scene *>(_p); \
	AssertEx(_pScene, ""); \
	Scene &rScene = *_pScene; \
	Obj_FellowPtr _Ptr = rScene.GetFellowByID(_nFellowID); \
	if (_Ptr) \
	{ \
		Obj_Fellow &rFellow = *_Ptr;
#define __END__FELLOW_DEFINE \
	} \
}
#endif
