/********************************************************************
	�ļ���: 	GameDefine_Impact.h
	�ļ�·��:\Project\Server\Server\Server\Common\ImpactStruct
	������:		luoy
	����ʱ��:	2014-5-26 15:20
	����˵����
	����˵��:
	�޸ļ�¼:

*********************************************************************/
#ifndef GAMEDEFINE_IMPACT_H
#define GAMEDEFINE_IMPACT_H

#define  GODBUFF 99901 //�޵�BUFF
#define  ENTERSCENEPROTECTBUFF 99902 //���볡�����޵б���BUFF
#define  PAOSHANGPROTECTBUFF 99903 //�����޵б���BUFF
#define  RELIVEPROTECTBUFF 99904 // �������buff,�����пͻ��˵�effect
#define  YINSHENFLAGBUFF_MIN 560000
#define  YINSHENFLAGBUFF_MAX 560099 // ���������Ǳ��buf,,��������"��ת��"����һ����Ȼ����
#define	 GMSTEALTHBUFF 179999
//BUFF����
struct BUFFTYPE
{
	enum 
	{
		DEBUFF=0,//����BUFF
		BUFF =1,//����BUFF
	};
};
struct BUFFFADEOUTRULE //BUFF��ɢ��������(�������ּ����� �ۼ�)
{
	enum
	{
		LEAVESCENE =1, //�뿪������ɢ
		ONDIE =2,//������ɢ
		SENDLEAVE =4,//�������뿪
		ONLOGIN =8,//��¼ʱ��ɢ
	};
};
#endif