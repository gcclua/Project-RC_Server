#include "DBCTable.h"

tint32	DBCFile::_ConvertStringToVector(const char* strStrINTgSource, bsvector< std::string >& vRet, const char* szKey, bool bOneOfKey, bool bIgnoreEmpty)
{
	vRet.clear();
	
	std::string strSrc = strStrINTgSource;
	if(strSrc.empty())
	{
		return 0;
	}

	std::string::size_type nLeft = 0;
	std::string::size_type nRight;
	if(bOneOfKey)
	{
		nRight = strSrc.find_first_of(szKey);
	}
	else
	{
		nRight = strSrc.find(szKey);
	}

	if(nRight == std::string::npos)
	{
		nRight = strSrc.length();
	}
	while(true)
	{
		std::string strItem = strSrc.substr(nLeft, nRight-nLeft);
		if(strItem.length() > 0 || !bIgnoreEmpty)
		{
			vRet.push_back(strItem);
		}

		if(nRight == strSrc.length())
		{
			break;
		}

		nLeft = nRight + (bOneOfKey ? 1 : strlen(szKey));
		
		if(bOneOfKey)
		{
			std::string strTemp = strSrc.substr(nLeft);
			nRight = strTemp.find_first_of(szKey);
			if(nRight != std::string::npos) nRight += nLeft;
		}
		else
		{
			nRight = strSrc.find(szKey, nLeft);
		}

		if(nRight == std::string::npos)
		{
			nRight = strSrc.length();
		}
	}

	return (int)vRet.size();
}


DBCFile::DBCFile()
{
	m_nRecordsNum = 0;
	m_nFieldsNum  = 0;
	m_pStringBuf  = null_ptr;
	m_nStringBufSize = 0;
}

DBCFile::~DBCFile()
{
	SAFE_DELETE_ARRAY(m_pStringBuf);
}

//从内存中字符串读取一行文本(按照换行符)
const char* DBCFile::_GetLineFromMemory(char* pStringBuf, int nBufSize, const char* pMemory, const char* pDeadEnd)
{
	//寻找下一个换行符
    const char* pMem = pMemory;
	if(pMem >= pDeadEnd || *pMem==0) return 0;

	while(pMem < pDeadEnd && pMem-pMemory+1<nBufSize && 
			*pMem != 0 && *pMem != '\r' && *pMem != '\n') *(pStringBuf++) = *(pMem++);
	//add 'null' end
	*pStringBuf = 0;

	//skip all next \r and \n
	while(pMem < pDeadEnd && *pMem != 0 && (*pMem=='\r' || *pMem=='\n')) pMem++;

	return pMem;
}

bool DBCFile::OpenFromMemory(const char* pMemory, const char* pDeadEnd, const char* szFileName)
{
	AssertEx(pMemory != null_ptr,"");
	AssertEx(pDeadEnd != null_ptr,"");
	//----------------------------------------------------
	//判断是否是二进制格式
	if(pDeadEnd - pMemory >=sizeof(FILE_HEAD) && *((tuint32*)pMemory)==0XDDBBCC00)
	{
		return OpenFromMemoryImpl_Binary(pMemory, pDeadEnd, szFileName);
	}
	else
	{
		return OpenFromMemoryImpl_Text(pMemory, pDeadEnd, szFileName);
	}
}

