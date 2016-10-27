//This code create by CodeEngine,don't modify
#include "Table_SceneNpc.h"









bool Table_SceneNpc::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SceneNpc Columns Differ"); 
 loader.ReadDirect(m_DataID,(tint32)ID_DATAID);
loader.ReadDirect(m_FaceDirection,(tint32)ID_FACEDIRECTION);
loader.ReadDirect(m_GroupID,(tint32)ID_GROUPID);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_MutexID,(tint32)ID_MUTEXID);
loader.ReadDirect(m_PosX,(tint32)ID_POSX);
loader.ReadDirect(m_PosZ,(tint32)ID_POSZ);
loader.ReadDirect(m_SceneID,(tint32)ID_SCENEID);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_SceneNpc);



