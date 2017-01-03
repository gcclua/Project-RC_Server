//This code create by CodeEngine,don't modify
#include "Table_CopySceneNpc.h"












bool Table_CopySceneNpc::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CopySceneNpc Columns Differ"); 
 loader.ReadDirect(m_CopySceneID,(tint32)ID_COPYSCENEID);
loader.ReadDirect(m_DataID[0],(tint32)ID_DATAID_1);
loader.ReadDirect(m_DataID[1],(tint32)ID_DATAID_2);
loader.ReadDirect(m_Difficulty[0],(tint32)ID_DIFFICULTY1);
loader.ReadDirect(m_Difficulty[1],(tint32)ID_DIFFICULTY2);
loader.ReadDirect(m_Difficulty[2],(tint32)ID_DIFFICULTY3);
loader.ReadDirect(m_Difficulty[3],(tint32)ID_DIFFICULTY4);
loader.ReadDirect(m_DifficultyTeam[0],(tint32)ID_DIFFICULTYTEAM1);
loader.ReadDirect(m_DifficultyTeam[1],(tint32)ID_DIFFICULTYTEAM2);
loader.ReadDirect(m_DifficultyTeam[2],(tint32)ID_DIFFICULTYTEAM3);
loader.ReadDirect(m_DifficultyTeam[3],(tint32)ID_DIFFICULTYTEAM4);
loader.ReadDirect(m_FaceDirection,(tint32)ID_FACEDIRECTION);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_MissionID,(tint32)ID_MISSIONID);
loader.ReadDirect(m_PosX,(tint32)ID_POSX);
loader.ReadDirect(m_PosZ,(tint32)ID_POSZ);
loader.ReadDirect(m_Tier,(tint32)ID_TIER);
loader.ReadDirect(m_Wave,(tint32)ID_WAVE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_CopySceneNpc);



