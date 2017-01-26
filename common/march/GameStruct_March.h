
#ifndef _GAMESTRUCT_MARCH_H_
#define _GAMESTRUCT_MARCH_H_

#include "Base.h"
#include "GameDefine_March.h"
#include "service/TimeInfo.h"
#include "troop/GameStruct_Troop.h"
#include "hero/GameStruct_Hero.h"
#include "DBStruct/DBStruct_March.h"
#include "Scene/GameStruct_Scene.h"

class March
{
public:
	March();
	virtual ~March();

	void CleanUp();

	March& operator=(March const& rhs);

public:
	void Tick(const TimeInfo& rTimeInfo);
	void OnLogin();

public:
	void SerializeToDB(DBMarch& rDest) const;
	void SerializeFromDB(const DBMarch& rSource);

public:
	
	ScenePos  GetPos() const {return m_pos;}
	void  SetPos(ScenePos nVal){m_pos = nVal;}


	int   GetBeginTime() const {return m_nBeginTime;}
	void  SetBeginTime(int nVal) {m_nBeginTime = nVal;}

	int   GetEndTime() const {return m_nEndTime;}
	void  SetEndTime(int nVal) {m_nEndTime = nVal;}

	int64 GetMarchId() const {return m_nMarchId;}
	void  SetMarchId(int64 nVal) {m_nMarchId = nVal;}

	int64 GetPlayerId() const {return m_nPlayerId;}
	void  SetPlayerId(int64 nVal) {m_nPlayerId = nVal;}

	int64 GetCityId() const {return m_nCityId;}
	void  SetCityId(int64 nVal) {m_nCityId = nVal;}

	int64 GetFightId() const {return m_nFightId;}
	void  SetFightId(int64 val) {m_nFightId = val;}

	int   GetStatus() const {return m_nStatus;}
	void  SetStatus(int nStatus){m_nStatus = nStatus;}

	int   GetWorldId() const {return m_nWorldId;}
	void  SetWorldId(int val) {m_nWorldId = val;}

	int64 GetForce() const {return m_nForce;}
	void  SetForce(int val) {m_nForce = val;}

	int64 GetBuildId() const {return m_nBuildId;}
	void  SetBuildId(int64 val){m_nBuildId = val;}

	int  GetSceneInstId() const {return m_nInstSceneId;}
	void SetSceneInstId(int nSceneId) {m_nInstSceneId = nSceneId;}

	int  GetSceneClass() const {return m_nSceneClass;}
	void SetSceneClass(int nClassId){m_nSceneClass = nClassId;}

	HERONAME GetName() const {return m_Hero.GetName();}

public:
	Hero GetHero() const {return m_Hero;}
	void SetHero(const Hero& rHero){m_Hero = rHero;}

	void FillMarchBaseInfo(MarchBaseInfo &rInfo);

public: 
	void SetHeroHp(int nHp);
	void SetTroopHp(int nArrangeIndex,int nHp);

private:
	// �����hero
	Hero m_Hero;

public:
	// ���Ӷ������
	bool AddTroop(int QueueIndex,int nTroopType,int nHp);

	// ����Ƿ�������Ӿ���
	bool CheckAddTroop(int QueueIndex,int nTroopType);

	// �������������Ϣ
	TroopList_T GetTroopList() const {return m_TroopList;}
	void SetTroopList(const TroopList_T& rTroopList) {m_TroopList = rTroopList;}

	// ����ÿ�������������е�λ��
	bool  SwapQueueForArrange(int nArrange1,int nArrange2);

	// ���ĳ���������פ��Ӣ��
	int64  GetHeroId();

	// ��ȡÿ�����������
	Troop GetQueueTroop(int nIndex);

private:
	TroopList_T m_TroopList;

	// ÿ�����Ӷ�Ӧ������ID
	TroopMarchMap m_TroopMarchMap;

private:
	ScenePos  m_pos;		//���ͼ��������
	int    m_nBeginTime; // ����ʱ��
	int    m_nEndTime;   // ����ʱ��
	int64  m_nMarchId;   // Ψһ��ʾ
	int64  m_nPlayerId;  // ���ID
	int64  m_nCityId;    // ����ID
	int    m_nStatus;    // ״̬
	int    m_nSpeed;     // �ٶ�
	int    m_nWorldId;   // �����ַ�ID
	int64  m_nFightId;   // ��ս��
	int    m_nForce;     // ս�������������������ط�
	int64  m_nBuildId;   // ��Ӧ�Ľ���ID

	tint32  m_nSceneClass;	 //�ϴε�¼����
	tint32  m_nInstSceneId;  //�ϴε�¼����ʵ��ID
};
typedef boost::shared_ptr<March> MarchPtr;
typedef std::map<int64,MarchPtr> MarchPtrMap;
typedef std::map<int64,int64> BuildMarchMap;
#endif