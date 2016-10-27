/********************************************************************************
 *	�ļ�����	ImpactBaseLogic.h
 *	ȫ·����	\Sever\Skill\ImpactBaseLogic.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2016/10/10
 *
 *	����˵����������Ч������
 *	�޸ļ�¼��
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
		IMPACT_000=0, //������ɵ��˺�
		IMPACT_001, //�˺�����
		IMPACT_002,//����ΧĿ���ɷ���BUFF(�ӳ��ɷ�)
		IMPACT_003,//����ΧĿ�������ʱ�ɷ���BUFF
		IMPACT_004,//ս����������
		IMPACT_005,//��ǰѪ �� ŭ������
		IMPACT_006,//������ʱ������BUFF(��Ը�BUFFӵ���߷�����buff)
		IMPACT_007,//���� ǿ�ƹ���ʩ����
		MAX_IMPACTLOGIC,
	};
	//BUFF ��Ч��Ч��ʱ���
	enum EFFCTPLAYMODE
	{
		PLAYACTIVE=0, //����ʱ
		PLAYEFFCT, //��Чʱ
	};
	//BUFF ��������
	enum LIFETYPE
	{
		TIMETYPE=0,//ʱ�����
		DAMAGECOUNTTYPE,//�˺��ۼ�������
	};
public:
	ImpactBaseLogic();
	~ImpactBaseLogic(){};
public:
	// ��Ч���Ƿ��ǳ���Ч��
	virtual bool IsContinue(void) const {return false;}
	// ��Ч���ǲ��Ƕ��ڷ�����Ч��
	virtual bool IsIntervaled(void) const {return false;}
	//event handler
	// ������ͳһ����
	virtual bool Tick(TimeInfo const&rTimeInfo,Obj_Character& rSelf);
	// Ч��������¼�
	virtual bool OnActive(Obj_Character& rSelf);
	//��ʼЧ������
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	//buff��ʼ��Ч ǰ�Ĵ���
	virtual bool BeforeStartEffec(Obj_Character& rSelf);
	//buff��ʼ��Ч
	virtual void StartEffect(Obj_Character& rSelf);
	// ��ɫ�ܵ��������˺�ʱ��������ӿ�����Ч��������Щ�˺�
	virtual void OnNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage) {};
	//�����������˺�
	virtual void IgnoreNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rDamage)  {};
	//���շ����������˺�
	virtual void AbsorbAndReflexNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)  {};
	virtual bool IsDecNoTypedDamagebyMulti(void){return false;};//�Ƿ��ǰ��۳˼����������˺�
	virtual float GetDecNoTypedDamagebyMulti(void){return 0.0f;};//���۳˼����������˺��İٷֱ�
	//��ɫ�ܵ������˺�ʱ��������ӿ�����Ч��������Щ�˺�
	virtual void OnTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)  {};
	//���������˺�
	virtual void IgnoreTypedDamage(Obj_Character& rSelf,DamagesInof_T& rDamage)  {};
	//���շ��������˺�
	virtual void AbsorbAndReflexTypedDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage)  {};
	// ��ɫ����ʱ����������ӿڣ� Ч�����ԶԽ�ɫ���������Լ�����Ӧ
	virtual void OnDie(Obj_Character& rSelf) {};
	// Ч����ɢ
	virtual void OnFadeOut(Obj_Character& rSelf);
	// Ч������ʱ�䵽��֮�� �ᱻ����һ�Ρ� �������¼��ӿ�
	virtual void OnIntervalOver(Obj_Character& rSelf){};
	// buff�Խ�ɫս�����Ե�����
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& buffCombatRefix)  {};
	// ��ɫ�Ƿ������ƶ�
	virtual bool IsMoveDisabled(void) const {return false;}
	// ��ɫ�Ƿ����ʹ�ü���
	virtual bool IsSkillDisabled(void) const {return false;}
	// �Ƿ����޵�ģʽ��GODģʽ��
	virtual bool IsGODModel(void) const {return false;}
	// �Ƿ��ܵ��˺�ʱ��ɢ
	virtual bool IsFadeoutWhenReceiveDamage(void) const {return false;}
	// �Ƿ񷢳��˺�ʱ��ɢ
	virtual bool IsFadeoutWhenSendDamage(void) const {return false;}
	// �Ƿ��ܵ�����ʱ��ɢ(�������� �˺��Ͳ����˺���DEBUFF)
	virtual bool IsFadeoutWhenReceiveAttack(void) const {return false;}
	// �Ƿ񷢳�����ʱ��ɢ(�������� �˺��Ͳ����˺���DEBUFF)
	virtual bool IsFadeoutWhenSendAttack(void) const {return false;}
	// �Ƿ��ƶ�ʱ��ɢ
	virtual bool IsFadeoutOnMoveTo(void) const {return false;}
	// �Ƿ��Ƿ�ʦ�ı���(����Ƿ�ʦ�ı���,���ܻ�Ӱ�취ʦ�˺��������)
	virtual bool IsFaShiFreeze(void) const {return false;}
	//�ܵ��˺�ʱ���Ĵ���
	virtual void OnReceiveDamage(Obj_Character& rSelf,DamagesInof_T const& rDamge){};
	//�ܵ�����ʱ���Ĵ���
	virtual void OnAttack(Obj_Character& rSelf,Obj_Character& rAttack){};
	//�����˺�����ʱ���Ĵ���
	virtual void OnSendDamgeFinish(Obj_Character& rSelf,Obj_Character& rDefenser,DamagesInof_T const& rDamge){};
	//�Ƿ��ǳ���BUFF
	virtual bool IsTaunt(void) const {return false;}
	//���Ӵ���
	virtual void OnOverlay(Obj_Character& rSelf);
	//�Ƿ�������BUFF
	virtual bool IsStealth(void) const {return false;}
	//�����������(���ר��)
	virtual void FellowZiZhiRefix(Obj_Character& rSelf,int nZiZhiType,int& nRefixValue,float& fRefixPer){};
	//�뿪����ǰ�Ĵ���
	virtual void BeforeLeaveScene(Obj_Character& rSelf);
	//�������ʵ�����
	virtual bool IsRefixHitPer(Obj_Character& rSelf,float& fRefixHitPer);
	//�Ա����ʵ�����
	virtual bool IsRefixCriPer(Obj_Character& rSelf,float& fRefixCriPer);
	// �������ͳ���ȫ���˺�,��ʱ���˺������߻�û�н���
	virtual void RefixSendAllDamage(Obj_Character& rSelf, Obj_Character& rTarget, DamagesInof_T& rRefixDamage,const DamagesInof_T& rSendDamage)  {};
public:
	//�κ�Ч���߼��Լ����ܰ��Լ�������Ч���ɷ���ȥ
	bool CheckSubImpactIsMyself(int nSubImpact)const;
	void SetActive(bool bIsActive){ m_bIsActive =bIsActive;}//�Ƿ񼤻�
	bool IsVaild(){return m_ImpactStruct.IsVaild();};//�����Ƿ���Ч
	bool IsActive(){return (m_bIsActive && IsVaild());}//�Ƿ񼤻�
	bool IsEffect(){return (IsActive() && m_bIsEffect);}//�Ƿ���Ч
	ImpactStruct& GetImpatInfo(void){return m_ImpactStruct;}
	ImpactStruct const& GetImpatInfo(void) const{return m_ImpactStruct;}
	//ͳһʹ�øýӿڻ�ȡBUFF������
	boost::shared_ptr<Obj_Character> GetImpactSender(Obj_Character& rSelf);
public:
	bool SerializeToDB(DBImpactStruct& rDest);//���ݿ������洢�ṹ��
	bool SerializeFromDB(const DBImpactStruct& rSour);//�洢�ṹ�����ݿ���
	//�����ݼ��غ� ��Ҫ���Ĳ���(һ����Գ�������Ч���غ����Ĵ���)
	virtual void InitAfterFromDB(Obj_Character& rSelf){};
protected:
	ImpactStruct m_ImpactStruct;
	bool m_bIsActive;//�Ƿ񼤻�
	bool m_bIsEffect;//�Ƿ���Ч
	int m_nContinueElapsedTime;//��¼���ۼƵĳ���ʱ��(��λ������)
	int m_nLifeType;//������������
};
POOLDEF_DECL(ImpactBaseLogic);

typedef std::list<ImpactBaseLogicPtr> ImpactPtrList;	

#endif // !IMPACTBASELOGIC_H
