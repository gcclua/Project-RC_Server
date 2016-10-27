#include "Script_User.h"
#include "Script_Define.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Obj/Obj_User.h"
#include "Packet/Packet/GC_RET_RELIVE_PAK.h"
#include "Packet/Packet/GC_UPDATENOTICEDATA_PAK.h"
#include "Packet/Packet/GC_PUSH_NOTIFICATION_PAK.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "TimeUtility.h"
/*----------------------------------------------------------------------
功能说明：服务器发送调试信息
参数个数：2
参数说明：
	1.UserObjID
	2.调试信息
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SendNoticeMsg(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	const char* strMsg = lua_tostring(L,2);

	__BEGIN_USER_DEFINE

	if (strMsg)
	{
		rUser.SendNotice(strMsg);
	}
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

int C_GetPlayerData(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	FLString<64> strData;
	strData = static_cast<const char*>(lua_tostring(L,2));

	__BEGIN_USER_DEFINE

	if (strData == "Profession")
	{
		lua_pushnumber(L, rUser.GetCurProfession());
		return 1;
	}
	else if (strData == "GuildGuid")
	{
		lua_pushnumber(L, rUser.GetGuildGuid().GetHigh32Value());
		lua_pushnumber(L, rUser.GetGuildGuid().GetLow32Value());
		return 2;
	}
	else if (strData == "Guid")
	{
		lua_pushnumber(L, rUser.GetGuid().GetHigh32Value());
		lua_pushnumber(L, rUser.GetGuid().GetLow32Value());
		return 2;
	}
	else if (strData == "Name")
	{
		lua_pushstring(L, rUser.GetName().GetCText());
		return 1;
	}
	lua_pushnumber(L, -1);
	return 1;
	__END_USER_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：设置玩家属性
参数个数：3
参数说明：
	1.UserObjID
	2.属性名称
	3.属性数值
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SetPlayerData(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	FLString<64> strData;
	strData = static_cast<const char*>(lua_tostring(L,2));
	int nValue = static_cast<int>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE
	if (strData == "XP")
	{
		rUser.IncreaseXp(nValue);
	}
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：传送单人副本
参数个数：2
参数说明：
	1.UserObjID
	2.副本SceneClassID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_OpenSingleCopyScene(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSceneClassID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	//rUser.OpenCopyScene(nSceneClassID, CopySceneDifficulty::DEFAULT,true);
	rUser.SendConfirmOpenMissionCopyScene(nSceneClassID, CopySceneDifficulty::DEFAULT);
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：学习技能
参数个数：2
参数说明：
	1.UserObjID
	2.nSkillId
	3.nSkillIndex
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_StudySkill(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSkillExId = static_cast<int>(lua_tonumber(L, 2));
	int nSkillIndex = static_cast<int>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE

		rUser.StudySkill(nSkillExId, false, nSkillIndex);
		return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：获取职业ID
参数个数：2
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetProfessionID(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	int nProfessionID = rUser.GetCurProfession();
	lua_pushnumber(L, nProfessionID);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：是否是队长
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_IsTeamLeader(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	bool isLeader = rUser.IsTeamLeader();
	lua_pushnumber(L, isLeader ? 1 : 0);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：是否是队长
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetTeamId(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	int teamId = rUser.GetTeamID();
	lua_pushnumber(L, teamId);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, invalid_id);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：是否是队长
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetIsPassiveFlag(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	bool passive = rUser.GetPassiveChallengeFlag();
	lua_pushnumber(L, passive ? 1 : 0);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：真气助战状态
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_ZhenQiZhuZhanState(lua_State* L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nState = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
	
		//rUser.RestZhenQiZhuZhanTimes( );
		//rUser.SendZhenQiState(nState);

	return 0;
	__END_USER_DEFINE
	__END_LUA
	return 0;
}


/*----------------------------------------------------------------------
功能说明：获取当前HP
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerCurHP(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	int nCurHP = rUser.GetCurHp();
	lua_pushnumber(L, nCurHP);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取当前MP
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerCurMP(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

		int nCurMP = rUser.GetCurMP();
	lua_pushnumber(L, nCurMP);
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取MaxHP
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerMaxHP(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

		int nMaxHP = rUser.GetCombatAttrByID(COMBATATTR_T::MAXHP);
	lua_pushnumber(L, nMaxHP);
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取obj的某个属性值
参数个数：2
参数说明：
	1.UserObjID
	2.属性枚举值
返回值个数：1
注意事项：
	见Script_Define.h
*/

