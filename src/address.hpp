#ifndef UUID_8B00007D6BED43B1AF63C689D9D35D78
#define UUID_8B00007D6BED43B1AF63C689D9D35D78

struct sockaddr_in;

struct address
{
	address(); /* uses host's ip address and picks a port automatically */
	address(unsigned short int port); /* uses host's ip address and
	                                     uses given port */
	address(unsigned short int port, char const* ip); /* uses given ip
	                                                     and port */
	address(address const& other);
	~address();

	address& operator=(address const& other);

	/*unsigned short int port() const;
	const char* ip() const;*/
	sockaddr_in const* data() const { return data_; }
	sockaddr_in* data() { return data_; }

private:
	void clear();
	sockaddr_in* data_;
};

#endif // UUID_8B00007D6BED43B1AF63C689D9D35D78
