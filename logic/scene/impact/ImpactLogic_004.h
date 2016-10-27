/********************************************************************************
 *	�ļ�����	ImpactLogic_004.h
 *	ȫ·����	\Server\Scene\Impact\ImpactLogic_004.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-2-18
 *
 *	����˵����ս����������BUFF
 ����˵����
 *			����1:ս����������1(��Ӧս�����Ե�ö������ !!!!������-1)
 *			����2������1������ֵ(�������� ������С ������0)
 *          ����3������1�����İٷֱ�(20��ʾ����20% -20��ʾ����20% ������0)
 *			����4:ս����������2(��Ӧս�����Ե�ö������ !!!!������-1)
 *			����5������2������ֵ(�������� ������С ������0)
 *          ����6������2�����İٷֱ�(20��ʾ����20% -20��ʾ����20% ������0)
 *			����7:ս����������3(��Ӧս�����Ե�ö������ !!!!������-1)
 *			����8������3������ֵ(�������� ������С ������0)
 *          ����9������3�����İٷֱ�(20��ʾ����20% -20��ʾ����20% ������0)
 *			����10������ʱ��(��λ����)
 *			����11:ս����������4(��Ӧս�����Ե�ö������ !!!!������-1)
 *			����12������4������ֵ(�������� ������С ������0)
 *          ����13������4�����İٷֱ�(20��ʾ����20% -20��ʾ����20% ������0)
 *	�޸ļ�¼��
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
		COMBATATTRTYPE1 =0,//ս����������1(��Ӧս�����Ե�ö������)
		TYPE1REFIXVALUE,//ֵ����
		TYPE1REFIXPER,//�ٷֱ�����
		COMBATATTRTYPE2,//ս����������2(��Ӧս�����Ե�ö������)
		TYPE2REFIXVALUE,//ֵ����
		TYPE2REFIXPER,//�ٷֱ�����
		COMBATATTRTYPE3,//ս����������3(��Ӧս�����Ե�ö������)
		TYPE3REFIXVALUE,//ֵ����
		TYPE3REFIXPER,//�ٷֱ�����
		CONTINUTIME,//����ʱ��
		COMBATATTRTYPE4,//ս����������4(��Ӧս�����Ե�ö������)
		TYPE4REFIXVALUE,//ֵ����
		TYPE4REFIXPER,//�ٷֱ�����
	};
	ImpactLogic_004(){};
	~ImpactLogic_004(){};

	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// ��Ч���Ƿ��ǳ���Ч��
	virtual bool IsContinue(void) const {return true;}
	//buff��ʼ��Ч
	virtual void StartEffect(Obj_Character& rSelf);
	//buff�Խ�ɫս�����Ե�����
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& buffCombatRefix);
	// Ч����ɢ
	virtual void OnFadeOut(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(ImpactLogic_004);

#endif