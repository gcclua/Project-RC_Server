#include "Script_Character.h"
#include "Script_Define.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Obj/Obj_Character.h"

/*----------------------------------------------------------------------
����˵������ȡ��ǰѪ��
����������1
����˵����
	1.character objID
����ֵ������1
����ֵ˵����
	1����ǰѪ��
ע�����
	��Script_Define.h
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
����˵������ȡ���Ѫ��
����������1
����˵����
	1.character objID
����ֵ������1
����ֵ˵����
	1�����Ѫ��
ע�����
	��Script_Define.h
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
����˵��������CharacterѪ��
����������3
����˵����
	1.objID
	2.���ӵ�Ѫ��
����ֵ������1
����ֵ˵����
	1.��ǰѪ��
ע�����
	��Script_Define.h
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
����˵����ǿ��ɱ��
����������2
����˵����
	1.objID
	2.killerID
����ֵ������1
����ֵ˵����
	
ע�����
	��Script_Define.h
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
����˵����ǿ�Ƶ�Ѫ
����������3
����˵����
	1.objID
	2.killerID
	3.�ٷֱ�
����ֵ������0
����ֵ˵����
	
ע�����
	��Script_Define.h
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
����˵������ȡCharacter����������ObjID
����������3
����˵����
	1.objID
	2.��Χ�뾶
����ֵ������1
����ֵ˵����
	1.ObjID
ע�����
	��Script_Define.h
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

		// ���4�ΰ�
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
����˵�����Ƿ���buff
����������3
����˵����
	1.objID
	2.buffID
����ֵ������1
����ֵ˵����
	1.�Ƿ�
ע�����
	��Script_Define.h
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
����˵�������buff
����������3
����˵����
	1.SourceobjID
	2.TargetObjID
	2.buffID
	3.skillID(�޼��ܣ�ֱ��-1)
����ֵ������1
����ֵ˵����
	1.����Ƿ�ɹ�
ע�����
	��Script_Define.h
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
����˵�����Ƴ�ĳ��buff
����������2
����˵����
	1.objID
	2.buffID
����ֵ������1
����ֵ˵����
	1.����Ƿ�ɹ�
ע�����
	��Script_Define.h
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
����˵����Character�Ƿ����
����������1
����˵����
	1.objID
����ֵ������1
����ֵ˵����
	1.��or��
ע�����
	��Script_Define.h
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
����˵����Character�ߵ�ĳ����
����������4
����˵����
	1.objID
	2.fPosX
	3.fPosY
	4.fStopRange
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵������Ѫ����
����������1
����˵����
	1.objID
����ֵ������1
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵������ȡ���ڳ����ĳ���ID
����������1
����˵����
	1.objID
����ֵ������1
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵������ȡCharacter��ĳ��ս������ֵ
����������2
����˵����
	1._nCharacterID
	2._nAttrId ������COMBATATTR_T::TYPEö��
����ֵ������1 ս������ֵ
ע�����
	��Script_Define.h
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
����˵������ȡObj_Character�ĵ�ǰ����
����������1
����˵����
	1.character objID _nCharacterID
����ֵ������1
����ֵ˵����
	1����ǰ����
ע�����
	��Script_Define.h
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
����˵�����ı�Character����
����������2
����˵����
	1.objID
	2.���ӻ���ٵ����� - ���� ����,���� ����
����ֵ������1
����ֵ˵����
	1.��ǰ����
ע�����
	��Script_Define.h
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
����˵�����л�NPC������״̬
����������1
����˵����
	1.npc��ObjID
	2.����Ŀ���ObjId
����ֵ������1
����ֵ˵����1: �ɹ� || 0: ʧ��
ע�����
	��Script_Define.h
*/
int C_SwithAIToFollow(lua_State *L)
{
	__BEGIN_LUA
	
	AssertEx(L, "");
	//NPC��ObjId
	AssertLuaNumberParam(L, 1);
	int _nNpcID = static_cast<int>(lua_tonumber(L, 1));
	//����Ŀ��(���)��ObjId
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
����˵�����л�NPCĿ��
����������2
����˵����
	1.npc��ObjID
	2.Ŀ��ObjID
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵�����л�NPC��Ӫ
����������2
����˵����
	1.npc��ObjID
	2.force
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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
����˵��������npc����ʱ�� ����
����������2
����˵����
	1.npc��ObjID
	2.lifetime
����ֵ������0
����ֵ˵����
ע�����
	��Script_Define.h
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