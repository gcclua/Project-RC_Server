#include "DBStruct_Troop.h"
#include "GuidDefine.h"
#include "Table/Table_Troop.h"
#include "Table/Table_RoleBaseAttr.h"

void DBTroop::CleanUp( )
{
	__ENTER_FUNCTION
		m_nId      = 0;
		m_nType    = TROOPTYPE_INVILID; 
		m_nLevel   = 0;
		m_nCount   = 0;
		m_nMarchId = 0;
		m_nHp      = 0;
		m_nArrangeIndex = 0;
		m_nQueueIndex   = 0;
	__LEAVE_FUNCTION
}
void DBTroop::CopyFrom(const DBTroop& rSource)
{
	__ENTER_FUNCTION
		m_nId      = rSource.m_nId;
		m_nType    = rSource.m_nType; //µØ¿éID
		m_nLevel   = rSource.m_nLevel;
		m_nCount   = rSource.m_nCount;
		m_nMarchId = rSource.m_nMarchId;
		m_nHp      = rSource.m_nHp;
		m_nArrangeIndex = rSource.m_nArrangeIndex;
		m_nQueueIndex   = rSource.m_nQueueIndex;
	__LEAVE_FUNCTION
}

void DBTroop::InitTroop(int nArrangeIndex,int nQueueIndex,int64 nMarchId)
{
	__ENTER_FUNCTION
		CleanUp();
		m_nId = GUIDDEF_GEN(Troop);
		m_nLevel = 1;
		m_nMarchId   = nMarchId;
		m_nArrangeIndex   = nArrangeIndex;
		m_nQueueIndex  = nQueueIndex;
		m_nType        = 1;
		m_nCount       = 18;

		Table_Troop const * pTableTroop = GetTable_TroopByID(m_nType);
		AssertEx(pTableTroop,"");

		Table_RoleBaseAttr const * pRoleBase = GetTable_RoleBaseAttrByID(pTableTroop->GetDataIDbyIndex(m_nLevel-1));

		m_nHp = m_nCount* pRoleBase->GetMaxHP();

		__LEAVE_FUNCTION
}
