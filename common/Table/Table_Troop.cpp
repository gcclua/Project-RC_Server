//This code create by CodeEngine,don't modify
#include "Table_Troop.h"











bool Table_Troop::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "Troop Columns Differ"); 
 loader.ReadDirect(m_ActionId,(tint32)ID_ACTIONID);
loader.ReadDirect(m_DataID[0],(tint32)ID_DATAID1);
loader.ReadDirect(m_DataID[1],(tint32)ID_DATAID2);
loader.ReadDirect(m_DataID[2],(tint32)ID_DATAID3);
loader.ReadDirect(m_DataID[3],(tint32)ID_DATAID4);
loader.ReadDirect(m_DataID[4],(tint32)ID_DATAID5);
loader.ReadDirect(m_DataID[5],(tint32)ID_DATAID6);
loader.ReadDirect(m_DataID[6],(tint32)ID_DATAID7);
loader.ReadDirect(m_DataID[7],(tint32)ID_DATAID8);
loader.ReadDirect(m_DataID[8],(tint32)ID_DATAID9);
loader.ReadDirect(m_DataID[9],(tint32)ID_DATAID10);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_ModelID,(tint32)ID_MODELID);
loader.ReadDirect(m_ModelSize,(tint32)ID_MODELSIZE);
loader.ReadDirect(m_Portrait,(tint32)ID_PORTRAIT);
loader.ReadDirect(m_Size,(tint32)ID_SIZE);
loader.ReadDirect(m_SoldierCpunt,(tint32)ID_SOLDIERCPUNT);
loader.ReadDirect(m_Type,(tint32)ID_TYPE);
loader.ReadDirect(m_VonetyID,(tint32)ID_VONETYID);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_Troop);



