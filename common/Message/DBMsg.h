/*
	����˵�������ݴ洢���������Ϣ
*/
#ifndef _DBMSG_H_
#define _DBMSG_H_

#include "service/Message.h"
#include "service/BaseService.h"
#include "../DBManage/DBTask/DBBaseTask.h"
#include "DBStruct/DBStruct_User.h"
#include "DBStruct/DBStruct_WordMap.h"

//////////////////////////////////////////////////////////////
// ����洢������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBAssignTaskMsg)
	DBBaseTaskPtr m_DBBaseTaskPtr;
MESSAGE_DEF_END(DBAssignTaskMsg)

//////////////////////////////////////////////////////////////
// ������ݿ��Ƿ�������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBCheckConnectMsg)
MESSAGE_DEF_END(DBCheckConnectMsg)

//////////////////////////////////////////////////////////////
// �������������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBLoadUserMsg)
	int64          m_UserGuid;        //��ҵ�uid
	string    m_UserName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
MESSAGE_DEF_END(DBLoadUserMsg);

//////////////////////////////////////////////////////////////
// �������������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadUserMsg)
	int64          m_UserGuid;        //��ҵ�uid
	string         m_UserName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
	int            m_nResult;       // ���ؽ��
MESSAGE_DEF_END(DBRetLoadUserMsg);

//////////////////////////////////////////////////////////////
// �������������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBSaveUserMsg)
	int64          m_UserGuid;        //��ҵ�uid
	DBFullUserData m_UserData;      // ��ҵ�����
	int            m_nResult;       // ���ؽ��
	bool           m_bImmediateSave;
	bool           m_bFinalSave;
MESSAGE_DEF_END(DBSaveUserMsg);

//////////////////////////////////////////////////////////////
// ���ر������������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetSaveUserMsg)
	int64          m_UserGuid;        //��ҵ�uid
	int            m_nResult;       // ���ؽ��
	bool           m_bImmediateSave;
	bool           m_bFinalSave;
MESSAGE_DEF_END(DBRetSaveUserMsg);

//////////////////////////////////////////////////////////////
// ������ɫ��Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBCreateCharMsg)
	int64          m_UserGuid;        //��ҵ�uid
	string         m_UserName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
MESSAGE_DEF_END(DBCreateCharMsg);

//////////////////////////////////////////////////////////////
// ���ش�����ɫ��Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetCreateCharMsg)
	int64          m_UserGuid;        //��ҵ�uid
	string         m_UserName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
	int            m_nResult;       // ���ؽ��
MESSAGE_DEF_END(DBRetCreateCharMsg);

//////////////////////////////////////////////////////////////
// ���ݲ������������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBOpRetMsg)
	int          m_OpRet;;        
	int          m_OpType;       
	int64        m_Key;     
	int          m_TaskType;   
	int          m_ReqOpTime;
MESSAGE_DEF_END(DBOpRetMsg);

//////////////////////////////////////////////////////////////
// ����ؿ���Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqLoadTileDataMsg)
	
MESSAGE_DEF_END(DBReqLoadTileDataMsg)

//////////////////////////////////////////////////////////////
// ����ؿ鷵����Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadTileDataMsg)
	DBTileDataPtr m_DataPtr;
	int m_nResult;
MESSAGE_DEF_END(DBRetLoadTileDataMsg)

//////////////////////////////////////////////////////////////
// ���󱣴�ؿ���Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqSaveTileDataMsg)
	DBTileDataPtr m_DataPtr;
MESSAGE_DEF_END(DBReqSaveTileDataMsg)

//////////////////////////////////////////////////////////////
// ����ؿ����������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetSaveTileDataMsg)
	int m_nResult;
MESSAGE_DEF_END(DBRetSaveTileDataMsg)

//////////////////////////////////////////////////////////////
// ���󱣴�ؿ���Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqSaveCityDataMsg)
	DBTileDataPtr m_DataPtr;
MESSAGE_DEF_END(DBReqSaveTileDataMsg)



#endif