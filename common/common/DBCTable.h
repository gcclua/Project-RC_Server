#ifndef _DBCTABLE_H_
#define _DBCTABLE_H_

/*
通用读表器，非线程安全。读取完毕后不变，因此可多线程访问
*/

#include "BaseType.h"
#include "BaseLib.h"
#include "BaseUtility.h"
#include "Exception.h"

class DBCFile	
{
public:
	struct FILE_HEAD
	{
		tuint32	m_Identify;				//标示	0XDDBBCC00
		tint32	m_nFieldsNum;			//列数
		tint32	m_nRecordsNum;			//行数
		tint32	m_nStringBlockSize;		//字符串区大小
	};

	enum FIELD_TYPE
	{
		T_INT		= 0,
		T_FLOAT		= 1,
		T_STRING	= 2,
	};
	//数据库格式描述
	typedef bsvector<FIELD_TYPE>	FIELD_TYPE_VEC;

	//数据段
	union FIELD
	{
		tfloatptr	fValue;
		tintptr		iValue;
		const tchar* 		pString;

		FIELD(void) {}
		FIELD(tintptr value) { iValue = value; }
		FIELD(tfloatptr value) { fValue = value; }
		FIELD(const tchar* value) { pString = value; }
	};
	//数据区
	typedef bsvector<FIELD> DATA_BUF;

public:
	DBCFile(void);
	~DBCFile(void);

public:
	bool OpenFromTXT(const tchar*  szFileName);
	bool OpenFromMemory(const tchar*  pMemory, const tchar*  pDeadEnd, const tchar*  szFileName);

protected:
	bool OpenFromMemoryImpl_Text(const tchar*  pMemory, const tchar*  pDeadEnd, const tchar*  szFileName);
	bool OpenFromMemoryImpl_Binary(const tchar* pMemory, const tchar* pDeadEnd, const tchar* szFileName);
	void CheckIndex(const tchar* szFileName);

public:
	const FIELD * Search_Posistion(tint32 nRecordLine, tint32 nColumNum) const;

public:
	tint32	GetFieldsNum(void) const	{ return m_nFieldsNum; }
	tint32	GetRecordsNum(void) const	{ return m_nRecordsNum; }

protected:
	FIELD_TYPE_VEC	m_theType;			//数据库格式描述	//【stl】
	tint32			m_nRecordsNum;		//行数
	tint32			m_nFieldsNum;		//列数
	DATA_BUF		m_vDataBuf;			//数据区	//【stl】
	tchar*			m_pStringBuf;		//字符串区
	tint32			m_nStringBufSize;	//字符串区大小

public:
	static tint32 _ConvertStringToVector(const tchar* strStrINTgSource, bsvector<std::string> &vRet, const tchar* szKey, bool bOneOfKey, bool bIgnoreEmpty);
	static const tchar* _GetLineFromMemory(tchar* pStringBuf, tint32 nBufSize, const tchar* pMemory, const tchar* pDeadEnd);
};

const tchar* _LoadConstStringFromDBC(const DBCFile &rDB, tint32 nRow, tint32 nColumn);

