/********************************************************************************
 *	文件名：	ImpactBaseLogic.h
 *	全路径：	\Sever\Skill\ImpactBaseLogic.h
 *	创建人：	zz
 *	创建时间：2016/10/10
 *
 *	功能说明：服务器效果基类
 *	修改记录：
*********************************************************************************/

#ifndef IMPACTBASELOGIC_H
#define IMPACTBASELOGIC_H

#include "Base.h"
#include "ImpactStruct/GameStruct_Impact.h"

class Obj_Character;
class TimeInfo;
class DamagesInof_T;
struct CombatAttr_Refix;

class ImpactBaseLogic
{
public:
	enum IMPACTLOGICTYPE
	{
		IMPACT_000=0, //攻击造成的伤害
		IMPACT_001, //伤害修正
		IMPACT_002,//向周围目标派发子BUFF(延迟派发)
		IMPACT_003,//向周围目标持续定时派发子BUFF
		IMPACT_004,//战斗属性修正
		IMPACT_005,//当前血 蓝 怒的修正
		IMPACT_006,//持续定时触发子BUFF(针对该BUFF拥有者发送子buff)
		IMPACT_007,//嘲讽 强制攻击施放者
		MAX_IMPACTLOGIC,
	};
	//BUFF 特效生效的时间点
	enum EFFCTPLAYMODE
	{
		PLAYACTIVE=0, //激活时
		PLAYEFFCT, //生效时
	};
	//BUFF 生命类型
	enum LIFETYPE
	{
		TIMETYPE=0,//时间控制
		DAMAGECOUNTTYPE,//伤害累计量控制
	};
public:
	ImpactBaseLogic();
	~ImpactBaseLogic(){};
public:
	// 本效果是否是持续效果
	virtual bool IsContinue(void) const {return false;}
	// 本效果是不是定期发作的效果
	virtual bool IsIntervaled(void) const {return false;}
	//event handler
	// 心跳的统一处理
	virtual bool Tick(TimeInfo const&rTimeInfo,Obj_Character& rSelf);
	// 效果激活的事件
	virtual bool OnActive(Obj_Character& rSelf);
	//初始效果参数
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	//buff开始生效 前的处理
	virtual bool BeforeStartEffec(Obj_Character& rSelf);
	//buff开始生效
	virtual void StartEffect(Obj_Character& rSelf);
	// 角色受到无类型伤害时调用这个接口来让效果修正这些伤害
	virtual void OnNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage) {};
	//忽视无类型伤害
	virtual void IgnoreNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rDamage)  {};
	//吸收反射无类型伤害
	virtual void AbsorbAndReflexNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)  {};
	virtual bool IsDecNoTypedDamagebyMulti(void){return false;};//是否是按累乘减免无类型伤害
	virtual float GetDecNoTypedDamagebyMulti(void){return 0.0f;};//按累乘减免类型无伤害的百分比
	//角色受到类型伤害时调用这个接口来让效果修正这些伤害
	virtual void OnTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)  {};
	//忽视类型伤害
	virtual void IgnoreTypedDamage(Obj_Character& rSelf,DamagesInof_T& rDamage)  {};
	//吸收反射类型伤害
	virtual void AbsorbAndReflexTypedDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)  {};
	// 角色死亡时，调用这个接口； 效果可以对角色死亡做出自己的响应
	virtual void OnDie(Obj_Character& rSelf) {};
	// 效果消散
	virtual void OnFadeOut(Obj_Character& rSelf);
	// 效果心跳时间到了之后， 会被调用一次。 周期性事件接口
	virtual void OnIntervalOver(Obj_Character& rSelf){};
	// buff对角色战斗属性的修正
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& buffCombatRefix)  {};
	// 角色是否被限制移动
	virtual bool IsMoveDisabled(void) const {return false;}
	// 角色是否可以使用技能
	virtual bool IsSkillDisabled(void) const {return false;}
	// 是否是无敌模式（GOD模式）
	virtual bool IsGODModel(void) const {return false;}
	// 是否受到伤害时消散
	virtual bool IsFadeoutWhenReceiveDamage(void) const {return false;}
	// 是否发出伤害时消散
	virtual bool IsFadeoutWhenSendDamage(void) const {return false;}
	// 是否受到攻击时消散(攻击包括 伤害和不带伤害的DEBUFF)
	virtual bool IsFadeoutWhenReceiveAttack(void) const {return false;}
	// 是否发出攻击时消散(攻击包括 伤害和不带伤害的DEBUFF)
	virtual bool IsFadeoutWhenSendAttack(void) const {return false;}
	// 是否移动时消散
	virtual bool IsFadeoutOnMoveTo(void) const {return false;}
	// 是否是法师的冰冻(如果是法师的冰冻,可能会影响法师伤害输出修正)
	virtual bool IsFaShiFreeze(void) const {return false;}
	//受到伤害时做的处理
	virtual void OnReceiveDamage(Obj_Character& rSelf,DamagesInof_T const& rDamge){};
	//受到攻击时做的处理
	virtual void OnAttack(Obj_Character& rSelf,Obj_Character& rAttack){};
	//发出伤害结束时做的处理
	virtual void OnSendDamgeFinish(Obj_Character& rSelf,Obj_Character& rDefenser,DamagesInof_T const& rDamge){};
	//是否是嘲讽BUFF
	virtual bool IsTaunt(void) const {return false;}
	//叠加处理
	virtual void OnOverlay(Obj_Character& rSelf);
	//是否是隐身BUFF
	virtual bool IsStealth(void) const {return false;}
	//伙伴资质修正(伙伴专用)
	virtual void FellowZiZhiRefix(Obj_Character& rSelf,int nZiZhiType,int& nRefixValue,float& fRefixPer){};
	//离开场景前的处理
	virtual void BeforeLeaveScene(Obj_Character& rSelf);
	//对命中率的修正
	virtual bool IsRefixHitPer(Obj_Character& rSelf,float& fRefixHitPer);
	//对暴击率的修正
	virtual bool IsRefixCriPer(Obj_Character& rSelf,float& fRefixCriPer);
	// 修正发送出的全部伤害,这时候伤害接收者还没有接收
	virtual void RefixSendAllDamage(Obj_Character& rSelf, Obj_Character& rTarget, DamagesInof_T& rRefixDamage,const DamagesInof_T& rSendDamage)  {};
