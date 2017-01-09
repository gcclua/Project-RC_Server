//This code create by CodeEngine,don't modify
#ifndef _ArrangeSelectTargetTABLE_H
 #define _ArrangeSelectTargetTABLE_H
 
 #include "DBCTable.h"

class Table_ArrangeSelectTarget:public DBC_Recorder_Loader<Table_ArrangeSelectTarget,20,20>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_SCENECLASS=2,
ID_FORCE,
ID_ARRANGEINDEX,
ID_TARGETPOS1,
ID_TARGETPOS2,
ID_TARGETPOS3,
ID_TARGETPOS4,
ID_TARGETPOS5,
ID_TARGETPOS6,
ID_TARGETPOS7,
ID_TARGETPOS8,
ID_TARGETPOS9,
ID_TARGETPOS10,
ID_TARGETPOS11,
ID_MARCHLINEX1,
ID_MARCHLINEZ1,
ID_MARCHLINEX2,
ID_MARCHLINEZ2,
ID_MARCHLINEX3,
ID_MARCHLINEZ3,
ID_MARCHLINEX4,
ID_MARCHLINEZ4,
ID_SELECTRADIUS1,
ID_SELECTRADIUS2,
ID_SELECTRADIUS3,
ID_TAB_CURCOL_COUNT,
MAX_ID=20,
MAX_RECORD=20
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_ArrangeIndex;
 public:
 tint32 GetArrangeIndex() const { return m_ArrangeIndex; }

private:
 tint32 m_Force;
 public:
 tint32 GetForce() const { return m_Force; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

public:
 tint32 getMarchLineXCount() const { return 4; } 
 private:
 tint32 m_MarchLineX[4];
 public:
 tint32 GetMarchLineXbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_MarchLineX[idx];
 return -1;
 }

public:
 tint32 getMarchLineZCount() const { return 4; } 
 private:
 tint32 m_MarchLineZ[4];
 public:
 tint32 GetMarchLineZbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_MarchLineZ[idx];
 return -1;
 }

private:
 tint32 m_SceneClass;
 public:
 tint32 GetSceneClass() const { return m_SceneClass; }

public:
 tint32 getSelectRadiusCount() const { return 3; } 
 private:
 tfloat32 m_SelectRadius[3];
 public:
 tfloat32 GetSelectRadiusbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_SelectRadius[idx];
 return 0.0f;
 }

public:
 tint32 getTargetPosCount() const { return 11; } 
 private:
 tint32 m_TargetPos[11];
 public:
 tint32 GetTargetPosbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<11) return m_TargetPos[idx];
 return -1;
 }

};
 
 DECL_TABLE_FUNCTIONS(Table_ArrangeSelectTarget);
 
 //bool InitTable_ArrangeSelectTargetTable( const tchar* szFileName );
 //bool InitTable_ArrangeSelectTargetTableFromMemory( const DBCFile& rDB );
 //const Table_ArrangeSelectTarget* GetTable_ArrangeSelectTargetByID(tint32 id);
 //const Table_ArrangeSelectTarget* GetTable_ArrangeSelectTargetByIndex(tint32 index);
 //tint32 GetTable_ArrangeSelectTargetCount(void);


 #endif
