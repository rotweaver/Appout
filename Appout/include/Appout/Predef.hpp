#pragma once

#if defined(__clang__)
	#define APPOUT_CLANG
#elif defined (__GNUC__) || defined (__GNUG__)
	#define APPOUT_GNU
#elif defined(_MSC_VER)
	#define APPOUT_MSVC
#endif


#if defined(_WIN64)
	#define APPOUT_WIN64 
#elif defined(_WIN32)
	#define APPOUT_WIN32
#endif
