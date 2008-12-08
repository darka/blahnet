#include "bit_stream.hpp"
#include <ctime>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <tut.h>

namespace tut
{
	struct bit_stream_data
	{
		static std::size_t bits_needed(int n) // bits needed to write the number
		{
			std::size_t shift = 32;
			do
			{
				shift -= 1;
				if (((n >> shift) & 0x1) == 1)
				{
					return shift + 1;
				}
			} while (shift != 0);
			return 1;
		}
		typedef std::pair<uint32, unsigned int> value_pair;
	};

	typedef test_group<bit_stream_data> tg;
	tg bit_stream_tg("bit_stream test");

	template<> template<>
	void tg::object::test<1>()
	{
		set_test_name("test-only bit counting function test");
		ensure_equals("bits for 7", bit_stream_data::bits_needed(7), 3);
		ensure_equals("bits for 0", bit_stream_data::bits_needed(0), 1);
		ensure_equals("bits for 1", bit_stream_data::bits_needed(1), 1);
		ensure_equals("bits for 12", bit_stream_data::bits_needed(12), 4);
		ensure_equals("bits for 65535", bit_stream_data::bits_needed(65535), 16);
		ensure_equals("bits for 2541252", bit_stream_data::bits_needed(2541252), 22);
		ensure_equals("bits for 2", bit_stream_data::bits_needed(2), 2);
	}

	template<> template<>
	void tg::object::test<2>()
	{
		set_test_name("mixed bit/uint/string reading and writing");
		bit_stream bs(1);

		bs.write_bool(false);
		bs.write_bool(false);
		bs.write_bool(true);
		bs.write_bool(false);

		bs.write_bool(true);
		bs.write_bool(false);
		bs.write_bool(false);
		bs.write_bool(false);

		bs.write_bool(false);

		bs.write_string("abcdefgh10209420938");

		std::vector<value_pair> values; // (value, bits_needed)
		values.push_back(std::make_pair(13, bit_stream_data::bits_needed(13)));
		values.push_back(std::make_pair(0, 12));
		values.push_back(std::make_pair(2541252, bit_stream_data::bits_needed(2541252)));
		values.push_back(std::make_pair(123456, bit_stream_data::bits_needed(123456)));
		values.push_back(std::make_pair(1, 32));
		values.push_back(std::make_pair(100, 32));
		values.push_back(std::make_pair(11234, 32));
		values.push_back(std::make_pair(0, bit_stream_data::bits_needed(0)));
		values.push_back(std::make_pair(1, bit_stream_data::bits_needed(1)));
		values.push_back(std::make_pair(3, bit_stream_data::bits_needed(3)));
		for (std::vector<value_pair>::iterator i = values.begin();
		     i != values.end(); ++i)
		{
			bs.write_uint(i->first, i->second);
		}

		bs.write_string("OMG TEST");

		bs.write_bool(false);
		bs.write_bool(true);
		bs.write_bool(true);
		bs.write_bool(false);

		bs.seek(0);

		ensure_equals("bool", bs.read_bool(), false);
		ensure_equals("bool", bs.read_bool(), false);
		ensure_equals("bool", bs.read_bool(), true);
		ensure_equals("bool", bs.read_bool(), false);

		ensure_equals("bool", bs.read_bool(), true);
		ensure_equals("bool", bs.read_bool(), false);
		ensure_equals("bool", bs.read_bool(), false);
		ensure_equals("bool", bs.read_bool(), false);

		ensure_equals("bool", bs.read_bool(), false);

		ensure_equals("string", bs.read_string(), "abcdefgh10209420938");

		for (std::vector<value_pair>::iterator i = values.begin();
		     i != values.end(); ++i)
		{
			ensure_equals("uint", bs.read_uint(i->second), i->first);
		}

		ensure_equals("string", bs.read_string(), "OMG TEST");

		ensure_equals("bool", bs.read_bool(), false);
		ensure_equals("bool", bs.read_bool(), true);
		ensure_equals("bool", bs.read_bool(), true);
		ensure_equals("bool", bs.read_bool(), false);
	}

	template<> template<>
	void tg::object::test<3>()
	{
		set_test_name("random uint writing");
		std::vector<value_pair> values;
		std::srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < 10000; ++i)
		{
			int value = rand();
			values.push_back(std::make_pair(value, bits_needed(value)));
		}

		bit_stream bs;
		for (std::vector<value_pair>::iterator i = values.begin();
		     i != values.end(); ++i)
		{
			bs.write_uint(i->first, i->second);
		}
		bs.seek(0);
		for (std::vector<value_pair>::iterator i = values.begin();
		     i != values.end(); ++i)
		{
			ensure_equals("uint", bs.read_uint(i->second), i->first);
		}
	}

	template<> template<>
	void tg::object::test<4>()
	{
		set_test_name("appending a bit stream");
		bit_stream bs1;
		bit_stream bs2;
		bs1.write_uint(5, 8);
		bs2.write_uint(4, 4);
		bs2.write_uint(7, 3);
		std::size_t orig_size = bs1.size();

		bs1.append(bs2);
		ensure_equals("size stays the same", bs1.size(), orig_size);
		bs1.write_uint(1, 1);

		bit_stream bs3;
		bs3.write_uint(1001, 32);
		bs1.append(bs3);
		bs1.write_uint(12, 4);
		bs1.seek(0);

		ensure_equals("uint", bs1.read_uint(8), 5);
		ensure_equals("uint", bs1.read_uint(4), 4);
		ensure_equals("uint", bs1.read_uint(3), 7);
		ensure_equals("uint", bs1.read_uint(1), 1);
		ensure_equals("uint", bs1.read_uint(32), 1001);
		ensure_equals("uint", bs1.read_uint(4), 12);
	}


	template<> template<>
	void tg::object::test<5>()
	{
		set_test_name("copy constructor and operator=");
		bit_stream bs1;
		bs1.write_uint(123);
		bs1.write_uint(321);
		bs1.seek(0);

		bit_stream bs2;
		bs2.write_uint(212);
		bs2 = bs1;

		bit_stream bs3(bs2);
		ensure_equals("original bs", bs1.read_uint(), 123);
		ensure_equals("original bs", bs1.read_uint(), 321);
		ensure_equals("operator= used", bs2.read_uint(), 123);
		ensure_equals("operator= used", bs2.read_uint(), 321);
		ensure_equals("copy constructor used", bs3.read_uint(), 123);
		ensure_equals("copy constructor used", bs3.read_uint(), 321);
	}
}
