/********************************************************************************
 *	�ļ�����  Obj_ZombieUser.cpp
 *	ȫ·����  E:\Code\Server\Server\Server\Server\Scene\Obj\Obj_ZombieUser.cpp
 *	�����ˣ�  mwh
 *	����ʱ�䣺2014/03/06
 *
 *	����˵����
 *	�޸ļ�¼��
*********************************************************************************/
#include "Obj_Character.h"
#include "Obj_ZombieUser.h"
#include "Scene/GameDefine_Scene.h"
#include "Scene/AI/AIState.h"
#include "Scene/AI/AITransition.h"
#include "Scene/AI/AIController.h"
#include "Scene/Scene/Scene.h"
#include "CombatStruct/GameStruct_CombatAttr.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_TitleData.h"
#include "Table/Table_InitialCombatAttr.h"
#include "Packet/Packet/GC_CREATE_ZOMBIEUSER_PAK.h"
#include "Packet/Packet/GC_RET_RELIVE_PAK.h"
#include "Packet/Packet/GC_SYNC_ACTIVETITLE_PAK.h"
#include "Packet/Packet/GC_RET_ISWILDENEMY2USER_PAK.h"

// ����ʬ�����ʱ�� ��λ ����
#define ZOMBIE_USER_CORPSE_TIME 3000

// �����Զ�����ʱ�� ��λ ����
#define ZOMBIE_USER_AUTOALIVE_TIME 10000

POOLDEF_IMPL(Obj_ZombieUser);

// ��Ӧrolebase���е�����id
const tint32 g_ProfessionZombieDefaultDataID[PROFESSIONTYPE_T::TYPE_MAXNUM]  = {0, 1, 2, 3, 4};

Obj_ZombieUser::Obj_ZombieUser( ) : m_AIController( *this ), m_fPropertyPer(1.0f),m_nChallengeCase(0),
	m_nCreatorProfession(-1)
{
	m_bCanAutoRevive = false;
	m_nAutoReviveMillsecond = 0;
	m_nCorpseTime = 0;
	m_bStopAI = false;
	m_nLifeTime = invalid_id;
	m_fAttackFactor = 1.0f;
	m_fDefendFactor = 1.0f;
	m_nCurSkillIndex = 0;
	m_nOwnerId = invalid_id;
}

Obj_ZombieUser::~Obj_ZombieUser( )
{

}

