//This code create by CodeEngine,don't modify
#ifndef _CopySceneNpcTABLE_H
 #define _CopySceneNpcTABLE_H
 
 #include "DBCTable.h"

class Table_CopySceneNpc:public DBC_Recorder_Loader<Table_CopySceneNpc,4999,5000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_COPYSCENEID=2,
ID_DATAID_1,
ID_DATAID_2,
ID_POSX,
ID_POSZ,
ID_FACEDIRECTION,
ID_DIFFICULTY1,
ID_DIFFICULTY2,
ID_DIFFICULTY3,
ID_DIFFICULTY4,
ID_DIFFICULTYTEAM1,
ID_DIFFICULTYTEAM2,
ID_DIFFICULTYTEAM3,
ID_DIFFICULTYTEAM4,
ID_WAVE,
ID_MISSIONID,
ID_TIER,
ID_TAB_CURCOL_COUNT,
MAX_ID=4999,
MAX_RECORD=5000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_CopySceneID;
 public:
 tint32 GetCopySceneID() const { return m_CopySceneID; }

public:
 tint32 getDataIDCount() const { return 2; } 
 private:
 tint32 m_DataID[2];
 public:
 tint32 GetDataIDbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<2) return m_DataID[idx];
 return -1;
 }

public:
 tint32 getDifficultyCount() const { return 4; } 
 private:
 tint32 m_Difficulty[4];
 public:
 tint32 GetDifficultybyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_Difficulty[idx];
 return -1;
 }

public:
 tint32 getDifficultyTeamCount() const { return 4; } 
 private:
 tint32 m_DifficultyTeam[4];
 public:
 tint32 GetDifficultyTeambyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_DifficultyTeam[idx];
 return -1;
 }

private:
 tfloat32 m_FaceDirection;
 public:
 tfloat32 GetFaceDirection() const { return m_FaceDirection; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_MissionID;
 public:
 tint32 GetMissionID() const { return m_MissionID; }

private:
 tfloat32 m_PosX;
 public:
 tfloat32 GetPosX() const { return m_PosX; }

private:
 tfloat32 m_PosZ;
 public:
 tfloat32 GetPosZ() const { return m_PosZ; }

private:
 tint32 m_Tier;
 public:
 tint32 GetTier() const { return m_Tier; }

private:
 tint32 m_Wave;
 public:
 tint32 GetWave() const { return m_Wave; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CopySceneNpc);
 
 //bool InitTable_CopySceneNpcTable( const tchar* szFileName );
 //bool InitTable_CopySceneNpcTableFromMemory( const DBCFile& rDB );
 //const Table_CopySceneNpc* GetTable_CopySceneNpcByID(tint32 id);
 //const Table_CopySceneNpc* GetTable_CopySceneNpcByIndex(tint32 index);
 //tint32 GetTable_CopySceneNpcCount(void);


 #endif
