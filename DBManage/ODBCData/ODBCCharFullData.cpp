
#include "ODBCCharFullData.h"
#include "DataBase/ODBCInterface.h"
#include "DataBase/SqlTemplate.h"



ODBCCharFullData::ODBCCharFullData(ODBCInterface* pInterface)
{

	mDBName = CHARACTER_DATABASE;
	mResult			= 0;
	mResultCount	= 0;
	m_CharGuid		= INVALID_ID;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

}


bool ODBCCharFullData::Load()
{

	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}

	pQuery->Clear();

	if(m_CharGuid==INVALID_ID)
	{
		return false;
	}

	pQuery->Parse(LoadCharFullData,CHAR_TABLE,m_CharGuid);

	return ODBCBase::Load();

}

bool ODBCCharFullData::Save(void* pSource)
{

	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}

	pQuery->Clear();

	if(m_CharGuid==INVALID_ID)
	{
		return false;
	}

	DBFullUserData* pCharFullData = static_cast<DBFullUserData*>(pSource);
	AssertEx(pCharFullData,"");
	


	if(!StrSafeCheck(pCharFullData->m_baseUser.m_Title,MAX_CHARACTER_TITLE))
		return false;


	tuint32 dbVersion = CalcCRC(pSource);

	pQuery->Parse(UpdateCharFullData,
				  CHAR_TABLE,
				  pCharFullData->m_baseUser.m_Title,
				  pCharFullData->m_baseUser.m_Sex,
				  pCharFullData->m_baseUser.m_Level,
				  pCharFullData->m_baseUser.m_DoubleExpTime_Num,
				  pCharFullData->m_baseUser.m_Exp,
				  pCharFullData->m_baseUser.m_Money,
				  pCharFullData->m_baseUser.m_HairColor,
				  pCharFullData->m_baseUser.m_FaceColor,
				  pCharFullData->m_baseUser.m_HairModel,
				  pCharFullData->m_baseUser.m_FaceModel,
				  pCharFullData->m_baseUser.m_LastLoginTime,
				  pCharFullData->m_baseUser.m_LastLogoutTime,
				  pCharFullData->m_baseUser.m_MenPai,
				  pCharFullData->m_baseUser.m_HP,
				  pCharFullData->m_baseUser.m_MP,
				  pCharFullData->m_baseUser.m_StrikePoint,
				  pCharFullData->m_baseUser.m_Level1Points,
			
				  pCharFullData->m_baseUser.m_PortraitID,
				  pCharFullData->m_baseUser.m_EnergyRegeneRate,
				  pCharFullData->m_baseUser.m_RMBMoney,
				  pCharFullData->m_baseUser.m_BankRMB,
				  pCharFullData->m_baseUser.m_VigorRegeneRate,
				  pCharFullData->m_baseUser.m_GmRight,
				  pCharFullData->m_baseUser.m_uPwdDelTime,
				  pCharFullData->m_baseUser.m_LeftDieTime,
				  pCharFullData->m_baseUser.m_Rage,
				  dbVersion,
				  m_CharGuid);
	
	if(!ODBCBase::Save())
		return false;
	

	AssertEx(mResultCount<=1,"");
	mInterface->Clear();
	if(mResultCount==0)
	{
		return true;
	}
	
	dbVersion = 0;

	return true;
}

