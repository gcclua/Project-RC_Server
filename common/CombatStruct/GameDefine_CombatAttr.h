/********************************************************************
	文件名: 	GameDefine_CombatAttr.h
	文件路径:	\Project\Server\Server\Server\Common\CombatStruct
	创建者:		luoy
	创建时间:	2014-5-20 17:14
	功能说明：
	参数说明:
	修改记录:

*********************************************************************/
#ifndef GAMEDEFINE_COMBATATTR_H
#define GAMEDEFINE_COMBATATTR_H

// 战斗属性字段 
struct COMBATATTR_T
{
	enum TYPE 
	{
		MAXHP =0,//单兵血上限
		MAXXP,//战意上限
		ATTACK,  //攻击
		DEFENCE,//防御
		HIT,//命中
		MOVESPEED,//移动速度
		ATTACKSPEED,//攻击速度
		ATTACKARRANGE,// 攻击范围
		TOTALMAXHP, // 所有兵的最大血
		COMBATATTR_MAXNUM
	};
};

//同步脏标记
struct BaseAttrSyncDirty_T
{
	enum 
	{
		TYPE_INVALID = -1,
		CURHP,			//HP
		CURMP,			//MP
		CURXP,			//XP
		LEVEL,			//等级
		EXP,			//经验
		MONEY,			//金钱
		YUANBAO,		//元宝
		BIND_YUANBAO,	//绑定元宝
		ZHENQI,			//真气
		COMATSTATE,		//战斗状态
		STAMINA,		//体能
		CREATETIME,		//角色创建时间
		TYPE_MAXNUM
	};
};

//广播脏标记
struct BaseAttrBroadDirty_T
{
	enum 
	{
		TYPE_INVALID = -1,
		PROFESSION,			//职业
		NAME,				//名字
		FORCETYPE,			//势力
		MOVESPPED,			//移动速度
		DIEFLAG,			//是否死亡
		FACEDIR,			//朝向
		WEAPONDATAID,		//武器ID
		WEAPONEFFECTGEM,	//武器宝石特效
		MODELVISUALID,		//模型预览ID
		STEALTHLEV,			//隐身级别
		COMBATVALUE,		//战力
		BINDINFO,			//绑定信息
		ATTREFFECTID,		//属性特效ID
		TYPE_MAXNUM
	};
};

#define MAX_RELIVE_ENTRY_TIME (30)	//入口复活时间
#define RELIVE_YUANBAO 5			//原地复活元宝数量


#define MAX_BOXITEM_LIFE_TIME 60000	//掉落物品时间 单位毫秒
#define MAX_DORPITEM_NUM	90		//一次最多生成90个道具

//动画状态 ！！！！跟客户端保持一致 OBJ_ANIMSTATE
struct ANIMATIONSTATE_T
{
	enum 
	{
		STATE_INVAILD        = -1,
		STATE_NORMOR         = 0,	//待机
		STATE_WALK           = 1,	//行走
		STATE_HIT            = 2,	//受击
		STATE_ATTACKDOWN     = 3,	//击倒
		STATE_ATTACKFLY      = 4,	//击飞
		STATE_DEATH          = 5,	//死亡
		STATE_HITBYFEIYUN    = 6,	//怪物受击（受到飞云的普攻）
		STATE_HITBYSHENFENG  = 7,	//怪物受击（受到神风的普攻）
		STATE_HITBYDUANQING  = 8,	//怪物受击（受到断情的普攻）
		STATE_HITBYMENGWU    = 9,	//怪物受击（受到梦舞的普攻）
		STATE_JUMP           = 10,	//跳跃
		STATE_JUMP_END       = 11,	//跳跃结束
		STATE_FASTRUN_LEFT   = 12,	//左倾斜快速奔跑
		STATE_FASTRUN_RIGHT  = 13,	//右倾斜快速奔跑
		STATE_CORPSE         = 14,	//尸体

		STATE_KNOCKUP        = 17,	//上挑
		STATE_KNOCKDOWM      = 18,	//下砸
		STATE_ATTACKFLOATING = 19,	// 被击浮空
	};
};

// 技能的消耗和收益类型常量定义
struct SKILLDELANDGAINTYPE
{
	enum 
	{
		HPVALUE  = 101,		//血值
		HPPER    = 102,		//血的百分比
		XPVALUE  = 301,		//战意值
		XPPER    = 302,		//战意百分比
	};
};
#endif