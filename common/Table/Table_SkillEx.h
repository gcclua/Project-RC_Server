//This code create by CodeEngine,don't modify
#ifndef _SkillExTABLE_H
 #define _SkillExTABLE_H
 
 #include "DBCTable.h"

class Table_SkillEx:public DBC_Recorder_Loader<Table_SkillEx,99999,5000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_SKILLEXID,
ID_BASEID=2,
ID_SKILLDESC,
ID_LEVEL,
ID_SKILLLOGIC,
ID_LOGICPARAM01,
ID_LOGICPARAM02,
ID_LOGICPARAM03,
ID_LOGICPARAM04,
ID_REFIXTHREAT,
ID_RADIUS,
ID_CDTIMEID,
ID_SKILLDELAYTIME,
ID_SKILLCONTINUETIME,
ID_DELTYPE,
ID_DELNUM,
ID_NEXTSKILLID,
ID_IMPACT_01,
ID_IMPACT_2,
ID_IMPACT_03,
ID_IMPACT_04,
ID_IMPACT_05,
ID_IMPACT_06,
ID_SATRTMOTIONID,
ID_SECONDMOTIONID,
ID_CAMERAROCKID,
ID_CAMERAROCKRATE,
ID_SCENEEFFECTID,
ID_BULLETEFFECTID_01,
ID_BULLETEFFECTID_02,
ID_BULLETEFFECTID_03,
ID_RANGEEFFECTTYPE,
ID_RANGEEFFECTTARTYPE,
ID_RANGEEFFECTSIZE01,
ID_RANGEEFFECTSIZE02,
ID_TAB_CURCOL_COUNT,
MAX_ID=99999,
MAX_RECORD=5000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_BaseId;
 public:
 tint32 GetBaseId() const { return m_BaseId; }

public:
 tint32 getBulletEffectIDCount() const { return 3; } 
 private:
 tint32 m_BulletEffectID[3];
 public:
 tint32 GetBulletEffectIDbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_BulletEffectID[idx];
 return -1;
 }

private:
 tint32 m_CDTimeId;
 public:
 tint32 GetCDTimeId() const { return m_CDTimeId; }

private:
 tint32 m_CameraRockId;
 public:
 tint32 GetCameraRockId() const { return m_CameraRockId; }

private:
 tint32 m_CameraRockRate;
 public:
 tint32 GetCameraRockRate() const { return m_CameraRockRate; }

private:
 tint32 m_DelNum;
 public:
 tint32 GetDelNum() const { return m_DelNum; }

private:
 tint32 m_DelType;
 public:
 tint32 GetDelType() const { return m_DelType; }

public:
 tint32 getImpactCount() const { return 6; } 
 private:
 tint32 m_Impact[6];
 public:
 tint32 GetImpactbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<6) return m_Impact[idx];
 return -1;
 }

public:
 tint32 getLogicParamCount() const { return 4; } 
 private:
 tint32 m_LogicParam[4];
 public:
 tint32 GetLogicParambyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_LogicParam[idx];
 return -1;
 }

private:
 tint32 m_NextSkillId;
 public:
 tint32 GetNextSkillId() const { return m_NextSkillId; }

private:
 tfloat32 m_Radius;
 public:
 tfloat32 GetRadius() const { return m_Radius; }

public:
 tint32 getRangeEffectSizeCount() const { return 2; } 
 private:
 tint32 m_RangeEffectSize[2];
 public:
 tint32 GetRangeEffectSizebyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<2) return m_RangeEffectSize[idx];
 return -1;
 }

private:
 tint32 m_RangeEffectTarType;
 public:
 tint32 GetRangeEffectTarType() const { return m_RangeEffectTarType; }

private:
 tint32 m_RangeEffectType;
 public:
 tint32 GetRangeEffectType() const { return m_RangeEffectType; }

private:
 tint32 m_RefixThreat;
 public:
 tint32 GetRefixThreat() const { return m_RefixThreat; }

private:
 tint32 m_SatrtMotionId;
 public:
 tint32 GetSatrtMotionId() const { return m_SatrtMotionId; }

private:
 tint32 m_SceneEffectId;
 public:
 tint32 GetSceneEffectId() const { return m_SceneEffectId; }

private:
 tint32 m_SecondMotionId;
 public:
 tint32 GetSecondMotionId() const { return m_SecondMotionId; }

private:
 tint32 m_SkillContinueTime;
 public:
 tint32 GetSkillContinueTime() const { return m_SkillContinueTime; }

private:
 tint32 m_SkillDelayTime;
 public:
 tint32 GetSkillDelayTime() const { return m_SkillDelayTime; }

private:
 const tchar* m_SkillDesc;
 public:
 const tchar* GetSkillDesc() const { return m_SkillDesc; }

private:
 tint32 m_SkillExID;
 public:
 tint32 GetSkillExID() const { return m_SkillExID; }

private:
 tint32 m_SkillLogic;
 public:
 tint32 GetSkillLogic() const { return m_SkillLogic; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SkillEx);
 
 //bool InitTable_SkillExTable( const tchar* szFileName );
 //bool InitTable_SkillExTableFromMemory( const DBCFile& rDB );
 //const Table_SkillEx* GetTable_SkillExByID(tint32 id);
 //const Table_SkillEx* GetTable_SkillExByIndex(tint32 index);
 //tint32 GetTable_SkillExCount(void);


 #endif
