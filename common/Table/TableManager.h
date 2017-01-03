//This code create by CodeEngine,don't modify
#ifndef _GAMETABLE_
 #define _GAMETABLE_
 #include "BaseType.h"
 #include "Table_ArrangeSelectTarget.h"
#include "Table_Building.h"
#include "Table_CityBuildingDefault.h"
#include "Table_CityBuildingLevel.h"
#include "Table_CityBuildingSlot.h"
#include "Table_CoolDownTime.h"
#include "Table_CopyScene.h"
#include "Table_CopySceneNpc.h"
#include "Table_CopySceneRule.h"
#include "Table_Hero.h"
#include "Table_Impact.h"
#include "Table_InitialCombatAttr.h"
#include "Table_NameFilter.h"
#include "Table_NpcOptionalSkill.h"
#include "Table_NpcSkillStrategy.h"
#include "Table_PatrolPoint.h"
#include "Table_PublicConfig.h"
#include "Table_RoleBaseAttr.h"
#include "Table_SceneClass.h"
#include "Table_SceneNpc.h"
#include "Table_ServerConfigList.h"
#include "Table_SkillActive.h"
#include "Table_SkillBase.h"
#include "Table_SkillEx.h"
#include "Table_SnareObjBuffInfo.h"
#include "Table_SnareObjInfo.h"
#include "Table_Troop.h"






























bool InitTable()
 {
 __ENTER_FUNCTION
 
 bool bRet=true;
 DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/ArrangeSelectTarget.txt ..."); 
 bRet &= InitTable_ArrangeSelectTargetTable("Config/ArrangeSelectTarget.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/ArrangeSelectTarget.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/ArrangeSelectTarget.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/ArrangeSelectTarget.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/Building.txt ..."); 
 bRet &= InitTable_BuildingTable("Config/Building.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Building.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/Building.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Building.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CityBuildingDefault.txt ..."); 
 bRet &= InitTable_CityBuildingDefaultTable("Config/CityBuildingDefault.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CityBuildingDefault.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CityBuildingDefault.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CityBuildingDefault.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CityBuildingLevel.txt ..."); 
 bRet &= InitTable_CityBuildingLevelTable("Config/CityBuildingLevel.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CityBuildingLevel.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CityBuildingLevel.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CityBuildingLevel.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CityBuildingSlot.txt ..."); 
 bRet &= InitTable_CityBuildingSlotTable("Config/CityBuildingSlot.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CityBuildingSlot.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CityBuildingSlot.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CityBuildingSlot.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CoolDownTime.txt ..."); 
 bRet &= InitTable_CoolDownTimeTable("Config/CoolDownTime.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CoolDownTime.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CoolDownTime.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CoolDownTime.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CopyScene.txt ..."); 
 bRet &= InitTable_CopySceneTable("Config/CopyScene.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CopyScene.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CopyScene.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CopyScene.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CopySceneNpc.txt ..."); 
 bRet &= InitTable_CopySceneNpcTable("Config/CopySceneNpc.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CopySceneNpc.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CopySceneNpc.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CopySceneNpc.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/CopySceneRule.txt ..."); 
 bRet &= InitTable_CopySceneRuleTable("Config/CopySceneRule.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CopySceneRule.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/CopySceneRule.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/CopySceneRule.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/Hero.txt ..."); 
 bRet &= InitTable_HeroTable("Config/Hero.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Hero.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/Hero.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Hero.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/Impact.txt ..."); 
 bRet &= InitTable_ImpactTable("Config/Impact.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Impact.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/Impact.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Impact.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/InitialCombatAttr.txt ..."); 
 bRet &= InitTable_InitialCombatAttrTable("Config/InitialCombatAttr.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/InitialCombatAttr.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/InitialCombatAttr.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/InitialCombatAttr.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/NameFilter.txt ..."); 
 bRet &= InitTable_NameFilterTable("Config/NameFilter.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/NameFilter.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/NameFilter.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/NameFilter.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/NpcOptionalSkill.txt ..."); 
 bRet &= InitTable_NpcOptionalSkillTable("Config/NpcOptionalSkill.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/NpcOptionalSkill.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/NpcOptionalSkill.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/NpcOptionalSkill.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/NpcSkillStrategy.txt ..."); 
 bRet &= InitTable_NpcSkillStrategyTable("Config/NpcSkillStrategy.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/NpcSkillStrategy.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/NpcSkillStrategy.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/NpcSkillStrategy.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/PatrolPoint.txt ..."); 
 bRet &= InitTable_PatrolPointTable("Config/PatrolPoint.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/PatrolPoint.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/PatrolPoint.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/PatrolPoint.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/PublicConfig.txt ..."); 
 bRet &= InitTable_PublicConfigTable("Config/PublicConfig.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/PublicConfig.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/PublicConfig.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/PublicConfig.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/RoleBaseAttr.txt ..."); 
 bRet &= InitTable_RoleBaseAttrTable("Config/RoleBaseAttr.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/RoleBaseAttr.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/RoleBaseAttr.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/RoleBaseAttr.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SceneClass.txt ..."); 
 bRet &= InitTable_SceneClassTable("Config/SceneClass.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SceneClass.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SceneClass.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SceneClass.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SceneNpc.txt ..."); 
 bRet &= InitTable_SceneNpcTable("Config/SceneNpc.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SceneNpc.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SceneNpc.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SceneNpc.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/ServerConfigList.txt ..."); 
 bRet &= InitTable_ServerConfigListTable("Config/ServerConfigList.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/ServerConfigList.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/ServerConfigList.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/ServerConfigList.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SkillActive.txt ..."); 
 bRet &= InitTable_SkillActiveTable("Config/SkillActive.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SkillActive.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SkillActive.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SkillActive.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SkillBase.txt ..."); 
 bRet &= InitTable_SkillBaseTable("Config/SkillBase.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SkillBase.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SkillBase.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SkillBase.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SkillEx.txt ..."); 
 bRet &= InitTable_SkillExTable("Config/SkillEx.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SkillEx.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SkillEx.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SkillEx.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SnareObjBuffInfo.txt ..."); 
 bRet &= InitTable_SnareObjBuffInfoTable("Config/SnareObjBuffInfo.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SnareObjBuffInfo.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SnareObjBuffInfo.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SnareObjBuffInfo.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/SnareObjInfo.txt ..."); 
 bRet &= InitTable_SnareObjInfoTable("Config/SnareObjInfo.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SnareObjInfo.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/SnareObjInfo.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/SnareObjInfo.txt Failed"); 
 }

DiskLog(LOGDEF_INST(ServerStatus),"Start Loading Table Config/Troop.txt ..."); 
 bRet &= InitTable_TroopTable("Config/Troop.txt");
 if(bRet)
 {
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Troop.txt OK"); 
 }
 else
 {
 AssertEx(false, "Load Table Config/Troop.txt Failed");
 DiskLog(LOGDEF_INST(ServerStatus),"Load Table Config/Troop.txt Failed"); 
 }


 return bRet;
 __LEAVE_FUNCTION
 return false;
 }




























#endif

