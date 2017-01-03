
#ifndef __DBSTRUCT_USER_H__
#define __DBSTRUCT_USER_H__

#include "DBStruct.h"
#include "DBStruct_City.h"
#include "DBStruct_Troop.h"
#include "DBStruct_Hero.h"
#include "DBStruct_March.h"



//��Ҫ����Ľ�ɫ����
struct DBBaseUserData
{
public:
	DBBaseUserData(){};
	~DBBaseUserData(){};

	void CleanUp( );
	void InitAsCreateNewChar(const tchar* szCharName,const tchar* szAccName,int gender);
	void CopyFrom(const DBBaseUserData& rSource);

public:
	//������Ϣ

	int64	m_Guid;						//Guid
	tint16  m_Level;					//�ȼ�
	tint32  m_Exp;						//����
	tint8   m_IsValid;
	tint8  	m_Gender;                   //�Ա�
	int64   m_CityId;                   // ����Id

	char m_CharName[MAX_NAME_SIZE];
	char m_AccName[MAX_ACCOUNT_SIZE];

	tint32	m_CommonData[MAX_CHAR_COMMON_DATA_NUM];	// ��ɫ���������Զ�������
	tint32	m_CommonFlag[MAX_CHAR_COMMON_FLAG_NUM];	// ��ɫ����FLAG���

	time_t		m_CreateRoleTime;        //��ɫ����ʱ��
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
	DBHero                      m_HeroList[HEROTYPE_MAX];                      // ���е�Ӣ���б�
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
