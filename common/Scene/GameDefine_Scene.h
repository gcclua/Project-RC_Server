#ifndef _GAMEDEFINE_SCENE_H_
#define _GAMEDEFINE_SCENE_H_

#include "Base.h"

//���Ƶ��ַ�������
#define MAX_NAME_SIZE	72// modify @ dlc6: 32 -> 72
typedef FLString<MAX_NAME_SIZE> CHARNAME;
//�˺��ַ�������
#define MAX_ACCOUNT_SIZE	80
typedef FLString<MAX_ACCOUNT_SIZE> ACCOUNTNAME;

typedef FLString<32> IPString;

//������ɫʱ���Ƴ���(������ɫ�ͽ�ɫ����ʱʹ�ã������ж϶�ʹ��MAX_NAME_SIZE)
#define CREATE_MAX_NAME_SIZE	18

// ����march���������
#define  MAX_FIND_MARCH_NUM     30


//������Ĵ�BUFF��
#define MAX_BUFF_SIZE 80 // ԭ����32 [7/15/2015 yuxiaoxi]

//��������󳡾�ID����
#define  MAX_REACHEDSCENEID_SIZE 128
//���׷�ٵ�����
#define  MAXTRACEPOINTNUM 12

class SceneType
{
public:
	enum
	{
		MAIN = 0,	//������(���ͼ��
		COPY,		//����
		MAX,
	};
};

#define JIANYU_ENTER_PKVALUE 20
#define JIANYU_PKRECOVER_CD 1		// ����ɱ���ָ�CD ��λ:����


class ObjType
{
public:
	enum
	{
		EMPTY = 0,
		MARCH,
		HERO,
		TROOP,
		NPC,
		SNAREOBJ,
		MAX,
	};
};

#define SCENEOBJIDMIN 1000			//����ObjID����ʼֵ��0-999�����ͻ��ˣ�����ʵ�ִ��ͻ���Obj
#define SCENEOBJIDMAX 2100000000	//����ObjID�����ֵ

#define COPYSCENEMAXPLAYERCOUNT 100	//���������Obj��

#define COPYWAITLINETIME 30 // �ȴ�����ʱ��


#define MAX_CHAR_COMMON_DATA_NUM  (512)
#define MAX_CHAR_COMMON_FLAG_NUM (5)

//////////////////////////////////////////////////////////////////////////
//��Ϣ�ɳ���ת�������ڶ���
#define MESSAGE_TRANSPORTTOMARCH_DECL(MSGTYPE) \
	virtual void HandleMessage(const MSGTYPE &rMsg);
#define MESSAGE_TRANSPORTTOMARCH_IMPL(MSGTYPE) \
	void Scene::HandleMessage(const MSGTYPE &rMsg) \
{ \
	Obj_MarchPtr Ptr = GetMarchByID(rMsg.m_nReceiveObjId); \
	if (Ptr && Ptr->GetPlayerId()>0 && Ptr->GetPlayerId()==rMsg.m_ReceiverGuid) \
{ \
	Ptr->HandleMessage(rMsg); \
} \
}

struct FORCETYPE_T //����
{
	enum      
	{
		TYPE_INVAILD   = -1,
		NPC_ATTACK     = 1, //������
		NPC_DEFENCE = 2, //���ط�
		MAX_NUM,            //���ֵ��ò�Ҫ����128�������Ҫ��������֪ͨ�޸����ݿ�洢

	};
};

//��ϵ
struct RELATIONTYPE_T
{
	enum RELATION
	{
		INVAILD_TYPE =-1,
		FRIEND,//�Ѻ�
		NEUTRAL,//����
		ENEMY,//�ж�
		MAXNUM,
	};

};

struct USER_COMMONDATA //ͨ�����ݴ洢
{
	// User CommonData�� ������Դ���������й���Ա����󣬷���һ��ID����ʹ�ã�ͬʱ��Global.lua�б���ö��һ�£�����
	enum
	{
		CD_MOUNT_AUTOFLAG_ID                    = 0, // �Զ�����ID
		CD_RELIVE_ENTRY_TIME_ID                 = 1, // ����ʱ��CD

		CD_MAX_NUM_DATA                         = 256, // ��Ϊ�洢�߽磬���������  ����Ҫ����ͻ���ͬ��
	};
};

