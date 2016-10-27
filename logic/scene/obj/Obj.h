#ifndef _OBJ_H_
#define _OBJ_H_

#include "Scene/GameStruct_Scene.h"
#include "Service/TimeInfo.h"


class Scene;
class CopyScene;
class Obj_March;
class MainScene;

class Obj
{
public:
	Obj(void);
	virtual ~Obj(void);
private:
	Obj(const Obj &);
	Obj& operator=(const Obj &);

public:
	virtual int GetObjType(void) const {return ObjType::EMPTY;}

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

	//��������˶�״̬ˢ��ָ�����
	virtual void SendMoveStatus(Obj_March &rMarch) {}
	//�����е�User�ܷ񿴵��Լ�
	virtual bool CanBeView(Obj_March &rMarch);
	//�����е�Obj�ܷ���⵽�Լ�if ()

	virtual bool CanBeScout(Obj &rObj);

public:
	virtual void DelFromScene(void) {SetActive(false);}

public:
	virtual bool GetActive(void) const {return m_bActive;}
	void SetActive(bool bActive) {m_bActive = bActive;}
private:
	bool m_bActive;

public:
	int GetID(void) const {return m_nID;}
	void SetID(int nID) {m_nID = nID;}
private:
	int m_nID;

public:
	ScenePos GetScenePos(void) const {return m_ScenePos;}
	virtual void SetScenePos(ScenePos Pos);
	void ForceSetScenePos(ScenePos Pos);
protected:
	virtual void OnScenePosChanged(void) {}
protected:
	ScenePos m_ScenePos;



public:
	SceneClassID GetSceneClassID(void) const;
	SceneInstID GetSceneInstID(void) const;
public:
	bool IsInCopyScene(void) const;
public:
	//�ȵ���IsSceneValid������true���ܵ���GetScene��������׳��쳣
	bool IsSceneValid(void) const;
	Scene &GetScene(void) const;
	void SetScene(Scene *pScene);
	CopyScene* GetCopyScene(void) const;
private:
	Scene *m_pScene;

public:
	bool IsCharacter(void);
	bool IsMarch(void);
	bool IsNpc(void);
	bool IsHero(void);
	bool IsSoldier(void);
	bool IsSnareObj(void);
public:
	int GetStealthLev() const { return m_nStealthLev; }
	virtual void SetStealthLev(int val) { m_nStealthLev = val; }
	int GetScout() const { return m_nScout; }
	void SetScout(int val) { m_nScout = val; }

public:

	virtual int	GetSceneNpcID(void) const {return invalid_id;}
	virtual	void	SetSceneNpcID(int nSceneNpcID) {}
	virtual void	SetGroupID(int nGroupID){ }
	virtual int	GetGroupID(){ return invalid_id;}
	virtual void	SetMutexID(int nMutexID){}
	virtual int	GetMutexID(){ return invalid_id;}

protected:

	int m_nStealthLev;//������
	int m_nScout;//��켶��
};

typedef boost::shared_ptr<Obj> ObjPtr;
typedef bsvector<ObjPtr> ObjPtrVec;
typedef std::map<int, ObjPtr> ObjPtrMap;

typedef GeneralObjRefCont<Obj, 512> ObjRefCont;

#endif
