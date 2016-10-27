#ifndef _ERROR_DEF_H_
#define _ERROR_DEF_H_


enum    ERROR_CODE
{
	CARDERR_SUCCESS						=		0,

	CARDERR_SYSTEM                      =     100,  //ϵͳ
	CARDERR_MODULE_MISS                 =     101,  //ģ�鶪ʧ
	CARDERR_ALLOC_FAIL                  =     102,  //�ڴ��������ʧ��
	CARDERR_SYSTEM_UNKOWN               =     103,  //δ֪ϵͳ����
	CARDERR_PROTO_NULL					=	  104,	//proto�ļ�Ϊ��

	CARDERR_COMMON                      =    1000,  //ͨ��
	CARDERR_CONFIG_MISS                 =    1001,  //δ�ҵ�����
	CARDERR_CONFIG_ERROR                =    1002,  //��������
	CARDERR_WRONG_PARAM                 =    1003,  //��������
	CARDERR_NOTENOUGH_GOLD				=    1004,  //��Ҳ���
	CARDERR_NOTENOUGH_CASH				=    1005,  //Ԫ������
	CARDERR_NOTENOUGH_ENERGY			=    1006,  //��������
	CARDERR_NOTENOUGH_QI				=    1007,  //������
	CARDERR_NAME_CANTEMPT				=    1008,  //���ֲ���Ϊ��
	CARDERR_NAME_EXIT					=    1009,  //�����Ѵ���
	CARDERR_LESS_LEVEL					=    1010,  //�ȼ�����
	CARDERR_NAME_BAD                    =    1011,  // ������
	CARDERR_LESS_VIP					=	 1012,  //vip�ȼ�����
	

	CARDERR_ROLE_NOTFIND                =    2000,  //û���ҵ���
	CARDERR_ROLE_NOTTRAINDATA           =    2001,  //û����������
	CARDERR_ROLE_NOTEXP			        =    2002,  //û�о���
	CARDERR_ROLE_NOTSOUL		        =    2003,  //û���㹻��
	CARDERR_ROLE_HAVEROLE		        =    2004,  //�Ѿ�ӵ��
	CARDERR_ROLE_NOTTIME		        =    2005,  //ʱ��δ��
	CARDERR_ROLE_NOTFINDSOUL	        =    2006,  //û���ҵ���
	CARDERR_ROLE_ROLEARRANGE	        =    2007,  //��������
	CARDERR_ROLE_ROLECARDPOS	        =    2008,  //�����ܿ�λ��
	CARDERR_ROLE_QIANLIERROR	        =    2009,  //Ǳ������
	CARDERR_ROLE_MAXARRANGECNT	        =    2010,  //�ѵ����������
	CARDERR_ROLE_ARRANGENOTON	        =    2011,  //��λ�ò���������
	CARDERR_ROLE_MAXCOUNTINVITE	        =    2012,  //�ﵽÿ�������ļ��

	CARDERR_CARD_NOTFIND		        =    3001,  //û�п�
	CARDERR_CARD_SKILLNOTSELL	        =    3002,  //���ܲ�����
	CARDERR_CARD_NOTFEEDCARD	        =    3003,  //û�����Ŀ�
	CARDERR_CARD_NOTSKILLCARD	        =    3004,  //�Ǽ��ܿ�
	CARDERR_CARD_SAMEASMAIN				=    3005,  //��Ҫ����Ŀ�
	CARDERR_CARD_SAMECARD				=    3006,  //ͬ���Ϳ�
	CARDERR_CARD_MAXEQUIPLEVEL			=    3007,  //�ѵ����ǿ���ȼ�
	CARDERR_CARD_ARRANGEPOSERR			=    3008,  //װ��λ�ô���

	CARDERR_TASK_TASKMAXCOUNT	        =    4001,  //�ﵽ���������
	CARDERR_TASK_HADGROUPREWARD	        =    4002,  //����ȡ�齱��
	CARDERR_TASK_NOTCOMPELETE	        =    4003,  //δ�������
	CARDERR_TASK_NOTUNLOCK		        =    4004,  //δ��������
	CARDERR_TASK_LOWSTART		        =    4005,  //�����Ǽ�����
	CARDERR_TASK_NOARRANGE		        =    4006,  //û�н�����
	CARDERR_TASK_HASCOUNT		        =    4006,  //������ս����

	CARDERR_INVENTORY_NEED_KEY			=	 5001,  //��ҪԿ��
	CARDERR_INVENTORY_KEY_COUNT			=	 5002,  //Կ����������
	CARDERR_INVENTORY_NOTFOUND			=	 5003,  //δ�ҵ�������Ʒ
	CARDERR_INVENTORY_NOTUSE			=	 5004,  //��Ʒ����ʹ��
	CARDERR_INVENTORY_NOTENOUGH			=	 5005,  //��Ʒ��Ŀ����
	CARDERR_INVENTORY_NOTBOX			=	 5006,  //δ�ҵ�����
	CARDERR_INVENTORY_MAXBUYCOUNT		=	 5007,  //�Ѵﵽ���������
	CARDERR_INVENTORY_VIPNOTUSE			=	 5008,  //vip��Ʒ�ѵ�������


	CARDERR_FORMAL_FLAG                 =    5010,  // �Ѿ��ΰݹ�

	CARDERR_LEVELGIFT_FLAG              =    5015,  // �ȼ�����Ѿ���ȡ
	CARDERR_LEVELGIFT_LOWLEVEL          =    5016,  // �ȼ�̫��
	CARDERR_TIMEPOWER_FLAG              =    5019,  // �Ѿ����
	CARDERR_TIMEPOWER_TIME              =    5020,  // ���ڻ�ڼ���

	CARDERR_FRAGCOMPOSE_NOFRAG          =    5021,  // ��Ƭ�ϳɣ�ȱ�ٲ�Ƭ
	CARDERR_FRAGFIGHT_NOFRAGMENT        =    5022,  // ��Ƭ�����û�ж�Ӧ��Ƭ
	CARDERR_FRAGFIGHT_FAIL              =    5023,  // ��Ƭ����ʧ��

	CARDERR_RANKFIGHT_SELFNORANK        =    5024,   // �۽���ս���Լ���������
	CARDERR_RANKFIGHT_OTHERNORANK       =    5025,   // �۽���ս���Է���������
	CARDERR_RANKFIGHT_RANKMIN           =    5026,   // �۽���ս���Լ��������ڶԷ�����
	CARDERR_RANKFIGHT_SUCESS            =    5027,   // �۽���ս�ɹ�
	CARDERR_RANKFIGHT_FAIL              =    5028,   // �Է���������������
	CARDERR_RANKMAXCOUNT                =    5029,   // ��ս��������

	CARDERR_SCOREBUY_NOSCORE            =    5030,   // ���ֲ���
	CARDERR_SCOREBUY_RANK               =    5031,   // û������������
	CARDERR_SCOREBUY_LEVEL              =    5032,   // �ȼ���������
	CARDERR_SCOREBUY_COUNT              =    5033,   // �����������
	CARDERR_RANKFIGHT_QI                =    5034,   // ��սʱԪ������
	CARDERR_RANK_USEITEM                =    5035,   // ����ʹ�����ž�
	CARDERR_FRIEND_COUNT                =    5036,   // ���Ѵ����Ѿ����
	CARDERR_FRIEND_ISFIREND             =    5037,   // �Ѿ��Ǻ���
	CARDERR_FRIEND_ATTENCOUNT           =    5038,   // ��ע�����Ѿ����
	CARDERR_FRIEND_ISATTEN              =    5039,   // �Ѿ��ڹ�ע�б�


	CARDERR_CHEATS_NOTFOUND				=	 6001,  //δ�ҵ��ز�

	CARDERR_CHAT_NOTITEM				=	 7001,  //δ�ҵ�ǧ�ﴫ��

	CARDERR_BLOOD_LESSROLE				=	 8001,  //����������
	CARDERR_BLOOD_DIFFCULTY				=	 8002,  //�Ѷ�ѡ�����
	CARDERR_BLOOD_NOTBUYBUFF			=	 8003,  //��ǰ�ؿ����ܹ���buff
	CARDERR_BLOOD_NOTREWARD				=	 8004,  //��ǰ�ؿ�������ȡ����
	CARDERR_BLOOD_BUFFTYPENOT			=	 8005,  //����buff���ʹ���
	CARDERR_BLOOD_NOTENOUGHSTAR			=	 8006,  //��ǰ��������
	CARDERR_BLOOD_NOTLEFTCOUNT			=	 8007,  //�μӴ�������
	CARDERR_BLOOD_NOTBATTLEBEGIN		=	 8008,  //����Ѫս��ʼ
	CARDERR_BLOOD_NOTSTARPRE			=	 8009,  //�ϴ�Ѫսδ����
	CARDERR_BLOOD_HAVECHOOSEBUFF		=	 8010,  //��ѡ��buff
	CARDERR_BLOOD_MUSTBUYBUFF			=	 8011,  //����Ҫ�����buff

	CARDERR_NEWTASK_NOTASK              =    9001,  // û�������
	CARDERR_NEWTASK_GIFT                =    9002,  // �Ѿ���ȡ��������
	CARDERR_NEWTASK_REGDAY              =    9003,  // ע������������

};

#endif