bool DBCFile::OpenFromMemoryImpl_Binary(const char* pMemory, const char* pDeadEnd, const char* szFileName)
{
	const char* pMem = pMemory;

	//----------------------------------------------------
	//Read Head
	FILE_HEAD theHead;
	memcpy(&theHead, pMem, sizeof(FILE_HEAD));
	if(theHead.m_Identify != 0XDDBBCC00 )
	{
		return false;
	}
	//check memory size
	if(	sizeof(FILE_HEAD) + 
		sizeof(tuint32)*theHead.m_nFieldsNum + 
		sizeof(FIELD)*theHead.m_nRecordsNum * theHead.m_nFieldsNum +
		theHead.m_nStringBlockSize > (tuint32)(pDeadEnd-pMemory))
	{
		return false;
	}

	pMem += sizeof(FILE_HEAD);

	//----------------------------------------------------
	//Init 
	m_nRecordsNum = theHead.m_nRecordsNum;
	m_nFieldsNum  = theHead.m_nFieldsNum;
	m_nStringBufSize = theHead.m_nStringBlockSize;

	//---------------------------------------------
	//Create String Blok
	m_pStringBuf = new char[theHead.m_nStringBlockSize];
	if(!m_pStringBuf) return false;

	//------------------------------------------------------
	// Read Field Types
	bsvector< tuint32 > vFieldType;
	vFieldType.resize(m_nFieldsNum);
	memcpy(&(vFieldType[0]), pMem, sizeof(tuint32)*m_nFieldsNum);
	pMem += sizeof(tuint32)*m_nFieldsNum;

	//Check it!
	m_theType.resize(m_nFieldsNum);
	for(int i=0; i<(int)m_nFieldsNum; i++)
	{
		switch(vFieldType[i])
		{
		case T_INT:
		case T_FLOAT:
		case T_STRING:
			m_theType[i] = (FIELD_TYPE)vFieldType[i];
			break;

		default:
			delete[] (m_pStringBuf);
			return false;
		}
	}

	//------------------------------------------------------
	// Read All Field
	m_vDataBuf.resize(theHead.m_nRecordsNum * m_nFieldsNum);
	memcpy(&(m_vDataBuf[0]), pMem, sizeof(FIELD)*theHead.m_nRecordsNum * m_nFieldsNum);
	pMem += sizeof(FIELD)*theHead.m_nRecordsNum * m_nFieldsNum;

	//------------------------------------------------------
	// Read String Block
	memcpy(m_pStringBuf, pMem, m_nStringBufSize);
	m_pStringBuf[m_nStringBufSize-1]=0;

	//------------------------------------------------------
	// TO runtime address
	for(int j=0; j<(int)m_nFieldsNum; j++)
	{
		if(vFieldType[j] != T_STRING) continue;

		for(int i=0; i<(int)theHead.m_nRecordsNum; i++)
		{
			
			m_vDataBuf[i*GetFieldsNum()+j].pString += reinterpret_cast<unsigned long long>(m_pStringBuf);
		}
	}

	//------------------------------------------------------
	//生成索引列
	CheckIndex(szFileName);

	return true;
}

