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
	virtual EnterResult EnterTo(const March& rMarch, tint32 nSceneInst);
	virtual EnterResult EnterTo(const March& rMarch);
public:
	virtual EnterResult FirstEnterTo(const March& rMarch);

public:
	virtual ChangeResult ChangeTo(const March& rMarch, tint32 nSceneInst);
	virtual ChangeResult ChangeTo(const March& rMarch);
public:
	virtual bool ChangeFromCheck(const SceneID &rsid, const int64 &rGuid);
	virtual bool ChangeToCheck(const SceneID &rsid, const int64 &rGuid);


public:
	virtual tint32 ReusingScene(void);
	virtual tint32 EnlargeScene(void);


};
POOLDEF_DECL(MainSceneClass);

#endif
