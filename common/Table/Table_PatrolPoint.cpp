//This code create by CodeEngine,don't modify
#include "Table_PatrolPoint.h"








bool Table_PatrolPoint::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "PatrolPoint Columns Differ"); 
 loader.ReadDirect(m_Action,(tint32)ID_ACTION);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_Mark,(tint32)ID_MARK);
loader.ReadDirect(m_NextIndex,(tint32)ID_NEXTINDEX);
loader.ReadDirect(m_P[0],(tint32)ID_P1);
loader.ReadDirect(m_P[1],(tint32)ID_P2);
loader.ReadDirect(m_P[2],(tint32)ID_P3);
loader.ReadDirect(m_Posx,(tint32)ID_POSX);
loader.ReadDirect(m_Posz,(tint32)ID_POSZ);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_PatrolPoint);



