#include "SL_ShunFa.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Obj/Obj_Character.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(SL_ShunFa);

//��ȡ����Ŀ������
int  SL_ShunFa::GetMaxTargetNum(void)//-1 ��ʾ����������
{
	__ENTER_FUNCTION
		if (false ==IsValid())
		{
			return -1;
		}
		Table_SkillEx const& rSkillEx=*m_CurSkillInfo.m_pSkillEx;
		int nMaxTargetNum =rSkillEx.GetLogicParambyIndex(MAXTARGETNUM);
		return nMaxTargetNum;
	__LEAVE_FUNCTION
		return -1;
}
