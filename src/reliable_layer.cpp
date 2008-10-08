#include "reliable_layer.hpp"
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
		packet* current_packet = packets.front();
		delete[] current_packet->msg;
		delete current_packet;
		packets.pop();
	}
}

void reliable_layer::sendto(char const* msg, std::size_t msg_len,
                            address const& addr)
{
	// TODO: split the packet here? need to guard against overflow anyway
	std::size_t prepared_msg_len = msg_len + 2;
	char* prepared_msg = new char[prepared_msg_len];
	std::memcpy(prepared_msg + 2, msg, msg_len);
	std::memset(prepared_msg, 0, 2);

	// attach header
	// first 7 bits = protocol version 
	// TODO: (how else do we do this? on connection? look at q3
	prepared_msg[0] |= (protocol_version << 1);
	// we're not sending an ack packet, so the 8th bit is 1
	prepared_msg[0] |= 1;
	// attach sequence number	
	prepared_msg[1] |= seq_num;
	// store in a queue?
	packets.push(new packet(prepared_msg, prepared_msg_len, addr));
	seq_num += 1;
}

void reliable_layer::work()
{
	if (!packets.empty())
	{
		// send top packet
		packet* current_packet = packets.front();
		sock.sendto(current_packet->msg, current_packet->msg_len,
		            current_packet->addr);
		delete[] current_packet->msg;
		delete current_packet;
		packets.pop();
	}
}