bool DBCFile::OpenFromMemoryImpl_Text(const char* pMemory, const char* pDeadEnd, const char* szFileName)
{
	//----------------------------------------------------
	//分析列数和类型
	const int MAX_LINE_BYTES = 1024 * 64;
	char szLine[MAX_LINE_BYTES] = {0};
	//读第一行
    const char* pMem = pMemory;
	pMem = _GetLineFromMemory(szLine, MAX_LINE_BYTES, pMem, pDeadEnd);
	if(!pMem) return false;

	pMem = _GetLineFromMemory(szLine, MAX_LINE_BYTES, pMem, pDeadEnd);
	if(!pMem) return false;

	//分解
	bsvector< std::string > vRet;
	_ConvertStringToVector(szLine, vRet, "\t", true, true);
	if(vRet.empty()) return false;

	//--------------------------------------------------------------
	//初始化
	int nRecordsNum	= 0;
	int nFieldsNum	= (int)vRet.size();


	//生成Field Types
	FIELD_TYPE_VEC vFieldsType;
	vFieldsType.resize(nFieldsNum);

	

	for(int i=0; i<(int)nFieldsNum; i++) 
	{
		if(vRet[i] == "INT") vFieldsType[i] = T_INT;
		else if(vRet[i] == "FLOAT") vFieldsType[i] = T_FLOAT;
		else if(vRet[i] == "STRING") vFieldsType[i] = T_STRING;
		else
		{
			return false;
		}
	}

	

	//临时字符串区
	bsvector< std::pair< std::string, int > >	vStringBuf;
	//检索表
	std::map< std::string, int >					mapStringBuf;

	//--------------------------------------------------------------
	//开始读取

	//空读一行
	pMem = _GetLineFromMemory(szLine, MAX_LINE_BYTES, pMem, pDeadEnd);
	if(!pMem) return false;

	pMem = _GetLineFromMemory(szLine, MAX_LINE_BYTES, pMem, pDeadEnd);
	if(!pMem) return false;

	int nStringBufSize = 0;
	do
	{
		//读取一行
		pMem = _GetLineFromMemory(szLine, MAX_LINE_BYTES, pMem, pDeadEnd);
		if(!pMem) break;;

		//是否是注释行
		if(szLine[0] == '#') continue;

		//分解
		_ConvertStringToVector(szLine, vRet, "\t", true, false);

		//列数不对
		if(vRet.empty()) continue;
        if(vRet.size() != nFieldsNum) 
		{
			//补上空格
			if((int)vRet.size() < nFieldsNum)
			{
				int nSubNum = nFieldsNum-(int)vRet.size();
				for(int i=0; i<nSubNum; i++)
				{
					vRet.push_back("");
				}
			}
		}

		//第一列不能为空
		if(vRet[0].empty()) continue;

		for(register int i=0; i<nFieldsNum; i++)
		{
			FIELD newField;
			switch(vFieldsType[i])
			{
			case T_INT:
				newField.iValue = (tintptr)atol(vRet[i].c_str());
				m_vDataBuf.push_back(newField);
				break;

			case T_FLOAT:
				newField.fValue = (tfloatptr)atof(vRet[i].c_str());
				m_vDataBuf.push_back(newField);
				break;

			case T_STRING:
				if(vRet[i].empty())
				{
					newField.iValue = 0;
				}
				else
				{
					const char * p = vRet[i].c_str();
					std::map< std::string, int >::iterator it = mapStringBuf.find(vRet[i]);
					if(it == mapStringBuf.end())
					{
						vStringBuf.push_back(std::make_pair(vRet[i], nStringBufSize));
						mapStringBuf.insert(std::make_pair(vRet[i], (int)vStringBuf.size()-1));
						newField.iValue = nStringBufSize + 1; // first char is '\0' for blank string
	
						nStringBufSize += (int)strlen(vRet[i].c_str()) + 1;
					}
					else
					{
						newField.iValue = vStringBuf[it->second].second + 1;
					}
				}

				m_vDataBuf.push_back(newField);
				break;
			}
		}

		nRecordsNum++;
	}while(true);

	//--------------------------------------------------------
	//生成正式数据库
	m_nRecordsNum = nRecordsNum;
	m_nFieldsNum  = nFieldsNum;
	m_nStringBufSize = nStringBufSize+1;

	//Create String Blok
	m_pStringBuf = new char[m_nStringBufSize];
	if(m_pStringBuf == null_ptr) 
	{
		return false;
	}

	//------------------------------------------------------
	// Create Field Types
	m_theType = vFieldsType;

	//------------------------------------------------------
	// Create String Block
	tbyte byBlank = '\0';
	m_pStringBuf[0] = '\0';

	char* p = m_pStringBuf + 1;
	for(int i=0; i<(int)vStringBuf.size(); i++)
	{
		memcpy(p, vStringBuf[i].first.c_str(), vStringBuf[i].first.size());	
		p += vStringBuf[i].first.size();

		*(p++) = '\0';
	}

	//------------------------------------------------------
	// Relocate String Block
	for(register int i=0; i<nFieldsNum; i++)
	{
		if(vFieldsType[i] != T_STRING) continue;

		for(register int j=0; j<nRecordsNum; j++)
		{
			FIELD& theField = m_vDataBuf[j*nFieldsNum+i];
			theField.pString = m_pStringBuf + theField.iValue;
		}
	}

	//------------------------------------------------------
	//生成索引列
	CheckIndex(szFileName);

	return true;
}

