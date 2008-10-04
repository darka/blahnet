#ifndef UUID_6091A81C00E14F7F855C382F4C918DA5
#define UUID_6091A81C00E14F7F855C382F4C918DA5

struct udp_socket;
struct tcp_socket;

struct socket_common
{
	struct socket_data
	{
		friend struct socket_common;
		friend struct udp_socket;
		friend struct tcp_socket;

		socket_data();
		~socket_data();
		socket_data(socket_data const& other);
		socket_data& operator=(socket_data const& other);

		union
		{
			void* wsock; // winsock socket
			int psock; // BSD POSIX socket
		};

	private:
		void set_needs_closing();
		void close();

		int count;
		bool needs_closing;
#ifdef BLAHNET_WIN32
		static int wsock_total_count;
#endif // BLAHNET_WIN32
	};

	socket_common();
	socket_common(socket_common const& other);
	~socket_common();
	socket_common& operator=(socket_common const& other);

	socket_data* data;
};

#endif // UUID_6091A81C00E14F7F855C382F4C918DA5

