#include "socket_common_func.hpp"
#include "socket_common.hpp"

#ifdef BLAHNET_WIN32

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
