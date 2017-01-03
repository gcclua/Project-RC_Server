#ifndef _SCANOPERATOR_H_
#define _SCANOPERATOR_H_

#include "Scene/Obj/Obj.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Obj/Obj_Npc.h"
#include "Scene/Obj/Obj_March.h"
#include "Scene/obj/Obj_Hero.h"
#include "Scene/obj/Obj_Troop.h"

//////////////////////////////////////////////////////////////////////////
//Obj类型过滤
class Scan_ObjFilter_All
{
public:
	bool operator()(ObjPtr &rPtr)
	{
		return true;
	}
public:
	Obj *Cast(ObjPtr &rPtr)
	{
		return (*this)(rPtr) ? rPtr.get() : null_ptr;
	}
};

class Scan_ObjFilter_Character
{
public:
	bool operator()(ObjPtr &rPtr)
	{
		return rPtr->IsCharacter();
	}
public:
	Obj_Character *Cast(ObjPtr &rPtr)
	{
		return (*this)(rPtr) ? static_cast<Obj_Character *>(rPtr.get()) : null_ptr;
	}
};

class Scan_ObjFilter_March
{
public:
	bool operator()(ObjPtr &rPtr)
	{
		return rPtr->IsMarch();
	}
public:
	Obj_March *Cast(ObjPtr &rPtr)
	{
		return (*this)(rPtr) ? static_cast<Obj_March *>(rPtr.get()) : null_ptr;
	}
};

class Scan_ObjFilter_Npc
{
public:
	bool operator()(ObjPtr &rPtr)
	{
		return rPtr->IsNpc();
	}
public:
	Obj_Npc *Cast(ObjPtr &rPtr)
	{
		return (*this)(rPtr) ? static_cast<Obj_Npc *>(rPtr.get()) : null_ptr;
	}
};

//////////////////////////////////////////////////////////////////////////
//扫描区域过滤
class Scan_AreaFilter_All
{
public:
	bool operator()(ObjPtr &rPtr)
	{
		return true;
	}
};

class Scan_AreaFilter_Ring
{
public:
	ScenePos m_OriginalPos;
	float m_fMinDistance;
	float m_fMaxDistance;
public:
	bool operator()(ObjPtr &rPtr)
	{
		float fDistance = m_OriginalPos.Distance(rPtr->GetScenePos());
		return ((fDistance >= m_fMinDistance) && (fDistance <= m_fMaxDistance));
	}
};

class Scan_AreaFilter_Circle
{
public:
	ScenePos m_OriginalPos;
	float m_fRadius;
public:
	bool operator()(ObjPtr &rPtr)
	{
		float fDistance = m_OriginalPos.Distance(rPtr->GetScenePos());
		return (fDistance <= m_fRadius);
	}
};

class Scan_AreaFilter_Sector
{
public:
	ScenePos m_OriginalPos;
	float m_fRadius;
	float m_fDirBegin;
	float m_fDirEnd;
public:
	bool operator()(ObjPtr &rPtr)
	{
		float fDistance = m_OriginalPos.Distance(rPtr->GetScenePos());
		if (fDistance <= m_fRadius)
		{
			float fDirection = CalcDirection(m_OriginalPos, rPtr->GetScenePos());
			if (m_fDirBegin < m_fDirEnd)
			{
				return (fDirection >= m_fDirBegin && fDirection <= m_fDirEnd);
			}
			else
			{
				return ((fDirection >= m_fDirBegin && fDirection <= _2PI) || (fDirection >= 0.0f && fDirection <= m_fDirEnd));
			}
		}
		else
		{
			return false;
		}
	}
};

class Scan_AreaFilter_Ray
{
public:
	ScenePos m_OriginalPos;
	ScenePos m_DestinationPos;
	float m_fScope;
public:
	bool operator()(ObjPtr &rPtr)
	{
		ScenePos VerifyPos = rPtr->GetScenePos();
		int InPrd =
			(m_DestinationPos.m_nX - m_OriginalPos.m_nX) * (VerifyPos.m_nX - m_OriginalPos.m_nX) +
			(m_DestinationPos.m_nZ - m_OriginalPos.m_nZ) * (VerifyPos.m_nZ - m_OriginalPos.m_nZ);
		if (InPrd >= 0)
		{
			int AbsValue =
				(m_DestinationPos.m_nX - m_OriginalPos.m_nX) * (m_DestinationPos.m_nX - m_OriginalPos.m_nX) +
				(m_DestinationPos.m_nZ - m_OriginalPos.m_nZ) * (m_DestinationPos.m_nZ - m_OriginalPos.m_nZ);
			float fR = (float)InPrd / AbsValue;
			if (fR <= 1.0f)
			{
				ScenePos ProjectionPos;
				ProjectionPos.m_nX = (int)(m_OriginalPos.m_nX + (m_DestinationPos.m_nX - m_OriginalPos.m_nX) * fR);
				ProjectionPos.m_nZ = (int)(m_OriginalPos.m_nZ + (m_DestinationPos.m_nZ - m_OriginalPos.m_nZ) * fR);

				float fDistance = VerifyPos.Distance(ProjectionPos);
				if (fDistance <= m_fScope)
				{
					return true;
				}
			}
		}
		return false;
	}
};

