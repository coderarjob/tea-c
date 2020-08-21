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

