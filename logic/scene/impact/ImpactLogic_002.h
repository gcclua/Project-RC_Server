/********************************************************************************
 *	文件名：	ImpactLogic_002.h
 *	全路径：	\Server\Scene\Impact\ImpactLogic_002.h
 *	创建人：	zz
 *	创建时间：2013-2-18
 *
 *	功能说明：向周围目标派发子BUFF(延迟派发)(注：该2号逻辑BUFF的发送者 向该BUFF的拥有者周围发送子BUFF)
 *	参数说明：
 *			参数1:子BUFF ID 
 *			参数2：选择目标类型(敌人 友方 队友等)(针对该2号逻辑BUFF的发送者来说)
 *			参数3：扫描方式(1 圆形扫描 2 扇形扫描 3直线扫描 4环形)
 *			参数4：扫描参数1(无则填-1 圆形扫描的半径 扇形扫描的半径 直线扫描的长度距离 环形的内圆半径）
 *			参数5：扫描参数2(无则填-1 圆形扫描 无填-1  扇形扫描扇形的角度值 直线扫描宽度距离 环形的外圆半径）
 *			参数6：扫描参数3(无则填-1 预留）
 *			参数7:目标上限 (无上限则填99999）
 *	修改记录：
*********************************************************************************/
#ifndef IMPACTLOGIC_002_H
#define IMPACTLOGIC_002_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_002 :public ImpactBaseLogic
{
public:
	enum 
	{
		///!!!不要调整顺序
		IMPACT_ID =0,//子BUFF ID 
		TARGETTYPE,//选择目标类型(敌人 友方 队友等)
		SCANTYPE,//扫描方式(1 圆形扫描 2 扇形扫描 3直线扫描 4环形 5客户端选中的目标)
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
		SCAN_RING,//环形
		SCAN_TARGETOBJ, // 客户端选中的目标
	};
	ImpactLogic_002(){};
	~ImpactLogic_002(){};
	
	//buff开始生效
	virtual void StartEffect(Obj_Character& rSelf);
	bool	IsWantedUnit(Table_Impact const& rImpactData,Obj_Character& rSelf,Obj_Character& rUnit,int nTargetType) ;
private:

};
POOLDEF_DECL(ImpactLogic_002);

#endif