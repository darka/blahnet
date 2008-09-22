#ifndef UUID_8B00007D6BED43B1AF63C689D9D35D78
#define UUID_8B00007D6BED43B1AF63C689D9D35D78

struct address
{
    address(); /* uses host's ip address and picks a port automatically */
    address(unsigned short int port); /* uses host's ip address and uses given port */
    address(unsigned short int port, const char* ip); /* uses given ip and port */
    
    unsigned short int port() const { return port_; }
    const char* ip() const { return ip_; }
    
private:
	const char* ip_;
	unsigned short int port_;
};

#endif // UUID_8B00007D6BED43B1AF63C689D9D35D78
