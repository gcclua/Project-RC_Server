
#ifndef _BASELIB_H_
#define _BASELIB_H_

/*
	����C����ʱ��
*/

#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "BaseType.h"

#if defined(_WIN32)
#include <direct.h>
#elif define(__LINUX__)
#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/time.h>
#endif

//Ϊset��map׼������׼C++������������erase�����޷���ֵ
template<typename _ContType>
typename _ContType::iterator _erase(_ContType &Cont, typename _ContType::iterator itRemove)
{
	typename _ContType::iterator itRet = itRemove;
	itRet++;
	Cont.erase(itRemove);
	return itRet;
}

/*
	������׼ģ���
*/
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <exception>
#include <algorithm>
#include <sstream>

#define BOOST_ALL_NO_LIB
#define BOOST_ENABLE_ASSERT_HANDLER
#define BOOST_SPIRIT_THREADSAFE

//date_time ���
#include "boost/date_time/gregorian/gregorian.hpp"

// �����ڶ���
#include "boost/static_assert.hpp"
#define  STATIC_ASSERT BOOST_STATIC_ASSERT


//�߳����
#include "pthread.h"
#include "boost/thread.hpp"
typedef boost::mutex bstMutex;
typedef boost::mutex::scoped_lock bstMutexScopedLock;

//����ָ��
#include "boost/shared_ptr.hpp"

// property_tree
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/system/error_code.hpp"

#endif