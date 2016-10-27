
#ifndef __DBSTRUCT_MARCH_H__
#define __DBSTRUCT_MARCH_H__

#include "DBStruct.h"
#include "DBStruct_Troop.h"
#include "DBStruct_Hero.h"
#include "Scene/GameStruct_Scene.h"

// ��ҳ�����Ϣ
struct DBMarch
{
public:
	DBMarch(){CleanUp();};
	~DBMarch(){};

	void CleanUp( );
	void CopyFrom(const DBMarch& rSource);

public:

	DBHero    m_Hero; // ��ս��Ӣ��
	DBTroop   m_TroopList[TROOP_QUEUE_MAX_COUNT];                // �����б�

	ScenePos  m_pos;		//��������
	int    m_nBeginTime; // ����ʱ��
	int    m_nEndTime;   // ����ʱ��
	int64  m_nMarchId;   // Ψһ��ʾ
	int64  m_nPlayerId;  // ���ID
	int64  m_nCityId;    // ����ID
	int    m_nStatus;    // ״̬

	
};

typedef DBCommonData<DBMarch> DBMarchData;
typedef boost::shared_ptr<DBMarchData> DBMarchDataPtr;



#endif
