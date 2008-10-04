#include "socket_common_func.hpp"
#include "socket_common.hpp"

#ifdef BLAHNET_WIN32

void init_wsock()
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);
}

void quit_wsock()
{
	WSACleanup();
}

SOCKET get_descriptor(socket_common const& socket)
{
	return (SOCKET)socket.data->wsock;
}

#else

int get_descriptor(socket_common const& socket)
{
	return socket.data->psock;
}

#endif // BLAHNET_WIN32
