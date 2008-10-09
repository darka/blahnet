#ifndef UUID_75A46991F81648ED83D9A7E8D598BE9D
#define UUID_75A46991F81648ED83D9A7E8D598BE9D

#include "types.hpp"

struct packet
{
	packet(char const* msg, std::size_t msg_len, 
	       uint8 peer_id, uint8 seq_num,
		   address const& addr); // message with a header
	// TODO: ack packets should contain multiple acks
	packet(uint8 peer_id, uint8 seq_num, 
	       address const& addr); // ack packet
	~packet();

	char* msg() { return msg; }
	std::size_t msg_len() { msg_len_; }
	address const& addr() { return addr_; }

private:
	char* msg_;
	std::size_t msg_len_;
	address const& addr_;
};

#endif // UUID_75A46991F81648ED83D9A7E8D598BE9D
