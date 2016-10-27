#include "Script_Scene.h"
#include "Script_Define.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Scene/ManorScene.h"
#include "Scene/Scene/MainScene.h"
#include "Packet/Packet/GC_CHAT_PAK.h"
#include "Packet/Packet/GC_OP_TELEPORT_PAK.h"
#include "Packet/Packet/GC_SCENE_TIMESCALE_PAK.h"
#include "Packet/Packet/GC_PLAY_MODELSOTRY_PAK.h"
#include "Packet/Packet/GC_OP_QINGGONGPOINT_PAK.h"
#include "Packet/Packet/GC_PLAY_FBELAPSETIME_PAK.h"
#include "Table/Table_CopySceneNpc.h"
#include "Table/Table_SceneClass.h"
#include "Table/Table_CopyScene.h"
#include "Table/Table_CopySceneRule.h"
#include "Table/Table_CopySceneScoreCalc.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Table/Table_DominateTheWorldNpc.h"
#include "Table/Table_HeroSoul.h"
#include "Scene/Scene/CopyScene.h"
#include "WorldBoss/GameDefine_WorldBoss.h"
#include "Service/MessageOp.h"
#include "Mail/GameInterface_Mail.h"
#include "Scene/GameInterface_Scene.h"
#include "Message/RankMsg.h"
#include "Message/WorldBossMsg.h"
#include "Message/FourVillainMsg.h"

