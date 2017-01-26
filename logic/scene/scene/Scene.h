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
//����������λ��ƽ��ֱ������ϵ��һ���ޣ���(0,0)��λ�����½�
//0����ָ��X��������
//����ͻ��˲�ͬ���ͻ���ע��ת��
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
	// ս����ص���Ϣ��
	virtual void HandleMessage(const ReqSetRobotOpenMsg& rMsg){};
	
protected:
	void Initialize(void);
protected:
	void CallOnCreateScript(void);
	//////////////////////////////////////////////////////////////////////////
	//����ID��Ϣ
public:
	void SetSceneClassID(SceneClassID nClassID) {m_nClassID = nClassID;}
	SceneClassID GetSceneClassID(void) const {return m_nClassID;}
	void SetSceneInstID(SceneInstID nInstID) {m_nInstID = nInstID;}
	SceneInstID GetSceneInstID(void) const {return m_nInstID;}
protected:
	SceneClassID	m_nClassID;			//��������ID
	SceneInstID		m_nInstID;			//����ʵ��ID
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�����������
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
	//�����ӿ�
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
	//Obj����������
	//���ص�����ָ����Ҫ�ж���Ч�ԣ�����
protected:
	void				NpcInit(void);

public:
	Obj_NpcPtr			CreateNpc(int nDataID, const ScenePos &rPos, bool bReliveable,int nForce, int nLevel = invalid_id,Obj_NpcPtr NpcPtr = null_ptr);

	Obj_MarchPtr		CreateMarch(const March& rMarchData,const ScenePos& rPos);

	Obj_SnarePtr		CreateSnareObj(tint32 nSnareID,tint32 OwnerId, const ScenePos &rPos);

	// ����Ӣ�۶���
	Obj_HeroPtr         CreateHeroObj(const Hero& rHero,const ScenePos &rPos,int nForce);

	// ��������         
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

	//Obj�ײ���룬��Ϸ�߼����õ�����Щ������Ҳ���÷�����Щ��Ա����
protected:
	void _AddMarchImmediate(Obj_MarchPtr userPtr, bool bFirstEnter);
	void _AddNonMarchObj(ObjPtr Ptr);
protected:
	void _DelMarchImmediate(int nObjID);
	ObjPtrMap::iterator _DelNonUserObjImmediate(ObjPtrMap::iterator itRemove);
protected:
	ObjPtrMap m_ObjPtrMap;				//��stl��
	ObjPtrVec m_AddingCacheObjPtrVec;	//��stl��
protected:
	int _AllocObjID(void);
	int _IncObjID(void);
	int m_nObjIDAlloc;
protected:
	void DelAllNonUserObj(void);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�����㲥
	//ʹ�ó����㲥ʱ��ע�⿼���Ƿ�㲥���Լ�������������
public:
	//����������ҷ���Ϣ
	void BroadCast(MessagePtr MsgPtr);
	//����������ҷ���Ϣ��������nObjIDָ�������
	void BroadCast_Except(MessagePtr MsgPtr, int nObjID);
	//���ܿ���nObjID�ĳ�������ҷ���Ϣ������nObjIDָ�������
	void BroadCast_InSight_Include(MessagePtr MsgPtr, int nObjID);
	//���ܿ���nObjID�ĳ�������ҷ���Ϣ��������nObjIDָ�������
	void BroadCast_InSight_Except(MessagePtr rMsg, int nObjID);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Objɨ���߼�
	//Obj���ͣ��ڶ������ʣ�Ԥ����All��Character��User��Npc
	//�������򣨵��������ʣ���All��Ring��Circle�����Ρ������Ρ��ı��Ρ����Ρ�ֱ�ߵ�
	//ʹ�ó���ɨ��ʱ��ע�⿼��ɨ�������ܴ����Լ�������������
public:
	//////////////////////////////////////////////////////////////////////////
	//����ɨ��ӿ�
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
	//����Ѱ·
public:
	bool FindPath(const ScenePos &rPosStart, const ScenePos &rPosEnd, PathCont &rPathCont);
	bool FindStraight(const ScenePos &rPosStart, const ScenePos &rPosEnd, ScenePos &rPosEndRefixed);
	bool FindDest(const ScenePos& rPosStart, const ScenePos &rPosEnd, ScenePos &rPosEndRefixed);		//���ݾ���Ѱ��Ŀ���
public:
	const SceneObstacle & GetSceneObstacle(void) const {AssertEx(m_pSceneObstacle != null_ptr, "");return *m_pSceneObstacle;}
	void SetSceneObstacle(const SceneObstacle *pSceneObstacle) {AssertEx(m_pSceneObstacle == null_ptr, "");m_pSceneObstacle = pSceneObstacle;}
	bool IsScenePosWalkAble( const ScenePos &rScenePos);//������Ƿ��ǿ������ߵĵ�

private:
	const SceneObstacle *m_pSceneObstacle;
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	virtual void HandleMessage(const MarchOpenCopySceneMsg &rMsg);
	virtual void HandleMessage(const AskJoinCopySceneMsg &rMsg);
	virtual void HandleMessage(const MarchReqNearListMsg &rMsg);
	virtual void HandleMessage(const ReqMarchSetPosMsg &rMsg);
	//��Ҫ����ת����March���������Message����
	//MESSAGE_TRANSPORTTOMARCH_DECL(MarchReqNearListMsg);
	MESSAGE_TRANSPORTTOMARCH_DECL(MarchMoveMsg);
	//MESSAGE_TRANSPORTTOMARCH_DECL(MarchOpenCopySceneMsg);
	//MESSAGE_TRANSPORTTOMARCH_DECL(AskJoinCopySceneMsg);
	
	
	//////////////////////////////////////////////////////////////////////////
};

typedef boost::shared_ptr<Scene> ScenePtr;
typedef bsvector<ScenePtr> ScenePtrVec;

#endif
