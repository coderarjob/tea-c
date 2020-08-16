/*
 * ---------------------------------------------------------------------------
 * Tiny Encryption Algorithm (TEA) implementation.
 * ---------------------------------------------------------------------------
 *  Encrypts/Decrypts reading from input stream, writes back to output
 *  stream.
 *
 *	Author: Arjob Mukherjee (arjobmukherjee@gmail.com)
 *	Dated : 16th August 2020
 * ---------------------------------------------------------------------------
 * */
#ifndef __TEA__
#define __TEA__

	#include <stdint.h>	// For standard int types
	void code(uint32_t v[1], uint32_t k[3]);
	void decode(uint32_t v[2], uint32_t k[4]);
#endif // __TEA__