/*----------------------------------------------------------------------
功能说明：创建ZombieUser
参数个数：3
参数说明：
	1.UserObjID
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateZombieUser(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE

	Obj_ZombieUserPtr zombiePtr = rScene.CreateZombieUser(_nUserID );
	if (zombiePtr)
	{
		lua_pushnumber(L, zombiePtr->GetID());
		return 1;
	}	

	__END_SCENE_DEFINE
	__END_LUA
	lua_pushnumber(L, invalid_id);
	return 1;

}

/*----------------------------------------------------------------------
功能说明：创建ZombieUser
参数个数：3
参数说明：
	1.UserObjID
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateZombieOfSelf(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	float _fPropertyPre = static_cast<float>(lua_tonumber(L, 3));
	const char* strName = lua_tostring(L,2);
	__BEGIN_USER_DEFINE



	Obj_ZombieUserPtr zombiePtr = rScene.CreateZombieOfSelf(_nUserID,strName, _fPropertyPre);
	if (zombiePtr)
	{
		lua_pushnumber(L, zombiePtr->GetID());
		return 1;
	}	

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, invalid_id);
	return 1;

}

/*----------------------------------------------------------------------
功能说明：创建雇佣兵
参数个数：3
参数说明：
	1.UserObjID
返回值个数：MERCENARY_MAX_HOLD
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateMercenary(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE

		for(int i = 0; i < MERCENARY_MAX_HOLD; i++)
		{
			Obj_ZombieUserPtr zombiePtr = rScene.CreateMercenary(_nUserID, i);
			if (zombiePtr)
			{
				lua_pushnumber(L, zombiePtr->GetID());
			}else
			{
				lua_pushnumber(L, invalid_id);
			}
		}

		return MERCENARY_MAX_HOLD;

		__END_SCENE_DEFINE
			__END_LUA

			for(int i = 0; i < MERCENARY_MAX_HOLD; i++)
				lua_pushnumber(L, invalid_id);
		return MERCENARY_MAX_HOLD;

}

/*----------------------------------------------------------------------
功能说明：创建世界boss
参数个数：0
参数说明：

返回值个数：0
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateWorldBoss(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");


	__BEGIN_SCENE_DEFINE
		WorldBossCreateReqPtr msg = POOLDEF_NEW(WorldBossCreateReq);
		AssertEx(msg,"");
		msg->m_nSceneClassId = rScene.GetSceneClassID();
		msg->m_nSceneInstanceId = rScene.GetSceneInstID();
		SendMessage2Srv(ServiceID::TEAM, msg);

		__END_SCENE_DEFINE
			__END_LUA
		return 0;

}
/*----------------------------------------------------------------------
功能说明：创建NPC
参数个数：3
参数说明：
	1.NPCDataID
	2.x坐标
	3.z坐标
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateNPC(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int nNPCDataID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_SCENE_DEFINE

	Obj_NpcPtr NpcPtr = rScene.CreateNpc(nNPCDataID, ScenePos(fPosX, fPosZ), false);
	if (NpcPtr)
	{
		lua_pushnumber(L, NpcPtr->GetID());
		return 1;
	}	

	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：创建NPC
参数个数：4
参数说明：
	1.NPCDataID
	2.x坐标
	3.z坐标
	4.level
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateLevelNPC(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int nNPCDataID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));
	int	nLevel = static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_SCENE_DEFINE

	Obj_NpcPtr NpcPtr = rScene.CreateNpc(nNPCDataID, ScenePos(fPosX, fPosZ), false, nLevel);
	if (NpcPtr)
	{
		lua_pushnumber(L, NpcPtr->GetID());
		return 1;
	}	

	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：创建玩家NPC
参数个数：4
参数说明：
	1._nUserID
	2.NPCDataID
	3.x坐标
	4.z坐标
	5.level
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateImagePlayerNPC(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nNPCDataID = static_cast<int>(lua_tonumber(L, 2));
	float fPosX = static_cast<float>(lua_tonumber(L, 3));
	float fPosZ = static_cast<float>(lua_tonumber(L, 4));
	int	nLevel = static_cast<int>(lua_tonumber(L, 5));
	__BEGIN_USER_DEFINE

	char szName[MAX_NAME_SIZE];
	memset(szName,0,sizeof(szName));
	tsnprintfex(szName, sizeof(szName), "%s%s", rUser.GetName().GetCText());	

	Obj_NpcPtr NpcPtr = rScene.CreateImagePlayerNpc(nNPCDataID, ScenePos(fPosX, fPosZ), false, nLevel,rUser.GetName().GetCText(),rUser.GetModelVisualID(),rUser.GetWeaponID(),rUser.GetCurProfession());
	if (NpcPtr)
	{
		lua_pushnumber(L, NpcPtr->GetID());
		return 1;
	}	

	__END_USER_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}
int C_SetNPCDirection(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	float fDirection = static_cast<float>(lua_tonumber(L, 2));

	__BEGIN_NPC_DEFINE

	rNpc.SetFaceDir(fDirection);
	return 0;

	__END_NPC_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：删除NPC
参数个数：1
参数说明：
	1.NPCObjID
返回值个数：0
返回值说明：

注意事项：
	见Script_Define.h
*/
int C_DelNpcByObjID(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nNpcObjID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE

	rScene.DelNpcByID(nNpcObjID);

	return 0;
	__END_SCENE_DEFINE
	__END_LUA

	return 0;
}
/*----------------------------------------------------------------------
功能说明：删除ZombieUser
参数个数：1
参数说明：
	1.ObjID
返回值个数：0
返回值说明：

注意事项：
	见Script_Define.h
*/
int C_DelZombieByObjID(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nNpcObjID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE

	rScene.DelZombieByID(nNpcObjID);

	return 0;
	__END_SCENE_DEFINE
	__END_LUA

	return 0;
}
/*----------------------------------------------------------------------
功能说明：获取NPCDataID
参数个数：1
参数说明：
	1.NPCObjID
返回值个数：1
返回值说明：
	1.NPCDataID
注意事项：
	见Script_Define.h
*/
int C_GetNPCDataID(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_NPC_DEFINE

	lua_pushnumber(L, rNpc.GetDataID());
	return 1;

	__END_NPC_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：杀死当前场景所有敌方NPC
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_KillAllEnemyNPC(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	NpcRefCont NRCont;
	rScene.Scan_Npc_All(NRCont);
	for (int i = 0; i < NRCont.Size(); i++)
	{
		if (rUser.IsEnemy(NRCont[i]))
		{
			NRCont[i].IncreaseHp(-NRCont[i].GetCurHp(), rUser);
		}
	}
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：服务器操作传送点 主要是副本用
参数个数：2
参数说明：
	1.UserObjID
	2.显示/隐藏
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SendTeleportOp(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nIsShow = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	Packets::GC_OP_TELEPORT_PAK pak;
	pak.m_PacketData.set_isshow(nIsShow);
	rUser.SendPacket(pak);
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

int C_SendQingGongPointOp(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaStringParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	const char* strName = lua_tostring(L, 2);
	int nIsShow = static_cast<int>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE

	Packets::GC_OP_QINGGONGPOINT_PAK pak;
	pak.m_PacketData.set_name(strName);
	pak.m_PacketData.set_isshow(nIsShow);
	rUser.SendPacket(pak);
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：判断NPC是否场景中已有
参数个数：1
参数说明：
	1.NPCDataID
返回值个数：1
返回值说明：
	1.是否已有（bool：0，没有；1，有）
注意事项：
	见Script_Define.h
*/
int C_IsNpcInScene(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int NpcDataID = static_cast<int>(lua_tonumber(L, 1));
	
	__BEGIN_SCENE_DEFINE

	NpcRefCont NRCont;
	rScene.Scan_Npc_All(NRCont);
	for (int i = 0; i < NRCont.Size(); i++)
	{
		if (NRCont[i].GetDataID() == NpcDataID)
		{
			lua_pushnumber(L, 1);
			return 1;
		}
	}


	lua_pushnumber(L, 0);
	return 1;
	__END_SCENE_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：服务器控制改变镜头速度 多在副本给boss最后一击时用慢放
参数个数：2
参数说明：
	1.UserObjID
	2.类型
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_SceneTimeScale(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nTimeScaleType = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	Packets::GC_SCENE_TIMESCALE_PAK pak;
	pak.m_PacketData.set_timescaletype(nTimeScaleType);
	rUser.SendPacket(pak);

	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：服务器控制改变镜头速度 多在副本给boss最后一击时用慢放
参数个数：1
参数说明：
	1.UserObjID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_LeaveCopyScene(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_USER_DEFINE

	rUser.ChangeScene_ExitCopyScene();
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：播放动画剧情
参数个数：1
参数说明：
	1.UserObjID
	2.动画ID 客户端临时做区分用
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_PlayModelStory(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nModelStoryID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

	Packets::GC_PLAY_MODELSOTRY_PAK pak;
	pak.m_PacketData.set_modelstoryid(nModelStoryID);
	rUser.SendPacket(pak);
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：获取副本是单人还是多人玩法
参数个数：0
参数说明：
返回值个数：1
返回值说明：
	1.副本玩法枚举，见CopyScenePlayType
注意事项：
	见Script_Define.h
*/
int C_GetCopyScenePlayType(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");

	__BEGIN_SCENE_DEFINE
	lua_pushnumber(L, rScene.GetCopyScenePlayType());
	return 1;
	__END_SCENE_DEFINE

	__END_LUA
	lua_pushnumber(L, CopyScenePlayType::NONE);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取副本难度
参数个数：0
参数说明：
返回值个数：1
返回值说明：
	1.副本难度，见CopySceneDifficulty
注意事项：
	见Script_Define.h
*/
int C_GetCopySceneDifficulty(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");

	__BEGIN_SCENE_DEFINE
	lua_pushnumber(L, rScene.GetCopySceneDifficulty());
	return 1;
	__END_SCENE_DEFINE

	__END_LUA
	lua_pushnumber(L, CopySceneDifficulty::DEFAULT);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：按波次刷怪
参数个数：3
参数说明：1第几波 2怪物等级 3层数
返回值个数：1
返回值说明：
	1.1成功，0失败
注意事项：
	见CopySceneNpc表格
*/
int C_CreateCopySceneNpc(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int nWaveId = static_cast<int>(lua_tonumber(L, 1));
	int nLevel = static_cast<int>(lua_tonumber(L, 2));
	int nTier = static_cast<int>(lua_tonumber(L, 3));
	__BEGIN_SCENE_DEFINE

	if (rScene.IsCopyScene() == false)
	{
		lua_pushnumber(L, 0);
		return 1;
	}


	const SceneClassID scID = rScene.GetSceneClassID();
	int nNpcIndex = 0;
	switch (scID)
	{
	case CopySceneTimesLimitedID::TLI_WUJUESHENGONG:
		{
			// 无神绝宫周末处理
			if (gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6)
			{
				nNpcIndex = 1;
			}
		}
		break;
	case CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI:
		{
			// 怒海锄奸圣诞节处理 圣诞节已过
		}
		break;
	}
	int nNpcCount = GetTable_CopySceneNpcCount();
// 	if (nLevel <= 0 )
// 	{
// 		nLevel = 1;
// 	}
	int nShowNpcCount = 0;
	for (int i = 0; i < nNpcCount; i++)
	{
		const Table_CopySceneNpc *pLine = GetTable_CopySceneNpcByIndex(i);
		if (pLine != null_ptr)
		{	
			const Table_CopySceneNpc &rLine = *pLine;
			if (rLine.GetCopySceneID() == scID && nWaveId == rLine.GetWave() && nTier == rLine.GetTier())
			{
				int nPlayType = rScene.GetCopyScenePlayType();
				int nDifficulty = rScene.GetCopySceneDifficulty();
				bool isShow = false;
				if (nPlayType == CopyScenePlayType::SINGLE)
				{
					if (rLine.GetDifficultybyIndex(nDifficulty -1) == 1)
					{
						isShow = true;
					}
				}
				else
				{
					if (rLine.GetDifficultyTeambyIndex(nDifficulty -1) == 1)
					{
						isShow = true;
					}
				}
				if (isShow)
				{
					int nDataID = rLine.GetDataIDbyIndex(nNpcIndex);
					//if ((gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6) && scID == CopySceneTimesLimitedID::TLI_WUJUESHENGONG)
					//{
					//	 nDataID = rLine.GetDataIDbyIndex(1);
					//}
					//else if (((gTimeManager.GetYear() == 2014 && gTimeManager.GetMonth() + 1 == 12 &&  gTimeManager.GetDay() >= 14 )
					//	||(gTimeManager.GetYear() == 2015&& gTimeManager.GetMonth() + 1 == 1 &&  gTimeManager.GetDay() < 4 ))
					//	&& scID == CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI)//怒海锄奸圣诞节处理
					//{
					//	nDataID = rLine.GetDataIDbyIndex(1);
					//}
					Obj_NpcPtr npcPtr = rScene.CreateNpc(nDataID,ScenePos(rLine.GetPosX(), rLine.GetPosZ()),false,nLevel);
					if (npcPtr)
					{
						npcPtr->SetFaceDir(rLine.GetFaceDirection());
						nShowNpcCount ++;
					}					
				}				
			}
		}
	}
	
	lua_pushnumber(L, nShowNpcCount);
	return 1;

	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：获取副本的基本信息
参数个数：1
参数说明：任务ID
返回值个数：8
返回值说明：
	1.难度
	2.单人或多人
	3.评分
	4.最高连击
	5.副本开始时间
	6.星级
	7.死亡统计
	8.副本怪的数量
注意事项：
	见CopyScene.h
*/
int C_GetCopySceneInfo(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nMissionId = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_SCENE_DEFINE
	if (rScene.IsCopyScene())
	{
		CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
		lua_pushnumber(L, rCopyScene.GetPlayType());
		lua_pushnumber(L, rCopyScene.GetDifficulty());
		lua_pushnumber(L, rCopyScene.GetScore());
		lua_pushnumber(L, rCopyScene.GetCarom());
		lua_pushnumber(L, rCopyScene.GetStartTime());
		lua_pushnumber(L, rCopyScene.GetStar());
		lua_pushnumber(L, rCopyScene.GetDieCount());

		SceneClassID nScID = rScene.GetSceneClassID();
		int nTier = rCopyScene.GetCopySceneTier();
		int nTabLineCount = GetTable_CopySceneNpcCount();
		int16 nTotalNpcCount = 0;
		for (int i = 0; i < nTabLineCount; i++)
		{
			const Table_CopySceneNpc *pLine = GetTable_CopySceneNpcByIndex(i);
			if (pLine != null_ptr)
			{	
				const Table_CopySceneNpc &rLine = *pLine;
				if (rLine.GetCopySceneID() == nScID && rLine.GetMissionID() == nMissionId && rLine.GetWave() != -1)
				{
					if (rLine.GetTier() == nTier || (1 == nTier && rLine.GetTier() <= 0))
					{
						int nPlayType = rScene.GetCopyScenePlayType();
						int nDifficulty = rScene.GetCopySceneDifficulty();
						bool isInCopyScene = false;
						if (nPlayType == CopyScenePlayType::SINGLE)
						{
							if (rLine.GetDifficultybyIndex(nDifficulty -1) == 1)
							{
								isInCopyScene = true;
							}
						}
						else
						{
							if (rLine.GetDifficultyTeambyIndex(nDifficulty -1) == 1)
							{
								isInCopyScene = true;
							}
						}

						const Table_RoleBaseAttr *pBaseRttr = GetTable_RoleBaseAttrByID(rLine.GetDataIDbyIndex(0));
						if (pBaseRttr == null_ptr)
						{
							continue;
						}

						if (pBaseRttr->GetCamp() != 3)
						{
							isInCopyScene = false;
						}

						if (isInCopyScene)
						{
							nTotalNpcCount++;
						}
					}
				}
			}
		}

		lua_pushnumber(L, nTotalNpcCount);
	}
	else
	{
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
		lua_pushnumber(L, invalid_id);
	}	
	return 8;
	__END_SCENE_DEFINE

	__END_LUA
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	return 8;
}

/*----------------------------------------------------------------------
功能说明：得到副本创建的敌对怪的总数
参数个数：1
参数说明：最大波次
返回值个数：1
返回值说明：
	1. NPC总数
注意事项：
	见CopyScene.h
*/
int C_GetCopySceneNPCTotalNum(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nMaxWave = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_SCENE_DEFINE
	int16 nNpcNum = 0;
	if (rScene.IsCopyScene() && nMaxWave > 0)
	{
		CopyScene& rCopyScene =  static_cast<CopyScene&>(rScene);
		bool bIsSingle = rScene.GetCopyScenePlayType() == CopyScenePlayType::SINGLE;
		const int nDiffIndex = rScene.GetCopySceneDifficulty() - 1;
		int nNpcIndex = 0;
		switch (rScene.GetSceneClassID())
		{
		case CopySceneTimesLimitedID::TLI_WUJUESHENGONG:
			{
				// 无神绝宫周末处理
				if (gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6)
				{
					nNpcIndex = 1;
				}
			}
			break;
		case CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI:
			{
				// 怒海锄奸圣诞节处理 圣诞节已过
			}
			break;
		}
		const int nTabLineCount = GetTable_CopySceneNpcCount();
		for (int i = 0; i < nTabLineCount; i++)
		{
			const Table_CopySceneNpc *pLine = GetTable_CopySceneNpcByIndex(i);
			if (pLine != null_ptr)
			{	
				const Table_CopySceneNpc &rLine = *pLine;
				if (rLine.GetCopySceneID() == rScene.GetSceneClassID() && rLine.GetWave() <= nMaxWave)
				{
					if (rLine.GetTier() <= 0 || rLine.GetTier() == rCopyScene.GetCopySceneTier())
					{
						const Table_RoleBaseAttr *pRoleBase = GetTable_RoleBaseAttrByID(rLine.GetDataIDbyIndex(nNpcIndex));
						if (pRoleBase == null_ptr)
						{
							continue;
						}
						if (pRoleBase->GetCamp() != FORCETYPE_T::NPC_ATTACK)
						{
							continue;
						}
						if (bIsSingle)
						{
							if (rLine.GetDifficultybyIndex(nDiffIndex) != 1)
							{
								continue;
							}
						}
						else
						{
							if (rLine.GetDifficultyTeambyIndex(nDiffIndex) != 1)
							{
								continue;
							}
						}
						++nNpcNum;
					}
				}
			}
		}

	}
	lua_pushnumber(L, nNpcNum);
	return 1;
	__END_SCENE_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：判断是否为副本NPC
参数个数：1
参数说明：NPC的ObjId
返回值个数：1
返回值说明：
	1. 是否此副本的NPC，通过C_CreateCopySceneNpc创建，CopySceneNpc.txt表中配置
注意事项：
	见CopyScene.h
*/
int C_IsCopySceneNPC(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_NPC_DEFINE
	bool bFound = false;
	if (rScene.IsCopyScene())
	{
		CopyScene& rCopyScene =  static_cast<CopyScene&>(rScene);
		bool bIsSingle = rScene.GetCopyScenePlayType() == CopyScenePlayType::SINGLE;
		const int nDiffIndex = rScene.GetCopySceneDifficulty() - 1;
		int nNpcIndex = 0;
		switch (rScene.GetSceneClassID())
		{
		case CopySceneTimesLimitedID::TLI_WUJUESHENGONG:
			{
				// 无神绝宫周末处理
				if (gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6)
				{
					nNpcIndex = 1;
				}
			}
			break;
		case CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI:
			{
				// 怒海锄奸圣诞节处理 圣诞节已过
			}
			break;
		}
		const int nTabLineCount = GetTable_CopySceneNpcCount();
		for (int i = 0; i < nTabLineCount; i++)
		{
			const Table_CopySceneNpc *pLine = GetTable_CopySceneNpcByIndex(i);
			if (pLine != null_ptr)
			{	
				const Table_CopySceneNpc &rLine = *pLine;
				if (rLine.GetCopySceneID() == rScene.GetSceneClassID() && rLine.GetDataIDbyIndex(nNpcIndex) == rNpc.GetDataID())
				{
					if (bIsSingle)
					{
						if (rLine.GetDifficultybyIndex(nDiffIndex) == 1)
						{
							bFound = true;
							break;
						}
					}
					else
					{
						if (rLine.GetDifficultyTeambyIndex(nDiffIndex) == 1)
						{
							bFound = true;
							break;
						}
					}

				}
			}
		}
	}
	lua_pushboolean(L, bFound);
	return 1;
	__END_NPC_DEFINE
	__END_LUA
	lua_pushboolean(L, false);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取副本的基本信息
参数个数：4
参数说明：_userId,返回值，星级，评分
返回值个数：1
返回值说明：
	1.是否成功

注意事项：
	见CopyScene.h
*/
int C_SetCopySceneResult(lua_State *L)
{
	__BEGIN_LUA


	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3)
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nResult = static_cast<int>(lua_tonumber(L, 2));
	int nStar = static_cast<int>(lua_tonumber(L, 3));
	int nScore = static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_USER_DEFINE
	if (rScene.IsCopyScene())
	{
		CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
		rCopyScene.SetResult(nResult);
		rCopyScene.SetStar(nStar);
		rCopyScene.SetScore(nScore);
		//nResult  1表示成功且结算   2表示失败且结算  3表示成功但是不结算
		if (nResult == 1 ||nResult == 2)
		{
		
			if( 1 )
			{
				UserRefCont Cont;
				rScene.Scan_User_All(Cont);
				rUser.ClearCopySceneUserGuid();
				for (int i = 0; i < Cont.Size(); i++)
				{
					if (Cont[i].IsUser() && Cont[i].GetGuid() != rUser.GetGuid())
					{
						rUser.AddCopySceneUserGuid(Cont[i].GetGuid());
					}
				}
			}

	// 		if (rCopyScene.GetPlayType() == CopyScenePlayType::SINGLE)	//单人
	// 		{
				//随机奖励
				rUser.CreateCopySceneReward();
				
				rUser.AddWinCopySceneNumber(rCopyScene.GetSceneClassID(),rCopyScene.GetDifficulty(),rCopyScene.GetPlayType()==1?true:false);	
				//做帮贡奖励
				rUser.AddMultipleCopySceneGuidReward();
				rUser.AddMultipleCopySceneMasterReward();
	// 		}
	// 		else	//按场景中得人发放
	// 		{
	// 			UserRefCont Cont;
	// 			rScene.Scan_User_All(Cont);
	// 			for (int i = 0; i < Cont.Size(); i++)
	// 			{
	// 				if (Cont[i].IsUser())
	// 				{
	// 					Cont[i].CreateCopySceneReward();
	// 					Cont[i].SendCopySceneReward();
	// 					Cont[i].AddWinCopySceneNumber(rCopyScene.GetSceneClassID(),rCopyScene.GetDifficulty(),false);
	// 				}
	// 			}
	// 		}
			
			if (nResult == 1 )
			{
				rUser.AddCopySceneRewardEP();
			}
			rUser.SendCopySceneReward();		
			//记录CMBI日志
			rUser.CMBI_CacheLog_CompleteCopyScene(rCopyScene);
		}
		
		if (nResult == 3)
		{
			rUser.SendCopySceneReward();	
		}

		// 副本成功通关后更新最高通关难度
		if(nResult == 1 || nResult == 3)
		{
			rUser.UpdateAccomplishDifficult(rCopyScene.GetSceneClassID(),
											rCopyScene.GetDifficulty(),
											rCopyScene.GetPlayType()==CopyScenePlayType::SINGLE?true:false
											);
		}

		
	}


	// 记录日志
	AuditLog(LOGDEF_INST(Audit_CopyScene),"CSR", rUser.GetGuid(), "SID=%d \1 DY=%d \1 SE=%d \1 LE=%d \1 RTt=%d \1 SR=%d \1 SE=%d",
		rUser.GetSceneClassID(),
		rScene.GetCopySceneDifficulty(),
		rScene.GetCopyScenePlayType(),
		rScene.GetLevel(),
		nResult,
		nStar,
		nScore);
	lua_pushnumber(L, 1);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取副本扫荡相关基本信息
参数个数：4
参数说明：_userId,返回值，难度，可扫荡模式
返回值个数：1
返回值说明：
	1.是否成功

注意事项：
	见CopyScene.h
*/
int C_SetSweepLevel(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3)
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nResult = static_cast<int>(lua_tonumber(L, 2));
	int nStar = static_cast<int>(lua_tonumber(L, 3));
	int nDiffcult = static_cast<int>(lua_tonumber(L, 4));
	__BEGIN_USER_DEFINE
		if (rScene.IsCopyScene())
		{
			CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
			rCopyScene.SetResult(nResult);	
			//标记
			if (nStar>=5)
			{
				rUser.AddCurSweepLevel(rScene.GetSceneClassID(),nDiffcult,rCopyScene.GetPlayType()==1?true:false);
			}
		}
		// 记录日志
		AuditLog(LOGDEF_INST(Audit_CopyScene),"CSR", rUser.GetGuid(), "SID=%d \1 DY=%d \1 SE=%d \1 LE=%d \1 RTt=%d \1 SR=%d \1 Diff=%d",
			rUser.GetSceneClassID(),
			rScene.GetCopySceneDifficulty(),
			rScene.GetCopyScenePlayType(),
			rScene.GetLevel(),
			nResult,
			nStar,
			nDiffcult);
		lua_pushnumber(L, 1);
		return 1;

		__END_USER_DEFINE
			__END_LUA
			lua_pushnumber(L, 0);
		return 1;
}
/*----------------------------------------------------------------------
功能说明：获取结果
参数个数：0
参数说明：
返回值个数：1
返回值说明：
副本结果
注意事项：
	见CopyScene.h
*/
int C_GetCopySceneResult(lua_State *L)
{
	__BEGIN_LUA

	__BEGIN_SCENE_DEFINE
	if (rScene.IsCopyScene())
	{
		CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
		lua_pushnumber(L, rCopyScene.GetResult());
	}
	else
	{
		lua_pushnumber(L, invalid_id);
	}
	return 1;

	__END_SCENE_DEFINE
	__END_LUA
	lua_pushnumber(L, invalid_id);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：副本任务按波次刷怪
参数个数：3
参数说明：1第几波 2怪物等级
返回值个数：2
返回值说明：
	1.1成功，0失败
	2.创建的数量
注意事项：
	见CopySceneNpc表格
*/
int C_CreateMissionCopySceneNpc(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);

	int nWaveId = static_cast<int>(lua_tonumber(L, 1));
	int nLevel = static_cast<int>(lua_tonumber(L, 2));
	int nMissionID = static_cast<int>(lua_tonumber(L, 3));

	__BEGIN_SCENE_DEFINE

	if (rScene.IsCopyScene() == false)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}


	SceneClassID scID = rScene.GetSceneClassID();
	int nNpcCount = GetTable_CopySceneNpcCount();
	int16 nNpcCreatedCount = 0;
	for (int i = 0; i < nNpcCount; i++)
	{
		const Table_CopySceneNpc *pLine = GetTable_CopySceneNpcByIndex(i);
		if (pLine != null_ptr)
		{	
			const Table_CopySceneNpc &rLine = *pLine;
			if (rLine.GetCopySceneID() == scID && nWaveId == rLine.GetWave() && nMissionID == rLine.GetMissionID())
			{
				int nPlayType = rScene.GetCopyScenePlayType();
				int nDifficulty = rScene.GetCopySceneDifficulty();
				bool isShow = false;
				if (nPlayType == CopyScenePlayType::SINGLE)
				{
					if (rLine.GetDifficultybyIndex(nDifficulty -1) == 1)
					{
						isShow = true;
					}
				}
				else
				{
					if (rLine.GetDifficultyTeambyIndex(nDifficulty -1) == 1)
					{
						isShow = true;
					}
				}
				if (isShow)
				{
					Obj_NpcPtr NpcPtr = rScene.CreateNpc(rLine.GetDataIDbyIndex(0),ScenePos(rLine.GetPosX(), rLine.GetPosZ()),false,nLevel);
					if(NpcPtr)
					{
						NpcPtr->SetFaceDir(rLine.GetFaceDirection());
						nNpcCreatedCount++;
					}
				}				
			}
		}
	}
	
	lua_pushnumber(L, 1);
	lua_pushnumber(L, nNpcCreatedCount);
	return 2;

	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	lua_pushnumber(L, 0);
	return 2;
}
/*----------------------------------------------------------------------
功能说明：获取副本评分因子
参数个数：3
参数说明：难度
返回值个数：4
返回值说明：
	1.A,B,C,K

注意事项：
	见CopyScene.h
*/
int C_GetCopySceneScoreFactor(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);

	int difficult = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE
		
	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(rScene.GetSceneClassID());
	if (pSceneClass != null_ptr)
	{
		const Table_SceneClass &rSceneClass = *pSceneClass;
		if (rSceneClass.GetType() == SceneType::COPY)
		{
			int nCopySceneID = rSceneClass.GetCopySceneID();
			if (nCopySceneID != invalid_id)
			{
				const Table_CopyScene *pCopyScene = GetTable_CopySceneByID(nCopySceneID);		
				if (pCopyScene != null_ptr)
				{
					const Table_CopyScene &rCopyScene = *pCopyScene;
					int nRule = -1;
					if (rScene.GetCopyScenePlayType() == CopyScenePlayType::SINGLE)
					{
						nRule = rCopyScene.GetRulebyIndex( difficult - 1);
					}
					else
					{
						nRule = rCopyScene.GetRuleTeambyIndex( difficult - 1);
					}
					if (nRule != -1)
					{
						const Table_CopySceneRule *pCopySceneRule = GetTable_CopySceneRuleByID(nRule);
						if (pCopySceneRule != null_ptr)
						{
							int calcId = pCopySceneRule->GetScoreCalcID( );
							const Table_CopySceneScoreCalc *pCopySceneScore =  GetTable_CopySceneScoreCalcByID(calcId);
							if( pCopySceneScore != null_ptr )
							{
								lua_pushnumber(L, pCopySceneScore->GetHitPointPer());
								lua_pushnumber(L, pCopySceneScore->GetPassTimePer());
								lua_pushnumber(L, pCopySceneScore->GetDeadTimesPer());
								lua_pushnumber(L, pCopySceneScore->GetKFactor());
								return 4;
							}
						}
					}
				}
			}
		}
	}

	__END_SCENE_DEFINE
		__END_LUA

		lua_pushnumber(L, 25);
		lua_pushnumber(L, 25);
		lua_pushnumber(L, 50);
		lua_pushnumber(L, 100);
	return 4;
}
/*----------------------------------------------------------------------
功能说明：获取副本评分星级
参数个数：2
参数说明：难度，分数
返回值个数：1
返回值说明：
	1.star

注意事项：
	见CopyScene.h
*/
int C_GetCopySceneScoreStar(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);

	int difficult = static_cast<int>(lua_tonumber(L, 1));
	int score = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_SCENE_DEFINE

		const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(rScene.GetSceneClassID());
	if (pSceneClass != null_ptr)
	{
		const Table_SceneClass &rSceneClass = *pSceneClass;
		if (rSceneClass.GetType() == SceneType::COPY)
		{
			int nCopySceneID = rSceneClass.GetCopySceneID();
			if (nCopySceneID != invalid_id)
			{
				const Table_CopyScene *pCopyScene = GetTable_CopySceneByID(nCopySceneID);		
				if (pCopyScene != null_ptr)
				{
					const Table_CopyScene &rCopyScene = *pCopyScene;
					int nRule = -1;
					if (rScene.GetCopyScenePlayType() == CopyScenePlayType::SINGLE)
					{
						nRule = rCopyScene.GetRulebyIndex( difficult - 1);
					}
					else
					{
						nRule = rCopyScene.GetRuleTeambyIndex( difficult - 1);
					}
					if (nRule != -1)
					{
						const Table_CopySceneRule *pCopySceneRule = GetTable_CopySceneRuleByID(nRule);
						if (pCopySceneRule != null_ptr)
						{
							int i = 0, star = 1;
							int iCount = pCopySceneRule->getScoreCount();
							for( i = 0; i < iCount; i++ )
								if( score >= pCopySceneRule->GetScorebyIndex(i)) break;
							if( i >= iCount || iCount == 0) 
								star = 1;
							else
							{
								star = iCount - i;
								star = _MIN(5, star);
							}

							lua_pushnumber(L, star);
							return 1;
						}
					}
				}
			}
		}
	}

	__END_SCENE_DEFINE
		__END_LUA

		lua_pushnumber(L, 1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：服务器当前时间
参数个数：0
参数说明：
返回值个数：1
返回值说明：
副本结果
注意事项：
	见CopyScene.h
*/
int C_GetServerAnsiTime(lua_State *L)
{
	__BEGIN_LUA
		lua_pushnumber(L, (int)gTimeManager.GetANSITime());
	return 1;
	__END_LUA
	lua_pushnumber(L, (int)gTimeManager.GetANSITime());
	return 1;

}

/*----------------------------------------------------------------------
功能说明：得到当前场景可扫荡等级
参数个数：0
参数说明：
返回值个数：1
返回值说明：
副本结果
注意事项：
	见CopyScene.h
*/
int C_GetCurSweepLevel(lua_State *L)
{
	__BEGIN_LUA
		lua_pushnumber(L, (int)gTimeManager.GetANSITime());
	return 1;
	__END_LUA
	lua_pushnumber(L, (int)gTimeManager.GetANSITime());
	return 1;

}
/*----------------------------------------------------------------------
功能说明：删除当前场景指定DataID的NPC
参数个数：1
参数说明：
	1.DataID
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_DelAllNpcByDataID(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nDataID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE

	NpcRefCont NRCont;
	rScene.Scan_Npc_All(NRCont);
	for (int i = 0; i < NRCont.Size(); i++)
	{
		if (NRCont[i].GetDataID() == nDataID)
		{
			NRCont[i].DelFromScene();
		}
	}
	return 0;

	__END_SCENE_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：删除当前场景的NPC
参数个数：
参数说明：
返回值个数：0
注意事项：
	见Script_Define.h
*/
int C_DelAllNpc(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	__BEGIN_SCENE_DEFINE

	NpcRefCont NRCont;
	rScene.Scan_Npc_All(NRCont);
	for (int i = 0; i < NRCont.Size(); i++)
	{
		NRCont[i].DelFromScene();
	}
	return 0;

	__END_SCENE_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：设置藏经阁胜利信息
参数个数：4
参数说明：_userId,返回值，层数，时间用时
返回值个数：1
返回值说明：
	1.是否成功

注意事项：
	见CopyScene.h
*/
int C_SetCangJingGeCopySceneResult(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3)
	AssertLuaNumberParam(L, 4);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nResult = static_cast<int>(lua_tonumber(L, 2));
	int nTier = static_cast<int>(lua_tonumber(L, 3));
	int nTime = static_cast<int>(lua_tonumber(L, 4));

	__BEGIN_USER_DEFINE
	if (rScene.IsCopyScene())
	{		
		CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
		rCopyScene.SetResult(nResult);
		rCopyScene.SetStar(nTier);
		rCopyScene.SetScore(nTime);
		if (rCopyScene.GetSceneClassID() == CopySceneTimesLimitedID::TLI_CANGJINGGE )
		{
			if( nResult == 1)
			{			
				rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_CANGJINGGERANK_TIME,nTime);	//记录通关时间
				rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_CANGJINGGERANK_TIER,nTier, true);	//记录通关层数
				int nLevel = 0;
				if ( false == rUser.IsGMUser(nLevel))
				{
					InsertCangJingGeRankMsgPtr msgPtr = POOLDEF_NEW(InsertCangJingGeRankMsg);
					AssertEx(msgPtr, "");
					msgPtr->mInfo.CleanUp();
					msgPtr->mInfo.SetGuid(rUser.GetGuid());
					msgPtr->mInfo.SetName(rUser.GetName());
					msgPtr->mInfo.SetLevel(rUser.GetLevel());
					msgPtr->mInfo.SetProfession(rUser.GetCurProfession());
					msgPtr->mInfo.SetTier(nTier);
					msgPtr->mInfo.SetTime(nTime);
					SendMessage2Srv(ServiceID::RANK, msgPtr);
				}
				
				//rUser.CreateCopySceneRewardByID(nTier);
				
				//给通关奖励
				//COPYSCENENAME name("藏经阁");
				//rUser.CreateCopySceneSweepReward(name.GetCText(),nTier);
				rUser.CreateCopySceneRewardByID(nTier, 0);
				//称号
				if (nTier == 90)
				{
					rUser.UserGainSystemTitle(35);
				}
				else if (nTier == 100)
				{
					rUser.UserGainSystemTitle(36);
				}
				rUser.AddCopySceneRewardEP();
			}
			else if( nResult == 0)
			{
				rUser.SetPowerPushEvent(EBPPE_RELIEVE_RETURN);
			}

			rUser.SendCopySceneReward();

			if(nResult == 1)
			{
				rUser.ReceiveCopySceneReward(false);
			}
		}


		// 爬塔任务相关
		rUser.MissionCangJingGe(nTier);
		

		// 记录日志
		AuditLog(LOGDEF_INST(Audit_CopyScene),"CSR", rUser.GetGuid(), "SID=%d \1 RT=%d \1 TR=%d \1 TE=%d",
			rUser.GetSceneClassID(),
			nResult,
			nTier,
			nTime);

		//记录CMBI日志
		rUser.CMBI_CacheLog_CompleteCopyScene(rCopyScene);

		lua_pushnumber(L, 1);
	}
	lua_pushnumber(L, 1);
	return 1;

	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：根据DataID获取当前场景NPC数量
参数个数：2
参数说明：
	1.DataID
返回值个数：1
	1.Npc数量
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_GetNpcCountByDataID(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nDataID = static_cast<int>(lua_tonumber(L, 1));

	int nCount = 0;
	__BEGIN_SCENE_DEFINE

	NpcRefCont Cont;
	rScene.Scan_Npc_All(Cont);
	for (int i = 0; i < Cont.Size(); i++)
	{
		if (Cont[i].GetDataID() == nDataID)
		{
			nCount++;
		}
	}
	lua_pushnumber(L, nCount);
	return 1;

	__END_SCENE_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：给周围玩家加Buff
参数个数：2
参数说明：
	1.objID
	2.buffID
	3.fRadius
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SendImpactToAroundUser(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	int nbuffID = static_cast<int>(lua_tonumber(L, 2));
	float fRadius = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_NPC_DEFINE

	UserRefCont Cont;
	rScene.Scan_User_Circle(Cont,rNpc.GetScenePos(), fRadius);
	for (int i = 0; i < Cont.Size(); i++)
	{
		if (Cont[i].IsAlive())
		{
			rNpc.SendImpactToUnit(Cont[i], nbuffID, -1);
		}
	}
	return 0;

	__END_NPC_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：设置副本层数
参数个数：1
参数说明：
	1.TierID
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_SetCopySceneTier(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nTierID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_SCENE_DEFINE

	if (rScene.IsCopyScene())
	{
		rScene.SetCopySceneTier(nTierID);
	}
	
	return 0;

	__END_SCENE_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：得到副本自适应等级
参数个数：1
参数说明：
返回值个数：
返回值说明：副本等级
注意事项：
	见Script_Define.h
*/
int C_GetCopySceneLevel(lua_State *L)
{
	__BEGIN_LUA

	__BEGIN_SCENE_DEFINE
	if (rScene.IsCopyScene() )
	{		
		int nLevel = rScene.GetLevel();
		lua_pushnumber(L,nLevel);
		return 1;
	}
	lua_pushnumber(L, 1);
	return 1;
	__END_SCENE_DEFINE
	__END_LUA
	lua_pushnumber(L, 1);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：创建掉落
参数个数：6
参数说明：
	如下
返回值个数：
返回值说明：0
注意事项：
	见Script_Define.h
*/
int C_CreateDropItem(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int _ObjID = static_cast<int>(lua_tonumber(L, 2));
	int nType = static_cast<int>(lua_tonumber(L, 3));
	int nItemID = static_cast<int>(lua_tonumber(L, 4));
	int nCount = static_cast<int>(lua_tonumber(L, 5));
	int nDropID = static_cast<int>(lua_tonumber(L, 6));

	__BEGIN_USER_DEFINE
		Obj_NpcPtr obj_Npc = rScene.GetNpcByID(_ObjID);
	if (obj_Npc != null_ptr)
	{
		if (rScene.IsCopyScene() )
		{		
			rScene.CreateDropItem(rUser.GetGuid(), nType, nItemID, nCount, obj_Npc->GetScenePos(), nDropID);
			return 1;
		}
	}
	return 0;
	__END_USER_DEFINE
	__END_LUA
	return 1;
}

/*----------------------------------------------------------------------
功能说明：系统名义发送邮件(带金钱带物品）
参数个数：7
参数说明：
	nReceiverGUIDH	玩家GUID高位
	nReceiverGUIDL	玩家GUID低位
	szContent		邮件内容
	nMoneyType		附带钱类型
	nMoneyValue		附带钱个数
	nItemDataID		附带物品ID
	nItemCount		附带物品个数
	nItemBind		物品绑定类型
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
*/
int C_SystemSendMail_WithMoneyAndItem(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaStringParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	AssertLuaNumberParam(L, 7);
	AssertLuaNumberParam(L, 8);

	int nReceiverGUIDH	= static_cast<int>(lua_tonumber(L, 1));
	int nReceiverGUIDL	= static_cast<int>(lua_tonumber(L, 2));
	const char* szContent	= lua_tostring(L, 3);
	int16 nMoneyType		= static_cast<int16>(lua_tonumber(L, 4));
	int nMoneyValue		= static_cast<int>(lua_tonumber(L, 5));
	int nItemDataID		= static_cast<int>(lua_tonumber(L, 6));
	int nItemCount		= static_cast<int>(lua_tonumber(L, 7));
	int nItemBind		= static_cast<int>(lua_tonumber(L, 8));

	if ( szContent )
	{
		int64 guidTarget(nReceiverGUIDH,nReceiverGUIDL);	
		MailInterface::SystemSendTextMail_WithMoneyAndItem(
			guidTarget,
			szContent,
			nMoneyType,nMoneyValue,
			nItemDataID, nItemCount, 
			OP_MAIL_SCRIPT,
			nItemBind == 1);
	}

	__END_LUA
	return 1;
}

/*----------------------------------------------------------------------
功能说明：系统名义发送邮件(不带附件）
参数个数：3
参数说明：
	nReceiverGUIDH	玩家GUID高位
	nReceiverGUIDL	玩家GUID低位
	szContent		邮件内容
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
*/
int C_SystemSendMail(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaStringParam(L, 3);

	int nReceiverGUIDH	= static_cast<int>(lua_tonumber(L, 1));
	int nReceiverGUIDL	= static_cast<int>(lua_tonumber(L, 2));
	const char* szContent	= lua_tostring(L, 3);

	if ( szContent )
	{
		int64 guidTarget(nReceiverGUIDH,nReceiverGUIDL);	
		MailInterface::SystemSendTextMail(
			guidTarget,
			szContent,
			OP_MAIL_SCRIPT);
	}

	__END_LUA
	return 1;
}

/*----------------------------------------------------------------------
功能说明：系统名义发送邮件(带金钱）
参数个数：5
参数说明：
	nReceiverGUIDH	玩家GUID高位
	nReceiverGUIDL	玩家GUID低位
	szContent		邮件内容
	nMoneyType		附带钱类型
	nMoneyValue		附带钱个数
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
*/
int C_SystemSendMail_WithMoney(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaStringParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);

	int nReceiverGUIDH	= static_cast<int>(lua_tonumber(L, 1));
	int nReceiverGUIDL	= static_cast<int>(lua_tonumber(L, 2));
	const char* szContent	= lua_tostring(L, 3);
	int16 nMoneyType		= static_cast<int16>(lua_tonumber(L, 4));
	int nMoneyValue		= static_cast<int>(lua_tonumber(L, 5));

	if ( szContent )
	{
		int64 guidTarget(nReceiverGUIDH,nReceiverGUIDL);	
		MailInterface::SystemSendTextMail_WithMoney(
			guidTarget,
			szContent,
			nMoneyType,nMoneyValue,
			OP_MAIL_SCRIPT);
	}

	__END_LUA
	return 1;
}

/*----------------------------------------------------------------------
功能说明：系统名义发送邮件(带物品）
参数个数：5
参数说明：
	nReceiverGUIDH	玩家GUID高位
	nReceiverGUIDL	玩家GUID低位
	szContent		邮件内容
	nItemDataID		附带物品ID
	nItemCount		附带物品个数
	nItemBind		附带物品绑定类型
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
*/
int C_SystemSendMail_WithItem(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaStringParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);

	int nReceiverGUIDH	= static_cast<int>(lua_tonumber(L, 1));
	int nReceiverGUIDL	= static_cast<int>(lua_tonumber(L, 2));
	const char* szContent	= lua_tostring(L, 3);
	int nItemDataID		= static_cast<int>(lua_tonumber(L, 4));
	int nItemCount		= static_cast<int>(lua_tonumber(L, 5));
	int nItemBind		= static_cast<int>(lua_tonumber(L, 6));

	if ( szContent )
	{
		int64 guidTarget(nReceiverGUIDH,nReceiverGUIDL);	
		MailInterface::SystemSendTextMail_WithItem(
			guidTarget,
			szContent,
			nItemDataID, 
			nItemCount, 
			OP_MAIL_SCRIPT,
			nItemBind == 1);
	}

	__END_LUA
	return 1;
}

/*----------------------------------------------------------------------
功能说明：玩家之间发邮件
参数个数：6
参数说明：
	nSenderGUIDH	发件人GUID高位
	nSenderGUIDL	发件人GUID低位
	szSenderName	发件人名字
	nReceiverGUIDH	收件人GUID高位
	nReceiverGUIDL	收件人GUID低位
	szContent		邮件内容
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
*/
int C_PlayerSendMail(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaStringParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaStringParam(L, 6);

	int nSenderGUIDH		= static_cast<int>(lua_tonumber(L, 1));
	int nSenderGUIDL		= static_cast<int>(lua_tonumber(L, 2));
	const char* szSenderName	= lua_tostring(L, 3);
	int nReceiverGUIDH	= static_cast<int>(lua_tonumber(L, 4));
	int nReceiverGUIDL	= static_cast<int>(lua_tonumber(L, 5));
	const char* szContent	= lua_tostring(L, 6);

	if ( szContent && szSenderName )
	{
		int64 guidRecevier(nReceiverGUIDH,nReceiverGUIDL);	
		int64 guidSender(nSenderGUIDH,nSenderGUIDL);
		MailInterface::PlayerSendTextMail(
			guidSender,
			szSenderName,
			guidRecevier,
			szContent,
			OP_MAIL_SCRIPT
			);
	}

	__END_LUA
	return 1;
}

/*==========================================================================
功能说明：按照序号获取补偿相关信息
参数个数：2
参数说明：
		1._nUserID	玩家ID 
		2.nIndex	序号
返回值个数：10
返回值说明：
		1.类型
		2~10.九个数值
注意事项：
	见Script_Define.h
============================================================================*/
int C_GetRedeemInfo(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID		= static_cast<int>(lua_tonumber(L, 1));
	int nIndex		= static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_USER_DEFINE

	if ( nIndex >= 0 && nIndex < MAX_REDEEM_NUM )
	{
		lua_pushnumber(L, rUser.GetRedeem().m_data[nIndex].m_rdType);
		for (int i = 0; i< MAX_REDEEM_PARAM; ++i)
		{
			lua_pushnumber(L, rUser.GetRedeem().m_data[nIndex].m_rdParam[i]);
		}
		return MAX_REDEEM_PARAM+1;
	}
	__END_USER_DEFINE
	__END_LUA

	//default
	for (int i = 0 ;i < MAX_REDEEM_PARAM+1; ++i)
	{
		lua_pushnumber(L,invalid_id);
	}
	return MAX_REDEEM_PARAM+1;	
}

/*==========================================================================
功能说明：按照类型设置数据
参数个数：4
参数说明：
		1._nUserID	玩家ID 
		2.nType	类型
		3.nIndex 序号
		4.nValue 数值
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
============================================================================*/
int C_SetRedeemInfo(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID		= static_cast<int>(lua_tonumber(L, 1));
	int nType		= static_cast<int>(lua_tonumber(L, 2));
	int nIndex		= static_cast<int>(lua_tonumber(L, 3));
	int nValue		= static_cast<int>(lua_tonumber(L, 4));
	__BEGIN_USER_DEFINE

	if ( nIndex >= 0 && nIndex < MAX_REDEEM_PARAM )
	{
		for (int mIndex = 0 ; mIndex < MAX_REDEEM_NUM; ++mIndex )
		{
			if ( rUser.GetRedeem().m_data[mIndex].m_rdType == nType )
			{
				rUser.GetRedeem().m_data[mIndex].m_rdParam[nIndex] = nValue;

				CacheLog(LOGDEF_INST(RedeemScript),"S,U[%08X,%08X],T(%d),K(%d),V(%d)",
					rUser.GetGuid().GetHigh32Value(),
					rUser.GetGuid().GetLow32Value(),				
					nType,
					nIndex,
					nValue);

				return 0;
			}
		}
	}
	CacheLog(LOGDEF_INST(RedeemScript),"SE,U[%08X,%08X],T(%d),K(%d),V(%d)",
		rUser.GetGuid().GetHigh32Value(),
		rUser.GetGuid().GetLow32Value(),				
		nType,
		nIndex,
		nValue);

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*==========================================================================
功能说明：增加一个补偿,替换最小type的其他补偿，如果有了就不会再增加。
参数个数：8
参数说明：
		1._nUserID	玩家ID 
		2.nType	类型
		3~11 nParam 参数 可有可无		
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
============================================================================*/
int C_AddRedeem(lua_State *L)
{
	__BEGIN_LUA

	bsarray<int, MAX_REDEEM_PARAM> aParam;
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
	AssertLuaNumberParam(L, 11);
	int _nUserID		= static_cast<int>(lua_tonumber(L, 1));
	int nType		= static_cast<int>(lua_tonumber(L, 2));
	for (int nIndex = 0; nIndex < MAX_REDEEM_PARAM; ++nIndex)
	{
		aParam[nIndex] = static_cast<int>(lua_tonumber(L, 3+nIndex));
	}
	
	__BEGIN_USER_DEFINE

	int minIndex = 0;
	int minType = rUser.GetRedeem().m_data[0].m_rdType;

	for (int mIndex = 0 ; mIndex < MAX_REDEEM_NUM; ++mIndex )
	{
		int curType = rUser.GetRedeem().m_data[mIndex].m_rdType;
		//如果有相同直接放弃
		if ( curType == nType )
		{			
			return 0;
		}
		if ( minType > curType  )
		{
			minType = curType;
			minIndex = mIndex;
		}
	}
	if ( minIndex >= 0 && minIndex < MAX_REDEEM_NUM )
	{
		rUser.GetRedeem().m_data[minIndex].m_rdType = nType;
		for (int nIndex = 0; nIndex < MAX_REDEEM_PARAM; ++nIndex)
		{
			rUser.GetRedeem().m_data[minIndex].m_rdParam[nIndex] = aParam[nIndex];
		}
		CacheLog(LOGDEF_INST(RedeemScript),"A,U[%08X,%08X],T(%d),P(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
			rUser.GetGuid().GetHigh32Value(),
			rUser.GetGuid().GetLow32Value(),
			nType,aParam[0],aParam[1],aParam[2],aParam[3],aParam[4],aParam[5],aParam[6],aParam[7],aParam[8]);
	}
	else
	{
		CacheLog(LOGDEF_INST(RedeemScript),"AE,U[%08X,%08X],T(%d),K(%d),P(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
			rUser.GetGuid().GetHigh32Value(),
			rUser.GetGuid().GetLow32Value(),
			nType,minIndex,aParam[0],aParam[1],aParam[2],aParam[3],aParam[4],aParam[5],aParam[6],aParam[7],aParam[8]);
	}

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*==========================================================================
功能说明：按照序号获取GM工具补偿相关信息
参数个数：2
参数说明：
		1._nUserID	玩家ID 
返回值个数：10
返回值说明：
		1.类型
		2~10.九个数值
注意事项：
	见Script_Define.h
============================================================================*/
int C_GetGMRedeemInfo(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	//AssertLuaNumberParam(L, 2);
	int _nUserID		= static_cast<int>(lua_tonumber(L, 1));
	//int nIndex		= static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_USER_DEFINE
	
	lua_pushnumber(L, rUser.GetGMRedeem().m_data[0].m_rdType);
	for (int i = 0; i< MAX_REDEEM_PARAM; ++i)
	{
		lua_pushnumber(L, rUser.GetGMRedeem().m_data[0].m_rdParam[i]);
	}
	return MAX_REDEEM_PARAM+1;

// 	if ( nIndex >= 0 && nIndex < MAX_REDEEM_NUM )
// 	{
// 		lua_pushnumber(L, rUser.GetGMRedeem().m_data[nIndex].m_rdType);
// 		for (int i = 0; i< MAX_REDEEM_PARAM; ++i)
// 		{
// 			lua_pushnumber(L, rUser.GetGMRedeem().m_data[nIndex].m_rdParam[i]);
// 		}
// 		return MAX_REDEEM_PARAM+1;
// 	}
	__END_USER_DEFINE
	__END_LUA

	//default
	for (int i = 0 ;i < MAX_REDEEM_PARAM+1; ++i)
	{
		lua_pushnumber(L,invalid_id);
	}
	return MAX_REDEEM_PARAM+1;	
}

/*==========================================================================
功能说明：按照类型设置数据
参数个数：4
参数说明：
		1._nUserID	玩家ID 
		2.nType	类型
		3.nIndex 序号
		4.nValue 数值
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
============================================================================*/
int C_SetGMRedeemInfo(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int _nUserID		= static_cast<int>(lua_tonumber(L, 1));
	int nType		= static_cast<int>(lua_tonumber(L, 2));
	int nIndex		= static_cast<int>(lua_tonumber(L, 3));
	int nValue		= static_cast<int>(lua_tonumber(L, 4));
	__BEGIN_USER_DEFINE

	if (nIndex >= 0 && nIndex < MAX_REDEEM_PARAM)
	{
		if (rUser.GetGMRedeem().m_data[0].m_rdType == nType)
		{
			rUser.GetGMRedeem().m_data[0].m_rdParam[nIndex] = nValue;
			CacheLog(LOGDEF_INST(RedeemScript),"GMTool:S,U[%08X,%08X],T(%d),K(%d),V(%d)",
				rUser.GetGuid().GetHigh32Value(),
				rUser.GetGuid().GetLow32Value(),				
				nType,
				nIndex,
				nValue);

			return 0;
		}
	}
	
// 	if ( nIndex >= 0 && nIndex < MAX_REDEEM_PARAM )
// 	{
// 		for (int mIndex = 0 ; mIndex < MAX_REDEEM_NUM; ++mIndex )
// 		{
// 			if ( rUser.GetGMRedeem().m_data[mIndex].m_rdType == nType )
// 			{
// 				rUser.GetGMRedeem().m_data[mIndex].m_rdParam[nIndex] = nValue;
// 
// 				CacheLog(LOGDEF_INST(RedeemScript),"GMTool:S,U[%08X,%08X],T(%d),K(%d),V(%d)",
// 					rUser.GetGuid().GetHigh32Value(),
// 					rUser.GetGuid().GetLow32Value(),				
// 					nType,
// 					nIndex,
// 					nValue);
// 
// 				return 0;
// 			}
// 		}
// 	}
	CacheLog(LOGDEF_INST(RedeemScript),"GMTool:SE,U[%08X,%08X],T(%d),K(%d),V(%d)",
		rUser.GetGuid().GetHigh32Value(),
		rUser.GetGuid().GetLow32Value(),				
		nType,
		nIndex,
		nValue);

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

 /*==========================================================================
功能说明：增加一个补偿,替换最小type的其他补偿，如果有了就不会再增加。
参数个数：8
参数说明：
		1._nUserID	玩家ID 
		2.nType	类型
		3~11 nParam 参数 可有可无		
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
============================================================================*/
int C_AddGMRedeem(lua_State *L)
{
	__BEGIN_LUA

	bsarray<int, MAX_REDEEM_PARAM> aParam;
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
	AssertLuaNumberParam(L, 11);

	int _nUserID		= static_cast<int>(lua_tonumber(L, 1));
	int nType		= static_cast<int>(lua_tonumber(L, 2));
	for (int nIndex = 0; nIndex < MAX_REDEEM_PARAM; ++nIndex)
	{
		aParam[nIndex] = static_cast<int>(lua_tonumber(L, 3+nIndex));
	}
	
	__BEGIN_USER_DEFINE

	if (nType < 0)
	{
		CacheLog(LOGDEF_INST(RedeemScript),"GMTool:InvalidType,U[%08X,%08X],T(%d),P(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
			rUser.GetGuid().GetHigh32Value(),
			rUser.GetGuid().GetLow32Value(),
			nType,aParam[0],aParam[1],aParam[2],aParam[3],aParam[4],aParam[5],aParam[6],aParam[7],aParam[8]);
		return 0;
	}

	// GM工具先只支持一个
	for (int mIndex = 0 ; mIndex < MAX_REDEEM_NUM; ++mIndex )
	{
		//如果有相同直接放弃
		if (nType == rUser.GetGMRedeem().m_data[mIndex].m_rdType)
		{
			return 0;
		}
	}

	// 先将现有的后移
	for (int i = MAX_REDEEM_NUM - 1; i > 0; --i)
	{
		rUser.GetGMRedeem().m_data[i].CopyFrom(rUser.GetGMRedeem().m_data[i - 1]);
	}

	// 再覆盖第0个位置
	rUser.GetGMRedeem().m_data[0].m_rdType = nType;
	for (int nIndex = 0; nIndex < MAX_REDEEM_PARAM; ++nIndex)
	{
		rUser.GetGMRedeem().m_data[0].m_rdParam[nIndex] = aParam[nIndex];
	}

	CacheLog(LOGDEF_INST(RedeemScript),"GMTool:A,U[%08X,%08X],T(%d),P(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
		rUser.GetGuid().GetHigh32Value(),
		rUser.GetGuid().GetLow32Value(),
		nType,aParam[0],aParam[1],aParam[2],aParam[3],aParam[4],aParam[5],aParam[6],aParam[7],aParam[8]);

	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*==========================================================================
功能说明：得到当前日期信息
参数个数：0
参数说明：无
返回值个数：1
返回值说明：日期数字
注意事项：
	见Script_Define.h
============================================================================*/
int C_GetTime2Day(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	lua_pushnumber(L, gTimeManager.Time2Day());
	return 1;
	__END_LUA
	lua_pushnumber(L, invalid_id);
	return 1;
}

/*==========================================================================
功能说明：得到玩家的创建角色时间（anis）
参数个数：1
参数说明：
	1._nUserID  玩家的ObjId
返回值个数：1
返回值说明：创建角色的Ansi时间
注意事项：
	见Script_Define.h
============================================================================*/
int C_GetRoleCreateTime(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_USER_DEFINE
	lua_pushnumber(L, static_cast<uint32>(rUser.GetCreateRoleTime()));
	return 1;
	__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, -1);
	return 1;
}

/*==========================================================================
功能说明：根据ansi时间得到多种日期表示
参数个数：1
参数说明：
	1.ansiTime Ansi时间
返回值个数：9
返回值说明：
	年、月、日、时、分、秒、星期、年天
注意事项：
	见Script_Define.h
============================================================================*/
int C_GetTimeDataByAnsi(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	uint32 ansiTime = static_cast<int>(lua_tonumber(L, 1));
	tm tmStruct;
	_localtime(ansiTime, tmStruct);
	lua_pushnumber(L, tmStruct.tm_year+1900);	//2xxx
	lua_pushnumber(L, tmStruct.tm_mon+1);		//1-12
	lua_pushnumber(L, tmStruct.tm_mday);		//1-31
	lua_pushnumber(L, tmStruct.tm_hour);		//0-23
	lua_pushnumber(L, tmStruct.tm_min);			//0-59
	lua_pushnumber(L, tmStruct.tm_sec);			//0-59
	lua_pushnumber(L, tmStruct.tm_wday);		//0-6
	lua_pushnumber(L, tmStruct.tm_yday);		//0-365
	return 8;
	__END_LUA
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);

	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);

	lua_pushnumber(L, invalid_id);
	lua_pushnumber(L, invalid_id);
	return 8;
}

/*----------------------------------------------------------------------
功能说明：发送简单系统频道消息 只有字符串 没链接
参数个数：1
参数说明：
		1.strNotice 
返回值个数：0
返回值说明：无
注意事项：
	见Script_Define.h
*/
int C_BroadcastSampleSystemChat(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaStringParam(L, 1);
	const char* strNotice	= lua_tostring(L, 1);
	SceneInterface::BroadCastSampleSystemChat2Scene(strNotice);
	return 0;

	__END_LUA
	return 0;
}

int C_BraodcastSystemChat_PlayerInfo(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaStringParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	const char* strNotice	= lua_tostring(L, 1);
	int guidLow = static_cast<int>(lua_tonumber(L, 2));
	int guidHigh = static_cast<int>(lua_tonumber(L, 3));

	Packets::GC_CHAT_PAK pak;
	pak.m_PacketData.set_chattype(GC_CHAT::CHAT_TYPE_SYSTEM);
	pak.m_PacketData.set_chatinfo(strNotice);
	pak.m_PacketData.add_linktype(GC_CHAT::LINK_TYPE_PLAYERINFO);
	pak.m_PacketData.add_intdata(guidHigh);
	pak.m_PacketData.add_intdata(guidLow);
	SceneInterface::BroadCastChatMsg2Scene(pak.m_PacketData);

	__END_LUA
	return 0;
}

int C_SendWorldBossChallenge2Service(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);	

	int winTeamId	= static_cast<int>(lua_tonumber(L, 1));
	int loseTeamId	= static_cast<int>(lua_tonumber(L, 2));

	WorldBossTeamChallengeResultMsgPtr msg = POOLDEF_NEW(WorldBossTeamChallengeResultMsg);
	AssertEx(msg, "");
	msg->m_nLoseTeam = loseTeamId;
	msg->m_nWinTeam = winTeamId;
	SendMessage2Srv(ServiceID::TEAM, msg);
	
	return 0;

	__END_LUA
		return 0;
}

int C_SetLingYunKuCopySceneResult(lua_State *L)
{

	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);

	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nResult = static_cast<int>(lua_tonumber(L, 2));
	int nStar = static_cast<int>(lua_tonumber(L, 3));
	int nScore = static_cast<int>(lua_tonumber(L, 4));
	int nTime = static_cast<int>(lua_tonumber(L, 5));

		__BEGIN_USER_DEFINE
		if (rScene.IsCopyScene())
		{
			CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
			rCopyScene.SetResult(nResult);
			rCopyScene.SetStar(nStar);
			rCopyScene.SetScore(nScore);
			if (nResult == 1)
			{
				rUser.CreateCopySceneReward();
				rUser.AddWinCopySceneNumber(rCopyScene.GetSceneClassID(),rCopyScene.GetDifficulty(),rCopyScene.GetPlayType()==1?true:false);
				rUser.AddCurSweepLevel(rCopyScene.GetSceneClassID(),rCopyScene.GetDifficulty(),rCopyScene.GetPlayType()==1?true:false);
				//做帮贡奖励
				rUser.AddMultipleCopySceneGuidReward();
				rUser.AddMultipleCopySceneMasterReward();

				if (rCopyScene.GetSceneClassID() == CopySceneTimesLimitedID::TLI_LINGYUNKU)
				{
					int nPreDiffcult = rUser.GetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_DIFFCULT);
					int nCurDiffcult = rCopyScene.GetCopySceneDifficulty();
					int nPreTime = rUser.GetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_TIME);
					//记录最好的成绩
					bool bUpdateRank = false;
					if ( nPreDiffcult < nCurDiffcult)
					{
						rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_TIME,nTime);	//记录通关时间
						rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_DIFFCULT,nCurDiffcult);	//记录通关难度
						bUpdateRank = true;
					}
					else if ( nPreDiffcult == nCurDiffcult)
					{
						if ( nPreTime > nTime)
						{
							rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_TIME,nTime);	//记录通关时间
							rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_DIFFCULT,nCurDiffcult);	//记录通关难度
							bUpdateRank = true;
						}
					}
					if (bUpdateRank)
					{
						InsertLingYunKuRankMsgPtr msgPtr = POOLDEF_NEW(InsertLingYunKuRankMsg);
						AssertEx(msgPtr, "");
						msgPtr->m_rankElemInfo.CleanUp();
						msgPtr->m_rankElemInfo.SetGuid(rUser.GetGuid());
						msgPtr->m_rankElemInfo.SetName(rUser.GetName());
						msgPtr->m_rankElemInfo.SetLevel(rUser.GetLevel());
						msgPtr->m_rankElemInfo.SetDiffcult(nCurDiffcult);
						msgPtr->m_rankElemInfo.SetTime(nTime);
						SendMessage2Srv(ServiceID::RANK, msgPtr);
					}
				}
				rUser.AddCopySceneRewardEP();
			}

			// 副本成功通关后更新最高通关难度
			if(nResult == 1 || nResult == 3)
			{
				rUser.UpdateAccomplishDifficult(rCopyScene.GetSceneClassID(),
					rCopyScene.GetDifficulty(),
					rCopyScene.GetPlayType()==CopyScenePlayType::SINGLE?true:false
					);
			}

			rUser.SendCopySceneReward();
			//记录CMBI日志
			rUser.CMBI_CacheLog_CompleteCopyScene(rCopyScene);
		}

		// 记录日志
		AuditLog(LOGDEF_INST(Audit_CopyScene),"CSR", rUser.GetGuid(), "SID=%d \1 DY=%d \1 SE=%d \1 L=%d \1 RT=%d \1 SR=%d \1 SE=%d",
			rUser.GetSceneClassID(),
			rScene.GetCopySceneDifficulty(),
			rScene.GetCopyScenePlayType(),
			rScene.GetLevel(),
			nResult,
			nStar,
			nScore);
		lua_pushnumber(L, 1);
		return 1;

		__END_USER_DEFINE
	__END_LUA
	lua_pushnumber(L, 0);
	return 1;
}
int C_GetWeek(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	lua_pushnumber(L, gTimeManager.GetWeek());
	return 1;

	__END_LUA
	return 0;
}

int C_CreateTeleportInScene(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);

	float fPosX		= static_cast<float>(lua_tonumber(L, 1));
	float fPosZ		= static_cast<float>(lua_tonumber(L, 2));
	float fTargetX	= static_cast<float>(lua_tonumber(L, 3));
	float fTargetZ	= static_cast<float>(lua_tonumber(L, 4));
	__BEGIN_SCENE_DEFINE
	TeleportInScene teleport;
	teleport.m_fPosX = fPosX;
	teleport.m_fPosZ = fPosZ;
	teleport.m_fTargetX = fTargetX;
	teleport.m_fTargetZ = fTargetZ;

	lua_pushnumber(L, rScene.CreateTeleportInScene(teleport));
	return 1;
	__END_SCENE_DEFINE

	__END_LUA
	lua_pushnumber(L, -1);
	return 1;
}

int C_RemoveTeleportInScene(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);

	int nTeleportID = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_SCENE_DEFINE
	rScene.RemoveTeleportInScene(nTeleportID);
	__END_SCENE_DEFINE

	__END_LUA
	return 0;
}

int C_SyncTeleportInSceneToUser(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);

	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_USER_DEFINE
	rScene.SyncAllTeleportInSceneToUser(rUser.GetGuid());
	__END_USER_DEFINE
	__END_LUA
	return 0;
}


/*----------------------------------------------------------------------
功能说明：判断场景中某个点是否可走 
参数个数：2
参数说明：
1，posX
2，posZ
返回值个数：1
返回值说明：
	1.有阻挡
	0无阻挡
*/
int C_IsObstacle( lua_State *L )
{
	__BEGIN_LUA
		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);

	float fPosX = static_cast<float>(lua_tonumber(L, 1));
	float fPosZ = static_cast<float>(lua_tonumber(L, 2));
	__BEGIN_SCENE_DEFINE
	const SceneObstacle& rSceneObstacle = rScene.GetSceneObstacle();
	if ( rSceneObstacle.GetObstacleValue(ScenePos(fPosX, fPosZ)) == ObstacleValue::WALKABLE )
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	__END_SCENE_DEFINE
		__END_LUA
		lua_pushnumber(L, 1);
		return 1;
}
/*----------------------------------------------------------------------
功能说明：给客户端传当前副本剩余时间  LMY
参数个数：2
参数说明：_userId,返回值
返回值个数：1
返回值说明：
	1.当前副本当前剩余时间

注意事项：
	见Script_Scene.h
*/
int C_SetCopySceneTimer( lua_State *L )
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	int nTimer = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_USER_DEFINE

		Packets::GC_PLAY_FBELAPSETIME_PAK pak;
	pak.m_PacketData.set_elapsetime(nTimer);
	rUser.SendPacket(pak);
	return 0;

	__END_USER_DEFINE
	__END_LUA
	return 0;	
}

