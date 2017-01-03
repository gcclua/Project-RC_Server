#include "GuidGenerator.h"
#include "Message/DBMsg.h"
#include "Service/MessageOp.h"

GuidGenerator::GuidGenerator( void )
{
	m_Type = 0xff;
	m_NextAvailableSerial = 0xffffffff;
	m_CurrentSavedSerial = 0xffffffff;

	m_bInited = false;
}

GuidGenerator::~GuidGenerator( void )
{
	
}

bool GuidGenerator::Init( tuint8 Type, int64 Serial )
{
	__ENTER_FUNCTION

	bstMutexScopedLock LockGuard(m_bstMutex);

	AssertEx(m_bInited == false, "");

	m_Type = Type;

	m_NextAvailableSerial = Serial;

	m_CurrentSavedSerial = Serial;

	m_bInited = true;

	CacheLog(LOGDEF_INST(Guid), "guid generator init  type(%u),  serial(%u)",
		static_cast<tuint32>(Type),
		static_cast<tuint32>(Serial));

	return true;

	__LEAVE_FUNCTION
	return false;
}

int64 GuidGenerator::Gen( void )
{
	__ENTER_FUNCTION

	bstMutexScopedLock LockGuard(m_bstMutex);

	AssertEx(m_bInited == true, "");

	if (m_NextAvailableSerial >= m_CurrentSavedSerial)
	{
		IncreaseSerial(m_CurrentSavedSerial, 1);
		SaveSerial();
	}

	IncreaseSerial(m_NextAvailableSerial, 1);

	CacheLog(LOGDEF_INST(Guid), "guid generator gen type(%u), serial(%u)",
		static_cast<tuint32>(m_Type),
		static_cast<tuint32>(m_NextAvailableSerial));

	return m_NextAvailableSerial;

	__LEAVE_FUNCTION
	return invalid_guid64;
}

void GuidGenerator::SaveSerial( void )
{
	__ENTER_FUNCTION

	int64 Temp = m_CurrentSavedSerial;
	IncreaseSerial(Temp, 2048);

	DBReqSaveGuidMsgPtr MsgPtr = POOLDEF_NEW(DBReqSaveGuidMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_Type = m_Type;
	MsgPtr->m_Serial = Temp;
	SendMessage2Srv(ServiceID::DBAGENT, MsgPtr);

	CacheLog(LOGDEF_INST(Guid), "guid generator saveserial type(%u), serial(%lld)",
		static_cast<tuint32>(m_Type),Temp);

	__LEAVE_FUNCTION
}

void GuidGenerator::IncreaseSerial( int64& rSerial, tint32 nValue )
{
	__ENTER_FUNCTION

	const static int64 MaxSerialValue = 0xFFFF0000L;

	AssertEx(nValue > 0 && nValue <= 4096, "");

	int64 uTemp = rSerial + nValue;
	AssertEx(uTemp > rSerial, "");

	if (uTemp < MaxSerialValue)
	{
		rSerial = uTemp;
	}
	else
	{
		rSerial = (uTemp % MaxSerialValue);
	}

	__LEAVE_FUNCTION
}
