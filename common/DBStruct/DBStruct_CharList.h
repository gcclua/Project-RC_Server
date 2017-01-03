////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺17:58 2014-02-18
//             ˵������ɫ�б�ṹ
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBSTRUCTCHARLIST_H__
#define __DBSTRUCTCHARLIST_H__
/*******************************************************************************/
//	�ر�ע�⣺1)DBCharList������Struct��Ҫ���� plain struct��������
//			  ���Բ��ܰ���ָ�룬���ã��麯����
//            2)����CleanUp��CopyFrom����������������Ϣ�俽�����ݣ���
//			  3)����GetKey��������Struct���Բ���������
/*******************************************************************************/
#include "Base.h"
#include "Scene/GameStruct_Scene.h"
struct DBCharData
{
public:
	DBCharData(){CleanUp();}
	~DBCharData(){}	 
	void CleanUp();
	void CopyFrom(const DBCharData& rSour);

public:
	int64	m_Guid;
	tchar   m_CharName[MAX_NAME_SIZE];
};

struct DBCharDataList
{
public:
	DBCharDataList(){CleanUp();}
	~DBCharDataList(){}	 
	void CleanUp();
	void CopyFrom(const DBCharDataList& rSour);
public:
	tint32	   m_CharNum;
	DBCharData m_CharDataList[DB_CHAR_NUMBER];
};

#endif