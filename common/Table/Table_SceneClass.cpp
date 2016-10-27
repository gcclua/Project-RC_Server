//This code create by CodeEngine,don't modify
#include "Table_SceneClass.h"





























bool Table_SceneClass::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SceneClass Columns Differ"); 
 loader.ReadDirect(m_BGMusic,(tint32)ID_BGMUSIC);
loader.ReadDirect(m_CopySceneID,(tint32)ID_COPYSCENEID);
loader.ReadDirect(m_DeadPunishRule,(tint32)ID_DEADPUNISHRULE);
loader.ReadDirect(m_EntryX,(tint32)ID_ENTRY_X);
loader.ReadDirect(m_EntryZ,(tint32)ID_ENTRY_Z);
loader.ReadDirect(m_IsCanCallTeam,(tint32)ID_ISCANCALLTEAM);
loader.ReadDirect(m_IsCanTeamFollow,(tint32)ID_ISCANTEAMFOLLOW);
loader.ReadDirect(m_IsCanUseLight,(tint32)ID_ISCANUSELIGHT);
loader.ReadDirect(m_IsCanUseXp,(tint32)ID_ISCANUSEXP);
loader.ReadDirect(m_Length,(tint32)ID_LENGTH);
loader.ReadDirect(m_Name,(tint32)ID_NAME);
loader.ReadDirect(m_Obstacle,(tint32)ID_OBSTACLE);
loader.ReadDirect(m_PVPRule,(tint32)ID_PVPRULE);
loader.ReadDirect(m_PlayerViewRadius,(tint32)ID_PLAYERVIEWRADIUS);
loader.ReadDirect(m_PlayersMaxA,(tint32)ID_PLAYERSMAXA);
loader.ReadDirect(m_PlayersMaxB,(tint32)ID_PLAYERSMAXB);
loader.ReadDirect(m_ReliveType[0],(tint32)ID_RELIVETYPE_1);
loader.ReadDirect(m_ReliveType[1],(tint32)ID_RELIVETYPE_2);
loader.ReadDirect(m_ReliveType[2],(tint32)ID_RELIVETYPE_3);
loader.ReadDirect(m_ResName,(tint32)ID_RESNAME);
loader.ReadDirect(m_SafeX,(tint32)ID_SAFE_X);
loader.ReadDirect(m_SafeZ,(tint32)ID_SAFE_Z);
loader.ReadDirect(m_SceneID,(tint32)ID_SCENEID);
loader.ReadDirect(m_SceneMapHeight,(tint32)ID_SCENEMAPHEIGHT);
loader.ReadDirect(m_SceneMapLogicWidth,(tint32)ID_SCENEMAPLOGICWIDTH);
loader.ReadDirect(m_SceneMapTexture,(tint32)ID_SCENEMAPTEXTURE);
loader.ReadDirect(m_SceneMapWidth,(tint32)ID_SCENEMAPWIDTH);
loader.ReadDirect(m_ScriptID,(tint32)ID_SCRIPTID);
loader.ReadDirect(m_Type,(tint32)ID_TYPE);
loader.ReadDirect(m_Width,(tint32)ID_WIDTH);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_SceneClass);



