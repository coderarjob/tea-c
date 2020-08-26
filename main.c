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
 *    Author: Arjob Mukherjee (arjobmukherjee@gmail.com)
 *    Dated : 16th August 2020
 * ---------------------------------------------------------------------------
 * */
#include <stdio.h>        // For printf and NULL, etc..
#include <stdint.h>       // For standard int types
#include <stdlib.h>       // For exit, malloc
#include <string.h>       // For strcmp, strlen, etc..
#include <unistd.h>       // For unlink
#include "tea.h"

#define USAGE(p) fprintf(stderr, \
        "Tiny Encryption Algorithm implementation, with 128 bit key.\n" \
        "Performs Encryption/Decruption of multiple flies.\n" \
        "usage:\n%s [-e |-d [-N] ] [-D] [-v] -k '16 byte key' -I <...>\n" \
        "-e    - Encrypt\n" \
        "        Encrypts the input files and the output files of each" \
        " will be placed in the same directory with extension .3\n" \
        "-d    - Decrypt\n" \
        "        Decrypts the input files and the output files of each" \
        " will be placed in the same directory excluding extension .3\n" \
        "-N    - When decrypting, display output to stdout.\n" \
        "-D    - Deletes source files after encryption or decryption.\n" \
        "-v    - Verbose\n" \
        "-k    - 16 byte key.\n" \
        "-I    - Files that need to be processed.\n" \
        "\nNotes:\n"\
        "      - Cannot use -D (Delete file), -N (stdout output) together.\n" \
        "      - Cannot use -e (encryption), -N (stdout output) together.\n" \
        "      - When using -N (stdout output), -v (Verbose) is ignored.\n" \
        , p)

#define MAX_FILENAME_LENGTH 255          // Length of file path
#define MAX_INPUT_FILES 50               // number of files
#define ENCRYPTED_FILE_EXTENSION ".3"

#define FLAG_DELETE_SOURCE_FILE      (1 << 0)
#define FLAG_VERBOSE                 (1 << 1)
#define FLAG_OUTPUT_TO_STDOUT        (1 << 2)

enum errors { ERR_NONE, 
              ERR_MALLOC, 
              ERR_FILE_FAILED, 
              ERR_INVALID_ARG };

struct op
{
    int  mode;
    int  count;
    char key[KEY_SIZE];
    char *files[MAX_INPUT_FILES];
    int  flags;                         /* Encryption or Decryption flags */
};

int readargs(char *argv[], struct op *out);
bool delete(char *filename);
char **read_args_files(char *argv[], struct op *out);
int read_args_key(char *arg, struct op *out);
int strip_extension(char *filename, char *extension, char *out);
bool args_is_valid(struct op *out);

int main(int argc,char *argv[])
{
    int status;
    struct op prm = {0};

    // 1. Read parameters
    if (argc >= 4)
        status = readargs(argv,&prm);

    if (status != ERR_NONE || prm.mode == UNSET || prm.key[0] == 0)
    {
        USAGE(argv[0]);
        exit(ERR_INVALID_ARG);
    }

    // Now we encrypt/decrypt each of the files.
    char output_filename[MAX_FILENAME_LENGTH + 2];
    int ed_status,
        enc_dec_mode = 0;

    for(int i = 0; i < prm.count; i++) {

        // -- 1. Perform Encryption and Decryption --

        if (prm.mode == ENCRYPT) {
            // Output file name: InputfilePath + ".3"
            output_filename[0] = '\0';
            strcat(output_filename, prm.files[i]);
            strcat(output_filename, ENCRYPTED_FILE_EXTENSION);
        }
        else{
            // Output file name: InputFilePath - ".3" extension
            if (strip_extension(prm.files[i], 
                                ENCRYPTED_FILE_EXTENSION,
                                output_filename) == ERR_INVALID_ARG){
                fprintf(stderr,"Warning: Invalid file extension in %s\n",
                        prm.files[i]);
                continue;
            }

            // Feature: Output to stdout
            if (prm.flags & FLAG_OUTPUT_TO_STDOUT) {
                strcpy(output_filename,"(stdout)");
                enc_dec_mode |= TEA_FLAG_OUTPUT_STDOUT;
                printf("-------------- %u: %s --------------\n", 
                        i+1, prm.files[i]);
            }

        } /* if (mode == ENCRYPT) */

        ed_status = encrypt_decrypt (prm.mode, 
                                     prm.key,
                                     enc_dec_mode,
                                     prm.files[i], 
                                     output_filename);

        // -- 2. Display message about the status of the above operation --

        // Feature: verbosity
        if (prm.flags & FLAG_VERBOSE){
            printf("%s: %s => %s : %s\n", 
                    (prm.mode == ENCRYPT) ? "Encryption" : "Decryption",
                    prm.files[i], 
                    output_filename,
                    (ed_status) ? "Success" : "Failed");
        }

        // -- 3. Delete the file if -D option is set --

        // Feature: Delete file is -D was provided.
        if (ed_status == true && 
            prm.flags & FLAG_DELETE_SOURCE_FILE) {
            // Feature: verbosity
            printf("Deletion: %s : %s\n", prm.files[i],
                    delete (prm.files[i]) ? "Success": "Failed");
        }
    }   /* for */
    return ERR_NONE;
}

