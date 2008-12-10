#ifndef UUID_52DA523EF9CE4CF3A46629AAEC07E467
#define UUID_52DA523EF9CE4CF3A46629AAEC07E467

#include "bit_stream.hpp"
#include "udp_socket.hpp"
#include <boost/signal.hpp>
#include <queue>

struct link_common
{
	enum disconnection_reason
	{
		timeout = 0,
		voluntary = 1
	};
	enum message_type
	{
		reliable_ordered = 0
		/*
		unreliable_ordered = 1,
		reliable_unordered = 2,
		unreliable_unordered = 3,
		*/
	};

	~link_common();

	//void host(unsigned short int port);
	//void connect(address const& addr);

	//void send(bit_stream const& data);

	static uint8 const header_size = 1; // in bytes
	static uint8 const protocol_version = 0;
	// Header:
	// 4 bits: protocol id
	// 3 bits: message type
	// 1 bit : is an ack packet
protected:
	link_common();
	bit_stream add_header(bit_stream const& msg,
	                      message_type msg_type, bool is_ack);
	//bool connected;
	//address addr;
	udp_socket sock;
	//std::queue<packet*> packets;
};
#endif // UUID_52DA523EF9CE4CF3A46629AAEC07E467