bool Obj_ZombieUser::OnThreat(Obj_Character& rAttacker,tint32 nIncThreat)
{
	__ENTER_FUNCTION
		bool bRet =Obj_Character::OnThreat(rAttacker,nIncThreat);
		if (false ==bRet)
		{
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

void Obj_ZombieUser::Init( const ChallRankMember& rMember, tfloat32 fPropertyPer, tint32 nCase, tint32 nCreatorProfession )
{
	__ENTER_FUNCTION
	m_bStopAI = false;
	m_fPropertyPer = fPropertyPer;
	m_nChallengeCase = nCase;
	m_nCreatorProfession = nCreatorProfession; // �����ߵ�ְҵ
	m_AIProto.Adjust( m_fPropertyPer );
	m_MemberBase.CopyFrom(rMember.GetMemberBase());
	m_MemberAttr.CopyFrom( rMember.GetMemberAttr() );
	m_MemberFellow.CopyFrom( rMember.GetMemberFellow() );
	m_AIController.Init( m_AIProto);
	InitAI( );
	InitAttr( );
	InitSkillDbg( );
	__LEAVE_FUNCTION
}

void Obj_ZombieUser::Init( const ChallRankMember& rMember, const ZombieAIConfig& za, tint32 nIndex, tfloat32 fPropertyPer )
{
	__ENTER_FUNCTION
	m_bStopAI = false;
	m_AIProto = za;
	m_fPropertyPer = fPropertyPer;
	m_nChallengeCase = 0;
	m_nCreatorProfession = -1;
	m_AIProto.Adjust( m_fPropertyPer );
	m_MemberBase.CopyFrom(rMember.GetMemberBase());
	m_MemberAttr.CopyFrom( rMember.GetMemberAttr() );
	m_MemberFellow.CopyFrom( rMember.GetMemberFellow() );
	m_AIController.Init( m_AIProto);
	m_AIController.SetFollowIndex( nIndex );
	InitAI( );
	InitAttr( );
	InitSkillDbg( );
	__LEAVE_FUNCTION
}

void Obj_ZombieUser::InitAsSkillSummoned(const ChallRankMember& rMember, tint32 nLifeMillSeconds, tfloat32 fAttackFactor, tfloat32 fDefendFactor)
{
	__ENTER_FUNCTION
	m_bStopAI = false;
	m_fPropertyPer = 1.0f;
	m_AIProto.eAIAction = ATAT_SUMMONED;
	m_AIProto.nMaxAttackMilliSecond = 100;
	m_nChallengeCase = CRCASE_SKILL_SUMMONED;
	m_nCreatorProfession = invalid_id;
	m_MemberBase.CopyFrom(rMember.GetMemberBase());
	m_MemberAttr.CopyFrom(rMember.GetMemberAttr());
	m_MemberFellow.CopyFrom(rMember.GetMemberFellow());
	SetLifeTime(nLifeMillSeconds);
	m_fAttackFactor = fAttackFactor;
	m_fDefendFactor = fDefendFactor;
	m_AIController.Init(m_AIProto);
	InitAttr();
	InitLimitSkills(4);
	m_OwnSkillList[1] = invalid_id;
	__LEAVE_FUNCTION
}

void Obj_ZombieUser::InitSkillDbg( )
{
	__ENTER_FUNCTION

	for (tint32 i = 0; i < MAXOWNSKILL; i++) 
	{
		m_OwnSkillList[i] = GetMemberAttr().m_OwnSkillList[i];
	}

	__LEAVE_FUNCTION
}

void Obj_ZombieUser::InitLimitSkills(tint32 nSkillNum)
{
	__ENTER_FUNCTION

	for (tint32 i = 0; i < MAXOWNSKILL; i++)
	{
		m_OwnSkillList[i] = invalid_id;
	}
	if (nSkillNum <= 0)
	{
		return;
	}
	if (nSkillNum > MAXOWNSKILL)
	{
		nSkillNum = MAXOWNSKILL;
	}
	for (tint32 i = 0; i < nSkillNum; i++) 
	{
		m_OwnSkillList[i] = GetMemberAttr().m_OwnSkillList[i];
	}

	__LEAVE_FUNCTION
}

void Obj_ZombieUser::InitAI( )
{
	// ..�ű�����
	SetAIStop( true );
}

void Obj_ZombieUser::InitAttr( )
{
	__ENTER_FUNCTION

	tint32 nProfession = GetMemberBase().GetProfession();
	if (nProfession >= 0 && nProfession < PROFESSIONTYPE_T::TYPE_MAXNUM)
	{
		SetDataID( g_ProfessionZombieDefaultDataID[nProfession] );
	}
	
	SetForceType( FORCETYPE_T::USER_NORMAL ); // todo
	
	//����
	SetName(GetMemberBase().GetName());
	//�ȼ�
	SetLevel(GetMemberBase().GetLevel());

	// ..
	MarkZombieUserCalcDirty( );

	//ս��������� ��������
	MarkCombatAttrCalcDirty();

	__LEAVE_FUNCTION
}

void Obj_ZombieUser::CallFellow( )
{
	__ENTER_FUNCTION
	if (IsSceneValid())
	{
		if( GetMemberFellow().IsValid() == true )
		{
			Scene& rScene = GetScene();
			const ScenePos pos = GetFollowPos();
			Obj_FellowPtr fellowPtr = rScene.CreateFellow(GetMemberFellow().GetFellowData(), pos); //����Obj_Fellow
			if( fellowPtr )
			{
				//�������˵�ObjId �� Guid
				fellowPtr->SetOwnerGuid(GetMemberBase().GetGUID());
				fellowPtr->SetOwnerObjId(GetID());
			}
		}
	}
__LEAVE_FUNCTION
}

void Obj_ZombieUser::AddTitle(tint32 titleID)
{
	__ENTER_FUNCTION

		const Table_TitleData* pTitle = GetTable_TitleDataByID(titleID);
	if (pTitle != null_ptr)
	{
		Packets::GC_SYNC_ACTIVETITLE_PAK pak_sync;
		pak_sync.m_PacketData.set_serverid(GetID());
		pak_sync.m_PacketData.set_titleid(titleID);
		if (IsSceneValid())
		{
			Scene& rScene = GetScene();
			rScene.BroadCast_InSight_Except(pak_sync, GetID());
		}		
	}
			
	__LEAVE_FUNCTION
}
void Obj_ZombieUser::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT
	Obj_Character::Tick( rTimeInfo );
	TickAI( rTimeInfo );
	Tick_AliveStatus(rTimeInfo);
	Tick_DeadStatus(rTimeInfo);
	__LEAVE_PROTECT
}


void Obj_ZombieUser::TickAI( const TimeInfo &rTimeInfo )
{
	__ENTER_FUNCTION
	if(!m_bStopAI) m_AIController.Update( rTimeInfo );
	__LEAVE_FUNCTION
}


tint32 Obj_ZombieUser::GetRelationByForceType(Obj_Character& rUnit)
{
	__ENTER_FUNCTION

	tint32 nType = invalid_id;
	if (m_AIProto.eAIAction == ATAT_SUMMONED)
	{
		if (GetOwnerObjID() == rUnit.GetID())
		{
			nType = RELATIONTYPE_T::FRIEND;
		}
		else
		{
			Obj_CharacterPtr ownerPtr = GetOwnerCharacter();
			if (ownerPtr)
			{
				nType = ownerPtr->GetRelationByForceType(rUnit);
			}
		}
	}
	else
	{
		nType = Obj_Character::GetRelationByForceType(rUnit);
	}

	return nType;

	__LEAVE_FUNCTION
		return -1;
}

void Obj_ZombieUser::OnDie(Obj_Character& rKiller)
{
	__ENTER_FUNCTION
		Obj_Character::OnDie(rKiller);
	GetAIController().Refresh( );

	//������
	if (!IsSceneValid())
	{
		return;
	}

	//������ս
	LeaveCombat();

	//������
	GetScene().OnObjDie(GetID(), rKiller.GetID());

	// �������������
	if (m_bCanAutoRevive)
	{
		m_nAutoReviveMillsecond = ZOMBIE_USER_AUTOALIVE_TIME;
	}
	else
	{
		m_nCorpseTime = ZOMBIE_USER_CORPSE_TIME;
	}

	__LEAVE_FUNCTION
}
//�����˺�
void Obj_ZombieUser::OnReceiveDamage(DamagesInof_T& rDamage)
{
	//���û���Ĵ���
	Obj_Character::OnReceiveDamage(rDamage);
}
void Obj_ZombieUser::SendBaseAttr(Obj_User &rUser)
{
	__ENTER_FUNCTION

	Packets::GC_CREATE_ZOMBIEUSER_PAK pak;
	pak.m_PacketData.set_serverid(GetID());
	pak.m_PacketData.set_dataid(GetDataID());
	pak.m_PacketData.set_posx((tint32)(GetScenePos().m_fX * 100));
	pak.m_PacketData.set_posz((tint32)(GetScenePos().m_fZ * 100));
	pak.m_PacketData.set_sceneclass(GetSceneClassID());
	pak.m_PacketData.set_sceneinst(GetSceneInstID());
	pak.m_PacketData.set_curforce(GetForceType());
	pak.m_PacketData.set_isdie(IsDie());
	pak.m_PacketData.set_name(GetName().GetCText());
	pak.m_PacketData.set_facedir((tint32)(GetFaceDir()*100));
	pak.m_PacketData.set_movespeed((tint32)(GetMoveSpeed()*100));
	pak.m_PacketData.set_modelvisualid(m_MemberBase.GetModelVisualID());
	pak.m_PacketData.set_weaponid(m_MemberBase.GetWeapon());
	pak.m_PacketData.set_weaponeffectgem(m_MemberBase.GetWeaponEffectGem());
	pak.m_PacketData.set_stealthlev(m_nStealthLev);
	pak.m_PacketData.set_profession(GetProfession());
	pak.m_PacketData.set_bindparent(GetBindParent());
	pak.m_PacketData.add_bindchildren(GetBindChildren(0));
	pak.m_PacketData.add_bindchildren(GetBindChildren(1));
	pak.m_PacketData.add_bindchildren(GetBindChildren(2));
	pak.m_PacketData.add_bindchildren(GetBindChildren(3));
	rUser.SendPacket(pak);

	if(m_AIProto.eAIAction == ATAT_MERCENARY)
	{
		AddTitle(MERCENARY_TITLE_ID);
	}

	__LEAVE_FUNCTION
}
tint32 Obj_ZombieUser::GetInitialCombatAttrTableIndex(tint32 nProfessoin,tint32 nLevel) const
{
	__ENTER_FUNCTION
		for (int i = 0; i < GetTable_InitialCombatAttrCount(); i++)
		{
			const Table_InitialCombatAttr* pTable= GetTable_InitialCombatAttrByIndex(i);
			if (pTable!=null_ptr)
			{
				if (pTable->GetProfessionId() == nProfessoin &&
					pTable->GetLevel() == nLevel)
				{
					return i;
				}
			}
		}
		return -1;
		__LEAVE_FUNCTION
			return -1;
}

void Obj_ZombieUser::CalculateInitalAttr(void)
{
	__ENTER_FUNCTION
	//!!!���¼���ǰ ������
	m_InitialAttr.CleanUp();
	const ChallMemberBase& rBase = GetMemberBase();
	int nTableIndex =GetInitialCombatAttrTableIndex(m_nCreatorProfession,rBase.GetLevel()); // ���ô�����ְҵ����һ��
	if (nTableIndex ==-1)
	{
		nTableIndex =GetInitialCombatAttrTableIndex(rBase.GetProfession(),rBase.GetLevel()); // ���������ְҵû�м������,���ü���ְҵ�ٴμ���
	}
	if (nTableIndex ==-1)
	{ // �������ְҵҲû�м������,��ô�ͷ���
		return;
	}
	const Table_InitialCombatAttr* pInitalAttrInfo= GetTable_InitialCombatAttrByIndex(nTableIndex);
	if (pInitalAttrInfo ==null_ptr)
	{
		return;
	}
	const Table_InitialCombatAttr& rInitalAttrInfo =*pInitalAttrInfo;

	//��ʼ�� ����ս������ֵ
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::MAXHP),rInitalAttrInfo.GetMaxHp());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::MAXMP),rInitalAttrInfo.GetMaxMP());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::MAXXP),rInitalAttrInfo.GetMaxXP());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::PYSATTACK),_MAX( rInitalAttrInfo.GetPAttack(), rInitalAttrInfo.GetMAttack()));
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::MAGATTACK),_MAX( rInitalAttrInfo.GetPAttack(), rInitalAttrInfo.GetMAttack()));
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::PYSDEF),rInitalAttrInfo.GetPDefense());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::MAGDEF),rInitalAttrInfo.GetMdefense());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::HIT),rInitalAttrInfo.GetHit());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::DODGE),rInitalAttrInfo.GetDodge());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::CRITICAL),rInitalAttrInfo.GetCritical());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::DECRITICAL),rInitalAttrInfo.GetDeCritical());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::STRIKE),rInitalAttrInfo.GetStrike());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::DUCTICAL),rInitalAttrInfo.GetDuctical());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::CRITIADD),rInitalAttrInfo.GetCritiAdd());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::CRITIMIS),rInitalAttrInfo.GetCritiMis());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::ATTACKSPEED),rInitalAttrInfo.GetAttackSpeed());
	m_InitialAttr.SetCombatAttrByIndex((tint32)(COMBATATTR_T::MOVESPEED),rInitalAttrInfo.GetMoveSpeed());

	__LEAVE_FUNCTION
}
void Obj_ZombieUser::CalculateZombieUserRefix(void)
{
	__ENTER_FUNCTION
	//!!!���¼���ǰ ������
	m_ZombieUserCombatRefix.CleanUp( );

	const CombatAttr_Refix& rCombatRefix = GetMemberAttr( ).GetCombatAttr( );
	for (tint32 index=0; index<COMBATATTR_T::COMBATATTR_MAXNUM; ++index)
	{
		tint32 attrType = index;
		tint32 addvalue = rCombatRefix.GetRefixValueByIndex(attrType);
		tfloat32 addper = rCombatRefix.GetRefixPerByIndex(attrType);
		tint32 curValue = m_ZombieUserCombatRefix.GetRefixValueByIndex(attrType);
		tfloat32 curPer = m_ZombieUserCombatRefix.GetRefixPerByIndex(attrType);
		m_ZombieUserCombatRefix.SetRefixValueByIndex(attrType, curValue+addvalue);
		m_ZombieUserCombatRefix.SetRefixPerByIndex(attrType, curPer+addper);
	}

	__LEAVE_FUNCTION
}

