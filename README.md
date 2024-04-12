# Encrypterizer

## Authors

- Nathan Ceci
- Tyler Dao
- Liam Cabarle
- Ginbot Weldeb

## Overview

This program provides a simple way to encrypt and decrypt files using a command-line interface. It supports various options to customize the encryption process, including key generation and specific encryption modes.

## Features

- Encrypt and decrypt files using a specified key
- Generate a random key for encryption
- Support for different operational modes like copy and shred after encryption/decryption


## Usage

To use this program, run it from the command line with the necessary arguments. Below are the available flags and CLI arguments:

### Copy Mode
- C - (default) Copy mode, will create a copy of the original file after the operation.
- S - Shred mode, securely deletes the original file after the operation.
### Key Mode
- P - Specifies that the next argument is the password (key) for encryption/decryption.
- R - (default) Generate a random key for the encryption.
### Function Mode (REQUIRED)
- E - Encrypt the file.
- D - Decrypt the file.


## Examples

To encrypt a file with a specified key:

```bash

./fileEncryptor filename.txt -E -P yourpassword
```

To decrypt a file with a specified key:
```bash

./fileEncryptor filename.txt -D -P yourpassword
```
To encrypt a file and generate a random key:

```bash

./fileEncryptor filename.txt -E -R
```

## License

This project is licensed under the GNU General Public License Version 3, dated 29 June 2007. You can find the full text of the license in the [`LICENSE`](LICENSE) file included in the project or online at [GNU's website](https://www.gnu.org/licenses/gpl-3.0.en.html).
