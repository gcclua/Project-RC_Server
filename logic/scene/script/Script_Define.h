#ifndef _SCRIPT_DEFINE_H_
#define _SCRIPT_DEFINE_H_

#include "Base.h"

/*----------------------------------------------------------------------
C�ӿڱ���ע�����
	1.������int (*f)(lua_State *L)��ʽ����
	2.��������ע����һ��
	3.ʹ��__BEGIN_LUA��__END_LUA
	4.ʹ��AssertEx(L, "")��֤lua_State
	5.��ÿһ�������ֱ�ʹ��AssertLuaNumberParam��AssertLuaStringParam������֤
	6.ʹ�ú��ʵ�BEGIN_X_DEFINE��END_X_DEFINE
	7.����ջƽ�⣬�����Ǹ������ش����κ�һ��return x֮ǰ���뱣֤��x������ֵ��ѹ��ջ��\
	8.����Ϊÿ���������ע��
*/

/*----------------------------------------------------------------------
Lua�ű�����ע�����
	1.�������ű��еı����ͺ�����ʹ��x+�ű���+_+���Ƶķ�ʽ����
	2.���۵Ȳ���һ��Ҫ�жϷ���ֵ����֤��ɾ���
	3.����ջƽ�⣬���ܲ�����Ҫ�뺯���ķ��ز���һ��
	4.�����ڲ�����һ��Ҫ����local
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
����
	lua_State *L
����
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
����
	lua_State *L
	int _nObjID
����
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
����
	lua_State *L
	int _nCharacterID
����
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
����
	lua_State *L
	int _nUserID
����
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
����
	lua_State *L
	int _nNpcID
����
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
����
	lua_State *L
	int _nZombieUserID
����
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
����
	lua_State *L
	int _nFellowID
����
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
