#pragma once

#include <tchar.h>
#include <string>
#include <iosfwd>//尽量减少头文件中包含数量，这里只包含前置声明
// Unicode & ANSI for std namespace

#ifdef _UNICODE
//
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __TFILE__ WIDEN(__FILE__)

// string
#define tstring		std::wstring
#define	tsprintf	swprintf_s

#define tstoi		_wtoi
#define tstof		_wtof
#define titos		_itow

// iostream
#define	tfstream	std::wfstream
#define	tifstream	std::wifstream
#define	tofstream	std::wofstream
#define	tiostream	std::wiostream
#define	tistream	std::wistream
#define	tostream	std::wostream

#define tcout		std::wcout
#define tcin		std::wcin
#define tcerr       std::wcerr
//tostring format string
#define tostringstream std::wostringstream
#define tios        std::wios
#else
#define __TFILE__ __FILE__
// string
#define tstring		std::string
#define	tsprintf	sprintf_s

#define tstoi		atoi
#define tstof		atof
#define titos		_itoa

// iostream
#define	tfstream	std::fstream
#define	tifstream	std::ifstream
#define	tofstream	std::ofstream
#define	tiostream	tiostream
#define	tistream	std::istream
#define	tostream	std::ostream

#define tcout		std::cout
#define tcin		std::cin
#define tcerr       std::cerr
#define tostringstream std::ostringstream
#define tios        std::ios

#endif