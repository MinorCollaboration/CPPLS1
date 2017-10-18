#ifndef MAIN_HEADER_INCLUDED
#define MAIN_HEADER_INCLUDED

#ifdef _WIN32
  #include <Windows.h>
  #ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define _CRTDBG_MAP_ALLOW_NEW
	#include <stdlib.h>
	#include <crtdbg.h>
  #endif // _DEBUG
#endif // _Win32

#include <iostream>
#include <exception>
#include <system_error>

#include "game/game.h"
#include "ui/userinterfacebase.h"
#include "ui/cnsl/userinterface.h"

#endif // _MAIN_HEADER_INCLUDED