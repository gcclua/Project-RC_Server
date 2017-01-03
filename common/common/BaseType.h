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



///////////////////////////////////////////////////////////////////////
//�������ݺ궨��
///////////////////////////////////////////////////////////////////////

//IP��ַ���ַ���󳤶�
#define IP_SIZE			24
#define KEY_SIZE			64
#define MAX_WORLDCOUNT			256
#define TIMELENTH			23

#if defined(_WIN32)
#define __FUNCTION_NAME__ __FUNCTION__
#define		tvsnprintf		_vsnprintf
#define		tstricmp		_stricmp
#define		tsnprintf		_snprintf
#define	tatoll	_atoi64

#define WIN32_LEAN_AND_MEAN
#elif defined(__LINUX__)
#define __FUNCTION_NAME__ __PRETTY_FUNCTION__

#define tvsnprintf vsnprintf
#define tstricmp strcasecmp
#define tsnprintf snprintf
#define	tatoll	atoll
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
