///////////////////////////////////////////////////////
//
//伙伴容器
//
//////////////////////////////////////////////////////
#ifndef _MARCHCONTAINER_H_
#define _MARCHCONTAINER_H_

#include "GameStruct_March.h"

struct DBMarchPack;
class MarchContainer
{
public:
	enum CONSTANT_VALUE
	{
		LIST_SIZE = MARCH_MAX_COUNT,
	};
public:
	MarchContainer();
	~MarchContainer();
	MarchContainer& operator=(const MarchContainer& rhs);
	void CopyFrom(const MarchContainer& rhs);
	void CleanUp(void);
public:
	//槽位数量
	tint32								GetSlotCount(void) const;
	void								SetSlotCount(tint32 nCount);
	//空槽数量
	tint32								GetEmptySlotCount(void) const;
	//根据伙伴Guid获取索引
	tint32								GetIndexByGuid(const int64 rMarchGuid) const;
	//从指定槽位开始查找其后的第一个空白槽位
	tint32								FindFirstEmptySlotIndex(tint32 StartSlot = 0) const;

public:
	//获取March
	bool								IsMarchGuidValid(const int64 rMarchGuid) const;
	March const&						GetMarchByGuid(const int64 rMarchGuid) const;
	bool								IsMarchIndexValid(tint32 nIndex) const;
	March const&						GetMarchByIndex(tint32 nIndex) const;

public:
	//增加 删除 修改
	bool								AddMarch(const March& rMarch);
	bool								CreateMarch(March& rMarch, int64 nBuildId);
	bool								AddMarchByBuildId(int64 nBuildId);
	bool								UpdateMarchByIndex( const March& rMarch, tint32 nIndex);
	bool								UpdateMarchByGuid( const March& rMarch, const int64 rMarchGuid);
	bool								CanAddMarch(const March& rMarch);										//是否可以添加

public:
	//脏标记相关
	bool								IsDirty(void) {return (m_DirtyFlags.GetMarkedBitCount() > 0) ? true : false;}
	void								ClearAllDirtyFlags(void) {m_DirtyFlags.ClearAllBits();}
	void								MarkAllDirtyFlags(void) {m_DirtyFlags.MarkAllBits();}
	bool								IsSlotDirty(tint32 index) {return m_DirtyFlags.GetBit(index);}
	void								SetSlotDirty(tint32 index, bool flag) {m_DirtyFlags.SetBit(index, flag);}
private:
	March const *						GetSlot(tint32 nIndex) const {return m_MarchContainer.GetSlot(nIndex);}
	March *							    GetSlot(tint32 nIndex) {return m_MarchContainer.GetSlot(nIndex);}
public:
	void                                SerializeFromDB(const DBMarchList& rDBMarchList);
	void								SerializeToDB(DBMarchList& rDBMarchList, tint32& nIndex) const;
private:
	typedef Container_T<March, LIST_SIZE> MarchContainer_T;
	typedef BitSet<LIST_SIZE> DirtyFlag;
private:
	MarchContainer_T m_MarchContainer;
	DirtyFlag m_DirtyFlags;					//脏标记
	tint32 m_nOpenSlotCount;				//开放槽位
};

#endif