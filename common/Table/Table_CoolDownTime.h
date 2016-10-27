//This code create by CodeEngine,don't modify
#ifndef _CoolDownTimeTABLE_H
 #define _CoolDownTimeTABLE_H
 
 #include "DBCTable.h"

class Table_CoolDownTime:public DBC_Recorder_Loader<Table_CoolDownTime,100000,100000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_CDTIME=2,
ID_TAB_CURCOL_COUNT,
MAX_ID=100000,
MAX_RECORD=100000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_CDTime;
 public:
 tint32 GetCDTime() const { return m_CDTime; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CoolDownTime);
 
 //bool InitTable_CoolDownTimeTable( const tchar* szFileName );
 //bool InitTable_CoolDownTimeTableFromMemory( const DBCFile& rDB );
 //const Table_CoolDownTime* GetTable_CoolDownTimeByID(tint32 id);
 //const Table_CoolDownTime* GetTable_CoolDownTimeByIndex(tint32 index);
 //tint32 GetTable_CoolDownTimeCount(void);


 #endif
