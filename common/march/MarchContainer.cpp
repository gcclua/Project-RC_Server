#include "MarchContainer.h"
#include "DBStruct/DBStruct_March.h"


MarchContainer::MarchContainer()
{
	CleanUp();
}

MarchContainer::~MarchContainer()
{

}

MarchContainer& MarchContainer::operator=(const MarchContainer& rhs)
{
	if (this != &rhs)
	{
		CopyFrom(rhs);
	}
	return *this;
}

void MarchContainer::CopyFrom(const MarchContainer& rhs)
{
	__ENTER_FUNCTION

	m_MarchContainer = rhs.m_MarchContainer;
	m_nOpenSlotCount = rhs.m_nOpenSlotCount;
	m_DirtyFlags = rhs.m_DirtyFlags;

	__LEAVE_FUNCTION
}

void MarchContainer::CleanUp(void)
{
	__ENTER_FUNCTION
	
	for (tint32 nIndex=0; nIndex<m_MarchContainer.GetSize(); ++nIndex)
	{
		March* pSlot = GetSlot(nIndex);
		if (pSlot != null_ptr)
		{
			March& rMarch = *pSlot;
			rMarch.CleanUp();
		}
	}
	ClearAllDirtyFlags();
	m_nOpenSlotCount = LIST_SIZE;

	__LEAVE_FUNCTION
}

tint32 MarchContainer::GetSlotCount(void) const
{
	__ENTER_FUNCTION
	
	AssertEx(m_nOpenSlotCount > 0 && m_nOpenSlotCount <= m_MarchContainer.GetSize(), "OpenSlotCount Error!");
	return m_nOpenSlotCount;

	__LEAVE_FUNCTION
	return 0;
}

void MarchContainer::SetSlotCount(tint32 nCount)
{
	__ENTER_FUNCTION
	
	AssertEx(nCount > 0 && nCount <= m_MarchContainer.GetSize(), "");
	m_nOpenSlotCount = nCount;

	__LEAVE_FUNCTION
}

tint32 MarchContainer::GetEmptySlotCount(void) const
{
	__ENTER_FUNCTION
	
	tint32 nRetCount = 0;
	tint32 nOpenCount = GetSlotCount();
	for (tint32 nIndex=0; nIndex<m_nOpenSlotCount; ++nIndex)
	{
		const March* pSlot = GetSlot(nIndex);
		if (pSlot != null_ptr)
		{
			const March rMarch = *pSlot;
			if (rMarch.GetMarchId() <= 0)
			{
				++nRetCount;
			}
		}
	}
	return nRetCount;

	__LEAVE_FUNCTION
	return 0;
}

tint32 MarchContainer::GetIndexByGuid(const int64 rMarchGuid) const
{
	__ENTER_FUNCTION
	
	tint32 nOpenCount = GetSlotCount();
	for (tint32 nIndex=0; nIndex<nOpenCount; ++nIndex)
	{
		const March* pSlot = GetSlot(nIndex);
		if (pSlot != null_ptr)
		{
			const March& rMarch = *pSlot;
			if (rMarch.IsValid() == true)
			{
				if (rMarch.GetMarchId() == rMarchGuid)
				{
					return nIndex;
				}
			}
		}
	}
	return -1;

	__LEAVE_FUNCTION
	return -1;
}

tint32 MarchContainer::FindFirstEmptySlotIndex(tint32 StartSlot /*= 0*/) const
{
	__ENTER_FUNCTION
	
	tint32 nOpenCount = GetSlotCount();
	for (tint32 nIndex=StartSlot; nIndex<nOpenCount; ++nIndex)
	{
		const March* pSlot = GetSlot(nIndex);
		if (pSlot != null_ptr)
		{
			const March& rMarch = *pSlot;
			if (rMarch.IsValid() == false) //ע��������false
			{
				return nIndex;
			}
		}
	}
	return -1;

	__LEAVE_FUNCTION
	return -1;
}

bool MarchContainer::IsMarchGuidValid(const int64 rMarchGuid) const
{
	__ENTER_FUNCTION
	
	tint32 nOpenCount = GetSlotCount();
	for (tint32 nIndex=0; nIndex<nOpenCount; ++nIndex)
	{
		const March* pSlot = GetSlot(nIndex);
		if (pSlot != null_ptr)
		{
			const March& rMarch = *pSlot;
			if (rMarch.GetMarchId() == rMarchGuid)
			{
				return true;
			}
		}
	}
	return false;

	__LEAVE_FUNCTION
	return false;
}

March const& MarchContainer::GetMarchByGuid(const int64 rMarchGuid) const
{
	__ENTER_FUNCTION
	
	tint32 nOpenCount = GetSlotCount();
	for (tint32 nIndex=0; nIndex<nOpenCount; ++nIndex)
	{
		const March* pSlot = GetSlot(nIndex);
		if (pSlot != null_ptr)
		{
			const March& rMarch = *pSlot;

			if (rMarch.GetMarchId() == rMarchGuid)
			{
				return rMarch;
			}
		}
	}
	//����ߵ����� ǰ���жϳ����� ֱ��Assert
	//ʹ��Get�ӿ�֮ǰû���ж�IsValid
	AssertEx(false, "");
	return *GetSlot(0);

	__LEAVE_FUNCTION
	return *GetSlot(0);
}

