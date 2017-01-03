
#ifndef __DBSTRUCT_HERO_H__
#define __DBSTRUCT_HERO_H__

#include "DBStruct.h"
#include "troop/GameDefine_Troop.h"



// ��ҳ�����Ϣ
struct DBHero
{
public:
	DBHero(){CleanUp();};
	~DBHero(){};

	void CleanUp( );
	void CopyFrom(const DBHero& rSource);

	void InitHero(int nHeroType,int64 nCityId);

public:
	int     m_nType;    //Ӣ������
	int     m_nLevel;   //�ȼ�
	int     m_nQuality; // Ʒ��
	int64   m_nCityID;  // ����ID
	int64   m_nExp;     // ����ֵ
	int     m_nStatus;  // Ӣ��״̬
	int64   m_nMarchId; // �������Ǹ�March
	int     m_nHp;       // ��ǰ��Ѫ��
	int     m_nArrangeIndex; // ���ε�λ��
	int     m_nQueueIndex;   // ���е�λ��
	int64   m_nHeroId;//Ӣ��ΨһID
};

typedef DBCommonData<DBHero> DBHeroData;
typedef boost::shared_ptr<DBHeroData> DBHeroDataPtr;


#endif