//////////////////////////////////////////////////////////////////////////
//HASH_SIZE: Hash宽度,为了提高查找效率,不宜设置过大,最好在千级别
//MAX_RECORD_NUM: 表的最大记录数,若读多个表,为各个表记录数之和上限,现默认为2048
//////////////////////////////////////////////////////////////////////////
template<typename U, tint32 HASH_SIZE, tint32 MAX_RECORD_NUM>
class DBC_Table_Hash_T
{
public:
	enum CONSTANT_VALUE
	{
		HASH_LIST_WIDTH = HASH_SIZE,
		SEEK_LIST_SIZE = MAX_RECORD_NUM
	};
public:
	class Slot_T
	{
	public:
		Slot_T(void) : m_nID(-1), m_pNext(null_ptr)
		{
		};
		Slot_T(const Slot_T &rhs) : m_nID(rhs.m_nID), m_pContent(rhs.m_pContent), m_pNext(rhs.m_pNext)
		{
		};
		~Slot_T(void)
		{
		};
		void Init(void)
		{
			m_nID = -1;
			m_pContent = null_ptr;
			m_pNext = null_ptr;
		}
		tint32 GetID(void) const
		{
			return m_nID;
		};
		const U * GetContent(void) const
		{
			return m_pContent;
		};
		void SetContent(tint32 nID, const U &rhs) 
		{
			m_nID = nID;
			m_pContent = &rhs;
		};
		Slot_T* GetNext(void) const
		{
			return m_pNext;
		};
		void SetNext(Slot_T* pNext)
		{
			m_pNext=pNext;
		};
		bool IsValid(void) const
		{
			return 0<=m_nID?true:false;
		};
	private:
		tint32 m_nID;
		const U *m_pContent;
		Slot_T *m_pNext;
	};

	class Node_T
	{
	public:
		U* GetBlockU(void) const
		{
			return m_pBlockU;
		}
		void SetBlockU(U* pBlock)
		{
			m_pBlockU = pBlock;
		}
		Slot_T* GetBlockSlot(void) const
		{
			return m_pBlockSlot;
		}
		void SetBlockSlot(Slot_T* pBlock)
		{
			m_pBlockSlot = pBlock;
		}
		Node_T* GetNext(void) const
		{
			return m_pNext;
		}
		void SetNext(Node_T* pNode)
		{
			m_pNext = pNode;
		}
	public:
		Node_T(void)
		{
			CleanUp();
		}
		~Node_T(void)
		{
		}
		void CleanUp(void)
		{
			m_pBlockU=null_ptr;
			m_pBlockSlot=null_ptr;
			m_pNext=null_ptr;
		}
	private:
		U *m_pBlockU;
		Slot_T *m_pBlockSlot;
		Node_T *m_pNext;
	};

public:
	DBC_Table_Hash_T()
	{
		m_bReady = false;
		m_nCount = 0;
		for(tint32 nIdx=0; SEEK_LIST_SIZE>nIdx; ++nIdx)
		{
			m_pSeekList[nIdx] = null_ptr;
		}
		for(tint32 nIdx=0; HASH_LIST_WIDTH>nIdx; ++nIdx)
		{
			m_vpHashList[nIdx]=null_ptr;
		}
		m_pHead = null_ptr;
	}
	~DBC_Table_Hash_T()
	{
		Release();
	}
	bool Init(void)
	{
		Release();
		return true;
	}
	bool LoadFromMemory(const DBCFile &rDB)
	{
		tint32 nSize = rDB.GetRecordsNum();
		if(0>m_nCount)
		{
			m_nCount = 0;
		}
		if(SEEK_LIST_SIZE<(nSize+m_nCount))
		{
			tchar szAlert[256];
			tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Hash_T::LoadFromMemory]: Record count is larger than SEEK_LIST_SIZE!!");
			szAlert[sizeof(szAlert)-1] = '\0';
			Release();
			throw(szAlert);
		}

