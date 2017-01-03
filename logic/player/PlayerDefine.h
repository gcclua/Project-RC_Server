#ifndef __PLAYERDEFINE_H__
#define __PLAYERDEFINE_H__

#include "Base.h"
#include "Scene/GameDefine_Scene.h"
class PlayerStatus
{
public:
	enum 
	{
		//��ʼֵ
		EMPTY = 0,
		
		//�ѳɹ���������
		//���ڴ�״̬ʱ�ɽ�����ҵĵ�½����
		CONNECTED,

		//���ڽ��е�½��֤
		LOGIN_VALIDATING,
		//��½��֤�ɹ�
		//��֤�˻�״̬
		LOGIN_VALIDATE_OK,
		//��½��֤ʧ��
		//����ΪCONNECTED״̬
		LOGIN_VALIDATE_FAILED,

		//������֤�˻�״̬
		LOGIN_ACCOUNTSTATECHECKING,
		//�˻�״̬��֤�ɹ�
		//��ѯ��ɫ�б�
		LOGIN_ACCOUNTSTATECHECK_OK,
		//�˻�״̬��֤ʧ��
		//����ΪCONNECTED״̬
		LOGIN_ACCOUNTSTATECHECK_FAILED,

		//�����Ŷ�
		LOGIN_QUEUING,
		//�Ŷ����
		LOGIN_QUEUE_FINISH,

		//���ڲ�ѯ��ɫ�б�
		LOGIN_QUERYING_CHARLIST,
		//��ѯ��ɫ�б�ɹ�
		//�ȴ����ѡ��򴴽���ɫ
		LOGIN_QUERY_CHARLIST_OK,
		//��ѯ��ɫ�б�ʧ��
		//����ΪCONNECTED״̬
		LOGIN_QUERY_CHARLIST_FAILED,


		//���ڴ�����ɫ
		LOGIN_CREATING_CHAR,
		//������ɫ�ɹ�
		//׼�����볡��
		LOGIN_CREATE_CHAR_OK,
		//������ɫʧ��
		//����ΪCONNECTED״̬
		LOGIN_CREATE_CHAR_FAILED,

		//�ȴ���Ҵ�����ɫ����ѡ���ɫ������
		LOGIN_READYTONEXT,

		//���ڼ��ؽ�ɫ
		LOGIN_LOADING_CHAR,
		//���ؽ�ɫ�ɹ�
		//׼�����볡��
		LOGIN_LOAD_CHAR_OK,
		//���ؽ�ɫʧ��
		//����ΪCONNECTED״̬
		LOGIN_LOAD_CHAR_FAILED,

		// ׼��������Ϸ����
		LOGIN_READYENTERWORLD,

		//
		GAME_ENTERINGWORLD,

		//�ѽ�����Ϸ
		GAME_PLAYERING,



	};
};

#define  HANDLEPACKET_EMPTY(PACKETCLASS) \
uint32 HandlePacket(PACKETCLASS &rPacket) \
{\
	return PACKET_EXE_CONTINUE; \
}

