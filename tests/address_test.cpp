#include "address.hpp"
#include <netinet/in.h>
#include <tut.h>

namespace tut
{
	struct address_data
	{

	};

	typedef test_group<address_data> tg;
	tg address_tg("address test");

	template<> template<>
	void tg::object::test<1>()
	{
		set_test_name("copy constructor and operator= test");
		address a(6666, "127.0.0.1");
		address b(a);
		address c(7777, "0.0.0.0");
		c = a;
		sockaddr_in* a_sock = a.data();
		sockaddr_in* b_sock = b.data();
		sockaddr_in* c_sock = c.data();
		ensure_equals("a and b sin_family", a_sock->sin_family, b_sock->sin_family);
		ensure_equals("a and c sin_family", a_sock->sin_family, c_sock->sin_family);
		ensure_equals("a and b sin_addr", a_sock->sin_addr.s_addr, b_sock->sin_addr.s_addr);
		ensure_equals("a and c sin_addr", a_sock->sin_addr.s_addr, c_sock->sin_addr.s_addr);
		ensure_equals("a and b sin_port", a_sock->sin_port, b_sock->sin_port);
		ensure_equals("a and c sin_port", a_sock->sin_port, c_sock->sin_port);
		b_sock->sin_port = htons(5555);
		c_sock->sin_port = htons(4444);
		ensure_equals("a sin_port after changes", a_sock->sin_port, htons(6666));
	}
}
