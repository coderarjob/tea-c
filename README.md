# Tiny Encryption Algorithm implementation in C

The Tiny Encryption Algorithm is one of the fastest and most efficient 
cryptographic algorithms in existence. It was developed by David Wheeler and 
Roger Needham at the Computer Laboratory of Cambridge University. 

## Goal

The goal was to learn a crypographic algorithm that is easy to implement both
on C and in Assembly language.

The TEA algorithm is easy to implement and the `tea` application with it gets
compilled into can used to Encrypt and Decrypt files.

## Implementation

The current implementation reads data from the Standard Input and writes
entrypted/decrypted output to the Standard Output. The algorithm is contained
in `tea.c` file and `main.c` deals with testing arguments and calling tea
routines to entrypt/decrypt entire files.

## Build

Run the `build.sh` file in shell. It will build in the local directory, but
will not install it anywhere. So no root is required.

## Usage:

```
./tea [-e|-d] '16 byte key'
-e    - Encrypt
-d    - Decrypt
```

## Example:

```
tea -e 'great elephant i' <password >password.e
```
This encrypts the file `password` using the key `great elephant i`, and creates
output in `password.e` file.

```
tea -d 'great elephant i' <password.e
```
This decrypts the file `password.e` using the key `great elephant i`, and
writes the output in standard output. You could also be redirect the output to
a file, if you want.

## Issues:

```
tea -e 'great elephant i' <password >password
```

The input and output file cannnot be the same. IT CLEARS THE WHOLE FILE.


