/********************************************************************
	�ļ���: 	SL_ZhiXian.h
	�ļ�·��:\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-3-3 10:19
	����˵����ֱ�߹������� �м��ʴ̴�һ��ֱ���ϵĵ���
	����˵��:
		����1:���ֱ�߹�����Ȩ��(20��ʾ 20%)
		����2:�ı��εĿ�ȷ�Χ
		����3:�ı��εĳ��ȷ�Χ
		����4:���Ŀ������
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_ZHIXIAN_H
#define SL_ZHIXIAN_H
#include "SkillBaseLogic.h"

class SL_ZhiXian:public SkillBaseLogic
{
public:
	SL_ZhiXian (){};
	~SL_ZhiXian(){};
	enum 
	{
		ZHIXIANRATE =0,//ֱ�ߵĿ��
		ZHIXIANSCOPE,//�ı��εĿ�ȷ�Χ
		ZHIXIANLENGTH,//�ı��εĳ��ȷ�Χ
		MAXTARGETNUM,//���Ŀ������
	};
	//��ʼ��Ч
	virtual void StarEffect(Obj_Character& rSelf);
private:
};
POOLDEF_DECL(SL_ZhiXian);
#endif