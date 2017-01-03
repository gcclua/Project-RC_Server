////////////////////////////////////////////////////////////////////////////////////////
//ʱ�䣺2014��7��2��11:40:55
//˵����������ֱ�
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DBRANDOMNAME_H__
#define __DBRANDOMNAME_H__
/*******************************************************************************/
//	�ر�ע��:1)DBRandomName������Struct��Ҫ���� plain struct�����������Բ��ܰ���ָ�룬���ã��麯����
//          2)����CleanUp��CopyFrom����������������Ϣ�俽�����ݣ���
//	        3)����GetKey��������Struct���Բ���������
/*******************************************************************************/
#include "Base.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct.h"
struct DBRandomName
{
public:
	DBRandomName(){CleanUp();}
	~DBRandomName(){}	 
	void CleanUp();
	void CopyFrom(const DBRandomName& rSour);
public:
	tchar  m_szName[MAX_NAME_SIZE];
};
struct DBRandomNameList
{
public:
	DBRandomNameList(){CleanUp();}
	~DBRandomNameList(){}	 
	void CleanUp();
	void CopyFrom(const DBRandomNameList& rSour);
public:	
	DBRandomName m_RandomNameList[RANDOM_NAME_BUFFER_MAX];
};

#endif//__DBRANDOMNAME_H__