#include "SceneClass.h"
#include "Message/SceneMsg.h"
#include "Service/Service.h"

SceneClass::SceneClass( void )
{
	m_nSceneType = invalid_id;
	m_nClassID = invalid_id;
	m_nMaxPlayerCountA = 0;
	m_nMaxPlayerCountB = 0;
}

SceneClass::~SceneClass( void )
{

}

InvokerPtr SceneClass::FetchSceneInvoker(void)
{
	InvokerPtr Ptr;
	if (!m_InvokerPtrList.empty())
	{
		Ptr = m_InvokerPtrList.front();
		m_InvokerPtrList.pop_front();
	}
	return Ptr;
}

void SceneClass::AddSceneInvoker(const InvokerPtr Ptr)
{
	m_InvokerPtrList.push_back(Ptr);
}

void SceneClass::InitSceneObstacle(int nWidth, int nHeight, const char *szObstacleFileName)
{
	__ENTER_FUNCTION

	m_SceneObstacle.Init(nWidth, nHeight);
	m_SceneObstacle.Load(szObstacleFileName);
	m_SceneObstacle.Record(m_nClassID);

	__LEAVE_FUNCTION
}
