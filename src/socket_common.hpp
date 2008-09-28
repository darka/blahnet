#ifndef UUID_6091A81C00E14F7F855C382F4C918DA5
#define UUID_6091A81C00E14F7F855C382F4C918DA5

struct socket_common
{
	socket_common();
	socket_common(socket_common const& other);
	~socket_common();
	socket_common& operator=(socket_common const& other);

protected:
	struct socket_data
	{
		socket_data();
		~socket_data();
		socket_data(socket_data const& other);
		socket_data& operator=(socket_data const& other);
		void set_needs_closing();
		void close();
		union
		{
			void* wsock; // winsock socket
			int psock; // BSD POSIX socket
		};
		int count;
	private:
		bool needs_closing;
#ifdef BLAHNET_WIN32
		static int wsock_total_count;
#endif // BLAHNET_WIN32
	};
	socket_data* data;
};

#endif // UUID_6091A81C00E14F7F855C382F4C918DA5