bool MarchContainer::IsMarchIndexValid(tint32 nIndex) const
{
	__ENTER_FUNCTION
	
	return (GetSlot(nIndex) != null_ptr);

	__LEAVE_FUNCTION
	return false;
}

March const& MarchContainer::GetMarchByIndex(tint32 nIndex) const
{
	__ENTER_FUNCTION
	
	AssertEx(GetSlot(nIndex) != null_ptr, "");
	return *GetSlot(nIndex);

	__LEAVE_FUNCTION
	return *GetSlot(0);
}


bool MarchContainer::AddMarch(const March& rMarch)
{
	__ENTER_FUNCTION
	
	bool bRet = false;
	March oMarch = rMarch; //����
	if (oMarch.GetMarchId() > 0)
	{
		tint32 nOpenCount = GetSlotCount();
		for (tint32 nIndex=0; nIndex<nOpenCount; ++nIndex)
		{
			March* pSlot = GetSlot(nIndex);//ȡ��constָ��
			if (pSlot != null_ptr)
			{
				March& rMarch = *pSlot;//ȡ��const����
				if (rMarch.GetMarchId()<=0)
				{
					//�ҵ��ո���
					rMarch = oMarch;//��ֵ
					SetSlotDirty(nIndex, true);
					oMarch.CleanUp();
					bRet = true;
					break;
				}
			}
		}
	}
	return bRet;

	__LEAVE_FUNCTION
	return false;
}

bool MarchContainer::CreateMarch(March& rMarch, int64 nBuildId)
{
	__ENTER_FUNCTION

	bool bRet = false;
	rMarch.SetBuildId(nBuildId);
	rMarch.SetStatus(MARCHSTATUS_IDEAL);
	
	return bRet;

	__LEAVE_FUNCTION
	return false;
}

bool MarchContainer::AddMarchByBuildId(int64 nBuildId)
{
	__ENTER_FUNCTION
	
	bool bRet = false;
	March oMarch;
	if (CreateMarch(oMarch, nBuildId) == true)
	{
		if (AddMarch(oMarch))
		{
			bRet = true;
		}
	}
	return bRet;

	__LEAVE_FUNCTION
	return false;
}

bool MarchContainer::UpdateMarchByIndex(const March& rMarch, tint32 nIndex)
{
	__ENTER_FUNCTION
	
	bool bRet = false;
	March* pSlot = GetSlot(nIndex);
	if (pSlot != null_ptr)
	{
		March& rSlot = *pSlot;
		rSlot = rMarch;
		SetSlotDirty(nIndex, true);

		bRet = true;
	}
	return bRet;

	__LEAVE_FUNCTION
	return false;
}

bool MarchContainer::UpdateMarchByGuid(const March& rMarch, const int64 rMarchGuid)
{
	__ENTER_FUNCTION
	
	bool bRet = false;
	if (rMarchGuid == invalid_guid64)
	{
		return bRet;
	}

	tint32 nOpenCount = GetSlotCount();
	for (tint32 nIndex=0; nIndex<nOpenCount; ++nIndex)
	{
		March* pSlot = GetSlot(nIndex); //ȡ��constָ��
		if (pSlot != null_ptr)
		{
			March& rSlot = *pSlot; //ȡ��const����

			if (rSlot.GetMarchId() == rMarchGuid)
			{
				rSlot = rMarch;
				SetSlotDirty(nIndex, true);
				bRet = true;
			}
		}
	}
	return bRet;

	__LEAVE_FUNCTION
	return false;
}

bool MarchContainer::CanAddMarch(const March& rMarch)
{
	__ENTER_FUNCTION
	
	if (rMarch.GetMarchId() > 0 )
	{
		tint32 nOpenCount = GetSlotCount();
		for (tint32 nIndex=0; nIndex<nOpenCount; ++nIndex)
		{
			March* pSlot = GetSlot(nIndex);//ȡ��constָ��
			if (pSlot != null_ptr)
			{
				March& rMarch = *pSlot;//ȡ��const����
				if (rMarch.GetMarchId() <=0)
				{
					return true;
				}
			}
		}
	}
	return false;

	__LEAVE_FUNCTION
	return false;
}

void  MarchContainer::SerializeFromDB(const DBMarchList& rDBMarchList)
{
	__ENTER_FUNCTION
		for (tint32 index = 0;index<LIST_SIZE;index++)
		{
			March* pMarch = GetSlot(index);
			AssertEx(pMarch,"");
			pMarch->SerializeFromDB(rDBMarchList.m_March[index]);
		}
	__LEAVE_FUNCTION
}

void MarchContainer::SerializeToDB(DBMarchList& rDBMarchList, tint32& nIndex) const
{
	__ENTER_FUNCTION

	for (tint32 index=0; index<LIST_SIZE; index++)
	{
		if (IsMarchIndexValid(index))
		{
			const March& rMarch = GetMarchByIndex(index);
			if (rMarch.GetMarchId()>0)
			{
				if (nIndex >= 0 && nIndex < MARCH_MAX_COUNT)					// march�������
				{
					rMarch.SerializeToDB(rDBMarchList.m_March[nIndex]);
					nIndex++;
				}
			}
		}
	}
	
	__LEAVE_FUNCTION
}