/*----------------------------------------------------------------------
功能说明：将副本区域比较远的下一波怪的位置发给玩家
参数个数：3
参数说明：_userId, posX, posZ
返回值个数：0
返回值说明：无

注意事项：
	见Script_Scene.h
*/
int C_SyncCopySceneNextWaveMonsterInfoToUser(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3)

	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE
		rUser.SendCopySceneNextWaveMonsterInfo(fPosX, fPosZ);
		return 0;
	__END_USER_DEFINE
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：四大恶人副本失败，返还精英次数
参数个数：0
参数说明：无
		
返回值个数：0
返回值说明：无
注意事项：
	无
*/

int C_FourVillainCopySceneFail(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	__BEGIN_SCENE_DEFINE
	if (rScene.IsCopyScene())
	{
		CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
		int nDiffcult = rCopyScene.GetCopySceneDifficulty();
		if (nDiffcult == CopySceneDifficulty::LEVEL3)
		{
			FailSuperVillainCopySceneMsgPtr msg = POOLDEF_NEW(FailSuperVillainCopySceneMsg);
			AssertEx(msg, "");
			msg->m_UserGuid = invalid_guid64;
			SendMessage2Srv(ServiceID::FOURVILLAIN, msg);
		}
	}
	return 0;
	__END_SCENE_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：四大恶人在准备刷第2,3,4,5,7,8波怪的时候，告知玩家此波怪物的刷新点。以便自动挂机状态可以跑过去
参数个数：3
参数说明：
		1._nUserID 玩家GUIG
		2. fPosX X坐标 
		3. fPosZ Y坐标
返回值个数：0
返回值说明：无
注意事项： 无
*/

int C_SyncVillainCopysceneMonsterInfoToClient(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3)

		int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_USER_DEFINE
		rUser.SyncVillainCopysceneMonsterInfoToClient(fPosX, fPosZ);
	return 0;
	__END_USER_DEFINE
		__END_LUA
		return 0;
}

