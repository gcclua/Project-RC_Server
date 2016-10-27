/********************************************************************
	文件名: 	GameDefine_PK.h
	文件路径:	\Project\Server\Server\Server\Common\CombatStruct
	创建者:		luoy
	创建时间:	2014-5-20 17:18
	功能说明：
	参数说明:
	修改记录:

*********************************************************************/
#ifndef GAMEDEFINE_PK_H
#define GAMEDEFINE_PK_H
struct PKModel_T
{
public:
	enum 
	{
		INVAILD_MODEL =-1,
		NORMAL_MODEL,		//休闲模式
		KILL_MODEL,			//杀戮模式
		MAX_NUM,
	};

};
struct PK_T
{
public:
	enum 
	{
		KILL2NORMALCDTIME =600000//杀戮模式切到休战模式的等待时间 10分钟
	};
	enum 
	{
		MAX_PKVALUE =99,//最大杀气值
		MIN_PKVALUE =-3//最小杀气值
	};
};
#define MAXPKDECLAREWARTIME 1800 //PK宣战最大时间 30分钟
#define MAXPKDECLAREWARNUM	30  //同时PK宣战最大人数 30人
#endif