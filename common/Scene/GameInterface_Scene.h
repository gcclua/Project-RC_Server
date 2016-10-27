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
	static bool IsNameScreening(const char* szName,bool bScreeningSpecialSign);	//�Ƿ��ǹ��˵�����	false��true��
	static bool IsNameContainSpecialSign(const char* szName);//�˺�������IsNameScreening��ʹ�� �����Ƿ��������ַ� false�� true��
	static void BroadCastSampleSystemChat2Scene(const char* strNotice);
	static void KickPlayerByGuid(const int64 &rGuid, int nReason);

};

#endif
