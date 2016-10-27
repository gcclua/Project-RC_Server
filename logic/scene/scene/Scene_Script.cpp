#include "Scene.h"
#include "Config.h"
#include "Table/Table_ScriptData.h"

#include "Scene/Script/Script_Obj.h"
#include "Scene/Script/Script_Character.h"
#include "Scene/Script/Script_User.h"
#include "Scene/Script/Script_Scene.h"
#include "Scene/Script/Script_User_Mission.h"
#include "Scene/Script/Script_User_Item.h"
#include "Scene/Script/Script_User_Additon.h"
#include "Scene/Script/Script_User_Fellow.h"
#include "Scene/Script/Script_Guild.h"
#include "Scene/Script/Script_User_Activity.h"

void Scene::LuaInit(void)
{
	__ENTER_PROTECT

	m_L = luaLL_newstate(this);
	AssertEx(m_L != null_ptr, "");

	luaL_openlibs(m_L);

	LuaRegisterAll();

	AssertEx(LuaLoad(0), "");

	if (_GameConfig().m_bLoadAllScriptOnInit)
	{
		VerifyEx(LuaLoadAll(), "");
	}

	CacheLog(LOGDEF_INST(Lua), "scene init lua, ok, scene(%d,%d)",
		GetSceneClassID(), GetSceneInstID());

	__LEAVE_PROTECT
}

void Scene::LuaClose(void)
{
	__ENTER_PROTECT

	lua_close(m_L);
	m_L = null_ptr;

	CacheLog(LOGDEF_INST(Lua), "scene close lua, ok, scene(%d,%d)",
		GetSceneClassID(), GetSceneInstID());

	__LEAVE_PROTECT
}

