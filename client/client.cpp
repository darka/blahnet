#include "udp_socket.hpp"
int main()
{
	udp_socket sock;
	sock.create();
	address addr(23232, "127.0.0.1");
	char msg[] = "lol wat";
	sock.sendto(msg, strlen(msg), addr);
}
