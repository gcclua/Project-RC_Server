#ifndef _LIBNETWORK_H_
#define _LIBNETWORK_H_

#if defined(_WIN32)
#define __USE_SELECT__
#elif defined(__LINUX__)
#define __USE_POLL__
#else
#error windows or linux is required.
#endif

#include "BaseType.h"
#include "BaseLib.h"
#include "Exception.h"
#include "Misc.h"

//////////////////////////////////////////////////////////////////////////
namespace FileAPI 
{
	void close_ex (tint32 fd);
	tint32 fcntl_ex (tint32 fd, tint32 cmd, long arg);
	bool getfilenonblocking_ex (tint32 fd);
	void setfilenonblocking_ex (tint32 fd, bool on);
	void ioctl_ex (tint32 fd, tint32 request, void* argp);
	tuint32 availablefile_ex (tint32 fd);
};

//////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
#include <winsock2.h>
#elif defined(__LINUX__)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

typedef		tint32		SOCKET;
#define     INVALID_SOCKET   -1
#define		SOCKET_ERROR	 -1
#endif

extern const tint32 SOCKET_ERROR_WOULDBLOCK;

typedef struct sockaddr_in SOCKADDR_IN;

namespace SocketAPI 
{
	const tchar* getsocketerror_ex(void);
	SOCKET socket_ex (tint32 domain, tint32 type, tint32 protocol) ;
	bool bind_ex (SOCKET s , const struct sockaddr * addr , tuint32 addrlen) ;
	bool connect_ex (SOCKET s , const struct sockaddr * addr , tuint32 addrlen) ;
	bool listen_ex (SOCKET s) ;
	SOCKET accept_ex (SOCKET s, struct sockaddr* addr, tuint32* addrlen) ;
	bool getsockopt_ex (SOCKET s, tint32 level, tint32 optname, void* optval, tuint32* optlen) ;
	tuint32 getsockopt_ex2 (SOCKET s, tint32 level, tint32 optname, void* optval, tuint32* optlen) ;
	bool setsockopt_ex (SOCKET s, tint32 level, tint32 optname, const void* optval, tuint32 optlen) ;
	tuint32 send_ex (SOCKET s, const void* buf, tuint32 len, tuint32 flags) ;
	tuint32 recv_ex (SOCKET s, void* buf, tuint32 len, tuint32 flags) ;
	bool closesocket_ex (SOCKET s) ;
	bool ioctlsocket_ex (SOCKET s, long cmd, unsigned long* argp) ;
	bool getsocketnonblocking_ex (SOCKET s) ;
	bool setsocketnonblocking_ex (SOCKET s, bool on) ;
	tuint32 availablesocket_ex (SOCKET s) ;
};

//////////////////////////////////////////////////////////////////////////
//IP��ַ���ַ���󳤶�
#define IP_SIZE			24

class Socket 
{
public :
	// constructor
	Socket () ;
	// destructor
	virtual ~Socket () ;

public :
	bool create() ;
	// close connection
	void close () ;
	// try connect to remote host
	bool connect () ;
	bool connect (const tchar* host, tuint32 port) ;
	// send data to peer
	tuint32 send (const void* buf, tuint32 len, tuint32 flags = 0) ;
	// receive data from peer
	tuint32 receive (void* buf, tuint32 len, tuint32 flags = 0) ;
	tuint32 available ()const ;
	SOCKET accept( struct sockaddr* addr, tuint32* addrlen ) ;
	bool bind( tuint32 port ) ;
	bool listen() ;

public :
	bool setLinger (tuint32 lingertime) ;
	bool setReuseAddr (bool on = true) ;
	bool getSockError()const ;
	bool setNonBlocking (bool on = true) ;
	bool isValid ()const ;
	SOCKET getSOCKET ()const ;
	bool isSockError()const ;

public :
	SOCKET m_SocketID;
	SOCKADDR_IN m_SockAddr;
	tchar m_Host[IP_SIZE];
	tuint32 m_Port;
};

//////////////////////////////////////////////////////////////////////////
class ServerSocket 
{
public :
	explicit ServerSocket (tuint32 port) ;
	~ServerSocket () ;

public :
	bool accept ( Socket* socket ) ;
	void setNonBlocking (bool on = true) { m_Socket->setNonBlocking(on); }
	SOCKET getSOCKET () { return m_Socket->getSOCKET(); }

protected :
	Socket* m_Socket;
};

//////////////////////////////////////////////////////////////////////////
//��ʼ���Ľ��ջ��泤��
#define SOCKETINPUT_BUFSIZE 64*1024
//����������Ļ��泤�ȣ������������ֵ����Ͽ�����
#define SOCKETINPUT_MAXBUFSIZE 1024*1024

typedef tuint16	PacketID_t;

class Packet;
class SocketInputStream
{
public :
	SocketInputStream( Socket* sock, 
		tuint32 BufferLen = SOCKETINPUT_BUFSIZE,
		tuint32 MaxBufferLen = SOCKETINPUT_MAXBUFSIZE ) ;
	virtual ~SocketInputStream( ) ;

public :
	tuint32	Read( tchar* buf, tuint32 len ) ;
	bool	ReadPacket( Packet &rPacket, tuint32 nSize, bool bIsCryptoPacket ) ;