void Scene::LuaRegisterAll(void)
{
	__ENTER_PROTECT

	AssertEx(m_L != null_ptr, "");

	//Obj
	lua_register(m_L, "C_GetScenePos", C_GetScenePos);
	lua_register(m_L, "C_ForceSetScenePos", C_ForceSetScenePos);
	lua_register(m_L, "C_ForceSetFellowScenePos", C_ForceSetFellowScenePos);
	lua_register(m_L, "C_IsNpcInScene", C_IsNpcInScene);
	lua_register(m_L, "C_DelNpcByObjID", C_DelNpcByObjID);
	lua_register(m_L, "C_DelZombieByObjID", C_DelZombieByObjID);
	lua_register(m_L, "C_GetCurHp", C_GetCurHp);
	lua_register(m_L, "C_GetMaxHp", C_GetMaxHp);
	lua_register(m_L, "C_IncreaseHp", C_IncreaseHp);
	lua_register(m_L, "C_ForceDecHp", C_ForceDecHp);
	lua_register(m_L, "C_GetCharMP", C_GetCharMP);
	lua_register(m_L, "C_IncCharMP", C_IncCharMP);
	lua_register(m_L, "C_ForceKill", C_ForceKill);
	lua_register(m_L, "C_GetRandomNearUserObjID", C_GetRandomNearUserObjID);
	lua_register(m_L, "C_IsHaveImpact", C_IsHaveImpact);
	lua_register(m_L, "C_SendImpactToUnit", C_SendImpactToUnit);
	lua_register(m_L, "C_RemoveImpactByID", C_RemoveImpactByID);
	lua_register(m_L, "C_GetNpcCountByDataID", C_GetNpcCountByDataID);
	lua_register(m_L, "C_SendImpactToAroundUser", C_SendImpactToAroundUser);
	lua_register(m_L, "C_IsActive", C_IsActive);
	lua_register(m_L, "C_MoveTo", C_MoveTo);
	lua_register(m_L, "C_FullHpAndMp", C_FullHpAndMp);
	lua_register(m_L, "C_GetSceneClassId", C_GetSceneClassId);
	lua_register(m_L, "C_GetCharCombatAttrValue", C_GetCharCombatAttrValue);

	// 任务相关
	lua_register(m_L, "C_PlayStory", C_PlayStory);
	lua_register(m_L, "C_AcceptMission", C_AcceptMission);
	lua_register(m_L, "C_IsHaveMission", C_IsHaveMission);
	lua_register(m_L, "C_SetMissionState", C_SetMissionState);
	lua_register(m_L, "C_GetMissionState", C_GetMissionState);
	lua_register(m_L, "C_SetMissionParam", C_SetMissionParam);
	lua_register(m_L, "C_GetMissionParam", C_GetMissionParam);
	lua_register(m_L, "C_IsMissionHaveDone", C_IsMissionHaveDone);
	lua_register(m_L, "C_SetMissionHaveDone", C_SetMissionHaveDone);
	lua_register(m_L, "C_SetMissionCareEvent", C_SetMissionCareEvent);
	lua_register(m_L, "C_SetMissionAbandon", C_SetMissionAbandon);
	lua_register(m_L, "C_NewPlayerGuide", C_NewPlayerGuide);
	lua_register(m_L, "C_UIOpterate", C_UIOpterate);
	lua_register(m_L, "C_GetMissionCopySceneMonstCount", C_GetMissionCopySceneMonstCount);
	lua_register(m_L, "C_CreateDynObstacle", C_CreateDynObstacle);
	lua_register(m_L, "C_DelDynObstacle", C_DelDynObstacle);
	lua_register(m_L, "C_OpenFunction", C_OpenFunction);
	lua_register(m_L, "C_IsHaveDailyMissionByKind", C_IsHaveDailyMissionByKind);
	lua_register(m_L, "C_MisAccept_ShangPiao", C_MisAccept_ShangPiao);
	lua_register(m_L, "C_MisComplete_ShangPiao", C_MisComplete_ShangPiao);
	lua_register(m_L, "C_MisAbandon_ShangPiao", C_MisAbandon_ShangPiao);
	lua_register(m_L, "C_FYIncDailyMissionData", C_FYIncDailyMissionData);

	//物品相关
	lua_register(m_L, "C_AddItem", C_AddItem);
	lua_register(m_L, "C_DelItem", C_DelItem);
	lua_register(m_L, "C_SNSItemLog", C_SNSItemLog);
	lua_register(m_L, "C_DelItem2Use",C_DelItem2Use);
	lua_register(m_L, "C_Recover", C_Recover);
	lua_register(m_L, "C_UsableItemID", C_UsableItemID);
	lua_register(m_L, "C_GetItemDynamicData", C_GetItemDynamicData);
	lua_register(m_L, "C_SetItemDynamicData", C_SetItemDynamicData);
	lua_register(m_L, "C_UsableItemTablebyID", C_UsableItemTablebyID);
	lua_register(m_L, "C_GetEmptySlotCount", C_GetEmptySlotCount);
	lua_register(m_L, "C_GetItemCountByDataId", C_GetItemCountByDataId);
	lua_register(m_L, "C_GetItemNameByDataId", C_GetItemNameByDataId);
	lua_register(m_L, "C_GetUsingItemDynamicData", C_GetUsingItemDynamicData);
	lua_register(m_L, "C_GetItemMaxStackSizeByDataId",C_GetItemMaxStackSizeByDataId);
	lua_register(m_L, "C_GetUseItemCreateTime", C_GetUseItemCreateTime);
	lua_register(m_L, "C_GetUseItemLeftValidityTime",C_GetUseItemLeftValidityTime);
	lua_register(m_L, "C_IsHaveEquipStar",C_IsHaveEquipStar);
	
	lua_register(m_L, "C_GetCopyExtraNumber2Bit", C_GetCopyExtraNumber2Bit);
	lua_register(m_L, "C_SetCopyExtraNumber2Bit",C_SetCopyExtraNumber2Bit);
	lua_register(m_L, "C_AddCopyDayExtraNumber",C_AddCopyDayExtraNumber);
	lua_register(m_L, "C_AddStarEquipToUser",C_AddStarEquipToUser);
	lua_register(m_L, "C_PlayYanHua",C_PlayYanHua);
	lua_register(m_L, "C_IsCanShareNanGua",C_IsCanShareNanGua);
	lua_register(m_L, "C_ShareNanGua",C_ShareNanGua);
	lua_register(m_L, "C_ItemNeedSlotCount", C_ItemNeedSlotCount);
	lua_register(m_L, "C_PlayEffect", C_PlayEffect);
	lua_register(m_L, "C_PlayLongEffect", C_PlayLongEffect);
	lua_register(m_L, "C_SendSupriseChestAward", C_SendSupriseChestAward);
	lua_register(m_L, "C_UseShituExpItem", C_UseShituExpItem);

	lua_register(m_L, "C_AddDoubleExpTime", C_AddDoubleExpTime);
	lua_register(m_L, "C_Recover", C_Recover);
	lua_register(m_L, "C_RateItem", C_RateItem);

	lua_register(m_L, "C_UseMarryRing", C_UseMarryRing);
	lua_register(m_L, "C_UseLightSkillBook", C_UseLightSkillBook);
	lua_register(m_L, "C_GetLightSkillLevel", C_GetLightSkillLevel);
	lua_register(m_L, "C_CanUseRecruitItem", C_CanUseRecruitItem);

	lua_register(m_L, "C_SendBoxForUserChooseMsg", C_SendBoxForUserChooseMsg);
	
	// 播放特效
	lua_register(m_L, "C_UserPlayEffect", C_UserPlayEffect);
	lua_register(m_L, "C_SceneTimeScale", C_SceneTimeScale);

	// 副本
	lua_register(m_L, "C_CreateNPC", C_CreateNPC);
	lua_register(m_L, "C_CreateLevelNPC", C_CreateLevelNPC);
	lua_register(m_L, "C_CreateImagePlayerNPC", C_CreateImagePlayerNPC);	
	lua_register(m_L, "C_SetNPCDirection", C_SetNPCDirection);
	lua_register(m_L, "C_GetNPCDataID", C_GetNPCDataID);
	lua_register(m_L, "C_KillAllEnemyNPC", C_KillAllEnemyNPC);
	lua_register(m_L, "C_SendTeleportOp", C_SendTeleportOp);
	lua_register(m_L, "C_SendQingGongPointOp", C_SendQingGongPointOp);
	lua_register(m_L, "C_CreateZombieUser", C_CreateZombieUser);
	lua_register(m_L, "C_CreateZombieOfSelf", C_CreateZombieOfSelf);
	lua_register(m_L, "C_CreateMercenary", C_CreateMercenary);
	lua_register(m_L, "C_CreateWorldBoss", C_CreateWorldBoss);
	lua_register(m_L, "C_LeaveCopyScene", C_LeaveCopyScene);
	lua_register(m_L, "C_PlayModelStory", C_PlayModelStory);
	lua_register(m_L, "C_GetCopyScenePlayType", C_GetCopyScenePlayType);
	lua_register(m_L, "C_GetCopySceneDifficulty", C_GetCopySceneDifficulty);
	lua_register(m_L, "C_CreateCopySceneNpc", C_CreateCopySceneNpc);
	lua_register(m_L, "C_GetCopySceneInfo", C_GetCopySceneInfo);
	lua_register(m_L, "C_GetCopySceneNPCTotalNum", C_GetCopySceneNPCTotalNum);
	lua_register(m_L, "C_IsCopySceneNPC", C_IsCopySceneNPC);
	lua_register(m_L, "C_SetCopySceneResult", C_SetCopySceneResult);
	lua_register(m_L, "C_SetSweepLevel", C_SetSweepLevel);
	lua_register(m_L, "C_GetCopySceneResult", C_GetCopySceneResult);
	lua_register(m_L, "C_CreateMissionCopySceneNpc", C_CreateMissionCopySceneNpc);
	lua_register(m_L, "C_DelAllNpcByDataID", C_DelAllNpcByDataID);
	lua_register(m_L, "C_GetCopySceneScoreFactor", C_GetCopySceneScoreFactor);
	lua_register(m_L, "C_GetCopySceneScoreStar", C_GetCopySceneScoreStar);
	lua_register(m_L, "C_GetServerAnsiTime", C_GetServerAnsiTime);
	lua_register(m_L, "C_SetCangJingGeCopySceneResult", C_SetCangJingGeCopySceneResult);
	lua_register(m_L, "C_SetCopySceneTier", C_SetCopySceneTier);
	lua_register(m_L, "C_GetCopySceneLevel", C_GetCopySceneLevel);
	lua_register(m_L, "C_DelAllNpc", C_DelAllNpc);
	lua_register(m_L, "C_CreateDropItem", C_CreateDropItem);
	lua_register(m_L, "C_SendWorldBossChallenge2Service", C_SendWorldBossChallenge2Service);
	lua_register(m_L, "C_SetLingYunKuCopySceneResult", C_SetLingYunKuCopySceneResult);
	lua_register(m_L, "C_GetWeek",C_GetWeek);
	lua_register(m_L, "C_CreateTeleportInScene",C_CreateTeleportInScene);
	lua_register(m_L, "C_RemoveTeleportInScene",C_RemoveTeleportInScene);
	lua_register(m_L, "C_SyncTeleportInSceneToUser",C_SyncTeleportInSceneToUser);
	lua_register(m_L, "C_IsObstacle",C_IsObstacle);
	lua_register(m_L, "C_SetCopySceneTimer", C_SetCopySceneTimer);//服务器传参给客户端当前副本剩余时间
	lua_register(m_L, "C_SyncCopySceneNextWaveMonsterInfoToUser", C_SyncCopySceneNextWaveMonsterInfoToUser);
	lua_register(m_L, "C_UpdateCharAttr", C_UpdateCharAttr);

	lua_register(m_L, "C_FourVillainCopySceneFail",C_FourVillainCopySceneFail);
	lua_register(m_L, "C_SyncVillainCopysceneMonsterInfoToClient",C_SyncVillainCopysceneMonsterInfoToClient);
	lua_register(m_L, "C_KillBossRewardItem", C_KillBossRewardItem);
	lua_register(m_L, "C_AuditLog_KillVillainBoss", C_AuditLog_KillVillainBoss);
	
	// 玩家常用
	lua_register(m_L, "C_SendNoticeMsg", C_SendNoticeMsg);
	lua_register(m_L, "C_GetPlayerData", C_GetPlayerData);
	lua_register(m_L, "C_SetPlayerData", C_SetPlayerData);
	lua_register(m_L, "C_OpenSingleCopyScene", C_OpenSingleCopyScene);
	lua_register(m_L, "C_ActiveBelle", C_ActiveBelle);
	lua_register(m_L, "C_CheckBelleActiveForever", C_CheckBelleActiveForever);
	lua_register(m_L, "C_CheckBelleIsOpen", C_CheckBelleIsOpen);
	lua_register(m_L, "C_CheckBelleFunctionOpen", C_CheckBelleFunctionOpen);
	lua_register(m_L, "C_StudySkill", C_StudySkill);
	lua_register(m_L, "C_GetProfessionID", C_GetProfessionID);
	lua_register(m_L, "C_GetPlayerCurHP", C_GetPlayerCurHP);
	lua_register(m_L, "C_GetPlayerCurMP", C_GetPlayerCurMP);
	lua_register(m_L, "C_GetPlayerMaxHP",C_GetPlayerMaxHP);
	lua_register(m_L, "C_GetPlayerMaxMP",C_GetPlayerMaxMP);
	lua_register(m_L, "C_SetPlayerCurHP",C_SetPlayerCurHP);
	lua_register(m_L, "C_SetPlayerCurMP",C_SetPlayerCurMP);
	lua_register(m_L, "C_SendCountdown", C_SendCountdown);
	lua_register(m_L, "C_GetPlayerLevel",C_GetPlayerLevel);
	lua_register(m_L, "C_GetPlayerStamina",C_GetPlayerStamina);
	lua_register(m_L, "C_GetPlayerName",C_GetPlayerName);
	lua_register(m_L, "C_ControlZombieUserAI", C_ControlZombieUserAI);
	lua_register(m_L, "C_ChangeZombieUserForce", C_ChangeZombieUserForce);
	lua_register(m_L, "C_CallZombieUserFellow", C_CallZombieUserFellow);
	lua_register(m_L, "C_SetUserForce", C_SetUserForce);
	lua_register(m_L, "C_GetUserForce", C_GetUserForce);
	lua_register(m_L, "C_SendChallengeResult", C_SendChallengeResult);
	lua_register(m_L, "C_SendDuelResult", C_SendDuelResult);
	lua_register(m_L, "C_SendHuaShanPvPResultByWinner", C_SendHuaShanPvPResultByWinner);
	lua_register(m_L, "C_ResetMercenary", C_ResetMercenary);
	lua_register(m_L, "C_GetObjIDByGuid", C_GetObjIDByGuid);
	lua_register(m_L, "C_GetUserChannel", C_GetUserChannel);
	lua_register(m_L, "C_IncGuildContribute", C_IncGuildContribute);
	lua_register(m_L, "C_IncExp", C_IncExp);
	lua_register(m_L, "C_IncMoney", C_IncMoney);
	lua_register(m_L, "C_IsTeamLeader", C_IsTeamLeader);
	lua_register(m_L, "C_GetTeamId", C_GetTeamId);
	lua_register(m_L, "C_GetIsPassiveFlag", C_GetIsPassiveFlag);
	lua_register(m_L, "C_ZhenQiZhuZhanState", C_ZhenQiZhuZhanState);
	lua_register(m_L, "C_ChangeScene", C_ChangeScene);
	lua_register(m_L, "C_GetDailyMissionDoneCount", C_GetDailyMissionDoneCount);
	lua_register(m_L, "C_CollectMount", C_CollectMount);
	lua_register(m_L, "C_IsMountCollected", C_IsMountCollected);
	lua_register(m_L, "C_Relive", C_Relive);
	lua_register(m_L, "C_ReliveOther",C_ReliveOther);
	lua_register(m_L, "C_GetCopySceneDayNumber", C_GetCopySceneDayNumber);
	lua_register(m_L, "C_PlaySoundEffect", C_PlaySoundEffect);
	lua_register(m_L, "C_IsPutDefensiveGem", C_IsPutDefensiveGem);
	lua_register(m_L, "C_IsPutAttackGem", C_IsPutAttackGem);//是否打了攻击宝石
	lua_register(m_L, "C_IsGetQiLinBi", C_IsGetQiLinBi);//是否得到麒麟臂
	lua_register(m_L, "C_IsHaveEquipthen",C_IsHaveEquipthen);//是否得到强化过
	lua_register(m_L, "C_SetOnlineAwardVersion", C_SetOnlineAwardVersion);
	lua_register(m_L, "C_SendAwardTableLine", C_SendAwardTableLine);
	lua_register(m_L, "C_SendUpdateNotice", C_SendUpdateNotice);
	lua_register(m_L, "C_GetUserPkValue", C_GetUserPkValue);
	lua_register(m_L, "C_IncUserPkValue", C_IncUserPkValue);
	lua_register(m_L, "C_SetCommonFlag", C_SetCommonFlag);
	lua_register(m_L, "C_GetCommonFlag", C_GetCommonFlag);
	lua_register(m_L, "C_SetCommonData", C_SetCommonData);
	lua_register(m_L, "C_GetCommonData", C_GetCommonData);
	lua_register(m_L, "C_SendPushNotification", C_SendPushNotification);
	lua_register(m_L, "C_SetNewOnlineAwardVersion", C_SetNewOnlineAwardVersion);
	lua_register(m_L, "C_SendNewAwardTableLine", C_SendNewAwardTableLine);
	lua_register(m_L, "C_SetNew7DayOnlineAwardVersion", C_SetNew7DayOnlineAwardVersion);
	lua_register(m_L, "C_SendNew7DayAwardTableLine", C_SendNew7DayAwardTableLine);
	lua_register(m_L, "C_IsNearNpc", C_IsNearNpc);
	lua_register(m_L, "C_SendSignInAwardTableaLine", C_SendSignInAwardTableaLine);

	// NPC相关
	lua_register(m_L, "C_SwithAIToFollow", C_SwithAIToFollow);
	lua_register(m_L, "C_ChangeCurSelectObjId", C_ChangeCurSelectObjId);
	lua_register(m_L, "C_SetNpcForce", C_SetNpcForce);
	lua_register(m_L, "C_SetNpcLifeTime", C_SetNpcLifeTime);

	//伙伴相关
	lua_register(m_L, "C_AddFellow", C_AddFellow);
	lua_register(m_L, "C_AddFellowWithQuality", C_AddFellowWithQuality);
	lua_register(m_L, "C_GetEmptyFellowSlotCount", C_GetEmptyFellowSlotCount);
	lua_register(m_L, "C_GetFellowCountByDataID", C_GetFellowCountByDataID);
	lua_register(m_L, "C_GetFellowFreeGainCount", C_GetFellowFreeGainCount);
	lua_register(m_L, "C_IsFellow", C_IsFellow);
	lua_register(m_L, "C_GetFellowOwerObjId", C_GetFellowOwerObjId);
	lua_register(m_L, "C_IsFellowLevelFull", C_IsFellowLevelFull);
	lua_register(m_L, "C_IncInstanceFellowExp", C_IncInstanceFellowExp);
	lua_register(m_L, "C_IsHaveInstanceFellow", C_IsHaveInstanceFellow);
	lua_register(m_L, "C_GetInstanceFellowObjId", C_GetInstanceFellowObjId);
	lua_register(m_L, "C_AddAndCallFellow", C_AddAndCallFellow);
	lua_register(m_L, "C_CallFellowByDataID", C_CallFellowByDataID);
	lua_register(m_L, "C_GetRemainRecruitSpace", C_GetRemainRecruitSpace);
	lua_register(m_L, "C_IncRecruitPoint", C_IncRecruitPoint);

	//帮战相关
	lua_register(m_L, "C_AddGuildWarPreliminaryTimes", C_AddGuildWarPreliminaryTimes);
	lua_register(m_L, "C_AddGuildWarPreliminaryKillNum", C_AddGuildWarPreliminaryKillNum);
	lua_register(m_L, "C_ProcessGuildWarResult", C_ProcessGuildWarResult);
	lua_register(m_L, "C_AddGuildWarAwardToUser", C_AddGuildWarAwardToUser);
	lua_register(m_L, "C_GetGuildWarType", C_GetGuildWarType);
	lua_register(m_L, "C_GetGuildWarPointType", C_GetGuildWarPointType);
	lua_register(m_L, "C_IsJoinGuild", C_IsJoinGuild);
	lua_register(m_L, "C_SetGuildwarPointFighting", C_SetGuildwarPointFighting);
	lua_register(m_L, "C_IsOpenPaoShang", C_IsOpenPaoShang);
	lua_register(m_L, "C_AddGuildWarRewardEP", 	C_AddGuildWarRewardEP);
	lua_register(m_L, "C_AddGuildCityWarRewardEP", 	C_AddGuildCityWarRewardEP);

	//mail
	lua_register(m_L, "C_SystemSendMail", C_SystemSendMail);
	lua_register(m_L, "C_SystemSendMail_WithMoneyAndItem", C_SystemSendMail_WithMoneyAndItem);
	lua_register(m_L, "C_SystemSendMail_WithMoney", C_SystemSendMail_WithMoney);
	lua_register(m_L, "C_SystemSendMail_WithItem", C_SystemSendMail_WithItem);
	lua_register(m_L, "C_PlayerSendMail", C_PlayerSendMail);

	lua_register(m_L, "C_BroadcastSampleSystemChat", C_BroadcastSampleSystemChat);
	lua_register(m_L, "C_BraodcastSystemChat_PlayerInfo", C_BraodcastSystemChat_PlayerInfo);

	lua_register(m_L, "C_AddSwordsMan", C_AddSwordsMan);
	lua_register(m_L, "C_GetEmptySwordsManSlotCount", C_GetEmptySwordsManSlotCount);
	lua_register(m_L, "C_GetSwordsManCountByDataID", C_GetSwordsManCountByDataID);

	//补偿
	lua_register(m_L, "C_GetRedeemInfo", C_GetRedeemInfo);
	lua_register(m_L, "C_SetRedeemInfo", C_SetRedeemInfo);
	lua_register(m_L, "C_AddRedeem", C_AddRedeem);
	lua_register(m_L, "C_GetTime2Day", C_GetTime2Day);
	lua_register(m_L, "C_GetRoleCreateTime", C_GetRoleCreateTime);
	lua_register(m_L, "C_GetTimeDataByAnsi", C_GetTimeDataByAnsi);

	//GM工具补偿
	lua_register(m_L, "C_GetGMRedeemInfo", C_GetGMRedeemInfo);
	lua_register(m_L, "C_SetGMRedeemInfo", C_SetGMRedeemInfo);
	lua_register(m_L, "C_AddGMRedeem", C_AddGMRedeem);

	// 称号
	lua_register(m_L, "C_IsGainTitle", C_IsGainTitle);
	lua_register(m_L, "C_IsSystemTitle", C_IsSystemTitle);
	lua_register(m_L, "C_IsDefTitle", C_IsDefTitle);
	lua_register(m_L, "C_GainSystemTitle", C_GainSystemTitle);
	lua_register(m_L, "C_GainDefTitle", C_GainDefTitle);

	lua_register(m_L, "C_AddFashionTime", C_AddFashionTime);	

	lua_register(m_L, "C_IsCanChangeName", C_IsCanChangeName);	
	lua_register(m_L, "C_ChangeName", C_ChangeName);	

	lua_register(m_L, "C_AuditNewPlayerLog", C_AuditNewPlayerLog);

	// 活动相关
	lua_register(m_L, "C_IsOpenSingleDay", C_IsOpenSingleDay);
	lua_register(m_L, "C_IsSelectRightLover", C_IsSelectRightLover);
	lua_register(m_L, "C_LoveRoseUseOver", C_LoveRoseUseOver);
	lua_register(m_L, "C_IsOpenHalloween", C_IsOpenHalloween);
	lua_register(m_L, "C_IsOpenThanksGivingDay", C_IsOpenThanksGivingDay);
	lua_register(m_L, "C_IsTodayCandoTanksGivMission", C_IsTodayCandoTanksGivMission);
	lua_register(m_L, "C_ThanksGivingDayFinished", C_ThanksGivingDayFinished);
	lua_register(m_L, "C_IsOpenChristmasDay", C_IsOpenChristmasDay);
	lua_register(m_L, "C_GetReturnAwardDayCount", C_GetReturnAwardDayCount);
	lua_register(m_L, "C_AutoFindPath", C_AutoFindPath);
	lua_register(m_L, "C_SetWaBaoInfo",C_SetWaBaoInfo);
	lua_register(m_L, "C_GetWaBaoInfo",C_GetWaBaoInfo);
	lua_register(m_L, "C_GetWaBaoNpcIDByBaoTu",C_GetWaBaoNpcIDByBaoTu);
	lua_register(m_L, "C_CheckUseBaoTu",C_CheckUseBaoTu);
	lua_register(m_L, "C_GetWaBaoLvlDiff",C_GetWaBaoLvlDiff);
	lua_register(m_L, "C_AuditLog_BaoTuUse", C_AuditLog_BaoTuUse);
	lua_register(m_L, "C_IsGuildInquireOpen", C_IsGuildInquireOpen);

	// 手机绑定相关
	lua_register(m_L, "C_SendBindPhoneAwardData", C_SendBindPhoneAwardData);
	lua_register(m_L, "C_SendWuLinResultByWinner", C_SendWuLinResultByWinner);

	lua_register(m_L, "C_IsMyGuildManor", C_IsMyGuildManor);
	lua_register(m_L, "C_GetSceneNameByID", C_GetSceneNameByID);

	// 雄霸天下
	lua_register(m_L, "C_CreateHeroSoul", C_CreateHeroSoul);
	lua_register(m_L, "C_CleanManorScene2Scene", C_CleanManorScene2Scene);
	lua_register(m_L, "C_GetDomainTheWorldGuildInfo", C_GetDomainTheWorldGuildInfo);
	lua_register(m_L, "C_CreateManorNPC", C_CreateManorNPC);
	lua_register(m_L, "C_BroadcastNotice2Guild", C_BroadcastNotice2Guild);
	lua_register(m_L, "C_GetDomainTheWorldGuildCount", C_GetDomainTheWorldGuildCount);
	lua_register(m_L, "C_BroadcastRollNotice", C_BroadcastRollNotice);
	lua_register(m_L, "C_BroadCastSampleSystemChat2Scene", C_BroadCastSampleSystemChat2Scene);
	lua_register(m_L, "C_CreateManorMissionNpcIfNeeded", C_CreateManorMissionNpcIfNeeded);
	lua_register(m_L, "C_CreateWLZZ", C_CreateWLZZ);
	lua_register(m_L, "C_IncShangYin", C_IncShangYin);
	lua_register(m_L, "C_IncHeroSoulExp", C_IncHeroSoulExp);
	lua_register(m_L, "C_CheckXBTXIsOpen", C_CheckXBTXIsOpen);
	lua_register(m_L, "C_CheckIsInDomainTheWorldCombat", C_CheckIsInDomainTheWorldCombat);

	//师徒任务
	lua_register(m_L, "C_ShituChallengeIsInSameTeam", C_ShituChallengeIsInSameTeam);
	lua_register(m_L, "C_ModifyChallengeMisState", C_ModifyChallengeMisState);
	lua_register(m_L, "C_ClearChushiChallengeGuid", C_ClearChushiChallengeGuid);
	lua_register(m_L, "C_NotifyChushiChallengeFailed", C_NotifyChushiChallengeFailed);
	lua_register(m_L, "C_ShituMissionIsTudi", C_ShituMissionIsTudi);
	lua_register(m_L, "C_ShituMissionIsShifu", C_ShituMissionIsShifu);
	
	// 成王败寇
	lua_register(m_L, "C_GetCWBKGuildInfo", C_GetCWBKGuildInfo);
	lua_register(m_L, "C_EndCWBK", C_EndCWBK);
	
	__LEAVE_PROTECT
}