bool ODBCCharFullData::ParseResult(void* pResult)
{

	switch(mOPType)
	{
	case DB_LOAD:
		{

			DBFullUserData* pCharFullData = static_cast<DBFullUserData*>(pResult);
			AssertEx(pCharFullData,"");

			pCharFullData->CleanUp();
			enum 
			{
				DB_CharGuid	=	1,
				DB_CharName,
				DB_Title,
				DB_Sex,
				DB_CreateTime,
				DB_Level,
				DB_Enegry,
				DB_Exp,
				DB_Money,
				DB_Pw,
				DB_HairColor,
				DB_FaceColor,
				DB_HairModel,
				DB_FaceModel,
				DB_Scene,
				DB_XPos,
				DB_ZPos,
				DB_LoginTime,
				DB_LogoutTime,
				DB_Version,
				DB_Camp,
				DB_Menpai,
				DB_HP,
				DB_MP,
				DB_StrikePoint,
				DB_Str,
				DB_Spr,
				DB_Con,
				DB_Ipr,
				DB_Dex,
				DB_Points,
				DB_Setting,
				DB_ShopInfo,
				DB_CarryPet,
				DB_GuildID,
				DB_TeamID,
				DB_HeadID,
				DB_eRecover,
				DB_RMB,
				DB_BANKRMB,
				DB_VRecover,
				DB_EnergyMax,
				DB_PwdelTime,
				DB_DieTime,
				DB_BankMoney,
				DB_BankEnd,
				DB_BackScene,
				DB_BackXPos,
				DB_BackZPos,
				DB_Rage,
			};
			
			AssertEx(mResultCount<=1,"");
			AssertEx(mInterface,"");
			int	   ErrorCode;

			//加载基本属性
			for(int i =0;i<1;i++)
			{
				if(!mInterface->Fetch())
					break;

				//加载角色基本属性
				pCharFullData->m_baseUser.m_GUID	=	mInterface->GetUInt(DB_CharGuid,ErrorCode);
				mInterface->GetString(DB_CharName,pCharFullData->m_baseUser.m_Name,MAX_CHARACTER_NAME,ErrorCode);
				mInterface->GetString(DB_Title,pCharFullData->m_baseUser.m_Title,MAX_CHARACTER_TITLE,ErrorCode);
				pCharFullData->m_baseUser.m_Sex	= mInterface->GetUInt(DB_Sex,ErrorCode);
				pCharFullData->m_baseUser.m_CreateDate	=	mInterface->GetUInt(DB_CreateTime,ErrorCode);
				pCharFullData->m_baseUser.m_Level	=	mInterface->GetUInt(DB_Level,ErrorCode);
				pCharFullData->m_baseUser.m_DoubleExpTime_Num	=	mInterface->GetUInt(DB_Enegry,ErrorCode);
				pCharFullData->m_baseUser.m_Exp	=	mInterface->GetUInt(DB_Exp,ErrorCode);
				pCharFullData->m_baseUser.m_Money	=	mInterface->GetUInt(DB_Money,ErrorCode);

				pCharFullData->m_baseUser.m_HairColor	=	mInterface->GetUInt(DB_HairColor,ErrorCode);
				pCharFullData->m_baseUser.m_FaceColor	=	mInterface->GetBYTE(DB_FaceColor,ErrorCode);
				pCharFullData->m_baseUser.m_HairModel	=	mInterface->GetBYTE(DB_HairModel,ErrorCode);
				pCharFullData->m_baseUser.m_FaceModel	=	mInterface->GetBYTE(DB_FaceModel,ErrorCode);
				pCharFullData->m_baseUser.m_LastLoginTime	=	mInterface->GetUInt(DB_LoginTime,ErrorCode);
				pCharFullData->m_baseUser.m_LastLogoutTime	=	mInterface->GetUInt(DB_LogoutTime,ErrorCode);
				pCharFullData->m_baseUser.m_DBVersion		=	mInterface->GetUInt(DB_Version,ErrorCode);
	

				pCharFullData->m_baseUser.m_MenPai	=	mInterface->GetUInt(DB_Menpai,ErrorCode);
				pCharFullData->m_baseUser.m_HP	=	mInterface->GetUInt(DB_HP,ErrorCode);
				pCharFullData->m_baseUser.m_MP	=	mInterface->GetUInt(DB_MP,ErrorCode);
				pCharFullData->m_baseUser.m_StrikePoint	=	mInterface->GetUInt(DB_StrikePoint,ErrorCode);
		
				pCharFullData->m_baseUser.m_Level1Points	=	mInterface->GetUInt(DB_Points,ErrorCode);
				
				pCharFullData->m_baseUser.m_PortraitID	=	mInterface->GetUInt(DB_HeadID,ErrorCode);
				pCharFullData->m_baseUser.m_EnergyRegeneRate	=	mInterface->GetInt(DB_eRecover,ErrorCode);	
				pCharFullData->m_baseUser.m_RMBMoney				=	mInterface->GetInt(DB_RMB,ErrorCode);					
				pCharFullData->m_baseUser.m_BankRMB			=  mInterface->GetInt(DB_BANKRMB,ErrorCode);
				pCharFullData->m_baseUser.m_VigorRegeneRate	=	mInterface->GetInt(DB_VRecover,ErrorCode);
				pCharFullData->m_baseUser.m_GmRight	=	mInterface->GetInt(DB_EnergyMax,ErrorCode);
				pCharFullData->m_baseUser.m_uPwdDelTime	=	mInterface->GetUInt(DB_PwdelTime,ErrorCode);
				pCharFullData->m_baseUser.m_LeftDieTime	=	mInterface->GetUInt(DB_DieTime,ErrorCode);
				pCharFullData->m_baseUser.m_Rage			  = mInterface->GetUInt(DB_Rage,ErrorCode);

				mInterface->Clear();

				tuint32 dbVersion = CalcCRC( pCharFullData );
				dbVersion = 0;
				
			}
		}
		break;
	case DB_SAVE:
		{
			
		}
		break;
	default:
		break;
	}


	return true;
}

int64	ODBCCharFullData::GetCharGuid()
{
	return m_CharGuid;
}

void	ODBCCharFullData::SetCharGuid(int64 guid)
{
	m_CharGuid	 = guid;
}

uint32	ODBCCharFullData::CalcCRC(void* pSource)
{
	DBFullUserData* pCharFullData = static_cast<DBFullUserData*>(pSource);
	AssertEx(pCharFullData,"");

	tuint32 dbVersion;
	dbVersion = pCharFullData->m_baseUser.m_Level + 
				pCharFullData->m_baseUser.m_Money + 
				pCharFullData->m_baseUser.m_HP + 
				pCharFullData->m_baseUser.m_MP +
				pCharFullData->m_baseUser.m_GmRight;
	dbVersion &= 0xFFFF0000;
	dbVersion |= 0x80000000;
	dbVersion += ( ( pCharFullData->m_baseUser.m_BankRMB & 0x000000FF ) << 8 );
	dbVersion += pCharFullData->m_baseUser.m_RMBMoney & 0x000000FF;

	return dbVersion;
}