/********************************************************************************
 *	文件名：	ImpactLogic_003.h
 *	全路径：	\Server\Scene\Impact\ImpactLogic_003.h
 *	创建人：	zz
 *	创建时间：2013-2-18
 *
 *	功能说明：持续定时向周围目标派发子BUFF（该3号逻辑的BUFF发送者定时向该BUFF的拥有者周围发送子BUFF）
 *	参数说明：
 *			参数1:持续时间 (单位毫秒)
 *			参数2：间隔触发时间(单位毫秒)
 *			参数3:子BUFF ID 
 *			参数4：选择目标类型(敌人 友方 队友等)(针对该3号逻辑的BUFF的发送者而言)
 *			参数5：扫描方式(1 圆形扫描 2 扇形扫描 3直线扫描 4圆环扫描)
 *			参数6：扫描参数1(无则填-1 圆形扫描的半径 扇形扫描的半径 直线扫描的长度距离 圆环内圆半径）
 *			参数7：扫描参数2(无则填-1 圆形扫描 无填-1  扇形扫描扇形的角度值 直线扫描宽度距离 圆环外圆半径）
 *			参数8：扫描参数3(无则填-1 预留）
 *			参数9：最大目标数  无上限则填9999
 *	修改记录：
*********************************************************************************/
#ifndef IMPACTLOGIC_003_H
#define IMPACTLOGIC_003_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_003 :public ImpactBaseLogic
{
public:
	enum 
	{
		CONTIUNTIME =0,//持续时间
		INTERVALTIME,//间隔触发时间
		IMPACT_ID ,//子BUFF ID 
		TARGETTYPE,//选择目标类型(针对该3号逻辑的BUFF的发送者而言)
		SCANTYPE,//扫描方式(1 圆形扫描 2 扇形扫描 3直线扫描)
		SCANPARAME_01,//扫描参数1(无则填-1 圆形扫描的半径 扇形扫描的半径 直线扫描的长度距离）
		SCANPARAME_02,//扫描参数2(无则填-1 圆形扫描 无填-1  扇形扫描扇形的角度值 直线扫描宽度距离）
		SCANPARAME_03,//扫描参数3(无则填-1 预留）
		MAXTARGETNUM,//目标上限 (无上限则填99999）
	};
	enum 
	{
		SCAN_CIRCLE =1,//圆形扫描
		SCAN_SECTOR,//扇形扫描
		SCAN_RAY,//直线扫描
		SCAN_RING,//圆环扫描
	};
	ImpactLogic_003(){};
	~ImpactLogic_003(){};
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// 本效果是否是持续效果
	virtual bool IsContinue(void) const {return true;}
	// 本效果是不是定期发作的效果
	virtual bool IsIntervaled(void) const {return true;}
	// 效果心跳时间到了之后， 会被调用一次。 周期性事件接口
	virtual void OnIntervalOver(Obj_Character& rSelf);
	bool	IsWantedUnit(Table_Impact const& rImpactData,Obj_Character& rSelf,Obj_Character& rUnit);
	
private:

};
POOLDEF_DECL(ImpactLogic_003);

#endif