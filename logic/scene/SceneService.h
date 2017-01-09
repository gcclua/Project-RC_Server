#ifndef _SCENESERVICE_H_
#define _SCENESERVICE_H_

#include "Base.h"
#include "service/Service.h"
#include "service/Invoker.h"
#include "Scene/GameStruct_Scene.h"
#include "Scene/SceneClass/SceneClass.h"

class SceneService : public Service
{
public:
	SceneService(void);
	virtual ~SceneService(void);

public:
	virtual int GetServiceID(void);
	virtual void Init(void);

protected:
	virtual void Shutdown(void);
	virtual void Openup(void);

public:
	virtual void Tick(const TimeInfo &rTimeInfo);
private:
	void Tick_OnlineLog(const TimeInfo &rTimeInfo);

private:
	void LoadMarch(const DBMarchData& rData);

private:
	void Tick_Shutdown(const TimeInfo &rTimeInfo);
private:
	int m_nShutdownTime;

public:
	virtual void HandleMessage(const MarchEnterSceneMsg& rMsg);
	virtual void HandleMessage(const MarchChangeSceneMsg &rMsg);
	virtual void HandleMessage(const MarchLeaveSceneMsg &rMsg);
	virtual void HandleMessage(const MarchReqChangeSceneMsg &rMsg);
	virtual void HandleMessage(const MarchReqFightMsg &rMsg);
	

	virtual void HandleMessage(const UpdateMarchBaseInfoMsg& rMsg);

	virtual void HandleMessage(const TransportToMarch &rMsg);
	virtual void HandleMessage(const TransportToAllScene &rMsg);
	virtual void HandleMessage(const TransportToSceneClass &rMsg);
	virtual void HandleMessage(const TransportToSceneInst &rMsg);
	virtual void HandleMessage(const DBRetLoadMapMarchMsg &rMsg);
	virtual void HandleMessage(const ReqMarchStartMsg &rMsg);
public:
	template<typename _MessagePtrT>
	void SendMessage(SceneID sceneid, _MessagePtrT Ptr)
	{
		SceneClassPtrMap::iterator it = m_SceneClassPtrMap.find(sceneid.m_nClassID);
		if (it != m_SceneClassPtrMap.end())
		{
			(*it).second->SendMessage(sceneid.m_nInstID, Ptr);
		}
	}
	template<typename _MessagePtrT>
	void SendMessage(SceneClassID nClassID, _MessagePtrT Ptr)
	{
		SceneClassPtrMap::iterator it = m_SceneClassPtrMap.find(nClassID);
		if (it != m_SceneClassPtrMap.end())
		{
			(*it).second->BroadcastMessage(Ptr);
		}
	}
	template<typename _MessagePtrT>
	void BroadcastMessage(_MessagePtrT Ptr)
	{
		for (SceneClassPtrMap::iterator it = m_SceneClassPtrMap.begin(); it != m_SceneClassPtrMap.end(); it++)
		{
			(*it).second->BroadcastMessage(Ptr);
		}
	}

private:
	SceneID EnterTo(const March& rMarch);
	SceneID EnterToDefaultScene(const March& rMarch);
private:
	SceneID ChangeTo(const March& rMarch, const SceneID &rsid);
	

private:
	void InitSceneClass(void);
	void Tick_UpdateAllSceneClass(const TimeInfo &rTimeInfo);
	void Tick_LogSceneClassStat(const TimeInfo &rTimeInfo);
private:
	SceneClassPtrMap m_SceneClassPtrMap;	//¡¾stl¡¿

	//////////////////////////////////////////////////////////////////////////
private:
	void AddMarchInfo(const MarchInfo &rInfo);
	void DelMarchInfo(const int64 &rGuid);
	MarchSceneInfo* GetMarchSceneInfo(const int64 &rGuid);
	MarchBaseInfo* GetMarchBaseInfo(const int64 &rGuid);
	void UpdateMarchInfo(const int64 &rGuid, int nState);
	void UpdateMarchInfo(const MarchInfo &rInfo);
	void UpdateMarchInfo(const MarchBaseInfo &rBaseInfo);
	int SearchMarchBaseInfo(const CHARNAME &szName, bsarray<MarchBaseInfo, MAX_FIND_MARCH_NUM> &rFindResult);
private:
	MarchInfoMap m_MarchInfoMap;	//¡¾stl¡¿
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
private:
	typedef std::pair<int64, MessagePtr> CachedMsg;
	typedef std::list<CachedMsg> CachedMsgList;
private:
	void PushCachedMsg(int64 guid, MessagePtr Ptr);
	void DistributeCachedMsg(int64 guid);
private:
	CachedMsgList m_CachedMsgList;	//¡¾stl¡¿
	//////////////////////////////////////////////////////////////////////////	

};

typedef GeneralInvoker<SceneService, 100, 100> SceneInvoker;

#endif
