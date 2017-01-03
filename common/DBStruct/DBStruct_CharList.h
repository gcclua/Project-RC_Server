////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：17:58 2014-02-18
//             说明：角色列表结构
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBSTRUCTCHARLIST_H__
#define __DBSTRUCTCHARLIST_H__
/*******************************************************************************/
//	特别注意：1)DBCharList及其子Struct需要满足 plain struct的条件，
//			  绝对不能包含指针，引用，虚函数。
//            2)包含CleanUp和CopyFrom两个函数（方便消息间拷贝数据）。
//			  3)包含GetKey函数（子Struct可以不包含）。
/*******************************************************************************/
#include "Base.h"
#include "Scene/GameStruct_Scene.h"
struct DBCharData
{
public:
	DBCharData(){CleanUp();}
	~DBCharData(){}	 
	void CleanUp();
	void CopyFrom(const DBCharData& rSour);

public:
	int64	m_Guid;
	tchar   m_CharName[MAX_NAME_SIZE];
};

struct DBCharDataList
{
public:
	DBCharDataList(){CleanUp();}
	~DBCharDataList(){}	 
	void CleanUp();
	void CopyFrom(const DBCharDataList& rSour);
public:
	tint32	   m_CharNum;
	DBCharData m_CharDataList[DB_CHAR_NUMBER];
};

#endif