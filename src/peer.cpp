#include "peer.hpp"

peer::peer(address const& addr)
: addr_(addr)
, incoming_seq_number_(0)
, outgoing_seq_number_(0)
{
}

