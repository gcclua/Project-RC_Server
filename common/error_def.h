#ifndef _ERROR_DEF_H_
#define _ERROR_DEF_H_


enum    ERROR_CODE
{
	CARDERR_SUCCESS						=		0,

	CARDERR_SYSTEM                      =     100,  //系统
	CARDERR_MODULE_MISS                 =     101,  //模块丢失
	CARDERR_ALLOC_FAIL                  =     102,  //内存申请操作失败
	CARDERR_SYSTEM_UNKOWN               =     103,  //未知系统错误
	CARDERR_PROTO_NULL					=	  104,	//proto文件为空

	CARDERR_COMMON                      =    1000,  //通用
	CARDERR_CONFIG_MISS                 =    1001,  //未找到配置
	CARDERR_CONFIG_ERROR                =    1002,  //配置有误
	CARDERR_WRONG_PARAM                 =    1003,  //参数错误
	CARDERR_NOTENOUGH_GOLD				=    1004,  //金币不足
	CARDERR_NOTENOUGH_CASH				=    1005,  //元宝不足
	CARDERR_NOTENOUGH_ENERGY			=    1006,  //精力不足
	CARDERR_NOTENOUGH_QI				=    1007,  //气不足
	CARDERR_NAME_CANTEMPT				=    1008,  //名字不能为空
	CARDERR_NAME_EXIT					=    1009,  //名字已存在
	CARDERR_LESS_LEVEL					=    1010,  //等级不足
	CARDERR_NAME_BAD                    =    1011,  // 屏蔽字
	CARDERR_LESS_VIP					=	 1012,  //vip等级不足
	

	CARDERR_ROLE_NOTFIND                =    2000,  //没有找到将
	CARDERR_ROLE_NOTTRAINDATA           =    2001,  //没有培养数据
	CARDERR_ROLE_NOTEXP			        =    2002,  //没有经验
	CARDERR_ROLE_NOTSOUL		        =    2003,  //没有足够魂
	CARDERR_ROLE_HAVEROLE		        =    2004,  //已经拥有
	CARDERR_ROLE_NOTTIME		        =    2005,  //时间未到
	CARDERR_ROLE_NOTFINDSOUL	        =    2006,  //没有找到魂
	CARDERR_ROLE_ROLEARRANGE	        =    2007,  //将以上阵
	CARDERR_ROLE_ROLECARDPOS	        =    2008,  //将技能卡位置
	CARDERR_ROLE_QIANLIERROR	        =    2009,  //潜力不足
	CARDERR_ROLE_MAXARRANGECNT	        =    2010,  //已到最大上阵数
	CARDERR_ROLE_ARRANGENOTON	        =    2011,  //此位置不可以上阵
	CARDERR_ROLE_MAXCOUNTINVITE	        =    2012,  //达到每日最大招募数

	CARDERR_CARD_NOTFIND		        =    3001,  //没有卡
	CARDERR_CARD_SKILLNOTSELL	        =    3002,  //技能不能卖
	CARDERR_CARD_NOTFEEDCARD	        =    3003,  //没有消耗卡
	CARDERR_CARD_NOTSKILLCARD	        =    3004,  //非技能卡
	CARDERR_CARD_SAMEASMAIN				=    3005,  //需要参悟的卡
	CARDERR_CARD_SAMECARD				=    3006,  //同类型卡
	CARDERR_CARD_MAXEQUIPLEVEL			=    3007,  //已到最大强化等级
	CARDERR_CARD_ARRANGEPOSERR			=    3008,  //装备位置错误

	CARDERR_TASK_TASKMAXCOUNT	        =    4001,  //达到任务最大数
	CARDERR_TASK_HADGROUPREWARD	        =    4002,  //已领取组奖励
	CARDERR_TASK_NOTCOMPELETE	        =    4003,  //未完成任务
	CARDERR_TASK_NOTUNLOCK		        =    4004,  //未解锁任务
	CARDERR_TASK_LOWSTART		        =    4005,  //任务星级不足
	CARDERR_TASK_NOARRANGE		        =    4006,  //没有将上阵
	CARDERR_TASK_HASCOUNT		        =    4006,  //还有挑战次数