	bool	Peek( tchar* buf, tuint32 len ) ;

	bool	Skip( tuint32 len ) ;

	tuint32	Fill( ) ;

	void	Initsize( ) ;
	bool	Resize( tint32 size ) ;

	tuint32	Length( )const ;

private :
	Socket*	m_pSocket ;

	tchar*	m_Buffer ;

	tuint32	m_BufferLen ;
	tuint32	m_MaxBufferLen ;

	tuint32	m_Head ;
	tuint32	m_Tail ;
};

//////////////////////////////////////////////////////////////////////////
//��ʼ���ķ��ͻ��泤��
#define SOCKETOUTPUT_BUFSIZE 16*1024
//����������Ļ��泤�ȣ������������ֵ����Ͽ�����
#define SOCKETOUTPUT_MAXBUFSIZE 1024*1024

class Packet;
class SocketOutputStream 
{
public :
	SocketOutputStream( Socket* sock, 
		tuint32 BufferLen = SOCKETOUTPUT_BUFSIZE,
		tuint32 MaxBufferLen = SOCKETOUTPUT_MAXBUFSIZE ) ;
	virtual ~SocketOutputStream( ) ;

public :
	tuint32	Write( const tchar* buf, tuint32 len ) ;
	bool	WritePacket( const Packet &rPacket, bool bIsCryptoPacket ) ;

	tuint32	Flush( ) ;

	void	Initsize( ) ;
	bool	Resize( tint32 size ) ;

	tuint32	Length( )const ;

protected :
	Socket*	m_pSocket ;

	tchar*	m_Buffer ;

	tuint32	m_BufferLen ;
	tuint32	m_MaxBufferLen ;

	tuint32	m_Head ;
	tuint32	m_Tail ;
};

//////////////////////////////////////////////////////////////////////////
#include "google/protobuf/message.h"

//��Ϣͷ�а�����tuint16-2�ֽڣ�tuint32-4�ֽ�
#define PACKET_HEADER_SIZE (sizeof(tuint32)+sizeof(tuint16))  //32+16��ͷ

//Packet::Execute(...) �ķ���ֵ
enum PACKET_EXE
{
	PACKET_EXE_ERROR = 0 ,
	PACKET_EXE_CONTINUE ,
};

class Player;
class ServerPlayer;
class Packet
{
public :
	google::protobuf::Message &m_rPacketData;
public :
	explicit Packet(google::protobuf::Message &rPacketData)
		: m_rPacketData(rPacketData)
	{
	}
	virtual ~Packet( ) 
	{
	}

	virtual void	CleanUp( ){} ;


	//����ֵΪ��PACKET_EXE �е����ݣ�
	//PACKET_EXE_ERROR ��ʾ�������ش��󣬵�ǰ������Ҫ��ǿ�ƶϿ�
	//PACKET_EXE_CONTINUE ��ʾ�����ڵ�ǰѭ����ִ��ʣ�µ���Ϣ
	virtual tuint32		Execute( Player* pPlayer ) = 0 ;
	virtual tuint32		Execute( ServerPlayer* pServerPlayer ) = 0 ;

	virtual	tuint16		GetPacketID( ) const = 0 ;

	virtual	tuint32		GetPacketSize( ) const
	{
		return m_rPacketData.ByteSize();
	}
};

//////////////////////////////////////////////////////////////////////////
class PacketFactory 
{
public :	
	virtual ~PacketFactory ()  {};
	virtual Packet*		CreatePacket ()  = 0;

	virtual tuint16	GetPacketID ()const  = 0;
};

//////////////////////////////////////////////////////////////////////////
class PacketFactoryManager 
{
public :
	PacketFactoryManager( ) ;
	~PacketFactoryManager( ) ;

private :
	void				AddFactory( PacketFactory* pFactory ) ;

public :
	//�ⲿ����ͨ�ýӿ�

	//��ʼ���ӿ�
	bool				Init( ) ;
	//������Ϣ���ʹ��ڴ��������Ϣʵ�����ݣ�������߳�ͬʱ���ã�
	Packet*				CreatePacket( tuint16 packetID ) ;
	//������Ϣ����ȡ�ö�Ӧ��Ϣ�����ߴ磨������߳�ͬʱ���ã�
	//tuint32				GetPacketMaxSize( tuint16 packetID ) ;
	//ɾ����Ϣʵ�壨������߳�ͬʱ���ã�
	void				RemovePacket( Packet* pPacket ) ;

	void				Lock( ){ m_Lock.lock(); } ;
	void				Unlock( ){ m_Lock.unlock(); } ;

private :
	PacketFactory **	m_Factories ;
	tuint16				m_Size ;
	bstMutex			m_Lock ;

public :
	tuint32*				m_pPacketAllocCount ;

};

extern PacketFactoryManager gPacketFactoryManager ;

#endif
