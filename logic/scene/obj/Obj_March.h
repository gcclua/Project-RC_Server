#ifndef _OBJ_MARCH_
#define _OBJ_MARCH_

#include "Obj_Character.h"
#include "Scene/GameStruct_Scene.h"
#include "Service/TimeInfo.h"
#include "hero/GameStruct_Hero.h"
#include "troop/GameStruct_Troop.h"
#include "service/Message.h"

class Player;
class Packet;
class MarchReqNearListMsg;
class MarchMoveMsg;

class Obj_March : public Obj_Character
{
public:
	Obj_March();
	virtual ~Obj_March(void);


public:
	virtual int GetObjType(void) const {return ObjType::MARCH;}

public:
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);

	virtual void Tick(const TimeInfo &rTimeInfo);

	void OnLogin(void);
	void OnLogout(void);

	virtual bool GetActive(void) const {return true;}

	//////////////////////////////////////////////////////////////////////////
	// ���� begin
	//////////////////////////////////////////////////////////////////////////
public:
	void Tick_General(const TimeInfo &rTimeInfo);	//ÿ�ε���
private:
	int m_nTickSecondTime;

public:
	time_t GetLastLogoutTime() const { return m_LastLogoutTime; }
	time_t GetCurLoginTime() const { return m_CurLoginTime; }
	time_t GetCreateRoleTime() const{return m_CreateRoleTime;}

private:
	time_t m_LastLogoutTime;		//�ϴεǳ�ʱ��
	time_t m_CurLoginTime;			//���ε���ʱ��
	time_t m_CreateRoleTime;        //��ɫ����ʱ��

public:
	void SendMessage(MessagePtr MsgPtr);

public:
	void FillMarchBaseInfo(MarchBaseInfo &rInfo);
	//TODO:���ݸı�ʱ���ô˺���
	void UpdateMarchBaseInfoToSceneService(void);

public:
	int64 GetGuid(void) const {return m_Guid;}
	void SetGuid(int64 Guid) {m_Guid = Guid;}
private:
	int64 m_Guid;

public:
	virtual void MoveTo(const ScenePos &rPos, float fStopDistance = 0.05f);
	void MoveAppend(const ScenePos &rPos);
public:
	virtual void Tick_Moving(const TimeInfo &rTimeInfo);
protected:
	virtual void OnScenePosChanged(void);

public:
	bool		IsUserBitLocked(USER_BITLOCKTYPE bltType){return m_BitLock.GetBit(bltType);}
	void		SetUserBitLocked(USER_BITLOCKTYPE bltType,uint32 nContinuTime);

public:
	void	AuditNewPlayerLog(int nType);

private:
	//������������е�bitlock
	void		UpdateBitLock();
	BitSet<USER_BITLOCK_NUM>	m_BitLock;
	struct UserBitLockInfo
	{
	public:
		uint32 m_nContinuedTime; //����ʱ�� ��λ����
		uint32 m_nStartLoackTime;//����ʱ��
		void CleanUp()
		{
			m_nContinuedTime =0;
			m_nStartLoackTime =0;
		}
	};
	bsarray<UserBitLockInfo, USER_BITLOCK_NUM> m_UserBitLockInfo;

	//////////////////////////////////////////////////////////////////////////
	// ��ʱ�洢 begin
	//////////////////////////////////////////////////////////////////////////
private:
	void TimingSave(void) {Save(false);}
	void RealSave(void) {Save(true);}
private:
	void Save(bool bImmediate);
private:
	void Tick_Save(const TimeInfo &rTimeInfo);
private:
	int m_nSaveTimeInterval;
	//////////////////////////////////////////////////////////////////////////
	// ��ʱ�洢 end
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// march��Ұ begin
	//////////////////////////////////////////////////////////////////////////
public:
	void Tick_View(const TimeInfo &rTimeInfo);
	bool IsInSight(int nObjID);
private:
	void OnInSight(Obj &rObj);
	void OnOutSight(int nObjID);
