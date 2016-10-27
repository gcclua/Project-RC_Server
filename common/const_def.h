#ifndef _CONST_DEF_H_
#define _CONST_DEF_H_

#pragma once
#include <vector>
#include <map>
#include <string>
#include "Commons.h"

#ifndef WIN32
#include <ext/hash_map>
using namespace __gnu_cxx;
namespace __gnu_cxx
{

	template<>
	struct hash<long long>
	{

		size_t
			operator()(long long __x) const
		{
			return __x;
		}
	} ;

	template<>
	struct hash<std::string>
	{

		size_t
			operator()(std::string __s) const
		{
			return __stl_hash_string(__s.c_str());
		}
	} ;
}
#else
#include <hash_map>
using namespace stdext;
#endif

using namespace std;
typedef long long		time_d;
typedef long long       int64;
typedef unsigned char   byte;
typedef unsigned int    u_int;

enum GameWorkingStatus 
{
	NOT_CONNECTED	= 0,
	NOT_SYNC_USER	= 1,
	LOST_CONNECTION = 2,
	NORMAL			= 3
};


//性别
const int Gender_NULL = 0;
const int Gender_Boy  = 1;
const int Gender_Girl = 2;
const int Gender_ALL  = 3;

// 论剑排名
const int Min_RankLevel = 1;//能进入排名的等级
const int Toltal_RankCount = 10;//最前几名的玩家数据
const int Rank_FightNum = 5;

const int Fragment_Down_Lv = 3;
const int Fragment_Up_lv   = 3;

const int Score_Time = 600;

const int Fight_Qi = 1; // 战斗所需元气


// 平台类型，对应WEB的siteid
enum PLAT_TYPE
{
	PLAT_TYPE_MIN	= 0,
	PLAT_XIAOYOU	= 0,	//校友
	PLAT_QZONE,			//空间
	PLAT_QQ_WEIBO,		//QQ微博
	PLAT_TYPE_MAX
};

enum CASH_TYPE_DEF
{
	CASH_TYPE_DEF_DEFAULT=0,
	CASH_TYPE_DEF_ADMIN = 1,		//0:管理员加勋章
	CASH_TYPE_DEF_TASK,             // 任务
	CASH_TYPE_DEF_TASKSPECIAL,      // 任务特殊掉落
	CASH_TYPE_DEF_BLOOD,            // 血战
	CASH_TYPE_DEF_BOX,              // 宝箱
	CASH_TYPE_DEF_KEYBOX,           // 使用钥匙开宝箱
	CASH_TYPE_DEF_PACK,             // 礼包
	CASH_TYPE_DEF_LEVEL,            // 等级礼物
	CASH_TYPE_DEF_FORMAL,           // 参拜
	CASH_TYPE_DEF_LOGINGIFT,        // 登录礼包
	CASH_TYPE_DEF_LEVELGIFT,        // 升级领元宝
	CASH_TYPE_DEF_WEB,              // 充值
	CASH_TYPE_DEF_FIRST,            // 第一次充值奖励
	CASH_TYPE_DEE_SYSEMAIL,         // 系统邮件
	CASH_TYPE_DEF_NEWPLAYETASK,     // 新手引导任务
};

enum CASH_TYPE_COST
{
	CASH_TYPE_COST_DEFAULT = 0,
	CASH_TYPE_COST_INVENTORY,
	CASH_TYPE_COST_TRAINROLE,
	CASH_TYPE_COST_INVITEROLE1,
	CASH_TYPE_COST_INVITEROLE2,
	CASH_TYPE_COST_INVITEROLE3,
	CASH_TYPE_COST_TASKCLEAR,        // 任务清除
};

enum NewPlayerTaskID
{
	NewTask_TaskTimes = 0,
	NewTask_Level,
	NewTask_LevelMoney,
	NewTask_InviteRole,
	NewTask_Arrange,
	NewTask_Formal,
	NewTask_Strength,
	NewTask_UpGradeSkill,
	NewTask_RankFight,
	NewTask_FrageFight,
	NewTask_SkillCompose,
	NewTask_TimePower,
	NewTask_BloodBattle,
	NewTask_Challenge,
	NewTask_Box,
	NewTask_CheatsUpdate,
	NewTask_GetGold,
	NewTask_VipLevel,
	NewTask_Count,
};

#ifndef PI
const double PI					= 3.141592653589793;
#endif

#define MAX_USER_LEVEL			100


//解决winsock冲突
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifdef _WIN32
	#pragma warning(disable:4996)
#endif

#ifdef _WIN32
#define usleep Sleep
#endif

#endif
