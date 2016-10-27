#ifndef _GAMEDEFINE_SCENE_H_
#define _GAMEDEFINE_SCENE_H_

#include "Base.h"

//名称的字符串长度
#define MAX_NAME_SIZE	72// modify @ dlc6: 32 -> 72
typedef FLString<MAX_NAME_SIZE> CHARNAME;
//账号字符串长度
#define MAX_ACCOUNT_SIZE	80
typedef FLString<MAX_ACCOUNT_SIZE> ACCOUNTNAME;

typedef FLString<32> IPString;

//创建角色时名称长度(创建角色和角色改名时使用，其他判断都使用MAX_NAME_SIZE)
#define CREATE_MAX_NAME_SIZE	18

// 查找march的最大数量
#define  MAX_FIND_MARCH_NUM     30


//身上最的大BUFF数
#define MAX_BUFF_SIZE 80 // 原来是32 [7/15/2015 yuxiaoxi]

//到过的最大场景ID数量
#define  MAX_REACHEDSCENEID_SIZE 128
//最大追踪点数量
#define  MAXTRACEPOINTNUM 12

class SceneType
{
public:
	enum
	{
		MAIN = 0,	//主场景(大地图）
		COPY,		//副本
		MAX,
	};
};

#define JIANYU_ENTER_PKVALUE 20
#define JIANYU_PKRECOVER_CD 1		// 监狱杀气恢复CD 单位:分钟


class ObjType
{
public:
	enum
	{
		EMPTY = 0,
		MARCH,
		HERO,
		SOLDIER,
		NPC,
		SNAREOBJ,
		MAX,
	};
};

#define SCENEOBJIDMIN 1000			//场景ObjID的起始值，0-999留给客户端，用以实现纯客户端Obj
#define SCENEOBJIDMAX 2100000000	//场景ObjID的最大值

#define COPYSCENEMAXPLAYERCOUNT 100	//副本最大玩家数


#define MAX_CHAR_COMMON_DATA_NUM  (512)
#define MAX_CHAR_COMMON_FLAG_NUM (5)

//////////////////////////////////////////////////////////////////////////
//消息由场景转到玩家
#define MESSAGE_TRANSPORTTOMARCH_DECL(MSGTYPE) \
	virtual void HandleMessage(const MSGTYPE &rMsg);
#define MESSAGE_TRANSPORTTOMARCH_IMPL(MSGTYPE) \
	void Scene::HandleMessage(const MSGTYPE &rMsg) \
{ \
	Obj_MarchPtr Ptr = GetMarchByGuid(rMsg.m_ReceiverGuid); \
	if (Ptr) \
{ \
	Ptr->HandleMessage(rMsg); \
} \
}

struct FORCETYPE_T //势力
{
	enum      
	{
		TYPE_INVAILD   = -1,
		USER_NORMAL    = 0, //玩家势力
		NPC_FRIEND     = 1, //友好NPC
		NPC_NEUTRALITY = 2, //中立NPC
		NPC_ATTACK     = 3, //敌对NPC (主动攻击的)
		PvP1           = 6, //PVP 势力1
		PvP2           = 7, //PVP 势力2
		HELP_NPC       = 8, //助战NPC 帮助玩家打怪
		MAX_NUM,            //最大值最好不要超过128，如果需要超过，请通知修改数据库存储

	};
};

//关系
struct RELATIONTYPE_T
{
	enum RELATION
	{
		INVAILD_TYPE =-1,
		FRIEND,//友好
		NEUTRAL,//中立
		ENEMY,//敌对
		MAXNUM,
	};

};

struct USER_COMMONDATA //通用数据存储
{
	// User CommonData， 公共资源必须先向有关人员申请后，分配一个ID才能使用，同时在Global.lua中保持枚举一致！！！
	enum
	{
		CD_MOUNT_AUTOFLAG_ID                    = 0, // 自动坐骑ID
		CD_RELIVE_ENTRY_TIME_ID                 = 1, // 复活时间CD

		CD_MAX_NUM_DATA                         = 256, // 此为存储边界，在上面添加  有需要的与客户端同步
	};
};

struct USER_COMMONFLAG  //通用标记存储
{
	// User CommonFlag，  公共资源必须先向有关人员申请后，分配一个ID才能使用，同时在Global.lua中保持枚举一致！！！
	enum	
	{
		CF_USER_FIRST_LOGIN					    = 0,	// 第一次登陆
		CF_DAYAWARD_FLAG					    = 1,	// 每日登陆奖励领取标记

		CF_MAX_NUM_FLAG                         = 160,  // 此为存储边界，在上面添加  有需要的与客户端同步   CF_REDEEM 标签的功能均支持删档后重用
	};
};

