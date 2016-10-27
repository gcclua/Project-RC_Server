
#ifndef __DBSTRUCT_H__
#define __DBSTRUCT_H__

#include "Base.h"

#define		MAX_SQL_LENGTH				4096
#define		MAX_LONG_SQL_LENGTH			204800

#define		USE_MYSQL


#define		HOST_STR_LEN				30
#define		CONNECTION_NAME_LEN			32


enum DB_NAMES
{
	CHARACTER_DATABASE	= 1,
};


#define MAX_CHARACTER_NAME 30

//��ҳƺų���
#define MAX_CHARACTER_TITLE 34

//���ݿ����Ƴ���
#define		DATABASE_STR_LEN			128
//���ݿ��û�������
#define		DB_USE_STR_LEN				32
//���ݿ����볤��
#define		DB_PASSWORD_STR_LEN			32

// Memeched���������ó���
#define      DB_MEM_SERVERLIST_LEN      256

// ͣ���洢��ʼʱ��ʱ���ӳ٣���������Ϣֻ������ж�û��Handle������λS)
#define      DB_FINAL_SAVE_DELAY_TIME   60

// �������ݴ洢���ʱ��
#define  TILE_DATA_SAVE_SEC (12*60) // �ؿ���Ϣ



enum DB_TASK_TYPE
{
	DB_TASK_INVALID  = INVALID_ID,
	DB_TASK_USER_DATA = 1, // ������ݴ洢
	DB_TASK_CREATECHAR,    // ������ɫ
	DB_TASK_TILE,

	DB_TASK_MAX_NUM,
};

#ifndef MAXPATH
#define  MAXPATH 260
#endif

class DBMsgResult
{
public:
	enum 
	{
		RESULT_FALL,         //ʧ��
		RESULT_SUCESS,       //�ɹ�
		RESULT_SAME_NAME,    // ��ɫ����
		RESULT_SAME_GUID,    // guid�ظ�
		RESULT_CHARNUM,      // �Ѵ��ڽ�ɫ
		RESULT_RET_DATA_FALL  // ���ؽ�ɫ����
	};

};


struct DB_QUERY
{
	UCHAR	m_SqlStr[MAX_SQL_LENGTH];		//ִ�е�Sql���

	VOID	Clear()
	{
		memset(m_SqlStr,0,MAX_SQL_LENGTH);
	}

	VOID	Parse(const char* pTemplate,...);

};

struct LONG_DB_QUERY
{
	UCHAR	m_SqlStr[MAX_LONG_SQL_LENGTH];		//ִ�е�Sql���

	VOID	Clear()
	{
		memset(m_SqlStr,0,MAX_LONG_SQL_LENGTH);
	}

	VOID	Parse(const char* pTemplate,...);
};


char		Value2Ascii(char in);
char		Ascii2Value(char in);

bool		Binary2String(const char* pIn,tuint32 InLength,char* pOut);
bool		DBStr2Binary(const char* pIn,tuint32 InLength,char* pOut,tuint32 OutLimit,tuint32& OutLength);
bool		String2Binary(const char* pIn,tuint32 InLength,char* pOut,tuint32 OutLimit,tuint32& OutLength);

//�������ݼ��ش洢ʱ��̬��������ݽṹģ��
template<typename _ElemType>
struct DBCommonData
{
public:
	int m_Count;
	_ElemType* m_pData;

public:
	DBCommonData<_ElemType>()
	{
		m_Count = 0;
		m_pData = null_ptr;
	}

	~DBCommonData<_ElemType>()
	{
		SAFE_DELETE_ARRAY(m_pData);
		m_pData = 0;
	}
	
	bool InitDataArray(int count)
	{
		__ENTER_FUNCTION
			AssertEx(count > 0,"");
		    AssertEx(null_ptr == m_pData,"");
			m_pData = new _ElemType[count];
			AssertEx(m_pData,"");
			m_Count = count;
			return true;
		__LEAVE_FUNCTION
			return false;
	}
};


#endif
