#ifndef UUID_A3C8588901A048B6B6FB438C5F31BBCF
#define UUID_A3C8588901A048B6B6FB438C5F31BBCF

#include "link_common.hpp"
#include "peer.hpp"
#include <map>

struct server : public link_common
{
	server();
	void host(unsigned short int port);
	void work();
	void stop(); // does nothing if not hosting

	void sendto(char* msg, std::size_t msg_len,
	            uint8 peer_id);

	// TODO: how to cache the addresses? ???
	boost::signal<void (address const&)> on_connect;
	boost::signal<void (address const&,
	                    disconnection_reason const&)> on_disconnect;

	boost::signal<void (address const&, bit_stream const&)> on_receive;
private:
	void generateId();

	std::map<uint8, peer*> peers; // unique peer id => peer
	bool expecting;
	uint8 id;
	std::map<message_type, uint8> counters;
};

#endif // UUID_A3C8588901A048B6B6FB438C5F31BBCF

