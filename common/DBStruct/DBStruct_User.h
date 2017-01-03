
#ifndef __DBSTRUCT_USER_H__
#define __DBSTRUCT_USER_H__

#include "DBStruct.h"
#include "DBStruct_City.h"
#include "DBStruct_Troop.h"
#include "DBStruct_Hero.h"
#include "DBStruct_March.h"



//需要保存的角色数据
struct DBBaseUserData
{
public:
	DBBaseUserData(){};
	~DBBaseUserData(){};

	void CleanUp( );
	void InitAsCreateNewChar(const tchar* szCharName,const tchar* szAccName,int gender);
	void CopyFrom(const DBBaseUserData& rSource);

public:
	//基本信息

	int64	m_Guid;						//Guid
	tint16  m_Level;					//等级
	tint32  m_Exp;						//经验
	tint8   m_IsValid;
	tint8  	m_Gender;                   //性别
	int64   m_CityId;                   // 城市Id

	char m_CharName[MAX_NAME_SIZE];
	char m_AccName[MAX_ACCOUNT_SIZE];

	tint32	m_CommonData[MAX_CHAR_COMMON_DATA_NUM];	// 角色身上任务自定义数据
	tint32	m_CommonFlag[MAX_CHAR_COMMON_FLAG_NUM];	// 角色身上FLAG标记

	time_t		m_CreateRoleTime;        //角色创建时间
	time_t      m_LastLogoutTime;


};

struct DBFullUserData
{
	DBFullUserData()
	{
		CleanUp();
	}
	DBBaseUserData				m_User;
	DBCity                      m_City;
	DBHero                      m_HeroList[HEROTYPE_MAX];                      // 所有的英雄列表
	DBMarch                     m_MarchList[MARCH_MAX_COUNT];
	bool						m_bIsPasswdUnlock;

	void   CleanUp();

	void   CopyFrom(const DBFullUserData& rSource);
	void	InitAsCreateNewChar(const tchar* szCharName,const tchar* szAccName,int gender);
	uint32 CalcCRC();

	int64  GetGuid() const {return m_User.m_Guid;}
	void   SetGuid( int64 rGuid){ m_User.m_Guid = rGuid;}

};

struct MemFullUserData
{
	MemFullUserData()
	{
		CleanUp();
	}

	void CleanUp()
	{
		m_UserData.CleanUp();
	}

	int m_DBVersion;
	DBFullUserData m_UserData;
};


#endif
