#include "LibNetwork.h"

#if _WIN32

#include <io.h>
#include <fcntl.h>
#include <string.h>

class WindowsSocketAutoInit
{
public:
	WindowsSocketAutoInit(void)
	{
		tword wVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		tint32 err = WSAStartup(wVersion, &wsaData);
	}
	~WindowsSocketAutoInit(void)
	{
		WSACleanup();
	}
}_wsai;

#elif __LINUX__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>

extern tint32 errno;

#endif

void FileAPI::close_ex( tint32 fd )
{
#if __LINUX__
	if (close(fd) < 0)
	{
		switch (errno)
		{
		case EBADF : 
		default :
			{
				break;
			}
		}
	}
#elif _WIN32
	if (_close(fd) < 0)
	{
	}
#endif
}

tint32 FileAPI::fcntl_ex( tint32 fd, tint32 cmd, long arg )
{
#if __LINUX__
	tint32 result = fcntl (fd, cmd, arg);
	if (result < 0)
	{
		switch (errno)
		{
		case EINTR : 
		case EINVAL : 
		case EBADF : 
		case EACCES : 
		case EAGAIN : 
		case EDEADLK : 
		case EMFILE  : 
		case ENOLCK : 
		default : 
			{
				break;
			}
		}
	}
	return result;
#elif _WIN32
	return 0;
#endif
}

bool FileAPI::getfilenonblocking_ex( tint32 fd )
{
#if __LINUX__
	tint32 flags = fcntl_ex(fd, F_GETFL, 0);
	return flags | O_NONBLOCK;
#elif _WIN32
	return false;
#endif
}

void FileAPI::setfilenonblocking_ex( tint32 fd, bool on )
{
#if __LINUX__
	tint32 flags = fcntl_ex(fd, F_GETFL, 0);
	if (on)
	{
		// make nonblocking fd
		flags |= O_NONBLOCK;
	}
	else
	{
		// make blocking fd
		flags &= ~O_NONBLOCK;
	}
	fcntl_ex(fd, F_SETFL, flags);
#elif _WIN32
#endif
}

void FileAPI::ioctl_ex( tint32 fd, tint32 request, void* argp )
{
#if __LINUX__
	if (ioctl(fd,request,argp) < 0)
	{
		switch (errno)
		{
		case EBADF : 
		case ENOTTY : 
		case EINVAL : 
		default :
			{
				break;
			}
		}
	}
#elif _WIN32
#endif
}

tuint32 FileAPI::availablefile_ex( tint32 fd )
{
#if __LINUX__
	tuint32 arg = 0;
	ioctl_ex(fd,FIONREAD,&arg);
	return arg;
#elif _WIN32
	return 0;
#endif
}

const tint32 SOCKET_ERROR_WOULDBLOCK = -100;

#define _ESIZE 256
tchar Error[_ESIZE] ;

const tchar* SocketAPI::getsocketerror_ex( void )
{
	Error[_ESIZE - 1] = '\0';
	return Error;
}

