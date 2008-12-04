#ifndef UUID_3A39D07169584AA1A5A6E890BF40AEC4
#define UUID_3A39D07169584AA1A5A6E890BF40AEC4

#include "types.hpp"
#include <cstddef>
#include <string>
#include <stdexcept>

// TODO: perhaps split class into read and write bit_streams

struct bit_stream
{
	typedef uint8 buffer_type;

	// TODO: TEST copy constructor and operator=, they're 
	//       completely untested
	bit_stream(std::size_t size=4);
	bit_stream(bit_stream const& other);
	bit_stream(buffer_type* data, std::size_t size);
	~bit_stream();

	bit_stream& operator=(bit_stream const& other);

	void write_bool(bool n);
	bool read_bool();

	void write_uint(uint32 n, unsigned int bits=32);
	uint32 read_uint(unsigned int bits);
    
	void write_sint(sint32 n, unsigned int bits=32);
	sint32 read_sint(unsigned int bits);
    
	void write_string(std::string const& str);
	std::string read_string();

	void append(bit_stream const& bs);

	buffer_type const* raw_data() const { return buffer; }
	buffer_type* raw_data() { return buffer; }
    std::size_t size() const { return size_; }

#if 0
	void printContents() const;
#endif

	void seek(unsigned int bit);

private:
	void write_bit(bool bit);
	bool read_bit();
	void inc_bit(); // increments cur_rel_bit and cur_byte if needed

	void affirm_size(std::size_t bits);
	void resize(std::size_t new_size);
	void clear();

	buffer_type* buffer;
	std::size_t size_;
	std::size_t cur_byte; // current byte
	unsigned int cur_rel_bit; // relative to current byte
	bool allocated_externally;
};

#endif // UUID_3A39D07169584AA1A5A6E890BF40AEC4

