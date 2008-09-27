#include "udp_socket.hpp"
#include <iostream>

int main()
{
	udp_socket sock;
	sock.create();
	sock.bind(23232);
	address receiver_addr;
	char buf[100];
	int bytes = sock.recvfrom(buf, 99, receiver_addr);
	std::cout << bytes << "\n";
}
