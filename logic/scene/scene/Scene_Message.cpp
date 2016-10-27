#include "Scene.h"
#include "Scene/GameInterface_Scene.h"
#include "Message/ChatMsg.h"
#include "Message/SceneMsg.h"
#include "Message/DBMsg.h"

//////////////////////////////////////////////////////////////////////////
//需要场景转发给March的相关Message定义

MESSAGE_TRANSPORTTOMARCH_IMPL(MarchReqNearListMsg);
MESSAGE_TRANSPORTTOMARCH_IMPL(MarchMoveMsg);



