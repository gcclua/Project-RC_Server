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
int C_CreateTeleportInScene(lua_State *L);			//���������ڴ��͵㣨ֻ���ڳ����ڴ�A�㴫�͵�B�㣩
int C_RemoveTeleportInScene(lua_State *L);			//�Ƴ�������ĳ�����͵㣨ֻ���ڳ����ڴ�A�㴫�͵�B�㣩
int C_SyncTeleportInSceneToUser(lua_State *L);		//ͬ����ǰ���������г����ڴ��͵��ĳ�����
int C_IsObstacle(lua_State *L);	//�ж�ĳ�����Ƿ����
int C_SetCopySceneTimer(lua_State *L); //���������θ��ͻ��˵�ǰ����ʣ��ʱ��
int C_SyncCopySceneNextWaveMonsterInfoToUser(lua_State *L); //����������Ƚ�Զ����һ���ֵ�λ�÷������
int C_FourVillainCopySceneFail(lua_State *L);
int C_SyncVillainCopysceneMonsterInfoToClient(lua_State *L);
int C_IsMyGuildManor(lua_State *L);
int C_GetSceneNameByID(lua_State *L);

////////////////////////////////////////////////////////////////////////////////
// �۰�����
int C_CreateHeroSoul(lua_State *L);
int C_CleanManorScene2Scene(lua_State *L);			// ����������ȫ����������
int C_CreateManorNPC(lua_State *L);					// �����۰�������NPC���а��ɹ���

int C_GetDomainTheWorldGuildCount(lua_State* L);		// ��ȡ��ս�������
int C_GetDomainTheWorldGuildInfo(lua_State *L);		// ����۰����°����Ϣ

int C_BroadcastNotice2Guild(lua_State *L);			// ����Ƶ���㲥��Ϣ
int C_BroadcastRollNotice(lua_State *L);				// ���͹�������
int C_BroadCastSampleSystemChat2Scene(lua_State *L);	// ����ϵͳ����
int C_CreateManorMissionNpcIfNeeded(lua_State *L);	// ��������NPC����𢶦��
int C_CreateWLZZ(lua_State *L);						// ������������

// �۰�����
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// �����ܿ�-begin
//////////////////////////////////////////////////////////////////////////

int C_GetCWBKGuildInfo(lua_State *L);					// �����ܿ�-��ȡ�����Ϣ
int C_EndCWBK(lua_State *L);								// �����ܿ�-��ȡ�����Ϣ
//////////////////////////////////////////////////////////////////////////
// �����ܿ�-end
//////////////////////////////////////////////////////////////////////////
#endif
