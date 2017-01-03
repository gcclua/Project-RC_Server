#ifndef _GUIDGENERATOR_H_
#define _GUIDGENERATOR_H_

#include "BaseType.h"
#include "BaseLib.h"
#include "Exception.h"

class GuidGenerator
{
public:
	GuidGenerator(void);
	~GuidGenerator(void);

public:
	bool	Init( tuint8 Type,int64 Serial);
	int64	Gen(void);
private:
	void	SaveSerial(void);
	void	IncreaseSerial(int64& rSerial, tint32 nValue);
private:
	bstMutex	m_bstMutex;
	tuint8		m_Type;
	int64	    m_NextAvailableSerial;
	int64	    m_CurrentSavedSerial;
private:
	bool		m_bInited;
};

#define GUIDDEF_INST(GUIDTYPE) \
	g##GUIDTYPE##GuidGenerator
#define GUIDDEF_DECL(GUIDTYPE) \
	extern GuidGenerator GUIDDEF_INST(GUIDTYPE)
#define GUIDDEF_IMPL(GUIDTYPE) \
	GuidGenerator GUIDDEF_INST(GUIDTYPE)
#define GUIDDEF_INIT(GUIDTYPE, TYPEVALUE, SERIAL) \
	GUIDDEF_INST(GUIDTYPE).Init(TYPEVALUE, SERIAL)
#define GUIDDEF_GEN(GUIDTYPE) \
	GUIDDEF_INST(GUIDTYPE).Gen()

#endif
