
#ifndef __DBSTRUCT_USER_H__
#define __DBSTRUCT_USER_H__

#include "DBStruct.h"
#include "DBStruct_City.h"
#include "DBStruct_Troop.h"
#include "DBStruct_Hero.h"




//需要保存的角色数据
struct DBBaseUserData
{
public:
	DBBaseUserData(){};
	~DBBaseUserData(){};

	void CleanUp( );
	void CopyFrom(const DBBaseUserData& rSource);


	//基本信息
	//
	int				m_PortraitID;					//角色头像
	char			m_Name[MAX_CHARACTER_NAME];		//角色名字
	char			m_Title[MAX_CHARACTER_TITLE];	//角色名字
	int64			m_GUID;							//角色完全唯一号
	int 			m_Sex;							//角色性别
	tuint32			m_CreateDate;					//角色创建日期
	int				m_Level;						//角色等级
	int				m_RMBMoney;						//m_Vigor;						//活力			//目前是元宝值 
	int				m_BankRMB;						//m_MaxVigor;						//活力上限	//存在银行的元宝
	int				m_VigorRegeneRate;				//活力恢复速度
	int				m_DoubleExpTime_Num;			//双倍经验时间和倍数;
	int				m_GmRight;					   //gm权限等级
	int				m_EnergyRegeneRate;				//精力恢复速度
	tuint32			m_Exp;							//角色经验值
	tuint32			m_Money;						//角色货币
	//int				m_nRMBMoney;					//元宝值
	tuint32			m_uPwdDelTime;					//设置强制解除密码的时间
	tuint32			m_HairColor;					//头发颜色	
	BYTE			m_FaceColor;					//脸形颜色
	BYTE			m_HairModel;					//头发模型
	BYTE			m_FaceModel;					//脸形模型

	//
	//基本状态
	//
	tuint32			m_OnlineTime;					//总在线时间
	tuint32			m_LastLoginTime;				//最后一次登入时间
	tuint32			m_LastLogoutTime;				//最后一次登出时间
	tuint32			m_LeftDieTime;					//剩余死亡时间
	tuint32			m_DBVersion;					//数据库版本

	//
	//战斗信息
	//
	int				m_MenPai;					//门派 MENPAI_ATTRIBUTE
	int				m_NeiShang;					//内伤
	int				m_HP;						//生命值
	int				m_MP;						//魔法
	int 			m_StrikePoint;				//连击点
	int 			m_Rage;						//怒气
	int				m_nPKValue;					//杀气
	int				m_Level1Points;				//一级属性剩余点数

	
};

struct DBFullUserData
{
	DBFullUserData()
	{
		CleanUp();
	}
	DBBaseUserData				m_baseUser;
	DBCity                      m_City;
	DBHero                      m_Hero;
	
	bool						m_bIsPasswdUnlock;

	void   CleanUp();

	void   CopyFrom(const DBFullUserData& rSource);
	uint32 CalcCRC();

	int64  getGuid() const {return m_baseUser.m_GUID;}

};

struct MemFullUserData
{
	MemFullUserData()
	{
		CleanUp();
	}

	void CleanUp()
	{
		m_UserData.CleanUp();
	}

	int m_DBVersion;
	DBFullUserData m_UserData;
};


#endif
