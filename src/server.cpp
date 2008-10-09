#include "server.hpp"

server::server()
: expecting(false)
{
}

void server::host(unsigned short int port)
{
	sock.create();
	sock.bind(port);
}

void server::work()
{
	// receive packets
	// TODO: enforce default max packet size everywhere? 
	//       should go into link.hpp if so
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

void server::stop()
{
	sock.close();
}

void server::sendto(char const* msg, std::size_t msg_len,
                    uint8 peer_id)
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


