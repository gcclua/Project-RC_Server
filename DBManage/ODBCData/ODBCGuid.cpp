////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺14:10 2014-06-20 
//			   ˵����GUID���ݴ洢
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCGuid.h"

ODBCGuid::ODBCGuid(ODBCInterface* pInterface)
{
	AssertEx(pInterface, "");
	mInterface = pInterface;
}

bool ODBCGuid::Save(DBGuidData* pSource)
{
	__ENTER_FUNCTION

	DB_QUERY* pQuery = GetInternalQuery();
	AssertEx(pQuery,"");

	AssertEx(pSource,"");
	DBGuidData& rGuidData = *pSource;

	pQuery->Clear();
	pQuery->Parse(SaveGuidData,
		rGuidData.m_Type,
		rGuidData.m_Serial);  

	if (!ODBCBase::Save_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError), "[ODBCGuid::Save]:Fail Type(%d),Serial(%u)",
			static_cast<tint32>(rGuidData.m_Type),
			rGuidData.m_Serial);
		return false;
	}
	AssertEx(mInterface,"");
	mInterface->Clear();

	return true;

	__LEAVE_FUNCTION
	return false;
}
