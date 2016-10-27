/********************************************************************************
 *	�ļ�����	ImpactLogic_003.h
 *	ȫ·����	\Server\Scene\Impact\ImpactLogic_003.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-2-18
 *
 *	����˵����������ʱ����ΧĿ���ɷ���BUFF����3���߼���BUFF�����߶�ʱ���BUFF��ӵ������Χ������BUFF��
 *	����˵����
 *			����1:����ʱ�� (��λ����)
 *			����2���������ʱ��(��λ����)
 *			����3:��BUFF ID 
 *			����4��ѡ��Ŀ������(���� �ѷ� ���ѵ�)(��Ը�3���߼���BUFF�ķ����߶���)
 *			����5��ɨ�跽ʽ(1 Բ��ɨ�� 2 ����ɨ�� 3ֱ��ɨ�� 4Բ��ɨ��)
 *			����6��ɨ�����1(������-1 Բ��ɨ��İ뾶 ����ɨ��İ뾶 ֱ��ɨ��ĳ��Ⱦ��� Բ����Բ�뾶��
 *			����7��ɨ�����2(������-1 Բ��ɨ�� ����-1  ����ɨ�����εĽǶ�ֵ ֱ��ɨ���Ⱦ��� Բ����Բ�뾶��
 *			����8��ɨ�����3(������-1 Ԥ����
 *			����9�����Ŀ����  ����������9999
 *	�޸ļ�¼��
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
		CONTIUNTIME =0,//����ʱ��
		INTERVALTIME,//�������ʱ��
		IMPACT_ID ,//��BUFF ID 
		TARGETTYPE,//ѡ��Ŀ������(��Ը�3���߼���BUFF�ķ����߶���)
		SCANTYPE,//ɨ�跽ʽ(1 Բ��ɨ�� 2 ����ɨ�� 3ֱ��ɨ��)
		SCANPARAME_01,//ɨ�����1(������-1 Բ��ɨ��İ뾶 ����ɨ��İ뾶 ֱ��ɨ��ĳ��Ⱦ��룩
		SCANPARAME_02,//ɨ�����2(������-1 Բ��ɨ�� ����-1  ����ɨ�����εĽǶ�ֵ ֱ��ɨ���Ⱦ��룩
		SCANPARAME_03,//ɨ�����3(������-1 Ԥ����
		MAXTARGETNUM,//Ŀ������ (����������99999��
	};
	enum 
	{
		SCAN_CIRCLE =1,//Բ��ɨ��
		SCAN_SECTOR,//����ɨ��
		SCAN_RAY,//ֱ��ɨ��
		SCAN_RING,//Բ��ɨ��
	};
	ImpactLogic_003(){};
	~ImpactLogic_003(){};
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// ��Ч���Ƿ��ǳ���Ч��
	virtual bool IsContinue(void) const {return true;}
	// ��Ч���ǲ��Ƕ��ڷ�����Ч��
	virtual bool IsIntervaled(void) const {return true;}
	// Ч������ʱ�䵽��֮�� �ᱻ����һ�Ρ� �������¼��ӿ�
	virtual void OnIntervalOver(Obj_Character& rSelf);
	bool	IsWantedUnit(Table_Impact const& rImpactData,Obj_Character& rSelf,Obj_Character& rUnit);
	
private:

};
POOLDEF_DECL(ImpactLogic_003);

#endif