
/* Cross platform implementation of Standard Integer types.
 * As the original project was developed in C99. We will keep the typenames
 * same.
 * */

#ifndef __STD_INT__
#define __STD_INT__

#include "crossplatform.h"
/* stdint */
#ifdef __WINDOWS
	// https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=vs-2019
	typedef __int32 uint32_t;
#else
	#include <stdint.h>    // For standard int types
#endif

#endif
