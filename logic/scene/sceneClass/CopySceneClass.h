#ifndef _COPYSCENECLASS_H_
#define _COPYSCENECLASS_H_

#include "SceneClass.h"
#include "Scene/Scene/CopyScene.h"

class CopySceneClass : public SceneClass
{
public:
	CopySceneClass(void);
	virtual ~CopySceneClass(void);

public:
	virtual EnterResult EnterTo(Obj_MarchPtr Ptr, int nSceneInst);
	virtual EnterResult EnterTo(Obj_MarchPtr Ptr);
	virtual EnterResult FirstEnterTo(Obj_MarchPtr Ptr);

public:
	virtual ChangeResult ChangeTo(Obj_MarchPtr Ptr, int nSceneInst);
	virtual ChangeResult ChangeTo(Obj_MarchPtr Ptr);
public:
	virtual bool ChangeFromCheck(const SceneID &rsid, const int64 &rGuid);
	virtual bool ChangeToCheck(const SceneID &rsid, const int64 &rGuid);

public:
	virtual int RemainCapacityA(SceneInstID nSceneInst);
	virtual int RemainCapacityB(SceneInstID nSceneInst);

protected:
	virtual int ReusingScene(void);
	virtual int EnlargeScene(void);
};
POOLDEF_DECL(CopySceneClass);

#endif