/*----------------------------------------------------------------------
功能说明：判断玩家当前所在场景是否是帮会领地 和 是否在自己所属帮会的领地
参数个数：1
参数说明：_nUserID 玩家的ObjID
		
返回值个数：2
返回值说明：1 - 玩家当前所在场景是否是帮会属地  2- 玩家是否在自己所属帮会的领地
注意事项：
	无
*/
int C_IsMyGuildManor(lua_State *L)
{
__BEGIN_LUA
	AssertEx(L, "");
	int _nUserID = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_USER_DEFINE
		bool bIsManor = false;
		bool bIsMyGuildManor = false;
		if (rScene.IsManorScene())
		{
			bIsManor = true;
			ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
			if (rUser.IsHaveGuild())
			{
				if (manor.GetGuildGUID() == rUser.GetGuildGuid())
				{
					bIsMyGuildManor = true;
				}
			}
		}
		lua_pushboolean(L, bIsManor);
		lua_pushboolean(L, bIsMyGuildManor);
		return 2;
	__END_USER_DEFINE
__END_LUA
	lua_pushboolean(L, false);
	lua_pushboolean(L, false);
	return 2;
}
/*----------------------------------------------------------------------
功能说明： 根据场景id返回场景名字
参数个数：1
参数说明：
	
返回值个数：0
返回值说明：

注意事项：
	见Script_Define.h
*/
int C_GetSceneNameByID(lua_State *L)
{
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int nSceneClassID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_LUA
	const Table_SceneClass *pScene = GetTable_SceneClassByID(nSceneClassID);
	if (null_ptr != pScene)
	{
		lua_pushstring(L, pScene->GetName());
		return 1;
	}	
	__END_LUA

	lua_pushstring(L, "");	
	return 1;
}

