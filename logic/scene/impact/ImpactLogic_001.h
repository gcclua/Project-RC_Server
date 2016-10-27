/********************************************************************************
 *	�ļ�����	ImpactLogic_001.h
 *	ȫ·����	\Server\Scene\Impact\ImpactLogic_001.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2016/10/10
 *
 *	����˵�����˺�����
 *	����˵����
 *			����1:�˺�����(0������ 1�����˺� 2�����˺�)��
 *			����2:�˺�������ֵ (������0 �������� ����Ϊ����)
 *			����3:�˺������ٷֱ�(������0 �������� ����Ϊ���� 2000��ʾ����20% -2000��ʾ����20% )
 *			����4������ʱ��(��λ:����)
 *			����5�����BUFF ID(��ʾֻ��� �иñ��BUFF���˺����������˺����� ������-1)
 *			����6���Ƿ����۳˵��������˺�����(�������˺������۳�ָ����İٷֱȲ����ӷ����˷� ������1 )
 *	�޸ļ�¼��
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
		DAMAGETYPETYPE =0,//�˺�����
		VALUE,//�˺�������ֵ
		PER, //�˺������ٷֱ�
		CONTINUETIME,//����ʱ��
		FLAGBUFFID,//���BUFF ID
		ISDECBYMULTI,//�Ƿ����۳˵��������˺�����(�������˺������۳�ָ����İٷֱȲ����ӷ����˷� ������1 )
	};
	enum 
	{
		NOTYPE =0,//�������˺�
		PHYTYPE,//�����˺�
		MAGTYPE,//�����˺�
	};
	ImpactLogic_001(){};
	~ImpactLogic_001(){};
	// ��Ч���Ƿ��ǳ���Ч��
	virtual bool IsContinue(void) const {return true;}
	//��ʼЧ������
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// ��ɫ�ܵ��������˺�ʱ��������ӿ�����Ч��������Щ�˺�
	virtual void OnNoTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage);
	virtual bool IsDecNoTypedDamagebyMulti(void);//�Ƿ��ǰ��۳˼����������˺�
	virtual float GetDecNoTypedDamagebyMulti(void);//���۳˼����������˺��İٷֱ�
	//��ɫ�ܵ������˺�ʱ��������ӿ�����Ч��������Щ�˺�
	virtual void OnTypeDamage(Obj_Character& rSelf,DamagesInof_T& rRefixDamage,const DamagesInof_T& rSelfDamage);
private:

};
POOLDEF_DECL(ImpactLogic_001);

#endif