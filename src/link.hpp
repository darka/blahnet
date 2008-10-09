#ifndef UUID_52DA523EF9CE4CF3A46629AAEC07E467
#define UUID_52DA523EF9CE4CF3A46629AAEC07E467

#include "bit_stream.hpp"
#include "udp_socket.hpp"
#include <boost/signal.hpp>

// TODO: rename to link_common
struct link
{
	enum disconnection_reason
	{
		timeout = 0,
		voluntary = 1
	};

	~link();
	
	//void host(unsigned short int port);
	//void connect(address const& addr);

	//void send(bit_stream const& data);
	
protected:
	link();
	//bool connected;
	//address addr;
	udp_socket sock;
	static uint8 const protocol_version = 0;
};
#endif // UUID_52DA523EF9CE4CF3A46629AAEC07E467

