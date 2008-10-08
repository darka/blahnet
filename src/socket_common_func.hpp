#ifndef UUID_9324CDC8D22248E98D42A8CC941A5635
#define UUID_9324CDC8D22248E98D42A8CC941A5635

struct socket_common;

#ifdef BLAHNET_WIN32

#include <winsock.h>

SOCKET get_descriptor(socket_common const& socket);

#else

int get_descriptor(socket_common const& socket);

#endif // BLAHNET_WIN32

#endif // UUID_9324CDC8D22248E98D42A8CC941A5635


