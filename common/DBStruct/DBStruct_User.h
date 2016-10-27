
#ifndef __DBSTRUCT_USER_H__
#define __DBSTRUCT_USER_H__

#include "DBStruct.h"
#include "DBStruct_City.h"
#include "DBStruct_Troop.h"
#include "DBStruct_Hero.h"




//��Ҫ����Ľ�ɫ����
struct DBBaseUserData
{
public:
	DBBaseUserData(){};
	~DBBaseUserData(){};

	void CleanUp( );
	void CopyFrom(const DBBaseUserData& rSource);


	//������Ϣ
	//
	int				m_PortraitID;					//��ɫͷ��
	char			m_Name[MAX_CHARACTER_NAME];		//��ɫ����
	char			m_Title[MAX_CHARACTER_TITLE];	//��ɫ����
	int64			m_GUID;							//��ɫ��ȫΨһ��
	int 			m_Sex;							//��ɫ�Ա�
	tuint32			m_CreateDate;					//��ɫ��������
	int				m_Level;						//��ɫ�ȼ�
	int				m_RMBMoney;						//m_Vigor;						//����			//Ŀǰ��Ԫ��ֵ 
	int				m_BankRMB;						//m_MaxVigor;						//��������	//�������е�Ԫ��
	int				m_VigorRegeneRate;				//�����ָ��ٶ�
	int				m_DoubleExpTime_Num;			//˫������ʱ��ͱ���;
	int				m_GmRight;					   //gmȨ�޵ȼ�
	int				m_EnergyRegeneRate;				//�����ָ��ٶ�
	tuint32			m_Exp;							//��ɫ����ֵ
	tuint32			m_Money;						//��ɫ����
	//int				m_nRMBMoney;					//Ԫ��ֵ
	tuint32			m_uPwdDelTime;					//����ǿ�ƽ�������ʱ��
	tuint32			m_HairColor;					//ͷ����ɫ	
	BYTE			m_FaceColor;					//������ɫ
	BYTE			m_HairModel;					//ͷ��ģ��
	BYTE			m_FaceModel;					//����ģ��

	//
	//����״̬
	//
	tuint32			m_OnlineTime;					//������ʱ��
	tuint32			m_LastLoginTime;				//���һ�ε���ʱ��
	tuint32			m_LastLogoutTime;				//���һ�εǳ�ʱ��
	tuint32			m_LeftDieTime;					//ʣ������ʱ��
	tuint32			m_DBVersion;					//���ݿ�汾

	//
	//ս����Ϣ
	//
	int				m_MenPai;					//���� MENPAI_ATTRIBUTE
	int				m_NeiShang;					//����
	int				m_HP;						//����ֵ
	int				m_MP;						//ħ��
	int 			m_StrikePoint;				//������
	int 			m_Rage;						//ŭ��
	int				m_nPKValue;					//ɱ��
	int				m_Level1Points;				//һ������ʣ�����

	
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
