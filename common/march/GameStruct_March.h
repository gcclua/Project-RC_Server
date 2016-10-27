
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

public:
	void SerializeToDB(DBMarch& rDest) const;
	void SerializeFromDB(const DBMarch& rSource);

public:
	
	ScenePos  GetPosX() const {return m_pos;}
	void  SetPosX(ScenePos nVal){m_pos = nVal;}


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

	int   GetStatus() const {return m_nStatus;}
	void  SetStatus(int nStatus){m_nStatus = nStatus;}

	HERONAME GetName() const {return m_Hero.GetName();}

public:
	Hero GetHero() {return m_Hero;}
	void SetHero(const Hero& rHero){m_Hero = rHero;}
	
	TroopList_T GetTroopList() {return m_TroopList;}
	void SetTroopList(const TroopList_T& rTroopList) {m_TroopList = rTroopList;}

private:
	// �����hero
	Hero m_Hero;

public:

	// ��ȡÿ�����������
	Troop GetQueueTroop(int nIndex);

private:
	TroopList_T m_TroopList;

private:
	ScenePos  m_pos;		//��������
	int    m_nBeginTime; // ����ʱ��
	int    m_nEndTime;   // ����ʱ��
	int64  m_nMarchId;   // Ψһ��ʾ
	int64  m_nPlayerId;  // ���ID
	int64  m_nCityId;    // ����ID
	int    m_nStatus;    // ״̬
	int    m_nSpeed;     // �ٶ�
};
typedef boost::shared_ptr<March> MarchPtr;
#endif