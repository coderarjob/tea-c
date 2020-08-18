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
		"usage:\n%s [-e|-d] -k '16 byte key' -I <...>\n" \
		"-e    - Encrypt\n" \
		"        Encrypts the input files and the output files of each" \
		" will be placed in the same directory with extension .3\n" \
		"-d    - Decrypt\n" \
		"        Decrypts the input files and the output files of each" \
		" will be placed in the same directory excluding extension .3\n" \
		"-k    - 16 byte key.\n" \
		"-I    - Files that need to be processed.\n" \
		, p)


#define KEY_SIZE 16 	// bytes
#define DATA_SIZE 8		// bytes
#define MAX_INPUT_FILES 50 // number of files
#define MAX_FILENAME_LENGTH 255 // Length of file path

enum opmode {UNSET,ENCRYPT, DECRYPT};

struct op
{
	int mode;
	int count;
	char key[KEY_SIZE];
	char *files[MAX_INPUT_FILES];
};

int readargs(char *argv[], struct op *out);
char **readfiles(char *argv[], struct op *out);
int readKey(char *arg, struct op *out);

int main(int argc,char *argv[])
{
	struct op prm = {0};

	// 1. Read parameters
	if (argc >= 4)
		readargs(argv,&prm);

	printf("mode %u, key: %s, file count: %u\n",prm.mode,prm.key,prm.count);
	for(int i = 0; i < prm.count; i++)
		printf("File %u: %s\n",i,prm.files[i]);

	if (prm.mode == UNSET || prm.key[0] == 0)
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
		if (prm.mode == ENCRYPT)
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

/*
 * It will read the startup arguments and fill the 'op' structure.
 *
 * */
int readargs(char *argv[], struct op *out)
{
	char *arg;

	// Default options
	out->mode = UNSET;
	out->count = 0;

	while((arg = *argv++)) {
		if (*arg == '-') {
			while(*++arg){
				switch(*arg) {
					case 'e':
						out->mode = ENCRYPT;
						break;
					case 'd':
						out->mode = DECRYPT;
						break;
					case 'k':
						readKey(*argv++,out);
						break;
					case 'I':
						argv = readfiles(argv,out);
						break;
					default:
						fprintf(stderr,"Error: Invaid argument: %s\n",arg);
						return 1;
						break;
				}
			}
		}
	}
	return 0;
}


int readKey(char *arg, struct op *out)
{
	if (strlen(arg) != KEY_SIZE){
		fprintf(stderr,
				"Error: Invalid key. Must be %u bytes long.\n", KEY_SIZE);
		return 1;
	}
	else{
		memcpy(out->key,arg,KEY_SIZE);	
	}
	return 0;
}

char **readfiles(char *argv[], struct op *out)
{
	int filei;
	char *arg;

	for(filei = 0 
			; (arg = argv[filei]) && *arg != '-' && filei < MAX_INPUT_FILES 
			; filei++)
	{

		// Check the length of the file name.
		int len = strlen(arg) + 1;	// +1 for EOL
		if (len > MAX_FILENAME_LENGTH) {
			fprintf(stderr,"Warning: Skipping, too long: %s", arg);
			continue;
		}

		// Create a string if required length.
		if ((out->files[filei] = malloc(sizeof(char) * len)) == NULL) {
			perror("malloc");
			exit(3);
		}

		// Copy file path from argument to file->files[filei]
		memcpy(out->files[filei],arg,len);	
	}

	if (arg != NULL && *arg != '-')
		fprintf(stderr, "Warning: Too many files. Skipping after: %s\n",arg);

	// Update count
	out->count = filei;

	return &argv[filei];
}
