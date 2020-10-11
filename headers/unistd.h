/* Cross platform implementation of methods from unistd.h
 * As the original project was developed in C99. We will keep the typenames
 * same.
 * */

#ifndef __STD_UNISTD__
#define __STD_UNISTD__

#include "crossplatform.h"

/* stdbool */
#ifdef __WINDOWS
    #include <io.h>
    // Part of C Runtime Library by Microsoft. 
    #define unlink _unlink 
    #define read _read 
    #define write _write 
    #define close _close 
    #define access _access

    // Macros
    #define STDIN_FILENO 0
    #define STDOUT_FILENO 1
    #define STDERR_FILENO 2
    #define F_OK 0
#else
	#include <unistd.h>     // unlink, read, write, access, close
#endif

#endif