void Obj_ZombieUser::CalculateFinalyAttr(void)
{
	__ENTER_FUNCTION
		bool isNeedCalculate=false;
	if (m_InitialAttr.IsCalculationFlagDirty())
	{
		CalculateInitalAttr();
		//������ɺ� �������
		m_InitialAttr.CleanAllCalculationDirtyFlag();
		isNeedCalculate=true;
	}

	if (m_SkillCombatRefix.IsCalculationFlagDirty())
	{
		CalculateSkillRefix();
		//������ɺ� �������
		m_SkillCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate=true;
	}
	if (m_BuffCombatRefix.IsCalculationFlagDirty())
	{
		CalculateBuffRefix();
		//������ɺ� �������
		m_BuffCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate=true;
	}

	if (m_ZombieUserCombatRefix.IsCalculationFlagDirty())
	{
		CalculateZombieUserRefix();
		//������ɺ� �������
		m_ZombieUserCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate=true;
	}

	//���¼��� ���յ�ս������ֵ
	if (isNeedCalculate)
	{
		m_FinalyAttr =m_InitialAttr*(m_SkillCombatRefix+m_BuffCombatRefix+m_ZombieUserCombatRefix);

		//TODO:���� m_fPropertyPer ��������ֵ
		tint32 nPropertyValD = (tint32) (m_fPropertyPer * 10);
		if( nPropertyValD < 10 && nPropertyValD > 0 )
		{
			for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
			{
				if( i == COMBATATTR_T::PYSATTACK ||
					i == COMBATATTR_T::MAGATTACK ||
					i == COMBATATTR_T::PYSDEF ||
					i == COMBATATTR_T::MAGDEF )
				{
					tint32 nCombatAttrVal = (tint32)(m_FinalyAttr.GetCombatAttrByIndex(i) * m_fPropertyPer);
					m_FinalyAttr.SetCombatAttrByIndex( i, nCombatAttrVal );
				}
			}
		}

		tfloat32 fHP = 1.0f, fAttack = 1.0f, fDef = 1.0f; // Ѫϵ��, ����ϵ��, ����ϵ��
		switch ( m_nChallengeCase )
		{
		case CRCASE_REFIX_NPC:
			fHP = 1.58f; fAttack = 0.88f; fDef = 1.0f;
			break;
		case CRCASE_MISSION37_USER:
			fHP = 1.0f; fAttack = 0.3f; fDef = 2.0f;
			break;
		case CRCASE_MISSION37_NPC:
			fHP = 1.13f; fAttack = 0.49f; fDef = 2.23f;
			break;
		case CRCASE_SKILL_SUMMONED:
			fHP = 1.0f; fAttack = m_fAttackFactor; fDef = m_fDefendFactor;
			break;
		default:
			break;
		}
		for (tint32 i=0;i<COMBATATTR_T::COMBATATTR_MAXNUM;i++)
		{
			if ( i == COMBATATTR_T::MAXHP )
			{ // Ѫ����
				tint32 nCombatAttrVal = (tint32)(m_FinalyAttr.GetCombatAttrByIndex(i) * fHP);
				m_FinalyAttr.SetCombatAttrByIndex( i, nCombatAttrVal );
			}
			else if( i == COMBATATTR_T::PYSATTACK ||
				i == COMBATATTR_T::MAGATTACK )
			{ // ������
				tint32 nCombatAttrVal = (tint32)(m_FinalyAttr.GetCombatAttrByIndex(i) * fAttack);
				m_FinalyAttr.SetCombatAttrByIndex( i, nCombatAttrVal );
			}
			else if ( i == COMBATATTR_T::PYSDEF ||
				i == COMBATATTR_T::MAGDEF )
			{ // ������
				tint32 nCombatAttrVal = (tint32)(m_FinalyAttr.GetCombatAttrByIndex(i) * fDef);
				m_FinalyAttr.SetCombatAttrByIndex( i, nCombatAttrVal );
			}
		}
		

		//-- ���ƶ��ٶ����20%������TM��
		tint32 nMoveSpeed = (tint32)(m_FinalyAttr.GetCombatAttrByIndex(COMBATATTR_T::MOVESPEED) * (1.0f+ZOMBIE_SPEED_UP));
		m_FinalyAttr.SetCombatAttrByIndex( COMBATATTR_T::MOVESPEED, nMoveSpeed );


		//��ǰѪ �� XP ��������ʱ ��������ǰֵΪ����ֵ 
		tint32 nMaxHp =GetCombatAttrByID((tint32)COMBATATTR_T::MAXHP);
		tint32 nMaxMp =GetCombatAttrByID((tint32)COMBATATTR_T::MAXMP);
		tint32 nMaxXp =GetCombatAttrByID((tint32)COMBATATTR_T::MAXXP);

		if (GetCurHp() >nMaxHp)
		{
			SetCurHp(nMaxHp);
		}
		if (GetCurMP() >nMaxMp)
		{
			SetCurMp(nMaxMp);
		}
		if (GetCurXP() >nMaxXp)
		{
			SetCurXp(nMaxXp);
		}
	}

	__LEAVE_FUNCTION
}
void Obj_ZombieUser::OnEnterScene(void)
{
	__ENTER_FUNCTION
		Obj_Character::OnEnterScene();
	SetCurHp(GetCombatAttrByID(static_cast<tint32>(COMBATATTR_T::MAXHP)));
	SetCurMp(GetCombatAttrByID(static_cast<tint32>(COMBATATTR_T::MAXMP)));
	__LEAVE_FUNCTION
}
//��ȡ����ս��������ֵ
tint32 Obj_ZombieUser::GetCombatAttrByID(tint32 AttrId)
{
	__ENTER_FUNCTION

		// �еݹ�����,ȥ��Σ�մ��� [7/16/2015 yuxiaoxi]
		//if (m_InitialAttr.IsCalculationFlagDirty() ||
		//	m_SkillCombatRefix.IsCalculationFlagDirty() ||
		//	m_BuffCombatRefix.IsCalculationFlagDirty() ||
		//	m_ZombieUserCombatRefix.IsCalculationFlagDirty( )
		//	)
		//{
		//	CalculateFinalyAttr();
		//}
		return m_FinalyAttr.GetCombatAttrByIndex(AttrId);
		__LEAVE_FUNCTION
			return 0;
}