		Node_T *pNode = new Node_T;
		bool bContinue = false;
		if(null_ptr!=pNode)
		{
			Slot_T *pBlockSlot = new Slot_T[nSize];
			U* pBlockU = new U[nSize];
			if(null_ptr!=pBlockSlot && null_ptr!=pBlockU)
			{
				bContinue = true;
				pNode->SetBlockSlot(pBlockSlot);
				pNode->SetBlockU(pBlockU);
				PushBlock(*pNode);
				//read data
				for(tint32 nIdx=0; nSize>nIdx; ++nIdx)
				{
					DBCFile::FIELD const* pField = rDB.Search_Posistion(nIdx,0);
					if(null_ptr!=pField)
					{
						tint32 nID = static_cast<tint32>(pField->iValue);
						U& rContent = pBlockU[nIdx];
						if(false!=rContent.LoadFromDB(rDB, nIdx))
						{
							if(false==PushContent(nIdx, nID, rContent))
							{
								return false;
							}
							else
							{
								if(SEEK_LIST_SIZE>m_nCount)
								{
									m_pSeekList[m_nCount] = &rContent;
									++m_nCount;
								}
								else
								{
									tchar szAlert[256];
									tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Hash_T::LoadFromMemory]: Record count is larger than SEEK_LIST_SIZE!!");
									szAlert[sizeof(szAlert)-1] = '\0';
									Release();
									throw(szAlert);
								}
							}
						}
						else
						{
							tchar szAlert[256];
							tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Hash_T::LoadFromMemory]: load content(%d) failed!!", nID);
							szAlert[sizeof(szAlert)-1] = '\0';
							throw(szAlert);
						}
					}
				}
			}
			else
			{
				if(null_ptr!=pNode)
				{
					SAFE_DELETE(pNode);
				}
				if(null_ptr!=pBlockSlot)
				{
					SAFE_DELETE_ARRAY(pBlockSlot);
				}
				else
				{
					throw("[DBC_Table_Hash_T::LoadFromMemory]: New memory for BlockSlot failed!!");
				}
				if(null_ptr!=pBlockU)
				{
					SAFE_DELETE_ARRAY(pBlockU);
				}
				else
				{
					throw("[DBC_Table_Hash_T::LoadFromMemory]: New memory for BlockU failed!!");
				}
				return false;
			}
		}
		else
		{
			throw("[DBC_Table_Hash_T::LoadFromMemory]: New memory for Node failed!!");
		}

		return true;
	}
	const U * const GetDataByID(tint32 nID) const
	{
		if(true==m_bReady)
		{
			const Slot_T *pSlot = FindSlotByID(nID);
			if(null_ptr!=pSlot)
			{
				return pSlot->GetContent();
			}
		}
		return null_ptr;
	}
	const U * const GetDataByIndex(tint32 nIndex) const
	{
		if(true==m_bReady)
		{
			if(0<=nIndex && m_nCount>nIndex && SEEK_LIST_SIZE>=m_nCount)
			{
				return m_pSeekList[nIndex];
			}
		}
		return null_ptr;
	}
	bool IsReady(void)
	{
		return m_bReady;
	};
	void MarkReadyFlag(void)
	{
		m_bReady=true;
	};
	tint32 GetCount(void) const
	{
		return m_nCount;
	}
