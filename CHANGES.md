## Release version: 2.0.1
* All header files are inside the headers folder.
* Binary for linux is built inside the bin/linux folder.

## Release version: 2.0.0
*  **BUG FIX**: Linux incompatability resolved. 
`typedef _int32 uint32_t` should be `typedef unsigend _int32 uint32_t`.
* Breaks backward-file compatability in Windows.

## Release version: 1.1.3
* **BUG FIX**: `_O_BINARY` flag is needed to prevent `_write` and `_read` to 
interpret CTRL+Z and end of file.
## Release version: 1.1.2
* Runs in Microsoft Windows. In Windows, build using build.bat
* BUG: Files encrypted in Linux is not getting decrypted properly in Windows
  and vice versa.

## Release version: 1.1.1

* **Change:** -D now works for both encryption and decryption. Deletes source
files if operation was successful.
* **Change:** Usage information changed to mention the above point.

## Release version: 1.1.0

* **Feature:** Output to stdout development complete.
* Usage changed: -N option.

* Added CHANGES.md file to keep track of the changes in versions.

## Release version: 1.0.3

* **BUG #0001 FIXED**: On read/write error, in `encrypt_decrypt ()` routine, 
  `perror ()` did not display the error code.
  **Resolution:** `close ()` before `perror ()`.

* **BUG #0002 FIXED**: With -D option, file got deleted, even when Encryption 
  failed.
  **Resolution:** Checked the result of `encrypt_decrypt` before deletion.

* **Feature:** Verbosity development complete.
* Usage changed: -v option.

* Code formatting changes in `main.c` and `tea.c`
* Added CHANGES.md file to keep track of the changes in versions.

## Release Version: 1.0.2      

* Feature: delete-file complete.
* Usage changes: -D option.
* Added `-Wextra` to build.sh
* LICENCE file added.

## Release Version: 1.0.1       
* Same as Version 1.0.0
* Minor changes to README.md file.

## Development Version: 1.0.0       

* Feature: feature-multiple-input complete.
* Usage changes: -I and -k options.
* One public function `encrypt_decrypt ()`.
* `structure op`;
* Removed `poc ()` routine.