#define HANDLEPACKET_LOGIN(PACKETCLASS, PLAYERSTATUS) \
	tuint32 HandlePacket(PACKETCLASS &rPacket) \
{ \
	if (GetStatus() == PLAYERSTATUS) \
{ \
	return m_LoginObj.HandlePacket(rPacket); \
} \
	else \
{ \
	CacheLog(LOGDEF_INST(Warning), "handle packet exception, handletype(%s), playerstatus(%d), packetclass(%s), packetexpectplayerstatus(%d)", "login", GetStatus(), #PACKETCLASS, (tint32)PLAYERSTATUS); \
	return PACKET_EXE_CONTINUE; \
} \
}

#define  HANDLEPACKET_USER(PACKETCLASS) \
	uint32 HandlePacket(PACKETCLASS &rPacket) \
{\
	if (GetStatus() == PlayerStatus::GAME_PLAYERING) \
{\
	return m_UserObj.HandlePacket(rPacket);\
}\
	else\
{\
	CacheLog(LOGDEF_INST(Warning), "handle packet exception, handletype(%s), playerstatus(%d), packetclass(%s), packetexpectplayerstatus(%d)", "user", GetStatus(), #PACKETCLASS, (tint32)PlayerStatus::GAME_PLAYERING); \
	return PACKET_EXE_CONTINUE; \
}\
}

#define  MAX_LASTPACKETSIZE 3

class PacketStat
{
public:
	PacketStat()
	{
		m_nReceiveCount = 0;
		m_nReceiveSize  = 0;
		m_nSendCount    = 0;
		m_nSendSize     = 0;
	}

public:
	int64 m_nReceiveCount;
	int64 m_nReceiveSize;
	int64 m_nSendCount;
	int64 m_nSendSize;

};

class PlayerKickReason
{
public:
	enum
	{
		GMTOOLS = 0,	//GM��������
		PAYTEST,		//��ֵ���ܲ�������
		BLOCKROLE,		//���ɫ����
		REPEATLOGINREPLACE,	//�ظ���¼ʱ����
		MODIFYVIPCOST,		//�޸�Vip�ȼ�ʱ����
		CHANGEWORLD,	//����������
	};
};

class PlayerQueuingData
{
public:
	enum
	{
		QUEUINGLEVEL_GM = 0,
		QUEUINGLEVEL_RECONNECTION,
		QUEUINGLEVEL_NORMAL,
	};

public:
	ACCOUNTNAME m_szAccount;
	int    m_nPlayerID;
	int    m_nQueuingLevel;
	int    m_nRechargeValue;

public:
	PlayerQueuingData(void)
	{
		m_szAccount      = "";
		m_nPlayerID      = INVALID_ID;
		m_nQueuingLevel  = QUEUINGLEVEL_NORMAL;
		m_nRechargeValue = 0;
	}

	PlayerQueuingData(const ACCOUNTNAME& szAccount,int nPlayerID,int nQueuingLevel,int nRechargeValue)
	{
		m_szAccount      = szAccount;
		m_nPlayerID      = nPlayerID;
		m_nQueuingLevel  = nQueuingLevel;
		m_nRechargeValue = nRechargeValue;
	}
	~PlayerQueuingData()
	{

	}
public:
	PlayerQueuingData(const PlayerQueuingData& rData)
	{
		m_szAccount      = rData.m_szAccount;
		m_nPlayerID      = rData.m_nPlayerID;
		m_nQueuingLevel  = rData.m_nQueuingLevel;
		m_nRechargeValue = rData.m_nRechargeValue;
	}

	PlayerQueuingData& operator = (const PlayerQueuingData& rData)
	{
		if (this != &rData)
		{
			m_szAccount      = rData.m_szAccount;
			m_nPlayerID      = rData.m_nPlayerID;
			m_nQueuingLevel  = rData.m_nQueuingLevel;
			m_nRechargeValue = rData.m_nRechargeValue;
		}
		return *this;
	}

public:
	bool operator < (const PlayerQueuingData& rData) const
	{
		switch (m_nQueuingLevel)
		{
		case QUEUINGLEVEL_GM:
			{
				if (rData.m_nQueuingLevel == QUEUINGLEVEL_GM)
				{
					return false;
				}
				else if (rData.m_nQueuingLevel == QUEUINGLEVEL_RECONNECTION)
				{
					return true;
				}
				return true;
			}
			break;
		case QUEUINGLEVEL_RECONNECTION:
			{
				if (rData.m_nQueuingLevel == QUEUINGLEVEL_GM)
				{
					return false;
				}
				else if (rData.m_nQueuingLevel == QUEUINGLEVEL_RECONNECTION)
				{
					return false;
				}
				return true;
			}
			break;
		default:
			{
				if (rData.m_nQueuingLevel == QUEUINGLEVEL_GM)
				{
					return false;
				}
				else if (rData.m_nQueuingLevel == QUEUINGLEVEL_RECONNECTION)
				{
					return false;
				}
				else
				{
					if (m_nRechargeValue <= rData.m_nRechargeValue)
					{
						return false;
					}
					else 
					{
						return true;
					}
				}
			}
			break;
		}
	}

};


#endif

