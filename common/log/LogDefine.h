#ifndef _LOGDEFINE_H_
#define _LOGDEFINE_H_

#include "Log.h"

//////////////////////////////////////////////////////////////////////////
//统计日志工具i


template<typename _LogSink>
inline void AuditLog(_LogSink &rLogSink, const tchar* szAuditIdentification, const int64 &rGuid,int nWorldId, const tchar* szLog)
{
	tchar szBuff[4096] = {0};
	StringParser log(szBuff, sizeof(szBuff), "%s  \1 %d \1 %08X \1 %s");
	log.Format(szAuditIdentification, nWorldId,rGuid,szLog);
	szBuff[sizeof(szBuff) - 1] = '\0';
	rLogSink.Log(szBuff, false);
}

#define DEF_AUDITLOG(X) \
	template<typename _LogSink, ParserRepeatArg1_##X(typename P)> \
	inline void AuditLog(_LogSink &rLogSink, const tchar* szAuditIdentification, const int64 &rGuid,int nWorldId, const tchar* szLog, ParserRepeatArg2_##X(P,p)) \
{ \
	tchar szFmt[4096] = {0}; \
	tsnprintf(szFmt, sizeof(szFmt), "%%s \1  %%d \1 %%08X \1 %s", szLog); \
	szFmt[sizeof(szFmt) - 1] = '\0'; \
	tchar szBuff[4096] = {0}; \
	StringParser log(szBuff, sizeof(szBuff), szFmt); \
	log.Format(szAuditIdentification,nWorldId,rGuid,ParserRepeatArg1_##X(p)); \
	szBuff[sizeof(szBuff) - 1] = '\0'; \
	rLogSink.Log(szBuff, false); \
}

DEF_AUDITLOG(1);
DEF_AUDITLOG(2);
DEF_AUDITLOG(3);
DEF_AUDITLOG(4);
DEF_AUDITLOG(5);
DEF_AUDITLOG(6);
DEF_AUDITLOG(7);
DEF_AUDITLOG(8);
DEF_AUDITLOG(9);
DEF_AUDITLOG(10);
DEF_AUDITLOG(11);
DEF_AUDITLOG(12);
DEF_AUDITLOG(13);
DEF_AUDITLOG(14);
DEF_AUDITLOG(15);
DEF_AUDITLOG(16);
DEF_AUDITLOG(17);
DEF_AUDITLOG(18);
DEF_AUDITLOG(19);
DEF_AUDITLOG(20);
DEF_AUDITLOG(21);
DEF_AUDITLOG(22);
DEF_AUDITLOG(23);
DEF_AUDITLOG(24);
DEF_AUDITLOG(25);
DEF_AUDITLOG(26);
DEF_AUDITLOG(27);
DEF_AUDITLOG(28);
DEF_AUDITLOG(29);
DEF_AUDITLOG(30);
DEF_AUDITLOG(31);
DEF_AUDITLOG(32);
DEF_AUDITLOG(33);
DEF_AUDITLOG(34);
DEF_AUDITLOG(35);
DEF_AUDITLOG(36);
DEF_AUDITLOG(37);
DEF_AUDITLOG(38);
DEF_AUDITLOG(39);
DEF_AUDITLOG(40);
DEF_AUDITLOG(41);
DEF_AUDITLOG(42);
DEF_AUDITLOG(43);
DEF_AUDITLOG(44);
DEF_AUDITLOG(45);

//////////////////////////////////////////////////////////////////////////
//添加一个新的Log频道，需要在下面三个文件中添加共计五处
//LogDefine.h		1处
//LogDefine.cpp		2处
//LogService.cpp	2处

//普通日志
LOGDEF_DECL(Login);
LOGDEF_DECL(Warning);
LOGDEF_DECL(Error);
LOGDEF_DECL(DBAgentError);
LOGDEF_DECL(DBAgent);
LOGDEF_DECL(SystemShop);
LOGDEF_DECL(TitleInvestitive);
LOGDEF_DECL(Lua);
LOGDEF_DECL(UserConsume);
LOGDEF_DECL(Mission);
LOGDEF_DECL(Chat);
LOGDEF_DECL(GMCommand);
LOGDEF_DECL(Fellow);
LOGDEF_DECL(Pool);
LOGDEF_DECL(Packet);
LOGDEF_DECL(Scene);
LOGDEF_DECL(Player);
LOGDEF_DECL(CopyScene);
LOGDEF_DECL(Efficiency);

LOGDEF_DECL(Guid);
//统计日志
LOGDEF_DECL(Audit_Item);
LOGDEF_DECL(Audit_Role);
LOGDEF_DECL(Audit_CopyScene);


//CMBI日志
//关键字段解释（重点注意）
//1.	[2050]游戏服务器登录（login） 一级日志
//2.	[3025]创建角色（rolebuild） 一级日志
//3.	[3030]角色登录（rolelogin） 一级日志
//4.	[4010-4990]新手引导（newstages） 一级日志
//5.	[9999]登出（logout） 一级日志
//6.	[5050]充值（recharge） 一级日志
//7.	[6010]升级（levelup） 一级日志
//8.	[B1010]经验或货币获得（acquire） 二级日志
//9.	[B1150]货币消耗（moneycost） 二级日志
//10.	[B2110]物品获得（getitem） 二级日志
//11.	[B2150]物品消耗（removeitem） 二级日志
//12.	[B3110]接受任务（gettask） 二级日志
//13.	[B3120]完成任务（finishtask） 二级日志
//14.	[B5110]完成成就（achievement） 二级日志
//15.	[B6110]参与活动（activity） 二级日志
//16.	[B9990]心跳日志（heart） 二级日志
//17.	[C0100]美人日志(beauty) 三级日志
//18.	[C0101]死亡日志(dead)  三级日志
//19.	[C0102]PK死亡日志(pkdead)  三级日志
//20.	[C0103]玩家购买商城日志(shop)  三级日志
//21.	[C0104]寄售日志(consignment)  三级日志
//22.   [C0105]放弃任务（caceltask） 三级日志
//23.   [C0106]伙伴（fellow） 三级日志
//24.   [C0107]匹配日志（match） 三级日志
//25.   [C0109]vip日志（vip） 三级日志
//26.	[C0108]关卡战斗（carbon） 三级日志
//27.	[C0110]跑商日志（business） 三级日志
LOGDEF_DECL(login);
LOGDEF_DECL(rolebuild);
LOGDEF_DECL(rolelogin);
LOGDEF_DECL(newstages);
LOGDEF_DECL(logout);
//////////////////////////////////////////////////////////////////////////
//初始化日志模块
void InitLogDefineModule(tint32 nWorldID);

//////////////////////////////////////////////////////////////////////////
class Item_T;
class Obj_User;
class ItemPack_T;
class Fellow;

//服务器内各个系统打印日志时 如果需要操作枚举值 都应该加在下面
//预先分配枚举值 目前:
//1-10000		物品相关
//10001-20000	经济相关
//20001-30000	统一消耗相关（统一消耗里面包括物品消耗 经济消耗等等）
//30001-40000	伙伴相关
//40001-45000	邮件相关
//45001-50000	经验相关
//55101-55500   精力值相关
enum
{
	OP_UNKNOW							= 0,		//未知操作
	//==========================物品相关操作开始========================
	OP_ITEM_START						= 1,		//物品相关在此之后添加！！！


	OP_ITEM_END							= 10000,	//物品相关在此之前添加！！！
	//==========================物品相关操作结束========================

	//==========================经济相关操作开始========================
	OP_ECO_START						= 10001,	//经济相关在此之后添加！！！

	OP_ECO_END							= 20000,	//经济相关在此之前添加！！！涉及到货币流动的，要注意添加到GetCurrencyFlow！！！
	//==========================经济相关操作结束========================



	//==========================邮件相关操作开始========================
	OP_MAIL_PLAYERSENDTEXT				= 40001,	//玩家发送文本邮件
	OP_MAIL_GMCOMMANDSENDTEXT			= 40002,	//GM指令发送文本邮件
	OP_MAIL_GMCOMMANDSENDTEXTWITHMONEY	= 40003,	//GM指令发送文本金钱邮件
	OP_MAIL_GMCOMMANDSENDTEXTWITHITEM	= 40004,	//GM指令发送文本物品邮件
	OP_MAIL_GMCOMMANDSENDTEXTWITHBELLE	= 40005,	//GM指令发送文本美人邮件
	OP_MAIL_GMCOMMANDSENDTEXTWITHMONEYANDITEM= 40006,	//GM指令发送文本金钱物品邮件

	OP_MAIL_END							= 44000,	//邮件请在此之前添加。！！！涉及到货币流动的，要注意添加到GetCurrencyFlow！！！

	//==========================邮件相关操作结束========================



};


#endif
