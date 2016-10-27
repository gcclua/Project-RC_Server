#include "GameInterface_SceneActivation.h"
#include "Packet/Packet/GC_UPDATE_SCENE_INSTACTIVATION_PAK.h"
#define SA_INSTMAXCOUNT 8192
#define SA_CLASSMAXCOUNT 128

class SA_SceneInstInfo
{
public:
	SA_SceneInstInfo(void)
	{
		m_nPlayerCount = 0;
	}
public:
	void UpdatePlayerCount(int nPlayerCount)
	{
		m_nPlayerCount = nPlayerCount;
	}
public:
	int m_nPlayerCount;
};

class SA_SceneClassInfo
{
public:
	SA_SceneClassInfo(void)
	{
		m_bValid = false;
		m_nSceneInstCount = 0;
	}
public:
	void Update(void)
	{
		m_bValid = true;
	}
	void UpdateInstCount(int nInstCount)
	{
		if (m_bValid)
		{
			m_nSceneInstCount = nInstCount;
		}
	}
	void UpdateInstPlayerCount(int nSceneInstID, int nPlayerCount)
	{
		if (m_bValid)
		{
			if (nSceneInstID >= 0 && nSceneInstID < SA_INSTMAXCOUNT)
			{
				m_SceneInst[nSceneInstID].UpdatePlayerCount(nPlayerCount);
			}
		}
	}
	bool FillInstActivation(Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAK &rPacket)
	{
		if (m_bValid)
		{
			rPacket.m_PacketData.set_sceneinstcount(m_nSceneInstCount);
			rPacket.m_PacketData.add_sceneactivation(0);
			for (int i = 1; i < m_nSceneInstCount && i < SA_INSTMAXCOUNT; i++)
			{
				if (m_SceneInst[i].m_nPlayerCount > 0)
				{
					rPacket.m_PacketData.add_sceneactivation(i);
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	bool m_bValid;
	int m_nSceneInstCount;
	bsarray<SA_SceneInstInfo, SA_INSTMAXCOUNT> m_SceneInst;
};

class SA_SceneInfo
{
public:
	SA_SceneInfo(void)
	{
	}
public:
	void UpdateSceneClass(int nSceneClassID)
	{
		if (nSceneClassID >= 0 && nSceneClassID < SA_CLASSMAXCOUNT)
		{
			m_SceneClass[nSceneClassID].Update();
		}
	}
	void UpdateSceneClassInstCount(int nSceneClassID, int nInstCount)
	{
		if (nSceneClassID >= 0 && nSceneClassID < SA_CLASSMAXCOUNT)
		{
			m_SceneClass[nSceneClassID].UpdateInstCount(nInstCount);
		}
	}
	void UpdateSceneClassInstPlayerCount(int nSceneClassID, int nSceneInstID, int nPlayerCount)
	{
		if (nSceneClassID >= 0 && nSceneClassID < SA_CLASSMAXCOUNT)
		{
			m_SceneClass[nSceneClassID].UpdateInstPlayerCount(nSceneInstID, nPlayerCount);
		}
	}
	bool FillSceneClassInstActivation(int nSceneClassID, Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAK &rPacket)
	{
		if (nSceneClassID >= 0 && nSceneClassID < SA_CLASSMAXCOUNT)
		{
			rPacket.m_PacketData.set_sceneclassid(nSceneClassID);
			if (m_SceneClass[nSceneClassID].FillInstActivation(rPacket))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
public:
	bsarray<SA_SceneClassInfo, SA_CLASSMAXCOUNT> m_SceneClass;
};

static SA_SceneInfo s_SA_SceneInfo;

void SceneActivationInterface::UpdateSceneClass(int nSceneClassID)
{
	s_SA_SceneInfo.UpdateSceneClass(nSceneClassID);
}

void SceneActivationInterface::UpdateSceneClassInstCount(int nSceneClassID, int nInstCount)
{
	s_SA_SceneInfo.UpdateSceneClassInstCount(nSceneClassID, nInstCount);
}

void SceneActivationInterface::UpdateSceneClassInstPlayerCount(int nSceneClassID, int nSceneInstID, int nPlayerCount)
{
	s_SA_SceneInfo.UpdateSceneClassInstPlayerCount(nSceneClassID, nSceneInstID, nPlayerCount);
}

bool SceneActivationInterface::FillSceneClassInstActivation(int nSceneClassID, Packets::GC_UPDATE_SCENE_INSTACTIVATION_PAK &rPacket)
{
	return s_SA_SceneInfo.FillSceneClassInstActivation(nSceneClassID, rPacket);
}
