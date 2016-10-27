#ifndef _SCRIPT_USER_H_
#define _SCRIPT_USER_H_

#include "Base.h"

struct lua_State;

int C_SendNoticeMsg(lua_State *L);
int C_GetPlayerData(lua_State *L);
int C_SetPlayerData(lua_State *L);
int C_OpenSingleCopyScene(lua_State *L);
int C_StudySkill(lua_State *L);
int C_GetProfessionID(lua_State *L);
int C_GetPlayerCurHP(lua_State *L);
int C_GetPlayerCurMP(lua_State *L);
int C_GetPlayerMaxHP(lua_State *L);
int C_GetPlayerMaxMP(lua_State *L);
int C_SetPlayerCurHP(lua_State *L);
int C_SetPlayerCurMP(lua_State *L);
int C_GetPlayerLevel(lua_State *L);
int C_GetPlayerStamina(lua_State *L);
int C_GetPlayerName(lua_State *L);
int C_ControlZombieUserAI(lua_State *L);
int C_ChangeZombieUserForce(lua_State *L);
int C_CallZombieUserFellow(lua_State *L);
int C_SendCountdown(lua_State* L);
int C_GetUserForce(lua_State *L);
int C_SetUserForce(lua_State *L);
int C_SendHuaShanPvPResult(lua_State *L);
int C_PlaySoundEffect(lua_State* L);			//播放音效
int C_PlaySceneBackGroundMusic(lua_State* L);	//播放场景音乐
int C_IsTeamLeader(lua_State* L);
int C_GetTeamId(lua_State *L);
int C_ZhenQiZhuZhanState(lua_State* L);
int C_GetIsPassiveFlag(lua_State *L);
int C_SendChallengeResult(lua_State *L);
int C_SendDuelResult(lua_State *L);
int C_SendHuaShanPvPResultByWinner(lua_State *L);
int C_ResetMercenary(lua_State *L);
int C_SendWuLinResultByWinner(lua_State *L);
int C_GetObjIDByGuid(lua_State *L);
int C_GetUserChannel(lua_State *L);
// 通用数据接口
int C_SetCommonFlag(lua_State *L);
int C_GetCommonFlag(lua_State *L);
int C_SetCommonData(lua_State *L);
int C_GetCommonData(lua_State *L);
int C_IncGuildContribute(lua_State *L);
int C_IncExp(lua_State *L);
int C_IncMoney(lua_State *L);
int C_ChangeScene(lua_State *L);
int C_GetDailyMissionDoneCount(lua_State *L);
int C_CollectMount(lua_State *L);
int C_IsMountCollected(lua_State *L);
int C_Relive(lua_State *L);
int C_ReliveOther(lua_State *L);
int C_GetCopySceneDayNumber(lua_State *L);
int C_IsPutDefensiveGem(lua_State *L);
int C_IsPutAttackGem(lua_State *L);//是否打了攻击宝石
int C_IsGetQiLinBi(lua_State *L);//是否得到麒麟臂
int C_IsHaveEquipthen(lua_State *L);//是否强化过
int C_SetOnlineAwardVersion(lua_State *L);
int C_SendAwardTableLine(lua_State *L);
int C_SendUpdateNotice(lua_State *L);
int C_GetUserPkValue(lua_State *L);
int C_IncUserPkValue(lua_State *L);
int C_AddFashionTime(lua_State *L);
int C_SendPushNotification(lua_State *L);
int C_SetNewOnlineAwardVersion(lua_State *L);
int C_SendNewAwardTableLine(lua_State *L);
int C_AuditNewPlayerLog(lua_State *L);
int C_SetNew7DayOnlineAwardVersion(lua_State *L);
int C_SendNew7DayAwardTableLine(lua_State *L);
int C_IsNearNpc(lua_State *L);
int C_SendSignInAwardTableaLine(lua_State *L);
int C_IsHaveInstanceFellow(lua_State *L);
int C_GetInstanceFellowObjId(lua_State *L);
int C_IncShangYin(lua_State *L);	// 增加商银
int C_IncHeroSoulExp(lua_State *L);
int C_CheckXBTXIsOpen(lua_State *L);
int C_CheckIsInDomainTheWorldCombat(lua_State *L);
#endif
