////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：17:38 2014-01-01
//             说明：PK相关数据存储结构
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBSTRUCTPK_H__
#define __DBSTRUCTPK_H__

#include "Base.h"
#include "CombatStruct/GameStruct_PK.h"

/*******************************************************************************/
//	特别注意：1)DBPKAttackerList及其子Struct需要满足 plain struct的条件，
//			  绝对不能包含指针，引用，虚函数。
//            2)包含CleanUp和CopyFrom两个函数（方便消息间拷贝数据）。
/*******************************************************************************/
struct DBPKAttackerInfo
{
public:
	DBPKAttackerInfo() {CleanUp();}
	void	CleanUp();
	void	CopyFrom(const DBPKAttackerInfo& rItemData);

public:
	int64 m_AttackerGUID;
	time_t m_nAttackTime;//留在列表的剩余时间 单位毫秒
};
struct DBPKAttackerList
{
public:
	DBPKAttackerList() {CleanUp();}
	void	CleanUp();
	void	CopyFrom(const DBPKAttackerList& rSour);
public:
	DBPKAttackerInfo m_AttackerList[PKAttackerList::MAX_LIST_SIZE];
};

#endif