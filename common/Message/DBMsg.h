/*
	功能说明：数据存储相关所有消息
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
// 分配存储任务消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBAssignTaskMsg)
	DBBaseTaskPtr m_DBBaseTaskPtr;
MESSAGE_DEF_END(DBAssignTaskMsg)

//////////////////////////////////////////////////////////////
// 检测数据库是否连接消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBCheckConnectMsg)
MESSAGE_DEF_END(DBCheckConnectMsg)

//////////////////////////////////////////////////////////////
// 加载玩家数据消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBLoadUserMsg)
	int64          m_UserGuid;        //玩家的uid
	ACCOUNTNAME    m_AccName;       // 玩家名称
	tint32		   m_nPlayerID;
	//DBFullUserData m_UserData;      // 玩家的数据
MESSAGE_DEF_END(DBLoadUserMsg);

//////////////////////////////////////////////////////////////
// 返回玩家数据消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadUserMsg)
	ACCOUNTNAME    m_AccountName;       // 玩家名称 
	DBFullUserData m_UserData;      // 玩家的数据
	int            m_nResult;       // 返回结果
	tint32		   m_nPlayerID;
MESSAGE_DEF_END(DBRetLoadUserMsg);

//////////////////////////////////////////////////////////////
// 保存玩家数据消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBSaveUserMsg)
	int64          m_UserGuid;        //玩家的uid
	DBFullUserData m_UserData;      // 玩家的数据
	int            m_nResult;       // 返回结果
	bool           m_bImmediateSave;
	bool           m_bFinalSave;
MESSAGE_DEF_END(DBSaveUserMsg);

//////////////////////////////////////////////////////////////
// 返回保存玩家数据消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetSaveUserMsg)
	int64          m_UserGuid;        //玩家的uid
	int            m_nResult;       // 返回结果
	bool           m_bImmediateSave;
	bool           m_bFinalSave;
MESSAGE_DEF_END(DBRetSaveUserMsg);

//////////////////////////////////////////////////////////////
// 创建角色消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBCreateCharMsg)
	ACCOUNTNAME    m_AccName;       // 玩家名称 
	DBFullUserData m_UserData;      // 玩家的数据
	int            m_nPlayerID;
MESSAGE_DEF_END(DBCreateCharMsg);

//////////////////////////////////////////////////////////////////////////
//创建角色返回消息
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetCreateCharMsg)
	int		m_nPlayerID;
	ACCOUNTNAME		m_AccName;
	tint8           m_Gender;
	
	tint32			m_Result;
	DBFullUserData	m_UserData;
MESSAGE_DEF_END(DBRetCreateCharMsg)

//////////////////////////////////////////////////////////////
// 数据操作结果返回消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBOpRetMsg)
	int          m_OpRet;;        
	int          m_OpType;       
	int64        m_Key;     
	int          m_TaskType;   
	int          m_ReqOpTime;
MESSAGE_DEF_END(DBOpRetMsg);

//////////////////////////////////////////////////////////////
// 请求地块信息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqLoadTileDataMsg)
	
MESSAGE_DEF_END(DBReqLoadTileDataMsg)

//////////////////////////////////////////////////////////////
// 请求地块返回消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadTileDataMsg)
	DBTileDataPtr m_DataPtr;
	int m_nResult;
MESSAGE_DEF_END(DBRetLoadTileDataMsg)

//////////////////////////////////////////////////////////////
// 请求地图March信息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqLoadMapMarchMsg)

MESSAGE_DEF_END(DBReqLoadMapMarchMsg)

//////////////////////////////////////////////////////////////
// 请求地块返回消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetLoadMapMarchMsg)
	DBMarchDataPtr m_DataPtr;
	int m_nResult;
MESSAGE_DEF_END(DBRetLoadMapMarchMsg)

//////////////////////////////////////////////////////////////
// 请求保存地块信息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqSaveTileDataMsg)
	DBTileDataPtr m_DataPtr;
MESSAGE_DEF_END(DBReqSaveTileDataMsg)

//////////////////////////////////////////////////////////////
// 保存地块操作返回消息
/////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetSaveTileDataMsg)
	int m_nResult;
MESSAGE_DEF_END(DBRetSaveTileDataMsg)

//////////////////////////////////////////////////////////////
// 请求保存地块信息
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
	bsvector<int> m_lstBuildType; // 建筑类型
	bsvector<int> m_lstSlot;      // 建筑的位置
MESSAGE_DEF_END(DBReqCreateBuildMsg)

MESSAGE_DEF_BEGIN(DBRetCreateBuildMsg)
	bsvector<int> m_lstBuildType; // 建筑类型
bsvector<int> m_lstSlot;      // 建筑的位置
bsvector<int64> m_lstBuildId; // 建筑ID
int           m_nRet; // 返回值
MESSAGE_DEF_END(DBRetCreateBuildMsg)

//////////////////////////////////////////////////////////////////////////
//存储GUID
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqSaveGuidMsg)
	tuint8	m_Type;
	int64	m_Serial;
MESSAGE_DEF_END(DBReqSaveGuidMsg)

MESSAGE_DEF_BEGIN(DBReqSaveMarchDataMsg)
	DBMarch  m_March;
MESSAGE_DEF_END(DBReqSaveMarchDataMsg)


//////////////////////////////////////////////////////////////////////////
//请求角色列表消息
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBAskCharListMsg)
	tint32		m_nPlayerID;
	ACCOUNTNAME	m_AccName;
MESSAGE_DEF_END(DBAskCharListMsg)
//////////////////////////////////////////////////////////////////////////
//请求角色列表返回消息
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBRetAskCharListMsg)
	tint32			m_nPlayerID;
	ACCOUNTNAME		m_AccName;
	tint32			m_Result;
	DBCharDataList	m_CharDataList;
MESSAGE_DEF_END(DBRetAskCharListMsg)

//////////////////////////////////////////////////////////////////////////
//请求随机名表
//////////////////////////////////////////////////////////////////////////
MESSAGE_DEF_BEGIN(DBReqLoadRandomNameMsg) 
MESSAGE_DEF_END(DBReqLoadRandomNameMsg)
//////////////////////////////////////////////////////////////////////////
//请求随机名表-返回消息
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