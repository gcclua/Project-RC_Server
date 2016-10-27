/********************************************************************************
 *	�ļ�����	SkillBaseLogic.h
 *	ȫ·����	\Sever\Skill\SkillBaseLogic.h
 *	�����ˣ�	zz
 *	����ʱ�䣺2013-12-24
 *
 *	����˵�������������ܻ���
 *	�޸ļ�¼��
*********************************************************************************/
#ifndef SKILLBASELOGIC_H
#define SKILLBASELOGIC_H

#include "Base.h"
#include "skill/GameStruct_Skill.h"

class Obj_Character;
struct CombatAttr_Refix;
class TimeInfo;


class SkillBaseLogic
{
public:
	enum SKILLLOGIC
	{
		SL_SHUFA                = 0,//��׼˲�����߼�
		SL_CHONGFENG            = 3,//��漼��
		SL_ZHIXIAN              = 5,//ֱ�߹�������
		SL_EFFECTTOSELF         = 8,//ʹ�ü��ܺ� ���Լ����ϼ�һ��BUFF�����ɷ�Ч����BUFF
		SL_SNARE                = 11,//���弼���߼�
		SL_TELEMOVE             = 12,//˲�Ƽ����߼�
		SL_MAXNUM,
	};
public:
	SkillBaseLogic();
	~SkillBaseLogic(){};
public: 
	//	virtual void MarkModifiedCombatAttrDirty(Obj_Character& rSelf)const{};
		
	//	virtual bool OnHitTarget(Obj_Character& rSelf,Obj_Character& rUnit);
	//	virtual bool OnDisturb(Obj_Character &rSelf ) ;
	//ʹ�ü��ܼ���ǰ�ļ�� ��ÿ�������߼�һ�ε������Ļ���
	virtual void OnBeforeActivate(Obj_Character& rSelf){};
	//�����
	virtual void OnActivate(Obj_Character& rSelf);
	//���� ���ܵ�ʱ�����Ч
	virtual bool Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo);
	//����׼����Ч
	virtual void OnTakeEffect(Obj_Character& rSelf);
	//��Чǰ�Ĵ���
	virtual bool OnBeforeEffect(Obj_Character& rSelf);
	//��ʼ��Ч
	virtual void StarEffect(Obj_Character& rSelf);
	//���ܶ�Ŀ����Ч
	virtual void OnEffectOnUnit(Obj_Character& rSelf, Obj_Character& rUnit);
	//���ܽ�������
	virtual void SkillFinish(Obj_Character& rSelf,bool bIsBreak);
	//�жϼ��ܴ���
	virtual void BreakSkill(Obj_Character& rSelf);
	//�뿪����ǰ�Ĵ���
	virtual void BeforLevelScene(Obj_Character& rSelf);
	//���ܶ�ս�����Ե�����
	virtual void CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix){} ;
	//�����޵�
	virtual bool IsSkillGod(void){return false;};
	//�ܵ�����
	virtual void OnBeAttacked(Obj_Character& rSelf);
	//��ȡ����Ŀ������
	virtual int GetMaxTargetNum(void){return -1;};//-1 ��ʾ����������
public:
	bool IsValid();
	bool IsEffect(){return m_bIsEffect;}
	void InitCurSkillInfo(SkillInfo_T& skillInfo){m_CurSkillInfo =skillInfo;}
	SkillInfo_T& GetCurSkillInfo(void){return m_CurSkillInfo;}
	const SkillInfo_T& GetCurSkillInfo(void) const{return m_CurSkillInfo;}
	void SwitchNextSkill(Obj_Character& rSelf,int nNextSkillId);
	//ɨ��
	void ScanEffectTargetList(Obj_Character& rSelf);
protected:
	SkillInfo_T m_CurSkillInfo;
	bool m_bIsActive;//�Ƿ�ʼ����
	bool m_bIsEffect;//�Ƿ�ʼ��Ч
};
POOLDEF_DECL(SkillBaseLogic);
#endif