SOCKET SocketAPI::socket_ex( tint32 domain, tint32 type, tint32 protocol )
{
	SOCKET s = ::socket(domain,type,protocol);

	if ( s == INVALID_SOCKET ) 
	{
#if __LINUX__
		switch ( errno ) 
		{
		case EPROTONOSUPPORT :
		case EMFILE : 
		case ENFILE : 
		case EACCES : 
		case ENOBUFS : 
		default : 
			{
				break;
			}
		}//end of switch
#elif _WIN32
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( Error, "WSAEAFNOSUPPORT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( Error, "WSAEMFILE", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAEPROTONOSUPPORT : 
			strncpy( Error, "WSAEPROTONOSUPPORT", _ESIZE ) ;
			break ;
		case WSAEPROTOTYPE : 
			strncpy( Error, "WSAEPROTOTYPE", _ESIZE ) ;
			break ;
		case WSAESOCKTNOSUPPORT : 
			strncpy( Error, "WSAESOCKTNOSUPPORT", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
	}

	return s;
}

bool SocketAPI::bind_ex( SOCKET s , const struct sockaddr * addr , tuint32 addrlen )
{
	if ( bind ( s , addr , addrlen ) == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{
		case EADDRINUSE :
		case EINVAL : 
		case EACCES : 
		case ENOTSOCK : 
		case EBADF : 
		case EROFS : 
		case EFAULT : 
		case ENAMETOOLONG : 
		case ENOENT : 
		case ENOMEM : 
		case ENOTDIR : 
		case ELOOP : 
		default :
			{
				break;
			}
		}//end of switch
#elif _WIN32
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSAESOCKTNOSUPPORT", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( Error, "WSAEADDRINUSE", _ESIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( Error, "WSAEADDRNOTAVAIL", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif

		return false ;
	}

	return true ;
}

bool SocketAPI::connect_ex( SOCKET s , const struct sockaddr * addr , tuint32 addrlen )
{
	if ( connect(s,addr,addrlen) == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) {
		case EALREADY : 
		case EINPROGRESS : 
		case ECONNREFUSED : 
		case EISCONN : 
		case ETIMEDOUT : 
		case ENETUNREACH : 
		case EADDRINUSE : 
		case EBADF : 
		case EFAULT : 
		case ENOTSOCK : 
		default :
			{
				break;
			}
		}//end of switch
#elif _WIN32
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( Error, "WSAEADDRINUSE", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEALREADY : 
			strncpy( Error, "WSAEALREADY", _ESIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( Error, "WSAEADDRNOTAVAIL", _ESIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( Error, "WSAEAFNOSUPPORT", _ESIZE ) ;
			break ;
		case WSAECONNREFUSED : 
			strncpy( Error, "WSAECONNREFUSED", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEISCONN : 
			strncpy( Error, "WSAEISCONN", _ESIZE ) ;
			break ;
		case WSAENETUNREACH : 
			strncpy( Error, "WSAENETUNREACH", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAETIMEDOUT : 
			strncpy( Error, "WSAETIMEDOUT", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK  : 
			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
		return false ;
	}

	return true ;
}

bool SocketAPI::listen_ex( SOCKET s )
{
	if ( listen( s , 128 ) == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{
		case EBADF : 
		case ENOTSOCK :
		case EOPNOTSUPP :
		default :
			{
				break;
			}
		}//end of switch
#elif _WIN32
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( Error, "WSAEADDRINUSE", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEISCONN : 
			strncpy( Error, "WSAEISCONN", _ESIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( Error, "WSAEMFILE", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif

		return false ;
	}

	return true ;
}

SOCKET SocketAPI::accept_ex( SOCKET s, struct sockaddr* addr, tuint32* addrlen )
{
#if __LINUX__
	SOCKET client = accept( s , addr , addrlen );
#elif _WIN32
	SOCKET client = accept( s , addr , (int*)addrlen );
#endif

	if ( client == INVALID_SOCKET ) 
	{
#if __LINUX__
		switch ( errno ) 
		{

		case EWOULDBLOCK : 
			strncpy( Error, "EWOULDBLOCK", _ESIZE ) ;
			break ;
		case ECONNRESET :
			strncpy( Error, "ECONNRESET", _ESIZE ) ;
			break ;
		case ECONNABORTED :
			strncpy( Error, "ECONNABORTED", _ESIZE ) ;
			break ;
		case EPROTO :
			strncpy( Error, "EPROTO", _ESIZE ) ;
			break ;
		case EINTR :
			// from UNIX Network Programming 2nd, 15.6
			// with nonblocking-socket, ignore above errors
			strncpy( Error, "EINTR", _ESIZE ) ;
			break ;
		case EBADF : 
			strncpy( Error, "EBADF", _ESIZE ) ;
			break ;
		case ENOTSOCK : 
			strncpy( Error, "ENOTSOCK", _ESIZE ) ;
			break ;
		case EOPNOTSUPP : 
			strncpy( Error, "EOPNOTSUPP", _ESIZE ) ;
			break ;
		case EFAULT : 
			strncpy( Error, "EFAULT", _ESIZE ) ;
			break ;
		default :
			{
				memset(Error,0,_ESIZE);
				sprintf(Error,"Error: %d",errno);
				break;
			}
		}//end of switch
#elif _WIN32
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( Error, "WSAEMFILE", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
	} else {
	}

	return client;
}

bool SocketAPI::getsockopt_ex( SOCKET s, tint32 level, tint32 optname, void* optval, tuint32* optlen )
{
#if __LINUX__
	if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		switch ( errno ) 
		{
		case EBADF : 
		case ENOTSOCK : 
		case ENOPROTOOPT : 
		case EFAULT : 
		default :
			{
				break;
			}
		}//end of switch

		return false ;
	}
#elif _WIN32
	if ( getsockopt( s , level , optname , (tchar*)optval , (int*)optlen ) == SOCKET_ERROR ) 
	{
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENOPROTOOPT : 
			strncpy( Error, "WSAENOPROTOOPT", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch

		return false ;
	}
#endif

	return true ;
}

tuint32 SocketAPI::getsockopt_ex2( SOCKET s, tint32 level, tint32 optname, void* optval, tuint32* optlen )
{
#if __LINUX__
	if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		switch ( errno ) 
		{
		case EBADF : 
			return 1;
		case ENOTSOCK : 
			return 2;
		case ENOPROTOOPT : 
			return 3;
		case EFAULT : 
			return 4;
		default :
			return 5;
		}//end of switch
	}
	return 0;

#elif _WIN32
	if ( getsockopt( s , level , optname , (tchar*)optval , (int*)optlen ) == SOCKET_ERROR ) 
	{
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED:
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN:
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT:
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS:
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL:
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENOPROTOOPT:
			strncpy( Error, "WSAENOPROTOOPT", _ESIZE ) ;
			break ;
		case WSAENOTSOCK:
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		}
	}
#endif

	return 0;
}

bool SocketAPI::setsockopt_ex( SOCKET s, tint32 level, tint32 optname, const void* optval, tuint32 optlen )
{
#if __LINUX__
	if ( setsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		switch ( errno ) 
		{
		case EBADF : 
		case ENOTSOCK : 
		case ENOPROTOOPT : 
		case EFAULT : 
		default :
			{
				break;
			}
		}//end of switch

		return false ;
	}
#elif _WIN32
	if ( setsockopt( s , level , optname , (tchar*)optval , optlen ) == SOCKET_ERROR ) 
	{
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( Error, "WSAENETRESET", _ESIZE ) ;
			break ;
		case WSAENOPROTOOPT : 
			strncpy( Error, "WSAENOPROTOOPT", _ESIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch

		return false ;
	}
#endif

	return true ;
}

tuint32 SocketAPI::send_ex( SOCKET s, const void* buf, tuint32 len, tuint32 flags )
{
	tint32 nSent;

	try
	{

#if __LINUX__
		nSent = send(s,buf,len,flags);
#elif _WIN32
		nSent = send(s,(const tchar *)buf,len,flags);
#endif

		if ( nSent == SOCKET_ERROR ) 
		{
#if __LINUX__
			switch ( errno ) 
			{

			case EWOULDBLOCK : 
				return SOCKET_ERROR_WOULDBLOCK;

			case ECONNRESET :
			case EPIPE :

			case EBADF : 
			case ENOTSOCK : 
			case EFAULT : 
			case EMSGSIZE : 
			case ENOBUFS : 

			default : 
				{
					break;
				}
			}//end of switch
#elif _WIN32
			tint32 iErr = WSAGetLastError() ;
			switch ( iErr ) 
			{
			case WSANOTINITIALISED : 
				strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
				break ;
			case WSAENETDOWN : 
				strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
				break ;
			case WSAEACCES : 
				strncpy( Error, "WSAEACCES", _ESIZE ) ;
				break ;
			case WSAEINTR : 
				strncpy( Error, "WSAEINTR", _ESIZE ) ;
				break ;
			case WSAEINPROGRESS : 
				strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
				break ;
			case WSAEFAULT : 
				strncpy( Error, "WSAEFAULT", _ESIZE ) ;
				break ;
			case WSAENETRESET : 
				strncpy( Error, "WSAENETRESET", _ESIZE ) ;
				break ;
			case WSAENOBUFS : 
				strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
				break ;
			case WSAENOTCONN : 
				strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
				break ;
			case WSAENOTSOCK : 
				strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
				break ;
			case WSAEOPNOTSUPP : 
				strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
				break ;
			case WSAESHUTDOWN : 
				strncpy( Error, "WSAESHUTDOWN", _ESIZE ) ;
				break ;
			case WSAEWOULDBLOCK : 
				//			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
				return SOCKET_ERROR_WOULDBLOCK ;
				break ;
			case WSAEMSGSIZE : 
				strncpy( Error, "WSAEMSGSIZE", _ESIZE ) ;
				break ;
			case WSAEHOSTUNREACH : 
				strncpy( Error, "WSAEHOSTUNREACH", _ESIZE ) ;
				break ;
			case WSAEINVAL : 
				strncpy( Error, "WSAEINVAL", _ESIZE ) ;
				break ;
			case WSAECONNABORTED : 
				strncpy( Error, "WSAECONNABORTED", _ESIZE ) ;
				break ;
			case WSAECONNRESET : 
				strncpy( Error, "WSAECONNRESET", _ESIZE ) ;
				break ;
			case WSAETIMEDOUT : 
				strncpy( Error, "WSAETIMEDOUT", _ESIZE ) ;
				break ;
			default :
				{
					strncpy( Error, "UNKNOWN", _ESIZE ) ;
					break ;
				};
			};//end of switch
#endif
		} 
		else if ( nSent == 0 )
		{
		}

	}
	catch(...)
	{
	}

	return nSent;
}

tuint32 SocketAPI::recv_ex( SOCKET s, void* buf, tuint32 len, tuint32 flags )
{
#if __LINUX__
	tint32 nrecv = recv(s,buf,len,flags);
#elif _WIN32
	tint32 nrecv = recv(s,(tchar*)buf,len,flags);
#endif

	if ( nrecv == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{

		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULDBLOCK;

		case ECONNRESET :
		case EPIPE :

		case EBADF : 
		case ENOTCONN : 
		case ENOTSOCK : 
		case EINTR : 
		case EFAULT : 

		default : 
			{
				break;
			}
		}//end of switch

#elif _WIN32
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( Error, "WSAENETRESET", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
			break ;
		case WSAESHUTDOWN : 
			strncpy( Error, "WSAESHUTDOWN", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			//			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			return SOCKET_ERROR_WOULDBLOCK ;
			break ;
		case WSAEMSGSIZE : 
			strncpy( Error, "WSAEMSGSIZE", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAECONNABORTED : 
			strncpy( Error, "WSAECONNABORTED", _ESIZE ) ;
			break ;
		case WSAETIMEDOUT : 
			strncpy( Error, "WSAETIMEDOUT", _ESIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( Error, "WSAECONNRESET", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
	} 
	else if ( nrecv == 0 )
	{
	}

	return nrecv;
}

bool SocketAPI::closesocket_ex( SOCKET s )
{
#if __LINUX__
	FileAPI::close_ex(s);
#elif _WIN32
	if ( closesocket(s) == SOCKET_ERROR ) 
	{
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch

		return false ;
	}
#endif

	return true ;
}

bool SocketAPI::ioctlsocket_ex( SOCKET s, long cmd, unsigned long* argp )
{
#if __LINUX__
#elif _WIN32
	if ( ioctlsocket(s,cmd,argp) == SOCKET_ERROR ) 
	{
		tint32 iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};

		return false ;
	}
#endif

	return true ;
}

bool SocketAPI::getsocketnonblocking_ex( SOCKET s )
{
#if __LINUX__
	return FileAPI::getfilenonblocking_ex(s);
#elif _WIN32
	return false ;
#endif
}

bool SocketAPI::setsocketnonblocking_ex( SOCKET s, bool on )
{
#if __LINUX__

	FileAPI::setfilenonblocking_ex(s,on);
	return true;
#elif _WIN32

	unsigned long argp = ( on == true ) ? 1 : 0;
	return ioctlsocket_ex( s,FIONBIO,&argp);

#endif
}

tuint32 SocketAPI::availablesocket_ex( SOCKET s )
{
#if __LINUX__
	return FileAPI::availablefile_ex(s);
#elif _WIN32
	unsigned long argp = 0;
	ioctlsocket_ex(s,FIONREAD,&argp);
	return argp;
#endif
}

Socket::Socket()
{
	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_Host, 0, IP_SIZE ) ;
	m_Port = 0 ;
}

Socket::~Socket()
{
	close() ;
}

bool Socket::create()
{
	m_SocketID = SocketAPI::socket_ex( AF_INET , SOCK_STREAM , 0 );

	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );

	m_SockAddr.sin_family = AF_INET;

	if( isValid() )
		return true ;
	else 
		return false ;
}

void Socket::close()
{
	if( isValid() && !isSockError() ) 
	{
		try 
		{
			SocketAPI::closesocket_ex( m_SocketID );
		} 
		catch(...)
		{
		}
	}

	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_Host, 0, IP_SIZE ) ;
	m_Port = 0 ;
}

bool Socket::connect()
{
	m_SockAddr.sin_addr.s_addr = inet_addr( m_Host );

	// set sockaddr's port
	m_SockAddr.sin_port = htons(m_Port);

	// try to connect to peer host
	bool result = SocketAPI::connect_ex( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );
	if( result)
		return true ;
	else
		return false ;
}

bool Socket::connect( const tchar* host, tuint32 port )
{
	strncpy( m_Host, host, IP_SIZE-1 ) ;
	m_Port = port ;

	return connect() ;
}

tuint32 Socket::send( const void* buf, tuint32 len, tuint32 flags /*= 0*/ )
{
	return SocketAPI::send_ex( m_SocketID , buf , len , flags );
}

tuint32 Socket::receive( void* buf, tuint32 len, tuint32 flags /*= 0*/ )
{
	return SocketAPI::recv_ex( m_SocketID , buf , len , flags );
}

tuint32 Socket::available() const
{
	return SocketAPI::availablesocket_ex( m_SocketID );
}

SOCKET Socket::accept( struct sockaddr* addr, tuint32* addrlen )
{
	return SocketAPI::accept_ex( m_SocketID, addr, addrlen ) ;
}

bool Socket::bind( tuint32 port )
{
	m_Port = port ;

	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_SockAddr.sin_port        = htons(m_Port);

	bool result = SocketAPI::bind_ex( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );
	if( result )
		return true ;
	else
		return false ;
}

bool Socket::listen()
{
	return SocketAPI::listen_ex( m_SocketID );
}

bool Socket::setLinger( tuint32 lingertime )
{
	struct linger ling;

	ling.l_onoff = lingertime > 0 ? 1 : 0;
	ling.l_linger = lingertime;

	return SocketAPI::setsockopt_ex( m_SocketID , SOL_SOCKET , SO_LINGER , &ling , sizeof(ling) );
}

bool Socket::setReuseAddr( bool on /*= true*/ )
{
	tint32 opt = on == true ? 1 : 0;

	return SocketAPI::setsockopt_ex( m_SocketID , SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt) );
}

bool Socket::getSockError() const
{
	return isSockError(); 
}

bool Socket::setNonBlocking( bool on /*= true*/ )
{
	return SocketAPI::setsocketnonblocking_ex( m_SocketID , on );
}

bool Socket::isValid() const
{
	return m_SocketID!=INVALID_SOCKET; 
}

SOCKET Socket::getSOCKET() const
{
	return m_SocketID; 
}

bool Socket::isSockError() const
{
	tint32 error;
	tuint32 len = sizeof(error);

	tint32 Result = SocketAPI::getsockopt_ex2( m_SocketID , SOL_SOCKET , SO_ERROR , &error, &len );

	if( Result == 0 ) 
		return false;
	else 			  
		return true;
}

ServerSocket::ServerSocket( tuint32 port )
{
	bool ret = false ;

	m_Socket = new Socket;
	if( m_Socket==null_ptr )
		throw 1 ;

	ret = m_Socket->create( ) ;
	if( ret==false )
		throw 1 ;

#if defined(__LINUX__)
	ret = m_Socket->setReuseAddr( ) ;
	if( ret==false )
		throw 1 ;
#endif

	ret = m_Socket->bind( port ) ;
	if( ret==false )
		throw 1 ;

	ret = m_Socket->listen( ) ;
	if( ret==false )
		throw 1 ;
}

ServerSocket::~ServerSocket()
{
	if ( m_Socket != null_ptr ) 
	{
		m_Socket->close();
		delete m_Socket;
		m_Socket = null_ptr;
	}
}

bool ServerSocket::accept( Socket* socket )
{
	tuint32 addrlen = sizeof(SOCKADDR_IN) ;
	socket->close( ) ;

	socket->m_SocketID = m_Socket->accept( (struct sockaddr *)(&(socket->m_SockAddr)), &addrlen ) ;
	if( socket->m_SocketID == INVALID_SOCKET )
		return false ;

	socket->m_Port = ntohs( socket->m_SockAddr.sin_port ) ;
	strncpy( socket->m_Host, inet_ntoa(socket->m_SockAddr.sin_addr), IP_SIZE-1 ) ;

	return true;
}

SocketInputStream::SocketInputStream( Socket* sock, tuint32 BufferLen, tuint32 MaxBufferLen )
{
	m_pSocket = sock ;
	m_BufferLen = BufferLen ;
	m_MaxBufferLen = MaxBufferLen ;

	m_Head = 0 ;
	m_Tail = 0 ;
	m_Buffer = new tchar[ m_BufferLen ];

	memset( m_Buffer, 0, m_BufferLen ) ;
}

SocketInputStream::~SocketInputStream()
{
	SAFE_DELETE_ARRAY(m_Buffer);
}

tuint32 SocketInputStream::Read( tchar* buf, tuint32 len )
{
	if ( len == 0 )
		return 0 ;

	if ( len > Length() )
		return 0 ;

	if ( m_Head < m_Tail ) 
	{
		memcpy( buf, &m_Buffer[m_Head], len ) ;
	} 
	else 
	{
		tuint32 rightLen = m_BufferLen-m_Head ;
		if( len<=rightLen ) 
		{
			memcpy( buf, &m_Buffer[m_Head], len ) ;
		} 
		else 
		{
			memcpy( buf, &m_Buffer[m_Head], rightLen ) ;
			memcpy( &buf[rightLen], m_Buffer, len-rightLen ) ;
		}
	}

	m_Head = (m_Head+len)%m_BufferLen ;

	return len ;
}

bool SocketInputStream::ReadPacket( Packet &rPacket, tuint32 nSize, bool bIsCryptoPacket )
{
	bool ret ;

	ret = Skip( PACKET_HEADER_SIZE ) ;
	if( !ret )
		return false ;

	if(nSize>2048)
	{
		tchar* buff = new tchar[nSize];
		if(buff == null_ptr) return false;
		memset(buff,0,sizeof(tchar)*nSize);
		Read(buff,sizeof(tchar)*nSize);
		if (bIsCryptoPacket)
		{
			XorDecrypt(buff, nSize);
		}
		if(!rPacket.m_rPacketData.ParseFromArray(buff,sizeof(tchar)*nSize))
		{
			SAFE_DELETE_ARRAY(buff);
			return false;
		}
		SAFE_DELETE_ARRAY(buff);
		return true;
	}
	else if(nSize>256)
	{
		tchar buff[2048]={0};
		Read(buff,sizeof(tchar)*nSize);
		if (bIsCryptoPacket)
		{
			XorDecrypt(buff, nSize);
		}
		if(!rPacket.m_rPacketData.ParseFromArray(buff,sizeof(tchar)*nSize))return false;
		return true;
	}
	else if(nSize>0)
	{
		tchar buff[256]={0};
		Read(buff,sizeof(tchar)*nSize);
		if (bIsCryptoPacket)
		{
			XorDecrypt(buff, nSize);
		}
		if(!rPacket.m_rPacketData.ParseFromArray(buff,sizeof(tchar)*nSize))return false;
		return true;
	}

	return false;
}

bool SocketInputStream::Peek( tchar* buf, tuint32 len )
{
	if( len==0 )
		return false ;

	if( len>Length() )
		return false ;

	if( m_Head<m_Tail ) 
	{
		memcpy( buf , &m_Buffer[m_Head] , len );

	} 
	else 
	{
		tuint32 rightLen = m_BufferLen-m_Head ;
		if( len<=rightLen ) 
		{
			memcpy( &buf[0], &m_Buffer[m_Head], len ) ;
		} 
		else 
		{
			memcpy( &buf[0], &m_Buffer[m_Head], rightLen ) ;
			memcpy( &buf[rightLen], &m_Buffer[0], len-rightLen ) ;
		}
	}

	return true ;
}

bool SocketInputStream::Skip( tuint32 len )
{
	if( len == 0 )
		return false ;

	if( len>Length( ) )
		return false ;

	m_Head = (m_Head+len)%m_BufferLen ;

	return true ;
}

tuint32 SocketInputStream::Fill()
{
	tuint32 nFilled = 0 ;
	tuint32 nReceived = 0 ;
	tuint32 nFree = 0 ;

	if ( m_Head <= m_Tail ) 
	{
		if ( m_Head == 0 ) 
		{
			//
			// H   T		LEN=10
			// 0123456789
			// abcd......
			//

			nReceived = 0 ;
			nFree = m_BufferLen-m_Tail-1 ;
			if( nFree != 0 )
			{
				nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , nFree );

				if (nReceived==SOCKET_ERROR_WOULDBLOCK) return 0 ; 
				if (nReceived==SOCKET_ERROR) return SOCKET_ERROR-1 ;
				if (nReceived==0) return SOCKET_ERROR-2 ;

				m_Tail += nReceived;
				nFilled += nReceived;
			}

			if( nReceived == nFree ) 
			{
				tuint32 available = m_pSocket->available();
				if ( available > 0 ) 
				{
					if( (m_BufferLen+available+1)>m_MaxBufferLen )
					{
						Initsize( ) ;
						return SOCKET_ERROR-3 ;
					}
					if( !Resize( available+1 ) )
						return 0 ;

					nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , available );
					if (nReceived==SOCKET_ERROR_WOULDBLOCK) return 0 ; 
					if (nReceived==SOCKET_ERROR) return SOCKET_ERROR-4 ;
					if (nReceived==0) return SOCKET_ERROR-5;

					m_Tail += nReceived;
					nFilled += nReceived;
				}
			}
		} 
		else 
		{
			//
			//    H   T		LEN=10
			// 0123456789
			// ...abcd...
			//

			nFree = m_BufferLen-m_Tail ;
			nReceived = m_pSocket->receive( &m_Buffer[m_Tail], nFree );
			if( nReceived==SOCKET_ERROR_WOULDBLOCK ) return 0 ; 
			if( nReceived==SOCKET_ERROR ) return SOCKET_ERROR-6 ;
			if( nReceived==0 ) return SOCKET_ERROR-7 ;

			m_Tail = (m_Tail+nReceived)%m_BufferLen ;
			nFilled += nReceived ;

			if( nReceived==nFree ) 
			{
				//				Assert( m_Tail == 0 );

				nReceived = 0 ;
				nFree = m_Head-1 ;
				if( nFree!=0 )
				{
					nReceived = m_pSocket->receive( &m_Buffer[0] , nFree );
					if( nReceived==SOCKET_ERROR_WOULDBLOCK ) return 0 ; 
					if( nReceived==SOCKET_ERROR ) return SOCKET_ERROR -8;
					if( nReceived==0 ) return SOCKET_ERROR-9 ;

					m_Tail += nReceived;
					nFilled += nReceived;
				}

				if( nReceived==nFree ) 
				{
					tuint32 available = m_pSocket->available();
					if ( available > 0 ) 
					{
						if( (m_BufferLen+available+1)>m_MaxBufferLen )
						{
							Initsize( ) ;
							return SOCKET_ERROR-10 ;
						}
						if( !Resize( available+1 ) )
							return 0 ;

						nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , available );
						if (nReceived==SOCKET_ERROR_WOULDBLOCK) return 0 ; 
						if (nReceived==SOCKET_ERROR) return SOCKET_ERROR-11 ;
						if (nReceived==0) return SOCKET_ERROR-12;

						m_Tail += nReceived;
						nFilled += nReceived;
					}
				}
			}
		}

	} 
	else 
	{	
		//
		//     T  H		LEN=10
		// 0123456789
		// abcd...efg
		//

		nReceived = 0 ;
		nFree = m_Head-m_Tail-1 ;
		if( nFree!=0 )
		{
			nReceived = m_pSocket->receive( &m_Buffer[m_Tail], nFree ) ;
			if( nReceived==SOCKET_ERROR_WOULDBLOCK ) return 0 ; 
			if( nReceived==SOCKET_ERROR ) return SOCKET_ERROR-13 ;
			if( nReceived==0 ) return SOCKET_ERROR-14 ;

			m_Tail += nReceived ;
			nFilled += nReceived ;
		}
		if( nReceived==nFree ) 
		{
			tuint32 available = m_pSocket->available( ) ;
			if ( available>0 ) 
			{
				if( (m_BufferLen+available+1)>m_MaxBufferLen )
				{
					Initsize( ) ;
					return SOCKET_ERROR-15 ;
				}
				if( !Resize( available+1 ) )
					return 0 ;

				nReceived = m_pSocket->receive( &m_Buffer[m_Tail], available ) ;
				if( nReceived==SOCKET_ERROR_WOULDBLOCK ) return 0 ; 
				if( nReceived==SOCKET_ERROR ) return SOCKET_ERROR-16 ;
				if( nReceived==0 ) return SOCKET_ERROR-17 ;

				m_Tail += nReceived ;
				nFilled += nReceived ;
			}
		}
	}

	return nFilled ;
}

void SocketInputStream::Initsize()
{
	m_Head = 0 ;
	m_Tail = 0 ;

	SAFE_DELETE_ARRAY( m_Buffer ) ;

	m_Buffer = new tchar[SOCKETINPUT_BUFSIZE] ;

	m_BufferLen = SOCKETINPUT_BUFSIZE ;

	memset( m_Buffer, 0, m_BufferLen ) ;
}

bool SocketInputStream::Resize( tint32 size )
{
	size = _MAX(size, (int)(m_BufferLen>>1));
	tuint32 newBufferLen = m_BufferLen + size;
	tuint32 len = Length();

	if ( size < 0 ) 
	{
		if ( newBufferLen < 0 || newBufferLen < len )
			return false ;		
	} 

	tchar * newBuffer = new tchar[ newBufferLen ];

	if ( m_Head < m_Tail ) 
	{
		memcpy( newBuffer , &m_Buffer[m_Head] , m_Tail - m_Head );
	} 
	else if ( m_Head > m_Tail ) 
	{
		memcpy( newBuffer , &m_Buffer[m_Head] , m_BufferLen - m_Head );
		memcpy( &newBuffer[ m_BufferLen - m_Head ] , m_Buffer , m_Tail );
	}

	delete [] m_Buffer ;

	m_Buffer = newBuffer ;
	m_BufferLen = newBufferLen ;
	m_Head = 0 ;
	m_Tail = len ;

	return true ;
}

tuint32 SocketInputStream::Length() const
{
	if( m_Head<m_Tail )
		return m_Tail-m_Head;

	else if( m_Head>m_Tail ) 
		return m_BufferLen-m_Head+m_Tail ;

	return 0 ;
}

SocketOutputStream::SocketOutputStream( Socket* sock, tuint32 BufferLen, tuint32 MaxBufferLen )
{
	m_pSocket = sock ;
	m_BufferLen = BufferLen ;
	m_MaxBufferLen = MaxBufferLen ;

	m_Head = 0 ;
	m_Tail = 0 ;

	m_Buffer = new tchar[ m_BufferLen ];

	memset( m_Buffer, 0, m_BufferLen ) ;
}

SocketOutputStream::~SocketOutputStream()
{
	SAFE_DELETE_ARRAY(m_Buffer);
}

tuint32 SocketOutputStream::Write( const tchar* buf, tuint32 len )
{
	tuint32 nFree = ( (m_Head<=m_Tail)?(m_BufferLen-m_Tail+m_Head-1):(m_Head-m_Tail-1) ) ;

	if( len>=nFree )
	{
		if( !Resize( len-nFree+1 ) )
			return 0 ;
	}

	if( m_Head<=m_Tail ) 
	{	
		if( m_Head==0 ) 
		{
			nFree = m_BufferLen - m_Tail - 1;
			memcpy( &m_Buffer[m_Tail], buf, len ) ;
		} 
		else 
		{
			nFree = m_BufferLen-m_Tail ;
			if( len<=nFree )
			{
				memcpy( &m_Buffer[m_Tail], buf, len ) ;
			}
			else 
			{
				memcpy( &m_Buffer[m_Tail], buf, nFree ) ;
				memcpy( m_Buffer, &buf[nFree], len-nFree ) ;
			}
		}
	} 
	else 
	{	
		memcpy( &m_Buffer[m_Tail], buf, len ) ;
	}

	m_Tail = (m_Tail+len)%m_BufferLen ;

	return len;
}

bool SocketOutputStream::WritePacket( const Packet &rPacket, bool bIsCryptoPacket )
{
	tuint32 uSizes = rPacket.GetPacketSize();
	if (!(uSizes > 0))
	{
		return false;
	}

	tuint32 packetSize = htonl(uSizes + PACKET_HEADER_SIZE);
	Write((tchar*)&packetSize, sizeof(tuint32));

	tuint16 packetID = htons(rPacket.GetPacketID());
	Write((tchar*)&packetID, sizeof(tuint16));

	if(uSizes>2048)
	{
		tchar* buff = new tchar[uSizes];
		if(buff == null_ptr) return false;
		memset(buff,0,sizeof(tchar)*uSizes);
		if(!rPacket.m_rPacketData.SerializePartialToArray(buff,sizeof(tchar)*uSizes))
		{
			SAFE_DELETE_ARRAY(buff);
			return false;
		}
		if (bIsCryptoPacket)
		{
			XorEncrypt(buff, uSizes);
		}
		Write(buff,sizeof(tchar)*uSizes);
		SAFE_DELETE_ARRAY(buff);
		return true;
	}
	else if(uSizes >256)
	{
		tchar buff[2048]={0};
		if(!rPacket.m_rPacketData.SerializePartialToArray(buff,sizeof(tchar)*uSizes))return false;
		if (bIsCryptoPacket)
		{
			XorEncrypt(buff, uSizes);
		}
		Write(buff,sizeof(tchar)*uSizes);
		return true;
	}
	else if(uSizes>0)
	{
		tchar buff[256]={0};
		if(!rPacket.m_rPacketData.SerializePartialToArray(buff,sizeof(tchar)*uSizes))return false;
		if (bIsCryptoPacket)
		{
			XorEncrypt(buff, uSizes);
		}
		Write(buff,sizeof(tchar)*uSizes);
		return true;
	}

	return false;
}

tuint32 SocketOutputStream::Flush()
{
	tuint32 nFlushed = 0;
	tuint32 nSent = 0;
	tuint32 nLeft;

	if( m_BufferLen>m_MaxBufferLen )
	{//如果单个客户端的缓存太大，则重新设置缓存，并将此客户端断开连接
		Initsize( ) ;

		return SOCKET_ERROR-1 ;
	}

#if defined(_WIN32)
	tuint32 flag = MSG_DONTROUTE ;
#elif defined(__LINUX__)
	tuint32 flag = MSG_NOSIGNAL ;
#endif

	try 
	{
		if ( m_Head < m_Tail ) 
		{
			nLeft = m_Tail - m_Head;

			while ( nLeft > 0 ) 
			{
				nSent = m_pSocket->send( &m_Buffer[m_Head] , nLeft , flag );
				if (nSent==SOCKET_ERROR_WOULDBLOCK) return 0 ; 
				if (nSent==SOCKET_ERROR) return SOCKET_ERROR-2 ;
				if (nSent==0) return 0;

				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}

			//			Assert( nLeft == 0 );

		} 
		else if( m_Head > m_Tail ) 
		{
			nLeft = m_BufferLen - m_Head;

			while ( nLeft > 0 ) 
			{
				nSent = m_pSocket->send( &m_Buffer[m_Head] , nLeft , flag );
				if (nSent==SOCKET_ERROR_WOULDBLOCK) return 0 ; 
				if (nSent==SOCKET_ERROR) return SOCKET_ERROR-3 ;
				if (nSent==0) return 0;

				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}

			//			Assert( m_Head == m_BufferLen );

			m_Head = 0;

			nLeft = m_Tail;

			while ( nLeft > 0 ) 
			{
				nSent = m_pSocket->send( &m_Buffer[m_Head] , nLeft , flag );
				if (nSent==SOCKET_ERROR_WOULDBLOCK) return 0 ; 
				if (nSent==SOCKET_ERROR) return SOCKET_ERROR-4 ;
				if (nSent==0) return 0;

				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}

			//			Assert( nLeft == 0 );
		}

		if ( m_Head != m_Tail ) 
		{
			//			Assert( m_Head == m_Tail );
		}

	}
	catch(...)
	{
		if( nSent>0 )
		{
			m_Head += nSent;
		}
	} 

	m_Head = m_Tail = 0 ;

	return nFlushed;
}

void SocketOutputStream::Initsize()
{
	m_Head = 0 ;
	m_Tail = 0 ;

	SAFE_DELETE_ARRAY( m_Buffer ) ;

	m_Buffer = new tchar[SOCKETOUTPUT_BUFSIZE] ;
	m_BufferLen = SOCKETOUTPUT_BUFSIZE ;

	memset( m_Buffer, 0, m_BufferLen ) ;
}

bool SocketOutputStream::Resize( tint32 size )
{
	tint32 orgSize = size;

	size = _MAX( size, (int)(m_BufferLen>>1) ) ;
	tuint32 newBufferLen = m_BufferLen+size ;
	tuint32 len = Length( ) ;

	if( size<0 ) 
	{
		if( newBufferLen<0 || newBufferLen<len )
			return false ;
	} 

	tchar * newBuffer = new tchar[ newBufferLen ] ;

	if( newBuffer==null_ptr )
		return false ;

	if( m_Head<m_Tail ) 
	{
		memcpy( newBuffer, &m_Buffer[m_Head], m_Tail-m_Head ) ;
	} 
	else if( m_Head>m_Tail ) 
	{
		memcpy( newBuffer, &m_Buffer[m_Head] , m_BufferLen-m_Head );
		memcpy( &newBuffer[m_BufferLen-m_Head], m_Buffer, m_Tail );
	}

	delete [] m_Buffer;

	m_Buffer = newBuffer;
	m_BufferLen = newBufferLen;
	m_Head = 0;
	m_Tail = len;	

	return true ;
}

tuint32 SocketOutputStream::Length() const
{
	if( m_Head<m_Tail )
		return m_Tail-m_Head;

	else if( m_Head>m_Tail ) 
		return m_BufferLen-m_Head+m_Tail ;

	return 0 ;
}