/*----------------------------------------------------------------------
功能说明：召唤英魂
参数个数：0
参数说明：
		
返回值个数：0
返回值说明：
注意事项：
	无
*/
int C_CreateHeroSoul(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	AssertLuaNumberParam(L, 5);
	AssertLuaNumberParam(L, 6);
	int guildGuidH = static_cast<int>(lua_tonumber(L, 1));
	int guildGuidL = static_cast<int>(lua_tonumber(L, 2));
	int heroId = static_cast<int>(lua_tonumber(L, 3));
	int posX = static_cast<int>(lua_tonumber(L, 4));
	int posZ = static_cast<int>(lua_tonumber(L, 5));
	int level = static_cast<int>(lua_tonumber(L, 6));
	int64 guildGuid(guildGuidH, guildGuidL);


	__BEGIN_SCENE_DEFINE
	if(rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);

		const Table_HeroSoul* npc = GetTable_HeroSoulByID(heroId);
		if(npc)
		{
			int npcDataID = npc->GetNpcId();
			float fPosX = (float)posX;
			float fPosZ = (float)posZ;

			XBTX_NPCNAME npcName;
			const Table_RoleBaseAttr* pNPCData = GetTable_RoleBaseAttrByID(npcDataID);
			if(pNPCData)
			{
				npcName = pNPCData->GetName();
			}
			for (int i = 0; i < npc->GetSummonNum(); i++)
			{
				Obj_NpcPtr NpcPtr = manor.CreateHeroSoulNpc(heroId, npcDataID, ScenePos(fPosX + i * 0.5f, fPosZ + i * 0.5f), guildGuid, level);
			}

			CacheLog(LOGDEF_INST(Guild),"SummonHeroSoulScript,GuildGUID=%08X,%08X,OP=%d,HEROID=%d",
				guildGuidH, guildGuidL, (int)OP_HEROSOUL_SUMMON_SUCCESS, heroId);
			//lua_pushnumber(L, NpcPtr->GetID());
			return 2;
		}
	}
	return 2;
	__END_SCENE_DEFINE
	__END_LUA
	return 2;

}


