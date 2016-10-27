#include "MainScene.h"
#include "Service/ServiceManager.h"
#include "Message/SceneMsg.h"
#include "Table/Table_SceneClass.h"

POOLDEF_IMPL(MainScene);
MainScene::MainScene( void )
{
	__ENTER_FUNCTION
	__LEAVE_FUNCTION
}

MainScene::~MainScene( void )
{

}

tint32 MainScene::GetRunState(void)
{
	switch (gServiceManager.GetStatus())
	{
	case ServiceManagerStatus::EMPTY:
		{
			AssertEx(false, "");
			return ServiceRunState::PAUSE;
		}
		break;
	case ServiceManagerStatus::OPENUP:
		{
			return ServiceRunState::PAUSE;
		}
		break;
	case ServiceManagerStatus::RUNNING:
	case ServiceManagerStatus::SHUTDOWN:
	case ServiceManagerStatus::FINALSAVE:
		{
			return ((m_nCurPlayerCount >= 1 || m_nEnteringPlayerCount >= 1) ? ServiceRunState::NORMAL : ServiceRunState::SLOWLY);
		}
		break;
	default:
		{
			AssertEx(false, "");
			return ServiceRunState::PAUSE;
		}
		break;
	}
}

void MainScene::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Scene::Tick(rTimeInfo);
	
	__LEAVE_FUNCTION
}

InvokerPtr MainScene::InitMyself(void)
{
	Initialize();

	tchar szInvokerName[64] = {0};
	sprintf_s(szInvokerName, sizeof(szInvokerName), "GeneralMainSceneInvoker(%d,%d)", GetSceneClassID(), GetSceneInstID());
	InvokerPtr Ptr(new GeneralMainSceneInvoker(*this, szInvokerName));
	return Ptr;
}

void MainScene::Initialize(void)
{
	__ENTER_FUNCTION

	//�ȸ�m_nScriptID��ֵ�ڵ���Scene::Initialize()����Ȼ�ڵ���OnSceneCreate �Լ�NpcInitʱ�ű�����invalid_id
	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(GetSceneClassID());
	AssertEx(pSceneClass, "");
	m_nScriptID = pSceneClass->GetScriptID();

	Scene::Initialize();
	
	__LEAVE_FUNCTION
}


void MainScene::OnSceneCreate()
{
	__ENTER_FUNCTION
		
	__LEAVE_FUNCTION
}

void MainScene::OnObjEnter(tint32 nID)
{
	__ENTER_FUNCTION
		ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}
	__LEAVE_FUNCTION
}
void MainScene::OnObjLeave(tint32 nID)
{
	__ENTER_FUNCTION
		ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}
	__LEAVE_FUNCTION
}
void MainScene::OnObjDie(tint32 nID,tint32 nKillerId)
{
	__ENTER_FUNCTION
		ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}
	__LEAVE_FUNCTION
}
