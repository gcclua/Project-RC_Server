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
����˵��������ZombieUser
����������3
����˵����
	1.UserObjID
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵��������ZombieUser
����������3
����˵����
	1.UserObjID
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵����������Ӷ��
����������3
����˵����
	1.UserObjID
����ֵ������MERCENARY_MAX_HOLD
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵������������boss
����������0
����˵����

����ֵ������0
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵��������NPC
����������3
����˵����
	1.NPCDataID
	2.x����
	3.z����
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵��������NPC
����������4
����˵����
	1.NPCDataID
	2.x����
	3.z����
	4.level
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵�����������NPC
����������4
����˵����
	1._nUserID
	2.NPCDataID
	3.x����
	4.z����
	5.level
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵����ɾ��NPC
����������1
����˵����
	1.NPCObjID
����ֵ������0
����ֵ˵����

ע�����
	��Script_Define.h
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
����˵����ɾ��ZombieUser
����������1
����˵����
	1.ObjID
����ֵ������0
����ֵ˵����

ע�����
	��Script_Define.h
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
����˵������ȡNPCDataID
����������1
����˵����
	1.NPCObjID
����ֵ������1
����ֵ˵����
	1.NPCDataID
ע�����
	��Script_Define.h
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
����˵����ɱ����ǰ�������ез�NPC
����������1
����˵����
	1.UserObjID
����ֵ������0
ע�����
	��Script_Define.h
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
����˵�����������������͵� ��Ҫ�Ǹ�����
����������2
����˵����
	1.UserObjID
	2.��ʾ/����
����ֵ������0
ע�����
	��Script_Define.h
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
����˵�����ж�NPC�Ƿ񳡾�������
����������1
����˵����
	1.NPCDataID
����ֵ������1
����ֵ˵����
	1.�Ƿ����У�bool��0��û�У�1���У�
ע�����
	��Script_Define.h
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
����˵�������������Ƹı侵ͷ�ٶ� ���ڸ�����boss���һ��ʱ������
����������2
����˵����
	1.UserObjID
	2.����
����ֵ������0
ע�����
	��Script_Define.h
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
����˵�������������Ƹı侵ͷ�ٶ� ���ڸ�����boss���һ��ʱ������
����������1
����˵����
	1.UserObjID
����ֵ������0
ע�����
	��Script_Define.h
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
����˵�������Ŷ�������
����������1
����˵����
	1.UserObjID
	2.����ID �ͻ�����ʱ��������
����ֵ������0
ע�����
	��Script_Define.h
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
����˵������ȡ�����ǵ��˻��Ƕ����淨
����������0
����˵����
����ֵ������1
����ֵ˵����
	1.�����淨ö�٣���CopyScenePlayType
ע�����
	��Script_Define.h
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
����˵������ȡ�����Ѷ�
����������0
����˵����
����ֵ������1
����ֵ˵����
	1.�����Ѷȣ���CopySceneDifficulty
ע�����
	��Script_Define.h
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
����˵����������ˢ��
����������3
����˵����1�ڼ��� 2����ȼ� 3����
����ֵ������1
����ֵ˵����
	1.1�ɹ���0ʧ��
