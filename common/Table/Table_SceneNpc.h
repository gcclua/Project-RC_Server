//This code create by CodeEngine,don't modify
#ifndef _SceneNpcTABLE_H
 #define _SceneNpcTABLE_H
 
 #include "DBCTable.h"

class Table_SceneNpc:public DBC_Recorder_Loader<Table_SceneNpc,4999,5000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_SCENEID=2,
ID_DATAID,
ID_POSX,
ID_POSZ,
ID_FACEDIRECTION,
ID_GROUPID,
ID_MUTEXID,
ID_TAB_CURCOL_COUNT,
MAX_ID=4999,
MAX_RECORD=5000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_DataID;
 public:
 tint32 GetDataID() const { return m_DataID; }

private:
 tfloat32 m_FaceDirection;
 public:
 tfloat32 GetFaceDirection() const { return m_FaceDirection; }

private:
 tint32 m_GroupID;
 public:
 tint32 GetGroupID() const { return m_GroupID; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_MutexID;
 public:
 tint32 GetMutexID() const { return m_MutexID; }

private:
 tfloat32 m_PosX;
 public:
 tfloat32 GetPosX() const { return m_PosX; }

private:
 tfloat32 m_PosZ;
 public:
 tfloat32 GetPosZ() const { return m_PosZ; }

private:
 tint32 m_SceneID;
 public:
 tint32 GetSceneID() const { return m_SceneID; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SceneNpc);
 
 //bool InitTable_SceneNpcTable( const tchar* szFileName );
 //bool InitTable_SceneNpcTableFromMemory( const DBCFile& rDB );
 //const Table_SceneNpc* GetTable_SceneNpcByID(tint32 id);
 //const Table_SceneNpc* GetTable_SceneNpcByIndex(tint32 index);
 //tint32 GetTable_SceneNpcCount(void);


 #endif
