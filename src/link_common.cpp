#include "link_common.hpp"

// TODO: error handling with exceptions

link_common::link_common()
{
}

bit_stream link_common::add_header(bit_stream const& msg, uint8 peer_id,
                                   message_type msg_type, bool is_ack)
{
	bit_stream packet(header_size);
	packet.write_uint(protocol_version);
	packet.write_uint(peer_id);
	packet.write_uint(msg_type);
	packet.write_uint(is_ack); // not an ack packet
	packet.append(msg);
	return packet;
}

link_common::~link_common()
{
	sock.close();
}

