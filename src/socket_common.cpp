#include "socket_common.hpp"
#include <unistd.h>

socket_common::socket_common()
: data(new socket_data())
{
}

socket_common::socket_common(socket_common const& other)
: data(other.data)
{
	++data->count;
}

socket_common::~socket_common()
{
	--data->count;
	if (data->count == 0)
	{
		delete data;
	}
}

socket_common& socket_common::operator=(socket_common const& other)
{
	socket_data* const old = data;
	data = other.data;
	++data->count;
	if (--old->count == 0) 
		delete old;
	return *this;

}

#if BLAHNET_WIN32==1

int socket_common::socket_data::wsock_total_count = 0;

void init_wsock()
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);
}

void quit_wsock()
{
	WSACleanup();
}
#endif

socket_common::socket_data::socket_data()
: count(1)
, needs_closing(false)
{
#if BLAHNET_WIN32==1
	if (wsock_total_count == 0)
	{
		init_wsock();
	}
	wsock_total_count += 1;
#endif
}

socket_common::socket_data::~socket_data()
{
	close();
#if BLAHNET_WIN32==1
	wsock_total_count -= 1;
	if (wsock_total_count == 0)
	{
		quit_wsock();
	}
#endif
}

void socket_common::socket_data::set_needs_closing()
{
	needs_closing = true;
}

void socket_common::socket_data::close()
{
	if (needs_closing)
	{
#if BLAHNET_WIN32==1
		closesocket((SOCKET)wsock);
#else
		::close(psock);
#endif
		needs_closing = false;
	}
}