bool DBCFile::OpenFromTXT(const char* szFileName)
{
	AssertEx(szFileName != null_ptr,"");

	//----------------------------------------------------
	//打开文件
	FILE* fp = fopen(szFileName, "rb");
	if(null_ptr == fp) return false;

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//读入内存
	char* pMemory = new char[nFileSize+1];
	fread(pMemory, 1, nFileSize, fp);
	pMemory[nFileSize] = 0;
	fclose(fp);
	fp = null_ptr;

	bool bRet = OpenFromMemory(pMemory, pMemory+nFileSize+1, szFileName);

	SAFE_DELETE_ARRAY(pMemory);

	return bRet;
}

void DBCFile::CheckIndex(const char* szFileName)
{
	std::set<tintptr> IndexSet;
	

	for(int i=0; i<(int)m_nRecordsNum; i++)
	{
		FIELD* p = &(m_vDataBuf[i*m_nFieldsNum]);
		AssertEx(p != null_ptr,"");


		std::set<tintptr>::iterator itFind = IndexSet.find(p->iValue);
		if(itFind != IndexSet.end())
		{
			char szTemp[260];
			tsnprintf(szTemp, 260, "[%s]Multi index at line %d(SAME:value=%d)", szFileName, i+1, p->iValue);
			AssertEx(false,szTemp);
			return;
		}
		IndexSet.insert(p->iValue);
	}
}


const DBCFile::FIELD* DBCFile::Search_Posistion(int nRecordLine, int nColumNum) const
{
	int nPosition = nRecordLine*GetFieldsNum() + nColumNum;

	if(nPosition <0 || nColumNum >= (int)m_vDataBuf.size()) 
	{
		char szTemp[260];
		tsnprintf(szTemp, sizeof(szTemp)-1, "DBC:Invalid search request[rec=%d, col=%d]", nRecordLine, nColumNum);
		throw std::string(szTemp);
		return null_ptr;
	}

	return &(m_vDataBuf[nPosition]);
}


class  DBC_String_T
{
private:
	enum CONSTANT_VALUE
	{
		HASH_WIDTH = 8 * 1024,
		MAGICWORD  = 0xFEEDFEED,
		STRING_BLOCK_SIZE = 32 * 1024,
		CHAR_BLOCK_SIZE   = 2048 * 1024,
	};

	class  String_T
	{
	public:
		String_T* GetNext(void) const {return m_pNext;}
		void      SetNext(String_T* pNext) {m_pNext = pNext;}

		const char* GetContent(void) const {return m_pContent;}
		void        SetContent(const char* pContent){m_pContent = pContent;}

		tuint32      GetHashValue(void) {return m_nHashValue;}
		void         SetHashValue(tuint32 nValue) {m_nHashValue=nValue;}

		tuint32      GetStringLength(void) const {return m_nStrlen;}
		void         SetStringLength(tuint32 nLength) {m_nStrlen = nLength;}
	public:
		String_T(void):m_pNext(null_ptr),m_pContent(null_ptr),m_nHashValue(0),m_nStrlen(0){};
		~ String_T(){CleanUp();}

		bool IsMe(const char* szString,tuint32 nHashValue,tuint32 nLength)
		{
			if (nLength == m_nStrlen && szString)
			{
				if (nHashValue == m_nHashValue)
				{
					if (tstricmp(szString,m_pContent) == 0)
					{
						return true;
					}
				}
			}
			return false;
		}

		void CleanUp(void)
		{
			m_pNext      = null_ptr;
			m_pContent   = null_ptr;
			m_nHashValue = 0;
			m_nStrlen    = 0;
		}

	private:
		String_T*  m_pNext;
		const char* m_pContent;
		tuint32    m_nHashValue;
		tuint32    m_nStrlen;
	};
	
	class StringTBlockNode_T
	{
	public:
		StringTBlockNode_T* GetNext(void) const {return m_pNext;}
		void                SetNext(StringTBlockNode_T* pNext){m_pNext = pNext;}

		String_T*           GetBlock(void) const {return m_pBlock;}
		void                SetBlock(String_T* pBlock){m_pBlock = pBlock;}

		tuint32             GetUserSlotCount(void) const {m_nUserdSlotCount;}
		void                SetUserSlotCount(tuint32 nCount){m_nUserdSlotCount = nCount;}

		bool    IsUnited(void) const
		{
			return null_ptr != m_pBlock;
		}

