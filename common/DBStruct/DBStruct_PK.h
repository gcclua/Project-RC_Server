////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺17:38 2014-01-01
//             ˵����PK������ݴ洢�ṹ
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBSTRUCTPK_H__
#define __DBSTRUCTPK_H__

#include "Base.h"
#include "CombatStruct/GameStruct_PK.h"

/*******************************************************************************/
//	�ر�ע�⣺1)DBPKAttackerList������Struct��Ҫ���� plain struct��������
//			  ���Բ��ܰ���ָ�룬���ã��麯����
//            2)����CleanUp��CopyFrom����������������Ϣ�俽�����ݣ���
/*******************************************************************************/
struct DBPKAttackerInfo
{
public:
	DBPKAttackerInfo() {CleanUp();}
	void	CleanUp();
	void	CopyFrom(const DBPKAttackerInfo& rItemData);

public:
	int64 m_AttackerGUID;
	time_t m_nAttackTime;//�����б��ʣ��ʱ�� ��λ����
};
struct DBPKAttackerList
{
public:
	DBPKAttackerList() {CleanUp();}
	void	CleanUp();
	void	CopyFrom(const DBPKAttackerList& rSour);
public:
	DBPKAttackerInfo m_AttackerList[PKAttackerList::MAX_LIST_SIZE];
};

#endif