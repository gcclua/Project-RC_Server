//This code create by CodeEngine,don't modify
#ifndef _SceneClassTABLE_H
 #define _SceneClassTABLE_H
 
 #include "DBCTable.h"

class Table_SceneClass:public DBC_Recorder_Loader<Table_SceneClass,1023,1024>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_SCENEID,
ID_NAME=2,
ID_RESNAME,
ID_TYPE,
ID_LENGTH,
ID_WIDTH,
ID_OBSTACLE,
ID_BGMUSIC,
ID_COPYSCENEID,
ID_SCENEMAPTEXTURE,
ID_SCENEMAPWIDTH,
ID_SCENEMAPHEIGHT,
ID_SCENEMAPLOGICWIDTH,
ID_PLAYERVIEWRADIUS,
ID_ATTACKPOSX1,
ID_ATTACKPOSZ1,
ID_ATTACKPOSX2,
ID_ATTACKPOSZ2,
ID_ATTACKPOSX3,
ID_ATTACKPOSZ3,
ID_ATTACKPOSX4,
ID_ATTACKPOSZ4,
ID_ATTACKPOSX5,
ID_ATTACKPOSZ5,
ID_ATTACKPOSX6,
ID_ATTACKPOSZ6,
ID_ATTACKPOSX7,
ID_ATTACKPOSZ7,
ID_ATTACKPOSX8,
ID_ATTACKPOSZ8,
ID_ATTACKPOSX9,
ID_ATTACKPOSZ9,
ID_ATTACKPOSX10,
ID_ATTACKPOSZ10,
ID_ATTACKPOSX11,
ID_ATTACKPOSZ11,
ID_DEFENCEPOSX1,
ID_DEFENCEPOSZ1,
ID_DEFENCEPOSX2,
ID_DEFENCEPOSZ2,
ID_DEFENCEPOSX3,
ID_DEFENCEPOSZ3,
ID_DEFENCEPOSX4,
ID_DEFENCEPOSZ4,
ID_DEFENCEPOSX5,
ID_DEFENCEPOSZ5,
ID_DEFENCEPOSX6,
ID_DEFENCEPOSZ6,
ID_DEFENCEPOSX7,
ID_DEFENCEPOSZ7,
ID_DEFENCEPOSX8,
ID_DEFENCEPOSZ8,
ID_DEFENCEPOSX9,
ID_DEFENCEPOSZ9,
ID_DEFENCEPOSX10,
ID_DEFENCEPOSZ10,
ID_DEFENCEPOSX11,
ID_DEFENCEPOSZ11,
ID_TAB_CURCOL_COUNT,
MAX_ID=1023,
MAX_RECORD=1024
 };
 public:
 bool __Load(DBC_Loader &loader);

public:
 tint32 getAttackPosXCount() const { return 11; } 
 private:
 tint32 m_AttackPosX[11];
 public:
 tint32 GetAttackPosXbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<11) return m_AttackPosX[idx];
 return -1;
 }

public:
 tint32 getAttackPosZCount() const { return 11; } 
 private:
 tint32 m_AttackPosZ[11];
 public:
 tint32 GetAttackPosZbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<11) return m_AttackPosZ[idx];
 return -1;
 }

private:
 tint32 m_BGMusic;
 public:
 tint32 GetBGMusic() const { return m_BGMusic; }

private:
 tint32 m_CopySceneID;
 public:
 tint32 GetCopySceneID() const { return m_CopySceneID; }

public:
 tint32 getDefencePosXCount() const { return 11; } 
 private:
 tint32 m_DefencePosX[11];
 public:
 tint32 GetDefencePosXbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<11) return m_DefencePosX[idx];
 return -1;
 }

public:
 tint32 getDefencePosZCount() const { return 11; } 
 private:
 tint32 m_DefencePosZ[11];
 public:
 tint32 GetDefencePosZbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<11) return m_DefencePosZ[idx];
 return -1;
 }

private:
 tint32 m_Length;
 public:
 tint32 GetLength() const { return m_Length; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

private:
 const tchar* m_Obstacle;
 public:
 const tchar* GetObstacle() const { return m_Obstacle; }

private:
 tint32 m_PlayerViewRadius;
 public:
 tint32 GetPlayerViewRadius() const { return m_PlayerViewRadius; }

private:
 const tchar* m_ResName;
 public:
 const tchar* GetResName() const { return m_ResName; }

private:
 tint32 m_SceneID;
 public:
 tint32 GetSceneID() const { return m_SceneID; }

private:
 tint32 m_SceneMapHeight;
 public:
 tint32 GetSceneMapHeight() const { return m_SceneMapHeight; }

private:
 tint32 m_SceneMapLogicWidth;
 public:
 tint32 GetSceneMapLogicWidth() const { return m_SceneMapLogicWidth; }

private:
 const tchar* m_SceneMapTexture;
 public:
 const tchar* GetSceneMapTexture() const { return m_SceneMapTexture; }

private:
 tint32 m_SceneMapWidth;
 public:
 tint32 GetSceneMapWidth() const { return m_SceneMapWidth; }

private:
 tint32 m_Type;
 public:
 tint32 GetType() const { return m_Type; }

private:
 tint32 m_Width;
 public:
 tint32 GetWidth() const { return m_Width; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SceneClass);
 
 //bool InitTable_SceneClassTable( const tchar* szFileName );
 //bool InitTable_SceneClassTableFromMemory( const DBCFile& rDB );
 //const Table_SceneClass* GetTable_SceneClassByID(tint32 id);
 //const Table_SceneClass* GetTable_SceneClassByIndex(tint32 index);
 //tint32 GetTable_SceneClassCount(void);


 #endif