bool Scene::LuaLoadAll(void)
{
	__ENTER_PROTECT

	bool bRet = true;

	int nScriptCount = GetTable_ScriptDataCount();
	for (int i = 0; i < nScriptCount; i++)
	{
		const Table_ScriptData *pLine = GetTable_ScriptDataByIndex(i);
		if (pLine != null_ptr)
		{
			const Table_ScriptData &rLine = *pLine;
			if (!LuaLoad(rLine.GetScriptID()))
			{
				bRet = false;
			}
		}
	}

	return bRet;

	__LEAVE_PROTECT
	return false;
}

bool Scene::LuaLoad(int nScript)
{
	__ENTER_PROTECT

	AssertEx(m_L != null_ptr, "");

	if (!_GameConfig().m_bLoadScriptAlways &&
		m_ErrorScriptIDSet.find(nScript) != m_ErrorScriptIDSet.end())
	{
		return false;
	}

	if (!_GameConfig().m_bLoadScriptAlways &&
		m_LoadedScriptIDSet.find(nScript) != m_LoadedScriptIDSet.end())
	{
		return true;
	}

	const Table_ScriptData *pLine = GetTable_ScriptDataByID(nScript);
	if (pLine != null_ptr)
	{
		const Table_ScriptData &rLine = *pLine;

		int nLoadRet = luaL_loadfile(m_L, rLine.GetLuaPath());
		if (nLoadRet == LUA_OK)
		{
			int nDoRet = lua_pcall(m_L, 0, LUA_MULTRET, 0);
			if (nDoRet == LUA_OK)
			{
				m_LoadedScriptIDSet.insert(nScript);
				CacheLog(LOGDEF_INST(Lua), "scene load lua script, ok, scene(%d,%d), script(%d,%s)",
					GetSceneClassID(), GetSceneInstID(), rLine.GetScriptID(), rLine.GetLuaPath());
				return true;
			}
			else
			{
				m_ErrorScriptIDSet.insert(nScript);
				CacheLog(LOGDEF_INST(Lua), "scene load lua script, pcall failed, scene(%d,%d), script(%d,%s), ret(%d)",
					GetSceneClassID(), GetSceneInstID(), rLine.GetScriptID(), rLine.GetLuaPath(), nDoRet);
				LuaLogStackTop();
				lua_pop(m_L, 1);
				return false;
			}
		}
		else
		{
			m_ErrorScriptIDSet.insert(nScript);
			CacheLog(LOGDEF_INST(Lua), "scene load lua script, loadfile failed, scene(%d,%d), script(%d,%s), ret(%d)",
				GetSceneClassID(), GetSceneInstID(), rLine.GetScriptID(), rLine.GetLuaPath(), nLoadRet);
			LuaLogStackTop();
			lua_pop(m_L, 1);
			return false;
		}
	}
	else
	{
		m_ErrorScriptIDSet.insert(nScript);
		CacheLog(LOGDEF_INST(Lua), "scene load lua script, gettable failed, scene(%d,%d), script(%d)",
			GetSceneClassID(), GetSceneInstID(), nScript);
		return false;
	}

	__LEAVE_PROTECT
	return false;
}

