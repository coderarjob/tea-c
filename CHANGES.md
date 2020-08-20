
## Development Version: 1.0.0       

* Feature: feature-multiple-input complete.
* Usage changes: -I and -k options.
* One public function `encrypt_decrypt ()`.
* `structure op`;
* Removed `poc ()` routine.

## Release Version: 1.0.1       
* Same as Version 1.0.0
* Minor changes to README.md file.

## Release Version: 1.0.2      

* Feature: delete-file complete.
* Usage changes: -D option.
* Added `-Wextra` to build.sh
* LICENCE file added.

## Current Development Version: 
* Code formatting changes in `main.c` and `tea.c`
* BUG FIX: On read/write error, in `encrypt_decrypt ()` routine, `perror ()` 
  did not display the error code.
  **Conclusion:** `close ()` before `perror ()`.
* Added CHANGES.md file to keep track of the changes in versions.