struct  DAMAGEBOARD_TYPE
{
public:
	enum 
	{
		PLAYER_TYPE_INVALID = -1,
		PLAYER_HP_UP = 0,				//我方HP增加
		PLAYER_HP_DOWN,					//我方HP减少
		PLAYER_XP_UP,					//我方XP增加
		PLAYER_XP_DOWN,					//我方XP减少
		TARGET_HPDOWN_PLAYER,			//我方主角造成对方HP减少
		PLAYER_ATTACK_MISS,				//我方攻击时 未命中
		TARGET_ATTACK_MISS,				//对方攻击时 未命中
		SKILL_NAME,						//技能名称
		PLAYER_ATTACK_IGNORE,			//我方攻击  出伤害免疫
		TARGET_ATTACK_IGNORE,			//对方攻击  出伤害免疫
		SKILL_NAME_NPC,					//NPC技能名称
	};
	
};

struct NPC_TYPE
{
	enum
	{
		INVAILD =-1,
		GENERAL,//普通
		ELITE,//精英
		BOSS,//BOSS
	};
};

class CopyScenePlayType
{
public:
	enum
	{
		NONE = 0,
		SINGLE,
		MULTIPLE,
	};
};

//由易到难
class CopySceneDifficulty
{
public:
	//// ！！！！难度不能随便加，会影响存储！！！！
	enum
	{
		DEFAULT	= 1,
		LEVEL1	= 1,	// 普通
		LEVEL2,			// 困难
		LEVEL3,			// 地狱
		LEVEL4,			// 磨难
		LEVELMAX,		// 取不到
	};
};

class CopySceneInviteResult
{
public:
	enum
	{
		EMPTY = 0,
		WAIT,
		AGREE,
		DISAGREE,
		CONDITIONDISSATISFY,
		OVERTIME,
	};
};

class CopySceneTimesLimitedID
{
public:
	enum TLI_ID
	{
		TLI_WUJUESHENGONG = 4,	//无绝神宫
		TLI_CANGJINGGE = 5,		//天下第一楼  原藏经阁
		TLI_LIANCHENGZHAI = 6,//连城寨 
	};
};

//副本返回结果
class CopySceneResult
{
public:
	enum
	{
		RESULT_INVALID	= invalid_id,
		RESULT_LOSE	= 0,	//失败
		RESULT_WIN,			//胜利
		RESULT_DRAW,		//平局
	};
};
#define MAX_COPYSCENE_USER	6		//副本最大人数
#define MAX_COPYSCENE_REWARD 10		//奖励最大数
#define MAX_COPYSCENE_DRAW 10		//抽奖数最大数
#define MAX_COPYSCENE_DRAW_YUANBAO 10	//抽奖全部拿去扣除的元宝数
#define MAX_COPYSCENE_CANGJINGGE_SWEEP 3	//藏经阁扫荡次数
#define MAX_COPYSCENE_RESET 10				//重置次数最大值
#define MAX_COPYSCENE_MASTER_LEVEL 20		//师门奖励等级相差等级

//密码字符串长度
#define MAX_COPYSCENENAME_SIZE	256
typedef FLString<MAX_COPYSCENENAME_SIZE> COPYSCENENAME;

#define MAX_CHARACTER_LEVEL	(110)	//角色等级上限，使用GM指令可以把玩家最高调整到这个值

#define MAX_COPYSCENE_NUMBER	(16)	//副本个数

//玩家冷却锁
enum USER_BITLOCKTYPE
{
	USER_BITLOCK_INVALID = -1,			//无效值
	USER_BITLOCK_COMMON = 0,			//公共
	USER_BITLOCK_CONSIGNSALE_BUY,		//寄售行购买操作

	//加在这个之前
	USER_BITLOCK_NUM
};

#define TICK_VIEW_TICK_INTERVAL 300 // 300ms

///////////////////////////////////////////////////////

//公告类型
struct ActivityNotice
{
public:
	enum
	{
		NOTICE_TYPE_SYS = 1,
		NOTICE_TYPE_ROLL = 2,
	};

	enum
	{
		TIMETYPE_ONCE = 1,
		TIMETYPE_DAY = 2,
		TIMETYPE_WEEK = 3,
		TIMETYPE_MONTH = 4,
	};
};
//////////////////////////////////////////////////////////////////////////	

struct USER_GENDER
{
	enum
	{
		INVAILD =-1,
		MALE	= 0,//男
		FEMALE	= 1,//女
	};
};



//合服标志
enum ServerMergeStatus
{
	MERGE_STATUS_INVALID = 0,	//正常状态
	MERGE_STATUS_BEFORE,		//合服之前
	MERGE_STATUS_AFTER,			//合服之后
};

//CopyeSceneNumber
class COPYSCENENUMBER_T
{
public:
	enum
	{
		EXTRANUMBER_ITEM = 0,	//使用物品加的副本而外次数。
		EXTRANUMBER_1,
		EXTRANUMBER_2,
		EXTRANUMBER_3,
		EXTRANUMBER_4,
		EXTRANUMBER_5,
		EXTRANUMBER_6,
		EXTRANUMBER_7,
		EXTRANUMBER_MAX	,		//大小
	};

};

#endif  //_GAMEDEFINE_SCENE_H_
