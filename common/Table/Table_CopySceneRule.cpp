//This code create by CodeEngine,don't modify
#include "Table_CopySceneRule.h"





















bool Table_CopySceneRule::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CopySceneRule Columns Differ"); 
 loader.ReadDirect(m_Battle,(tint32)ID_BATTLE);
loader.ReadDirect(m_EndTime,(tint32)ID_ENDTIME);
loader.ReadDirect(m_ExistTime,(tint32)ID_EXISTTIME);
loader.ReadDirect(m_Exp,(tint32)ID_EXP);
loader.ReadDirect(m_FiveStarDieCountStrDicID,(tint32)ID_FIVESTARDIECOUNTSTRDICID);
loader.ReadDirect(m_FiveStarTimeStrDicID,(tint32)ID_FIVESTARTIMESTRDICID);
loader.ReadDirect(m_GuidContribute,(tint32)ID_GUIDCONTRIBUTE);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_MasterContribute,(tint32)ID_MASTERCONTRIBUTE);
loader.ReadDirect(m_Money,(tint32)ID_MONEY);
loader.ReadDirect(m_NormalBuyYestodayRule,(tint32)ID_NORMALBUYYESTODAYRULE);
loader.ReadDirect(m_Number,(tint32)ID_NUMBER);
loader.ReadDirect(m_PerfectBuyYestodayRule,(tint32)ID_PERFECTBUYYESTODAYRULE);
loader.ReadDirect(m_RewardID[0],(tint32)ID_REWARDID1);
loader.ReadDirect(m_RewardID[1],(tint32)ID_REWARDID2);
loader.ReadDirect(m_RewardID[2],(tint32)ID_REWARDID3);
loader.ReadDirect(m_RewardID[3],(tint32)ID_REWARDID4);
loader.ReadDirect(m_RewardID[4],(tint32)ID_REWARDID5);
loader.ReadDirect(m_Score[0],(tint32)ID_SCORE1);
loader.ReadDirect(m_Score[1],(tint32)ID_SCORE2);
loader.ReadDirect(m_Score[2],(tint32)ID_SCORE3);
loader.ReadDirect(m_Score[3],(tint32)ID_SCORE4);
loader.ReadDirect(m_Score[4],(tint32)ID_SCORE5);
loader.ReadDirect(m_ScoreCalcID,(tint32)ID_SCORECALCID);
loader.ReadDirect(m_Stamina,(tint32)ID_STAMINA);
loader.ReadDirect(m_StartTime,(tint32)ID_STARTTIME);
loader.ReadDirect(m_SweepRewardID,(tint32)ID_SWEEPREWARDID);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_CopySceneRule);



