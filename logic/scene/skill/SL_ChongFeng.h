/********************************************************************
	�ļ���: 	SL_ChongFeng.h
	�ļ�·��:	\Project\Server\Server\Server\Scene\Skill
	������:		luoy
	����ʱ��:	2014-3-3 10:15
	����˵������漼��
	����˵��:
		����1������ٶ�
		����2�����ֹͣ�ľ���
	�޸ļ�¼:

*********************************************************************/
#ifndef SL_CHONGFENG_H
#define SL_CHONGFENG_H
#include "SkillBaseLogic.h"

class SL_ChongFeng:public SkillBaseLogic
{
public:
	SL_ChongFeng();
	~SL_ChongFeng(){};
	enum 
	{
		SPEED =0,//����1:�����ٶ�
		STOPDIS =1,//����2�����ֹͣ�ľ���
	};
	//���ܼ���
	virtual void OnActivate(Obj_Character& rSelf);
	//������������
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix);
	//���ܽ���
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
private:
	tint32 m_nNeedIncSpeed;
private:

};
POOLDEF_DECL(SL_ChongFeng);
#endif 