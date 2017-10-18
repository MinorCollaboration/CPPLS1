#ifndef UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED
#define UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED

namespace ui
{
	namespace cnsl
	{
		class CommandDescription
		{
		public:
			char* command;		// pointer of char string
			char* description;	// pointer of char string
			char** parameters;	// pointer Array of char strings
		}; // class CommandDescription
	} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED