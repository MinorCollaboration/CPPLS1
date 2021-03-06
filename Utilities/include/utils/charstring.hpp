#ifndef UTILS_CHARSTRING_HEADER_INCLUDED
#define UTILS_CHARSTRING_HEADER_INCLUDED

#include <iostream>
#include <istream>
#include <cctype>

namespace utils
{
	class CharString {
	public:
		char* str;
		CharString() : str() {}  // Initialize NULL
		CharString(char* text) : str(text){}
		//~CharString() { delete[] str; }
		// Conversions to be usable with C functions
		operator char**() { return &str; }
		operator char*() { return str; }
		friend std::istream& operator>>(std::istream &is, CharString &cs);
	};

	static std::istream& operator>> (std::istream& in, CharString& cs) {
		// read all the data you need to construct an object.
		//
		char* text = new char[100];
		in.getline(text, 100, ' ');
		// Then:
		if (in) { // Read succeeded! Update object.
			// Build a new object of the appropriate type.
			
			CharString dup(text);

			// Swap the object you were given as input for the one you
			// just read. This way, if the read completely succeeds, you
			// update the rhs, and if the read failed, nothing happens.
			std::swap(cs, dup);
		}
		return in;
	}

	/*template <typename ... char>
	char* concat(const char* first, const char*... rest)
	{
		return first << concat(rest...);
	}*/
	static char& chartolower(const char* a) {
		char* b = _strdup(a);
		char* start = b;
		while (*b) {
			*b = tolower(*b);
			b++;
		}

		return *start;
	}

	// check if there are differences (besides case)
	static int icompare(const char* a, const char* b) noexcept
	{
		return strcmp(&chartolower(a), &chartolower(b));
	}

	/**
	 * 
	 */
	
	// Check the number of differences
	static int istrcmp(const char* a, const char* b) noexcept
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