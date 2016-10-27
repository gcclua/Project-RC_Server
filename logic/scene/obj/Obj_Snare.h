/********************************************************************
	�ļ���: 	Obj_Snare.h
	�ļ�·��:	\Project\Server\Server\Server\Scene\Obj
	������:		luoy
	����ʱ��:	2014-4-28 20:21
	����˵��������
	�޸ļ�¼:

*********************************************************************/
#ifndef OBJ_SNARE_H
#define OBJ_SNARE_H

#include "Obj_Character.h"
class Obj_Snare : public Obj
{
public:
	Obj_Snare(void);
	virtual ~Obj_Snare(void){};

public:
	virtual tint32 GetObjType(void) const {return ObjType::SNAREOBJ;};
public:
	virtual void Tick(const TimeInfo &rTimeInfo);
	virtual bool CanBeView(Obj_March &rObj);
public:
	enum 
	{
		STATE_INVALID =-1,
		STATE_NOACTIVATE =0,//δ����״̬
		STATE_ACTIVATE,//����״̬
		STATE_DEAD,//����״̬
	};
	enum  //���弤�ʽ
	{
		ACTIVATE_SCAN =1,//�ӳ�ʱ�䵽����ɨ�赽ָ��Ŀ�꼤�� 
		ACTIVATE_TIME =2,//�ӳ�ʱ��һ���ͼ������ɨ�赽ָ��Ŀ��
	};
	struct SnareSendImpactInfo
	{
	public:
		SnareSendImpactInfo()
		{
			CleanUp();
		}
		tint32 m_nImpactId; //BUFF Id
		tint32 m_DelayTime;	//BUFF �״���Ч���ӳ�ʱ��
		tint32 m_nScanIntervalTime;//ɨ����ʱ��
		tint32 m_nMaxEffectTimes;//BUFF�����Ч�Ĵ���
		bool   m_bIsEffectByHit;//�Ƿ�����Ŀ�������Ч����
		tint32 m_nValidRadius;//BUFFɨ��뾶
		tint32 m_nMaxValidNum;//BUFF����Ŀ������
		tuint32 m_nLastScanTime;//�ϴ�ɨ��ʱ��
		tint32	m_nEffectTimes ;//�Ѿ���Ч�Ĵ���
		void CleanUp()
		{
			m_nImpactId =invalid_id; //BUFF Id
			m_DelayTime =0;	//BUFF �״���Ч���ӳ�ʱ��
			m_nScanIntervalTime =0;//ɨ����ʱ��
			m_nMaxEffectTimes =0;//BUFF�����Ч�Ĵ���
			m_bIsEffectByHit =false;//�Ƿ�����Ŀ�������Ч����
			m_nValidRadius =0;//BUFFɨ��뾶
			m_nMaxValidNum =0;//BUFF����Ŀ������
			m_nLastScanTime =0;//�ϴ�ɨ��ʱ��
			m_nEffectTimes =0;//�Ѿ���Ч�Ĵ���
		}
	};
	enum 
	{
		MAXBUFFNUM =6, //֧�ַ��͵����BUFF��
	};
	void SetOwnerId(tint32 val) { m_OwnerId = val; }
	void SetIsOwnerCanSee(bool val) { m_bIsOwnerCanSee = val; }
	void SetIsActivateCanSee(bool val) { m_bIsActivateCanSee = val; }
	void SetIsDelOwnerLevelScene(bool val) { m_bDelOwnerLevelScene = val; }
	void SetLifeTime(tint32 val) { m_nLifeTime = val; }
	void SetValidDelayTime(tint32 val) { m_nValidDelayTime = val; }
	void SetActivateRadius(tint32 val) { m_ActivateRadius = val; }
	void SetImpactInfoByIndex(SnareSendImpactInfo const& rImpactInfo,tint32 nIndex);
	void SetNeedTargetType(tint32 val) { m_nNeedTargetType = val; }
	void SetCurState(tint16 val) { m_nCurState = val; }
	void SetCreateTime(tuint32 val) { m_nCreateTime = val; }
	tint32 GetSnareId() const { return m_snareId; }
	void SetSnareId(tint32 val) { m_snareId = val; }
	int64 GetOwnerGuid() const { return m_OwnerGuid; }
	void SetOwnerGuid(int64 val) { m_OwnerGuid = val; }
	void SetActivateModel(tint32 val) { m_nActivateModel = val; }
private:
	void BroadcastBuff(Obj_CharacterPtr OwnerPtr);
	bool IsWantedTarget(Obj_Character& rTarget,Obj_CharacterPtr OwnerPtr);
private:
	tint32 m_snareId;//����ID
	tint32 m_OwnerId;//����ID
	int64 m_OwnerGuid;//����GUID 
	bool m_bIsOwnerCanSee; //�Ƿ����˿ɼ�
	bool m_bIsActivateCanSee;//�Ƿ���Ч��ɼ�
	bool m_bDelOwnerLevelScene;//���˲��ڳ���ʱ�Ƿ�ɾ��
	tint32 m_nActivateModel;//���弤�ʽ
	tint32 m_nLifeTime;//���ʱ��
	tint32 m_nValidDelayTime;//�ӳ���Чʱ��
	tint32 m_ActivateRadius;//���崥���뾶
	tint32 m_nNeedTargetType;//ɨ��Ŀ������(���������˵)
	bsarray<SnareSendImpactInfo, Obj_Snare::MAXBUFFNUM> m_ImpactInfo;
	tint16 m_nCurState; //��ǰ״̬
	tuint32 m_nCreateTime;//����ʱ��
	tuint32 m_nActiveTime;//�����ʱ��
};

POOLDEF_DECL(Obj_Snare);

#endif
