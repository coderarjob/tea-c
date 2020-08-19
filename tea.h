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
#ifndef __TEA__
#define __TEA__

    #include <stdint.h>    // For standard int types
    #include <stdbool.h>    // for bool, true, false

    // Cannot be changed, without impact to the code.
    
    #define KEY_SIZE 16     // bytes
    #define DATA_SIZE 8        // bytes

    // Can be changed if needed.
    
    #define DEFAULT_FILE_CREATION_MODE    00644

    enum opmode {UNSET,
                 ENCRYPT, 
                 DECRYPT};

    void code(uint32_t v[1], uint32_t k[3]);
    void decode(uint32_t v[2], uint32_t k[4]);
    bool encrypt_decrypt(int mode, char *in_file, char *out_file, char *key);
#endif // __TEA__