protected:
	const Slot_T * LastSlotByHashValue(tuint32 nHash) const
	{
		Slot_T const* pCurrent = m_vpHashList[nHash];
		while(null_ptr!=pCurrent)
		{
			if(null_ptr==pCurrent->GetNext())
			{
				return pCurrent;
			}
			pCurrent = pCurrent->GetNext();
		}
		return null_ptr;
	}
	const Slot_T * FindSlotByID(tint32 nID) const
	{
		tuint32 nHash = Hash(nID);
		if (nHash < 0 || nHash >= HASH_LIST_WIDTH)
			return null_ptr;
		Slot_T const* pCurrent = m_vpHashList[nHash];
		while(null_ptr!=pCurrent)
		{
			if(nID==pCurrent->GetID())
			{
				return pCurrent;
			}
			pCurrent = pCurrent->GetNext();
		}
		return null_ptr;
	}
	bool PushContent(tint32 nIndex, tint32 nID, const U &rContent)
	{
		if(null_ptr==FindSlotByID(nID))
		{
			Node_T* pNode = GetHead();
			if(null_ptr!=pNode)
			{
				Slot_T* pSlotBlock = pNode->GetBlockSlot();
				if(null_ptr!=pSlotBlock)
				{
					Slot_T& rSlot = pSlotBlock[nIndex]; //注意:内部函数不考虑溢出
					tuint32 nHash = Hash(nID);
					if (nHash < 0 || nHash >= HASH_LIST_WIDTH)
						return false;
					rSlot.SetContent(nID, rContent);
					rSlot.SetNext(m_vpHashList[nHash]);
					m_vpHashList[nHash] = &rSlot;
					return true;
				}
				else
				{
					throw("[DBC_Table_Hash_T::PushContent]: SlotBlock is Empty!!");
				}
			}
			else
			{
				throw("[DBC_Table_Hash_T::PushContent]: Head is Empty!!");
			}
		}
		else
		{
			tchar szAlert[256];
			tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Hash_T::PushContent]: Duplicated ID(%d) found!!", nID);
			szAlert[sizeof(szAlert)-1] = '\0';
			throw(szAlert);
		}
	}
	void Release(void)
	{
		m_bReady = false;
		m_nCount = 0;
		for(tint32 nIdx=0; SEEK_LIST_SIZE>nIdx; ++nIdx)
		{
			m_pSeekList[nIdx] = null_ptr;
		}
		for(tint32 nIdx=0; HASH_LIST_WIDTH>nIdx; ++nIdx)
		{
			m_vpHashList[nIdx]=null_ptr;
		}
		Node_T* pNode = GetHead();
		while(null_ptr!=pNode)
		{
			PopBlock();
			U* pBlockU = pNode->GetBlockU();
			if(null_ptr!=pBlockU)
			{
				SAFE_DELETE_ARRAY(pBlockU);
			}
			Slot_T* pBlockSlot = pNode->GetBlockSlot();
			if(null_ptr!=pBlockSlot)
			{
				SAFE_DELETE_ARRAY(pBlockSlot);
			}
			SAFE_DELETE(pNode);
			pNode = GetHead();
		}
		m_pHead	= null_ptr;
	}
	tuint32 Hash(tint32 nID) const
	{
		if(0>nID)
		{
			return (-nID)%HASH_LIST_WIDTH;
		}
		return (+nID)%HASH_LIST_WIDTH;
	}
private:
	void PushBlock(Node_T &rBlockNode)
	{
		rBlockNode.SetNext(m_pHead);
		m_pHead = &rBlockNode;
	}
	Node_T* GetHead(void) const
	{
		return m_pHead;
	}
	void PopBlock(void)
	{
		if(null_ptr!=m_pHead)
		{
			m_pHead = m_pHead->GetNext();
		}
	}
private:
	bool m_bReady;
	Slot_T *m_vpHashList[HASH_LIST_WIDTH];
	U *m_pSeekList[SEEK_LIST_SIZE];
	tint32 m_nCount;
	Node_T *m_pHead;
};

