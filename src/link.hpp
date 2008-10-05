#ifndef UUID_52DA523EF9CE4CF3A46629AAEC07E467
#define UUID_52DA523EF9CE4CF3A46629AAEC07E467

#include "bit_stream.hpp"
#include "udp_socket.hpp"
#include <boost/signal.hpp>

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

	void send(bit_stream const& data);
	
	// TODO: how to cache the addresses?
	boost::signal<void (address const&)> on_connect;
	boost::signal<void (address const&, 
	                    disconnection_reason const&)> on_disconnect;
	
	boost::signal<void (address const&, bit_stream const&)> on_receive;
protected:
	link();
	//bool connected;
	//address addr;
	udp_socket sock;
};
#endif // UUID_52DA523EF9CE4CF3A46629AAEC07E467