ע�����
	��CopySceneNpc���
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
			// ���������ĩ����
			if (gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6)
			{
				nNpcIndex = 1;
			}
		}
		break;
	case CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI:
		{
			// ŭ������ʥ���ڴ��� ʥ�����ѹ�
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
					//	&& scID == CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI)//ŭ������ʥ���ڴ���
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
����˵������ȡ�����Ļ�����Ϣ
����������1
����˵��������ID
����ֵ������8
����ֵ˵����
	1.�Ѷ�
	2.���˻����
	3.����
	4.�������
	5.������ʼʱ��
	6.�Ǽ�
	7.����ͳ��
	8.�����ֵ�����
ע�����
	��CopyScene.h
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
����˵�����õ����������ĵжԹֵ�����
����������1
����˵������󲨴�
����ֵ������1
����ֵ˵����
	1. NPC����
ע�����
	��CopyScene.h
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
				// ���������ĩ����
				if (gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6)
				{
					nNpcIndex = 1;
				}
			}
			break;
		case CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI:
			{
				// ŭ������ʥ���ڴ��� ʥ�����ѹ�
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
����˵�����ж��Ƿ�Ϊ����NPC
����������1
����˵����NPC��ObjId
����ֵ������1
����ֵ˵����
	1. �Ƿ�˸�����NPC��ͨ��C_CreateCopySceneNpc������CopySceneNpc.txt��������
ע�����
	��CopyScene.h
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
				// ���������ĩ����
				if (gTimeManager.GetWeek() == 0 || gTimeManager.GetWeek() == 6)
				{
					nNpcIndex = 1;
				}
			}
			break;
		case CopySceneTimesLimitedID::TLI_JIANZONGLUNHUI:
			{
				// ŭ������ʥ���ڴ��� ʥ�����ѹ�
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
����˵������ȡ�����Ļ�����Ϣ
����������4
����˵����_userId,����ֵ���Ǽ�������
����ֵ������1
����ֵ˵����
	1.�Ƿ�ɹ�

ע�����
	��CopyScene.h
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
		//nResult  1��ʾ�ɹ��ҽ���   2��ʾʧ���ҽ���  3��ʾ�ɹ����ǲ�����
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

	// 		if (rCopyScene.GetPlayType() == CopyScenePlayType::SINGLE)	//����
	// 		{
				//�������
				rUser.CreateCopySceneReward();
				
				rUser.AddWinCopySceneNumber(rCopyScene.GetSceneClassID(),rCopyScene.GetDifficulty(),rCopyScene.GetPlayType()==1?true:false);	
				//���ﹱ����
				rUser.AddMultipleCopySceneGuidReward();
				rUser.AddMultipleCopySceneMasterReward();
	// 		}
	// 		else	//�������е��˷���
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
			//��¼CMBI��־
			rUser.CMBI_CacheLog_CompleteCopyScene(rCopyScene);
		}
		
		if (nResult == 3)
		{
			rUser.SendCopySceneReward();	
		}

		// �����ɹ�ͨ�غ�������ͨ���Ѷ�
		if(nResult == 1 || nResult == 3)
		{
			rUser.UpdateAccomplishDifficult(rCopyScene.GetSceneClassID(),
											rCopyScene.GetDifficulty(),
											rCopyScene.GetPlayType()==CopyScenePlayType::SINGLE?true:false
											);
		}

		
	}


	// ��¼��־
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
����˵������ȡ����ɨ����ػ�����Ϣ
����������4
����˵����_userId,����ֵ���Ѷȣ���ɨ��ģʽ
����ֵ������1
����ֵ˵����
	1.�Ƿ�ɹ�

ע�����
	��CopyScene.h
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
			//���
			if (nStar>=5)
			{
				rUser.AddCurSweepLevel(rScene.GetSceneClassID(),nDiffcult,rCopyScene.GetPlayType()==1?true:false);
			}
		}
		// ��¼��־
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
����˵������ȡ���
����������0
����˵����
����ֵ������1
����ֵ˵����
�������
ע�����
	��CopyScene.h
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
����˵�����������񰴲���ˢ��
����������3
����˵����1�ڼ��� 2����ȼ�
����ֵ������2
����ֵ˵����
	1.1�ɹ���0ʧ��
	2.����������
ע�����
	��CopySceneNpc���
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
����˵������ȡ������������
����������3
����˵�����Ѷ�
����ֵ������4
����ֵ˵����
	1.A,B,C,K

ע�����
	��CopyScene.h
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
����˵������ȡ���������Ǽ�
����������2
����˵�����Ѷȣ�����
����ֵ������1
����ֵ˵����
	1.star

