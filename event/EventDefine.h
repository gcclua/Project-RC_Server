#ifndef _EVENTDEFINE_H_
#define _EVENTDEFINE_H_

#pragma once

#include "../gamed/event/MessageDef.h"

#ifndef EVENT_BASE
#define EVENT_BASE 0

enum EVENT_DEFINE
{
	EVENT_UPDATE_WORKING_STATUS	= EVENT_BASE + 1,
	EVENT_USER_LOGIN,
	EVENT_USER_LOGOUT,
	EVENT_USER_AUTH,
	EVENT_TIMER,
	EVENT_SEND_REMOTE_USER,
	EVENT_GWG_FRIEND_REQUEST,
	EVETN_GWG_GAMESTAR_REQUEST,
	EVENT_UPDATE_FRIEND_CACHE,
	EVENT_UPDATE_STARINFO,	
	EVENT_GWG_CHECK_ATTACK,
	EVENT_STAR_STATE,	
	EVENT_USER_PRELOGIN,	//用户预加载
	//管理员命令
	EVENT_ADMIN = 2048,
	EVENT_ADMIN_PROFILE,
	EVENT_ADMIN_ADDEXP,
	EVENT_ADMIN_ADDCREDIT,
	EVENT_ADMIN_SETLEVEL,
	EVENT_ADMIN_BANCHAT,
	EVENT_ADMIN_BANLOGIN,
	EVENT_ADMIN_RELOAD,
	EVENT_ADMIN_CANATTACK,
	EVENT_WEB_INVITEFRIEND,
	EVENT_WEB_SENDGIFT,
	EVENT_WEB_SENDGIFTPLATID,
	EVENT_ADMIN_BANDWGUSER,
	EVENT_ADMIN_OPT,
	EVENT_WEB_PHOTO,
	EVENT_WEB_CALLBACKFRIEND,
	EVENT_WEB_CALLBACKFRIENDPLATID,
	EVENT_ADMIN_ADDHONOR,
};

enum Status_UpdateWorkingStatus 
{
	UpdateWorkingStatus_GW_Disconn = 0,
	UpdateWorkingStatus_WG_Disconn,
	UpdateWorkingStatus_GW_Conn,
	UpdateWorkingStatus_WG_Sync,
	UpdateWorkingStatus_GW_Sync,
	UpdateWorkingStatus_WG_Fin,

	UpdateWorkingStatus_GH_Disconn,
	UpdateWorkingStatus_HG_Disconn,
	UpdateWorkingStatus_GH_Conn,
	UpdateWorkingStatus_HG_Sync,
	UpdateWorkingStatus_GH_Sync,
	UpdateWorkingStatus_HG_Fin,

};

enum Status_UserLogin 
{
	UserLogin_WW_Req = 0,
	UserLogin_WG_Req,
	UserLogin_GW_Rsp,

	UserLogin_FG_Req,
	UserLogin_GF_Rsp,
};

enum Status_NormalStats
{
	Status_Normal_WW_Req = 0,
	Status_Normal_Game,
	Status_Normal_To_World,
	Status_Normal_Logic_Game,
	Status_Normal_Back_World,
	Status_Normal_Back_Game,

	Status_Normal_To_Star,
	Status_Normal_Star_Back,
	Status_Normal_StarSlf,

};

enum EventState
{
	EVENTSTATE_CG = 0,
	EVENTSTATE_CGW,
	EVENTSTATE_CGWG,
	EVENTSTATE_CGWGW,
	EVENTSTATE_CGWGWG,
};

enum Status_UserAuth 
{
	UserAuth_CG_Req = 0,
	UserAuth_GC_Rsp
};

enum Status_SendRemoteUser 
{
	SendRemoteUser_GW_Req = 0,
	SendRemoteUser_WG_Req
};

enum Status_Admin 
{
	Admin_AG_Req = 0,
	Admin_GW_Req,
	Admin_WG_Req,
	Admin_GW_Rsp,
	Admin_WG_Rsp,
	Admin_GA_Rsp,
	Admin_WW_Req,
};

#endif

#endif
