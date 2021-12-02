
## Tiny Encryption Algorithm implementation in C

The Tiny Encryption Algorithm is one of the fastest and most efficient 
cryptographic algorithms in existence. It was developed by David Wheeler and 
Roger Needham at the Computer Laboratory of Cambridge University. 

## Goal

The goal was to learn a crypographic algorithm that is easy to implement both 
on C and in Assembly language.

The TEA algorithm is easy to implement and the `tea` application with it gets 
compilled into can used to Encrypt and Decrypt files.

## Implementation

It takes as input, names of files that need to be entrypted/decrypted and after
performing the operation writes the output in separate files.

|Mode | Input | -N option | Output |
|-----------|--------------|-------------|-------------|
|**Encryption** | `any file type` | true | _Invalid option_ |
|**Encryption** | `any file type` | false | files with same name but `.3` extension added |
|**Decryption** | files of `.3` extension | true | Output in stdout |
|**Decryption** | files of `.3` extension | false | files with same name but `.3` extension removed |

The algorithm is contained in `tea.c` file and `main.c` deals with testing 
arguments and calling tea routines to entrypt/decrypt entire files.

## Build

Run the 

* `build.sh`  (Linux) file in shell. 
* `build.bat` (Windows)

It will build in the local directory, but 
will not install it anywhere. So no root is required.

## Usage:

```
tea [-e |-d [-N] ] [-D] [-v] [-k '16 byte key'|-K] -I <...>
-e    - Encrypt
        Encrypts the input files and the output files of each will be placed in the same directory with extension .3
-d    - Decrypt
        Decrypts the input files and the output files of each will be placed in the same directory excluding extension .3
-N    - When decrypting, display output to stdout.
-D    - Deletes source files after encryption or decryption.
-v    - Verbose
-k    - 16 byte key (as argument).
-K    - 16 byte key (from stdin).
-I    - Files that need to be processed.

Notes:
      - Cannot use -D (Delete file), -N (stdout output) together.
      - Cannot use -e (encryption), -N (stdout output) together.
      - When using -N (stdout output), -v (Verbose) is ignored.

```

## Example:

```
$ tea -ek 'great elephant i' -I secret1 secret2 secret3
```

**or**


```
# With the new -K option
$ tea -eK -I secret1 secret2 secret3
Enter key (16 characters): great elephant i
```

This encrypts the files `secret1, secret2, secret3` using the key 
`great elephant i`, and creates three output files, one for each, with 
`.3` extension.


```
$ tea -dk 'great elephant i' -I password.3
```

**or**

```
# With the new -K option
$ tea -dK -I password.3
Enter key (16 characters): great elephant i
```

This decrypts the file `password.3` using the key `great elephant i`, and 
writes the output to `password` file. 

