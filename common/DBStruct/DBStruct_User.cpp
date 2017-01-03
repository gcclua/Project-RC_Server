
#include "DBStruct_User.h"
#include "GuidDefine.h"
void DBBaseUserData::CleanUp( )
{
	//基本信息
	m_Guid = invalid_guid64;		
	m_Level = 0;
	m_Exp = 0;
	m_IsValid = invalid_id;
	m_Gender  = 0;
	m_CityId = invalid_guid64;
	memset(m_CharName,0,sizeof(m_CharName));
	memset(m_AccName,0,sizeof(m_AccName));

	memset( m_CommonData, 0, sizeof(tint32)*MAX_CHAR_COMMON_DATA_NUM ) ;
	memset( m_CommonFlag, 0, sizeof(tint32)*MAX_CHAR_COMMON_FLAG_NUM ) ;

	m_CreateRoleTime = 0;
	m_LastLogoutTime = 0;

}

void DBBaseUserData::CopyFrom(const DBBaseUserData& rSource)
{
	__ENTER_FUNCTION
		m_Guid    = rSource.m_Guid;
		m_Level   = rSource.m_Level;
		m_Exp     = rSource.m_Exp;
		m_IsValid = rSource.m_IsValid;
		m_Gender  = rSource.m_Gender;
		m_CityId  = rSource.m_CityId;
		memset(m_CharName,0,sizeof(m_CharName));
		tsnprintfex(m_CharName, sizeof(m_CharName), "%s",rSource.m_CharName);

		memset(m_AccName,0,sizeof(m_AccName));
		tsnprintfex(m_AccName, sizeof(m_AccName), "%s",rSource.m_AccName);

		memcpy( m_CommonData, rSource.m_CommonData, sizeof(tint32)*MAX_CHAR_COMMON_DATA_NUM ) ;
		memcpy( m_CommonFlag, rSource.m_CommonFlag, sizeof(tint32)*MAX_CHAR_COMMON_FLAG_NUM ) ;

		m_CreateRoleTime = rSource.m_CreateRoleTime;
		m_LastLogoutTime = rSource.m_LastLogoutTime;
		
	__LEAVE_FUNCTION
}

//如果创建角色时，数据无特殊赋值要求，可以不在InitAsCreateNewChar接口中添加赋值处理，但是CleanUp接口中一定要有初始化赋值
void DBBaseUserData::InitAsCreateNewChar(const tchar* szCharName,const tchar* szAccName,int gender)
{
	__ENTER_FUNCTION
		m_Guid = GUIDDEF_GEN(Char);
		m_Level = 1;			
		m_Exp = 0;	
		m_IsValid = 1;
		m_Gender  = gender;
		m_CityId  = 0;
		memset(m_CharName,0,sizeof(m_CharName));
		tsnprintfex(m_CharName, sizeof(m_CharName), "%s",szCharName);

		memset(m_AccName,0,sizeof(m_AccName));
		tsnprintfex(m_AccName, sizeof(m_AccName), "%s",szAccName);

		memset( m_CommonData, 0, sizeof(tint32)*MAX_CHAR_COMMON_DATA_NUM ) ;
		memset( m_CommonFlag, 0, sizeof(tint32)*MAX_CHAR_COMMON_FLAG_NUM ) ;

	
	m_CreateRoleTime = gTimeManager.GetANSITime();
	m_LastLogoutTime = 0;
	__LEAVE_FUNCTION
}

void DBFullUserData::CleanUp()
{
	m_User.CleanUp();
	for (int i=0;i<HEROTYPE_MAX;i++)
	{
		m_HeroList[i].CleanUp();
	}
	m_City.CleanUp();
	for (int i=0;i<MARCH_MAX_COUNT;i++)
	{
		m_MarchList[i].CleanUp();
	}
}

void  DBFullUserData::CopyFrom(const DBFullUserData& rSource)
{
	__ENTER_FUNCTION
		CleanUp();
	m_User.CopyFrom(rSource.m_User);
	for (int i=0;i<HEROTYPE_MAX;i++)
	{
		m_HeroList[i].CopyFrom(rSource.m_HeroList[i]);
	}
	m_City.CopyFrom(rSource.m_City);

	for (int i=0;i<MARCH_MAX_COUNT;i++)
	{
		m_MarchList[i].CopyFrom(rSource.m_MarchList[i]);
	}
	
	__LEAVE_FUNCTION
}
uint32 DBFullUserData::CalcCRC()
{
	__ENTER_FUNCTION
		return 0;
	__LEAVE_FUNCTION
}

void DBFullUserData::InitAsCreateNewChar(const tchar* szCharName,const tchar* szAccName,int gender)
{
	__ENTER_FUNCTION
		//重置数据
		CleanUp();
	//设置初建角色数据
	m_User.InitAsCreateNewChar(szCharName,szAccName,gender);
	__LEAVE_FUNCTION
}