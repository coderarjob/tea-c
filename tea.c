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
#include "tea.h"

void decode(uint32_t *v, uint32_t *k)
{
	uint32_t v0 = v[0],
			 v1 = v[1],
			 delta = 0x9e3779b9,
			 n = 32;	// Invariant: Number of bits remaining
			
	uint32_t sum = delta * 32;
	while(n--)
	{
		v1 -= ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
		v0 -= ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
		sum -= delta;
	}
	v[0] = v0;
	v[1] = v1;
}

void code(uint32_t *v, uint32_t *k)
{
	uint32_t v0 = v[0],
			 v1 = v[1],
			 delta = 0x9e3779b9,
			 n = 32;	// Invariant: Number of bits remaining
			
	uint32_t sum = 0;
	while(n--)
	{
		sum += delta;
		v0 += ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
		v1 += ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
	}
	v[0] = v0;
	v[1] = v1;
}

