#ifndef UUID_073328F7899A4DD0B86369768768AFE7
#define UUID_073328F7899A4DD0B86369768768AFE7

#include "udp_socket.hpp"
#include "bit_stream.hpp"
#include "types.hpp"
#include <queue>
#include <utility>

struct reliable_layer
{
	reliable_layer();
	~reliable_layer();
	void sendto(char const* msg, std::size_t msg_len,
	            address const& addr);
	void work();

private:
	
	void pop_top_packet(); // handles memory

	udp_socket sock;
	uint8 seq_num; // sequence number used in sent message header
	bool expecting; // if expecting ack packets
	uint8 expected_num; // sequence number we're waiting for
	std::queue<packet*> packets;
	static uint8 const protocol_version = 0;
};

#endif // UUID_073328F7899A4DD0B86369768768AFE7

