/********************************************************************
	�ļ���: 	GameDefine_CombatAttr.h
	�ļ�·��:	\Project\Server\Server\Server\Common\CombatStruct
	������:		luoy
	����ʱ��:	2014-5-20 17:14
	����˵����
	����˵��:
	�޸ļ�¼:

*********************************************************************/
#ifndef GAMEDEFINE_COMBATATTR_H
#define GAMEDEFINE_COMBATATTR_H

// ս�������ֶ� 
struct COMBATATTR_T
{
	enum TYPE 
	{
		MAXHP =0,//����Ѫ����
		MAXXP,//ս������
		ATTACK,  //����
		DEFENCE,//����
		HIT,//����
		MOVESPEED,//�ƶ��ٶ�
		ATTACKSPEED,//�����ٶ�
		ATTACKARRANGE,// ������Χ
		TOTALMAXHP, // ���б������Ѫ
		COMBATATTR_MAXNUM
	};
};

//ͬ������
struct BaseAttrSyncDirty_T
{
	enum 
	{
		TYPE_INVALID = -1,
		CURHP,			//HP
		CURMP,			//MP
		CURXP,			//XP
		LEVEL,			//�ȼ�
		EXP,			//����
		MONEY,			//��Ǯ
		YUANBAO,		//Ԫ��
		BIND_YUANBAO,	//��Ԫ��
		ZHENQI,			//����
		COMATSTATE,		//ս��״̬
		STAMINA,		//����
		CREATETIME,		//��ɫ����ʱ��
		TYPE_MAXNUM
	};
};

//�㲥����
struct BaseAttrBroadDirty_T
{
	enum 
	{
		TYPE_INVALID = -1,
		PROFESSION,			//ְҵ
		NAME,				//����
		FORCETYPE,			//����
		MOVESPPED,			//�ƶ��ٶ�
		DIEFLAG,			//�Ƿ�����
		FACEDIR,			//����
		WEAPONDATAID,		//����ID
		WEAPONEFFECTGEM,	//������ʯ��Ч
		MODELVISUALID,		//ģ��Ԥ��ID
		STEALTHLEV,			//������
		COMBATVALUE,		//ս��
		BINDINFO,			//����Ϣ
		ATTREFFECTID,		//������ЧID
		TYPE_MAXNUM
	};
};

#define MAX_RELIVE_ENTRY_TIME (30)	//��ڸ���ʱ��
#define RELIVE_YUANBAO 5			//ԭ�ظ���Ԫ������


#define MAX_BOXITEM_LIFE_TIME 60000	//������Ʒʱ�� ��λ����
#define MAX_DORPITEM_NUM	90		//һ���������90������

//����״̬ �����������ͻ��˱���һ�� OBJ_ANIMSTATE
struct ANIMATIONSTATE_T
{
	enum 
	{
		STATE_INVAILD        = -1,
		STATE_NORMOR         = 0,	//����
		STATE_WALK           = 1,	//����
		STATE_HIT            = 2,	//�ܻ�
		STATE_ATTACKDOWN     = 3,	//����
		STATE_ATTACKFLY      = 4,	//����
		STATE_DEATH          = 5,	//����
		STATE_HITBYFEIYUN    = 6,	//�����ܻ����ܵ����Ƶ��չ���
		STATE_HITBYSHENFENG  = 7,	//�����ܻ����ܵ������չ���
		STATE_HITBYDUANQING  = 8,	//�����ܻ����ܵ�������չ���
		STATE_HITBYMENGWU    = 9,	//�����ܻ����ܵ�������չ���
		STATE_JUMP           = 10,	//��Ծ
		STATE_JUMP_END       = 11,	//��Ծ����
		STATE_FASTRUN_LEFT   = 12,	//����б���ٱ���
		STATE_FASTRUN_RIGHT  = 13,	//����б���ٱ���
		STATE_CORPSE         = 14,	//ʬ��

		STATE_KNOCKUP        = 17,	//����
		STATE_KNOCKDOWM      = 18,	//����
		STATE_ATTACKFLOATING = 19,	// ��������
	};
};

// ���ܵ����ĺ��������ͳ�������
struct SKILLDELANDGAINTYPE
{
	enum 
	{
		HPVALUE  = 101,		//Ѫֵ
		HPPER    = 102,		//Ѫ�İٷֱ�
		XPVALUE  = 301,		//ս��ֵ
		XPPER    = 302,		//ս��ٷֱ�
	};
};
#endif