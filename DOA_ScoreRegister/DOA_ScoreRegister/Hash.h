#pragma once
#include <string>

extern int ARRAY_SIZE;

namespace Hash
{
	int hh(std::string s)
	{
		const char* str = s.c_str();
		return (str[0] + str[s.length() / 2] + str[s.length() - 1]) % ARRAY_SIZE;

	}


	int djb2(std::string s)
	{
		unsigned long hash = 5381;
		int c;
		auto str = s.c_str();

		while (c = *str++)
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		return (hash % ARRAY_SIZE);
	}
}