//////////////////////////////////////////////////////////////////////////
//MAX_ID: 最大ID限制
//MAX_RECORD_NUM: 表的最大记录数,现在默认为OXFFFF,使用时调整
//////////////////////////////////////////////////////////////////////////
template<typename U, tint32 MAX_ID, tint32 MAX_RECORD_NUM>
class DBC_Table_Index_T
{
public:
	enum CONSTANT_VALUE
	{
		INDEX_LIST_SIZE = MAX_ID+1,
		UNIT_LIST_SIZE = MAX_RECORD_NUM
	};
	class Node_T
	{
	public:
		U* GetBlock(void) const
		{
			return m_pBlock;
		}
		void SetBlock(U* pBlock)
		{
			m_pBlock = pBlock;
		}
		Node_T* GetNext(void) const
		{
			return m_pNext;
		}
		void SetNext(Node_T* pNode)
		{
			m_pNext = pNode;
		}
	public:
		Node_T(void)
		{
			CleanUp();
		}
		~Node_T(void)
		{
		}
		void CleanUp(void)
		{
			m_pBlock=null_ptr;
			m_pNext=null_ptr;
		}
	private:
		U *m_pBlock;
		Node_T* m_pNext;
	};

public:
	DBC_Table_Index_T()
	{
		m_bReady = false;
		m_nCount = 0;
		for(tint32 nIdx=0; UNIT_LIST_SIZE>nIdx; ++nIdx)
		{
			m_pUnitList[nIdx] = null_ptr;
		}
		for(tint32 nIdx=0; INDEX_LIST_SIZE>nIdx; ++nIdx)
		{
			m_pIndexList[nIdx]=null_ptr;
		}
		m_pHead = null_ptr;
	}
	~DBC_Table_Index_T()
	{
		Release();
	}
	bool Init(void)
	{
		Release();
		return true;
	}
	bool LoadFromMemory(const DBCFile &rDB)
	{
		tchar szAlert[256];
		tint32 nSize = rDB.GetRecordsNum();
		if(0>m_nCount)
		{
			m_nCount = 0;
		}
		if(UNIT_LIST_SIZE<(nSize+m_nCount))
		{
			tchar szAlert[256];
			tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Hash_T::LoadFromMemory]: Record count is larger than UNIT_LIST_SIZE!!");
			szAlert[sizeof(szAlert)-1] = '\0';
			Release();
			throw(szAlert);
			return false;
		}
		//read data
		Node_T* pNode = new Node_T;
		if(null_ptr!=pNode)
		{
			U* pBlock = new U[nSize];
			if(null_ptr!=pBlock)
			{
				pNode->SetBlock(pBlock);
				PushBlock(*pNode);
				{
					//开始读取
					U * pContent = null_ptr;
					for(tint32 nIdx=0; nSize>nIdx; ++nIdx)
					{
						DBCFile::FIELD const* pField = rDB.Search_Posistion(nIdx,0);
						if(null_ptr!=pField)
						{
							tint32 nID = static_cast<tint32>(pField->iValue);
							U& rContent = pBlock[nIdx];
							if(false!=rContent.LoadFromDB(rDB, nIdx))
							{
								if(UNIT_LIST_SIZE>m_nCount)
								{
									m_pUnitList[m_nCount] = &rContent;
									++m_nCount;
									if(INDEX_LIST_SIZE>nID)
									{
										if(null_ptr==m_pIndexList[nID])
										{
											m_pIndexList[nID] = &rContent;
										}
										else
										{
											tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Index_T::LoadFromMemory]: Duplicate Record(%d) found!!", nID);
											szAlert[sizeof(szAlert)-1] = '\0';
											Release();
											throw(szAlert);
											return false;
										}
									}
									else
									{
										tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Index_T::LoadFromMemory]: ID(%d)>MAX_ID over flow!!", nID);
										szAlert[sizeof(szAlert)-1] = '\0';
										Release();
										throw(szAlert);
										return false;
									}
								}
								else
								{
									tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Index_T::LoadFromMemory]: Record count is larger than UNIT_LIST_SIZE!!");
									szAlert[sizeof(szAlert)-1] = '\0';
									Release();
									throw(szAlert);
									return false;
								}
							}
							else
							{
								tsnprintf(szAlert, sizeof(szAlert), "[DBC_Table_Index_T::LoadFromMemory]: load content(%d) failed!!", nID);
								szAlert[sizeof(szAlert)-1] = '\0';
								throw(szAlert);
								return false;
							}
						}
					}
					return true;
				}
			}
			else
			{
				SAFE_DELETE(pNode);
				throw("[DBC_Table_Index_T::LoadFromMemory]: New memory for block failed!!");
				return false;
			}
		}
		else
		{
			throw("[DBC_Table_Index_T::LoadFromMemory]: New memory for node failed!!");
			return false;
		}
		return false;
	}
	const U * const GetDataByID(tint32 nID) const
	{
		if(true==m_bReady)
		{
			if(0<=nID && INDEX_LIST_SIZE>nID)
			{
				return m_pIndexList[nID];
			}
		}
		return null_ptr;
	}
	const U * const GetDataByIndex(tint32 nIndex) const
	{
		if(true==m_bReady)
		{
			if(0<=nIndex && m_nCount>nIndex && UNIT_LIST_SIZE>=m_nCount)
			{
				return m_pUnitList[nIndex];
			}
		}
		return null_ptr;
	}
	bool IsReady(void)
	{
		return m_bReady;
	};
	void MarkReadyFlag(void)
	{
		m_bReady=true;
	};
	tint32 GetCount(void) const
	{
		return m_nCount;
	}
