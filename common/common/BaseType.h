/////////////////////////////////////////////////////////////////////////////////
//�ļ����ƣ�BaseType.h
//����������ϵͳ�ײ����ͻ����ļ�������Ȩ��Ա�����޸Ĵ��ļ�����
//�汾˵����Windows����ϵͳ��Ҫ����꣺__WINDOWS__
//			Linux����ϵͳ��Ҫ����꣺__LINUX__
//�޸������
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __BASETYPE_H__
#define __BASETYPE_H__



/////////////////////////////////////////////////////////////////////////////////
//������ϢԤ�����
/////////////////////////////////////////////////////////////////////////////////
#ifndef FD_SETSIZE
#define FD_SETSIZE      1024
#endif /* FD_SETSIZE */


/////////////////////////////////////////////////////////////////////////////////
//��ǰ������ϵͳͷ�ļ�����
/////////////////////////////////////////////////////////////////////////////////
#if defined(__WINDOWS__)
	#pragma warning ( disable : 4786 )
	#include <Windows.h>
	#include "crtdbg.h"
#elif defined(__LINUX__)
	#include <sys/types.h>
	#include <pthread.h>
	#include <execinfo.h>
	#include <signal.h>
	#include <exception>
	#include <setjmp.h>
	#include <sys/epoll.h>
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <stdarg.h>


///////////////////////////////////////////////////////////////////////
//��׼�������Ͷ���
///////////////////////////////////////////////////////////////////////
typedef unsigned short	uint16;			//��׼�޷���short
typedef short			int16;			//��׼short

typedef uint16			PacketID_t;
typedef long long       int64;
typedef char			int8;			//��׼char
typedef unsigned char	uint8;			//��׼�޷���char

typedef char				tint8;
typedef unsigned char		tuint8;
typedef char				tchar;
typedef unsigned char		tbyte;

typedef short				tint16;
typedef unsigned short		tuint16;
typedef unsigned short		tword;

typedef int					tint32;
typedef unsigned int		tuint32;
typedef unsigned int		tdword;

typedef long long			tint64;
typedef unsigned long long	tuint64;

typedef float				tfloat32;
typedef double				tfloat64;

#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64) || defined (_WIN64)
typedef tint64				tintptr;
typedef tfloat64			tfloatptr;
#else
typedef tint32				tintptr;
typedef tfloat32			tfloatptr;
#endif


typedef unsigned int uint32;

#define OVER_MAX_SERVER 256

//��Ч�ľ��
#define INVALID_HANDLE	-1
//��Ч��IDֵ
#define INVALID_ID		-1
// ���ַ���
#define null_ptr         NULL

#define invalid_id (-1)
#define invalid_guid64 (0)

//�ļ�·�����ַ���󳤶�
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

//���winsock��ͻ
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef WIN32
#include <ext/hash_map>
using namespace __gnu_cxx;
namespace __gnu_cxx
{

	template<>
	struct hash<long long>
	{

		size_t
			operator()(long long __x) const
		{
			return __x;
		}
	} ;

	template<>
	struct hash<std::string>
	{

		size_t
			operator()(std::string __s) const
		{
			return __stl_hash_string(__s.c_str());
		}
	} ;
}
#else
#include <hash_map>
using namespace stdext;
#endif


///////////////////////////////////////////////////////////////////////
//�������ݺ궨��
///////////////////////////////////////////////////////////////////////

//IP��ַ���ַ���󳤶�
#define IP_SIZE			24
#define KEY_SIZE			64
#define MAX_WORLDCOUNT			256
#define TIMELENTH			23

#if defined(_WIN32)
#define		tvsnprintf		_vsnprintf
#define		tstricmp		_stricmp
#define		tsnprintf		_snprintf
#elif defined(__LINUX__)
#define		tvsnprintf		vsnprintf
#define		tstricmp		strcasecmp
#define		tsnprintf		snprintf
#endif

///////////////////////////////////////////////////////////////////////
//����Ԥ����궨��
///////////////////////////////////////////////////////////////////////
#if defined(NDEBUG)
	#define __ENTER_FUNCTION_FOXNET if(1){
	#define __LEAVE_FUNCTION_FOXNET }
#else
	#define __ENTER_FUNCTION_FOXNET if(1){
	#define __LEAVE_FUNCTION_FOXNET }
#endif

#define _MAX(a,b) (((a) > (b)) ? (a) : (b))
#define _MIN(a,b) (((a) < (b)) ? (a) : (b))
#define _ABS(a)	((a) < 0 ? -(a) : (a))

#define _PI 3.141592f
#define _2PI 6.283185f

#define _45FLOAT2INT(val) (val >= 0.0f ? (static_cast<int>(val + 0.5f)) : (static_cast<int>(val - 0.5f)))

//����ָ��ֵɾ���ڴ�
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
//����ָ��ֵɾ�����������ڴ�
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
//����ָ�����free�ӿ�
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
//����ָ�����Release�ӿ�
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif


#endif
