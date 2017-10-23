#ifndef MAIN_HEADER_INCLUDED
#define MAIN_HEADER_INCLUDED

#ifdef _WIN32
 #include <Windows.h>
 #ifdef _DEBUG
  #define _CRTDBG_MAP_ALLOC
  #define _CRTDBG_MAP_ALLOC_NEW
  #define _CRT_SECURE_NO_WARNINGS
  #include <stdlib.h>
  #include <crtdbg.h>
 #endif // _DEBUG 
#endif // _WIN32

#include <iostream>
#include <stdexcept>
#include <system_error>

#include "game/game.h"
#include "ui/userinterfacebase.h"
#include "ui/cnsl/userinterface.h"

#endif // #ifndef MAIN_HEADER_INCLUDED