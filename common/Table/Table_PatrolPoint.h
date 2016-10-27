//This code create by CodeEngine,don't modify
#ifndef _PatrolPointTABLE_H
 #define _PatrolPointTABLE_H
 
 #include "DBCTable.h"

class Table_PatrolPoint:public DBC_Recorder_Loader<Table_PatrolPoint,1024,1025>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_MARK=2,
ID_POSX,
ID_POSZ,
ID_NEXTINDEX,
ID_ACTION,
ID_P1,
ID_P2,
ID_P3,
ID_TAB_CURCOL_COUNT,
MAX_ID=1024,
MAX_RECORD=1025
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Action;
 public:
 tint32 GetAction() const { return m_Action; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_Mark;
 public:
 tint32 GetMark() const { return m_Mark; }

private:
 tint32 m_NextIndex;
 public:
 tint32 GetNextIndex() const { return m_NextIndex; }

public:
 tint32 getPCount() const { return 3; } 
 private:
 tint32 m_P[3];
 public:
 tint32 GetPbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_P[idx];
 return -1;
 }

private:
 tint32 m_Posx;
 public:
 tint32 GetPosx() const { return m_Posx; }

private:
 tint32 m_Posz;
 public:
 tint32 GetPosz() const { return m_Posz; }

};
 
 DECL_TABLE_FUNCTIONS(Table_PatrolPoint);
 
 //bool InitTable_PatrolPointTable( const tchar* szFileName );
 //bool InitTable_PatrolPointTableFromMemory( const DBCFile& rDB );
 //const Table_PatrolPoint* GetTable_PatrolPointByID(tint32 id);
 //const Table_PatrolPoint* GetTable_PatrolPointByIndex(tint32 index);
 //tint32 GetTable_PatrolPointCount(void);


 #endif
