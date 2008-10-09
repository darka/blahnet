#ifndef UUID_A3C8588901A048B6B6FB438C5F31BBCF
#define UUID_A3C8588901A048B6B6FB438C5F31BBCF

#include "link.hpp"
#include "peer.hpp"
#include <map>

struct server : public link
{
	server();
	void host(unsigned short int port);
	void work();
	void stop(); // does nothing if not hosting

	void sendto(char const* msg, std::size_t msg_len,
	            uint8 peer_id);

	// TODO: how to cache the addresses? ???
	boost::signal<void (address const&)> on_connect;
	boost::signal<void (address const&, 
	                    disconnection_reason const&)> on_disconnect;
	
	boost::signal<void (address const&, bit_stream const&)> on_receive;
private:
	std::map<uint8, peer> peers; // unique peer id => peer
	bool expecting;
	
};

#endif // UUID_A3C8588901A048B6B6FB438C5F31BBCF

