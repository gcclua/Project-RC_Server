#ifndef _BADWORDSTBL_H_
#define _BADWORDSTBL_H_
#pragma once
#include <string>
#include "Base.h"
using namespace std;


class badwordsBase
{
public:
	badwordsBase(){};
	~badwordsBase(){};

protected:
};

class badwordsTbl
{
public:
	badwordsTbl();
	~badwordsTbl();

	void			LoadTbl();
	void			ClearTbl();

	bool	GetbadwordsBase(const string& str);

	static badwordsTbl&	Instance(){return m_tblbadwords;}
protected:
	static const char*  szConfigFile;
	static badwordsTbl	m_tblbadwords;
	hash_map<string,int>	m_mapbadwordsBase;
};

#endif

