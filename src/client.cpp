#include "client.hpp"

client::client()
{
}

client::~client()
{
}

void client::connect(address const& addr)
{
	sock.create();
	// TODO: send a packet informing of connection
}
