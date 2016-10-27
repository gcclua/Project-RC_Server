/********************************************************************************
 *	�ļ�����	ImpactLogic_002.h
 *	ȫ·����	\Server\Scene\Impact\ImpactLogic_002.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-2-18
 *
 *	����˵��������ΧĿ���ɷ���BUFF(�ӳ��ɷ�)(ע����2���߼�BUFF�ķ����� ���BUFF��ӵ������Χ������BUFF)
 *	����˵����
 *			����1:��BUFF ID 
 *			����2��ѡ��Ŀ������(���� �ѷ� ���ѵ�)(��Ը�2���߼�BUFF�ķ�������˵)
 *			����3��ɨ�跽ʽ(1 Բ��ɨ�� 2 ����ɨ�� 3ֱ��ɨ�� 4����)
 *			����4��ɨ�����1(������-1 Բ��ɨ��İ뾶 ����ɨ��İ뾶 ֱ��ɨ��ĳ��Ⱦ��� ���ε���Բ�뾶��
 *			����5��ɨ�����2(������-1 Բ��ɨ�� ����-1  ����ɨ�����εĽǶ�ֵ ֱ��ɨ���Ⱦ��� ���ε���Բ�뾶��
 *			����6��ɨ�����3(������-1 Ԥ����
 *			����7:Ŀ������ (����������99999��
 *	�޸ļ�¼��
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
		///!!!��Ҫ����˳��
		IMPACT_ID =0,//��BUFF ID 
		TARGETTYPE,//ѡ��Ŀ������(���� �ѷ� ���ѵ�)
		SCANTYPE,//ɨ�跽ʽ(1 Բ��ɨ�� 2 ����ɨ�� 3ֱ��ɨ�� 4���� 5�ͻ���ѡ�е�Ŀ��)
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
		SCAN_RING,//����
		SCAN_TARGETOBJ, // �ͻ���ѡ�е�Ŀ��
	};
	ImpactLogic_002(){};
	~ImpactLogic_002(){};
	
	//buff��ʼ��Ч
	virtual void StartEffect(Obj_Character& rSelf);
	bool	IsWantedUnit(Table_Impact const& rImpactData,Obj_Character& rSelf,Obj_Character& rUnit,int nTargetType) ;
private:

};
POOLDEF_DECL(ImpactLogic_002);

#endif