/********************************************************************************
 *	文件名：	GameStruct_Impact.h
 *	全路径：	\Server\Common\ImpactStruct\GameStruct_Impact.h
 *	创建人：	zz
 *	创建时间：2013-1-8
 *
 *	功能说明：BUFF相关数据结构
 *	修改记录：
*********************************************************************************/

#ifndef GAMESTRUCT_IMPACT_H
#define GAMESTRUCT_IMPACT_H

#include "Base.h"
#include "GameDefine_Impact.h"

struct  DBImpactStruct;
class Table_Impact;

struct ImpactStruct
{
public:
	enum 
	{
		MAX_IMAPCT_PARAM_NUM =8,
		MAX_WRAPCNT =256,
	};
	ImpactStruct()
	{
		CleanUp();
	}
	void CleanUp()
	{
		m_nImpactId =invalid_id;//BuffId
		m_nSkillId =invalid_id;//技能ID
		m_nSenderObjId =invalid_id;//发送者objId
		m_fContinuTime =0.0f;//持续时间
		m_nEffectTime =0;//BUFF生效的时间
		m_nIntervalElapsed =0;//流逝的间隔
		m_nDelayTime =0;//延迟生效时间
		m_nImpactWrapCnt =0;//叠加层数
		m_nIntervalTime =0;
		m_nSenderType =-1;//obj Type Npc 玩家 伙伴 僵尸玩家
		m_SenderGuid =invalid_guid64;//玩家和伙伴有GUID
		m_nSceneClassId =-1;//BUFF发送时的场景Class ID
		m_nSceneInstanceId =-1;//BUFF发送时的场景实例 ID
		m_pImpactDataInfo =null_ptr;
		for (int i=0;i<MAX_IMAPCT_PARAM_NUM;i++)
		{
			m_aParams[i] =0;
		}
	}
	bool IsVaild() const {return (m_pImpactDataInfo !=null_ptr);};
	int GetParamByIndex(int nIndex)
	{
		if (nIndex<0 || nIndex>=MAX_IMAPCT_PARAM_NUM)
		{
			return invalid_id;
		}
		return m_aParams[nIndex];
	}

	void SetParamByIndex(int nIndex,int nValue)
	{
		if (nIndex<0 || nIndex>=MAX_IMAPCT_PARAM_NUM)
		{
			return;
		}
		m_aParams[nIndex] =nValue;
	}
public:
	bool SerializeToDB(DBImpactStruct& rDest);//数据拷贝到存储结构中
	bool SerializeFromDB(const DBImpactStruct& rSour);//存储结构中数据拷贝
public:
	int m_nImpactId;//BuffId
	int m_nSkillId;//技能ID
	int m_nSenderType;//obj Type Npc 玩家 伙伴 僵尸玩家
	int64 m_SenderGuid;//玩家和伙伴有GUID
	int m_nSceneClassId;//BUFF发送时的场景Class ID
	int m_nSceneInstanceId;//BUFF发送时的场景实例 ID
	int m_nSenderObjId;//发送者objId
	float m_fContinuTime;//持续时间(单位:秒)
	time_t m_nEffectTime;//BUFF生效的时间(单位:秒)
	int m_nIntervalTime;//间隔触发时间(单位:毫秒)
	int m_nIntervalElapsed;//流逝的间隔(单位:毫秒)
	int m_nDelayTime;//延迟生效
	uint8 m_nImpactWrapCnt;//叠加层数
	Table_Impact const* m_pImpactDataInfo;
private:
	bsarray<int, MAX_IMAPCT_PARAM_NUM> m_aParams;
};


#endif