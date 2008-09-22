#ifndef UUID_6091A81C00E14F7F855C382F4C918DA5
#define UUID_6091A81C00E14F7F855C382F4C918DA5

#include "address.hpp"

struct socket_handle
{
	socket_handle();
	socket_handle(const socket_handle& other);
	~socket_handle();
	socket_handle& operator=(const socket_handle& other);

private:
	struct socket_handle_data
	{
		socket_handle_data();
		socket_handle_data(const socket_handle_data& other);
		socket_handle_data& operator=(const socket_handle_data& other);
		union
		{
			void* wsock; // winsock socket
			int psock; // BSD POSIX socket
		};
		int count;
	};
	socket_handle_data* data;
};

void udp_socket(const socket_handle& handle);
void bind_socket(const socket_handle& handle, const address& address); 

#endif // UUID_6091A81C00E14F7F855C382F4C918DA5

