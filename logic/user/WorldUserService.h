
#ifndef _WORLDUSERSERVICE_H_
#define _WORLDUSERSERVICE_H_

#include "Base.h"
#include "service/Invoker.h"
#include "service/Service.h"
#include "User.h"
#include "user/GameDefine_User.h"

class MarchEnterSceneMsg;
class RetMarchMoveMsg;


class WorldUserService :public Service
{
public:
	explicit WorldUserService();
	virtual ~WorldUserService(void);

public:
	friend class GamePlayerManager;

public:
	virtual int GetServiceID(void){return ServiceID::WORLDUSER;}

public:
	virtual void Init(void);
	virtual void Tick(const TimeInfo &rTimeInfo);

protected:
	virtual void Shutdown(void);

public:
	virtual void HandleMessage(const RetMarchMoveMsg &rMsg);	
	
	MESSAGE_TRANSPORTTOUSER_DECL(MarchRetNearListMsg);

private:
	UserPtr			GetUserByGuid(int64 guid);


public:

	// 保存玩家信息
	void Tick_User(const TimeInfo &rTimeInfo);

private:

	UserPtrMap m_mapUser;
};


typedef GeneralInvoker<WorldUserService,200,200> WorldUserInvoker;


#endif