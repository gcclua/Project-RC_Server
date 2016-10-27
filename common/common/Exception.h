
#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "BaseType.h"
#include "BaseLib.h"

/*
	AssertEx���ԣ����ʧ��->��ӡassert��־->����->�����׳�һ���쳣
	_do_assert_���̰߳�ȫ�ģ����AssertEXҲ��
*/

void _do_assert_(const char* szFile,uint32 nLine,const char* szFunc,const char* szExpr,const char* szMsg,bool bReThrow);

#define AssertEx(expr,msg) \
{\
	if (!(expr)) \
{\
	_do_assert_(__FILE__,__LINE__,__FUNCTION__,#expr,msg,true); \
}\
}

#define __ENTER_FUNCTION  {try{

#define __LEAVE_FUNCTION \
}\
	catch(const std::exception &err) \
{\
	AssertEx(false,err.what()); \
}\
	catch (const std::string &err) \
{\
	AssertEx(false,err.c_str()); \
}\
	catch (const char* err) \
{\
	AssertEx(false,err); \
}\
catch(...)\
{\
AssertEx(false,__FUNCTION__); \
}\
}

/*
	VerifyEx���ԣ���AssertEx���񣬵��ǲ��ܳ��쳣
*/
#define VerifyEx(expr,msg) \
{\
	if (!(expr)) \
{\
	_do_assert_(__FILE__,__LINE__,__FUNCTION__,#expr,msg,false); \
}\
}

/*
��__ENTER_FUNCTION��__LEAVE_FUNCTION���ƣ������ڼ��쳣���ᱻ���񣬵����׳�
*/

#define __ENTER_PROTECT  {try{

#define __LEAVE_PROTECT \
}\
	catch(const std::exception &err) \
{\
	VerifyEx(false,err.what()); \
}\
	catch (const std::string &err) \
{\
	VerifyEx(false,err.c_str()); \
}\
	catch (const char* err) \
{\
	VerifyEx(false,err); \
}\
	catch(...)\
{\
	VerifyEx(false,__FUNCTION__); \
}\
}

/*
��__ENTER_PROTECT��__ENTER_PROTECT���ƣ������ڼ��쳣���ᱻ���񣬵����׳�

*/

#define __ENTER_PROTECT_EX \
{\
	bool _bExpCatched = false; \
	try\
    {
#define __CATCH_PROTECT_EX \
} \
catch(const std::exception &err) \
{\
	VerifyEx(false,err.what()); \
	_bExpCatched = true;\
}\
	catch (const std::string &err) \
{\
	VerifyEx(false,err.c_str()); \
	_bExpCatched = true;\
}\
	catch (const char* err) \
{\
	VerifyEx(false,err); \
	_bExpCatched = true;\
}\
	catch(...)\
{\
	VerifyEx(false,__FUNCTION__); \
	_bExpCatched = true;\
}\
	if (_bExpCatched) \
	{


#define __LEAVE_PROTECT_EX \
}\
}
	

#endif