//This code create by CodeEngine,don't modify
#include "Table_ArrangeSelectTarget.h"









bool Table_ArrangeSelectTarget::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "ArrangeSelectTarget Columns Differ"); 
 loader.ReadDirect(m_ArrangeIndex,(tint32)ID_ARRANGEINDEX);
loader.ReadDirect(m_Force,(tint32)ID_FORCE);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_MarchLineX[0],(tint32)ID_MARCHLINEX1);
loader.ReadDirect(m_MarchLineX[1],(tint32)ID_MARCHLINEX2);
loader.ReadDirect(m_MarchLineX[2],(tint32)ID_MARCHLINEX3);
loader.ReadDirect(m_MarchLineX[3],(tint32)ID_MARCHLINEX4);
loader.ReadDirect(m_MarchLineZ[0],(tint32)ID_MARCHLINEZ1);
loader.ReadDirect(m_MarchLineZ[1],(tint32)ID_MARCHLINEZ2);
loader.ReadDirect(m_MarchLineZ[2],(tint32)ID_MARCHLINEZ3);
loader.ReadDirect(m_MarchLineZ[3],(tint32)ID_MARCHLINEZ4);
loader.ReadDirect(m_SceneClass,(tint32)ID_SCENECLASS);
loader.ReadDirect(m_SelectRadius[0],(tint32)ID_SELECTRADIUS1);
loader.ReadDirect(m_SelectRadius[1],(tint32)ID_SELECTRADIUS2);
loader.ReadDirect(m_SelectRadius[2],(tint32)ID_SELECTRADIUS3);
loader.ReadDirect(m_TargetPos[0],(tint32)ID_TARGETPOS1);
loader.ReadDirect(m_TargetPos[1],(tint32)ID_TARGETPOS2);
loader.ReadDirect(m_TargetPos[2],(tint32)ID_TARGETPOS3);
loader.ReadDirect(m_TargetPos[3],(tint32)ID_TARGETPOS4);
loader.ReadDirect(m_TargetPos[4],(tint32)ID_TARGETPOS5);
loader.ReadDirect(m_TargetPos[5],(tint32)ID_TARGETPOS6);
loader.ReadDirect(m_TargetPos[6],(tint32)ID_TARGETPOS7);
loader.ReadDirect(m_TargetPos[7],(tint32)ID_TARGETPOS8);
loader.ReadDirect(m_TargetPos[8],(tint32)ID_TARGETPOS9);
loader.ReadDirect(m_TargetPos[9],(tint32)ID_TARGETPOS10);
loader.ReadDirect(m_TargetPos[10],(tint32)ID_TARGETPOS11);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_ArrangeSelectTarget);