bool  Obj_ZombieUser::IsPysicalAttack()//�﹥ 
{
	__ENTER_FUNCTION
		const tint32 nProfession = GetMemberBase().GetProfession( );
		return ProfessionUtility::IsPysicalAttack(nProfession);
	__LEAVE_FUNCTION
		return false;
}

bool  Obj_ZombieUser::IsMagicalAttack()//ħ��
{
	__ENTER_FUNCTION
		const tint32 nProfession = GetMemberBase().GetProfession();
		return ProfessionUtility::IsMagicalAttack(nProfession);
	__LEAVE_FUNCTION
		return false;
}
bool  Obj_ZombieUser::IsCloseCombat()//��ս
{
	__ENTER_FUNCTION
		const tint32 nProfession = GetMemberBase().GetProfession( );
		return ProfessionUtility::IsCloseCombat(nProfession);
	__LEAVE_FUNCTION
		return false;
}
bool  Obj_ZombieUser::IsLongCombat()//Զ��
{
	__ENTER_FUNCTION
		const tint32 nProfession = GetMemberBase().GetProfession( );
		return ProfessionUtility::IsLongCombat(nProfession);
	__LEAVE_FUNCTION
		return false;
}

Obj_CharacterPtr Obj_ZombieUser::GetOwnerCharacter()
{
	__ENTER_FUNCTION
		if (m_nOwnerId < 0)
		{
			return Obj_CharacterPtr();
		}
		if (IsSceneValid())
		{
			return GetScene().GetCharacterByID(m_nOwnerId);
		}
	__LEAVE_FUNCTION
		return Obj_CharacterPtr();
}