protected:
	void Release(void)
	{
		m_bReady = false;
		m_nCount = 0;
		for(tint32 nIdx=0; UNIT_LIST_SIZE>nIdx; ++nIdx)
		{
			m_pUnitList[nIdx]=null_ptr;
		}
		for(tint32 nIdx=0; INDEX_LIST_SIZE>nIdx; ++nIdx)
		{
			m_pIndexList[nIdx]=null_ptr;
		}
		Node_T* pNode = GetHead();
		while(null_ptr!=pNode)
		{
			PopBlock();
			U* pBlock = pNode->GetBlock();
			if(null_ptr!=pBlock)
			{
				SAFE_DELETE_ARRAY(pBlock);
			}
			SAFE_DELETE(pNode);
			pNode = GetHead();
		}
		m_pHead	= null_ptr;
	}
private:
	void PushBlock(Node_T &rBlockNode)
	{
		rBlockNode.SetNext(m_pHead);
		m_pHead = &rBlockNode;
	}
	Node_T* GetHead(void) const
	{
		return m_pHead;
	}
	void PopBlock(void)
	{
		if(null_ptr!=m_pHead)
		{
			m_pHead = m_pHead->GetNext();
		}
	}
private:
	bool m_bReady;
	U* m_pUnitList[UNIT_LIST_SIZE];
	U* m_pIndexList[INDEX_LIST_SIZE];
	tint32 m_nCount;
	Node_T* m_pHead;
};

class DBC_Loader
{
	template<typename T>
	class __LoadTypeOf
	{
	public:
		typedef tint32 _type;
		static inline T CastFrom(tint32 v)
		{
			return static_cast<T>(v);
		}
	};
private:
	template<typename T>
	static inline void	Read(T& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn)
	{
		typename __LoadTypeOf<T>::_type v;
		_Read(v,rDB,nRow,nColumn);
		val=__LoadTypeOf<T>::CastFrom(v);
	}
private:
	static void	_Read(tint32& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn);
	static void	_Read(tfloat32& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn);
	static void	_Read(const tchar* & val,const DBCFile& rDB, tint32 nRow, tint32 nColumn);
	static void	_Read(bool& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn);
public:
	DBC_Loader(const DBCFile& rDB, tint32 nRow):m_DB(rDB)
	{
		m_Row=nRow;
		m_Column=0;
	}
	template<typename T>
	inline void ReadNext(T& val)
	{
		Read(val,m_DB,m_Row,m_Column++);
	}
	template<typename T>
	inline void ReadDirect(T& val, tint32 nColumn)
	{
		Read(val,m_DB,m_Row,nColumn);
	}
	inline void	Skip(void)
	{
		++m_Column;
	}
	inline void Skip(tint32 recordNum)
	{
		m_Column+=recordNum;
	}
	inline void MoveTo(tint32 recordPos)
	{
		m_Column=recordPos;
	}
	inline tint32 GetRow()
	{
		return m_Row;
	}
	inline tint32 GetColumn()
	{
		return m_Column;
	}
	inline tint32 GetFieldsNum()
	{
		return m_DB.GetFieldsNum();
	}
private://禁止拷贝与赋值
	DBC_Loader(const DBC_Loader&);
	DBC_Loader& operator= (const DBC_Loader&);
private:
	const DBCFile	&m_DB;
	tint32			m_Row;
	tint32			m_Column;
};

