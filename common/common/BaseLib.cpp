#include "BaseLib.h"
#include "Exception.h"
STATIC_ASSERT(sizeof(time_t) == 8);


#if defined(_WIN32)

namespace boost
{
	void tss_cleanup_implemented(){}
}
#include "libs/thread/src/win32/thread.cpp"
#include "libs/thread/src/win32/tss_dll.cpp"
#include "libs/thread/src/win32/tss_pe.cpp"

#else
#include "libs/thread/src/pthread/thread.cpp"
#include "libs/thread/src/pthread/once.cpp"
#endif


#include "Exception.h"
void boost::assertion_failed(char const * expr, char const * function, char const * file, long line)
{
	_do_assert_(file,(uint32)line,function,expr,expr,true);
}

void boost::assertion_failed_msg(char const * expr, char const * msg,char const * function, char const * file, long line)
{
	_do_assert_(file,(uint32)line,function,expr,msg,true);
}
