/********************************************************************
	文件名: 	ImpactLogic_007.h
	文件路径:	F:\Mobile_Sever\LDJ_Moblie_Sever\Project\Server\Server\Server\Scene\Impact
	创建者:		luoy
	创建时间:	2014-2-26 13:16
	功能说明：嘲讽(拉怪 立即修正NPC的攻击对象为buff发送者)
	参数说明:
		参数1:持续时间
	修改记录:

*********************************************************************/
#ifndef IMPACTLOGIC_007_H
#define IMPACTLOGIC_007_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_007 :public ImpactBaseLogic
{
public:
	enum 
	{
		CONTINUETIME =0,//持续时间
	};
	ImpactLogic_007(){};
	~ImpactLogic_007(){};
	//buff开始生效
	virtual void StartEffect(Obj_Character& rSelf);
	//初始效果参数
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// 本效果是否是持续效果
	virtual bool IsContinue(void) const {return true;}
	//是否是嘲讽
	virtual bool IsTaunt(void) const {return true;}

private:

};
POOLDEF_DECL(ImpactLogic_007);
#endif