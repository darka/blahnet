#include "link.hpp"

// TODO: error handling with exceptions

link::link()
{
}

link::~link()
{
	sock.close();
}

