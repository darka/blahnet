#include "socket_handle.hpp"

socket_handle::socket_handle()
: data(new socket_handle_data())
{
}

socket_handle::socket_handle(const socket_handle& other)
: data(other.data)
{
	++data->count;
}

socket_handle::~socket_handle()
{
	--data->count;
	if (data->count == 0)
	{
		delete data;
	}
}

socket_handle& socket_handle::operator=(const socket_handle& other)
{
	socket_handle_data* const old = data;
	data = other.data;
	++data->count;
	if (--old->count == 0) 
		delete old;
	return *this;

}

socket_handle::socket_handle_data::socket_handle_data()
: count(1)
{

}


