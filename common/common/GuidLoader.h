#ifndef _GUIDLOADER_H_
#define _GUIDLOADER_H_

#include "Base.h"
//������ʱ���������ȷ���ṹ֮�����֮��ͬʱ�޸ĺ����ӿ�
struct GUIDInfo
{
	int64	m_Serial;	//���кţ�(��)123429
};

void LoadGUIDFromDB( GUIDInfo info[], tint8 length );

#endif