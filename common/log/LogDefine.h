#ifndef _LOGDEFINE_H_
#define _LOGDEFINE_H_

#include "Log.h"

//////////////////////////////////////////////////////////////////////////
//ͳ����־����i


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
//���һ���µ�LogƵ������Ҫ�����������ļ�����ӹ����崦
//LogDefine.h		1��
//LogDefine.cpp		2��
//LogService.cpp	2��

//��ͨ��־
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
//ͳ����־
LOGDEF_DECL(Audit_Item);
LOGDEF_DECL(Audit_Role);
LOGDEF_DECL(Audit_CopyScene);


//CMBI��־
//�ؼ��ֶν��ͣ��ص�ע�⣩
//1.	[2050]��Ϸ��������¼��login�� һ����־
//2.	[3025]������ɫ��rolebuild�� һ����־
//3.	[3030]��ɫ��¼��rolelogin�� һ����־
//4.	[4010-4990]����������newstages�� һ����־
//5.	[9999]�ǳ���logout�� һ����־
//6.	[5050]��ֵ��recharge�� һ����־
//7.	[6010]������levelup�� һ����־
//8.	[B1010]�������һ�ã�acquire�� ������־
//9.	[B1150]�������ģ�moneycost�� ������־
//10.	[B2110]��Ʒ��ã�getitem�� ������־
//11.	[B2150]��Ʒ���ģ�removeitem�� ������־
//12.	[B3110]��������gettask�� ������־
//13.	[B3120]�������finishtask�� ������־
//14.	[B5110]��ɳɾͣ�achievement�� ������־
//15.	[B6110]������activity�� ������־
//16.	[B9990]������־��heart�� ������־
//17.	[C0100]������־(beauty) ������־
//18.	[C0101]������־(dead)  ������־
//19.	[C0102]PK������־(pkdead)  ������־
//20.	[C0103]��ҹ����̳���־(shop)  ������־
//21.	[C0104]������־(consignment)  ������־
//22.   [C0105]��������caceltask�� ������־
//23.   [C0106]��飨fellow�� ������־
//24.   [C0107]ƥ����־��match�� ������־
//25.   [C0109]vip��־��vip�� ������־
//26.	[C0108]�ؿ�ս����carbon�� ������־
//27.	[C0110]������־��business�� ������־
LOGDEF_DECL(login);
LOGDEF_DECL(rolebuild);
LOGDEF_DECL(rolelogin);
LOGDEF_DECL(newstages);
LOGDEF_DECL(logout);
//////////////////////////////////////////////////////////////////////////
//��ʼ����־ģ��
void InitLogDefineModule(tint32 nWorldID);

//////////////////////////////////////////////////////////////////////////
class Item_T;
class Obj_User;
class ItemPack_T;
class Fellow;

//�������ڸ���ϵͳ��ӡ��־ʱ �����Ҫ����ö��ֵ ��Ӧ�ü�������
//Ԥ�ȷ���ö��ֵ Ŀǰ:
//1-10000		��Ʒ���
//10001-20000	�������
//20001-30000	ͳһ������أ�ͳһ�������������Ʒ���� �������ĵȵȣ�
//30001-40000	������
//40001-45000	�ʼ����
//45001-50000	�������
//55101-55500   ����ֵ���
enum
{
	OP_UNKNOW							= 0,		//δ֪����
	//==========================��Ʒ��ز�����ʼ========================
	OP_ITEM_START						= 1,		//��Ʒ����ڴ�֮����ӣ�����


	OP_ITEM_END							= 10000,	//��Ʒ����ڴ�֮ǰ��ӣ�����
	//==========================��Ʒ��ز�������========================

	//==========================������ز�����ʼ========================
	OP_ECO_START						= 10001,	//��������ڴ�֮����ӣ�����

	OP_ECO_END							= 20000,	//��������ڴ�֮ǰ��ӣ������漰�����������ģ�Ҫע����ӵ�GetCurrencyFlow������
	//==========================������ز�������========================



	//==========================�ʼ���ز�����ʼ========================
	OP_MAIL_PLAYERSENDTEXT				= 40001,	//��ҷ����ı��ʼ�
	OP_MAIL_GMCOMMANDSENDTEXT			= 40002,	//GMָ����ı��ʼ�
	OP_MAIL_GMCOMMANDSENDTEXTWITHMONEY	= 40003,	//GMָ����ı���Ǯ�ʼ�
	OP_MAIL_GMCOMMANDSENDTEXTWITHITEM	= 40004,	//GMָ����ı���Ʒ�ʼ�
	OP_MAIL_GMCOMMANDSENDTEXTWITHBELLE	= 40005,	//GMָ����ı������ʼ�
	OP_MAIL_GMCOMMANDSENDTEXTWITHMONEYANDITEM= 40006,	//GMָ����ı���Ǯ��Ʒ�ʼ�

	OP_MAIL_END							= 44000,	//�ʼ����ڴ�֮ǰ��ӡ��������漰�����������ģ�Ҫע����ӵ�GetCurrencyFlow������

	//==========================�ʼ���ز�������========================



};


#endif
