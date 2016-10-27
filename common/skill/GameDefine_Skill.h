/********************************************************************
	文件名: 	GameDefine_Skill.h
	文件路径:	\Project\Server\Server\Server\Common\SkillStruct
	创建者:		luoy
	创建时间:	2014-5-26 15:17
	功能说明：
	参数说明:
	修改记录:

*********************************************************************/
#ifndef GAMEDEFINE_SKILL_H
#define GAMEDEFINE_SKILL_H
struct TAEGETSEL_T
{
public:
	enum 
	{
		LOGIC_INVALID	= -1,
		SINGLE, //单个目标
		AROUNDSELF,//周围目标
		SELF,//自身
	};

};

//每一个int位表示一种类型 类型相加的和表示相加的类型都包括

struct TAEGETTYPE_T
{
public:
	enum 
	{
		TYPE_INVALID	= 0,
		SELF =1, //自身 
		TEAMMEM =2,//队友 
		ENEMY =4,//敌人(敌对和中立) 
		FRIND =8,//友方
		OWNER =16,//主人(夥伴專用)
	};

};

struct SKILLFINISH_T
{
public:
	enum 
	{
		BREAK =1,
		FINISH =2,
	};

};

struct SKILLUSETYPE_T
{
public:
	enum 
	{
		SHUNFA =0, //瞬发
		YINGCHANG =1,//吟唱
	};

};
//每个int位表示一种类型 符合两种及以上累加
struct SKILLCLASS
{
public:
	enum
	{
		INITIATIVE=1,//主动技
		PASSIVITY=2,//被动技
		AUTOREPEAT=4,//自动连续技
		XP=8,//XP技
		CHONGFENG=16,//冲锋技
	};
};
//技能使用失败的原因
struct SKILLFAILTYPE
{
public:
	enum 
	{
		INVALID =-1,
		DISTANCE =0,//距离不够
	};
};

#define  MAXOWNSKILL 15
#define  SKILLPUBLICCD 40
#define	 YTWJBASEID 307 //以退为进BaseID
#define  MINXPSKILLSTUDYLEV 16 //XP 学习等级


#endif
