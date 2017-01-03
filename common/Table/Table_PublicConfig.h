//This code create by CodeEngine,don't modify
#ifndef _PublicConfigTABLE_H
 #define _PublicConfigTABLE_H
 
 #include "DBCTable.h"

class Table_PublicConfig:public DBC_Recorder_Loader<Table_PublicConfig,10,10>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_KEY=2,
ID_INTVALUE,
ID_STRINGVALUE,
ID_FLOATVALUE,
ID_TAB_CURCOL_COUNT,
MAX_ID=10,
MAX_RECORD=10
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tfloat32 m_FloatValue;
 public:
 tfloat32 GetFloatValue() const { return m_FloatValue; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_IntValue;
 public:
 tint32 GetIntValue() const { return m_IntValue; }

private:
 const tchar* m_Key;
 public:
 const tchar* GetKey() const { return m_Key; }

private:
 const tchar* m_StringValue;
 public:
 const tchar* GetStringValue() const { return m_StringValue; }

};
 
 DECL_TABLE_FUNCTIONS(Table_PublicConfig);
 
 //bool InitTable_PublicConfigTable( const tchar* szFileName );
 //bool InitTable_PublicConfigTableFromMemory( const DBCFile& rDB );
 //const Table_PublicConfig* GetTable_PublicConfigByID(tint32 id);
 //const Table_PublicConfig* GetTable_PublicConfigByIndex(tint32 index);
 //tint32 GetTable_PublicConfigCount(void);


 #endif
