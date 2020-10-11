/*
 * Hold all the definations and header file includes, that change with
 * platform.
 * */
#ifndef __CROSS_PLATFORM__
#define __CROSS_PLATFORM__

#if defined(_WIN32) || defined(_WIN64)
	#define __WINDOWS
#endif

#endif // __CROSS_PLATFORM__

