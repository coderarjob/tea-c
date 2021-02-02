/*
 * Hold all the definations and header file includes, that change with
 * platform.
 * ---------------------------------------------------------------------------
 * Information:
 * ---------------------------------------------------------------------------
 *  WINDOWS:
 *  The C++ Compiler comes with C Runtime Library which is responsible for
 *  providing a POSIC like compatability. When compiling a C file with CL, the
 *  CRT library msvcrt.lib by default. 
 *  Helpful links:
 *      - https://docs.microsoft.com/en-us/cpp/c-runtime-library/crt-library-features?view=vs-2019
 *      - https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/crt-alphabetical-function-reference?view=vs-2019
 * ---------------------------------------------------------------------------
 * */
#ifndef __CROSS_PLATFORM__
#define __CROSS_PLATFORM__

#if defined(_WIN32) || defined(_WIN64)
	#define __WINDOWS
#endif

#endif // __CROSS_PLATFORM__

