#include "link_common.hpp"

// TODO: error handling with exceptions

link_common::link_common()
{
}

bit_stream link_common::add_header(bit_stream const& msg,
                                   message_type msg_type, bool is_ack)
{
	bit_stream packet(header_size);
	packet.write_uint(protocol_version, 4);
	packet.write_uint(msg_type, 3);
	packet.write_bool(is_ack);
	packet.append(msg);
	return packet;
}

link_common::~link_common()
{
	sock.close();
}

