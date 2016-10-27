#include "GameStruct_PK.h"
#include "DBStruct/DBStruct_PK.h"

bool PKAttackerInfo::SerializeToDB(DBPKAttackerInfo& rDest)
{
	__ENTER_FUNCTION
 	rDest.m_AttackerGUID = m_AttackerGUID;
 	rDest.m_nAttackTime  = m_nAttackTime;
    	return true;
	__LEAVE_FUNCTION
		return false;
}

bool PKAttackerInfo::SerializeFromDB(const DBPKAttackerInfo& rSour)
{
	__ENTER_FUNCTION
 	m_AttackerGUID = rSour.m_AttackerGUID;
 	m_nAttackTime  = rSour.m_nAttackTime;
		return true;
	__LEAVE_FUNCTION
		return false;
}
bool PKAttackerList::SerializeToDB(DBPKAttackerList& rDest)
{
	__ENTER_FUNCTION
 	for (int i = 0;i < MAX_LIST_SIZE; i++)
 	{
 		m_AttackerList[i].SerializeToDB(rDest.m_AttackerList[i]);
 	}
	
	return true;
	__LEAVE_FUNCTION
	return false;

}
bool PKAttackerList::SerializeFromDB(const DBPKAttackerList& rSour)
{
	__ENTER_FUNCTION
 	for (int i = 0;i < MAX_LIST_SIZE; i++)
 	{
 		m_AttackerList[i].SerializeFromDB(rSour.m_AttackerList[i]);
 	}
		return true;
	__LEAVE_FUNCTION
		return false;
}