/*----------------------------------------------------------------------
功能说明：将领地内玩家全部传出场景
参数个数：0
参数说明：
		
返回值个数：0
返回值说明：
注意事项：
	无
*/
int C_CleanManorScene2Scene(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	tint8 _nSceneClassID = static_cast<tint8>(lua_tonumber(L, 1));
	__BEGIN_SCENE_DEFINE
	if (rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
		
		// 扫描出当前场景所有玩家
		UserRefCont Cont;
		manor.Scan_User_All(Cont);
		for (int i = 0; i < Cont.Size(); i++)
		{
			Obj_User &rUser = Cont[i];
			rUser.ChangeScene_ExitManorScene(_nSceneClassID);
		}

	}
	return 0;
	__END_SCENE_DEFINE
	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
功能说明：创建NPC
参数个数：3
参数说明：
	1.归属帮派 guildGuidH
	2.归属帮派 guildGuidL
	3.帮派等级 level
	4.NPC列索引 index
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
*/
int C_CreateManorNPC(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	AssertLuaNumberParam(L, 4);
	int guildGuidH = static_cast<int>(lua_tonumber(L, 1));
	int guildGuidL = static_cast<int>(lua_tonumber(L, 2));
	int level = static_cast<int>(lua_tonumber(L, 3));
	int index = static_cast<int>(lua_tonumber(L, 4));
	int64 guildGuid(guildGuidH, guildGuidL);
	__BEGIN_SCENE_DEFINE
	if(rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);

		const Table_DominateTheWorldNpc* npc = null_ptr;
		for(int i = 0; i < GetTable_DominateTheWorldNpcCount(); ++i)
		{
			const Table_DominateTheWorldNpc* pTab = GetTable_DominateTheWorldNpcByIndex(i);
			if(pTab)
			{
				if(pTab->GetGuildLevel() == level && pTab->GetActivtyType() == manor.GetManorSceneActivityType())
				{
					npc = pTab;
				}
			}
		}
		if(npc
			&& index > -1
			&& index < npc->getNpcIDCount()
			&& index < npc->getNpcXCount()
			&& index < npc->getNpcZCount()
			)
		{
			int npcDataID = npc->GetNpcIDbyIndex(index);
			float fPosX = npc->GetNpcXbyIndex(index);
			float fPosZ = npc->GetNpcZbyIndex(index);
			float fFaceDire = npc->GetNPCFacebyIndex(index);
			XBTX_NPCNAME npcName;
			const Table_RoleBaseAttr* pNPCData = GetTable_RoleBaseAttrByID(npcDataID);
			if(pNPCData)
			{
				npcName = pNPCData->GetName();
			}

			Obj_NpcPtr NpcPtr = manor.CreateManorSceneNpc(npcDataID, ScenePos(fPosX, fPosZ), fFaceDire, index, guildGuid);
			if(NpcPtr)
			{

				lua_pushnumber(L, NpcPtr->GetID());
				lua_pushstring(L, NpcPtr->GetName().GetCText());
				return 2;
			}
		}
	}
	lua_pushnumber(L, -1);
	lua_pushstring(L, "");
	return 2;
	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	lua_pushstring(L, "");
	return 2;
}

