/********************************************************************************
 *	文件名：	ImpactLogic_000.h
 *	全路径：	\Server\Scene\Impact\ImpactLogic_000.h
 *	创建人：	zz
 *	创建时间：2016/10/10
 *
 *	功能说明：攻击造成的伤害
 *	参数说明：
 *			参数1:伤害百分比修正 (100表示100%攻击伤害 120表示120%攻击伤害 60表示60%攻击伤害 无则填0)
 *			参数2：附加无类型伤害值修正(无则填0)
 *			参数3:附加掉血百分比(无则填0)
 *			参数4:附加掉血值(无则填0)
 *			参数5：击倒概率(无则填0)
 *			参数6:击飞概率(无则填0)
 *			参数7:击飞最小水平位移(无则填0)
 *			参数8:击飞最大水平位移(无则填0)
 *			参数9:击飞最小垂直位移(无则填0)
 *			参数10:击飞最大垂直位移(无则填0)
 *			参数11:击飞时间(单位:毫秒)(无则填0)
 *			参数12:附加攻击值(无则填0)
 *			参数13:伤害客户端分几次冒(无需求 填-1)
 *          参数14::伤害客户端分多次冒泡的间隔时间(无需求 填-1 单位：毫秒)
 注：只填附加掉血  伤害百分比修正和都为0 表示值走掉血 不走攻击造成的扣血（即本次伤害的掉血数就是填的附加掉血数）
 *	修改记录：
*********************************************************************************/
#ifndef IMPACTLOGIC_000_H
#define IMPACTLOGIC_000_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_000 :public ImpactBaseLogic
{
public:
	enum 
	{
		DAMAGEREFIX =0,//伤害百分比修正
		DAMAGEADD, //附加无类型伤害值修正
		HPPERREFIX,//附加掉血百分比修正
		HPVALUEREFIX,//附加掉血值修正
		ATTACKDOWNRATE,//击倒概率
		ATTACKFLYRATE,//击飞概率
		ATTACKFLYMINDIS,//击飞最小水平位移
		ATTACKFLYMAXDIS,//击飞最大水平位移
		ATTACKFLYMINHIGHT,//击飞最小垂直位移
		ATTACKFLYMAXHIGHT,//击飞最大垂直位移
		ATTACKFLYTIME,//击飞时间(单位:毫秒)
		ATTACKADD,//附加攻击值
		CLIENTSHOWTIMES,//伤害客户端分几次冒(无需求 填-1)
		CLIENTSHOWINTER,//伤害客户端分多次冒泡的间隔时间(无需求 填-1 单位：毫秒)
	};
	
	ImpactLogic_000(){};
	~ImpactLogic_000(){};
	
	//buff开始生效
	virtual void StartEffect(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(ImpactLogic_000);

#endif