Obj_UserPtr Obj_ZombieUser::GetOwnerUser()
{
	__ENTER_FUNCTION
		if (m_nOwnerId < 0)
		{
			return Obj_UserPtr();
		}
		if (IsSceneValid())
		{
			return GetScene().GetUserByID(m_nOwnerId);
		}
	__LEAVE_FUNCTION
		return Obj_UserPtr();
}

tint32 Obj_ZombieUser::SelectSkill()
{
	__ENTER_FUNCTION

	tint32 nSkillId = invalid_id;
	for (tint32 i = 0; i < MAXOWNSKILL; ++ i)
	{
		m_nCurSkillIndex = m_nCurSkillIndex % MAXOWNSKILL;
		nSkillId = GetOwnSkillByIndex(m_nCurSkillIndex);
		if (nSkillId >= 54000 && nSkillId < 55000)//�����������֮��
		{
			++ m_nCurSkillIndex;
			continue;
		}
		if (nSkillId != invalid_id && GetTable_SkillExByID(nSkillId) != null_ptr)
		{
			break;
		}
		++ m_nCurSkillIndex;
	}

	if (nSkillId == invalid_id)
	{
		m_nCurSkillIndex = 0;
		nSkillId = GetOwnSkillByIndex( m_nCurSkillIndex );
	}

	++ m_nCurSkillIndex;
	
	return nSkillId;
	
	__LEAVE_FUNCTION
	
	return invalid_id;
}