void Scene::LuaReload(int nScript)
{
	__ENTER_PROTECT

	m_ErrorScriptIDSet.erase(nScript);
	m_LoadedScriptIDSet.erase(nScript);

	__LEAVE_PROTECT
}

void Scene::LuaLogStackTop(void)
{
	__ENTER_PROTECT

	AssertEx(m_L != null_ptr, "");

	int nTopIndex = lua_gettop(m_L);
	if (nTopIndex >= 1)
	{
		if (lua_isstring(m_L, nTopIndex))
		{
			const char *szContent = lua_tostring(m_L, nTopIndex);
			CacheLog(LOGDEF_INST(Lua), "lua stack top, top(%s), scene(%d,%d)",
				szContent != null_ptr ? szContent : "",
				GetSceneClassID(), GetSceneInstID());
		}
		else
		{
			CacheLog(LOGDEF_INST(Lua), "lua stack top, top(not string), scene(%d,%d)",
				GetSceneClassID(), GetSceneInstID());
		}
	}
	else
	{
		CacheLog(LOGDEF_INST(Lua), "lua stack top, top(nonexistence), scene(%d,%d)",
			GetSceneClassID(), GetSceneInstID());
	}

	__LEAVE_PROTECT
}

bool Scene::LuaIsFuctionExist(const char *szFuction)
{
	__ENTER_PROTECT

	AssertEx(m_L != null_ptr, "");
	AssertEx(szFuction != null_ptr, "");

	int nStackTopIndex1 = lua_gettop(m_L);

	lua_getglobal(m_L, szFuction);
	bool bNil = lua_isnil(m_L, -1);
	lua_pop(m_L, 1);

	int nStackTopIndex2 = lua_gettop(m_L);
	AssertEx(nStackTopIndex1 == nStackTopIndex2, "");
	
	return !bNil;

	__LEAVE_PROTECT
	return false;
}

