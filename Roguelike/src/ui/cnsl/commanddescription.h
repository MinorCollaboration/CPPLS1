#ifndef UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED
#define UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED

#include <string>
#include <utils/array.hpp>

namespace ui
{
namespace cnsl
{
	class CommandDescription
	{
	public:
		char* command;
		char* description;
		utils::Array<char*> parameters;
	}; // class CommandDescription
} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED
