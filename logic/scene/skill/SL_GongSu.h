/********************************************************************
	�ļ���: 	SL_GongSu.h
	�ļ�·��:\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-3-3 10:06
	����˵�������ٵ��Ӽ���
	����˵��:
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_GONGSU_H
#define SL_GONGSU_H
#include "SkillBaseLogic.h"

class SL_GongSu:public SkillBaseLogic
{
public:
	SL_GongSu(){};
	~SL_GongSu(){};

	//	virtual bool Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo){};
private:

};

POOLDEF_DECL(SL_GongSu);
#endif
