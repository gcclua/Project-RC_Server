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
	virtual EnterResult EnterTo(const March& rMarch, int nSceneInst);
	virtual EnterResult EnterTo(const March& rMarch);
	virtual EnterResult FirstEnterTo(const March& rMarch);

public:
	virtual ChangeResult ChangeTo(const March& rMarch, int nSceneInst);
	virtual ChangeResult ChangeTo(const March& rMarch);
public:
	virtual bool ChangeFromCheck(const SceneID &rsid, const int64 &rGuid);
	virtual bool ChangeToCheck(const SceneID &rsid, const int64 &rGuid);

protected:
	virtual int ReusingScene(void);
	virtual int EnlargeScene(void);

};
POOLDEF_DECL(CopySceneClass);

#endif
