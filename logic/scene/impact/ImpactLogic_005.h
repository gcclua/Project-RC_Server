/********************************************************************************
 *	文件名：	ImpactLogic_005.h
 *	全路径：	\Server\Scene\Impact\ImpactLogic_005.h
 *	创建人：	zz
 *	创建时间：2013-2-18
 *
 *	功能说明：当前血 蓝 怒的修正
 *	参数说明：
 *			参数1:当前血量的值修正(无则填0 正数增加 负数减小)
 *			参数2：当前血量的百分比修正(无则填0 血上限的百分比 20表示增加20% -20表示减少20%)
 *			参数3:当前法力的值修正(无则填0 正数增加 负数减小)
 *			参数4：当前法力的百分比修正(无则填0 法力上限的百分比 20表示增加20% -20表示减少20%)
 *			参数5:当前XP能量的值修正(无则填0 正数增加 负数减小)
 *			参数6：当前XP能量的百分比修正(无则填0 XP能量上限的百分比 20表示增加20% -20表示减少20%)
 *			参数7：当前血量的百分比修正(无则填0 当前血量的百分比 20表示增加当前血量的20% -20表示减少当前血量的20%)
 *	修改记录：
*********************************************************************************/
#ifndef IMPACTLOGIC_005_H
#define IMPACTLOGIC_005_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_005 :public ImpactBaseLogic
{
public:
	enum 
	{
		HPREFIXVALUE =0,//当前血量的值修正
		HPREFIXPER,//当前血量的百分比修正(血上限的百分比)
		MPREFIXVALUE,//当前法力的百分比修正(法力上限的百分比)
		MPREFIXPER,//当前XP能量的值修正
		XPREFIXVALUE,//当前XP能量的值修正
		XPREFIXPER,//当前XP能量的百分比修正(XP能量上限的百分比)
		HPREFIXCURPER, // 当前血量的百分比修正(当前血量的百分比)
	};
	ImpactLogic_005(){};
	~ImpactLogic_005(){};
	
	//buff开始生效
	virtual void StartEffect(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(ImpactLogic_005);

#endif