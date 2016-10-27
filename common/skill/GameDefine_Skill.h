/********************************************************************
	�ļ���: 	GameDefine_Skill.h
	�ļ�·��:	\Project\Server\Server\Server\Common\SkillStruct
	������:		luoy
	����ʱ��:	2014-5-26 15:17
	����˵����
	����˵��:
	�޸ļ�¼:

*********************************************************************/
#ifndef GAMEDEFINE_SKILL_H
#define GAMEDEFINE_SKILL_H
struct TAEGETSEL_T
{
public:
	enum 
	{
		LOGIC_INVALID	= -1,
		SINGLE, //����Ŀ��
		AROUNDSELF,//��ΧĿ��
		SELF,//����
	};

};

//ÿһ��intλ��ʾһ������ ������ӵĺͱ�ʾ��ӵ����Ͷ�����

struct TAEGETTYPE_T
{
public:
	enum 
	{
		TYPE_INVALID	= 0,
		SELF =1, //���� 
		TEAMMEM =2,//���� 
		ENEMY =4,//����(�жԺ�����) 
		FRIND =8,//�ѷ�
		OWNER =16,//����(ⷰ錣��)
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
		SHUNFA =0, //˲��
		YINGCHANG =1,//����
	};

};
//ÿ��intλ��ʾһ������ �������ּ������ۼ�
struct SKILLCLASS
{
public:
	enum
	{
		INITIATIVE=1,//������
		PASSIVITY=2,//������
		AUTOREPEAT=4,//�Զ�������
		XP=8,//XP��
		CHONGFENG=16,//��漼
	};
};
//����ʹ��ʧ�ܵ�ԭ��
struct SKILLFAILTYPE
{
public:
	enum 
	{
		INVALID =-1,
		DISTANCE =0,//���벻��
	};
};

#define  MAXOWNSKILL 15
#define  SKILLPUBLICCD 40
#define	 YTWJBASEID 307 //����Ϊ��BaseID
#define  MINXPSKILLSTUDYLEV 16 //XP ѧϰ�ȼ�


#endif
