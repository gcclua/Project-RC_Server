#ifndef _OBJ_TROOP_H_
#define _OBJ_TROOP_H_

#include "Obj_Character.h"
#include "Table/Table_NpcSkillStrategy.h"
#include "Table/Table_NpcOptionalSkill.h"
#include "Obj_Npc.h"
#include "troop/GameStruct_Troop.h"


class Obj_Troop : public Obj_Npc
{
public:
	Obj_Troop(void);
	virtual ~Obj_Troop(void);

public:
	virtual int GetObjType(void) const {return ObjType::TROOP;}
	

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

	virtual bool CanBeView(Obj_Character &rObj);
	// 战斗属性相关
public:
	virtual void CalculateInitalAttr(void);
	virtual void CalculateFinalyAttr(void);

	//获取最终战斗属性数值
	virtual tint32 GetCombatAttrByID(tint32 AttrId);
public:

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}


private:
	int     m_nType;    //士兵类型
	


};

POOLDEF_DECL(Obj_Troop);

typedef GeneralObjRefCont<Obj_Troop, 256> TroopRefCont;


#endif
