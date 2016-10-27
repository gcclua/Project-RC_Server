#ifndef _OBJ_HERO_H_
#define _OBJ_HERO_H_

#include "Obj_Character.h"
#include "Table/Table_NpcSkillStrategy.h"
#include "Table/Table_NpcOptionalSkill.h"
#include "Obj_Npc.h"
#include "hero/GameStruct_Hero.h"

class Obj_Hero : public Obj_Npc
{
public:
	Obj_Hero(void);
	virtual ~Obj_Hero(void);

public:
	virtual int GetObjType(void) const {return ObjType::HERO;}

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

public:

	int64 GetUID() const {return m_nID;}
	void  SetUID(int64 uid){m_nID=uid;}

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}

	int  GetLevel() const {return m_nLevel;}
	void SetLevel(int nVal) {m_nLevel = nVal;}

	int  GetQuality() const {return m_nQuality;}
	void SetQuality(int nVal) {m_nQuality=nVal;}

	HERONAME GetName() const {return m_Name;}
	void   SetName(HERONAME szName) {m_Name=szName;}

private:
	int     m_nType;    //英雄类型
	int     m_nLevel;   //等级
	int     m_nQuality; // 品质
	
	HERONAME m_Name;        // 名称

	int64   m_nID;       // 英雄的uid

};

POOLDEF_DECL(Obj_Hero);

typedef GeneralObjRefCont<Obj_Hero, 256> HeroRefCont;


#endif
