////////////////////////////////////////////////////////////////////////////////////////
//时间：2014年7月2日11:40:55
//说明：随机名字表
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBRANDOMNAME_H__
#define __DBRANDOMNAME_H__
/*******************************************************************************/
//	特别注意:1)DBRandomName及其子Struct需要满足 plain struct的条件，绝对不能包含指针，引用，虚函数。
//          2)包含CleanUp和CopyFrom两个函数（方便消息间拷贝数据）。
//	        3)包含GetKey函数（子Struct可以不包含）。
/*******************************************************************************/
#include "Base.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct.h"
struct DBRandomName
{
public:
	DBRandomName(){CleanUp();}
	~DBRandomName(){}	 
	void CleanUp();
	void CopyFrom(const DBRandomName& rSour);
public:
	tchar  m_szName[MAX_NAME_SIZE];
};
struct DBRandomNameList
{
public:
	DBRandomNameList(){CleanUp();}
	~DBRandomNameList(){}	 
	void CleanUp();
	void CopyFrom(const DBRandomNameList& rSour);
public:	
	DBRandomName m_RandomNameList[RANDOM_NAME_BUFFER_MAX];
};

#endif//__DBRANDOMNAME_H__