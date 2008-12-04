#include "server.hpp"
#include "bit_stream.hpp" 

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
	//       should go into link_common if so
	//       If anything we need to check the size isn't too small
	unsigned int const packet_size = 20;
	char raw_msg[packet_size];
	address addr;
	int result = sock.recvfrom(raw_msg, packet_size - 1, addr);
	bit_stream msg(reinterpret_cast<uint8*>(raw_msg), packet_size);
	if (result != -1)
	{
		// TODO: should disconnect the client instead
		assert((msg.read_uint(4)) == protocol_version);
		// TODO: check if such peer exists at all
		peer* sender = peers[msg.read_uint(8)];
		uint8 msg_type = msg.read_uint(3);

		// is packet an ack?
		if (msg.read_uint(1))
		{
			uint8 seq_number = msg.read_uint(8);
			//if (expecting && seq_number == sender->outgoing_seq_number())
			//	pop_top_packet();
		}
		else
		{
			// send an ack
			// TODO: pack many acks in one packet
		}

	}
	
	/*if (packets.empty())
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
	}*/

}

void server::stop()
{
	sock.close();
}

void server::sendto(char* msg, std::size_t msg_len,
                    uint8 peer_id)
{
	// TODO: split the packet here? need to guard against overflow anyway
	/*std::size_t prepared_msg_len = msg_len + 2;
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
	prepared_msg[1] |= seq_num;*/
	bit_stream bs(reinterpret_cast<bit_stream::buffer_type*>(msg), msg_len);
	bit_stream packet(header_size);
	packet.write_uint(protocol_version);
	packet.write_uint(peer_id);
	packet.write_uint(reliable_ordered);
	packet.write_uint(false); // not an ack packet
	packet.append(bs);
	// store in a queue?
	//packets.push(packet);
	counters[reliable_ordered] += 1;
}


