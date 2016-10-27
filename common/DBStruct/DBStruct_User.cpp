
#include "DBStruct_User.h"

void DBBaseUserData::CleanUp( )
{
	//基本信息
	m_PortraitID		= -1;
	memset( m_Name, 0, MAX_CHARACTER_NAME ) ;
	memset( m_Title, 0, MAX_CHARACTER_TITLE ) ;
	m_GUID				= INVALID_ID ;
	m_Sex				= false ;
	m_CreateDate		= 0 ;
	m_Level				= 0;
	m_RMBMoney			= 0;
	m_BankRMB			= 0;
	m_VigorRegeneRate	= 0;
	m_DoubleExpTime_Num			= 1;
	m_GmRight			= 0;
	m_EnergyRegeneRate	= 0;
	m_Exp				= 0;
	m_Money				= 0;;
	m_uPwdDelTime		= 0;
	m_HairColor			= 0xFFFFFFFF;
	m_FaceColor			= 0xFF;
	m_HairModel			= -1;
	m_FaceModel			= -1;

	//基本状态
	m_OnlineTime		= 0;
	m_LastLoginTime		= 0;
	m_LastLogoutTime	= 0;
	m_LeftDieTime		= 0;
	m_DBVersion			= 0;

	//战斗信息
	m_MenPai			= 0;
	m_NeiShang			= 0;
	m_HP				= 0;
	m_MP				= 0;
	m_StrikePoint		= 0;
	m_Rage				= 0;
	m_nPKValue			= 0;

	m_Level1Points		= 0;
}

void DBBaseUserData::CopyFrom(const DBBaseUserData& rSource)
{


}

void DBFullUserData::CleanUp()
{
	m_baseUser.CleanUp();
}

void  DBFullUserData::CopyFrom(const DBFullUserData& rSource)
{
	__ENTER_FUNCTION
	m_baseUser.CopyFrom(rSource.m_baseUser);
	__LEAVE_FUNCTION
}
uint32 DBFullUserData::CalcCRC()
{
	__ENTER_FUNCTION
		return 0;
	__LEAVE_FUNCTION
}