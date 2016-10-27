/********************************************************************************
 *	文件名：	ImpactLogic_001.h
 *	全路径：	\Server\Scene\Impact\ImpactLogic_001.h
 *	创建人：	zz
 *	创建时间：2016/10/10
 *
 *	功能说明：伤害修正
 *	参数说明：
 *			参数1:伤害类型(0无类型 1物理伤害 2法术伤害)；
 *			参数2:伤害修正数值 (无则填0 正数增加 负数为减少)
 *			参数3:伤害修正百分比(无则填0 正数增加 负数为减少 2000表示增加20% -2000表示减少20% )
 *			参数4：持续时间(单位:毫秒)
 *			参数5：标记BUFF ID(表示只针对 有该标记BUFF的伤害发送者做伤害修正 无则填-1)
 *			参数6：是否是累乘的无类型伤害减免(无类型伤害减免累乘指减免的百分比不做加法做乘法 是则填1 )
 *	修改记录：
*********************************************************************************/
#ifndef IMPACTLOGIC_001_H
#define IMPACTLOGIC_001_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_001 :public ImpactBaseLogic
{
public:
	enum 
	{
		DAMAGETYPETYPE =0,//伤害类型
		VALUE,//伤害修正数值
		PER, //伤害修正百分比
		CONTINUETIME,//持续时间
		FLAGBUFFID,//标记BUFF ID
		ISDECBYMULTI,//是否是累乘的无类型伤害减免(无类型伤害减免累乘指减免的百分比不做加法做乘法 是则填1 )
	};
	enum 
	{
		NOTYPE =0,//无类型伤害
		PHYTYPE,//物理伤害
		MAGTYPE,//法术伤害
	};
	ImpactLogic_001(){};
	~ImpactLogic_001(){};
	// 本效果是否是持续效果
	virtual bool IsContinue(void) const {return true;}
	//初始效果参数
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// 角色受到无类型伤害时调用这个接口来让效果修正这些伤害
	virtual void OnNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage);
	virtual bool IsDecNoTypedDamagebyMulti(void);//是否是按累乘减免无类型伤害
	virtual float GetDecNoTypedDamagebyMulti(void);//按累乘减免类型无伤害的百分比
	//角色受到类型伤害时调用这个接口来让效果修正这些伤害
	virtual void OnTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage);
private:

};
POOLDEF_DECL(ImpactLogic_001);

#endif