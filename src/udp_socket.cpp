#include "udp_socket.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

udp_socket::udp_socket()
{
}

int udp_socket::create()
{
	data->psock = ::socket(PF_INET, SOCK_DGRAM, 0);
	if (data->psock == -1)
		return -1;
	data->set_needs_closing();
	return 0;
}

/* TODO: real error handling */

int udp_socket::bind(unsigned short int port)
{
	address addr(port);
	return ::bind(data->psock, 
	              reinterpret_cast<sockaddr*>(addr.data()),
	              sizeof(sockaddr));
}

int udp_socket::sendto(void const* msg, std::size_t len, 
                       address const& addr)
{
	return ::sendto(data->psock, msg, len, 0, 
	                reinterpret_cast<sockaddr const*>(addr.data()),
	                sizeof(sockaddr));
}

int udp_socket::recvfrom(void* msg, std::size_t len, address& addr)
{
	socklen_t from_len = sizeof(sockaddr);
	return ::recvfrom(data->psock, msg, len, 0, 
	                  reinterpret_cast<sockaddr*>(addr.data()),
	                  &from_len);
}

void udp_socket::close()
{
	data->close();
}

