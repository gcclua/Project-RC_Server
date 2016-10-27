//This code create by CodeEngine,don't modify
#ifndef _CopySceneRuleTABLE_H
 #define _CopySceneRuleTABLE_H
 
 #include "DBCTable.h"

class Table_CopySceneRule:public DBC_Recorder_Loader<Table_CopySceneRule,1024,1025>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_STAMINA=2,
ID_LEVEL,
ID_BATTLE,
ID_NUMBER,
ID_STARTTIME,
ID_ENDTIME,
ID_EXP,
ID_MONEY,
ID_GUIDCONTRIBUTE,
ID_MASTERCONTRIBUTE,
ID_SCORE1,
ID_REWARDID1,
ID_SCORE2,
ID_REWARDID2,
ID_SCORE3,
ID_REWARDID3,
ID_SCORE4,
ID_REWARDID4,
ID_SCORE5,
ID_REWARDID5,
ID_SWEEPREWARDID,
ID_SCORECALCID,
ID_EXISTTIME,
ID_FIVESTARDIECOUNTSTRDICID,
ID_FIVESTARTIMESTRDICID,
ID_NORMALBUYYESTODAYRULE,
ID_PERFECTBUYYESTODAYRULE,
ID_TAB_CURCOL_COUNT,
MAX_ID=1024,
MAX_RECORD=1025
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Battle;
 public:
 tint32 GetBattle() const { return m_Battle; }

private:
 tint32 m_EndTime;
 public:
 tint32 GetEndTime() const { return m_EndTime; }

private:
 tint32 m_ExistTime;
 public:
 tint32 GetExistTime() const { return m_ExistTime; }

private:
 tint32 m_Exp;
 public:
 tint32 GetExp() const { return m_Exp; }

private:
 tint32 m_FiveStarDieCountStrDicID;
 public:
 tint32 GetFiveStarDieCountStrDicID() const { return m_FiveStarDieCountStrDicID; }

private:
 tint32 m_FiveStarTimeStrDicID;
 public:
 tint32 GetFiveStarTimeStrDicID() const { return m_FiveStarTimeStrDicID; }

private:
 tint32 m_GuidContribute;
 public:
 tint32 GetGuidContribute() const { return m_GuidContribute; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_MasterContribute;
 public:
 tint32 GetMasterContribute() const { return m_MasterContribute; }

private:
 tint32 m_Money;
 public:
 tint32 GetMoney() const { return m_Money; }

private:
 tint32 m_NormalBuyYestodayRule;
 public:
 tint32 GetNormalBuyYestodayRule() const { return m_NormalBuyYestodayRule; }

private:
 tint32 m_Number;
 public:
 tint32 GetNumber() const { return m_Number; }

private:
 tint32 m_PerfectBuyYestodayRule;
 public:
 tint32 GetPerfectBuyYestodayRule() const { return m_PerfectBuyYestodayRule; }

public:
 tint32 getRewardIDCount() const { return 5; } 
 private:
 tint32 m_RewardID[5];
 public:
 tint32 GetRewardIDbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<5) return m_RewardID[idx];
 return -1;
 }

public:
 tint32 getScoreCount() const { return 5; } 
 private:
 tint32 m_Score[5];
 public:
 tint32 GetScorebyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<5) return m_Score[idx];
 return -1;
 }

private:
 tint32 m_ScoreCalcID;
 public:
 tint32 GetScoreCalcID() const { return m_ScoreCalcID; }

private:
 tint32 m_Stamina;
 public:
 tint32 GetStamina() const { return m_Stamina; }

private:
 tint32 m_StartTime;
 public:
 tint32 GetStartTime() const { return m_StartTime; }

private:
 tint32 m_SweepRewardID;
 public:
 tint32 GetSweepRewardID() const { return m_SweepRewardID; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CopySceneRule);
 
 //bool InitTable_CopySceneRuleTable( const tchar* szFileName );
 //bool InitTable_CopySceneRuleTableFromMemory( const DBCFile& rDB );
 //const Table_CopySceneRule* GetTable_CopySceneRuleByID(tint32 id);
 //const Table_CopySceneRule* GetTable_CopySceneRuleByIndex(tint32 index);
 //tint32 GetTable_CopySceneRuleCount(void);


 #endif
