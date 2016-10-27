#ifndef _MAINSCENECLASS_H_
#define _MAINSCENECLASS_H_

#include "SceneClass.h"
#include "Scene/Scene/MainScene.h"

class MainSceneClass : public SceneClass
{
public:
	MainSceneClass(void);
	virtual ~MainSceneClass(void);

public:
	virtual EnterResult EnterTo(Obj_MarchPtr Ptr, tint32 nSceneInst);
	virtual EnterResult EnterTo(Obj_MarchPtr Ptr);
public:
	virtual EnterResult FirstEnterTo(Obj_MarchPtr Ptr);

public:
	virtual ChangeResult ChangeTo(Obj_MarchPtr Ptr, tint32 nSceneInst);
	virtual ChangeResult ChangeTo(Obj_MarchPtr Ptr);
public:
	virtual bool ChangeFromCheck(const SceneID &rsid, const int64 &rGuid);
	virtual bool ChangeToCheck(const SceneID &rsid, const int64 &rGuid);

public:
	virtual tint32 RemainCapacityA(SceneInstID nSceneInst);
	virtual tint32 RemainCapacityB(SceneInstID nSceneInst);

public:
	virtual tint32 ReusingScene(void);
	virtual tint32 EnlargeScene(void);
};
POOLDEF_DECL(MainSceneClass);

#endif