/*----------------------------------------------------------------------
功能说明：获取参战帮会数量
参数个数：0
参数说明：
返回值个数：1
返回值说明：
	1.返回本期参战帮会数量
注意事项：
*/
int C_GetDomainTheWorldGuildCount(lua_State* L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	int num = static_cast<int>(lua_tonumber(L, 1));
	if(num < 0)
	{
		num = 0;
	}
	__BEGIN_SCENE_DEFINE
	if(rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
		int count = manor.GetDominateTheWorldGuildsCount();
		lua_pushnumber(L, count);
		return 1;
	}
	lua_pushnumber(L, 0);
	return 1;
	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, 0);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：获取雄霸天下帮会信息
参数个数：3
参数说明：
	1.index 获取第N个帮会信息
返回值个数：
返回值说明：4
	1.返回帮会guid，第一个为防守帮会，其他为进攻帮会
注意事项：
*/
int C_GetDomainTheWorldGuildInfo(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int index = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_SCENE_DEFINE
	if(rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
		DominateTheWorldInfo info = manor.GetDominateTheWorldGuild(index);
		if(info.m_GuildGuid != invalid_guid64)
		{
			lua_pushnumber(L, info.m_GuildGuid.GetHigh32Value());
			lua_pushnumber(L, info.m_GuildGuid.GetLow32Value());
			lua_pushnumber(L, info.m_GuildLevel);
			lua_pushboolean(L, info.m_isLastWeekKing);
			return 4;
		}
	}
	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushboolean(L, false);
	return 4;
	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushboolean(L, false);
	return 4;
}
/*----------------------------------------------------------------------
功能说明：向帮会频道广播消息
参数个数：
参数说明：
	1.guildGuidH 帮会guild高位
	2.guildGuidL 帮会guild低位
	3.msg 消息
返回值个数：0
返回值说明：
注意事项：
*/
int C_BroadcastNotice2Guild(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaStringParam(L, 3);
	int guildGuidH = static_cast<int>(lua_tonumber(L, 1));
	int guildGuidL = static_cast<int>(lua_tonumber(L, 2));
	const char* strNotice	= lua_tostring(L, 3);
	int64 guildGuid(guildGuidH,guildGuidL);
	SceneInterface::BroadCastNotice2Guid(guildGuid, strNotice);
	return 0;
	__END_LUA
	return 0;
}

