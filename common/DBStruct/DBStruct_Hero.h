
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

public:
	int     m_nType;    //Ӣ������
	int     m_nLevel;   //�ȼ�
	int     m_nQuality; // Ʒ��
	int64   m_nCityID;  // ����ID
	int64   m_nExp;     // ����ֵ
};

typedef DBCommonData<DBHero> DBHeroData;
typedef boost::shared_ptr<DBHeroData> DBHeroDataPtr;


#endif
