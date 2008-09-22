#include "bit_stream.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

bit_stream::bit_stream(std::size_t size_)
: size_(size_)
, cur_byte(0)
, cur_rel_bit(0)
{
    buffer = new buffer_type[size_];
	memset(buffer, 0, size_);
}

bit_stream::bit_stream(const bit_stream& other)
: size_(other.size_)
, cur_byte(other.cur_byte)
, cur_rel_bit(other.cur_rel_bit)
{
	buffer = new buffer_type[size_];
	memcpy(buffer, other.buffer, size_);
}

bit_stream::bit_stream(buffer_type* data, std::size_t size_)
: buffer(data)
, size_(size_)
, cur_byte(0)
, cur_rel_bit(0)
{
}

bit_stream::~bit_stream()
{
	clear();
}

bit_stream& bit_stream::operator=(const bit_stream& other)
{
	clear();
	size_ = other.size_;
	cur_byte = other.cur_byte;
	cur_rel_bit = other.cur_rel_bit;
	buffer = new buffer_type[size_];
	memcpy(buffer, other.buffer, size_);
	return *this;
}

void bit_stream::seek(unsigned int bit)
{
	cur_byte = bit / 8;
	cur_rel_bit = bit % 8;
}

void bit_stream::affirm_size(std::size_t bits)
{
	std::size_t new_size = size_;
	while (bits > (new_size - cur_byte) * 8 - cur_rel_bit)
	{
		new_size = new_size * 2;
	}
	if (new_size > size_)
	{
		std::cout << new_size << "\n";
		resize(new_size);
	}
}

void bit_stream::resize(std::size_t new_size)
{
	buffer_type* new_buffer = new buffer_type[new_size];
	// TODO: some redundancy here
	memset(new_buffer, 0, new_size);
	memcpy(new_buffer, buffer, size_);
	delete[] buffer;
	buffer = new_buffer;
	size_ = new_size;
}

void bit_stream::write_bool(bool n)
{
	write_bit(n);
}

void bit_stream::write_uint(uint32 n, unsigned int bits)
{
    // TODO: throw if bits > 32
    assert(bits <= 32);
    affirm_size(bits);
    unsigned int i = 0; // How many bits we've already written
    while (i < bits)
    {
        unsigned int bits_to_write; // How many bits we'll be writing
        // There are 2 possibilities, either we're writing until the end of the byte on the buffer
        // or we aren't! We have to make the choice from either
        if ((8 - cur_rel_bit) <= (bits - i))
        {
            // We get here if we're writing to the end of the current byte
            // on the buffer
            bits_to_write = 8 - cur_rel_bit;
            buffer[cur_byte] |= (n >> (bits - i - bits_to_write));
            ++cur_byte;
        }
        else
        {
            // We get here if writing all the bits we're still left to write
            // won't make us reach the end of the byte we're writing to
            bits_to_write = bits - i;
            uint8 portion = ((n << (8 - bits_to_write)) & 0xFF);
            portion >>= cur_rel_bit;
            buffer[cur_byte] |= portion;
        }
        i += bits_to_write;
        cur_rel_bit = (cur_rel_bit + bits_to_write) % 8;
    }
}

bool bit_stream::read_bool()
{
	return read_bit();
}

void bit_stream::write_sint(sint32 n, unsigned int bits)
{
    write_uint(static_cast<uint32>(n), bits);
}

uint32 bit_stream::read_uint(unsigned int bits)
{
    assert(bits <= 32);
    uint32 ret = 0;
    unsigned int i = 0;
    while (i < bits)
    {
        unsigned int bits_to_write;
        if ((bits - i) <= (8 - cur_rel_bit))
        {
            // We're here because on the current byte in the buffer we have
            // bits to the right that we're supposed to skip
            bits_to_write = bits - i;
            uint8 portion = (buffer[cur_byte] << cur_rel_bit) & 0xFF;
            
            assert(bits_to_write <= 8);
            ret |= (portion >> (8 - bits_to_write));
        }
        else
        {
            // We're here to read the current byte on the buffer from
            // cur_rel_bit till the end
            bits_to_write = 8 - cur_rel_bit;
            
            // Clear up the leftmost bits
            uint8 portion = (buffer[cur_byte] << cur_rel_bit) & 0xFF;
            portion >>= cur_rel_bit;
            
            assert(bits - i - bits_to_write <= bits);
            ret |= (portion << (bits - i - bits_to_write));
        }
        i += bits_to_write;
        cur_rel_bit = cur_rel_bit + bits_to_write;
        if (cur_rel_bit >= 8)
        {
            ++cur_byte;
            cur_rel_bit %= 8;
        }
    }
    return ret;
}

sint32 bit_stream::read_sint(unsigned int bits)
{
    return static_cast<sint32>(read_uint(bits));
}

void bit_stream::write_string(const std::string& str)
{
    write_uint(str.size(), 32);
    for (std::string::const_iterator iter = str.begin(); iter != str.end();
         ++iter)
    {
        write_uint(*iter, 8);
    }
}

std::string bit_stream::read_string()
{
    std::string ret;
    std::string::size_type chars = read_uint(32);
    for (std::string::size_type i = 0; i < chars; ++i)
    {
        ret.append(1, read_uint(8));
    }
    return ret;    
}

#if 0
void bit_stream::printContents() const
{
	for (std::size_t i = 0; i < size_; ++i)
    {
		std::cout << static_cast<unsigned int>(buffer[i]) << "\n";
	}
}
#endif

void bit_stream::clear()
{
	if (buffer != 0)
		delete[] buffer;
}

void bit_stream::write_bit(bool bit)
{
	affirm_size(1);
	buffer[cur_byte] |= (bit << (8 - cur_rel_bit - 1));
	inc_bit();
}

bool bit_stream::read_bit()
{
	bool ret = (buffer[cur_byte] >> (8 - cur_rel_bit - 1)) & 0x01;
	inc_bit();	
	return ret;
}

void bit_stream::inc_bit()
{
	cur_rel_bit += 1;
	if (cur_rel_bit == 8)
	{
		cur_byte += 1;
		cur_rel_bit = 0;
	}
}