		String_T* GetAvaildSlot(void) const
		{
			if (null_ptr != m_pBlock && STRING_BLOCK_SIZE>m_nUserdSlotCount)
			{
				return &(m_pBlock[m_nUserdSlotCount]);
			}
			return null_ptr;
		}

		void StepForwardCursor(void)
		{
			if (null_ptr != m_pBlock && STRING_BLOCK_SIZE > m_nUserdSlotCount)
			{
				++m_nUserdSlotCount;
			}
		}

	public:
		StringTBlockNode_T(void):m_pNext(null_ptr),m_pBlock(null_ptr),m_nUserdSlotCount(0){};
		~StringTBlockNode_T(void){CleanUp();}
		void CleanUp(void) {m_pBlock = null_ptr; m_pNext = null_ptr;}

	private:
		StringTBlockNode_T* m_pNext;
		String_T*           m_pBlock;
		tuint32             m_nUserdSlotCount;

	};

	class  CharBlockNode_T
	{
	public:
		CharBlockNode_T*   GetNext(void) const {return m_pNext;}
		void               SetNext(CharBlockNode_T* pNext){m_pNext = pNext;}

		char*              GetBlock(void) const {return m_pBlock;}
		void               SetBlock(char* pBlock){m_pBlock = pBlock;}

		tuint32            GetUsedSize(void) const {return m_nUsedSize;}
		void               SetUsedSize(tuint32 nSize) {m_nUsedSize = nSize;}

		char*              GetAvaildBuffer(tuint32 nStrLen) const
		{
			char* pBuffer = null_ptr;
			tuint32 nBufferSize = ((nStrLen+1)/2+2)*2;
			if (null_ptr != m_pBlock && CHAR_BLOCK_SIZE >(m_nUsedSize+nBufferSize))
			{
				pBuffer = &(m_pBlock[m_nUsedSize]);
				memset(pBuffer,'\0',nBufferSize); // 清空缓冲区
			}
			return pBuffer;
		}

		void StepForwardCursor(tuint32 nStrLen)
		{
			tuint32 nBufferSize = ((nStrLen+1)/2+2)*2;
			if (null_ptr != m_pBlock && CHAR_BLOCK_SIZE >(m_nUsedSize+nBufferSize))
			{
				m_nUsedSize += nBufferSize;
			}
		}

	public:
		 CharBlockNode_T():m_pNext(null_ptr),m_pBlock(null_ptr),m_nUsedSize(0){};;
		 ~ CharBlockNode_T(){CleanUp();}
		void CleanUp(void){m_pNext = null_ptr;m_pBlock = null_ptr; m_nUsedSize = 0;}

