/********************************************************************
	文件名: 	ImpactLogic_006.h
	文件路径:\Project\Server\Server\Server\Scene\Impact
	创建者:		luoy
	创建时间:	2014-2-25 13:32
	功能说明：持续定时触发子BUFF(该6号逻辑BUFF的发送者针对该BUFF拥有者发送子buff)
	参数说明:
	参数1:持续时间 (单位毫秒)
	参数2:定时触发时间 (单位毫秒)
	参数3:触发子BUFF1 ID(无则填-1)
	参数4:触发子BUFF2 ID(无则填-1)
	参数5:触发子BUFF3 ID(无则填-1)
	参数6:触发子BUFF4 ID(无则填-1)
	参数7:触发子BUFF5 ID(无则填-1)
	参数8:触发子BUFF6 ID(无则填-1)
	修改记录:	
*********************************************************************/
#ifndef IMPACTLOGIG_006_H
#define IMPACTLOGIG_006_H

#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_006 :public ImpactBaseLogic
{
public:
	enum 
	{
		CONTINUTIME =0,//持续时间
		INTERTIME,//定时触发时间
		BUFFID_01,//触发子BUFF1 ID
		BUFFID_02,//触发子BUFF2 ID
		BUFFID_03,//触发子BUFF3 ID
		BUFFID_04,//触发子BUFF4 ID
		BUFFID_05,//触发子BUFF5 ID
		BUFFID_06,//触发子BUFF6 ID
	};
	enum 
	{
		MAXBUFFNUM =6,//最大子BUFF数 
	};
	ImpactLogic_006(){};
	~ImpactLogic_006(){};
	//初始效果参数
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// 本效果是否是持续效果
	virtual bool IsContinue(void) const {return true;}
	// 本效果是不是定期发作的效果
	virtual bool IsIntervaled(void) const {return true;}
	// 效果心跳时间到了之后， 会被调用一次。 周期性事件接口
	virtual void OnIntervalOver(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(ImpactLogic_006);


#endif // !IMPACTLOGIG_006_H
