#ifndef _CITYMSG_H_
#define _CITYMSG_H_

#include "service/Message.h"


MESSAGE_DEF_BEGIN(TrainTroopOverMsg)
	int   m_nType; // ����
	int   m_nHp;   // ѵ��Ѫ��
	int64 m_nBuildId;
	int64 m_ID;
	int   m_nQueueIndex;
MESSAGE_DEF_END(TrainTroopOverMsg)


#endif
