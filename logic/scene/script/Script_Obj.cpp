#include "Script_Obj.h"
#include "Script_Define.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Obj/Obj.h"
#include "Scene/Scene/CopyScene.h"
#include "Mail/GameInterface_Mail.h"

/*----------------------------------------------------------------------
����˵������ȡObjλ��
����������1
����˵����
	1.ObjID
����ֵ������2
����ֵ˵����
	1.X����
	2.Z����
ע�����
	��Script_Define.h
*/
int C_GetScenePos(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	int _nObjID = static_cast<int>(lua_tonumber(L, 1));

	__BEGIN_OBJ_DEFINE
	lua_pushnumber(L, rObj.GetScenePos().m_fX);
	lua_pushnumber(L, rObj.GetScenePos().m_fZ);
	return 2;
	__END_OBJ_DEFINE

	__END_LUA
	lua_pushnumber(L, 0.0f);
	lua_pushnumber(L, 0.0f);
	return 2;
}

/*----------------------------------------------------------------------
����˵����ǿ������Objλ��
����������3
����˵����
	1.ObjID
	2.PosX
	3.PosZ
����ֵ������0
ע�����
	��Script_Define.h
*/
int C_ForceSetScenePos(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nObjID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_OBJ_DEFINE

	rObj.ForceSetScenePos(ScenePos(fPosX, fPosZ));
	return 0;

	__END_OBJ_DEFINE

	__END_LUA
	return 0;
}
/*----------------------------------------------------------------------
����˵����ǿ������Obj���λ��
����������3
����˵����
	1.ObjID
	2.PosX
	3.PosZ
����ֵ������0
ע�����
	��Script_Define.h
*/
int C_ForceSetFellowScenePos(lua_State *L)
{
	__BEGIN_LUA

	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nObjID = static_cast<int>(lua_tonumber(L, 1));
	float fPosX = static_cast<float>(lua_tonumber(L, 2));
	float fPosZ = static_cast<float>(lua_tonumber(L, 3));

	__BEGIN_OBJ_DEFINE
	Scene& rScene =rObj.GetScene();
	Obj_User & rUser = dynamic_cast<Obj_User &>(rObj);
	Obj_FellowPtr curCallFellowPtr = rScene.GetFellowByID( rUser.GetInstanceFellowObjId() );
	if (curCallFellowPtr)
	{
		curCallFellowPtr->ForceSetScenePos(ScenePos(fPosX, fPosZ));
	}
	return 0;
	 
	__END_OBJ_DEFINE

	__END_LUA
	return 0;
}

int C_AuditLog_KillVillainBoss(lua_State *L)
{
	__BEGIN_LUA

		AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	
	int _nObjID = static_cast<int>(lua_tonumber(L, 1));
	int _nKillerID = static_cast<int>(lua_tonumber(L, 2));

	__BEGIN_SCENE_DEFINE
		if (rScene.IsCopyScene())
		{
			CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
			int nDiffcult = rCopyScene.GetCopySceneDifficulty();
			int nSceneLevel = rCopyScene.GetLevel();
			Obj_NpcPtr _NpcPtr = rScene.GetNpcByID(_nObjID);
			Obj_UserPtr _UserPtr = rScene.GetUserByID(_nKillerID); 
			if (_NpcPtr  && _UserPtr)
			{
				Obj_User &rUser = *_UserPtr;
				Obj_Npc &rNpc = *_NpcPtr;
				if (rNpc.GetNpcType() == NPC_TYPE::BOSS)
				{
					// ��¼��־
					AuditLog(LOGDEF_INST(Audit_Villain),"KBOSS", rUser.GetGuid(), "SID=%d \1 DY=%d \1 SE=%d \1 LE=%d \1 BID=%d",
						rUser.GetSceneClassID(),
						rScene.GetCopySceneDifficulty(),
						rScene.GetCopyScenePlayType(),
						rScene.GetLevel(),
						rNpc.GetDataID());
				}
			}
		}
		return 0;
		__END_SCENE_DEFINE
			__END_LUA
			return 0;
}

int C_KillBossRewardItem(lua_State *L)
{
	__BEGIN_LUA
	AssertEx(L, "");
	AssertLuaNumberParam(L, 1);
	AssertLuaNumberParam(L, 2);
	AssertLuaNumberParam(L, 3);
	int _nObjID = static_cast<int>(lua_tonumber(L, 1));
	int _nKillerID = static_cast<int>(lua_tonumber(L, 2));
	int _nItemID = static_cast<int>(lua_tonumber(L, 3));
	__BEGIN_SCENE_DEFINE
		if (!rScene.IsCopyScene())
		{
			return 0;
		}
		CopyScene& rCopyScene =  dynamic_cast<CopyScene&>(rScene);
		Obj_NpcPtr _NpcPtr = rScene.GetNpcByID(_nObjID);
		Obj_UserPtr _UserPtr = rScene.GetUserByID(_nKillerID); 
		if (_NpcPtr  && _UserPtr)
		{
			Obj_User &rUser = *_UserPtr;
			Obj_Npc &rNpc = *_NpcPtr;
			
			//Obj_UserPtr _LeaderPtr = rScene.GetUserByGuid(rUser.GetLeaderGuid()); 
			if (rNpc.GetNpcType() == NPC_TYPE::BOSS)
			{
				MailInterface::SystemSendTextMail_WithItem(rUser.GetLeaderGuid(), "#{5152}", 
					_nItemID, 1, OP_MAIN_VILLAIN_REWARD);
			}
		}
		return 0;
	__END_SCENE_DEFINE
		__END_LUA
		return 0;
}
