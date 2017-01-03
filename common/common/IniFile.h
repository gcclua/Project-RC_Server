#ifndef _INIFILE_H_
#define _INIFILE_H_

/*
ini文件读取功能，非线程安全
*/

#include "BaseType.h"
#include "BaseLib.h"

class IniFile
{
public:
	IniFile(void);
	~IniFile(void);

public:
	bool	ReadInt(const tchar* index, const tchar* name, tint32& rResult);
	bool	ReadUInt(const tchar* index, const tchar* name, tuint32& rResult);
	bool	ReadFloat(const tchar* index, const tchar* name, tfloat32& rResult);
	bool	ReadText(const tchar* index, const tchar* name, tchar* str, tint32 size);
public:
	bool	Open(const tchar* filename);

private:
	void	InitIndex(void);
	tint32	FindIndex(const tchar* string);
	tint32	FindData(tint32 index, const tchar* string);
	tint32	GotoNextLine(tint32 p);
	bool	ReadDataName(tint32 &p, tchar* szBuffer, tint32 nBufferSize);
	bool	ReadText(tint32 p, tchar* pBuffer, tint32 nBufferSize);

private:
	tchar			m_szFileName[256];
	tint32			m_nFileSize;
	tchar*			m_szFileData;

	tint32			m_nIndexNum;
	tint32*			m_pIndexList;
};

#endif