#include "Login/GameInterface_Login.h"
#include "Message/LoginMsg.h"
#include "Service/MessageOp.h"
#include "Config.h"


void LoginInterface::KickPlayerByAccount(const ACCOUNTNAME &rAccount, tint32 nReason)
{
	__ENTER_FUNCTION

	if (rAccount.GetLength() > 0)
	{
		KickPlayerByAccountMsgPtr MsgPtr = POOLDEF_NEW(KickPlayerByAccountMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_szAccount = rAccount;
		MsgPtr->m_nReason = nReason;
		SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
	}

	__LEAVE_FUNCTION
}

void LoginInterface::ModifyVipCost(int64 rGuid, tint32 nVipCost)
{
	__ENTER_FUNCTION

	static tint32 nMinVipCost = 0;
	static tint32 nMaxVipCost = 100000000;

	tint32 nDestVipCost = nVipCost;
	nDestVipCost = _MAX(nMinVipCost, nDestVipCost);
	nDestVipCost = _MIN(nMaxVipCost, nDestVipCost);

	AskModifyVipCostMsgPtr MsgPtr = POOLDEF_NEW(AskModifyVipCostMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_Guid = rGuid;
	MsgPtr->m_nVipCost = nDestVipCost;
	SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

	__LEAVE_FUNCTION
}