template<>
class DBC_Loader::__LoadTypeOf<tfloat32>
{
public:
	typedef tfloat32 _type;
	static inline tfloat32 CastFrom(tfloat32 v)
	{
		return v;
	}
};
template<>
class DBC_Loader::__LoadTypeOf<const tchar*>
{
public:
	typedef const tchar* _type;
	static inline const tchar* CastFrom(const tchar* v)
	{
		return v;
	}
};
template<>
class DBC_Loader::__LoadTypeOf<tchar*>
{
public:
	typedef const tchar* _type;
	static inline tchar* CastFrom(const tchar* v)
	{
		return const_cast<tchar*>(v);
	}
};
template<>
class DBC_Loader::__LoadTypeOf<bool>
{
public:
	typedef bool _type;
	static inline bool CastFrom(bool v)
	{
		return v;
	}
};

//此模板类用作基类，但只用于提供实现代码，不应用作抽象类，所以析构不是虚函数。
template<typename SubclassT,tint32 maxID,tint32 maxRecordNum>
class DBC_Recorder_Loader
{
public:
	enum
	{
		MAX_ID = maxID,
		MAX_RECORD_NUM = maxRecordNum,
	};
public:
	DBC_Recorder_Loader(void)
	{
		m_bInited = false;
	}
public:
	inline bool IsInited(void) const
	{
		return m_bInited;
	}
	inline bool InitFromDB(DBCFile const& rDB, tint32 const nRow)
	{
		return LoadFromDB(rDB,nRow);
	}
	inline bool LoadFromDB(DBCFile const& rDB, tint32 const nRow)
	{
		DBC_Loader loader(rDB,nRow);
		SubclassT* pThis=static_cast<SubclassT*>(this);
		bool ret=pThis->__Load(loader);
		if(false==ret)
			return false;
		m_bInited=true;
		return true;
	}
private:
	bool m_bInited;
};

#define __DECL_COMMON_TABLE_FUNCTIONS(theClass,theName)	\
bool Init##theName##Table( const tchar* szFileName ); \
bool Init##theName##TableFromMemory( const DBCFile& rDB ); \
const theClass* Get##theName##ByID(tint32 id); \
const theClass* Get##theName##ByIndex(tint32 index); \
tint32 Get##theName##Count(void);

#define DECL_TABLE_FUNCTIONS(theClass) __DECL_COMMON_TABLE_FUNCTIONS(theClass,theClass)

template<typename T,tint32 k,tint32 m>		
class SequenceMgrType
{
public:
	typedef DBC_Table_Index_T<T,k,m> Type;		
};

template<typename T,tint32 k,tint32 m>		
class HashMgrType
{
public:
	typedef DBC_Table_Hash_T<T,k,m> Type;
};

template<template<typename T1,tint32 k,tint32 m> class MgrT,typename T,tint32 maxID,tint32 maxRecordNum>		
class DBC_Table_Mgr_Adapter
{
public:
	inline bool InitFromDB(const tchar* szFileName);
	inline bool InitFromDBMemory(const DBCFile& rDB);
	inline const T* GetRecordByID(tint32 id);
	inline const T* GetRecordByIndex(tint32 index);
	inline tint32 GetCount(void);
};

template<typename T,tint32 maxID,tint32 maxRecordNum>
class DBC_Table_Mgr_Adapter<SequenceMgrType,T,maxID,maxRecordNum>
{
public:
	inline bool InitFromDB(const tchar* szFileName)
	{
		DBCFile dbcFile;
		if(false==dbcFile.OpenFromTXT(szFileName))
			return false;
		return InitFromDBMemory(dbcFile);
	}
	inline bool InitFromDBMemory(const DBCFile& rDB)
	{
		if(true==m_Mgr.IsReady())
		{
			m_Mgr.Init();
		}
		if(!m_Mgr.LoadFromMemory(rDB))
		{
			return false;
		}
		m_Mgr.MarkReadyFlag();
		return true;
	}
	inline const T* GetRecordByID(tint32 id)
	{
		return m_Mgr.GetDataByID(id);
	}
	inline const T* GetRecordByIndex(tint32 index)
	{
		return m_Mgr.GetDataByIndex(index);
	}
	inline tint32 GetCount(void)
	{
		return m_Mgr.GetCount();
	}
private:
	typename SequenceMgrType<T,maxID,maxRecordNum>::Type m_Mgr;
};

