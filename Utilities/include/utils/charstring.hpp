#ifndef UTILS_CHARSTRING_HEADER_INCLUDED
#define UTILS_CHARSTRING_HEADER_INCLUDED

#include <cctype>

namespace utils
{
	/*template <typename ... char>
	char* concat(const char* first, const char*... rest)
	{
		return first << concat(rest...);
	}*/

	int istrcmp(const char* a, const char* b) noexcept
	{
		for (;; a++, b++)
		{
			int d = tolower(*a) - tolower(*b);
			if (d != 0 || !*a)
				return d;
		}
		return 0;
	}
}

#endif