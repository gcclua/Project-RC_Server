/********************************************************************
	文件名: 	SL_GongSu.h
	文件路径:\Project\Server\Server\Server\Scene\Skill
	创建者:		luoy
	创建时间:	2014-3-3 10:06
	功能说明：攻速叠加技能
	参数说明:
	修改记录:

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