ScriptReturnValue Scene::LuaCall(int nScript, const char* szFunction, const ScriptParamList &rParam)
{
	__ENTER_PROTECT_EX

	AssertEx(m_L != null_ptr, "");
	AssertEx(nScript > invalid_id, "");
	AssertEx(szFunction != null_ptr, "");

	char szScriptFuction[256] = {0};
	tsnprintfex(szScriptFuction, sizeof(szScriptFuction), "x%.4d_%s", nScript, szFunction);

	AssertEx(LuaLoad(nScript), szScriptFuction);

	if (!LuaIsFuctionExist(szScriptFuction))
	{
		ScriptReturnValue FuctionNotExistRet;
		FuctionNotExistRet.m_nRet = ScriptReturnValue::RET_FUNCTIONNOTEXIST;
		return FuctionNotExistRet;
	}

	bool bHasException = false;

	ScriptReturnValue Ret;

	int nStackTopIndex = lua_gettop(m_L);

		__ENTER_PROTECT_EX

		//函数压栈
		lua_getglobal(m_L, szScriptFuction);
		AssertEx(!lua_isnil(m_L, -1), szScriptFuction);

		//参数压栈
		for (int i = 0; i < rParam.Size(); i++)
		{
			lua_pushnumber(m_L, rParam[i]);
		}

		//调用函数
		int nCall = lua_pcall(m_L, rParam.Size(), LUA_MULTRET, 0);
		if (nCall != LUA_OK)
		{
			CacheLog(LOGDEF_INST(Lua), "scene call lua script, failed, scene(%d,%d), scriptid(%d), fuction(%s), ret(%d)",
				GetSceneClassID(), GetSceneInstID(), nScript, szScriptFuction, nCall);
			LuaLogStackTop();
			lua_pop(m_L, 1);
		}
		AssertEx(nCall == LUA_OK, szScriptFuction);

		//获取返回值
		int nNewStackTopIndex = lua_gettop(m_L);
		AssertEx(nStackTopIndex <= nNewStackTopIndex, szScriptFuction);
		for (int i = nStackTopIndex + 1; i <= nNewStackTopIndex; i++)
		{
			Ret.m_ValueList.Append(static_cast<int>(lua_tonumber(m_L, i)));
		}

		__CATCH_PROTECT_EX

		bHasException = true;

		__LEAVE_PROTECT_EX

	lua_settop(m_L, nStackTopIndex);
	AssertEx(!bHasException, szScriptFuction);

	Ret.m_nRet = ScriptReturnValue::RET_OK;
	return Ret;

	__CATCH_PROTECT_EX
	ScriptReturnValue FailedRet;
	FailedRet.m_nRet = ScriptReturnValue::RET_FAILED;
	return FailedRet;

	__LEAVE_PROTECT_EX
	ScriptReturnValue FailedRet;
	FailedRet.m_nRet = ScriptReturnValue::RET_FAILED;
	return FailedRet;
}
