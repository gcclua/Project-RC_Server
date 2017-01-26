#include "GameStruct_Scene.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"
#include "GameInterface_Scene.h"

tfloat32 CalcDirection(const ScenePos &rPosStart, const ScenePos &rPosEnd)
{
	__ENTER_FUNCTION

		if (rPosStart != rPosEnd)
		{
			tfloat32 fZ = rPosEnd.m_fZ - rPosStart.m_fZ;
			tfloat32 fX = rPosEnd.m_fX - rPosStart.m_fX;
			tfloat32 fValue = ::atan2(fZ, fX);
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

void NormaliseDirection(tfloat32 &rDirection)
{
	__ENTER_FUNCTION

		if (rDirection >= _2PI)
		{
			rDirection -= (static_cast<tfloat32>(static_cast<tint32>(rDirection / _2PI)) * _2PI);
			rDirection = _MAX(rDirection, 0.0f);
			rDirection = _MIN(rDirection, _2PI);
			return;
		}
		if (rDirection < 0.0f)
		{
			rDirection += (static_cast<tfloat32>(static_cast<tint32>(-rDirection / _2PI) + 1) * _2PI);
			rDirection = _MAX(rDirection, 0.0f);
			rDirection = _MIN(rDirection, _2PI);
			return;
		}

		__LEAVE_FUNCTION
}

