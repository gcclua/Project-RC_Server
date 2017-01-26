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
#include "scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_CharList.h"
#include "DBStruct/DBStruct_RandomName.h"
#include "DBStruct/DBStruct_CityCreate.h"
#include "DBStruct/DBStruct_March.h"

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
	ACCOUNTNAME    m_AccName;       // �������
	tint32		   m_nPlayerID;
	//DBFullUserData m_UserData;      // ��ҵ�����
MESSAGE_DEF_END(DBLoadUserMsg);

//////////////////////////////////////////////////////////////
// �������������Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadUserMsg)
	ACCOUNTNAME    m_AccountName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
	int            m_nResult;       // ���ؽ��
	tint32		   m_nPlayerID;
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
	ACCOUNTNAME    m_AccName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
	int            m_nPlayerID;
MESSAGE_DEF_END(DBCreateCharMsg);

//////////////////////////////////////////////////////////////////////////
//������ɫ������Ϣ
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetCreateCharMsg)
	int		m_nPlayerID;
	ACCOUNTNAME		m_AccName;
	tint8           m_Gender;
	
	tint32			m_Result;
	DBFullUserData	m_UserData;
MESSAGE_DEF_END(DBRetCreateCharMsg)

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
// �����ͼMarch��Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqLoadMapMarchMsg)

MESSAGE_DEF_END(DBReqLoadMapMarchMsg)

//////////////////////////////////////////////////////////////
// ����ؿ鷵����Ϣ
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadMapMarchMsg)
	DBMarchDataPtr m_DataPtr;
	int m_nResult;
MESSAGE_DEF_END(DBRetLoadMapMarchMsg)

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

MESSAGE_DEF_BEGIN(DBReqCreateCityMsg)
	DBCityCreate m_Data;
	tint32		m_nPlayerID;
MESSAGE_DEF_END(DBReqCreateCityMsg)

MESSAGE_DEF_BEGIN(DBRetCreateCityMsg)
	int m_Result;
	DBCityCreate m_Data;
	tint32		   m_nPlayerID;
MESSAGE_DEF_END(DBRetCreateCityMsg)

MESSAGE_DEF_BEGIN(DBReqCreateBuildMsg)
	bsvector<int> m_lstBuildType; // ��������
	bsvector<int> m_lstSlot;      // ������λ��
MESSAGE_DEF_END(DBReqCreateBuildMsg)

MESSAGE_DEF_BEGIN(DBRetCreateBuildMsg)
	bsvector<int> m_lstBuildType; // ��������
bsvector<int> m_lstSlot;      // ������λ��
bsvector<int64> m_lstBuildId; // ����ID
int           m_nRet; // ����ֵ
MESSAGE_DEF_END(DBRetCreateBuildMsg)

//////////////////////////////////////////////////////////////////////////
//�洢GUID
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqSaveGuidMsg)
	tuint8	m_Type;
	int64	m_Serial;
MESSAGE_DEF_END(DBReqSaveGuidMsg)

MESSAGE_DEF_BEGIN(DBReqSaveMarchDataMsg)
	DBMarch  m_March;
MESSAGE_DEF_END(DBReqSaveMarchDataMsg)


//////////////////////////////////////////////////////////////////////////
//�����ɫ�б���Ϣ
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBAskCharListMsg)
	tint32		m_nPlayerID;
	ACCOUNTNAME	m_AccName;
MESSAGE_DEF_END(DBAskCharListMsg)
//////////////////////////////////////////////////////////////////////////
//�����ɫ�б�����Ϣ
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetAskCharListMsg)
	tint32			m_nPlayerID;
	ACCOUNTNAME		m_AccName;
	tint32			m_Result;
	DBCharDataList	m_CharDataList;
MESSAGE_DEF_END(DBRetAskCharListMsg)

//////////////////////////////////////////////////////////////////////////
//�����������
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqLoadRandomNameMsg) 
MESSAGE_DEF_END(DBReqLoadRandomNameMsg)
//////////////////////////////////////////////////////////////////////////
//�����������-������Ϣ
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetReqLoadRandomNameMsg) 
	tint32				m_Result;
	DBRandomNameList	m_Data;
MESSAGE_DEF_END(DBRetReqLoadRandomNameMsg)

MESSAGE_DEF_BEGIN(DBReqSaveTroopTrainMsg)
	DBTroopTrain m_Data;
MESSAGE_DEF_END(DBReqSaveTroopTrainMsg)

MESSAGE_DEF_BEGIN(DBReqSaveHeroMsg)
	DBHero m_Data;
MESSAGE_DEF_END(DBReqSaveHeroMsg)

#endif