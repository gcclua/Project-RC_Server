/*
	����˵������¼���������Ϣ
*/
#ifndef _LOGINMSG_H_
#define _LOGINMSG_H_

#include "service/Message.h"
#include "service/BaseService.h"
#include "DBStruct/DBStruct_User.h"
#include "Scene/GameStruct_Scene.h"

//////////////////////////////////////////////////////////////
// ��ɵ�¼��Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(QueueFinishMsg)
	int64          m_nPlayerID;        //��ҵ�uid
	ACCOUNTNAME    m_szAccount;       // ������� 
MESSAGE_DEF_END(QueueFinishMsg);

MESSAGE_DEF_BEGIN(SavePlayerDataMsg)
	int64			m_Guid;
	DBFullUserData	m_UserData;
	bool			m_bImmediateSave;
MESSAGE_DEF_END(SavePlayerDataMsg);


#endif