#include "../../common/json-util.h"
#include "../../event/event.pb.h"
#include "../../event/EventQueue.h"
#include "../GameEventHandler.h"
#include "../GameDataHandler.h"
#include "../../logic/Player.h"
#include "ProcessWorldEvent.h"
#include "../../logic/Broadcast_T.h"


void ProcessWorldEvent::handle(Event* e)
{
	if (!e)
	{
		return;
	}
	switch(e->cmd())
	{
	case EVENT_USER_BRAODCAST:
		processBroadcastMsg(e);
		break;
	case EVENT_WEB_BROADCAST:
		processWebBroadMsg(e);
		break;
	default:
		break;
	}
}


void ProcessWorldEvent::processBroadcastMsg(Event* e)
{
	if (!e)
	{
		return;
	}

	switch (e->state())
	{
	case Status_Normal_WG_UPBROADCAST:
		{
			if(e->has_se_rsecombroadcast() == true)
			{
				RseComBroadcast* pMsg = e->mutable_se_rsecombroadcast();
				GameDataHandler* pUserManager = eh_->getDataHandler();
				int nRegion = pMsg->region();
				if(nRegion>=0)
				{
					nRegion = serverConfig.getmapregion(nRegion);
					pMsg->set_region(nRegion);
				}
				pUserManager->AddBroadCast2Lst(pMsg);

				//const Broadcast_Dict* pBroadcastDict = g_BroadcastDict.GetTableByID(pMsg->id());
				//if ( pBroadcastDict && pBroadcastDict->GetIsOpen() == 1)
				//{

				//	string str;
				//	pMsg->SerializeToString(&str);

				//	int iMinLvl = pBroadcastDict->GetMinLv();
				//	int iMaxLvl = pBroadcastDict->GetMaxLv();

				//	if(iMinLvl == -1 && iMaxLvl == -1)
				//	{
				//		eh_->SendToAllOnlineUser(S2C_RseComBroadcast,str,pMsg->region(),false);
				//	}
				//	else
				//	{
				//		eh_->SendToAllOnlineUserByLevel(S2C_RseComBroadcast,str,iMinLvl,iMaxLvl,pMsg->region(),false);
				//	}
				//}
			}
		}
		break;
	default:
		break;
	}
}

void ProcessWorldEvent::processWebBroadMsg(Event* e)
{
	if (!e)
	{

		return;
	}
	Msg_WebBroadcast* pMsg = e->mutable_msg_webbroadcast();
	if (pMsg)
	{
		RseWebBroadcast rseWebBroadcast;
		rseWebBroadcast.set_content(pMsg->content());
		string str;
		rseWebBroadcast.SerializeToString(&str);
		eh_->SendToAllOnlineUser(S2C_RseWebBroadcast,str,pMsg->region(),false);
	}
}
