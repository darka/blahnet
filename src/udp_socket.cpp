#include "socket_common_func.hpp" // includes winsock.h
#include "udp_socket.hpp"

#ifndef BLAHNET_WIN32

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#endif // BLAHNET_WIN32

udp_socket::udp_socket()
{
}

int udp_socket::create()
{
	int result;
#ifdef BLAHNET_WIN32
	result = data->wsock = ::socket(PF_INET, SOCK_DGRAM, 0);
#else
	result = data->psock = ::socket(PF_INET, SOCK_DGRAM, 0);
#endif // BLAHNET_WIN32
	if (result == -1)
		return -1;
	data->set_needs_closing();
	return 0;
}

void udp_socket::set_nonblocking()
{
#ifdef BLAHNET_WIN32
	u_long non_blocking = 1;
	ioctlsocket(get_descriptor(*this), FIONBIO, &non_blocking);
#else
	fcntl(get_descriptor(*this), F_SETFL, O_NONBLOCK);
#endif // BLAHNET_WIN32
}

/* TODO: real error handling */

int udp_socket::bind(unsigned short int port)
{
	address addr(port);
	return ::bind(get_descriptor(*this),
	              reinterpret_cast<sockaddr*>(addr.data()),
	              sizeof(sockaddr));
}

int udp_socket::sendto(char const* msg, std::size_t len, 
                       address const& addr)
{
	return ::sendto(get_descriptor(*this), msg, len, 0, 
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
	return ::recvfrom(get_descriptor(*this), msg, len, 0, 
	                  reinterpret_cast<sockaddr*>(addr.data()),
	                  &from_len);
}

void udp_socket::close()
{
	data->close();
}

