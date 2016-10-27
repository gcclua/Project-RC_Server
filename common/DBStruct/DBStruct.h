
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

// 公共数据存储间隔时间
#define  TILE_DATA_SAVE_SEC (12*60) // 地块信息



enum DB_TASK_TYPE
{
	DB_TASK_INVALID  = INVALID_ID,
	DB_TASK_USER_DATA = 1, // 玩家数据存储
	DB_TASK_CREATECHAR,    // 创建角色
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
		RESULT_FALL,         //失败
		RESULT_SUCESS,       //成功
		RESULT_SAME_NAME,    // 角色重名
		RESULT_SAME_GUID,    // guid重复
		RESULT_CHARNUM,      // 已存在角色
		RESULT_RET_DATA_FALL  // 返回角色错误
	};

};


struct DB_QUERY
{
	UCHAR	m_SqlStr[MAX_SQL_LENGTH];		//执行的Sql语句

	VOID	Clear()
	{
		memset(m_SqlStr,0,MAX_SQL_LENGTH);
	}

	VOID	Parse(const char* pTemplate,...);

};

struct LONG_DB_QUERY
{
	UCHAR	m_SqlStr[MAX_LONG_SQL_LENGTH];		//执行的Sql语句

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


#endif
