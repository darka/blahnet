#include "address.hpp"

address::address()
: ip_(0)
, port_(0)
{
}

address::address(unsigned short int port)
: ip_(0)
, port_(port)
{
}

address::address(unsigned short int port, const char* ip)
: ip_(ip)
, port_(port)
{
}
#if 0
void address::zeroPad()
{
    std::memset(data.sin_zero, '\0', sizeof(data.sin_zero));
}
#endif
