#ifndef _SCENE_H_
#define _SCENE_H_

#include "Scene/GameStruct_Scene.h"
#include "Scene/GameStruct_Obstacle.h"
#include "Service/ServiceCell.h"
#include "player/GamePlayerManager.h"
#include "ScanOperator.h"

#include "Scene/Obj/Obj_Npc.h"
#include "Scene/obj/Obj_Snare.h"
#include "march/GameStruct_March.h"
#include "service/Message.h"

//////////////////////////////////////////////////////////////////////////
//服务器场景位于平面直角坐标系第一象限，即(0,0)点位于左下角
//0朝向指向X轴正方向
//如与客户端不同，客户端注意转换
//////////////////////////////////////////////////////////////////////////


class Scene : public ServiceCell
{
public:
	Scene(void);
	virtual ~Scene(void);

public:
	friend class GamePlayerManager;

public:
	virtual void Tick(const TimeInfo &rTimeInfo);

protected:
	void Tick_Obj(const TimeInfo &rTimeInfo);
	void Tick_AddObjs(void);
	void Tick_DelObjs(void);
	void Tick_RunObjs(const TimeInfo &rTimeInfo);

public:
	void InitMarchObj(const March& rMarch){};
	
public:
	virtual void HandleMessage(const MarchEnterSceneMsg &rMsg);
	virtual void HandleMessage(const MarchAcceptChangeSceneMsg &rMsg);
	virtual void HandleMessage(const ReqMarchStartMsg &rMsg){};

public:
	// 战斗相关的消息包
	virtual void HandleMessage(const ReqSetRobotOpenMsg& rMsg){};
	
protected:
	void Initialize(void);
protected:
	void CallOnCreateScript(void);
	//////////////////////////////////////////////////////////////////////////
	//场景ID信息
public:
	void SetSceneClassID(SceneClassID nClassID) {m_nClassID = nClassID;}
	SceneClassID GetSceneClassID(void) const {return m_nClassID;}
	void SetSceneInstID(SceneInstID nInstID) {m_nInstID = nInstID;}
	SceneInstID GetSceneInstID(void) const {return m_nInstID;}
protected:
	SceneClassID	m_nClassID;			//场景类型ID
	SceneInstID		m_nInstID;			//场景实例ID
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//场景玩家数量
public:
	void SetCurPlayerCount(int nCurPlayerCount);
	int GetCurPlayerCount(void) const {return m_nCurPlayerCount;}
protected:
	int m_nCurPlayerCount;
public:
	void SetEnteringPlayerCount(int nEnteringPlayerCount) {m_nEnteringPlayerCount = nEnteringPlayerCount;}
	int GetEnteringPlayerCount(void) const {return m_nEnteringPlayerCount;}
	void IncEnteringPlayerCount(void) {m_nEnteringPlayerCount++;}
	void DecEnteringPlayerCount(void) {m_nEnteringPlayerCount--;}
protected:
	int m_nEnteringPlayerCount;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//副本接口
public:
	virtual bool GetActive(void) const {return true;}
	virtual void SetActive(void) {}
	virtual void OnObjEnter(int nID) {}
	virtual void OnObjLeave(int nID) {}
	virtual void OnObjEnterCombat(int nID) {}
	virtual void OnObjLeaveCombat(int nID) {}
	virtual void OnObjDie(int nID,int nKillerId) {}
	virtual void OnObjTeleportChangeScene(int nID) {}
	virtual bool IsCopyScene(void) const {return false;}
	virtual bool IsWildScene(void) const {return false;}
	virtual bool IsMainScene(void) const {return false;}
	virtual bool IsCanEnterByGuid(const int64 &rGuid) {return false;}
	virtual int GetCopyScenePlayType(void) const { return CopyScenePlayType::NONE; }
	virtual int GetCopySceneDifficulty(void) const { return CopySceneDifficulty::DEFAULT; }
	virtual int GetCopySceneTier(void) const { return 0; }
	virtual void SetCopySceneTier(int val) {}
	virtual int GetLevel(void) const {return 0;}
	virtual void SetLevel(int val) {}
	virtual void OnSceneCreate(){}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Obj创建、查找
	//返回的智能指针需要判断有效性！！！
protected:
	void				NpcInit(void);

public:
	Obj_NpcPtr			CreateNpc(int nDataID, const ScenePos &rPos, bool bReliveable,int nForce, int nLevel = invalid_id,Obj_NpcPtr NpcPtr = null_ptr);

	Obj_MarchPtr		CreateMarch(const March& rMarchData,const ScenePos& rPos);

	Obj_SnarePtr		CreateSnareObj(tint32 nSnareID,tint32 OwnerId, const ScenePos &rPos);

	// 创建英雄对象
	Obj_HeroPtr         CreateHeroObj(const Hero& rHero,const ScenePos &rPos,int nForce);

	// 创建军队         
	Obj_TroopPtr        CreateTroopObj(const Troop& rTroop,const ScenePos &rPos,int nForce);

public:
	Obj_MarchPtr		GetMarchByGuid(int64 guid);
	Obj_MarchPtr		GetMarchByID(int nObjID);
	Obj_NpcPtr			GetNpcByID(int nObjID);
	Obj_CharacterPtr	GetCharacterByID(int nObjID);
	ObjPtr				GetObjByID(int nObjID);
	Obj_SnarePtr		GetSnareObjByID(tint32 nObjID);
public:
	void				DelNpcByID(int nObjID);