//////////////////////////////////////////////////////////////////////////
//过滤容器
template<typename _RefCont,
		 typename _ObjFilter,
		 typename _AreaFilter>
class GeneralScanner
{
public:
	_ObjFilter m_of;
	_AreaFilter m_af;
public:
	void operator()(_RefCont &Cont, ObjPtr &rPtr)
	{
		if (m_of(rPtr))
		{
			if (m_af(rPtr))
			{
				Cont.Append(m_of.Cast(rPtr));
			}
		}
	}
};

//////////////////////////////////////////////////////////////////////////
//过滤容器实例
typedef GeneralScanner<ObjRefCont, Scan_ObjFilter_All, Scan_AreaFilter_All> ScannerAllAll;
typedef GeneralScanner<ObjRefCont, Scan_ObjFilter_All, Scan_AreaFilter_Ring> ScannerAllRing;
typedef GeneralScanner<ObjRefCont, Scan_ObjFilter_All, Scan_AreaFilter_Circle> ScannerAllCircle;
typedef GeneralScanner<ObjRefCont, Scan_ObjFilter_All, Scan_AreaFilter_Sector> ScannerAllSector;
typedef GeneralScanner<ObjRefCont, Scan_ObjFilter_All, Scan_AreaFilter_Ray> ScannerAllRay;

typedef GeneralScanner<CharacterRefCont, Scan_ObjFilter_Character, Scan_AreaFilter_All> ScannerCharacterAll;
typedef GeneralScanner<CharacterRefCont, Scan_ObjFilter_Character, Scan_AreaFilter_Ring> ScannerCharacterRing;
typedef GeneralScanner<CharacterRefCont, Scan_ObjFilter_Character, Scan_AreaFilter_Circle> ScannerCharacterCircle;
typedef GeneralScanner<CharacterRefCont, Scan_ObjFilter_Character, Scan_AreaFilter_Sector> ScannerCharacterSector;
typedef GeneralScanner<CharacterRefCont, Scan_ObjFilter_Character, Scan_AreaFilter_Ray> ScannerCharacterRay;

typedef GeneralScanner<MarchRefCont, Scan_ObjFilter_March, Scan_AreaFilter_All> ScannerMarchAll;
typedef GeneralScanner<MarchRefCont, Scan_ObjFilter_March, Scan_AreaFilter_Ring> ScannerMarchRing;
typedef GeneralScanner<MarchRefCont, Scan_ObjFilter_March, Scan_AreaFilter_Circle> ScannerMarchCircle;
typedef GeneralScanner<MarchRefCont, Scan_ObjFilter_March, Scan_AreaFilter_Sector> ScannerMarchSector;
typedef GeneralScanner<MarchRefCont, Scan_ObjFilter_March, Scan_AreaFilter_Ray> ScannerMarchRay;

typedef GeneralScanner<NpcRefCont, Scan_ObjFilter_Npc, Scan_AreaFilter_All> ScannerNpcAll;
typedef GeneralScanner<NpcRefCont, Scan_ObjFilter_Npc, Scan_AreaFilter_Ring> ScannerNpcRing;
typedef GeneralScanner<NpcRefCont, Scan_ObjFilter_Npc, Scan_AreaFilter_Circle> ScannerNpcCircle;
typedef GeneralScanner<NpcRefCont, Scan_ObjFilter_Npc, Scan_AreaFilter_Sector> ScannerNpcSector;
typedef GeneralScanner<NpcRefCont, Scan_ObjFilter_Npc, Scan_AreaFilter_Ray> ScannerNpcRay;

//////////////////////////////////////////////////////////////////////////
//判定仿函数
//"<"判定，第一个Obj到指定点的距离比第二个小
class Pred_ObjDistanceLess
{
public:
	explicit Pred_ObjDistanceLess(const ScenePos &rPos)
		: m_OriginalPos(rPos)
	{
	}
public:
	ScenePos m_OriginalPos;
public:
	bool operator()(const Obj *p1, const Obj *p2)
	{
		AssertEx(p1 != null_ptr, "");
		AssertEx(p2 != null_ptr, "");
		float fDistance1 = m_OriginalPos.Distance(p1->GetScenePos());
		float fDistance2 = m_OriginalPos.Distance(p2->GetScenePos());
		return (fDistance1 < fDistance2);
	}
};

//"=="判定，Obj的ID与指定ID相同
class Pred_ObjIDEqual
{
public:
	explicit Pred_ObjIDEqual(int nID)
		: m_nID(nID)
	{
	}
public:
	int m_nID;
public:
	bool operator()(const Obj &rObj) const
	{
		return (rObj.GetID() == m_nID);
	}
};

#endif