	private:
		CharBlockNode_T* m_pNext;
		char*            m_pBlock;
		tuint32          m_nUsedSize;
	};
public:
	tuint32 GetCount(void) const {return m_nCount;}
	tuint32 GetTotalSize(void) const {return m_nTotalSize;}
	const char* RegisterConstString(const char* szString,tuint32 nLength)
	{
		const char* pReturn = null_ptr;
		if (null_ptr != szString)
		{
			if (nLength == strlen(szString))
			{
				bstMutexScopedLock LockGuard(m_Lock);
				pReturn = GetSameString(szString,nLength);
				if (null_ptr == pReturn)
				{
					char* pBlock = NewStringBuffer(nLength);
					if (null_ptr != pBlock)
					{
						strncpy(pBlock,szString,nLength);
						pBlock[nLength] = '\0';
						String_T* pSlot = NewStringTStruct();
						if (null_ptr != pSlot)
						{
							tuint32 nHashValue = GetHashValue(szString,nLength);
							tuint32 nHashIndex = GetHashIndex(nHashValue);
							AssertEx(nHashIndex>=0 && nHashIndex<HASH_WIDTH,"");

							pSlot->SetNext(m_apHashHeadList[nHashIndex]);
							pSlot->SetContent(pBlock);
							pSlot->SetHashValue(nHashValue);
							pSlot->SetStringLength(nLength);
							m_apHashHeadList[nHashIndex] = pSlot;

							++m_nCount;
							m_nTotalSize += nLength;

							if (null_ptr != m_pStringBLockHead)
							{
								m_pStringBLockHead->StepForwardCursor();
							}
							if (null_ptr != m_pCharBlockHead)
							{
								m_pCharBlockHead->StepForwardCursor(nLength);
							}
							pReturn = pSlot->GetContent();
						}
					}
				}
			}
		}
		return pReturn;
	}
public:
	DBC_String_T(void)
	{
		bstMutexScopedLock LockGuard(m_Lock);
		for (tuint32 nIdx = 0;nIdx <HASH_WIDTH;++nIdx)
		{
			m_apHashHeadList[nIdx] = null_ptr;
		}
		m_pStringBLockHead = null_ptr;
		m_pCharBlockHead   = null_ptr;
		m_nCount = 0;
		m_nTotalSize = 0;
	}
	~DBC_String_T()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		bstMutexScopedLock LockGuard(m_Lock);
		for (int nIdx = 0; nIdx<HASH_WIDTH; ++nIdx)
		{
			m_apHashHeadList[nIdx] = null_ptr;
		}
		{
			StringTBlockNode_T* pNextBlock = m_pStringBLockHead;
			while (null_ptr != pNextBlock)
			{
				m_pStringBLockHead = pNextBlock->GetNext();
				String_T* pBlock = pNextBlock->GetBlock();
				if (null_ptr != pBlock)
				{
					SAFE_DELETE_ARRAY(pBlock);
				}
				SAFE_DELETE(pNextBlock);
				pNextBlock = m_pStringBLockHead;
			}
		}

		{
			CharBlockNode_T* pNextBlock = m_pCharBlockHead;
			while (null_ptr != pNextBlock)
			{
				m_pCharBlockHead = pNextBlock->GetNext();
				char* pBlock = pNextBlock->GetBlock();
				if (null_ptr != pBlock)
				{
					SAFE_DELETE_ARRAY(pBlock);
				}
				SAFE_DELETE(pNextBlock);
				pNextBlock = m_pCharBlockHead;
			}
		}

		m_nCount = 0;
		m_nTotalSize = 0;
	}
private:
	tuint32 GetHashIndex(tuint32 nHashValue)
	{
		return nHashValue % HASH_WIDTH;
	}

	tuint32  GetHashValue(const char* szString,tuint32 nLength)
	{
		tuint32 seed1 = 0x7FED7FED;
		tuint32 seed2 = 0xEEEEEEEE;
		for (tuint32 nIdx = 0; nLength>nIdx; ++nIdx)
		{
			tuint32 nChar = static_cast<tbyte>(szString[nIdx]);
			tuint32 nValue = nChar<<(8*(nIdx%sizeof(tuint32)));
			seed1 = nValue^(seed1 + seed2);
			seed2 = nChar + seed1 + seed2 + (seed2<<5) + 3;
		}

		return seed1;
	}

	const char* GetSameString(const char* szString,tuint32 nLength)
	{
		tuint32 nHashValue = GetHashValue(szString,nLength);
		tuint32 nHashIndex = GetHashIndex(nHashValue);

		AssertEx(nHashIndex >=0 && nHashIndex < HASH_WIDTH,"");
		
		String_T* pNext = m_apHashHeadList[nHashIndex];
		while (null_ptr != pNext)
		{
			if (pNext->IsMe(szString,nHashValue,nLength))
			{
				return pNext->GetContent();
			}

			// 防止空指针检查报错
			String_T* pTemp = pNext;
			AssertEx(pTemp,"");
			pNext = pTemp->GetNext();
		}
		return null_ptr;
	}

	String_T* NewStringTStruct(void)
	{
		String_T* pReturn = null_ptr;
		StringTBlockNode_T* pBlockNode = m_pStringBLockHead;
		if (null_ptr != pBlockNode)
		{
			pReturn = pBlockNode->GetAvaildSlot();
		}
		if (null_ptr == pReturn)
		{
			StringTBlockNode_T* pNode = null_ptr;
			String_T* pBlock = null_ptr;
			try
			{
				pNode = new StringTBlockNode_T;
				pBlock = new String_T[STRING_BLOCK_SIZE];
			}
			catch (...)
			{
				
			}
			if (null_ptr != pNode && null_ptr != pBlock)
			{
				pNode->SetBlock(pBlock);
				pNode->SetNext(m_pStringBLockHead);
				m_pStringBLockHead = pNode;
				pReturn = pNode->GetAvaildSlot();
			}
			else
			{
				if (null_ptr != pNode)
				{
					SAFE_DELETE(pNode);
				}

				if (null_ptr != pBlock)
				{
					SAFE_DELETE_ARRAY(pBlock);
				}
			}
			
		}
		return pReturn;
	}

	char* NewStringBuffer(tuint32 nStrLen)
	{
		char* pReturn = null_ptr;
		CharBlockNode_T* pBlockNode = m_pCharBlockHead;
		if (null_ptr != pBlockNode)
		{
			pReturn = pBlockNode->GetAvaildBuffer(nStrLen);
		}
		if (null_ptr == pReturn)
		{
			CharBlockNode_T* pNode = null_ptr;
			char* pBlock = null_ptr;
			try
			{
				pNode = new CharBlockNode_T;
				pBlock = new char[CHAR_BLOCK_SIZE];
			}
			catch (...)
			{
				
			}
			if (null_ptr != pNode && null_ptr != pBlock)
			{
				pNode->SetBlock(pBlock);
				pNode->SetNext(m_pCharBlockHead);
				m_pCharBlockHead = pNode;
				pReturn = pNode->GetAvaildBuffer(nStrLen);
			}
			else
			{
				if (null_ptr != pNode)
				{
					SAFE_DELETE(pNode);
				}
				if (null_ptr != pBlock)
				{
					SAFE_DELETE_ARRAY(pBlock);
				}
			}
		}
		return pReturn;
	}