struct USER_COMMONFLAG  //ͨ�ñ�Ǵ洢
{
	// User CommonFlag��  ������Դ���������й���Ա����󣬷���һ��ID����ʹ�ã�ͬʱ��Global.lua�б���ö��һ�£�����
	enum	
	{
		CF_USER_FIRST_LOGIN					    = 0,	// ��һ�ε�½
		CF_DAYAWARD_FLAG					    = 1,	// ÿ�յ�½������ȡ���

		CF_MAX_NUM_FLAG                         = 160,  // ��Ϊ�洢�߽磬���������  ����Ҫ����ͻ���ͬ��   CF_REDEEM ��ǩ�Ĺ��ܾ�֧��ɾ��������
	};
};

struct  DAMAGEBOARD_TYPE
{
public:
	enum 
	{
		PLAYER_TYPE_INVALID = -1,
		PLAYER_HP_UP = 0,				//�ҷ�HP����
		PLAYER_HP_DOWN,					//�ҷ�HP����
		PLAYER_XP_UP,					//�ҷ�XP����
		PLAYER_XP_DOWN,					//�ҷ�XP����
		TARGET_HPDOWN_PLAYER,			//�ҷ�������ɶԷ�HP����
		PLAYER_ATTACK_MISS,				//�ҷ�����ʱ δ����
		TARGET_ATTACK_MISS,				//�Է�����ʱ δ����
		SKILL_NAME,						//��������
		PLAYER_ATTACK_IGNORE,			//�ҷ�����  ���˺�����
		TARGET_ATTACK_IGNORE,			//�Է�����  ���˺�����
		SKILL_NAME_NPC,					//NPC��������
	};
	
};

class CopyScenePlayType
{
public:
	enum
	{
		NONE = 0,
		SINGLE,
		MULTIPLE,
	};
};

//���׵���
class CopySceneDifficulty
{
public:
	//// ���������ѶȲ������ӣ���Ӱ��洢��������
	enum
	{
		DEFAULT	= 1,
		LEVEL1	= 1,	// ��ͨ
		LEVEL2,			// ����
		LEVEL3,			// ����
		LEVEL4,			// ĥ��
		LEVELMAX,		// ȡ����
	};
};

class CopySceneInviteResult
{
public:
	enum
	{
		EMPTY = 0,
		WAIT,
		AGREE,
		DISAGREE,
		CONDITIONDISSATISFY,
		OVERTIME,
	};
};

class CopySceneTimesLimitedID
{
public:
	enum TLI_ID
	{
		TLI_WUJUESHENGONG = 4,	//�޾���
		TLI_CANGJINGGE = 5,		//���µ�һ¥  ԭ�ؾ���
		TLI_LIANCHENGZHAI = 6,//����կ 
	};
};

//�������ؽ��
class CopySceneResult
{
public:
	enum
	{
		RESULT_INVALID	= invalid_id,
		RESULT_LOSE	= 0,	//ʧ��
		RESULT_WIN,			//ʤ��
		RESULT_DRAW,		//ƽ��
	};
};

//�����ַ�������
#define MAX_COPYSCENENAME_SIZE	256
typedef FLString<MAX_COPYSCENENAME_SIZE> COPYSCENENAME;

#define MAX_CHARACTER_LEVEL	(110)	//��ɫ�ȼ����ޣ�ʹ��GMָ����԰������ߵ��������ֵ

#define MAX_COPYSCENE_NUMBER	(16)	//��������

//�����ȴ��
enum USER_BITLOCKTYPE
{
	USER_BITLOCK_INVALID = -1,			//��Чֵ
	USER_BITLOCK_COMMON = 0,			//����
	USER_BITLOCK_CHANGESCENE,			//�л�����CD
	USER_BITLOCK_COPYSCENE_OPEN,		//���븱���Ӹ���

	//�������֮ǰ
	USER_BITLOCK_NUM
};

#define TICK_VIEW_TICK_INTERVAL 300 // 300ms
#define MAX_ARRANGE_COUNT        11 // ��������λ��
#define MAX_ATTACK_SET           3  // ���Ĺ�������

///////////////////////////////////////////////////////

//��������
struct ActivityNotice
{
public:
	enum
	{
		NOTICE_TYPE_SYS = 1,
		NOTICE_TYPE_ROLL = 2,
	};

	enum
	{
		TIMETYPE_ONCE = 1,
		TIMETYPE_DAY = 2,
		TIMETYPE_WEEK = 3,
		TIMETYPE_MONTH = 4,
	};
};
//////////////////////////////////////////////////////////////////////////	



#endif  //_GAMEDEFINE_SCENE_H_
