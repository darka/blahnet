#include "udp_socket.hpp"

#ifdef BLAHNET_WIN32

#include <winsock.h>

#define SOCKET_DESCRIPTOR() (SOCKET)data->wsock

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET_DESCRIPTOR() data->psock

#endif // BLAHNET_WIN32

udp_socket::udp_socket()
{
}

int udp_socket::create()
{
	// TODO: fix this
	data->psock = ::socket(PF_INET, SOCK_DGRAM, 0);
	if (data->psock == -1)
		return -1;
	data->set_needs_closing();
	return 0;
}

void udp_socket::set_nonblocking()
{
#ifdef BLAHNET_WIN32
	u_long non_blocking = 1;
	ioctlsocket(SOCKET_DESCRIPTOR(), FIONBIO, &non_blocking);
#else
	fcntl(SOCKET_DESCRIPTOR(), F_SETFL, O_NONBLOCK);
#endif // BLAHNET_WIN32
}

/* TODO: real error handling */

int udp_socket::bind(unsigned short int port)
{
	address addr(port);
	return ::bind(SOCKET_DESCRIPTOR(),
	              reinterpret_cast<sockaddr*>(addr.data()),
	              sizeof(sockaddr));
}

int udp_socket::sendto(char const* msg, std::size_t len, 
                       address const& addr)
{
	return ::sendto(SOCKET_DESCRIPTOR(), msg, len, 0, 
	                reinterpret_cast<sockaddr const*>(addr.data()),
	                sizeof(sockaddr));
}

int udp_socket::recvfrom(char* msg, std::size_t len, address& addr)
{
#ifdef BLAHNET_WIN32
	int from_len = sizeof(sockaddr);
#else
	socklen_t from_len = sizeof(sockaddr);
#endif // BLAHNET_WIN32
	return ::recvfrom(SOCKET_DESCRIPTOR(), msg, len, 0, 
	                  reinterpret_cast<sockaddr*>(addr.data()),
	                  &from_len);
}

void udp_socket::close()
{
	data->close();
}