void Obj_ZombieUser::AutoRevive( )
{
	__ENTER_FUNCTION
		if(IsSceneValid() == false)
			return;

	if (m_AIProto.eAIAction == ATAT_MERCENARY)
	{
		AddTitle(MERCENARY_TITLE_ID);
	}

	tint32 nMaxHp = GetCombatAttrByID(COMBATATTR_T::MAXHP);
	tint32 nMaxMp = GetCombatAttrByID(COMBATATTR_T::MAXMP);
	tint32 nMaxXp = GetCombatAttrByID(COMBATATTR_T::MAXXP);
	Relive(nMaxHp, nMaxMp, nMaxXp, RELIVE_ORIGINAL);

	Packets::GC_RET_RELIVE_PAK pak;
	pak.m_PacketData.set_objid(GetID());

	GetScene().BroadCast(pak);

	__LEAVE_FUNCTION
}

void Obj_ZombieUser::Tick_DeadStatus( const TimeInfo& rTimeInfo )
{
	__ENTER_FUNCTION

	if (!GetActive())
	{
		return;
	}
	if (!IsDie())
	{
		return;
	}

	if (m_bCanAutoRevive)
	{
		// �Զ�����
		m_nAutoReviveMillsecond -= rTimeInfo.m_uTimeElapse;
		if (m_nAutoReviveMillsecond <= 0)
		{
			AutoRevive();
			m_nAutoReviveMillsecond = ZOMBIE_USER_AUTOALIVE_TIME;
		}
	}
	else
	{
		// ʬ������
		m_nCorpseTime -= rTimeInfo.m_uTimeElapse;
		if (m_nCorpseTime <= 0)
		{
			DelFromScene();
		}
	}
	__LEAVE_FUNCTION
}

void Obj_ZombieUser::Tick_AliveStatus(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		if (GetActive() && IsAlive())
		{
			if (IsSummoned())
			{
				Obj_CharacterPtr ownerPtr = GetOwnerCharacter();
				if (ownerPtr)
				{
					if (!ownerPtr->GetActive() || !ownerPtr->IsAlive())
					{
						DelFromScene();
						return;
					}
				}
			}
			if (GetLifeTime() > 0)
			{
				tint32 nNewLifeTime = GetLifeTime() - rTimeInfo.m_uTimeElapse;
				if (nNewLifeTime < 0)
				{
					nNewLifeTime = 0;
				}
				SetLifeTime(nNewLifeTime);
			}
			if (GetLifeTime() == 0)
			{
				// �������� ɾ��
				DelFromScene();
			}
		}

	__LEAVE_FUNCTION
}
