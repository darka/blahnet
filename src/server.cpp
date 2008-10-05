#include "server.hpp"

server::server()
{
}

void server::host(unsigned short int port)
{
	sock.create();
	sock.bind(port);
}

void server::stop()
{
	sock.close();
}