template<typename T,tint32 nHashsize,tint32 maxRecordNum>
class DBC_Table_Mgr_Adapter<HashMgrType,T,nHashsize,maxRecordNum>
{
public:
	inline bool InitFromDB(const tchar* szFileName)
	{
		DBCFile dbcFile;
		if(false==dbcFile.OpenFromTXT(szFileName))
			return false;
		return InitFromDBMemory(dbcFile);
	}
	inline bool InitFromDBMemory(const DBCFile& rDB)
	{
		if(true==m_Mgr.IsReady())
		{
			m_Mgr.Init();
		}
		if(!m_Mgr.LoadFromMemory(rDB))
		{
			return false;
		}
		m_Mgr.MarkReadyFlag();
		return true;
	}
	inline const T* GetRecordByID(tint32 id)
	{
		return m_Mgr.GetDataByID(id);
	}
	inline const T* GetRecordByIndex(tint32 index)
	{
		return m_Mgr.GetDataByIndex(index);
	}
	inline tint32 GetCount(void)
	{
		return m_Mgr.GetCount();
	}
private:
	typename HashMgrType<T,nHashsize,maxRecordNum>::Type m_Mgr;
};

//定义数据表的初始化函数与按记录顺序读取记录的全局函数，此宏应用在CPP文件中，并且该文件需要包含头文件DBC_Table.h
#define __DEFINE_COMMON_TABLE_FUNCTIONS(mgrClass,theClass,maxID,maxRecordNum,theName) \
typedef DBC_Table_Mgr_Adapter<mgrClass,theClass,maxID,maxRecordNum> theName##Mgr; \
static theName##Mgr g_##theName##Mgr; \
bool Init##theName##Table( const tchar* szFileName ) \
{ \
	__ENTER_FUNCTION \
	return g_##theName##Mgr.InitFromDB(szFileName); \
	__LEAVE_FUNCTION \
	return false; \
} \
bool Init##theName##TableFromMemory(DBCFile const& rDB ) \
{ \
	__ENTER_FUNCTION \
	return g_##theName##Mgr.InitFromDBMemory(rDB); \
	__LEAVE_FUNCTION \
	return false; \
} \
theClass const* Get##theName##ByID(tint32 id) \
{ \
	__ENTER_FUNCTION \
	return g_##theName##Mgr.GetRecordByID(id); \
	__LEAVE_FUNCTION \
	return null_ptr; \
} \
theClass const* Get##theName##ByIndex(tint32 index) \
{ \
	__ENTER_FUNCTION \
	return g_##theName##Mgr.GetRecordByIndex(index); \
	__LEAVE_FUNCTION \
	return null_ptr; \
} \
tint32 Get##theName##Count(void) \
{ \
	__ENTER_FUNCTION \
	return g_##theName##Mgr.GetCount(); \
	__LEAVE_FUNCTION \
	return 0; \
}

#define DEFINE_SEQUENCE_TABLE_FUNCTIONS(theClass)	__DEFINE_COMMON_TABLE_FUNCTIONS(SequenceMgrType,theClass,theClass::MAX_ID,theClass::MAX_RECORD_NUM,theClass)
#define DEFINE_HASH_TABLE_FUNCTIONS(theClass)	__DEFINE_COMMON_TABLE_FUNCTIONS(HashMgrType,theClass,theClass::MAX_ID,theClass::MAX_RECORD_NUM,theClass)

#endif