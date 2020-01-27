#pragma once

#ifdef SQ_PLATFORM_WINDOWS
	#ifdef SQ_BUILD_DLL
		#define SQUARE_API __declspec(dllexport)
	#else
		#define SQUARE_API __declspec(dllimport)
	#endif
#else
	#error Square only supports Windows!
#endif