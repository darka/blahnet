#ifndef UUID_96F8FCADA2CD4A1EAC27C1575447E3A7
#define UUID_96F8FCADA2CD4A1EAC27C1575447E3A7

#include "socket_common.hpp"
#include "address.hpp"
#include <cstring>

struct udp_socket : public socket_common
{
	udp_socket();
	int create();
	int bind(unsigned short int port);
	int sendto(char const* msg, std::size_t len, address const& addr);
	int recvfrom(char* msg, std::size_t len, address& addr);
	void close();
};

#endif // UUID_96F8FCADA2CD4A1EAC27C1575447E3A7

