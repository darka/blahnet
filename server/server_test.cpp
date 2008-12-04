#include "server.hpp"
#include <iostream>

int main()
{
	/*udp_socket sock;
	sock.create();
	sock.bind(23232);
	address receiver_addr;
	char buf[100];
	int bytes = sock.recvfrom(buf, 99, receiver_addr);*/
	server serv;
	serv.host(23232);


	//std::cout << bytes << "\n";
}