	//Obj底层代码，游戏逻辑不得调用这些函数，也不得访问这些成员变量
protected:
	void _AddMarchImmediate(Obj_MarchPtr userPtr, bool bFirstEnter);
	void _AddNonMarchObj(ObjPtr Ptr);
protected:
	void _DelMarchImmediate(int nObjID);
	ObjPtrMap::iterator _DelNonUserObjImmediate(ObjPtrMap::iterator itRemove);
protected:
	ObjPtrMap m_ObjPtrMap;				//【stl】
	ObjPtrVec m_AddingCacheObjPtrVec;	//【stl】
protected:
	int _AllocObjID(void);
	int _IncObjID(void);
	int m_nObjIDAlloc;
protected:
	void DelAllNonUserObj(void);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//场景广播
	//使用场景广播时，注意考虑是否广播给自己！！！！！！
public:
	//给场景内玩家发消息
	void BroadCast(MessagePtr MsgPtr);
	//给场景内玩家发消息，不包括nObjID指定的玩家
	void BroadCast_Except(MessagePtr MsgPtr, int nObjID);
	//给能看到nObjID的场景内玩家发消息，包括nObjID指定的玩家
	void BroadCast_InSight_Include(MessagePtr MsgPtr, int nObjID);
	//给能看到nObjID的场景内玩家发消息，不包括nObjID指定的玩家
	void BroadCast_InSight_Except(MessagePtr rMsg, int nObjID);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Obj扫描逻辑
	//Obj类型（第二个单词）预计有All、Character、User、Npc
	//限制区域（第三个单词）有All、Ring、Circle、扇形、环扇形、四边形、矩形、直线等
	//使用场景扫描时，注意考虑扫描结果可能带有自己！！！！！！
public:
	//////////////////////////////////////////////////////////////////////////
	//基础扫描接口
	void Scan_All_All(ObjRefCont &Cont);
	void Scan_All_Ring(ObjRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance);
	void Scan_All_Circle(ObjRefCont &Cont, ScenePos OriginalPos, float fRadius);
	void Scan_All_Sector(ObjRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian);
	void Scan_All_Ray(ObjRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope);

	void Scan_Character_All(CharacterRefCont &Cont);
	void Scan_Character_Ring(CharacterRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance);
	void Scan_Character_Circle(CharacterRefCont &Cont, ScenePos OriginalPos, float fRadius);
	void Scan_Character_Sector(CharacterRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian);
	void Scan_Character_Ray(CharacterRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope);

	void Scan_March_All(MarchRefCont &Cont);
	void Scan_March_Ring(MarchRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance);
	void Scan_March_Circle(MarchRefCont &Cont, ScenePos OriginalPos, float fRadius);
	void Scan_March_Sector(MarchRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian);
	void Scan_March_Ray(MarchRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope);

	void Scan_March_Block(MarchRefCont&Cont,int nBlockId);

	void Scan_Npc_All(NpcRefCont &Cont);
	void Scan_Npc_Ring(NpcRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance);
	void Scan_Npc_Circle(NpcRefCont &Cont, ScenePos OriginalPos, float fRadius);
	void Scan_Npc_Sector(NpcRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian);
	void Scan_Npc_Ray(NpcRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope);

	//////////////////////////////////////////////////////////////////////////
protected:
	template<typename _Cont, typename _Scanner>
	void Scan(_Cont &cont, _Scanner &scanner)
	{
		for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); it++)
		{
			if ((*it).second->GetActive())
			{
				scanner(cont, (*it).second);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//场景寻路
public:
	bool FindPath(const ScenePos &rPosStart, const ScenePos &rPosEnd, PathCont &rPathCont);
	bool FindStraight(const ScenePos &rPosStart, const ScenePos &rPosEnd, ScenePos &rPosEndRefixed);
	bool FindDest(const ScenePos& rPosStart, const ScenePos &rPosEnd, ScenePos &rPosEndRefixed);		//根据距离寻找目标点
public:
	const SceneObstacle & GetSceneObstacle(void) const {AssertEx(m_pSceneObstacle != null_ptr, "");return *m_pSceneObstacle;}
	void SetSceneObstacle(const SceneObstacle *pSceneObstacle) {AssertEx(m_pSceneObstacle == null_ptr, "");m_pSceneObstacle = pSceneObstacle;}
	bool IsScenePosWalkAble( const ScenePos &rScenePos);//坐标点是否是可以行走的点

private:
	const SceneObstacle *m_pSceneObstacle;
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	virtual void HandleMessage(const MarchOpenCopySceneMsg &rMsg);
	virtual void HandleMessage(const AskJoinCopySceneMsg &rMsg);
	virtual void HandleMessage(const MarchReqNearListMsg &rMsg);
	virtual void HandleMessage(const ReqMarchSetPosMsg &rMsg);
	//需要场景转发给March的所有相关Message声明
	//MESSAGE_TRANSPORTTOMARCH_DECL(MarchReqNearListMsg);
	MESSAGE_TRANSPORTTOMARCH_DECL(MarchMoveMsg);
	//MESSAGE_TRANSPORTTOMARCH_DECL(MarchOpenCopySceneMsg);
	//MESSAGE_TRANSPORTTOMARCH_DECL(AskJoinCopySceneMsg);
	
	
	//////////////////////////////////////////////////////////////////////////
};

typedef boost::shared_ptr<Scene> ScenePtr;
typedef bsvector<ScenePtr> ScenePtrVec;

#endif
