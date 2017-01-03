//This code create by CodeEngine,don't modify
#include "Table_ServerConfigList.h"

















bool Table_ServerConfigList::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "ServerConfigList Columns Differ"); 
 loader.ReadDirect(m_BattleWorldID,(tint32)ID_BATTLEWORLDID);
loader.ReadDirect(m_DBName,(tint32)ID_DBNAME);
loader.ReadDirect(m_DBPsw,(tint32)ID_DBPSW);
loader.ReadDirect(m_DBThreadCount,(tint32)ID_DBTHREADCOUNT);
loader.ReadDirect(m_DBUser,(tint32)ID_DBUSER);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_PortForClient,(tint32)ID_PORTFORCLIENT);
loader.ReadDirect(m_PortForGMI,(tint32)ID_PORTFORGMI);
loader.ReadDirect(m_PortForNewGM,(tint32)ID_PORTFORNEWGM);
loader.ReadDirect(m_PortForParallel,(tint32)ID_PORTFORPARALLEL);
loader.ReadDirect(m_SelfIp,(tint32)ID_SELFIP);
loader.ReadDirect(m_StartTime,(tint32)ID_STARTTIME);
loader.ReadDirect(m_StartTimeForExpLimit,(tint32)ID_STARTTIMEFOREXPLIMIT);
loader.ReadDirect(m_ThreadCount,(tint32)ID_THREADCOUNT);
loader.ReadDirect(m_WorldName,(tint32)ID_WORLDNAME);
loader.ReadDirect(m_WorldType,(tint32)ID_WORLDTYPE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_ServerConfigList);



