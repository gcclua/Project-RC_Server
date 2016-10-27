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
ID_PVPRULE,
ID_RELIVETYPE_1,
ID_RELIVETYPE_2,
ID_RELIVETYPE_3,
ID_ENTRY_X,
ID_ENTRY_Z,
ID_SAFE_X,
ID_SAFE_Z,
ID_DEADPUNISHRULE,
ID_COPYSCENEID,
ID_PLAYERSMAXA,
ID_PLAYERSMAXB,
ID_ISCANUSEXP,
ID_ISCANUSELIGHT,
ID_SCENEMAPTEXTURE,
ID_SCENEMAPWIDTH,
ID_SCENEMAPHEIGHT,
ID_SCENEMAPLOGICWIDTH,
ID_PLAYERVIEWRADIUS,
ID_ISCANTEAMFOLLOW,
ID_ISCANCALLTEAM,
ID_SCRIPTID,
ID_TAB_CURCOL_COUNT,
MAX_ID=1023,
MAX_RECORD=1024
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_BGMusic;
 public:
 tint32 GetBGMusic() const { return m_BGMusic; }

private:
 tint32 m_CopySceneID;
 public:
 tint32 GetCopySceneID() const { return m_CopySceneID; }

private:
 tint32 m_DeadPunishRule;
 public:
 tint32 GetDeadPunishRule() const { return m_DeadPunishRule; }

private:
 tfloat32 m_EntryX;
 public:
 tfloat32 GetEntryX() const { return m_EntryX; }

private:
 tfloat32 m_EntryZ;
 public:
 tfloat32 GetEntryZ() const { return m_EntryZ; }

private:
 tint32 m_IsCanCallTeam;
 public:
 tint32 GetIsCanCallTeam() const { return m_IsCanCallTeam; }

private:
 tint32 m_IsCanTeamFollow;
 public:
 tint32 GetIsCanTeamFollow() const { return m_IsCanTeamFollow; }

private:
 tint32 m_IsCanUseLight;
 public:
 tint32 GetIsCanUseLight() const { return m_IsCanUseLight; }

private:
 tint32 m_IsCanUseXp;
 public:
 tint32 GetIsCanUseXp() const { return m_IsCanUseXp; }

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
 tint32 m_PVPRule;
 public:
 tint32 GetPVPRule() const { return m_PVPRule; }

private:
 tint32 m_PlayerViewRadius;
 public:
 tint32 GetPlayerViewRadius() const { return m_PlayerViewRadius; }

private:
 tint32 m_PlayersMaxA;
 public:
 tint32 GetPlayersMaxA() const { return m_PlayersMaxA; }

private:
 tint32 m_PlayersMaxB;
 public:
 tint32 GetPlayersMaxB() const { return m_PlayersMaxB; }

public:
 tint32 getReliveTypeCount() const { return 3; } 
 private:
 tint32 m_ReliveType[3];
 public:
 tint32 GetReliveTypebyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_ReliveType[idx];
 return -1;
 }

private:
 const tchar* m_ResName;
 public:
 const tchar* GetResName() const { return m_ResName; }

private:
 tfloat32 m_SafeX;
 public:
 tfloat32 GetSafeX() const { return m_SafeX; }

private:
 tfloat32 m_SafeZ;
 public:
 tfloat32 GetSafeZ() const { return m_SafeZ; }

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
 tint32 m_ScriptID;
 public:
 tint32 GetScriptID() const { return m_ScriptID; }

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