int C_BroadcastRollNotice(lua_State *L)
{
	__BEGIN_LUA
	AssertLuaStringParam(L, 1);
	const char* strNotice	= lua_tostring(L, 1);
	SceneInterface::BroadcastRollNotice(strNotice);
	return 0;
	__END_LUA
	return 0;
}

int C_BroadCastSampleSystemChat2Scene(lua_State *L)
{
	__BEGIN_LUA
	AssertLuaStringParam(L, 1);
	const char* strNotice	= lua_tostring(L, 1);
	SceneInterface::BroadCastSampleSystemChat2Scene(strNotice);
	return 0;
	__END_LUA
	return 0;
}

/*----------------------------------------------------------------------
功能说明：创建领地任务NPC
参数个数：3
参数说明：
	1.NPCDataID
	2.x坐标
	3.z坐标
返回值个数：1
返回值说明：
	1.NPCObjID
注意事项：
	见Script_Define.h
*/
int C_CreateManorMissionNpcIfNeeded(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int nNPCDataID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_SCENE_DEFINE

		if(rScene.IsManorScene())
		{
			ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
			if (manor.GetIsOwnSJD() == true)
			{
				Obj_NpcPtr NpcPtr = rScene.CreateNpc(nNPCDataID, ScenePos(fPosX, fPosZ), false);
				if (NpcPtr)
				{
					lua_pushnumber(L, NpcPtr->GetID());
					return 1;
				}	
			}
		}
		lua_pushnumber(L, -1);
		return 1;

	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}

/*----------------------------------------------------------------------
功能说明：创建武林至尊
参数个数：0
参数说明：
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_CreateWLZZ(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");

	__BEGIN_SCENE_DEFINE

		if(rScene.IsMainScene())
		{
			ReqCreateWLZZNPCMsgPtr msg = POOLDEF_NEW(ReqCreateWLZZNPCMsg);
			AssertEx(msg,"");
			msg->m_nSceneClassId = rScene.GetSceneClassID();
			msg->m_nSceneInstanceId = rScene.GetSceneInstID();
			SendMessage2Srv(ServiceID::GUILD, msg);
		}
		lua_pushnumber(L, -1);
		return 1;

	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	return 1;
}
/*----------------------------------------------------------------------
功能说明：获取成王败寇帮会信息
参数个数：0
参数说明：
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_GetCWBKGuildInfo(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int index = static_cast<int>(lua_tonumber(L, 1));
	__BEGIN_SCENE_DEFINE
	if(rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
		CWBKGuildInfo info = manor.GetCWBKGuild(index);
		if(info.m_GuildGuid != invalid_guid64)
		{
			lua_pushnumber(L, info.m_GuildGuid.GetHigh32Value());
			lua_pushnumber(L, info.m_GuildGuid.GetLow32Value());
			lua_pushnumber(L, info.m_GuildLevel);
			lua_pushnumber(L, info.m_nRound);
			return 4;
		}
	}
	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushboolean(L, -1);
	return 4;
	__END_SCENE_DEFINE
	__END_LUA

	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushnumber(L, -1);
	lua_pushboolean(L, -1);
	return 4;
}

/*----------------------------------------------------------------------
功能说明：攻方打死社稷鼎后
参数个数：0
参数说明：
返回值个数：0
返回值说明：
注意事项：
	见Script_Define.h
*/
int C_EndCWBK(lua_State *L)
{
	__BEGIN_LUA
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	int guildGuidH = static_cast<int>(lua_tonumber(L, 1));
	int guildGuidL = static_cast<int>(lua_tonumber(L, 2));
	__BEGIN_SCENE_DEFINE
	if(rScene.IsManorScene())
	{
		ManorScene& manor = dynamic_cast<ManorScene&>(rScene);
		int64 winGuildGuid(guildGuidH,guildGuidL);	
		manor.OnCWBKEnd(winGuildGuid);
	}
	return 0;
	__END_SCENE_DEFINE
	return 0;
	__END_LUA
	return 0;
}