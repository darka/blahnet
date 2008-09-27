#include "address.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

void zero_pad(sockaddr_in& data)
{
	std::memset(data.sin_zero, '\0', sizeof(data.sin_zero));
}

address::address()
: data_(new sockaddr_in)
{
}

address::address(unsigned short int port)
: data_(new sockaddr_in)
{
	data_->sin_family = AF_INET;
	data_->sin_port = htons(port);
	data_->sin_addr.s_addr = INADDR_ANY;
	zero_pad(*data_);
}

address::address(unsigned short int port, char const* ip)
: data_(new sockaddr_in)
{
	data_->sin_family = AF_INET;
	data_->sin_port = htons(port);
	inet_aton(ip, &(data_->sin_addr));
	zero_pad(*data_);
}

address::~address()
{
	delete data_;
}

