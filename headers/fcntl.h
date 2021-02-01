/* Cross platform implementation of methods from fcntl.h
 * fcntl.h is part of the C Runtime Library, but function names are little
 * different. 
 * As the original project was developed in C99. We will keep the typenames
 * same.
 * */

#ifndef __STD_FCNTL__
#define __STD_FCNTL__

#include "crossplatform.h"

/* stdbool */
#ifdef __WINDOWS
    #include <io.h>     // _open
	#include <fcntl.h>  // Macros

    // Part of C Runtime Library by Microsoft. 
    #define open _open

    // Macros
    #define O_RDONLY _O_RDONLY
    #define O_CREAT  _O_CREAT
    #define O_WRONLY _O_WRONLY
#else
	#include <fcntl.h>      // open

    // In linux _O_BINARY is not used.  In Windows, this is needed to prevent
    // _write, _read to interpret CTRL+Z as EOL.
    // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/write?view=msvc-160
    #define _O_BINARY 0     
#endif

#endif
