#include "peer.hpp"

peer::peer(address const& addr)
: addr(addr)
, incoming_seq_number(0)
, outgoing_seq_number(0)
{
}