bool delete(char *filename)
{
    if (unlink(filename) == -1){
        fprintf(stderr,
                "File %s could not be deleted.\n", filename);
        perror("unlink");
        return false;
    }

    return true;
}

/*
 * Fills 'out' parameter with the filename with Extension removed.
 * */
int strip_extension(char *filename, char *extension, char *out)
{
    int flen = strlen(filename),
        el    = flen - strlen(extension);   // Extension begins at this index.

    *out = '\0';
    if (strcmp (filename + el,extension))
        return ERR_INVALID_ARG;

    strcpy(out, filename);
    *(out + el) = '\0';
    return ERR_NONE;
}

/*
 * It will read the startup arguments and fill the 'op' structure.
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
                        read_args_key(*argv++,out);
                        break;
                    case 'I':
                        argv = read_args_files(argv,out);
                        break;
                    case 'N':
                        out->flags |= FLAG_OUTPUT_TO_STDOUT;
                        break;
                    case 'v':
                        out->flags |= FLAG_VERBOSE;
                        break;
                    case 'D':
                        out->flags |= FLAG_DELETE_SOURCE_FILE;
                        break;
                    default:
                        fprintf(stderr,"Error: Invaid argument: %s\n",arg);
                        return ERR_INVALID_ARG;
                        break;
                }
            }
        }
    }

    // Check validity of arguments and return
    return (args_is_valid (out)) ? ERR_NONE : ERR_INVALID_ARG;
}

bool args_is_valid(struct op *out)
{

    if (out->flags & FLAG_OUTPUT_TO_STDOUT && out->mode == ENCRYPT){
        fprintf(stderr,
                "Error: -N option can only be used in Decrypt mode.\n");
        return false;
    }

    if (out->flags & FLAG_OUTPUT_TO_STDOUT && 
            out->flags & FLAG_DELETE_SOURCE_FILE) {
        fprintf(stderr,
                "Warning: -D is ignored when outputing to stdout.\n");
       
        // Remove -D flag
        out->flags &= ~FLAG_DELETE_SOURCE_FILE;
    }

    if (out->flags & FLAG_OUTPUT_TO_STDOUT && out->flags & FLAG_VERBOSE) {
        fprintf(stderr,
                "Warning: -v is ignored when outputing to stdout.\n");
        
        // Clear verbose flag
        out->flags &= ~FLAG_VERBOSE;
    }
    return true;
}

int read_args_key(char *arg, struct op *out)
{
    if (strlen(arg) != KEY_SIZE){
        fprintf(stderr,
                "Error: Invalid key. Must be %u bytes long.\n", KEY_SIZE);
        return ERR_INVALID_ARG;
    }

    memcpy(out->key,arg,KEY_SIZE);    
    return 0;
}

char **read_args_files(char *argv[], struct op *out)
{
    int filei;        // Points to the string in argv being copied.
    char *file;       // Points to the current string at argv[filei]

    // It will take each of the strings in argv and copy them to out->files[].
    // The loop stops when there are no more strings in argv array or when the
    // current pointed string starts with a - (- marks start of parameter).
    for(filei = 0 
            ; (file = argv[filei]) && *file != '-' && filei < MAX_INPUT_FILES 
            ; filei++)
    {
        // Check the length of the file name.
        // Check if filename + EOL < MAX_FILENAME_LENGTH
        int len = strlen(file) + 1;
        if (len > MAX_FILENAME_LENGTH) {
            fprintf(stderr,"Warning: Skipping, too long: %s", file);
            continue;
        }

        // Create a string if required length.
        if ((out->files[filei] = malloc(sizeof(char) * len)) == NULL) {
            perror("malloc");
            exit(ERR_MALLOC);
        }

        // Copy file path from argument to file->files[filei]
        memcpy(out->files[filei],file,len);    
    }

    // There are more files than space in out->files[] i.e > MAX_INPUT_FILES
    if (file != NULL && *file != '-')
        fprintf(stderr, "Warning: Too many files. Skipping after: %s\n",file);

    // Update count
    out->count = filei;

    return &argv[filei];
}
