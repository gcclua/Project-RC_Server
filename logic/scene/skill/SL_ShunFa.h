/********************************************************************
	�ļ���: 	SL_ShunFa.h
	�ļ�·��:	\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-3-3 9:55
	����˵������׼˲�����߼�
	����˵��:
	����1������Ŀ������(-1 ��ʾ����������)
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_SHUFA_H
#define SL_SHUFA_H
#include "SkillBaseLogic.h"

class SL_ShunFa:public SkillBaseLogic
{
public:
	SL_ShunFa (){};
	~SL_ShunFa(){};
public:
	enum 
	{
		MAXTARGETNUM =0,
	};
	//��ȡ����Ŀ������
	virtual int GetMaxTargetNum(void);//-1 ��ʾ����������
private:
};
POOLDEF_DECL(SL_ShunFa);
#endif