	CARDERR_INVENTORY_NEED_KEY			=	 5001,  //需要钥匙
	CARDERR_INVENTORY_KEY_COUNT			=	 5002,  //钥匙数量不够
	CARDERR_INVENTORY_NOTFOUND			=	 5003,  //未找到背包物品
	CARDERR_INVENTORY_NOTUSE			=	 5004,  //物品不能使用
	CARDERR_INVENTORY_NOTENOUGH			=	 5005,  //物品数目不足
	CARDERR_INVENTORY_NOTBOX			=	 5006,  //未找到宝箱
	CARDERR_INVENTORY_MAXBUYCOUNT		=	 5007,  //已达到最大购买数量
	CARDERR_INVENTORY_VIPNOTUSE			=	 5008,  //vip物品已到最大次数


	CARDERR_FORMAL_FLAG                 =    5010,  // 已经参拜过

	CARDERR_LEVELGIFT_FLAG              =    5015,  // 等级礼包已经领取
	CARDERR_LEVELGIFT_LOWLEVEL          =    5016,  // 等级太低
	CARDERR_TIMEPOWER_FLAG              =    5019,  // 已经完成
	CARDERR_TIMEPOWER_TIME              =    5020,  // 不在活动期间内

	CARDERR_FRAGCOMPOSE_NOFRAG          =    5021,  // 残片合成，缺少残片
	CARDERR_FRAGFIGHT_NOFRAGMENT        =    5022,  // 残片抢夺放没有对应残片
	CARDERR_FRAGFIGHT_FAIL              =    5023,  // 残片抢夺失败

	CARDERR_RANKFIGHT_SELFNORANK        =    5024,   // 论剑挑战，自己不在排行
	CARDERR_RANKFIGHT_OTHERNORANK       =    5025,   // 论剑挑战，对方不在排行
	CARDERR_RANKFIGHT_RANKMIN           =    5026,   // 论剑挑战，自己排名大于对方排名
	CARDERR_RANKFIGHT_SUCESS            =    5027,   // 论剑挑战成功
	CARDERR_RANKFIGHT_FAIL              =    5028,   // 对方排名不满足条件
	CARDERR_RANKMAXCOUNT                =    5029,   // 挑战次数已满

	CARDERR_SCOREBUY_NOSCORE            =    5030,   // 积分不够
	CARDERR_SCOREBUY_RANK               =    5031,   // 没到达过最好排名
	CARDERR_SCOREBUY_LEVEL              =    5032,   // 等级条件不够
	CARDERR_SCOREBUY_COUNT              =    5033,   // 超过购买次数
	CARDERR_RANKFIGHT_QI                =    5034,   // 挑战时元气不够
	CARDERR_RANK_USEITEM                =    5035,   // 不能使用掌门绝
	CARDERR_FRIEND_COUNT                =    5036,   // 好友次数已经最多
	CARDERR_FRIEND_ISFIREND             =    5037,   // 已经是好友
	CARDERR_FRIEND_ATTENCOUNT           =    5038,   // 关注人数已经最多
	CARDERR_FRIEND_ISATTEN              =    5039,   // 已经在关注列表


	CARDERR_CHEATS_NOTFOUND				=	 6001,  //未找到秘策

	CARDERR_CHAT_NOTITEM				=	 7001,  //未找到千里传音

	CARDERR_BLOOD_LESSROLE				=	 8001,  //上阵将数不足
	CARDERR_BLOOD_DIFFCULTY				=	 8002,  //难度选择错误
	CARDERR_BLOOD_NOTBUYBUFF			=	 8003,  //当前关卡不能购买buff
	CARDERR_BLOOD_NOTREWARD				=	 8004,  //当前关卡不能领取奖励
	CARDERR_BLOOD_BUFFTYPENOT			=	 8005,  //购买buff类型错误
	CARDERR_BLOOD_NOTENOUGHSTAR			=	 8006,  //当前星数不足
	CARDERR_BLOOD_NOTLEFTCOUNT			=	 8007,  //参加次数已满
	CARDERR_BLOOD_NOTBATTLEBEGIN		=	 8008,  //不是血战开始
	CARDERR_BLOOD_NOTSTARPRE			=	 8009,  //上次血战未获星
	CARDERR_BLOOD_HAVECHOOSEBUFF		=	 8010,  //已选择buff
	CARDERR_BLOOD_MUSTBUYBUFF			=	 8011,  //有需要购买的buff

	CARDERR_NEWTASK_NOTASK              =    9001,  // 没完成任务
	CARDERR_NEWTASK_GIFT                =    9002,  // 已经领取过任务奖励
	CARDERR_NEWTASK_REGDAY              =    9003,  // 注册天数不满足

};

#endif

