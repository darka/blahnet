#ifndef UUID_A3C8588901A048B6B6FB438C5F31BBCF
#define UUID_A3C8588901A048B6B6FB438C5F31BBCF

#include "link.hpp"

struct server : public link
{
	server();
	void host(unsigned short int port);
	void stop(); // does nothing if not hosting
//private:
	
};

#endif // UUID_A3C8588901A048B6B6FB438C5F31BBCF

