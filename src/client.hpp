#ifndef UUID_D9717A39A7864EDC96BAA9C5A9A7E38C
#define UUID_D9717A39A7864EDC96BAA9C5A9A7E38C

#include "address.hpp"
#include "link_common.hpp"

struct client : public link_common
{
	client();
	void connect(address const& addr);
	~client();

private:

};

#endif // UUID_D9717A39A7864EDC96BAA9C5A9A7E38C

