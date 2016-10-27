/********************************************************************************
 *	文件名：	ImpactLogic_004.h
 *	全路径：	\Server\Scene\Impact\ImpactLogic_004.h
 *	创建人：	zz
 *	创建时间：2013-2-18
 *
 *	功能说明：战斗属性修正BUFF
 参数说明：
 *			参数1:战斗属性类型1(对应战斗属性的枚举类型 !!!!无则填-1)
 *			参数2：类型1修正的值(正数增加 负数减小 无则填0)
 *          参数3：类型1修正的百分比(20表示增加20% -20表示减少20% 无则填0)
 *			参数4:战斗属性类型2(对应战斗属性的枚举类型 !!!!无则填-1)
 *			参数5：类型2修正的值(正数增加 负数减小 无则填0)
 *          参数6：类型2修正的百分比(20表示增加20% -20表示减少20% 无则填0)
 *			参数7:战斗属性类型3(对应战斗属性的枚举类型 !!!!无则填-1)
 *			参数8：类型3修正的值(正数增加 负数减小 无则填0)
 *          参数9：类型3修正的百分比(20表示增加20% -20表示减少20% 无则填0)
 *			参数10：持续时间(单位毫秒)
 *			参数11:战斗属性类型4(对应战斗属性的枚举类型 !!!!无则填-1)
 *			参数12：类型4修正的值(正数增加 负数减小 无则填0)
 *          参数13：类型4修正的百分比(20表示增加20% -20表示减少20% 无则填0)
 *	修改记录：
*********************************************************************************/
#ifndef IMPACTLOGIC_004_H
#define IMPACTLOGIC_004_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_004 :public ImpactBaseLogic
{
public:
	enum 
	{
		COMBATATTRTYPE1 =0,//战斗属性类型1(对应战斗属性的枚举类型)
		TYPE1REFIXVALUE,//值修正
		TYPE1REFIXPER,//百分比修正
		COMBATATTRTYPE2,//战斗属性类型2(对应战斗属性的枚举类型)
		TYPE2REFIXVALUE,//值修正
		TYPE2REFIXPER,//百分比修正
		COMBATATTRTYPE3,//战斗属性类型3(对应战斗属性的枚举类型)
		TYPE3REFIXVALUE,//值修正
		TYPE3REFIXPER,//百分比修正
		CONTINUTIME,//持续时间
		COMBATATTRTYPE4,//战斗属性类型4(对应战斗属性的枚举类型)
		TYPE4REFIXVALUE,//值修正
		TYPE4REFIXPER,//百分比修正
	};
	ImpactLogic_004(){};
	~ImpactLogic_004(){};

	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// 本效果是否是持续效果
	virtual bool IsContinue(void) const {return true;}
	//buff开始生效
	virtual void StartEffect(Obj_Character& rSelf);
	//buff对角色战斗属性的修正
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& buffCombatRefix);
	// 效果消散
	virtual void OnFadeOut(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(ImpactLogic_004);

#endif