/********************************************************************
	�ļ���: 	GameDefine_PK.h
	�ļ�·��:	\Project\Server\Server\Server\Common\CombatStruct
	������:		luoy
	����ʱ��:	2014-5-20 17:18
	����˵����
	����˵��:
	�޸ļ�¼:

*********************************************************************/
#ifndef GAMEDEFINE_PK_H
#define GAMEDEFINE_PK_H
struct PKModel_T
{
public:
	enum 
	{
		INVAILD_MODEL =-1,
		NORMAL_MODEL,		//����ģʽ
		KILL_MODEL,			//ɱ¾ģʽ
		MAX_NUM,
	};

};
struct PK_T
{
public:
	enum 
	{
		KILL2NORMALCDTIME =600000//ɱ¾ģʽ�е���սģʽ�ĵȴ�ʱ�� 10����
	};
	enum 
	{
		MAX_PKVALUE =99,//���ɱ��ֵ
		MIN_PKVALUE =-3//��Сɱ��ֵ
	};
};
#define MAXPKDECLAREWARTIME 1800 //PK��ս���ʱ�� 30����
#define MAXPKDECLAREWARNUM	30  //ͬʱPK��ս������� 30��
#endif