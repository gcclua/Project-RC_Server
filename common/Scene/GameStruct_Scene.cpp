#include "GameStruct_Scene.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"
#include "GameInterface_Scene.h"

float CalcDirection(const ScenePos &rPosStart, const ScenePos &rPosEnd)
{
	__ENTER_FUNCTION

	if (rPosStart != rPosEnd)
	{
		float fZ = (float)(rPosEnd.m_nZ - rPosStart.m_nZ);
		float fX = (float)(rPosEnd.m_nX - rPosStart.m_nX);
		float fValue = ::atan2(fZ, fX);
		fValue += _2PI;
		NormaliseDirection(fValue);
		return fValue;
	}
	else
	{
		return 0.0f;
	}

	__LEAVE_FUNCTION
	return 0.0f;
}

void NormaliseDirection(float &rDirection)
{
	__ENTER_FUNCTION

	if (rDirection >= _2PI)
	{
		rDirection -= (static_cast<int>(static_cast<int>(rDirection / _2PI)) * _2PI);
		rDirection = _MAX(rDirection, 0.0f);
		rDirection = _MIN(rDirection, _2PI);
		return;
	}
	if (rDirection < 0.0f)
	{
		rDirection += (static_cast<int>(static_cast<int>(-rDirection / _2PI) + 1) * _2PI);
		rDirection = _MAX(rDirection, 0.0f);
		rDirection = _MIN(rDirection, _2PI);
		return;
	}

	__LEAVE_FUNCTION
}

