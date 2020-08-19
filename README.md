
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

|Mode | Input | Output |
|-----------|--------------|-------------|
|**Encryption** | `any file type` | files with same name but `.3` extension added |
|**Decryption** | files of `.3` extension | files with same name but `.3` extension removed |

The algorithm is contained in `tea.c` file and `main.c` deals with testing 
arguments and calling tea routines to entrypt/decrypt entire files.

## Build

Run the `build.sh` file in shell. It will build in the local directory, but 
will not install it anywhere. So no root is required.

## Usage:

```
tea [-e [-D] |-d] -k '16 byte key' -I <input files...>
-e    - Encrypt.
-d    - Decrypt.
-D    - Delete source files after encryption.
-k    - 16 byte key.
-I    - Input files for decryption/encryption.
```

## Example:

```
tea -ek 'great elephant i' -I secret1 secret2 secret3
```

This encrypts the files `secret1, secret2, secret3` using the key 
`great elephant i`, and creates three output files, one for each, with 
`.3` extension.


```
tea -dk 'great elephant i' -I password.3
```
This decrypts the file `password.3` using the key `great elephant i`, and 
writes the output to `password` file. 


