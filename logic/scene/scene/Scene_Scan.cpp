#include "Scene.h"

void Scene::Scan_All_All(ObjRefCont &Cont)
{
	__ENTER_FUNCTION

	ScannerAllAll Scanner;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_All_Ring(ObjRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance)
{
	__ENTER_FUNCTION

	ScannerAllRing Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fMinDistance = fMinDistance;
	Scanner.m_af.m_fMaxDistance = fMaxDistance;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_All_Circle(ObjRefCont &Cont, ScenePos OriginalPos, float fRadius)
{
	__ENTER_FUNCTION

	ScannerAllCircle Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_All_Sector(ObjRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian)
{
	__ENTER_FUNCTION

	ScannerAllSector Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;

	NormaliseDirection(fDirection);
	fRadian = _MAX(fRadian, 0.1f);
	fRadian = _MIN(fRadian, _2PI - 0.1f);

	Scanner.m_af.m_fDirBegin = (fDirection - fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirBegin);
	Scanner.m_af.m_fDirEnd = (fDirection + fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirEnd);

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_All_Ray(ObjRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope)
{
	__ENTER_FUNCTION

	ScannerAllRay Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;

	NormaliseDirection(fDirection);
	fLength = _MAX(fLength, 0.1f);
	fScope = _MAX(fScope, 0.1f);

	Scanner.m_af.m_DestinationPos.m_nX = (int)(Scanner.m_af.m_OriginalPos.m_nX + fLength * ::cos(fDirection));
	Scanner.m_af.m_DestinationPos.m_nZ = (int)(Scanner.m_af.m_OriginalPos.m_nZ + fLength * ::sin(fDirection));

	Scanner.m_af.m_fScope = fScope;

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Character_All(CharacterRefCont &Cont)
{
	__ENTER_FUNCTION

	ScannerCharacterAll Scanner;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Character_Ring(CharacterRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance)
{
	__ENTER_FUNCTION

	ScannerCharacterRing Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fMinDistance = fMinDistance;
	Scanner.m_af.m_fMaxDistance = fMaxDistance;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Character_Circle(CharacterRefCont &Cont, ScenePos OriginalPos, float fRadius)
{
	__ENTER_FUNCTION

	ScannerCharacterCircle Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Character_Sector(CharacterRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian)
{
	__ENTER_FUNCTION

	ScannerCharacterSector Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;

	NormaliseDirection(fDirection);
	fRadian = _MAX(fRadian, 0.1f);
	fRadian = _MIN(fRadian, _2PI - 0.1f);

	Scanner.m_af.m_fDirBegin = (fDirection - fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirBegin);
	Scanner.m_af.m_fDirEnd = (fDirection + fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirEnd);

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Character_Ray(CharacterRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope)
{
	__ENTER_FUNCTION

	ScannerCharacterRay Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;

	NormaliseDirection(fDirection);
	fLength = _MAX(fLength, 0.1f);
	fScope = _MAX(fScope, 0.1f);

	Scanner.m_af.m_DestinationPos.m_nX = (int)(Scanner.m_af.m_OriginalPos.m_nX + fLength * ::cos(fDirection));
	Scanner.m_af.m_DestinationPos.m_nZ = (int)(Scanner.m_af.m_OriginalPos.m_nZ + fLength * ::sin(fDirection));

	Scanner.m_af.m_fScope = fScope;

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_March_All(MarchRefCont &Cont)
{
	__ENTER_FUNCTION

	ScannerMarchAll Scanner;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_March_Ring(MarchRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance)
{
	__ENTER_FUNCTION

	ScannerMarchRing Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fMinDistance = fMinDistance;
	Scanner.m_af.m_fMaxDistance = fMaxDistance;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_March_Circle(MarchRefCont &Cont, ScenePos OriginalPos, float fRadius)
{
	__ENTER_FUNCTION

	ScannerMarchCircle Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_March_Sector(MarchRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian)
{
	__ENTER_FUNCTION

	ScannerMarchSector Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;

	NormaliseDirection(fDirection);
	fRadian = _MAX(fRadian, 0.1f);
	fRadian = _MIN(fRadian, _2PI - 0.1f);

	Scanner.m_af.m_fDirBegin = (fDirection - fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirBegin);
	Scanner.m_af.m_fDirEnd = (fDirection + fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirEnd);

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_March_Ray(MarchRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope)
{
	__ENTER_FUNCTION

	ScannerMarchRay Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;

	NormaliseDirection(fDirection);
	fLength = _MAX(fLength, 0.1f);
	fScope = _MAX(fScope, 0.1f);

	Scanner.m_af.m_DestinationPos.m_nX = (int)(Scanner.m_af.m_OriginalPos.m_nX + fLength * ::cos(fDirection));
	Scanner.m_af.m_DestinationPos.m_nZ = (int)(Scanner.m_af.m_OriginalPos.m_nZ + fLength * ::sin(fDirection));

	Scanner.m_af.m_fScope = fScope;

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Npc_All(NpcRefCont &Cont)
{
	__ENTER_FUNCTION

	ScannerNpcAll Scanner;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Npc_Ring(NpcRefCont &Cont, ScenePos OriginalPos, float fMinDistance, float fMaxDistance)
{
	__ENTER_FUNCTION

	ScannerNpcRing Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fMinDistance = fMinDistance;
	Scanner.m_af.m_fMaxDistance = fMaxDistance;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Npc_Circle(NpcRefCont &Cont, ScenePos OriginalPos, float fRadius)
{
	__ENTER_FUNCTION

	ScannerNpcCircle Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;
	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Npc_Sector(NpcRefCont &Cont, ScenePos OriginalPos, float fRadius, float fDirection, float fRadian)
{
	__ENTER_FUNCTION

	ScannerNpcSector Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;
	Scanner.m_af.m_fRadius = fRadius;

	NormaliseDirection(fDirection);
	fRadian = _MAX(fRadian, 0.1f);
	fRadian = _MIN(fRadian, _2PI - 0.1f);

	Scanner.m_af.m_fDirBegin = (fDirection - fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirBegin);
	Scanner.m_af.m_fDirEnd = (fDirection + fRadian / 2.0f);
	NormaliseDirection(Scanner.m_af.m_fDirEnd);

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

void Scene::Scan_Npc_Ray(NpcRefCont &Cont, ScenePos OriginalPos, float fDirection, float fLength, float fScope)
{
	__ENTER_FUNCTION

	ScannerNpcRay Scanner;
	Scanner.m_af.m_OriginalPos = OriginalPos;

	NormaliseDirection(fDirection);
	fLength = _MAX(fLength, 0.1f);
	fScope = _MAX(fScope, 0.1f);

	Scanner.m_af.m_DestinationPos.m_nX = (int)(Scanner.m_af.m_OriginalPos.m_nX + fLength * ::cos(fDirection));
	Scanner.m_af.m_DestinationPos.m_nZ = (int)(Scanner.m_af.m_OriginalPos.m_nZ + fLength * ::sin(fDirection));

	Scanner.m_af.m_fScope = fScope;

	Scan(Cont, Scanner);

	__LEAVE_FUNCTION
}

Obj_MarchPtr Scene::GetMarchByGuid(int64 guid)
{
	__ENTER_FUNCTION

		Obj_MarchPtr PtrRet;
	for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); it++)
	{
		AssertEx((*it).second, "");
		if ((*it).second->GetActive())
		{
			if ((*it).second->IsMarch())
			{
				Obj_MarchPtr Ptr = boost::static_pointer_cast<Obj_March, Obj>((*it).second);
				if (Ptr)
				{
					if (Ptr->GetGuid() == guid)
					{
						PtrRet = Ptr;
						break;
					}
				}
			}
		}
	}
	return PtrRet;

	__LEAVE_FUNCTION
		return Obj_MarchPtr();
}

Obj_MarchPtr Scene::GetMarchByID(int nObjID)
{
	__ENTER_FUNCTION
	Obj_MarchPtr PtrRet;
	ObjPtr Ptr = GetObjByID(nObjID);
	if (Ptr)
	{
		if (Ptr->IsMarch())
		{
			PtrRet = boost::static_pointer_cast<Obj_March, Obj>(Ptr);
		}
	}
	return PtrRet;

	__LEAVE_FUNCTION
		return Obj_MarchPtr();
}
