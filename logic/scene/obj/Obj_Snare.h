/********************************************************************
	文件名: 	Obj_Snare.h
	文件路径:	\Project\Server\Server\Server\Scene\Obj
	创建者:		luoy
	创建时间:	2014-4-28 20:21
	功能说明：陷阱
	修改记录:

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
		STATE_NOACTIVATE =0,//未激活状态
		STATE_ACTIVATE,//激活状态
		STATE_DEAD,//死亡状态
	};
	enum  //陷阱激活方式
	{
		ACTIVATE_SCAN =1,//延迟时间到并且扫描到指定目标激活 
		ACTIVATE_TIME =2,//延迟时间一到就激活，无需扫描到指定目标
	};
	struct SnareSendImpactInfo
	{
	public:
		SnareSendImpactInfo()
		{
			CleanUp();
		}
		tint32 m_nImpactId; //BUFF Id
		tint32 m_DelayTime;	//BUFF 首次生效的延迟时间
		tint32 m_nScanIntervalTime;//扫描间隔时间
		tint32 m_nMaxEffectTimes;//BUFF最大生效的次数
		bool   m_bIsEffectByHit;//是否命中目标才算生效次数
		tint32 m_nValidRadius;//BUFF扫描半径
		tint32 m_nMaxValidNum;//BUFF作用目标上限
		tuint32 m_nLastScanTime;//上次扫描时间
		tint32	m_nEffectTimes ;//已经生效的次数
		void CleanUp()
		{
			m_nImpactId =invalid_id; //BUFF Id
			m_DelayTime =0;	//BUFF 首次生效的延迟时间
			m_nScanIntervalTime =0;//扫描间隔时间
			m_nMaxEffectTimes =0;//BUFF最大生效的次数
			m_bIsEffectByHit =false;//是否命中目标才算生效次数
			m_nValidRadius =0;//BUFF扫描半径
			m_nMaxValidNum =0;//BUFF作用目标上限
			m_nLastScanTime =0;//上次扫描时间
			m_nEffectTimes =0;//已经生效的次数
		}
	};
	enum 
	{
		MAXBUFFNUM =6, //支持发送的最大BUFF数
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
	tint32 m_snareId;//陷阱ID
	tint32 m_OwnerId;//主人ID
	int64 m_OwnerGuid;//主人GUID 
	bool m_bIsOwnerCanSee; //是否主人可见
	bool m_bIsActivateCanSee;//是否生效后可见
	bool m_bDelOwnerLevelScene;//主人不在场景时是否删除
	tint32 m_nActivateModel;//陷阱激活方式
	tint32 m_nLifeTime;//存活时间
	tint32 m_nValidDelayTime;//延迟生效时间
	tint32 m_ActivateRadius;//陷阱触发半径
	tint32 m_nNeedTargetType;//扫描目标类型(针对主人来说)
	bsarray<SnareSendImpactInfo, Obj_Snare::MAXBUFFNUM> m_ImpactInfo;
	tint16 m_nCurState; //当前状态
	tuint32 m_nCreateTime;//创建时间
	tuint32 m_nActiveTime;//激活的时间
};

POOLDEF_DECL(Obj_Snare);

#endif
