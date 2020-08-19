/*
 * ---------------------------------------------------------------------------
 * Tiny Encryption Algorithm (TEA) implementation.
 * ---------------------------------------------------------------------------
 *  Encrypts/Decrypts reading from input stream, writes back to output
 *  stream.
 *
 *    Author: Arjob Mukherjee (arjobmukherjee@gmail.com)
 *    Dated : 16th August 2020
 * ---------------------------------------------------------------------------
 * */
#include "tea.h"
#include <unistd.h>        // For read, write, access, close
#include <fcntl.h>         // For open
#include <stdio.h>         // For printf and NULL, etc..
#include <string.h>        // For memset

void decode(uint32_t *v, uint32_t *k)
{
    uint32_t v0 = v[0],
             v1 = v[1],
             delta = 0x9e3779b9,
             n = 32;    // Invariant: Number of bits remaining
            
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
             n = 32;    // Invariant: Number of bits remaining
            
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

bool encrypt_decrypt(int mode, char *in_file, char *out_file, char *key)
{
    char d[DATA_SIZE];
    int len, inf, outf;

    // 1. Check if out_file already exists
    if (access(out_file, F_OK) == 0){
        fprintf(stderr,"Warning: Output file already exists %s\n",
                out_file);
        return false;
    }
    
    // Check if input file exists.
    if (access(in_file, F_OK) == -1){
        fprintf(stderr,"Warning: Skipping, Input file do not exists %s\n",
                in_file);
        return false;
    }

    // 2. Open the files
    if ((inf = open (in_file, O_RDONLY)) == -1) {
        perror("open - input");
        return false;
    }

    if ((outf = open (out_file, 
                      O_CREAT|O_WRONLY,
                      DEFAULT_FILE_CREATION_MODE)) == -1) {
        perror("open - output");
        close(inf);
        return false;
    }

    // Read 8 bytes from the file, until EOF is reached or some error
    // occurs.
    while ((len = read (inf,d,DATA_SIZE)) > 0){

        // Fill rest of the d array with zero.
        memset(&d[len], 0, DATA_SIZE - len);    

        // Performs Encryption / Decryption operation
        if (mode == ENCRYPT)
            code ((uint32_t *) d, (uint32_t *) key);
        else
            decode ((uint32_t *) d, (uint32_t *) key);

        // Write back
        if ((len = write (outf,d,DATA_SIZE)) < 0)
            break;
    }

    // Clean up and exit
    close (inf);
    close (outf);

    // In case of read or write error, we exit and display this error.
    if (len < 0){
        perror("read/write");
        return false;
    }

    return true;
}
