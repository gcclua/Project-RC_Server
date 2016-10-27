/********************************************************************
	�ļ���: 	ImpactLogic_006.h
	�ļ�·��:\Project\Server\Server\Server\Scene\Impact
	������:		luoy
	����ʱ��:	2014-2-25 13:32
	����˵����������ʱ������BUFF(��6���߼�BUFF�ķ�������Ը�BUFFӵ���߷�����buff)
	����˵��:
	����1:����ʱ�� (��λ����)
	����2:��ʱ����ʱ�� (��λ����)
	����3:������BUFF1 ID(������-1)
	����4:������BUFF2 ID(������-1)
	����5:������BUFF3 ID(������-1)
	����6:������BUFF4 ID(������-1)
	����7:������BUFF5 ID(������-1)
	����8:������BUFF6 ID(������-1)
	�޸ļ�¼:	
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
		CONTINUTIME =0,//����ʱ��
		INTERTIME,//��ʱ����ʱ��
		BUFFID_01,//������BUFF1 ID
		BUFFID_02,//������BUFF2 ID
		BUFFID_03,//������BUFF3 ID
		BUFFID_04,//������BUFF4 ID
		BUFFID_05,//������BUFF5 ID
		BUFFID_06,//������BUFF6 ID
	};
	enum 
	{
		MAXBUFFNUM =6,//�����BUFF�� 
	};
	ImpactLogic_006(){};
	~ImpactLogic_006(){};
	//��ʼЧ������
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// ��Ч���Ƿ��ǳ���Ч��
	virtual bool IsContinue(void) const {return true;}
	// ��Ч���ǲ��Ƕ��ڷ�����Ч��
	virtual bool IsIntervaled(void) const {return true;}
	// Ч������ʱ�䵽��֮�� �ᱻ����һ�Ρ� �������¼��ӿ�
	virtual void OnIntervalOver(Obj_Character& rSelf);
private:

};
POOLDEF_DECL(ImpactLogic_006);


#endif // !IMPACTLOGIG_006_H