ע�����
	��CopyScene.h
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
����˵������������ǰʱ��
����������0
����˵����
����ֵ������1
����ֵ˵����
�������
ע�����
	��CopyScene.h
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
����˵�����õ���ǰ������ɨ���ȼ�
����������0
����˵����
����ֵ������1
����ֵ˵����
�������
ע�����
	��CopyScene.h
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
����˵����ɾ����ǰ����ָ��DataID��NPC
����������1
����˵����
	1.DataID
����ֵ������0
ע�����
	��Script_Define.h
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
����˵����ɾ����ǰ������NPC
����������
����˵����
����ֵ������0
ע�����
	��Script_Define.h
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
����˵�������òؾ���ʤ����Ϣ
����������4
����˵����_userId,����ֵ��������ʱ����ʱ
����ֵ������1
����ֵ˵����
	1.�Ƿ�ɹ�

ע�����
	��CopyScene.h
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
				rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_CANGJINGGERANK_TIME,nTime);	//��¼ͨ��ʱ��
				rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_CANGJINGGERANK_TIER,nTier, true);	//��¼ͨ�ز���
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
				
				//��ͨ�ؽ���
				//COPYSCENENAME name("�ؾ���");
				//rUser.CreateCopySceneSweepReward(name.GetCText(),nTier);
				rUser.CreateCopySceneRewardByID(nTier, 0);
				//�ƺ�
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


		// �����������
		rUser.MissionCangJingGe(nTier);
		

		// ��¼��־
		AuditLog(LOGDEF_INST(Audit_CopyScene),"CSR", rUser.GetGuid(), "SID=%d \1 RT=%d \1 TR=%d \1 TE=%d",
			rUser.GetSceneClassID(),
			nResult,
			nTier,
			nTime);

		//��¼CMBI��־
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
����˵��������DataID��ȡ��ǰ����NPC����
����������2
����˵����
	1.DataID
����ֵ������1
	1.Npc����
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵��������Χ��Ҽ�Buff
����������2
����˵����
	1.objID
	2.buffID
	3.fRadius
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵�������ø�������
����������1
����˵����
	1.TierID
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵�����õ���������Ӧ�ȼ�
����������1
����˵����
����ֵ������
����ֵ˵���������ȼ�
ע�����
	��Script_Define.h
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
����˵������������
����������6
����˵����
	����
����ֵ������
����ֵ˵����0
ע�����
	��Script_Define.h
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
����˵����ϵͳ���巢���ʼ�(����Ǯ����Ʒ��
����������7
����˵����
	nReceiverGUIDH	���GUID��λ
	nReceiverGUIDL	���GUID��λ
	szContent		�ʼ�����
	nMoneyType		����Ǯ����
	nMoneyValue		����Ǯ����
	nItemDataID		������ƷID
	nItemCount		������Ʒ����
	nItemBind		��Ʒ������
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵����ϵͳ���巢���ʼ�(����������
����������3
����˵����
	nReceiverGUIDH	���GUID��λ
	nReceiverGUIDL	���GUID��λ
	szContent		�ʼ�����
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵����ϵͳ���巢���ʼ�(����Ǯ��
����������5
����˵����
	nReceiverGUIDH	���GUID��λ
	nReceiverGUIDL	���GUID��λ
	szContent		�ʼ�����
	nMoneyType		����Ǯ����
	nMoneyValue		����Ǯ����
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵����ϵͳ���巢���ʼ�(����Ʒ��
����������5
����˵����
	nReceiverGUIDH	���GUID��λ
	nReceiverGUIDL	���GUID��λ
	szContent		�ʼ�����
	nItemDataID		������ƷID
	nItemCount		������Ʒ����
	nItemBind		������Ʒ������
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵�������֮�䷢�ʼ�
����������6
����˵����
	nSenderGUIDH	������GUID��λ
	nSenderGUIDL	������GUID��λ
	szSenderName	����������
	nReceiverGUIDH	�ռ���GUID��λ
	nReceiverGUIDL	�ռ���GUID��λ
	szContent		�ʼ�����
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵����������Ż�ȡ���������Ϣ
����������2
����˵����
		1._nUserID	���ID 
		2.nIndex	���
����ֵ������10
����ֵ˵����
		1.����
		2~10.�Ÿ���ֵ
ע�����
	��Script_Define.h
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
����˵��������������������
����������4
����˵����
		1._nUserID	���ID 
		2.nType	����
		3.nIndex ���
		4.nValue ��ֵ
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵��������һ������,�滻��Сtype������������������˾Ͳ��������ӡ�
����������8
����˵����
		1._nUserID	���ID 
		2.nType	����
		3~11 nParam ���� ���п���		
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
		//�������ֱͬ�ӷ���
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
����˵����������Ż�ȡGM���߲��������Ϣ
����������2
����˵����
		1._nUserID	���ID 
����ֵ������10
����ֵ˵����
		1.����
		2~10.�Ÿ���ֵ
ע�����
	��Script_Define.h
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
����˵��������������������
����������4
����˵����
		1._nUserID	���ID 
		2.nType	����
		3.nIndex ���
		4.nValue ��ֵ
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
����˵��������һ������,�滻��Сtype������������������˾Ͳ��������ӡ�
����������8
����˵����
		1._nUserID	���ID 
		2.nType	����
		3~11 nParam ���� ���п���		
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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

	// GM������ֻ֧��һ��
	for (int mIndex = 0 ; mIndex < MAX_REDEEM_NUM; ++mIndex )
	{
		//�������ֱͬ�ӷ���
		if (nType == rUser.GetGMRedeem().m_data[mIndex].m_rdType)
		{
			return 0;
		}
	}

	// �Ƚ����еĺ���
	for (int i = MAX_REDEEM_NUM - 1; i > 0; --i)
	{
		rUser.GetGMRedeem().m_data[i].CopyFrom(rUser.GetGMRedeem().m_data[i - 1]);
	}

	// �ٸ��ǵ�0��λ��
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
����˵�����õ���ǰ������Ϣ
����������0
����˵������
����ֵ������1
����ֵ˵������������
ע�����
	��Script_Define.h
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
����˵�����õ���ҵĴ�����ɫʱ�䣨anis��
����������1
����˵����
	1._nUserID  ��ҵ�ObjId
����ֵ������1
����ֵ˵����������ɫ��Ansiʱ��
ע�����
	��Script_Define.h
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
����˵��������ansiʱ��õ��������ڱ�ʾ
����������1
����˵����
	1.ansiTime Ansiʱ��
����ֵ������9
����ֵ˵����
	�ꡢ�¡��ա�ʱ���֡��롢���ڡ�����
ע�����
	��Script_Define.h
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
����˵�������ͼ�ϵͳƵ����Ϣ ֻ���ַ��� û����
����������1
����˵����
		1.strNotice 
����ֵ������0
����ֵ˵������
ע�����
	��Script_Define.h
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
				//���ﹱ����
				rUser.AddMultipleCopySceneGuidReward();
				rUser.AddMultipleCopySceneMasterReward();

				if (rCopyScene.GetSceneClassID() == CopySceneTimesLimitedID::TLI_LINGYUNKU)
				{
					int nPreDiffcult = rUser.GetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_DIFFCULT);
					int nCurDiffcult = rCopyScene.GetCopySceneDifficulty();
					int nPreTime = rUser.GetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_TIME);
					//��¼��õĳɼ�
					bool bUpdateRank = false;
					if ( nPreDiffcult < nCurDiffcult)
					{
						rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_TIME,nTime);	//��¼ͨ��ʱ��
						rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_DIFFCULT,nCurDiffcult);	//��¼ͨ���Ѷ�
						bUpdateRank = true;
					}
					else if ( nPreDiffcult == nCurDiffcult)
					{
						if ( nPreTime > nTime)
						{
							rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_TIME,nTime);	//��¼ͨ��ʱ��
							rUser.SetCommonData(USER_COMMONDATA::CD_COPYSCENE_LINGYUNKU_DIFFCULT,nCurDiffcult);	//��¼ͨ���Ѷ�
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

			// �����ɹ�ͨ�غ�������ͨ���Ѷ�
			if(nResult == 1 || nResult == 3)
			{
				rUser.UpdateAccomplishDifficult(rCopyScene.GetSceneClassID(),
					rCopyScene.GetDifficulty(),
					rCopyScene.GetPlayType()==CopyScenePlayType::SINGLE?true:false
					);
			}

			rUser.SendCopySceneReward();
			//��¼CMBI��־
			rUser.CMBI_CacheLog_CompleteCopyScene(rCopyScene);
		}

		// ��¼��־
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
����˵�����жϳ�����ĳ�����Ƿ���� 
����������2
����˵����
1��posX
2��posZ
����ֵ������1
����ֵ˵����
	1.���赲
	0���赲
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
����˵�������ͻ��˴���ǰ����ʣ��ʱ��  LMY
����������2
����˵����_userId,����ֵ
����ֵ������1
����ֵ˵����
	1.��ǰ������ǰʣ��ʱ��

ע�����
	��Script_Scene.h
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
����˵��������������Ƚ�Զ����һ���ֵ�λ�÷������
����������3
����˵����_userId, posX, posZ
����ֵ������0
����ֵ˵������

ע�����
	��Script_Scene.h
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
����˵�����Ĵ���˸���ʧ�ܣ�������Ӣ����
����������0
����˵������
		
����ֵ������0
����ֵ˵������
ע�����
	��
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
����˵�����Ĵ������׼��ˢ��2,3,4,5,7,8���ֵ�ʱ�򣬸�֪��Ҵ˲������ˢ�µ㡣�Ա��Զ��һ�״̬�����ܹ�ȥ
����������3
����˵����
		1._nUserID ���GUIG
		2. fPosX X���� 
		3. fPosZ Y����
����ֵ������0
����ֵ˵������
ע����� ��
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
����˵�����ж���ҵ�ǰ���ڳ����Ƿ��ǰ����� �� �Ƿ����Լ������������
����������1
����˵����_nUserID ��ҵ�ObjID
		
����ֵ������2
����ֵ˵����1 - ��ҵ�ǰ���ڳ����Ƿ��ǰ������  2- ����Ƿ����Լ������������
ע�����
	��
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
����˵���� ���ݳ���id���س�������
����������1
����˵����
	
����ֵ������0
����ֵ˵����

ע�����
	��Script_Define.h
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
����˵�����ٻ�Ӣ��
����������0
����˵����
		
����ֵ������0
����ֵ˵����
ע�����
	��
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
����˵��������������ȫ����������
����������0
����˵����
		
����ֵ������0
����ֵ˵����
ע�����
	��
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
		
		// ɨ�����ǰ�����������
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
����˵��������NPC
����������3
����˵����
	1.�������� guildGuidH
	2.�������� guildGuidL
	3.���ɵȼ� level
	4.NPC������ index
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
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
����˵������ȡ��ս�������
����������0
����˵����
����ֵ������1
����ֵ˵����
	1.���ر��ڲ�ս�������
ע�����
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
����˵������ȡ�۰����°����Ϣ
����������3
����˵����
	1.index ��ȡ��N�������Ϣ
����ֵ������
����ֵ˵����4
	1.���ذ��guid����һ��Ϊ���ذ�ᣬ����Ϊ�������
ע�����
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
����˵��������Ƶ���㲥��Ϣ
����������
����˵����
	1.guildGuidH ���guild��λ
	2.guildGuidL ���guild��λ
	3.msg ��Ϣ
����ֵ������0
����ֵ˵����
ע�����
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
����˵���������������NPC
����������3
����˵����
	1.NPCDataID
	2.x����
	3.z����
����ֵ������1
����ֵ˵����
	1.NPCObjID
ע�����
	��Script_Define.h
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
����˵����������������
����������0
����˵����
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵������ȡ�����ܿܰ����Ϣ
����������0
����˵����
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵��������������𢶦��
����������0
����˵����
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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