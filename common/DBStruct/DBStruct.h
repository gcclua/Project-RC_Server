
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

//玩家称号长度
#define MAX_CHARACTER_TITLE 34

#define RANDOM_NAME_BUFFER_MAX (100000)
#define RANDOM_NAME_SEND_COUNT (10)
#define RANDOM_NAME_SEARCH_MAX (5000)

//账号保存角色个数
#define		DB_CHAR_NUMBER				3

//数据库名称长度
#define		DATABASE_STR_LEN			128
//数据库用户名长度
#define		DB_USE_STR_LEN				32
//数据库密码长度
#define		DB_PASSWORD_STR_LEN			32

// Memeched服务器配置长度
#define      DB_MEM_SERVERLIST_LEN      256

// 停服存储开始时的时间延迟，避免有消息只进入队列而没有Handle处理（单位S)
#define      DB_FINAL_SAVE_DELAY_TIME   60

//玩家数据存储DB时间间隔（单位ms）
#define		DB_USER_SAVE_DB_INTERVAL	10*60*1000

// 公共数据存储间隔时间
#define  TILE_DATA_SAVE_SEC (12*60) // 地块信息

//错误信息最大长度
#define     DB_MAX_ERROR_BUFF			(512)



enum DB_TASK_TYPE
{
	DB_TASK_INVALID  = INVALID_ID,
	DB_TASK_USER_DATA = 1, // 玩家数据存储
	DB_TASK_CREATECHAR,    // 创建角色
	DB_TASK_WORDMAP,
	DB_TASK_CREATERCHAR,
	DB_TASK_GUID,
	DB_TASK_CHARLIST,
	DB_TASK_RANDOMNAME,
	DB_TASK_CREATERCITY,
	DB_TASK_WORDMARCH,
	DB_TASK_MARCH,

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
		RESULT_FAIL,         //失败
		RESULT_SUCCESS,       //成功
		RESULT_SAME_NAME,    // 角色重名
		RESULT_SAME_GUID,    // guid重复
		RESULT_CHARNUM,      // 已存在角色
		RESULT_RET_DATA_FALL  // 返回角色错误
	};

};


struct DB_QUERY
{
	tbyte	m_SqlStr[MAX_SQL_LENGTH];		//执行的Sql语句

	void	Clear()
	{
		m_SqlStr[0] = '\0';
	}

	void	Parse(const tchar* pTemplate,...);

};

struct LONG_DB_QUERY
{
	tbyte	m_SqlStr[MAX_LONG_SQL_LENGTH];		//执行的Sql语句

	void	Clear()
	{
		m_SqlStr[0] = '\0';
	}

	void	Parse(const tchar* pTemplate,...);
};


char		Value2Ascii(char in);
char		Ascii2Value(char in);

bool        Binary2String(const tchar* pIn,tuint32 InLength,tchar* pOut, tuint32 OutLength = invalid_id);
bool        DBStr2Binary(const tchar* pIn,tuint32 InLength,tchar* pOut,tuint32 OutLimit,tuint32& OutLength);
bool		String2Binary(const char* pIn,tuint32 InLength,char* pOut,tuint32 OutLimit,tuint32& OutLength);

//公共数据加载存储时动态申请的数据结构模板
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

//Guid
struct DBGuidData
{
public:
	void CleanUp();
	void CopyFrom(const DBGuidData& rSour);
public:
	DBGuidData(){CleanUp();}
public:
	tuint8	m_Type;
	int64	m_Serial;
};


#endif
