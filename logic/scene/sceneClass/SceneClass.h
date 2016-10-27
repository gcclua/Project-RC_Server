#ifndef _SCENECLASS_H_
#define _SCENECLASS_H_

#include "Player/Player.h"
#include "Scene/Scene/Scene.h"
#include "Message/SceneMsg.h"
#include "Scene/GameStruct_Obstacle.h"
#include "scene/obj/Obj_March.h"

class SceneClass
{
public:
	SceneClass(void);
	virtual ~SceneClass(void);

public:
	typedef std::pair<bool, SceneID> EnterResult;
public:
	virtual EnterResult EnterTo(Obj_MarchPtr Ptr, int nSceneInst) = 0;
	virtual EnterResult EnterTo(Obj_MarchPtr Ptr) = 0;
public:
	virtual EnterResult FirstEnterTo(Obj_MarchPtr Ptr) = 0;

public:
	typedef std::pair<bool, SceneID> ChangeResult;
public:
	virtual ChangeResult ChangeTo(Obj_MarchPtr Ptr, int nSceneInst) = 0;
	virtual ChangeResult ChangeTo(Obj_MarchPtr Ptr) = 0;
public:
	virtual bool ChangeFromCheck(const SceneID &rsid, const int64 &rGuid) = 0;
	virtual bool ChangeToCheck(const SceneID &rsid, const int64 &rGuid) = 0;

public:
	virtual int RemainCapacityA(SceneInstID nSceneInst) = 0;
	virtual int RemainCapacityB(SceneInstID nSceneInst) = 0;

public:
	virtual int ReusingScene(void) = 0;
	virtual int EnlargeScene(void) = 0;

public:
	template<typename _MessagePtrT>
	void SendMessage(SceneInstID nInstID, _MessagePtrT Ptr)
	{
		if (nInstID >= 0 && nInstID < (int)m_ScenePtrVec.size())
		{
			ConstMessagePtr csp = boost::static_pointer_cast<const Message, typename _MessagePtrT::element_type>(Ptr);
			m_ScenePtrVec[nInstID]->ReceiveMessage(csp);
		}
	}
	template<typename _MessagePtrT>
	void BroadcastMessage(_MessagePtrT Ptr)
	{
		for (int i = 0; i < (int)m_ScenePtrVec.size(); i++)
		{
			SendMessage(i, Ptr);
		}
	}
public:
	void SendMarchEnterSceneMessage(SceneInstID nInstID, MarchEnterSceneMsgPtr Ptr)
	{
		if (nInstID >= 0 && nInstID < (int)m_ScenePtrVec.size())
		{
			m_ScenePtrVec[nInstID]->IncEnteringPlayerCount();
			SendMessage(nInstID, Ptr);
		}
	}

public:
	int GetSceneInstCount(void) const {return static_cast<int>(m_ScenePtrVec.size());}
protected:
	ScenePtrVec m_ScenePtrVec;	//¡¾stl¡¿

public:
	InvokerPtr FetchSceneInvoker(void);
protected:
	void AddSceneInvoker(const InvokerPtr Ptr);
private:
	InvokerPtrList m_InvokerPtrList;	//¡¾stl¡¿

public:
	int GetSceneType(void) const { return m_nSceneType; }
	void SetSceneType(int nSceneType) { m_nSceneType = nSceneType; }
protected:
	int m_nSceneType;

public:
	SceneClassID GetSceneClassID(void) const {return m_nClassID;}
	void SetSceneClassID(SceneClassID nClassID) {m_nClassID = nClassID;}
protected:
	SceneClassID m_nClassID;

public:
	int GetMaxPlayerCountA(void) const {return m_nMaxPlayerCountA;}
	void SetMaxPlayerCountA(int nMaxPlayerCountA) {m_nMaxPlayerCountA = nMaxPlayerCountA;}
	int GetMaxPlayerCountB(void) const {return m_nMaxPlayerCountB;}
	void SetMaxPlayerCountB(int nMaxPlayerCountB) {m_nMaxPlayerCountB = nMaxPlayerCountB;}
protected:
	int m_nMaxPlayerCountA;
	int m_nMaxPlayerCountB;

public:
	void InitSceneObstacle(int nWidth, int nHeight, const char *szObstacleFileName);
protected:
	SceneObstacle m_SceneObstacle;
};

typedef boost::shared_ptr<SceneClass> SceneClassPtr;
typedef std::map<int, SceneClassPtr> SceneClassPtrMap;

#endif