int C_GetPlayerAttrValue(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int _nAttrId = static_cast<int>(lua_tonumber(L, 2));

	if ( _nAttrId < COMBATATTR_T::MAXHP || _nAttrId >= COMBATATTR_T::COMBATATTR_MAXNUM )
	{
		lua_pushnumber(L, 0);
		return 1;
	}

	__BEGIN_USER_DEFINE

		int nAttrValue = rUser.GetCombatAttrByID(_nAttrId);
	lua_pushnumber(L, nAttrValue);
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取Level
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerLevel(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

		int nLevel = rUser.GetLevel();
	lua_pushnumber(L, nLevel);
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：获取MaxMP
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerMaxMP(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

		int nMaxMP = rUser.GetCombatAttrByID(COMBATATTR_T::MAXMP);
	lua_pushnumber(L, nMaxMP);
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：设置当前HP
参数个数：2
参数说明：
	1.UserObjID
	2.hp
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SetPlayerCurHP(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nCurHP = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	rUser.SetCurHp( nCurHP );
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：设置当前MP
参数个数：2
参数说明：
	1.UserObjID
	2.Mp
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SetPlayerCurMP(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nCurMP = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	rUser.SetCurMp( nCurMP );
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：获得当前体力
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerStamina(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	int nStamina = rUser.GetStamina();
	lua_pushnumber(L, nStamina);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获得玩家名字
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetPlayerName(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	lua_pushstring(L, rUser.GetName().GetCText());
	return 1;

	__END_USER_DEFINE
	__END_LUA

	lua_pushstring(L, "");
	return 1;
}

/*----------------------------------------------------------------------
功能说明：通知客户端显示倒数
参数个数：2
参数说明：
	1.UserObjID
	2.秒
返回值个数：0
注意事项：
	见C_SendCountdown.h
*/
int C_SendCountdown(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSecond = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

		rUser.SendCountDown(nSecond);
	return 0;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 0;
}
/*----------------------------------------------------------------------
功能说明：取得玩家势力
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetUserForce(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE
		int forceType = rUser.GetForceType( );
		lua_pushnumber(L, forceType);
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, FORCETYPE_T::TYPE_INVAILD);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：设置玩家势力
参数个数：2
参数说明：
	1.UserObjID
	2.势力
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SetUserForce(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int forceType = static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_USER_DEFINE
		
		if(FORCETYPE_T::TYPE_INVAILD < forceType && forceType < FORCETYPE_T::MAX_NUM)
			rUser.SetForceType( forceType );
	
	return 0;

	__END_USER_DEFINE
		__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：不更新ZombieUser AI
参数个数：2
参数说明：
	1.ZombieUserObjID
	2.bool
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_ControlZombieUserAI(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nZombieUserID = static_cast<int>(lua_tonumber(L, 1));
	int enable = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_ZOMBIEUSER_DEFINE

	rZombieUser.SetAIStop( enable == 0 );

	return 0;

	__END_ZOMBIEUSER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：重设ZombieUser 势力
参数个数：2
参数说明：
	1.ZombieUserObjID
	2.势力
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_ChangeZombieUserForce(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nZombieUserID = static_cast<int>(lua_tonumber(L, 1));
	int nZombieForce = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_ZOMBIEUSER_DEFINE

	if(FORCETYPE_T::TYPE_INVAILD < nZombieForce && nZombieForce < FORCETYPE_T::MAX_NUM)
		rZombieUser.SetForceType( nZombieForce );

	return 0;

	__END_ZOMBIEUSER_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：C_CallZombieUserFellow
参数个数：1
参数说明：
	1.ZombieUserObjID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_CallZombieUserFellow(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nZombieUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_ZOMBIEUSER_DEFINE

	rZombieUser.CallFellow( );

	return 0;

	__END_ZOMBIEUSER_DEFINE
	__END_LUA
	return 0;
}


/*----------------------------------------------------------------------
功能说明：C_PlaySoundEffect 播放音效
参数个数：2
参数说明：
    1._nUserID, 玩家ID
	2. szSoundName
	声音名称，Sound.txt表格里面的首列内容
返回值个数：0
注意事项：
	见Script_Define.h
-------------------------------------------------------------------------
*/

int C_PlaySoundEffect(lua_State* L)		//播放音效
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSoundID = static_cast<int>(lua_tonumber(L, 1));

	if (nSoundID < 0)
	{
		return 0;
	}

	__BEGIN_USER_DEFINE

	rUser.PlaySoundEffect(nSoundID);

	__END_USER_DEFINE

	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：C_PlaySceneBackGroundMusic 播放场景背景音乐，带淡入淡出效果
参数个数：1
参数说明：
	1.szSoundName
	声音名称，Sound.txt表格里面的首列内容
返回值个数：0
注意事项：
	见Script_Define.h
-------------------------------------------------------------------------
*/
int C_PlaySceneBackGroundMusic(lua_State* L)	//播放场景音乐
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSoundID = static_cast<int>(lua_tonumber(L, 1));

	if (nSoundID < 0)
	{
		return 0;
	}

	__BEGIN_USER_DEFINE

	rUser.PlaySceneBackGroundMusic(nSoundID);

	__END_USER_DEFINE

	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：取得玩家CommonFlag
参数个数：1
参数说明：
	1.UserObjID
	2.nIndex
返回值个数：1
	1.Flag
注意事项：
	见Script_Define.h
*/
int C_GetCommonFlag(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nBit = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		
		lua_pushnumber(L, (rUser.GetCommonFlag(nBit)?1:0) );
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：设置玩家CommonFlag
参数个数：3
参数说明：
	1.UserObjID
	2.nIndex
	3.bFlag(true, false)
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SetCommonFlag(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nIndex = static_cast<int>(lua_tonumber(L, 2));
	int nFlag = static_cast<int>(lua_tonumber(L, 3));
	__BEGIN_USER_DEFINE
		bool bFlag = (nFlag==1?true:false);
		rUser.SetCommonFlag(nIndex,bFlag);
	return 0;

	__END_USER_DEFINE
		__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：取得玩家CommonData
参数个数：2
参数说明：
	1.UserObjID
	2.nIndex
返回值个数：1
	1.CommonData 数据
注意事项：
	见Script_Define.h
*/
int C_GetCommonData(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nIndex = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		lua_pushnumber(L, rUser.GetCommonData(nIndex));
	return 1;

	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：设置玩家CommonData
参数个数：3
参数说明：
	1.UserObjID
	2.nIndex
	3.nValue
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SetCommonData(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nIndex = static_cast<int>(lua_tonumber(L, 2));
	int nValue = static_cast<int>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE
		
		rUser.SetCommonData(nIndex, nValue,true);
	return 0;

	__END_USER_DEFINE
		__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：返回挑战结果
参数个数：3
参数说明：
	1.UserObjID
	1.result
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SendChallengeResult(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nResult  = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		bool bWin = (nResult > 0);
		rUser.SendChallengeResult2Service( bWin );
		return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;

}

/*----------------------------------------------------------------------
功能说明：返回切磋结果
参数个数：3
参数说明：
	1.UserObjID
	1.result
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SendDuelResult(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nResult  = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		bool bWin = (nResult > 0);
		rUser.DuelResult( bWin );
		return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;

}

/*----------------------------------------------------------------------
功能说明：返回华山论剑结果
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SendHuaShanPvPResultByWinner(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int opType  = static_cast<int>(lua_tonumber(L, 2));
	int selfHp  = static_cast<int>(lua_tonumber(L, 3));
	int otherHp  = static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_USER_DEFINE
		rUser.WinnerNotifyHuaShanPvPResult2Service(opType, selfHp, otherHp);
	return 0;

	__END_USER_DEFINE

		__END_LUA
		return 0;

}
/*----------------------------------------------------------------------
功能说明：根据GUID 获取objID
参数个数：2
参数说明：
	1.GUIDH
	2.GUIDL
返回值个数：1
返回值说明：objID
注意事项：
	见Script_Define.h
*/
int C_GetObjIDByGuid(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	__BEGIN_SCENE_DEFINE
		int _nGuidH = static_cast<int>(lua_tonumber(L, 1));
		int _nGuidL = static_cast<int>(lua_tonumber(L, 2));
		int64 _UserGuid(_nGuidH,_nGuidL);
		Obj_UserPtr _userPtr =rScene.GetUserByGuid(_UserGuid);
		if (_userPtr)
		{
			lua_pushnumber(L, _userPtr->GetID());
			return 1;
		}
		lua_pushnumber(L, invalid_id);
		return 1;
	__END_SCENE_DEFINE
		lua_pushnumber(L, invalid_id);
		return 1;
	__END_LUA
		lua_pushnumber(L, invalid_id);
		return 1;

}
/*____________________________________________________
功能说明：获得玩家的Channel，字符串形式
参数个数：1
参数说明：1.玩家id
______________________________________________________*/
int C_GetUserChannel(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L,"");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_USER_DEFINE
		lua_pushstring(L, rUser.GetChannelID().GetCText());
	return 1;
	__END_USER_DEFINE
		__END_LUA
		lua_pushstring(L,"");
	return 1;
}
/*----------------------------------------------------------------------
功能说明：清除雇佣兵数据
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_ResetMercenary(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE
		rUser.ResetMercenary(  );
		return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;

}

/*----------------------------------------------------------------------
功能说明：增加帮贡
参数个数：2
参数说明：
	1.UserObjID
	2.nAddValue
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_IncGuildContribute(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nAddValue = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		rUser.IncGuildContribute(nAddValue);
		return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：是否在雄霸天下活动期间内
参数个数：2
参数说明：
	1.UserObjID
	2.nAddValue
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_CheckXBTXIsOpen(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE
		
		if (TimeUtility::IsInDominateWorldWarTime())
		{
			lua_pushnumber(L, 1);
			return 1;
		}
		lua_pushnumber(L, 0);
		return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：是否是雄霸天下进攻方
参数个数：2
参数说明：
	1.UserObjID
	2.nAddValue
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_CheckIsInDomainTheWorldCombat(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE
		
		if (rUser.GetXBTXType() == XBTX_GUILD_TYPE::XBTX_ATTACK || rUser.GetXBTXType() == XBTX_GUILD_TYPE::XBTX_DEFENSE)
		{
			lua_pushnumber(L, 1);
			return 1;
		}
		lua_pushnumber(L, 0);
		return 1;

	__END_USER_DEFINE

	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：增加帮派魂点
参数个数：2
参数说明：
	1.UserObjID
	2.nAddValue
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_IncHeroSoulExp(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nAddValue = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		
		rUser.IncHeroSoulExpEx(nAddValue, OP_ADDEXP_HEROSOUL_SCRIPT);
		return 1;

	__END_USER_DEFINE

	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：增加经验
参数个数：2
参数说明：
	1.UserObjID
	2.nAddValue
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_IncExp(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nAddValue = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
		int nRealAddExp = 0;
		
		rUser.IncExpEx(nAddValue, nRealAddExp, OP_ADDEXP_SCRIPT);
		lua_pushnumber(L, nRealAddExp);
		return 1;

	__END_USER_DEFINE

	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：增加金钱
参数个数：2
参数说明：
	1.UserObjID
	2.nAddType
	3.nAddValue
	4.nOpType
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_IncMoney(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nAddType = static_cast<int>(lua_tonumber(L, 2));
	int nAddValue= static_cast<int>(lua_tonumber(L, 3));
	int nOpType= static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_USER_DEFINE
	if (nAddType > MONEYTYPE_INVALID && nAddType < MONEYTYPE_TYPECOUNT)
	{
		rUser.MoneyOP_IncMoney((MONEYTYPE)nAddType,nAddValue,nOpType);
	}
	return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：增加金钱
参数个数：2
参数说明：
	1.UserObjID
	2.nSceneID
	3.fPosX
	4.fPosY
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_ChangeScene(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSceneID = static_cast<int>(lua_tonumber(L, 2));
	float fPosX	= static_cast<float>(lua_tonumber(L, 3));
	float fPosY	= static_cast<float>(lua_tonumber(L, 4));

	__BEGIN_USER_DEFINE
		if (rUser.IsInPaoShang())//跑商状态下不能 传送
		{
			rUser.SendNotice("#{3937}");  
			return 0;
		}
		rUser.ChangeScene_General(nSceneID, ScenePos(fPosX, fPosY));
		return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：取得玩家当天日常任务完成次数
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
	1.次数
注意事项：
	见Script_Define.h
*/
int C_GetDailyMissionDoneCount(lua_State *L)
{
	__BEGIN_LUA

// 		AssertEx(L, "");
// 	AssertLuaNumberParam(L, 1);
// 	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
// 
// 	__BEGIN_USER_DEFINE
// 		lua_pushnumber(L, rUser.GetDailyMissionDoneCount());
// 	return 1;
// 
// 	__END_USER_DEFINE
		__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：玩家获取坐骑
参数个数：2
参数说明：
	1.UserObjID
	2.MountID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_CollectMount(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nMountID = static_cast<int>(lua_tonumber(L, 2));
	int nLeftTime = static_cast<int>(lua_tonumber(L, 3));
	__BEGIN_USER_DEFINE

	rUser.CollectMount(nMountID, nLeftTime);
	return 0;

	__END_USER_DEFINE
	
	__END_LUA
	return 0;
}
 /*----------------------------------------------------------------------
功能说明：取得玩家是否已经获取此坐骑
参数个数：2
参数说明：
	1.UserObjID
	2.MountID
返回值个数：1
	1.是否已经获取
注意事项：
	见Script_Define.h
*/
int C_IsMountCollected(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nMountID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE
	if (rUser.IsMountCollected(nMountID))
	{
		lua_pushnumber(L, 1);
		return 1;
	}

	lua_pushnumber(L, 0);
	return 1;

	__END_USER_DEFINE

	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：玩家原地复活(不扣除金钱)
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_Relive(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			int nMaxHp =rUser.GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXHP));
			int nMaxMp =rUser.GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXMP));
			int nMaxXp =rUser.GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXXP));
			
			rUser.Relive(nMaxHp,nMaxMp,nMaxXp,RELIVE_ORIGINAL);
			Packets::GC_RET_RELIVE_PAK pak;
			pak.m_PacketData.set_objid(_nUserID);
			rScene.BroadCast(pak);
			return 0;
		__END_USER_DEFINE

	__END_LUA
		return 0;
}
/*----------------------------------------------------------------------
功能说明：玩家原地复活(不扣除金钱)
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_ReliveOther(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			int nMaxHp =rUser.GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXHP));
			int nMaxMp =rUser.GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXMP));
			int nMaxXp =rUser.GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXXP));
			
			rUser.Relive(nMaxHp,nMaxMp,nMaxXp,RELIVE_OTHER);
			Packets::GC_RET_RELIVE_PAK pak;
			pak.m_PacketData.set_objid(_nUserID);
			rScene.BroadCast(pak);
			return 0;
		__END_USER_DEFINE

	__END_LUA
		return 0;
}
/*----------------------------------------------------------------------
功能说明：副本通过次数
参数个数：4
参数说明：
	1.UserObjID
	2.nSceneClassID
	3.nDifficulty
	4.IsSingle
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_GetCopySceneDayNumber(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nSceneClassID = static_cast<int>(lua_tonumber(L, 2));
	int IsSingle = static_cast<int>(lua_tonumber(L, 3));
	bool bIsSingle = (IsSingle == 1?true:false);
		__BEGIN_USER_DEFINE
			const int nDayNum = rUser.GetCopySceneDayNumber(nSceneClassID, bIsSingle);
			lua_pushnumber(L, nDayNum);
			return 1;
		__END_USER_DEFINE

	__END_LUA
		lua_pushnumber(L,0);
		return 1;
}
/*----------------------------------------------------------------------
功能说明：玩家是否打了防御性宝石
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
	1.true/false
注意事项：
	见Script_Define.h
*/
int C_IsPutDefensiveGem(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			
			lua_pushboolean(L, rUser.IsHavePutDefensiveGem());
			return 1;
		__END_USER_DEFINE

	__END_LUA
		lua_pushboolean(L,false);
		return 1;
}


/*----------------------------------------------------------------------
功能说明：玩家是否打了攻击性宝石
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
	1.true/false
注意事项：
	见Script_Define.h
*/
int C_IsPutAttackGem(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			
			lua_pushboolean(L, rUser.IsHavePutAttackGem());
			return 1;
		__END_USER_DEFINE

	__END_LUA
		lua_pushboolean(L,false);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：获取玩家杀气值
参数个数：2
参数说明：
	1.UserObjID
返回值个数：1
注意事项：
	见Script_Define.h
*/
int C_GetUserPkValue(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			lua_pushnumber(L, rUser.GetPKValue());
			return 1;
		__END_USER_DEFINE
	__END_LUA
		lua_pushnumber(L, 0);
		return 1;
}
/*----------------------------------------------------------------------
功能说明：修改玩家的杀气值
参数个数：2
参数说明：
	1.UserObjID
	2.杀气值(正数增加 负数减小)
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_IncUserPkValue(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		AssertLuaNumberParam(L, 2);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		int nIncPkValue = static_cast<int>(lua_tonumber(L, 2));
		__BEGIN_USER_DEFINE
			int nNewPkvalue =rUser.GetPKValue()+nIncPkValue;
			rUser.SetPKValue(nNewPkvalue);
			return 0;
		__END_USER_DEFINE
	__END_LUA
		return 0;
}
/*----------------------------------------------------------------------
功能说明：设置玩家在线领奖同步数据版本号
参数个数：2
参数说明：
	1.UserObjID
	2.nVersionID
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SetOnlineAwardVersion(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nVersion = static_cast<int>(lua_tonumber(L, 2));
		__BEGIN_USER_DEFINE
			
			rUser.SetAwardTableVerSion(nVersion);
			return 0;
		__END_USER_DEFINE

	__END_LUA
		return 0;
}

/*----------------------------------------------------------------------
功能说明：发送在线领奖表格数据
参数个数：1
参数说明：
	1.UserObjID
	2.索引ID
	3.时长
	4.经验
	5.金币
	6.绑定元宝
	7.物品1DataID
	8.物品1Count
	9.物品2DataID
	10.物品2Count
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SendAwardTableLine(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	AssertLuaNumberParam(L, 7);
	AssertLuaNumberParam(L, 8);
	AssertLuaNumberParam(L, 9);
	AssertLuaNumberParam(L, 10);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	OnlineAwardTableLine DataLine;
	DataLine.m_ID = static_cast<int>(lua_tonumber(L, 2));
	DataLine.m_LeftTime = static_cast<int>(lua_tonumber(L, 3));
	DataLine.m_Exp = static_cast<int>(lua_tonumber(L, 4));
	DataLine.m_Money = static_cast<int>(lua_tonumber(L, 5));
	DataLine.m_BindYuanbao = static_cast<int>(lua_tonumber(L, 6));
	DataLine.m_Item1DataID = static_cast<int>(lua_tonumber(L, 7));
	DataLine.m_Item1Count = static_cast<int>(lua_tonumber(L, 8));
	DataLine.m_Item2DataID= static_cast<int>(lua_tonumber(L, 9));
	DataLine.m_Item2Count = static_cast<int>(lua_tonumber(L, 10));
		__BEGIN_USER_DEFINE
			
			rUser.SendOnlineAwardTable(DataLine);
			return 0;
		__END_USER_DEFINE

	__END_LUA
		return 0;
}
/*----------------------------------------------------------------------
功能说明：发送更新公告
参数个数：4
参数说明：
	1.UserObjID
	2.标题
	3.内容
	4.日期
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SendUpdateNotice(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	AssertLuaStringParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	const char* strTitle = lua_tostring(L,2);
	const char* strNews = lua_tostring(L,3);
	int nData = static_cast<int>(lua_tonumber(L,4));
	__BEGIN_USER_DEFINE

	if (strTitle && strNews)
	{
		Packets::GC_UPDATENOTICEDATA_PAK pak;
		if ( nData > rUser.GetCommonData(USER_COMMONDATA::CD_NOTICE_DATA))
		{
			pak.m_PacketData.set_isshow(nData);
		}
		rUser.SetCommonData(USER_COMMONDATA::CD_NOTICE_DATA,nData);
		pak.m_PacketData.add_news(strNews);
		pak.m_PacketData.add_data(strTitle);
		rUser.SendPacket(pak);
	}
	

	return 0;
	__END_USER_DEFINE
	__END_LUA
	return 0;

}

int C_AddFashionTime(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nFashionID = static_cast<int>(lua_tonumber(L, 2));
	int nAddTime = static_cast<int>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE

	rUser.AddFashionTime(nFashionID, nAddTime);
	rUser.SendFashionInfo(nFashionID);

	return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：发送推送信息
参数个数：4
参数说明：
	1.UserObjID
	2.内容
	3.日期
	4.重复类型 0：不重复，1：日重复，2：周末重复
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SendPushNotification(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	const char* strNews = lua_tostring(L,2);
	int nDate = static_cast<int>(lua_tonumber(L,3));
	int nRepeat = static_cast<int>(lua_tonumber(L,4));
	__BEGIN_USER_DEFINE

	if (strNews)
	{
		Packets::GC_PUSH_NOTIFICATION_PAK pak;

		pak.m_PacketData.add_news(strNews);
		pak.m_PacketData.add_data(nDate);
		pak.m_PacketData.add_repeat(nRepeat);
		rUser.SendPacket(pak);
	}
	__END_USER_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：设置玩家开服在线领奖同步数据版本号
参数个数：2
参数说明：
	1.UserObjID
	2.nVersionID
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SetNewOnlineAwardVersion(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nVersion = static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_USER_DEFINE
			
	rUser.SetNewAwardTableVerSion(nVersion);
	return 0;
	__END_USER_DEFINE

	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：发送在线领奖表格数据
参数个数：1
参数说明：
	1.UserObjID
	2.索引ID
	3.时长
	4.经验
	5.金币
	6.绑定元宝
	7.物品1DataID
	8.物品1Count
	9.物品2DataID
	10.物品2Count
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SendNewAwardTableLine(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	AssertLuaNumberParam(L, 7);
	AssertLuaNumberParam(L, 8);
	AssertLuaNumberParam(L, 9);
	AssertLuaNumberParam(L, 10);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	OnlineAwardTableLine DataLine;
	DataLine.m_ID = static_cast<int>(lua_tonumber(L, 2));
	DataLine.m_LeftTime = static_cast<int>(lua_tonumber(L, 3));
	DataLine.m_Exp = static_cast<int>(lua_tonumber(L, 4));
	DataLine.m_Money = static_cast<int>(lua_tonumber(L, 5));
	DataLine.m_BindYuanbao = static_cast<int>(lua_tonumber(L, 6));
	DataLine.m_Item1DataID = static_cast<int>(lua_tonumber(L, 7));
	DataLine.m_Item1Count = static_cast<int>(lua_tonumber(L, 8));
	DataLine.m_Item2DataID= static_cast<int>(lua_tonumber(L, 9));
	DataLine.m_Item2Count = static_cast<int>(lua_tonumber(L, 10));
	__BEGIN_USER_DEFINE
			
	rUser.SendNewOnlineAwardTable(DataLine);
	return 0;
	__END_USER_DEFINE
	__END_LUA
	return 0;
}

int C_AuditNewPlayerLog(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nType = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	rUser.AuditNewPlayerLog(nType);

	__END_USER_DEFINE

	return 0;

	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：设置玩家开服在线领奖同步数据版本号
参数个数：2
参数说明：
	1.UserObjID
	2.nVersionID
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SetNew7DayOnlineAwardVersion(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nVersion = static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_USER_DEFINE
			
	rUser.SetNew7DayAwardTableVerSion(nVersion);
	return 0;
	__END_USER_DEFINE

	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：发送在线领奖表格数据
参数个数：1
参数说明：
	1.UserObjID
	2.索引ID
	3.时长
	4.经验
	5.金币
	6.绑定元宝
	7.物品1DataID
	8.物品1Count
	9.物品2DataID
	10.物品2Count
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SendNew7DayAwardTableLine(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	AssertLuaNumberParam(L, 7);
	AssertLuaNumberParam(L, 8);
	AssertLuaNumberParam(L, 9);
	AssertLuaNumberParam(L, 10);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	OnlineAwardTableLine DataLine;
	DataLine.m_ID = static_cast<int>(lua_tonumber(L, 2));
	DataLine.m_LeftTime = static_cast<int>(lua_tonumber(L, 3));
	DataLine.m_Exp = static_cast<int>(lua_tonumber(L, 4));
	DataLine.m_Money = static_cast<int>(lua_tonumber(L, 5));
	DataLine.m_BindYuanbao = static_cast<int>(lua_tonumber(L, 6));
	DataLine.m_Item1DataID = static_cast<int>(lua_tonumber(L, 7));
	DataLine.m_Item1Count = static_cast<int>(lua_tonumber(L, 8));
	DataLine.m_Item2DataID= static_cast<int>(lua_tonumber(L, 9));
	DataLine.m_Item2Count = static_cast<int>(lua_tonumber(L, 10));
	__BEGIN_USER_DEFINE
			
	rUser.SendNew7DayOnlineAwardTable(DataLine);
	return 0;
	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：判断一定距离内npc是否存在
参数个数：3
参数说明：
	1.UserObjID
	2.npc DataID
	3.fRadius 距离
返回值个数：1
	是 否
注意事项：
	见Script_Define.h
*/
int C_IsNearNpc(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nNpcDataID = static_cast<int>(lua_tonumber(L, 2));
	float fRadius = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE
		NpcRefCont Cont;
		rScene.Scan_Npc_Circle(Cont, rUser.GetScenePos(), fRadius);
		for (int i = 0; i < Cont.Size(); i++)
		{
			if (Cont[i].IsAlive() && Cont[i].GetDataID() == nNpcDataID)
			{
				lua_pushnumber(L, 1);
				return 1;
			}
		}
	__END_USER_DEFINE
	__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：发送每日签到表格数据
参数个数：1
参数说明：
	1.UserObjID
	2.索引ID
	3.时长
	4.经验
	5.金币
	6.绑定元宝
	7.物品1DataID
	8.物品1Count
	9.物品2DataID
	10.物品2Count
返回值个数：
注意事项：
	见Script_Define.h
*/
int C_SendSignInAwardTableaLine(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	AssertLuaNumberParam(L, 7);
	AssertLuaNumberParam(L, 8);
	AssertLuaNumberParam(L, 9);
	AssertLuaNumberParam(L, 10);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	SignInAwardTableLine DataLine;
	DataLine.m_Index = static_cast<int>(lua_tonumber(L, 2));
	DataLine.m_vipLimit = static_cast<int>(lua_tonumber(L, 3));
	DataLine.m_Exp = static_cast<int>(lua_tonumber(L, 4));
	DataLine.m_Money = static_cast<int>(lua_tonumber(L, 5));
	DataLine.m_BindYuanbao = static_cast<int>(lua_tonumber(L, 6));
	DataLine.m_Item1DataID = static_cast<int>(lua_tonumber(L, 7));
	DataLine.m_Item1Count = static_cast<int>(lua_tonumber(L, 8));
	DataLine.m_Item2DataID= static_cast<int>(lua_tonumber(L, 9));
	DataLine.m_Item2Count = static_cast<int>(lua_tonumber(L, 10));
	DataLine.m_SupplySignCost = static_cast<int>(lua_tonumber(L, 11));
		__BEGIN_USER_DEFINE
			
			rUser.SendDaySignInAwardTable(DataLine);
			return 0;
		__END_USER_DEFINE

	__END_LUA
		return 0;
}

/*----------------------------------------------------------------------
功能说明：玩家是否得到麒麟臂
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
	1.true/false
注意事项：
	见Script_Define.h
*/
int C_IsGetQiLinBi(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			
			lua_pushboolean(L, rUser.IsHaveGetQiLinBi());
			return 1;
		__END_USER_DEFINE

	__END_LUA
		lua_pushboolean(L,false);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：玩家是否有出战伙伴
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
	1.true/false
注意事项：
	见Script_Define.h
*/
int C_IsHaveInstanceFellow(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			
			lua_pushboolean(L, rUser.IsFellowInstance());
			return 1;
		__END_USER_DEFINE

	__END_LUA
		lua_pushboolean(L,false);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：获取出战伙伴ObjID
参数个数：1
参数说明：
	1.UserObjID
返回值个数：1
	1.InstanceFellowObjID
注意事项：
	见Script_Define.h
*/
int C_GetInstanceFellowObjId(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
		AssertLuaNumberParam(L, 1);
		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
		__BEGIN_USER_DEFINE
			
			lua_pushnumber(L, rUser.GetInstanceFellowObjId());
			return 1;
		__END_USER_DEFINE

	__END_LUA
		lua_pushnumber(L,-1);
		return 1;
}

/*----------------------------------------------------------------------
功能说明：玩家是否强化过装备
参数个数：1
参数说明：
1.userid
返回值个数：1
返回值说明：1 或者 0
注意事项：
----------------------------------------------------------------------*/
int C_IsHaveEquipthen(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));	

	__BEGIN_USER_DEFINE
		ItemPack_T&	 oEquipPack = rUser.GetEquipPack();
	for (int index=0; index<oEquipPack.GetSlotCount(); ++index)
	{
		if (oEquipPack.IsItemValid(index))
		{
			const Item_T& rEquip = oEquipPack.GetItemByIndex(index);
			if (rEquip.IsValid())
			{
				if (rEquip.GetEnchanceLevel() > 0)
				{
					lua_pushnumber(L, 1);
					return 1;
				}
			}
		}
	}

	__END_USER_DEFINE
		lua_pushnumber(L, 0);
	return 1;
	__END_LUA
		lua_pushnumber(L, 0);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：返回武林大会结果
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SendWuLinResultByWinner(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);

	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int opType  = static_cast<int>(lua_tonumber(L, 2));
	int selfHp  = static_cast<int>(lua_tonumber(L, 3));
	int otherHp  = static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_USER_DEFINE
		rUser.WinnerNotifyWuLinResult2Service(opType, selfHp, otherHp);
		return 0;

	__END_USER_DEFINE

	__END_LUA
	return 0;

}

/*----------------------------------------------------------------------
功能说明：增加商银
参数个数：1
参数说明：
	1.num 增加的商银数
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_IncShangYin(lua_State *L)
{
	__BEGIN_LUA
		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int num = static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_USER_DEFINE

	int nDeltaVal = rUser.IncGuildBusinessCoin(num);
	char szNotice[256] = {0};
	if (DictionaryFormat::FormatDictionary(szNotice, sizeof(szNotice), "#{8201}", nDeltaVal) != null_ptr)
	{
		rUser.SendNotice(szNotice);
	}
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}