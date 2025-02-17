# Mini-libc

## Overview  
**Mini-libc** is a minimalistic implementation of the C standard library for Linux systems, designed to serve as a lightweight replacement for glibc. It provides essential functionalities such as string handling, memory management, and POSIX file I/O, all implemented directly using the **Linux syscall interface** on `x86_64` architecture.  

This project was initially developed as part of a university assignment and has been refined to serve as a **learning resource for system programming, libc internals, and syscall-based development**.

---

## Features
- **Freestanding Implementation** – No dependencies on external libraries  
- **Direct Syscall Usage** – Implements functions using low-level Linux system calls  
- **Memory Management** – Implements `malloc()`, `calloc()`, `realloc()`, `free()`, and `mmap()`  
- **String Handling** – Implements `strcpy()`, `strlen()`, `strcmp()`, and more  
- **File I/O** – Implements `open()`, `close()`, `lseek()`, `stat()`, `truncate()`, etc.  
- **Time Handling** – Implements `nanosleep()` and `sleep()`  

---

## Directory Structure
```
mini-libc/
│── src/          # Main source code
│── samples/      # Example programs using mini-libc
│── tests/        # Automated tests
│── include/      # Header files
│── Makefile      # Build system
│── README.md     # Project documentation
```

---

## Implemented API Functions
### **1. String Handling (`<string.h>`)**
- `strcpy()`, `strcat()`, `strlen()`, `strncpy()`, `strncat()`, `strcmp()`, `strncmp()`, `strstr()`, `strrstr()`
- `memcpy()`, `memset()`, `memmove()`, `memcmp()`

### **2. File I/O (`<stdio.h>`, `<unistd.h>`, `<fcntl.h>`, `<sys/stat.h>`)**
- `open()`, `close()`, `lseek()`, `stat()`, `fstat()`, `truncate()`, `ftruncate()`
- `puts()`

### **3. Memory Management (`<stdlib.h>`, `<sys/mman.h>`)**
- `malloc()`, `calloc()`, `realloc()`, `free()`, `realloc_array()`
- `mmap()`, `mremap()`, `munmap()`

### **4. Time Handling (`<time.h>`)**
- `nanosleep()`, `sleep()`

### **5. Error Handling (`<errno.h>`)**
- Defines `errno` and updates it correctly in implemented functions.

---

## Building Mini-libc
To compile `mini-libc`, run:
```sh
cd src/
make
```
To build example programs:
```sh
cd samples/
make
```

---

## Running Tests
Mini-libc includes an automated test suite. To run all tests:
```sh
cd tests/
./run_all_tests.sh
```
To execute individual tests:
```sh
./test_malloc.sh
./test_string.sh
./test_open_close.sh
```

---

## Usage Example
To use `mini-libc` in a project, compile with `-nostdlib` and link against `mini-libc.a`:
```sh
gcc -nostdlib -o my_program my_program.c -Lpath/to/mini-libc -lmini-libc
```

---

## Resources
- [GNU libc manual](https://www.gnu.org/software/libc/manual/html_mono/libc.html)  
- [Linux syscalls documentation](https://man7.org/linux/man-pages/dir_section_2.html)  
- [musl - lightweight libc implementation](https://musl.libc.org/)  
- [glibc source code](https://sourceware.org/git/?p=glibc.git)  

---

## License
This project is licensed under the **MIT License**. See `LICENSE` for details.
