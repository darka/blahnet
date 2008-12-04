#include "link_common.hpp"

// TODO: error handling with exceptions

link_common::link_common()
{
}

link_common::~link_common()
{
	sock.close();
}