private:
	bstMutex m_Lock;
	String_T* m_apHashHeadList[HASH_WIDTH];
	StringTBlockNode_T* m_pStringBLockHead;
	CharBlockNode_T*    m_pCharBlockHead;

	tuint32             m_nCount; // 实际条目数
	tuint32				m_nTotalSize; // 字节数
};


static DBC_String_T g_DBC_CString_Table;
static const char* szEmpty = "";

const char* _LoadConstStringFromDBC(const DBCFile &rDB,int nRow,int nColumn)
{
	if (0<=nRow && 0<=nColumn)
	{
		const char* szEmpty = null_ptr;
		szEmpty = rDB.Search_Posistion(nRow,nColumn)->pString;
		if (null_ptr != szEmpty)
		{
			tuint32 nStringLength = static_cast<tuint32>(strlen(szEmpty));
			if (0<nStringLength)
			{
				return  g_DBC_CString_Table.RegisterConstString(szEmpty,nStringLength);
			}
		}
	}
	return null_ptr;
}

static void	_Read(bool& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn);
void DBC_Loader::_Read(tint32& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn)
{
	const DBCFile::FIELD* pField = rDB.Search_Posistion(nRow,nColumn);
	if (pField != null_ptr)
	{
		val = static_cast<tint32>(pField->iValue);
	}
}

void DBC_Loader::_Read(tfloat32& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn)
{
	const DBCFile::FIELD* pField = rDB.Search_Posistion(nRow,nColumn);
	if (pField != null_ptr)
	{
		val = static_cast<tfloat32>(pField->fValue);
	}
}

void DBC_Loader::_Read(const tchar* &  val,const DBCFile& rDB, tint32 nRow, tint32 nColumn)
{
	val = _LoadConstStringFromDBC(rDB,nRow,nColumn);
}

void DBC_Loader::_Read(bool& val,const DBCFile& rDB, tint32 nRow, tint32 nColumn)
{
	const DBCFile::FIELD* pField = rDB.Search_Posistion(nRow,nColumn);
	if (pField != null_ptr)
	{
		if (pField->iValue != 0)
		{
			val = true;
		}
		else
		{
			val = false;
		}
	}
}