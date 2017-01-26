#ifndef _CITYMANAGER_H_
#define _CITYMANAGER_H_

#pragma once

#include "../BaseManager.h"

#include "city/GameStruct_City.h"

#include "Scene/GameStruct_Scene.h"

class GC_CityData;
class GC_Building_LevelUp;
class GC_Troop_Train;

class CityManager : public BaseManager
{
public:
	CityManager(User &rUser);
	virtual ~CityManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	// ��¼����
	void		OnLogin();

public:
	 ScenePos      GetPos();

public:
	// ���ĳ����Ӫ���߳�ǽ�ܷ�פ��Ӣ��
	//bool       CheckAssignHero(int64 nBuildId);
	// ��һ��Ӣ��פ������Ӫ���߳�ǽ
	//void       AssignHeroToBuild(int64 nBuildId,int64 nHeroId);

	// �ӳ�������ǲһ�ӱ������ͼ
	bool       CheckSendMarchIntoMap(int64 nBuildId);

	// ��������
	bool       BuildLevelUp(int64 nBuildId,GC_Building_LevelUp* pMessage);

	// ��ʼѵ����
	bool       BeginTrainTroop(int64 nBuildId,int nQueueIndex,int nType,int Count,GC_Troop_Train* pMessage);



public:
	void    FileData(GC_CityData* pCityData);


protected:

	CityPtr     m_CityPtr;
};


#endif
