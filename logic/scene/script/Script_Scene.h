#ifndef _SCRIPT_SCENE_H_
#define _SCRIPT_SCENE_H_

#include "Base.h"

struct lua_State;

int C_CreateZombieUser(lua_State *L);
int C_CreateMercenary(lua_State *L);
int C_CreateZombieOfSelf(lua_State *L);
int C_CreateWorldBoss(lua_State *L);
int C_CreateNPC(lua_State *L);
int C_CreateLevelNPC(lua_State *L);
int C_CreateImagePlayerNPC(lua_State *L);
int C_SetNPCDirection(lua_State *L);
int C_DelNpcByObjID(lua_State *L);
int C_GetNPCDataID(lua_State *L);
int C_DelZombieByObjID(lua_State *L);
int C_KillAllEnemyNPC(lua_State *L);
int C_SendTeleportOp(lua_State *L);
int C_SendQingGongPointOp(lua_State *L);
int C_IsNpcInScene(lua_State *L);
int C_SceneTimeScale(lua_State *L);
int C_LeaveCopyScene(lua_State *L);
int C_PlayModelStory(lua_State *L);
int C_GetCopyScenePlayType(lua_State *L);
int C_GetCopySceneDifficulty(lua_State *L);
int C_CreateCopySceneNpc(lua_State *L);
int C_GetCopySceneInfo(lua_State *L);
int C_GetCopySceneNPCTotalNum(lua_State *L);
int C_IsCopySceneNPC(lua_State *L);
int C_SetCopySceneResult(lua_State *L);
int C_SetSweepLevel(lua_State *L);
int C_GetCopySceneResult(lua_State *L);
int C_CreateMissionCopySceneNpc(lua_State *L);
int C_DelAllNpcByDataID(lua_State *L);
int C_DelAllNpc(lua_State *L);
int C_GetCopySceneScoreFactor(lua_State *L);
int C_GetCopySceneScoreStar(lua_State *L);
int C_GetServerAnsiTime(lua_State *L);
int C_SetCangJingGeCopySceneResult(lua_State *L);
int C_GetNpcCountByDataID(lua_State *L);
int C_SendImpactToAroundUser(lua_State *L);
int C_SetCopySceneTier(lua_State *L);
int C_GetCopySceneLevel(lua_State *L);
int C_CreateDropItem(lua_State *L);
int C_SystemSendMail(lua_State *L);
int C_SystemSendMail_WithMoneyAndItem(lua_State *L);
int C_SystemSendMail_WithMoney(lua_State *L);
int C_SystemSendMail_WithItem(lua_State *L);
int C_PlayerSendMail(lua_State *L);
int C_BroadcastSampleSystemChat(lua_State *L);
int C_BraodcastSystemChat_PlayerInfo(lua_State *L);
int C_GetRedeemInfo(lua_State *L);
int C_SetRedeemInfo(lua_State *L);
int C_AddRedeem(lua_State *L);
int C_GetGMRedeemInfo(lua_State *L);
int C_SetGMRedeemInfo(lua_State *L);
int C_AddGMRedeem(lua_State *L);
int C_GetTime2Day(lua_State *L);
int C_GetRoleCreateTime(lua_State *L);
int C_GetTimeDataByAnsi(lua_State *L);
int C_SendWorldBossChallenge2Service(lua_State *L);
int C_SetLingYunKuCopySceneResult(lua_State *L);
int C_GetWeek(lua_State *L);
int C_CreateTeleportInScene(lua_State *L);			//创建副本内传送点（只能在场景内从A点传送到B点）
int C_RemoveTeleportInScene(lua_State *L);			//移除副本内某个传送点（只能在场景内从A点传送到B点）
int C_SyncTeleportInSceneToUser(lua_State *L);		//同步当前副本内所有场景内传送点给某个玩家
int C_IsObstacle(lua_State *L);	//判断某个点是否可走
int C_SetCopySceneTimer(lua_State *L); //服务器传参给客户端当前副本剩余时间
int C_SyncCopySceneNextWaveMonsterInfoToUser(lua_State *L); //将副本区域比较远的下一波怪的位置发给玩家
int C_FourVillainCopySceneFail(lua_State *L);
int C_SyncVillainCopysceneMonsterInfoToClient(lua_State *L);
int C_IsMyGuildManor(lua_State *L);
int C_GetSceneNameByID(lua_State *L);

////////////////////////////////////////////////////////////////////////////////
// 雄霸天下
int C_CreateHeroSoul(lua_State *L);
int C_CleanManorScene2Scene(lua_State *L);			// 将领地内玩家全部传出场景
int C_CreateManorNPC(lua_State *L);					// 创建雄霸天下期NPC，有帮派归属

int C_GetDomainTheWorldGuildCount(lua_State* L);		// 获取参战帮会数量
int C_GetDomainTheWorldGuildInfo(lua_State *L);		// 获得雄霸天下帮会信息

int C_BroadcastNotice2Guild(lua_State *L);			// 向帮会频道广播消息
int C_BroadcastRollNotice(lua_State *L);				// 发送滚屏公告
int C_BroadCastSampleSystemChat2Scene(lua_State *L);	// 发送系统公告
int C_CreateManorMissionNpcIfNeeded(lua_State *L);	// 创建任务NPC（社稷鼎）
int C_CreateWLZZ(lua_State *L);						// 创建武林至尊

// 雄霸天下
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 成王败寇-begin
//////////////////////////////////////////////////////////////////////////

int C_GetCWBKGuildInfo(lua_State *L);					// 成王败寇-获取帮会信息
int C_EndCWBK(lua_State *L);								// 成王败寇-获取帮会信息
//////////////////////////////////////////////////////////////////////////
// 成王败寇-end
//////////////////////////////////////////////////////////////////////////
#endif
