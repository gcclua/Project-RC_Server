#ifndef _MESSAGEDEF_H_
#define _MESSAGEDEF_H_
#pragma once
//���ļ�Ϊʹ�ù����Զ����ɣ��벻Ҫ���ļ����޸ģ�����Ҫ�޸ģ�����sskylin��ϵ��
enum S2C_EVENT
{
	S2C_EVENT_BASE = 511,
};
enum C2S_EVENT
{
	C2S_EVENT_BASE = 1023,
	C2S_RceAddArmy,		//^c^RceAddArmy#
};
#endif

