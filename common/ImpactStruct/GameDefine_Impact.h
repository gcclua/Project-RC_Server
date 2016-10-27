/********************************************************************
	文件名: 	GameDefine_Impact.h
	文件路径:\Project\Server\Server\Server\Common\ImpactStruct
	创建者:		luoy
	创建时间:	2014-5-26 15:20
	功能说明：
	参数说明:
	修改记录:

*********************************************************************/
#ifndef GAMEDEFINE_IMPACT_H
#define GAMEDEFINE_IMPACT_H

#define  GODBUFF 99901 //无敌BUFF
#define  ENTERSCENEPROTECTBUFF 99902 //进入场景的无敌保护BUFF
#define  PAOSHANGPROTECTBUFF 99903 //跑商无敌保护BUFF
#define  RELIVEPROTECTBUFF 99904 // 复活保护的buff,附带有客户端的effect
#define  YINSHENFLAGBUFF_MIN 560000
#define  YINSHENFLAGBUFF_MAX 560099 // 上面两个是标记buf,,用来处理"急转步"破隐一击必然暴击
#define	 GMSTEALTHBUFF 179999
//BUFF类型
struct BUFFTYPE
{
	enum 
	{
		DEBUFF=0,//减益BUFF
		BUFF =1,//增益BUFF
	};
};
struct BUFFFADEOUTRULE //BUFF消散规则类型(符合两种及以上 累加)
{
	enum
	{
		LEAVESCENE =1, //离开场景消散
		ONDIE =2,//死亡消散
		SENDLEAVE =4,//发送者离开
		ONLOGIN =8,//登录时消散
	};
};
#endif