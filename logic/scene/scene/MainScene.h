#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "Scene.h"
#include "service/Invoker.h"

class MainScene : public Scene
{
public:
	MainScene(void);
	virtual ~MainScene(void);

public:
	virtual tint32 GetRunState(void);
public:
	virtual void Tick(const TimeInfo &rTimeInfo);

public:
	virtual InvokerPtr InitMyself(void);

public:
	virtual bool IsMainScene(void) const {return true;}
protected:
	void Initialize(void);

public:

	virtual void OnSceneCreate();
	virtual void OnObjEnter(tint32 nID);
	virtual void OnObjLeave(tint32 nID);
	virtual void OnObjDie(tint32 nID,tint32 nKillerId);


protected:
	tint32 m_nScriptID;
};

POOLDEF_DECL(MainScene);

typedef GeneralInvoker<MainScene, 125, 10000> GeneralMainSceneInvoker;

#endif
