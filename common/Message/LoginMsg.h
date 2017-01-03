/*
	功能说明：登录相关所有消息
*/
#ifndef _LOGINMSG_H_
#define _LOGINMSG_H_

#include "service/Message.h"
#include "service/BaseService.h"
#include "DBStruct/DBStruct_User.h"
#include "Scene/GameStruct_Scene.h"

//////////////////////////////////////////////////////////////
// 完成登录消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(QueueFinishMsg)
	int          m_nPlayerID;         //玩家的连接ＩＤ
	ACCOUNTNAME    m_szAccount;       // 玩家名称 
MESSAGE_DEF_END(QueueFinishMsg);

MESSAGE_DEF_BEGIN(SavePlayerDataMsg)
	int64			m_Guid;
	DBFullUserData	m_UserData;
	bool			m_bImmediateSave;
MESSAGE_DEF_END(SavePlayerDataMsg);


MESSAGE_DEF_BEGIN(KickPlayerByAccountMsg)
	ACCOUNTNAME	m_szAccount;
tint32		m_nReason;
MESSAGE_DEF_END(KickPlayerByAccountMsg)

MESSAGE_DEF_BEGIN(AskModifyVipCostMsg)
	int64 m_Guid;
tint32 m_nVipCost;
MESSAGE_DEF_END(AskModifyVipCostMsg)

MESSAGE_DEF_BEGIN(AccountStateCheckMsg)
	int m_nPlayerID;
	ACCOUNTNAME m_szAccount;
MESSAGE_DEF_END(AccountStateCheckMsg)

MESSAGE_DEF_BEGIN(AccountOfflineMsg)
	int m_nPlayerID;
	ACCOUNTNAME m_szAccount;
MESSAGE_DEF_END(AccountOfflineMsg)

MESSAGE_DEF_BEGIN(ReqIdleTileMsg)
	int64 m_userId;
	tint32 m_nPlayerID;
MESSAGE_DEF_END(ReqIdleTileMsg)

MESSAGE_DEF_BEGIN(RetIdleTileMsg)
	int m_tileId;
	int m_posX;
	int m_posY;
	int64 m_userId;
	tint32 m_nPlayerID;
MESSAGE_DEF_END(RetIdleTileMsg)

MESSAGE_DEF_BEGIN(ReqSetTileOwerMsg)
	int m_tileId;
	int64 m_userId;
MESSAGE_DEF_END(ReqSetTileOwerMsg)


#endif