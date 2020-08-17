/*
 * ---------------------------------------------------------------------------
 * Tiny Encryption Algorithm (TEA) implementation.
 * ---------------------------------------------------------------------------
 *  Encrypts/Decrypts reading from input stream, writes back to output
 *  stream.
 *
 *  Reference:
 *   - https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
 *   - http://www.tayloredge.com/reference/Mathematics/TEA-XTEA.pdf
 *
 *	Author: Arjob Mukherjee (arjobmukherjee@gmail.com)
 *	Dated : 16th August 2020
 * ---------------------------------------------------------------------------
 * */
#include <stdio.h>	// For printf and NULL
#include <stdint.h>	// For standard int types
#include <unistd.h>	// For read, write
#include <stdlib.h> // For exit
#include <string.h> // For strcmp
#include "tea.h"

#define USAGE(p) fprintf(stderr, \
		"Tiny Encryption Algorithm implementation, with 128 bit key.\n" \
		"Performs Encryption/Decruption of multiple flies.\n" \
		"usage:\n%s [-e|-d] -k '16 byte key' <...>\n" \
		"-e    - Encrypt\n" \
		"        Encrypts the input files and the output files of each" \
		" will be placed in the same directory with extension .3\n" \
		"-d    - Decrypt\n" \
		"        Decrypts the input files and the output files of each" \
		" will be placed in the same directory excluding extension .3\n" \
		, p)

#define KEY_SIZE 16 	// bytes
#define DATA_SIZE 8		// bytes

enum opmode {ENCRYPT, DECRYPT, UNSET};

struct op
{
	int mode;
	char *key;
	char *files[];
};

int main(int argc, char *argv[])
{
	int mode = UNSET;
	uint8_t d[DATA_SIZE];
	uint8_t k[KEY_SIZE] = {0};

	// 1. Read parameters
	if (argc >= 3) {
		// 1.1 Read Mode
		if (strcmp(argv[1],"-e") == 0)
			mode = ENCRYPT;
		else if (strcmp(argv[1],"-d") == 0)
			mode = DECRYPT;
		else
			fprintf(stderr,"Invalid option %s\n",argv[1]);

		// 1.2 Read Key
		if (strlen(argv[2]) != KEY_SIZE)
			fprintf(stderr,"Invalid key. Must be %u bytes long.\n", KEY_SIZE);
		else
			memcpy(&k,argv[2],KEY_SIZE);	// Copy into k variable

	}
	
	if (mode == UNSET || k[0] == 0)
	{
		USAGE(argv[0]);
		exit(1);
	}

	// 2. Read 8 bytes from the file, until EOF is reached or some error
	// occurs.
	int len;
	while ((len = read(0,d,DATA_SIZE)) > 0){
		// 3. If read < 8, pad with zeros
		//    Alternate: bzero(&d[len],8-len); 
		// Note: if 'd' is delcared as 
		//
		// 			uint32_t d[4], 
		//
		// then the below code will look like 
		//
		//         memset(((uint8_t *)&d[0]+len),0,8 - len);	Why?
		//
		// Because, &d[0] is uint32_t *, so addition will increment in 4 byte
		// increments. We want increments of 1 byte, thats why we cast it to
		// uint8_t *. 
		memset(&d[len],0,DATA_SIZE - len);	

		// 4. If mode == ENCRYPT, we code the read 8 bytes
		//    else decode the 8 bytes
		if (mode == ENCRYPT)
			code((uint32_t *) d, (uint32_t *) k);
		else
			decode((uint32_t *) d, (uint32_t *) k);

		// 5. Write back
		if ((len = write(1,d,DATA_SIZE)) < 0)
			break;
	}

	// In case of read or write error, we exit and display this error.
	if (len < 0){
		perror("read/write");
		exit(2);
	}

	return 0;
}

struct op *readargs(const char *argv[])
{
	struct op *out;
	if ((out = malloc(sizeof(struct op))) == NULL)
	{
		perror("malloc");
		exit(3);
	}

	return out;
}
