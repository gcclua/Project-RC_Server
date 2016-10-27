/********************************************************************
	�ļ���: 	ImpactLogic_007.h
	�ļ�·��:	F:\Mobile_Sever\LDJ_Moblie_Sever\Project\Server\Server\Server\Scene\Impact
	������:		luoy
	����ʱ��:	2014-2-26 13:16
	����˵��������(���� ��������NPC�Ĺ�������Ϊbuff������)
	����˵��:
		����1:����ʱ��
	�޸ļ�¼:

*********************************************************************/
#ifndef IMPACTLOGIC_007_H
#define IMPACTLOGIC_007_H
#include "Base.h"
#include "Scene/Impact/ImpactBaseLogic.h"

class ImpactLogic_007 :public ImpactBaseLogic
{
public:
	enum 
	{
		CONTINUETIME =0,//����ʱ��
	};
	ImpactLogic_007(){};
	~ImpactLogic_007(){};
	//buff��ʼ��Ч
	virtual void StartEffect(Obj_Character& rSelf);
	//��ʼЧ������
	virtual void InitImpactDataInfo(ImpactStruct& rImpactStruct);
	// ��Ч���Ƿ��ǳ���Ч��
	virtual bool IsContinue(void) const {return true;}
	//�Ƿ��ǳ���
	virtual bool IsTaunt(void) const {return true;}

private:

};
POOLDEF_DECL(ImpactLogic_007);
#endif