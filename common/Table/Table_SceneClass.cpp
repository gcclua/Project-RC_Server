//This code create by CodeEngine,don't modify
#include "Table_SceneClass.h"



















bool Table_SceneClass::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SceneClass Columns Differ"); 
 loader.ReadDirect(m_AttackPosX[0],(tint32)ID_ATTACKPOSX1);
loader.ReadDirect(m_AttackPosX[1],(tint32)ID_ATTACKPOSX2);
loader.ReadDirect(m_AttackPosX[2],(tint32)ID_ATTACKPOSX3);
loader.ReadDirect(m_AttackPosX[3],(tint32)ID_ATTACKPOSX4);
loader.ReadDirect(m_AttackPosX[4],(tint32)ID_ATTACKPOSX5);
loader.ReadDirect(m_AttackPosX[5],(tint32)ID_ATTACKPOSX6);
loader.ReadDirect(m_AttackPosX[6],(tint32)ID_ATTACKPOSX7);
loader.ReadDirect(m_AttackPosX[7],(tint32)ID_ATTACKPOSX8);
loader.ReadDirect(m_AttackPosX[8],(tint32)ID_ATTACKPOSX9);
loader.ReadDirect(m_AttackPosZ[0],(tint32)ID_ATTACKPOSZ1);
loader.ReadDirect(m_AttackPosZ[1],(tint32)ID_ATTACKPOSZ2);
loader.ReadDirect(m_AttackPosZ[2],(tint32)ID_ATTACKPOSZ3);
loader.ReadDirect(m_AttackPosZ[3],(tint32)ID_ATTACKPOSZ4);
loader.ReadDirect(m_AttackPosZ[4],(tint32)ID_ATTACKPOSZ5);
loader.ReadDirect(m_AttackPosZ[5],(tint32)ID_ATTACKPOSZ6);
loader.ReadDirect(m_AttackPosZ[6],(tint32)ID_ATTACKPOSZ7);
loader.ReadDirect(m_AttackPosZ[7],(tint32)ID_ATTACKPOSZ8);
loader.ReadDirect(m_AttackPosZ[8],(tint32)ID_ATTACKPOSZ9);
loader.ReadDirect(m_BGMusic,(tint32)ID_BGMUSIC);
loader.ReadDirect(m_CopySceneID,(tint32)ID_COPYSCENEID);
loader.ReadDirect(m_DefencePosX[0],(tint32)ID_DEFENCEPOSX1);
loader.ReadDirect(m_DefencePosX[1],(tint32)ID_DEFENCEPOSX2);
loader.ReadDirect(m_DefencePosX[2],(tint32)ID_DEFENCEPOSX3);
loader.ReadDirect(m_DefencePosX[3],(tint32)ID_DEFENCEPOSX4);
loader.ReadDirect(m_DefencePosX[4],(tint32)ID_DEFENCEPOSX5);
loader.ReadDirect(m_DefencePosX[5],(tint32)ID_DEFENCEPOSX6);
loader.ReadDirect(m_DefencePosX[6],(tint32)ID_DEFENCEPOSX7);
loader.ReadDirect(m_DefencePosX[7],(tint32)ID_DEFENCEPOSX8);
loader.ReadDirect(m_DefencePosX[8],(tint32)ID_DEFENCEPOSX9);
loader.ReadDirect(m_DefencePosZ[0],(tint32)ID_DEFENCEPOSZ1);
loader.ReadDirect(m_DefencePosZ[1],(tint32)ID_DEFENCEPOSZ2);
loader.ReadDirect(m_DefencePosZ[2],(tint32)ID_DEFENCEPOSZ3);
loader.ReadDirect(m_DefencePosZ[3],(tint32)ID_DEFENCEPOSZ4);
loader.ReadDirect(m_DefencePosZ[4],(tint32)ID_DEFENCEPOSZ5);
loader.ReadDirect(m_DefencePosZ[5],(tint32)ID_DEFENCEPOSZ6);
loader.ReadDirect(m_DefencePosZ[6],(tint32)ID_DEFENCEPOSZ7);
loader.ReadDirect(m_DefencePosZ[7],(tint32)ID_DEFENCEPOSZ8);
loader.ReadDirect(m_DefencePosZ[8],(tint32)ID_DEFENCEPOSZ9);
loader.ReadDirect(m_Length,(tint32)ID_LENGTH);
loader.ReadDirect(m_Name,(tint32)ID_NAME);
loader.ReadDirect(m_Obstacle,(tint32)ID_OBSTACLE);
loader.ReadDirect(m_PlayerViewRadius,(tint32)ID_PLAYERVIEWRADIUS);
loader.ReadDirect(m_ResName,(tint32)ID_RESNAME);
loader.ReadDirect(m_SceneID,(tint32)ID_SCENEID);
loader.ReadDirect(m_SceneMapHeight,(tint32)ID_SCENEMAPHEIGHT);
loader.ReadDirect(m_SceneMapLogicWidth,(tint32)ID_SCENEMAPLOGICWIDTH);
loader.ReadDirect(m_SceneMapTexture,(tint32)ID_SCENEMAPTEXTURE);
loader.ReadDirect(m_SceneMapWidth,(tint32)ID_SCENEMAPWIDTH);
loader.ReadDirect(m_Type,(tint32)ID_TYPE);
loader.ReadDirect(m_Width,(tint32)ID_WIDTH);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_SceneClass);



