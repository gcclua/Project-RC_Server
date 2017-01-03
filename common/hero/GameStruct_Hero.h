
#ifndef _GAMESTRUCT_HERO_H_
#define _GAMESTRUCT_HERO_H_

#include "Base.h"
#include "GameDefine_Hero.h"
#include "DBStruct/DBStruct_Hero.h"
#include "skill/GameStruct_Skill.h"


class Hero
{

public:
	Hero();
	virtual ~Hero(void);

	void CleanUp();


	Hero& operator=(Hero const& rhs);

public:
	void Tick(const TimeInfo& rTimeInfo);
	void OnLogin();

public:
	void SerializeToDB(DBHero& rDest) const;
	void SerializeFromDB(const DBHero& rSource);


public:
	int64 AddExp(int64 nAdd);

public:

	int64 GetUID() const {return m_nID;}
	void  SetUID(int64 uid){m_nID=uid;}

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}

	int  GetLevel() const {return m_nLevel;}
	void SetLevel(int nVal) {m_nLevel = nVal;}

	int  GetQuality() const {return m_nQuality;}
	void SetQuality(int nVal) {m_nQuality=nVal;}

	int64 GetExp() const {return m_nExp;}
	void  SetExp(int64 nVal){m_nExp=nVal;}

	int   GetHp() const {return m_nHp;}
	void  SetHp(int nVal) {m_nHp=nVal;}

	int   GetStatus() const {return m_nStatus;}
	void  SetStatus(int val) {m_nStatus = val;}

	HERONAME GetName() const {return m_Name;}
	void   SetName(HERONAME szName) {m_Name=szName;}

	// ����ID
	int64    GetCityID() const {return m_nCityID;}
	void   SetCityID(int64 val) {m_nCityID = val;}

	int64  GetMarchId() const {return m_nMarchId;}
	void   SetMarchId(int64 val) {m_nMarchId = val;}

	int   GetArrangeIndex() const {return m_nArrangeIndex;}
	void  SetArrangeIndex(int val) {m_nArrangeIndex = val;}

	CooldownList_T&		GetCooldownList(void){return m_CoolDownList;}
	CooldownList_T const& GetCooldownList(void)const{return m_CoolDownList;}
	tint32				GetOwnSkill(tint32 index) const;
	void				SetOwnSkill(tint32 skillId, tint32 index);
	void				AddOwnSkill(tint32 skillId);

private:
	int     m_nType;    //Ӣ������
	int     m_nLevel;   //�ȼ�
	int     m_nQuality; // Ʒ��
	int     m_nHp;      // Ѫ��
	int64   m_nExp;         // ����ֵ
	int64   m_nCityID;  // ��������
	HERONAME m_Name;        // ����
	int64   m_nID;       // Ӣ�۵�uid
	int     m_nArrangeIndex; // ���ε�λ��

	int     m_nStatus;    // Ӣ�۵�״̬
	int64   m_nMarchId;   // Ӣ���������Ǹ�March��

	CooldownList_T		m_CoolDownList;					//��ȴ�б�
	TroopOwnSkillList	m_OwnSkillList;					//�����б�
	
};

typedef boost::shared_ptr<Hero> HeroPtr;
typedef std::map<int64,HeroPtr> HeroPtrMap;


#endif