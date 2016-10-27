//This code create by CodeEngine,don't modify
#include "Table_SnareObjBuffInfo.h"









bool Table_SnareObjBuffInfo::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SnareObjBuffInfo Columns Differ"); 
 loader.ReadDirect(m_DelayTime,(tint32)ID_DELAYTIME);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_ImpactId,(tint32)ID_IMPACTID);
loader.ReadDirect(m_IsEffectByHit,(tint32)ID_ISEFFECTBYHIT);
loader.ReadDirect(m_MaxEffectTime,(tint32)ID_MAXEFFECTTIME);
loader.ReadDirect(m_MaxValidNum,(tint32)ID_MAXVALIDNUM);
loader.ReadDirect(m_ScanIntervalTime,(tint32)ID_SCANINTERVALTIME);
loader.ReadDirect(m_ValidRadius,(tint32)ID_VALIDRADIUS);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_SnareObjBuffInfo);