public:
	//任何效果逻辑自己不能把自己当成子效果派发出去
	bool CheckSubImpactIsMyself(int nSubImpact)const;
	void SetActive(bool bIsActive){ m_bIsActive =bIsActive;}//是否激活
	bool IsVaild(){return m_ImpactStruct.IsVaild();};//数据是否有效
	bool IsActive(){return (m_bIsActive && IsVaild());}//是否激活
	bool IsEffect(){return (IsActive() && m_bIsEffect);}//是否生效
	ImpactStruct& GetImpatInfo(void){return m_ImpactStruct;}
	ImpactStruct const& GetImpatInfo(void) const{return m_ImpactStruct;}
	//统一使用该接口获取BUFF发送者
	boost::shared_ptr<Obj_Character> GetImpactSender(Obj_Character& rSelf);
public:
	bool SerializeToDB(DBImpactStruct& rDest);//数据拷贝到存储结构中
	bool SerializeFromDB(const DBImpactStruct& rSour);//存储结构中数据拷贝
	//从数据加载后 需要做的操作(一般针对持续性特效加载后做的处理)
	virtual void InitAfterFromDB(Obj_Character& rSelf){};
protected:
	ImpactStruct m_ImpactStruct;
	bool m_bIsActive;//是否激活
	bool m_bIsEffect;//是否生效
	int m_nContinueElapsedTime;//记录下累计的持续时间(单位：毫秒)
	int m_nLifeType;//生命控制类型
};
POOLDEF_DECL(ImpactBaseLogic);

typedef std::list<ImpactBaseLogicPtr> ImpactPtrList;	

#endif // !IMPACTBASELOGIC_H
