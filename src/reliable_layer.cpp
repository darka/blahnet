#include "reliable_layer.hpp"
#include <cassert>
#include <cstring>

reliable_layer::reliable_layer()
: seq_num(0)
, expecting(false)
, expected_num(0)
{
	sock.create();
	sock.set_nonblocking();
}

reliable_layer::~reliable_layer()
{
	while (!packets.empty())
	{
		pop_top_packet();
	}
}

void reliable_layer::work()
{
	// receive packets
	// TODO: enforce default max packet size everywhere?
	unsigned int const packet_size = 20;
	char msg[packet_size];
	address addr;
	int result = sock.recvfrom(msg, packet_size - 1, addr);
	if (result != -1)
	{
		// TODO: should disconnect the client instead
		assert((msg[0] >> 1) == protocol_version);
		// is packet an ack?
		if ((msg[0] & 0x1) == 0)
		{
			if (expecting && msg[1] == expected_num)
				pop_top_packet();
		}
		else
		{
			// send an ack
			// TODO: pack many acks in one packet
		}

	}
	
	if (packets.empty())
	{
		expecting = false;
	}
	else
	{
		// send top packet
		packet* current_packet = packets.front();
		// TODO: error checking
		sock.sendto(current_packet->msg, current_packet->msg_len,
		            current_packet->addr);
		expecting = true;
		expected_num = current_packet->msg[1];
		pop_top_packet();
	}
	
}

void reliable_layer::pop_top_packet()
{
		packet* current_packet = packets.front();
		delete[] current_packet->msg;
		delete current_packet;
		packets.pop();
}
