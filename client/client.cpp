#include "reliable_layer.hpp"
int main()
{
	reliable_layer rel_link;
	address addr(23232, "127.0.0.1");
	char msg[] = "lol wat";
	rel_link.sendto(msg, strlen(msg), addr);
	rel_link.work();
}
