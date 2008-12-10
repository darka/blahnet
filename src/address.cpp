#include "address.hpp"

#ifdef BLAHNET_WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#endif // BLAHNET_WIN32

#include <cstring>

void zero_pad_data(sockaddr_in& data)
{
	std::memset(data.sin_zero, '\0', sizeof(data.sin_zero));
}

void copy_data(sockaddr_in const& from, sockaddr_in& to)
{
	to.sin_family = from.sin_family;
	to.sin_port = from.sin_port;
	to.sin_addr.s_addr = from.sin_addr.s_addr;
	zero_pad_data(to);
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
	zero_pad_data(*data_);
}

address::address(unsigned short int port, char const* ip)
: data_(new sockaddr_in)
{
	data_->sin_family = AF_INET;
	data_->sin_port = htons(port);
	data_->sin_addr.s_addr = inet_addr(ip);
	zero_pad_data(*data_);
}

address::address(address const& other)
: data_(new sockaddr_in)
{
	copy_data(*other.data_, *this->data_);
}

address::~address()
{
	clear();
}

address& address::operator=(address const& other)
{
	if (this == &other) return *this;
	clear();
	data_ = new sockaddr_in();
	copy_data(*other.data_, *this->data_);
	return *this;
}

void address::clear()
{
	delete data_;
}
