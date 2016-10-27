#ifndef _GAMEINTERFACE_SCENE_H_
#define _GAMEINTERFACE_SCENE_H_

#include "Base.h"
#include "GameStruct_Scene.h"

class Scene;
class GC_CHAT;

class SceneInterface
{
public:

public:
	static void BroadCastChatMsg2Scene(::GC_CHAT &rPacket);
	static void SendNoticeToUser(const int64 &rGuid, const char *szNotice);
	static void BroadcastNotice(const char *szNotice);
	static void BroadcastNoticeToSceneClass(SceneClassID nClassID,const char *szNotice);
	static void BroadcastNoticeToSceneInst(SceneID sceneid,const char *szNotice);
	static bool IsNameScreening(const char* szName,bool bScreeningSpecialSign);	//是否是过滤的名字	false否：true是
	static bool IsNameContainSpecialSign(const char* szName);//此函数仅在IsNameScreening中使用 名字是否含有特殊字符 false否 true是
	static void BroadCastSampleSystemChat2Scene(const char* strNotice);
	static void KickPlayerByGuid(const int64 &rGuid, int nReason);

};

#endif
