#include "DBStruct_City.h"
#include "GuidDefine.h"
void DBCity::CleanUp( )
{
	__ENTER_FUNCTION
		m_tileID    = 0; //�ؿ�ID
		m_nCityID   = 0;
		m_nPlayerId = 0;
		m_nLevel    = 0;
		m_nFood     = 0;
		m_nStone    = 0;
		m_nIron     = 0;
		m_fPosX     = 0.f;
		m_fPosZ     = 0.f;
		m_nGold     = 0;
		for (int i=0;i<MAX_CITY_CONSTRUCT_COUNT;i++)
		{
			m_ConstructList[i].CleanUp();
		}
		for (int i=0;i<MAX_CITY_RESEARCH_COUNT;i++)
		{
			m_TechResearchList[i].CleanUp();
		}

		for (int i=0;i<BUILDING_MAX_SLOT;i++)
		{
			m_BuildingList[i].CleanUp();
		}

		for (int i=0;i<TECHNOLOGYTYPE_MAX;i++)
		{
			m_TechList[i].CleanUp();
		}

		for (int i=0;i<(BUILDING_BARRACK_MAX+BUILDING_WALL_MAX);i++)
		{
			m_TrainList[i].CleanUp();
		}

		//for (int i=0;i<TROOPTYPE_MAX;i++)
		//{
			//m_TroopList[i].CleanUp();
		//}
		
	__LEAVE_FUNCTION
}
void DBCity::CopyFrom(const DBCity& rSource)
{
	__ENTER_FUNCTION
		m_tileID    = rSource.m_tileID; //�ؿ�ID
		m_nCityID   = rSource.m_nCityID;
		m_nPlayerId = rSource.m_nPlayerId;
		m_nLevel    = rSource.m_nLevel;
		m_nFood     = rSource.m_nFood;
		m_nStone    = rSource.m_nStone;
		m_nIron     = rSource.m_nIron;
		m_fPosX     = rSource.m_fPosX;
		m_fPosZ     = rSource.m_fPosZ;
		m_nGold     = rSource.m_nGold;
		for (int i=0;i<MAX_CITY_CONSTRUCT_COUNT;i++)
		{
			m_ConstructList[i].CopyFrom(rSource.m_ConstructList[i]);
		}
		for (int i=0;i<MAX_CITY_RESEARCH_COUNT;i++)
		{
			m_TechResearchList[i].CopyFrom(rSource.m_TechResearchList[i]);
		}

		for (int i=0;i<BUILDING_MAX_SLOT;i++)
		{
			m_BuildingList[i].CopyFrom(rSource.m_BuildingList[i]);
		}

		for (int i=0;i<TECHNOLOGYTYPE_MAX;i++)
		{
			m_TechList[i].CopyFrom(rSource.m_TechList[i]);
		}

		for (int i=0;i<(BUILDING_BARRACK_MAX+BUILDING_WALL_MAX);i++)
		{
			m_TrainList[i].CopyFrom(rSource.m_TrainList[i]);
		}

		//for (int i=0;i<MAX_TROOP_QUEUE;i++)
		//{
			//m_TroopList[i].CopyFrom(rSource.m_TroopList[i]);
		//}

	__LEAVE_FUNCTION
}

void DBTechnology::CleanUp( )
{
	__ENTER_FUNCTION
		m_ID = 0; // �Ƽ�ID
		m_nLevel = 0; // �ȼ�
		m_nType = 0; // ����
	__LEAVE_FUNCTION
}
void DBTechnology::CopyFrom(const DBTechnology& rSource)
{
	__ENTER_FUNCTION
		m_ID      = rSource.m_ID; //�ؿ�ID
		m_nLevel  = rSource.m_nLevel;
		m_nType   = rSource.m_nType;
	
	__LEAVE_FUNCTION
}

void DBTroopTrain::CleanUp( )
{
	__ENTER_FUNCTION
		m_ID = 0 ; // ID
		m_nType = 0; // ��������
		m_nBeginTime = 0; // ��ʼʱ��
		m_nCompleteTime = 0; // ���ʱ��
		m_nCityID = 0; // ��������
		m_nHp = 0;   // ѵ��Ѫ�� 
		m_nBuildId = invalid_guid64;
		m_nQueueIndex = invalid_id;
	__LEAVE_FUNCTION
}
void DBTroopTrain::CopyFrom(const DBTroopTrain& rSource)
{
	__ENTER_FUNCTION
		m_ID            = rSource.m_ID ; // ID
		m_nType         = rSource.m_nType; // ��������
		m_nBeginTime    = rSource.m_nBeginTime; // ��ʼʱ��
		m_nCompleteTime = rSource.m_nCompleteTime; // ���ʱ��
		m_nCityID       = rSource.m_nCityID; // ��������
		m_nHp           = rSource.m_nHp;   // ѵ��Ѫ��
		m_nBuildId      = rSource.m_nBuildId;
		m_nQueueIndex   = rSource.m_nQueueIndex;
	__LEAVE_FUNCTION
}

void DBTroopTrain::InitTrain(int64 nBuildId,int64 nCityId)
{
	__ENTER_FUNCTION
		CleanUp();
		m_ID = GUIDDEF_GEN(TroopTrain);
		m_nBuildId = nBuildId;
		m_nCityID  = nCityId;
	__LEAVE_FUNCTION
}

void DBTechResearch::CleanUp( )
{
	__ENTER_FUNCTION
		m_nType  = 0;
		m_nBeginTime  = 0;
		m_nLevel = 0;
		m_nCompleteTime = 0;
	__LEAVE_FUNCTION
}
void DBTechResearch::CopyFrom(const DBTechResearch& rSource)
{
	__ENTER_FUNCTION
		m_nType         = rSource.m_nType; //�ؿ�ID
		m_nBeginTime    = rSource.m_nBeginTime;
		m_nLevel        = rSource.m_nLevel;
		m_nCompleteTime = rSource.m_nCompleteTime;
	__LEAVE_FUNCTION
}

void DBBuilding::CleanUp( )
{
	__ENTER_FUNCTION
		m_ID     = 0;
	    m_nLevel = 0;
	    m_nSlot  = 0;
	    m_nType  = 0;
		m_nCityID = 0;
	__LEAVE_FUNCTION
}
void DBBuilding::CopyFrom(const DBBuilding& rSource)
{
	__ENTER_FUNCTION
		m_nType     = rSource.m_nType; //�ؿ�ID
		m_nLevel    = rSource.m_nLevel;
		m_nSlot     = rSource.m_nSlot;
		m_nType     = rSource.m_nType;
		m_nCityID   = rSource.m_nCityID;
		m_ID        = rSource.m_ID;
	__LEAVE_FUNCTION
}

void DBBuildConstruct::CleanUp( )
{
	__ENTER_FUNCTION
		m_BuildId  = 0;
		m_nBeginTime  = 0;
		m_nLevel = 0;
		m_nCompleteTime = 0;
	__LEAVE_FUNCTION
}
void DBBuildConstruct::CopyFrom(const DBBuildConstruct& rSource)
{
	__ENTER_FUNCTION
		m_BuildId       = rSource.m_BuildId; //�ؿ�ID
		m_nBeginTime    = rSource.m_nBeginTime;
		m_nLevel        = rSource.m_nLevel;
		m_nCompleteTime = rSource.m_nCompleteTime;
	__LEAVE_FUNCTION
}