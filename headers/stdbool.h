/* Cross platform implementation of Boolean types.
 * As the original project was developed in C99. We will keep the typenames
 * same.
 * */

#ifndef __STD_BOOL_
#define __STD_BOOL_

#include "crossplatform.h"

/* stdbool */
#ifdef __WINDOWS
    // In VS-2008 (CL - 1500), bool was not part of the language.
    typedef __int8 bool;
    #define true 1
    #define false 0
#else
	#include <stdbool.h>    // for bool, true, false
#endif

#endif
