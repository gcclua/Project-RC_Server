#ifndef _GUIDLOADER_H_
#define _GUIDLOADER_H_

#include "Base.h"
//定义暂时放这里，房迪确定结构之后替代之，同时修改函数接口
struct GUIDInfo
{
	int64	m_Serial;	//序列号：(例)123429
};

void LoadGUIDFromDB( GUIDInfo info[], tint8 length );

#endif