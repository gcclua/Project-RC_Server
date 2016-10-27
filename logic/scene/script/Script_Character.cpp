#include "Script_Character.h"
#include "Script_Define.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Obj/Obj_Character.h"

/*----------------------------------------------------------------------
功能说明：获取当前血量
参数个数：1
参数说明：
	1.character objID
返回值个数：1
返回值说明：
	1、当前血量
注意事项：
	见Script_Define.h
*/
int C_GetCurHp(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_CHARACTER_DEFINE

		lua_pushnumber(L, rCharacter.GetCurHp());
		return 1;

	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取最大血量
参数个数：1
参数说明：
	1.character objID
返回值个数：1
返回值说明：
	1、最大血量
注意事项：
	见Script_Define.h
*/
int C_GetMaxHp(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_CHARACTER_DEFINE

		int nMaxHP = rCharacter.GetCombatAttrByID((int)(COMBATATTR_T::MAXHP));
		lua_pushnumber(L, nMaxHP);
		return 1;

	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：增加Character血量
参数个数：3
参数说明：
	1.objID
	2.增加的血量
返回值个数：1
返回值说明：
	1.当前血量
注意事项：
	见Script_Define.h
*/
int C_IncreaseHp(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int nIncValue = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_CHARACTER_DEFINE

		lua_pushnumber(L, rCharacter.IncreaseHp(nIncValue, rCharacter));
	return 1;

	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：强制杀死
参数个数：2
参数说明：
	1.objID
	2.killerID
返回值个数：1
返回值说明：
	
注意事项：
	见Script_Define.h
*/
int C_ForceKill(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int _KillerID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_CHARACTER_DEFINE

		Obj_CharacterPtr killerPtr = rScene.GetCharacterByID(_KillerID);
		if( killerPtr )
		{
			int nCurHP = rCharacter.GetCurHp();
			rCharacter.IncreaseHp(0-nCurHP, *killerPtr);
		}

	__END_CHARACTER_DEFINE
		__END_LUA

	return 0;
}
/*----------------------------------------------------------------------
功能说明：强制掉血
参数个数：3
参数说明：
	1.objID
	2.killerID
	3.百分比
返回值个数：0
返回值说明：
	
注意事项：
	见Script_Define.h
*/
int C_ForceDecHp(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int _KillerID = static_cast<int>(lua_tonumber(L, 2));
	float fPercent = static_cast<float>(lua_tonumber(L, 3));


	__BEGIN_CHARACTER_DEFINE

		Obj_CharacterPtr killerPtr = rScene.GetCharacterByID(_KillerID);
		if( killerPtr )
		{
			int nCurHP = (int)(rCharacter.GetCurHp() * fPercent);
			rCharacter.IncreaseHp(0-nCurHP, *killerPtr);
		}

	__END_CHARACTER_DEFINE
		__END_LUA

	return 0;
}
/*----------------------------------------------------------------------
功能说明：获取Character附近随机玩家ObjID
参数个数：3
参数说明：
	1.objID
	2.范围半径
返回值个数：1
返回值说明：
	1.ObjID
注意事项：
	见Script_Define.h
*/
int C_GetRandomNearUserObjID(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	float fRadius = static_cast<float>(lua_tonumber(L, 2));

	__BEGIN_CHARACTER_DEFINE
		UserRefCont Cont;
		rScene.Scan_User_Circle(Cont, rCharacter.GetScenePos(), fRadius);

		// 最多4次吧
		for (int i = 0; i < 4; i++)
		{
			int nRandom = Random::Gen(0,Cont.Size());
			if (nRandom >= 0 && nRandom < Cont.Size())
			{
				if (Cont[nRandom].IsAlive())
				{
					lua_pushnumber(L, Cont[nRandom].GetID());
					return 1;
				}
			}
		}

		lua_pushnumber(L, -1);
		return 1;
	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, -1);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：是否有buff
参数个数：3
参数说明：
	1.objID
	2.buffID
返回值个数：1
返回值说明：
	1.是否
注意事项：
	见Script_Define.h
*/
int C_IsHaveImpact(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int nBufferID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_CHARACTER_DEFINE

		lua_pushnumber(L, rCharacter.IsHaveImpact(nBufferID));
		return 1;

	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：添加buff
参数个数：3
参数说明：
	1.SourceobjID
	2.TargetObjID
	2.buffID
	3.skillID(无技能，直接-1)
返回值个数：1
返回值说明：
	1.添加是否成功
注意事项：
	见Script_Define.h
*/
int C_SendImpactToUnit(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int nTargetObjID = static_cast<int>(lua_tonumber(L, 2));
	int nBufferID = static_cast<int>(lua_tonumber(L, 3));
	int nSkillID = static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_CHARACTER_DEFINE

		Obj_CharacterPtr TargetObjPtr = rScene.GetCharacterByID(nTargetObjID);
		if (TargetObjPtr && nBufferID !=invalid_id)
		{
			rCharacter.SendImpactToUnit(*TargetObjPtr, nBufferID, nSkillID);
			lua_pushnumber(L, 1);
			return 1;
		}

		lua_pushnumber(L, 0);
		return 1;

	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：移除某个buff
参数个数：2
参数说明：
	1.objID
	2.buffID
返回值个数：1
返回值说明：
	1.添加是否成功
注意事项：
	见Script_Define.h
*/
int C_RemoveImpactByID(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int nBufferID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_CHARACTER_DEFINE

		bool bRet = rCharacter.RemoveImpactById(nBufferID);

		lua_pushnumber(L, static_cast<int>(bRet));
		return 1;

	__END_CHARACTER_DEFINE
		__END_LUA

		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：Character是否活着
参数个数：1
参数说明：
	1.objID
返回值个数：1
返回值说明：
	1.是or否
注意事项：
	见Script_Define.h
*/
int C_IsActive(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_CHARACTER_DEFINE
			if (rCharacter.GetActive() && rCharacter.IsAlive())
			{
				lua_pushnumber(L, 1);
				return 1;
			}
		__END_CHARACTER_DEFINE
	__END_LUA
		lua_pushnumber(L, 0);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：Character走到某个点
参数个数：4
参数说明：
	1.objID
	2.fPosX
	3.fPosY
	4.fStopRange
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_MoveTo(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosY = static_cast<float>(lua_tonumber(L, 3));
	float fStopRange = static_cast<float>(lua_tonumber(L, 4));

	__BEGIN_CHARACTER_DEFINE

		rCharacter.MoveTo(ScenePos(fPosX, fPosY), fStopRange);
	return 0;

	__END_CHARACTER_DEFINE
		__END_LUA

	return 1;
}


/*----------------------------------------------------------------------
功能说明：满血满蓝
参数个数：1
参数说明：
	1.objID
返回值个数：1
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_FullHpAndMp(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_CHARACTER_DEFINE
			int nMaxHP =rCharacter.GetCombatAttrByID((int)(COMBATATTR_T::MAXHP));
			int nMaxMP =rCharacter.GetCombatAttrByID((int)(COMBATATTR_T::MAXMP));
			rCharacter.IncreaseHp(nMaxHP,rCharacter);
			rCharacter.IncreaseMp(nMaxMP);
			return 0;
		__END_CHARACTER_DEFINE
	__END_LUA
		return 0;
}

/*----------------------------------------------------------------------
功能说明：获取所在场景的场景ID
参数个数：1
参数说明：
	1.objID
返回值个数：1
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_GetSceneClassId(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_CHARACTER_DEFINE
			lua_pushnumber(L, rScene.GetSceneClassID());
			return 1;
		__END_CHARACTER_DEFINE
	__END_LUA
		lua_pushnumber(L, -1);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：获取Character的某个战斗属性值
参数个数：2
参数说明：
	1._nCharacterID
	2._nAttrId 必须是COMBATATTR_T::TYPE枚举
返回值个数：1 战斗属性值
注意事项：
	见Script_Define.h
*/
int C_GetCharCombatAttrValue(lua_State *L)
{
__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int _nAttrId = static_cast<int>(lua_tonumber(L, 2));

	if ( _nAttrId < COMBATATTR_T::MAXHP || _nAttrId >= COMBATATTR_T::COMBATATTR_MAXNUM )
	{
		lua_pushnumber(L, 0);
		return 1;
	}

	__BEGIN_CHARACTER_DEFINE

	int nAttrValue = rCharacter.GetCombatAttrByID(_nAttrId);
	lua_pushnumber(L, nAttrValue);
	return 1;

	__END_CHARACTER_DEFINE
__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取Obj_Character的当前蓝量
参数个数：1
参数说明：
	1.character objID _nCharacterID
返回值个数：1
返回值说明：
	1、当前蓝量
注意事项：
	见Script_Define.h
*/
int C_GetCharMP(lua_State *L)
{
__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_CHARACTER_DEFINE

		lua_pushnumber(L, rCharacter.GetCurMP());
		return 1;

	__END_CHARACTER_DEFINE
	
__END_LUA

		lua_pushnumber(L, 0);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：改变Character蓝量
参数个数：2
参数说明：
	1.objID
	2.增加或减少的蓝量 - 正数 加蓝,负数 减蓝
返回值个数：1
返回值说明：
	1.当前蓝量
注意事项：
	见Script_Define.h
*/
int C_IncCharMP(lua_State *L)
{
__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nCharacterID = static_cast<int>(lua_tonumber(L, 1));
	int nIncValue = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_CHARACTER_DEFINE

		lua_pushnumber(L, rCharacter.IncreaseMp(nIncValue));
		return 1;

	__END_CHARACTER_DEFINE
	
__END_LUA

		lua_pushnumber(L, 0);
		return 1;
}


/*----------------------------------------------------------------------
功能说明：切换NPC到跟随状态
参数个数：1
参数说明：
	1.npc的ObjID
	2.跟随目标的ObjId
返回值个数：1
返回值说明：1: 成功 || 0: 失败
注意事项：
	见Script_Define.h
*/
int C_SwithAIToFollow(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	//NPC的ObjId
	AssertLuaNumberParam(L, 1);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	//跟随目标(玩家)的ObjId
	AssertLuaNumberParam(L, 2);
	int targetID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_NPC_DEFINE

	rNpc.SetFollowTargetObjId(targetID);
	bool bRet = rNpc.SwitchAI(Obj_Npc::AI_FOLLOW);
	if (bRet)
	{
		lua_pushnumber(L, 1);
		return 1;
	}
	else
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	__END_NPC_DEFINE

	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：切换NPC目标
参数个数：2
参数说明：
	1.npc的ObjID
	2.目标ObjID
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_ChangeCurSelectObjId(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	int nTargetID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_NPC_DEFINE

	rNpc.ChangeCurSelectObjId(nTargetID);
	return 0;

	__END_NPC_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：切换NPC阵营
参数个数：2
参数说明：
	1.npc的ObjID
	2.force
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SetNpcForce(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	int forceType = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_NPC_DEFINE


		if(FORCETYPE_T::TYPE_INVAILD < forceType && forceType < FORCETYPE_T::MAX_NUM)
			rNpc.SetForceType( forceType );
	return 0;

	__END_NPC_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：设置npc生命时长 毫秒
参数个数：2
参数说明：
	1.npc的ObjID
	2.lifetime
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SetNpcLifeTime(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	int nLifeTime = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_NPC_DEFINE

	if (nLifeTime > 0)
	{
		rNpc.SetLifeTime(nLifeTime);
	}
	return 0;

	__END_NPC_DEFINE
	__END_LUA
	return 0;
}