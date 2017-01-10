#ifndef _MARCHMANAGER_H_
#define _MARCHMANAGER_H_

#pragma once

#include "../BaseManager.h"
#include "service/TimeInfo.h"
#include "march/GameStruct_March.h"

class GC_MarchList;
class GC_MarchData;

class MarchManager : public BaseManager
{
public:
	MarchManager(User &rUser);
	virtual ~MarchManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	void		OnLogin();
public:
	void    FileData(GC_MarchList* pMarchList);


private:
	void    FileSingMarch(MarchPtr Ptr,GC_MarchData * pMarchData);

public:

	// ��ʼmarchinfo
	bool        InitMarchInfo(int64 nBuildId,const TroopList_T& rTroopList,const Hero& rHero,March& rMarch);

	// ����march��״̬
	bool        UpdateMarchState(int64 nMarchId,int nState);

	// ���ĳ����Ӫ���߳�ǽ�ܷ�פ��Ӣ��
	bool        CheckAssignHero(int64 nMarchId);
	// ��һ��Ӣ��פ������Ӫ���߳�ǽ
	void        AssignHeroToMarch(int64 nMarchId,const Hero& rHero);

	// �ӳ�������ǲһ�ӱ������ͼ
	bool       CheckSendMarchIntoMap(int64 nMarchId);

	// ����march����
	bool       UpdateMarchData(const March &rMarch);

public:

	MarchPtr      GetMarchInfo(int64 nMarchId);

public:
	bool        AddTroop(int64 nMarchId,int nType,int nHp);

protected:

	MarchPtrMap     m_mapMarch;
	// ������march��ӳ������ڸ��߻���ǰ����һ����Ӫ����ֻ��һ��march����march�͵�����Ӫ
	BuildMarchMap   m_mapBuildMarch;
};

#endif