private:
	void ForceInSight(Obj &rObj);	
private:
	void CleanUpView(void);
private:
	typedef std::map<int, bool> ViewObjIDMap;
	ViewObjIDMap m_ViewObjIDMap;	//��stl��
	int m_TickViewInterval;
	//////////////////////////////////////////////////////////////////////////
	// �����Ұ end
	//////////////////////////////////////////////////////////////////////////

public:
	ScenePos	GetChangeScenePos(void) const;
	void		SetChangeScenePos(const ScenePos &rPos);
private:
	void		UpdateChangeScenePosOnLogin(void);
private:
	ScenePos	m_ChangeScenePos;

	//////////////////////////////////////////////////////////////////////////
	// ���λ����� begin
	//////////////////////////////////////////////////////////////////////////
public:
	SceneID		GetLastSceneID(void) const;
	void		SetLastSceneID(const SceneID &rSceneID);
	ScenePos	GetLastScenePos(void) const;
	void		SetLastScenePos(const ScenePos &rScenePos);
private:
	void		UpdateLastSceneIDAndScenePos(void);
private:
	SceneID		m_LastSceneID;	//�����������
	ScenePos	m_LastScenePos;	//�������������λ��

public:
	SceneID		GetLastNoneCopySceneID(void) const;
	void		SetLastNoneCopySceneID(const SceneID &rSceneID);
	ScenePos	GetLastNoneCopyScenePos(void) const;
	void		SetLastNoneCopyScenePos(const ScenePos &rScenePos);
private:
	void		UpdateLastNoneCopySceneIDAndScenePos(void);
private:
	SceneID		m_LastNoneCopySceneID;	//��������Ǹ�������
	ScenePos	m_LastNoneCopyScenePos;	//��������Ǹ���������λ��

	//////////////////////////////////////////////////////////////////////////
	// ���λ����� end
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// ��������б���� begin
	//////////////////////////////////////////////////////////////////////////
public:
	void HandleMessage(const MarchReqNearListMsg &rMsg);
	void HandleMessage(const MarchMoveMsg &rMsg);
private:
	void	SendSceneMarchListToClient(const MarchReqNearListMsg &rMsg);
	//////////////////////////////////////////////////////////////////////////
	// ��������б���� end
	//////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	//������ص�
	//////////////////////////////////////////////////////////////////////////
public:
	void SetHero(const Hero& rHero){m_Hero = rHero;}
	void SetTroop(const TroopList_T& rTroopList) {m_TroopList = rTroopList;}
private:
	// �����hero
	Hero m_Hero;

public:

	// ��ȡÿ�����������
	Troop GetQueueTroop(int nIndex);

private:
	TroopList_T m_TroopList;

	/////////////////////////////////////////////////////////////////////////////
	//march������Ϣ
	/////////////////////////////////////////////////////////////////////////////
public:
	ScenePos  GetScenePosX() const {return m_ScenePos;}
	void  SetScenePos(ScenePos nVal){m_ScenePos = nVal;}


	int64 GetMarchId() const {return m_nMarchId;}
	void  SetMarchId(int64 nVal) {m_nMarchId = nVal;}

	int64 GetPlayerId() const {return m_nPlayerId;}
	void  SetPlayerId(int64 nVal) {m_nPlayerId = nVal;}

	int64 GetCityId() const {return m_nCityId;}
	void  SetCityId(int64 nVal) {m_nCityId = nVal;}

	HERONAME GetName() const {return m_Name;}
	void   SetName(HERONAME szName) {m_Name=szName;}


private:
	ScenePos m_ScenePos;
	int64  m_nMarchId;   // Ψһ��ʾ
	int64  m_nPlayerId;  // ���ID
	int64  m_nCityId;    // ����ID
	int    m_nSpeed;     // �ٶ�
	
	HERONAME m_Name;        // ����

};

POOLDEF_DECL(Obj_March);

typedef GeneralObjRefCont<Obj_March, 256> MarchRefCont;

#endif
