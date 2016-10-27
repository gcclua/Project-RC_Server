#ifndef _GAMEINTERFACE_SCENEACTIVATION_H_
#define _GAMEINTERFACE_SCENEACTIVATION_H_

#include "Base.h"

namespace Packets
{
	class GC_UPDATE_SCENE_INSTACTIVATION_PAK;
}

class SceneActivationInterface
{
public:
	static void UpdateSceneClass(int nSceneClassID);
	static void UpdateSceneClassInstCount(int nSceneClassID, int nInstCount);
	static void UpdateSceneClassInstPlayerCount(int nSceneClassID, int nSceneInstID, int nPlayerCount);
	static bool FillSceneClassInstActivation(int nSceneClassID, Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAK &rPacket);
};

#endif
