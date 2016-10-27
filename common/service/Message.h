
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "Base.h"

class BaseService;

class Message
{
public:
	Message(void);
	virtual ~Message(void);

public:
	virtual void ReflectHandle(BaseService &rService) const =0;

public:
	int64 m_ReceiverGuid ; //接受逻辑的用户ＩＤ
	int   m_nCount;
};

typedef boost::shared_ptr<Message> MessagePtr;
typedef boost::shared_ptr<const Message> ConstMessagePtr;
typedef tslist<ConstMessagePtr> ConstMessagePtrTSList;

#define MESSAGE_REFLECTHANDLE_DECL \
virtual void ReflectHandle(BaseService &rService) const;

#define  MESSAGE_REFLECTHANDLE_IMPL(MSGCLASS) \
void MSGCLASS::ReflectHandle(BaseService &rService) const \
{\
	__ENTER_FUNCTION \
	rService.HandleMessage(*this); \
   __LEAVE_FUNCTION \
}

#define MESSAGE_DEF_BEGIN(MSGCLASS) \
class MSGCLASS : public Message \
{ \
public: \
	MSGCLASS(void){} \
	virtual ~MSGCLASS(void){} \
public:\
	MESSAGE_REFLECTHANDLE_DECL \
public:

#define MESSAGE_DEF_END(MSGCLASS) \
}; \
POOLDEF_DECL(MSGCLASS);

#define MESSAGE_IMPL(MSGCLASS) \
POOLDEF_IMPL(MSGCLASS); \
MESSAGE_REFLECTHANDLE_IMPL(MSGCLASS);

#endif