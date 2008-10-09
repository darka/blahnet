#ifndef UUID_166D7E8EF9514324B94DBBCCCF7FEDA8
#define UUID_166D7E8EF9514324B94DBBCCCF7FEDA8

#include "address.hpp"
#include "types.hpp"

struct peer
{
	peer(address const& addr);

	address const& addr() { return addr_; }
	uint8 incoming_seq_number() { return incoming_seq_number_; }
	uint8 outgoing_seq_number() { return outgoing_seq_number_; }

private:
	address addr_;
	uint8 incoming_seq_number_;
	uint8 outgoing_seq_number_;
};

#endif // UUID_166D7E8EF9514324B94DBBCCCF7FEDA8

